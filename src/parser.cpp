#include "../include/parser.h"
//ParserError

ParserError::ParserError(ParserErrorType type, const std::string& message, Token faultyToken) : faultyToken(faultyToken){
    this->type = type;
    this->message = message;
}

ParserError::~ParserError(){ std::exit(1); }

void ParserError::report(){
    bool columnMode = false;
    std::cerr << "ParserError at " << __FILE__ << "\n";
    std::cerr << "Type " << static_cast<int>(type) << ": " << message << "\n";
}

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

Token TokenStream::consume(TokenType tokenType){
    if (tokens.getList()[position].getType() == tokenType)
        return tokens.getList()[position];
    ParserError(ParserErrorType::UnexpectedToken, "there is a unexpected token", tokens.getList()[position]);
    return Token(TokenType::SKIP, "", 0, 0);
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
