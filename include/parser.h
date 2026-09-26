#pragma once
#include "lexer.h"
#include <string>
#include <vector>
#include <memory>

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

//ParserError
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
        Parser(TokenList tokens);
        std::unique_ptr<ASTNode> parse();

        std::unique_ptr<ASTNode> parseInteger();
        std::unique_ptr<ASTNode> parseFloat();
        std::unique_ptr<ASTNode> parseList();
        std::unique_ptr<ASTNode> parseString();
        std::unique_ptr<ASTNode> parseBoolean();
        std::unique_ptr<ASTNode> parseIdentifier();

        std::unique_ptr<ASTNode> parseExpression();
        std::unique_ptr<ASTNode> parsePrimary();
        std::unique_ptr<ASTNode> parseBinaryExpression();
        std::unique_ptr<ASTNode> parseAssignment();
        std::unique_ptr<ASTNode> parseIfStatement();
        std::unique_ptr<ASTNode> parseWhileStatement();
        std::unique_ptr<ASTNode> parseLoopStatement();
        std::unique_ptr<ASTNode> parseFunctionDefinition();
        std::unique_ptr<ASTNode> parseFunctionCall();
        std::unique_ptr<ASTNode> parseReturnStatement();
        std::unique_ptr<ASTNode> parseUnaryExpression();

};

