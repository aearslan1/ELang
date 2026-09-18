#include "../include/lexer.h"
#include <string>
#include <iostream>

/*
----TOKEN----
*/

//Filling token constructor
Token::Token(TokenType type, const std::string& value, int line, int column){
    this->type = type;
    this->value = value;
    this->line = line;
    this->column = column;
}

void Token::show(){
    std::cout << "{type: " << static_cast<int>(type) << " -> " << "value: " << value << "} (" << line << ", " << column << ")\n";
}

/*
----TOKEN LIST----
*/

//Filling token list constructor
TokenList::TokenList(){
    this->tokenList = {};
}

//Filling token list append method: appends token to token list
void TokenList::append(Token token){
    this->tokenList.push_back(token);
}

//Filling token get list method
std::vector<Token>& TokenList::getList(){
    return this->tokenList;
}

void TokenList::show(){
    for (unsigned int i = 0; i < TokenList::getList().size(); i++){
        TokenList::getList()[i].show();
    }
}

/*
----LEXER----
*/

//Filling lexer constructor
Lexer::Lexer(std::string& source){
    this->source = source;
    this->position = 0;
}

//Filling lexer peek method: returns current char in source
char Lexer::peek() const{
    return source[position];
}

//Filling lexer advance method: returns forward char in source and increase postion to one
char Lexer::advance(){
    if (position + 1 < this->source.length())
        return source[position++];
    return '\0';
}

//Filling lexer look method: returns postion + offset th char
char Lexer::look(const int& offset) const{
    if (position + offset < source.length())
        return source[position + offset];
    return '\0';
}

