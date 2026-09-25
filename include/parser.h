#pragma once
#include "lexer.h"
#include <string>
//Node Types
enum class ParserErrorType{
    UnexpectedToken,
};

enum class NodeType{
    //Main node
    PROGRAM,

    //DATATYPES
    PUREINTEGER,
    PUREFLOAT,
    PURESTRING,
    PUREBOOL,
    PURELIST,
    IDENTIFIER,
    BINARYEXP,
    UNARYEXP,
    
    //Statements
    ASSIGMENT,
    IFSTATEMENT,
    WHILESTATEMENT,
    LOOPSTATEMENT,

    //FUNCTIONS
    FUNCTIONDEF,
    FUNCTIONCALL,
    RETURNSTATEMENT,
};
class ParserError{
    ParserErrorType type;
    std::string message;
    Token faultyToken;
    
    public:
        
        ParserError(ParserErrorType type, const std::string& message, Token faultyToken);
        ~ParserError();
        std::string errorPart();
        void report();
};
//ASTNode
class ASTNode
{
    public:
        virtual ~ASTNode() = default;  
};

class NumberNode : public ASTNode{
    public:
        int value;
        NumberNode(int value);
};

class FloatNode : public ASTNode{
    public:
        double value;
        FloatNode(double value);
};

class IdentifierNode : public ASTNode{
    public:
        std::string value;
        IdentifierNode(const std::string& value);
};

class BinaryExpressionNode : public ASTNode{
    

    public:
        ASTNode* left;
        TokenType op;
        ASTNode* right;
        BinaryExpressionNode(ASTNode* left, TokenType op, ASTNode* right);
};

class TokenStream{
    unsigned int position;
    TokenList tokens;

    public:
        TokenStream(TokenList tokens);

        Token peek() ;
        Token advance();
        Token look(const int& offset);
        Token consume(TokenType tokenType);
};

class Parser{
    TokenStream tokenStream;

    public:
        Parser(TokenList tokenStream);
        ASTNode* parse();
};