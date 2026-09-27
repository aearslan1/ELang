#include "../include/parser.h"

//ParserError
ParserError::ParserError(ParserErrorType type, const std::string& message, Token faultyToken) : faultyToken(faultyToken){
    this->type = type;
    this->message = message;
}

ParserError::~ParserError(){ std::exit(1); }

void ParserError::report(){
    std::cerr << "ParserError at " << __FILE__ << " in ";
    std::cerr << "(line: " << faultyToken.line + 1 << ", " << "column: " << faultyToken.column + 1 << ")\n";
    std::cerr << "Type " << static_cast<int>(type) << ": " << message << "\n";
}

//ASTNode
//-NumberNode
NumberNode::NumberNode(const int& value){
    this->type = NodeType::PUREINTEGER;
    this->value = value;
}

void NumberNode::show(){
    std::cout << "{type: " << static_cast<int>(type) << ", value: " << value << "}\n";
}

//-FloatNode
FloatNode::FloatNode(const float& value){
    this->type = NodeType::PUREFLOAT;
    this->value = value;
}

void FloatNode::show(){
    std::cout << "{type: " << static_cast<int>(type) << ", value: " << value << "}\n";
}

//-StringNode
StringNode::StringNode(const std::string& value){
    this->type = NodeType::PURESTRING;
    this->value = value;
}

void StringNode::show(){
    std::cout << "{type: " << static_cast<int>(type) << ", value: " << value << "}\n";
}

//-BoolNode
BoolNode::BoolNode(const bool& value){
    this->type = NodeType::PUREBOOL;
    this->value = value;
}

void BoolNode::show(){
    std::cout << "{type: " << static_cast<int>(type) << ", value: " << value << "}\n";
}

//NodeList
std::vector<std::unique_ptr<ASTNode>>& NodeList::getList(){
    return nodes;
}

void NodeList::append(std::unique_ptr<ASTNode> element){
    nodes.push_back(std::move(element));
}

void NodeList::show(){
    for (int i = 0; i < nodes.size(); i++)
        nodes[i]->show();
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
Parser::Parser(TokenList tokens) : tokenStream(tokens){
}

std::unique_ptr<ASTNode> Parser::parse(){
    Token token = tokenStream.peek();
    NodeList nodes;
    std::unique_ptr<ASTNode> root = nullptr;
    while (token.getType() != TokenType::ENDFILE)
    {
        
        token = tokenStream.advance();
    }
    return root;
}
