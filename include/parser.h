#pragma once
#include "lexer.h"
#include <string>

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

class Parser{
    TokenList tokens;
    unsigned int position;

    public:
        Parser(TokenList tokens);
};