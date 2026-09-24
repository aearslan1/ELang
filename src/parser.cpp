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

//TokenStream
TokenStream::TokenStream(TokenList tokens){
    this->position = 0;
    this->tokens = tokens;
}

Token TokenStream::peek(){
    return tokens.getList()[position];
}

Token TokenStream::look(const int& offset){
    return tokens.getList()[position + offset];
}

Token TokenStream::advance(){
    return tokens.getList()[++position];
}

//Parser
Parser::Parser(TokenList tokenList) : tokenStream(tokenList){
}
    
ASTNode* Parser::parse(){
    Token token = tokenStream.peek();
    while (token.getType() != TokenType::ENDFILE)
    {
        token = tokenStream.advance();
    }

    return nullptr;
}
