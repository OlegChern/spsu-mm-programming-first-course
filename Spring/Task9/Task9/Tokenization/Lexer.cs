using System;
using System.Collections.Generic;
using System.Diagnostics.Contracts;
using System.Text.RegularExpressions;

namespace Task9.Tokenization
{
    public static class Lexer
    {
        // NOTE: make sure to update simultaneously with Commands.cs
        static readonly IDictionary<string, Command> Commands =
            new Dictionary<string, Command>(StringComparer.InvariantCultureIgnoreCase)
            {
                {"echo", Command.Echo},
                {"exit", Command.Exit},
                {"pwd", Command.Pwd},
                {"cat", Command.Cat},
                {"wc", Command.Wc}
            };

        // NOTE: make sure to update simultaneously with Operator.cs
        static readonly IDictionary<char, Operator> Operators = new Dictionary<char, Operator>
        {
            {'=', Operator.Assign},
            {'|', Operator.Forward}
        };

        const char VariableMarker = '$';

        [Pure]
        public static IEnumerable<Token> Tokenize(string input)
        {
            int index = 0;

            while (index < input.Length)
            {
                index = GetWordStart(input, index);
                yield return GetNextToken(input, index);
                index += GetWordLength(input, index);
            }
        }

        [Pure]
        public static Token GetNextToken(string input, int index)
        {
            int length = GetWordLength(input, index);

            string tokenString = input.Substring(index, length);

            return ParseToken(tokenString);
        }

        [Pure]
        public static Token ParseToken(string tokenString)
        {
            if (!IsValidToken(tokenString))
            {
                throw new InvalidTokenException(tokenString);
            }

            if (Commands.ContainsKey(tokenString))
            {
                return new CommandToken(Commands[tokenString]);
            }

            if (int.TryParse(tokenString, out int result))
            {
                return new IntegerConstantToken(result);
            }

            if (tokenString.StartsWith("'") && tokenString.EndsWith("'") ||
                tokenString.StartsWith("\"") && tokenString.EndsWith("\""))
            {
                return new StringConstantToken(tokenString.Substring(1, tokenString.Length - 2));
            }

            if (tokenString.StartsWith("$"))
            {
                return new VariableToken(tokenString.Substring(1));
            }

            if (tokenString.Length == 1 && Operators.ContainsKey(tokenString[0]))
            {
                return new OperatorToken(Operators[tokenString[0]]);
            }

            return new UnknownToken(tokenString);
        }

        [Pure]
        public static bool IsValidToken(string tokenString)
        {
            return !string.IsNullOrEmpty(tokenString) &&
                   // Oh my god, what have I done...
                   Regex.IsMatch(tokenString, @"^-?\d*\z|^\$?[a-zA-Z_]\w*\z|^[\|=]\z|^(['""])(?!.*\1.*\1).*\1\z");
        }

        [Pure]
        public static int GetWordStart(string input, int index)
        {
            while (index < input.Length && IsWhiteSpace(input[index]))
            {
                index++;
            }

            return index;
        }

        [Pure]
        public static int GetWordLength(string input, int start)
        {
            if (start >= input.Length)
            {
                throw new ArgumentOutOfRangeException(nameof(start));
            }

            if (Operators.ContainsKey(input[start]))
            {
                return 1;
            }

            int charIndex = start;

            switch (input[charIndex])
            {
                case '\'':
                case '\"':
                    char quote = input[charIndex];
                    charIndex++;

                    while (charIndex < input.Length && input[charIndex] != quote)
                    {
                        charIndex++;
                    }

                    if (charIndex == input.Length)
                    {
                        return charIndex - start;
                    }

                    return charIndex - start + 1;

                case VariableMarker:
                    charIndex++;
                    break;
            }

            while (charIndex < input.Length && !IsWhiteSpace(input[charIndex]) &&
                   !Operators.ContainsKey(input[charIndex]))
            {
                charIndex++;
            }

            return charIndex - start;
        }

        [Pure]
        public static bool IsWhiteSpace(char c)
        {
            return Regex.IsMatch(c.ToString(), @"\s");
        }
    }
}
