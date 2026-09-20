#pragma once
#include <iostream>
#include <string>
#include <vector>

//Error types
enum class ErrorType{
    UnexpectedChar,
    FaultyFloat,
    FaultyString,
    InvalidEscapeSequence,
    InvalidSymbol
};

//Token types
enum class TokenType {
    //Variable and datatypes
    ID,
    STRING,
    INTEGER,
    FLOAT,
    LIST,
    BOOL,
    ASSIGN,
    DEFINE,

    //Conditional statements
    IF,
    ELIF,
    ELSE,

    // Functions
    FUNCDEFINE,
    RETURN,
    ARROW,

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
    PLUSPLUS,
    MINUS,
    MINUSMINUS,
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
    LBRACKET,
    RBRACKET,
    LBRACE,
    RBRACE,

    NEWLINE,
    TAB,
    SKIP,
    ENDFILE,
    UNKNOWN,

    DOT,
    COMMA,
    COLON,
    SEMICOLON,

    INCLUDE,

};

//Token class
struct Token {
    //Token type
    TokenType type;

    //Token value
    std::string value;

    //Line and column info
    int line;
    int column;


    Token(TokenType type, const std::string& value, int line, int column);
    void show() const;
};

//TokenList class
class TokenList{
    std::vector<Token> tokenList;

    public:
        TokenList();
        void append(Token token);
        std::vector<Token>& getList(); //reference because copy is unhealthy
        void show();
};

//Lexer class
class Lexer {
    //string index
    unsigned int position;
    std::string source;


    public:
        unsigned int line;
        unsigned int column;
        //get source code
        explicit Lexer(const std::string& source);

        //get current char
        char peek() const;

        //get current char and resume position
        char advance();

        //get position + offset char
        char look(const int& offset) const;

        char jump (const int& offset);
        //add 1 to row info and turn to 0 to column
        void newline();
};

//LexerError class
class LexerError{
    ErrorType type;
    std::string message;
    unsigned int line;
    unsigned int column;
    std::string source;

    public:
        
        LexerError(ErrorType type, const std::string& message, unsigned int line, unsigned int column, const std::string& source);
        ~LexerError();
        std::string errorPart();
        void report();
};

//Tokenizer class
class Tokenizer{
    Lexer lexer;
    TokenList tokenList;
    std::string source;

    public:
        explicit Tokenizer(const std::string& source);
        Token whitespace(); // NEWLINE, TAB ...
        Token number(); // INTEGER, FLOAT
        Token alpha(); // KEYWORDS, ID, FUNCTION
        Token string(); // "HELLO WORLD!"
        Token op(); // +, -, *, /, %
        Token punctuation(); // (, ), [, ], {, }

        TokenList tokenize();
};
