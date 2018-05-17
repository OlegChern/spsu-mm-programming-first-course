import Commands.CommandExecutionFailedException;
import Lexer.StringLexer;
import Lexer.TokenGenerator;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class Main {
    
    private static StringLexer<Token> initStringLexer() {
        TokenTypes name = TokenTypes.NAME;
        TokenGenerator<Token> nameGenerator = string -> new Token(name, string);
    
        List<TokenTypes> specTokens = new ArrayList<>(Arrays.asList(TokenTypes.values()));
        specTokens.remove(name);
        Map<String, TokenGenerator<Token>> specSymbolsMap = specTokens.stream().collect(Collectors.toMap(
                TokenTypes::getRegexp,
                tokenType -> (string -> new Token(tokenType, string))
        ));
        
        return new StringLexer<>(specSymbolsMap, nameGenerator);
    }
    
    public static void main(String[] args) throws IOException {
        BufferedReader input = new BufferedReader(new InputStreamReader(System.in));

        StringLexer<Token> stringLexer = initStringLexer();
        StackExecutor executor = new StackExecutor();

        while (true) {
            System.out.print(">>> ");
            String expression = null;
            try {
                expression = input.readLine().trim();
            } catch (NullPointerException e) {
                System.exit(0);
            }
    
            if (expression.equals("exit")) {
                break;
            }
            Token[] tokens = stringLexer.tokenize(expression).toArray(new Token[0]);

            try {
                executor.run(tokens);
            } catch (FileNotFoundException | IncorrectSyntaxException | UnknownVariableException | IncorrectSemanticsException e) {
                System.err.println(e.getMessage());
            } catch (CommandExecutionFailedException ignored) {
                // it was already printed to the specified error stream
            }
        }
    }
}
