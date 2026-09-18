#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iostream>

enum class TokenType {
    //Variable and datatypes
    ID,
    STRING,
    INTEGER,
    FLOAT,
    LIST,
    ASSIGN,
    DEFINE,

    //Conditional statements
    IF,
    ELIF,
    ELSE,

    // Functions
    FUNCDEFINE,
    RETURN,
    FUNCINVOKE,

    // Comparison Operators
    EQUAL,
    NOTEQUAL,
    GREATER,
    LESS,
    GREATEREQUAL,
    LESSEQUAL,

    //Operators
    //-Arithmetic Operators
    PLUS,
    MINUS,
    MULT,
    DIVIDE,
    MODULO,

    //-Logical Operators
    AND,
    OR,
    NOT,
    XOR,

    //Loops
    WHILE,
    LOOP,
    BREAK,
    CONTINUE,

    //Other
    LPAREN,
    RPAREN,
    LRACKET,
    RBRACKET,
    LBRACE,
    RBRACE,

    NEWLINE,
    ENDFILE,
    UNKNOWN,

    DOT,
    COMMA,
    COLON,
    SEMICOLON,

    INCLUDE,

};

struct Token {
    //Token type
    TokenType type;

    //Token value
    std::string value;

    //Line and column info
    int line;
    int column;


    Token(TokenType type, const std::string& value, int line, int column);
    void show();
};

class TokenList{
    std::vector<Token> tokenList;

    public:
        TokenList();
        void append(Token token);
        std::vector<Token>& getList(); //reference because copy is unhealthy
        void show();
};

class Lexer {
    //string index
    unsigned int position;
    std::string source;
    public:
        //get source code
        explicit Lexer(std::string& source);

        //get current char
        char peek() const;

        //get current char and resume position
        char advance();
        char look(const int& offset) const;
};
