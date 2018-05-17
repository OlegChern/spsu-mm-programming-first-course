package Lexer;


import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Parses string on tokens of {@code type T}.
 * All special tokens are taken from the given {@code Map<String, TokenGenerator<T>> specSymbolsMap}.
 * Any position in the string due to the space that will not be recognized as one from this map
 * will be supposed as {@linkplain #word}.
 *
 * @param <T>
 */
public class StringLexer<T> {
    
    private List<TokenMatcher> specSymbols;
    private TokenGenerator<T> word;
    
    private class TokenMatcher {
        Matcher matcher;
        TokenGenerator<T> generator;
        
        TokenMatcher(Matcher matcher, TokenGenerator<T> generator) {
            this.matcher = matcher;
            this.generator = generator;
        }
    }
    
    public StringLexer(Map<String, TokenGenerator<T>> specSymbolsMap, TokenGenerator<T> word) {
        this.specSymbols = new ArrayList<>();
        
        // all regexps must be tested from the beginning of the substrings
        // '^' guarantee this and increases a performance of the tokenize() method
        specSymbolsMap.forEach((regexp, generator) ->
                specSymbols.add(new TokenMatcher(
                        Pattern.compile(regexp.charAt(0) == '^' ? regexp : "^" + regexp).matcher(""),
                        generator
                ))
        );
        
        this.word = word;
    }
    
    public List<T> tokenize(String expression) {
        List<T> tokens = new ArrayList<>();
        
        int firstWordSymbol = -1;
        for (int i = 0; i < expression.length(); i++) {
            boolean specSymbolFound = false;
            
            for (TokenMatcher specSymbol : specSymbols) {
                specSymbol.matcher.reset(expression.substring(i));
                if (specSymbol.matcher.find()) {
                    String result = specSymbol.matcher.group(0);
                    
                    specSymbolFound = true;
                    if (firstWordSymbol != -1) {
                        tokens.add(word.generateToken(expression.substring(firstWordSymbol, i)));
                        firstWordSymbol = -1;
                    }
    
                    tokens.add(specSymbol.generator.generateToken(result));
                    i += result.length() - 1;
                    break;
                }
            }
            
            if (!specSymbolFound && firstWordSymbol == -1) {
                firstWordSymbol = i;
            }
        }
    
        if (firstWordSymbol != -1) {
            tokens.add(word.generateToken(expression.substring(firstWordSymbol, expression.length())));
        }
        
        return tokens;
    }
}
