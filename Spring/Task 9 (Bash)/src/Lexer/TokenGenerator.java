package Lexer;

@FunctionalInterface
public interface TokenGenerator<T> {
    T generateToken(String expression);
}