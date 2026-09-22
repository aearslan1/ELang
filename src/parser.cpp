#include "../include/parser.h"

//NumberNode
NumberNode::NumberNode(int value){
    this->value = value;
}

//FloatNode
FloatNode::FloatNode(double value){
    this->value = value;
}

//IdentifierNode
IdentifierNode::IdentifierNode(const std::string& value){
    this->value = value;
}

//BinaryExperssionNode
BinaryExpressionNode::BinaryExpressionNode(ASTNode* left, TokenType op, ASTNode* right){
    this->left = left;
    this->op = op;
    this->right = right;
}

//Parser
Parser::Parser(TokenList tokens){
    this->position = 0;
    this->tokens = tokens;
}




