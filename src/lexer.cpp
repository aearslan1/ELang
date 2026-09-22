#include "../include/lexer.h"
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>


/*
   ----TOKEN----
   */

// Filling token constructor
Token::Token(TokenType type, const std::string &value, int line, int column)
{
  this->type = type;
  this->value = value;
  this->line = line;
  this->column = column;
}

void Token::show() const
{
  std::cout << "{type: " << static_cast<int>(type) << " -> "
            << "value: " << value << "} (" << line << ", " << column << ")\n";
}

std::string Token::getValue() const{
  return this->value;
}

TokenType Token::getType() const{
  return this->type;
}

/*
   ----TOKEN LIST----
   */

// Filling token list constructor
TokenList::TokenList() { this->tokenList = {}; }

// Filling token list append method: appends token to token list
void TokenList::append(Token token) { this->tokenList.push_back(token); }

// Filling token get list method
std::vector<Token> &TokenList::getList() { return this->tokenList; }

// Filling token show method
void TokenList::show()
{
  for (unsigned int i = 0; i < TokenList::getList().size(); i++)
  {
    TokenList::getList()[i].show();
  }
}

/*
   ----LEXER----
   */

// Filling lexer constructor
Lexer::Lexer(const std::string &source)
{
  this->source = source;
  this->position = 0;
  this->line = 0;
  this->column = 0;
}

// Filling lexer peek method: returns current char in source
char Lexer::peek() const { return source[position]; }

// Filling lexer advance method: returns forward char in source and increase
// postion to one
char Lexer::advance() { 
  this->column++;
  return source[++position]; 
}

// Filling lexer look method: returns postion + offset th char
char Lexer::look(const int &offset) const
{
  if (position + offset < source.length())
    return source[position + offset];
  return '\0';
}

char Lexer::jump(const int &offset) { return source[position += offset]; }

void Lexer::newline()
{
  this->line++;
  this->column = 0;
}

/*
   ---LEXERERROR---
   */

LexerError::LexerError(ErrorType type, const std::string &message,
                       unsigned int line, unsigned int column,
                       const std::string &source)
{
  this->type = type;
  this->message = message;
  this->line = line;
  this->column = column;
  this->source = source;
}

LexerError::~LexerError() { std::exit(1); }

std::string LexerError::errorPart(){
  std::vector<std::string> splitedSource = {};
  std::string stringPacket = "";

  for (int i = 0; i < source.length(); i++){
    if (source[i] == '\n'){
      splitedSource.push_back(stringPacket);
      stringPacket = "";
    }
    else
      stringPacket += source[i];
    
  }
  splitedSource.push_back(stringPacket);
  return splitedSource[this->line];
}

void LexerError::report()
{
  bool columnMode = false;
  std::cerr << "LexerError at " << __FILE__ << " in ";
  std::cerr << "(line: " << line + 1 << ", " << "column: " << column + 1 << ")\n";
  std::cerr << "\t" << errorPart() << "\n\t";
  for (int i = 0; i < errorPart().length(); i++){
    if (i == column){
        columnMode = true;
    }
    if (columnMode)
      std::cerr << "^";
    else
      std::cerr << " ";
    
  }
  std::cerr << "\n";
  std::cerr << "Type " << static_cast<int>(type) << ": " << message << "\n";
}

/*
   ----TOKENIZER----
*/

// Filling tokenizer constructor: routing source to lexer
Tokenizer::Tokenizer(const std::string &source) : lexer(source)
{
  this->tokenList = {};
  this->source = source;
}

Token Tokenizer::whitespace()
{
  char ch = lexer.peek();
  if (ch == '\n')
  {
    int startLine = lexer.line;
    int startColumn = lexer.column;
    lexer.newline();
    lexer.advance();
    return Token(TokenType::NEWLINE, "", startLine, startColumn);
  }
  lexer.advance();
  return Token(TokenType::SKIP, "", lexer.line, lexer.column);
}

Token Tokenizer::number()
{ 
  bool isFloat = false;
  char ch = lexer.peek();
  std::string parsedNumber = "";

  while (std::isdigit(ch))
  {
    parsedNumber += ch;
    ch = lexer.advance();
  }

  if (ch == '.')
  {
    if (std::isdigit(lexer.look(1)))
    {
      isFloat = true;
      parsedNumber += ch;
      ch = lexer.advance();
      while (std::isdigit(ch))
      {
        parsedNumber += ch;
        ch = lexer.advance();
      }
    }
    else
    {
      LexerError(ErrorType::FaultyFloat, "there is a no number after '.'",
                 lexer.line, lexer.column, source)
          .report();
    }
  }
  if (isFloat)
  {
    return Token(TokenType::FLOAT, parsedNumber, lexer.line, lexer.column);
  }
  return Token(TokenType::INTEGER, parsedNumber, lexer.line, lexer.column);
}

Token Tokenizer::alpha()
{
  char ch = lexer.peek();
  std::string parsedAlpha = "";

  while (std::isalpha(ch))
  {
    parsedAlpha += ch; // adding char to blank string
    ch = lexer.advance();
  }

  if (std::isdigit(ch) || ch == '_')
  { // is parsedString end with '_' or
    // number?
    while (std::isalpha(ch) || std::isdigit(ch) || ch == '_')
    {
      parsedAlpha += ch;
      ch = lexer.advance();
    }
  }

  //Variable keywords
  if (parsedAlpha == "id")
    return Token(TokenType::DEFINE, parsedAlpha, lexer.line, lexer.column);

  else if (parsedAlpha == "const")
    return Token(TokenType::CONST, parsedAlpha, lexer.line, lexer.column);

  else if (parsedAlpha == "ref")
    return Token(TokenType::REF, parsedAlpha, lexer.line, lexer.column);
    
  else if (parsedAlpha == "true" || parsedAlpha == "false")
    return Token(TokenType::BOOL, parsedAlpha, lexer.line, lexer.column);

  // Comparison keywords
  else if (parsedAlpha == "if")
    return Token(TokenType::IF, parsedAlpha, lexer.line, lexer.column);

  else if (parsedAlpha == "elif")
    return Token(TokenType::ELIF, parsedAlpha, lexer.line, lexer.column);

  else if (parsedAlpha == "else")
    return Token(TokenType::ELSE, parsedAlpha, lexer.line, lexer.column);

  // Function keywords
  else if (parsedAlpha == "function")
    return Token(TokenType::FUNCDEFINE, parsedAlpha, lexer.line, lexer.column);

  else if (parsedAlpha == "return")
    return Token(TokenType::RETURN, parsedAlpha, lexer.line, lexer.column);

  // Logical operator keyword
  else if (parsedAlpha == "and")
    return Token(TokenType::AND, parsedAlpha, lexer.line, lexer.column);

  else if (parsedAlpha == "or")
    return Token(TokenType::OR, parsedAlpha, lexer.line, lexer.column);

  else if (parsedAlpha == "xor")
    return Token(TokenType::XOR, parsedAlpha, lexer.line, lexer.column);

  else if (parsedAlpha == "not")
    return Token(TokenType::NOT, parsedAlpha, lexer.line, lexer.column);

  // Loops
  else if (parsedAlpha == "while")
    return Token(TokenType::WHILE, parsedAlpha, lexer.line, lexer.column);

  else if (parsedAlpha == "loop")
    return Token(TokenType::LOOP, parsedAlpha, lexer.line, lexer.column);

  else if (parsedAlpha == "break")
    return Token(TokenType::BREAK, parsedAlpha, lexer.line, lexer.column);

  else if (parsedAlpha == "continue")
    return Token(TokenType::CONTINUE, parsedAlpha, lexer.line, lexer.column);

  // Library keywords
  else if (parsedAlpha == "include")
    return Token(TokenType::INCLUDE, parsedAlpha, lexer.line, lexer.column);
  // Return normal ID
  return Token(TokenType::ID, parsedAlpha, lexer.line, lexer.column);

  return Token(TokenType::ID, parsedAlpha, lexer.line, lexer.column);
}

Token Tokenizer::string()
{
  char ch = lexer.advance();
  std::string parsedString = "";

  while (ch != '"' && ch != '\0')
  {

    if (ch == '\\')
    {
      ch = lexer.advance();

      switch (ch)
      {
      case 'n':
        parsedString += '\n';
        break;

      case 't':
        parsedString += '\t';
        break;

      case 'r':
        parsedString += '\r';
        break;

      case '"':
        parsedString += '"';
        break;

      case '\\':
        parsedString += '\\';
        break;

      default:
        LexerError(ErrorType::InvalidEscapeSequence, "invalid escape sequence",
                   lexer.line, lexer.column, source)
            .report();
        break;
      }

      ch = lexer.advance();
      continue;
    }

    parsedString += ch;
    ch = lexer.advance();
  }
  if (ch == '\0')
  {
    LexerError(ErrorType::FaultyString, "there is a string that is not closed",
               lexer.line, lexer.column, source)
        .report();
  }

  lexer.advance();

  return Token(TokenType::STRING, parsedString, lexer.line, lexer.column);
}

Token Tokenizer::op()
{
  char ch = lexer.peek();

  // Arithmetic Operators (arrow)
  switch (ch)
  {
  case '+':
    if (lexer.look(1) == '+')
    {
      ch = lexer.jump(2);
      return Token(TokenType::PLUSPLUS, "++", lexer.line, lexer.column);
    }
    ch = lexer.advance();
    return Token(TokenType::PLUS, "+", lexer.line, lexer.column);

  case '-':
    if (lexer.look(1) == '-')
    {
      ch = lexer.jump(2);
      return Token(TokenType::MINUSMINUS, "--", lexer.line, lexer.column);
    }

    else if (lexer.look(1) == '>')
    {
      ch = lexer.jump(2);
      return Token(TokenType::ARROW, "->", lexer.line, lexer.column);
    }

    ch = lexer.advance();
    return Token(TokenType::MINUS, "-", lexer.line, lexer.column);

  case '*':
    lexer.advance();
    return Token(TokenType::MULT, "*", lexer.line, lexer.column);
    lexer.advance();
  case '/':
    lexer.advance();
    return Token(TokenType::DIVIDE, "/", lexer.line, lexer.column);
  case '%':
    lexer.advance();
    return Token(TokenType::MODULO, "%", lexer.line, lexer.column);

  // Comparison opeartors
  case '=':
    if (lexer.look(1) == '=')
    {
      ch = lexer.jump(2);
      return Token(TokenType::EQUAL, "==", lexer.line, lexer.column);
    }
    ch = lexer.advance();
    return Token(TokenType::ASSIGN, "=", lexer.line, lexer.column);

  case '!':
    if (lexer.look(1) == '=')
    {
      ch = lexer.jump(2);
      return Token(TokenType::NOTEQUAL, "!=", lexer.line, lexer.column);
    }
    ch = lexer.advance();
    return Token(TokenType::NOT, "!", lexer.line, lexer.column);

  case '<':
    if (lexer.look(1) == '=')
    {
      ch = lexer.jump(2);
      return Token(TokenType::LESSEQUAL, "<=", lexer.line, lexer.column);
    }
    ch = lexer.advance();
    return Token(TokenType::LESS, "<", lexer.line, lexer.column);

  case '>':
    if (lexer.look(1) == '=')
    {
      ch = lexer.jump(2);
      return Token(TokenType::GREATEREQUAL, ">=", lexer.line, lexer.column);
    }
    ch = lexer.advance();
    return Token(TokenType::GREATER, ">", lexer.line, lexer.column);

  default:
    LexerError(ErrorType::InvalidSymbol, "there is a invalid symbol",
               lexer.line, lexer.column, source)
        .report();

    return Token(TokenType::SKIP, "", lexer.line, lexer.column);
  }
}

Token Tokenizer::punctuation()
{
  char ch = lexer.peek();
  switch (ch)
  {
  case '(':
    lexer.advance();
    return Token(TokenType::LPAREN, "(", lexer.line, lexer.column);
  case ')':
    lexer.advance();
    return Token(TokenType::RPAREN, ")", lexer.line, lexer.column);
  case '[':
    lexer.advance();
    return Token(TokenType::LBRACKET, "[", lexer.line, lexer.column);
  case ']':
    lexer.advance();
    return Token(TokenType::RBRACKET, "]", lexer.line, lexer.column);
  case '{':
    lexer.advance();
    return Token(TokenType::LBRACE, "{", lexer.line, lexer.column);
  case '}':
    lexer.advance();
    return Token(TokenType::RBRACE, "}", lexer.line, lexer.column);
  case '.':
    lexer.advance();
    return Token(TokenType::DOT, ".", lexer.line, lexer.column);
  case ',':
    lexer.advance();
    return Token(TokenType::COMMA, ",", lexer.line, lexer.column);
  case ':':
    lexer.advance();
    return Token(TokenType::COLON, ":", lexer.line, lexer.column);
  case ';':
    lexer.advance();
    return Token(TokenType::SEMICOLON, ";", lexer.line, lexer.column);
  default:
    LexerError(ErrorType::UnexpectedChar, "there is a unexpected token",
               lexer.line, lexer.column, source)
        .report();
  }
  return Token(TokenType::SKIP, "", lexer.line, lexer.column);
}

TokenList Tokenizer::tokenize()
{
  char ch = lexer.peek();

  while (ch != '\0')
  {
    ch = lexer.peek();

    if (std::isalpha(ch))
    {
      tokenList.append(alpha());
    }
    else if (std::isdigit(ch))
    {
      tokenList.append(number());
    }
    else if (ch == '"')
    {
      tokenList.append(string());
    }
    else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' ||
             ch == '<' || ch == '>' || ch == '=' || ch == '!')
    {
      tokenList.append(op());
    }
    else if (ch == '.' || ch == ',' || ch == ':' || ch == ';' || ch == '(' ||
             ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}')
    {
      tokenList.append(punctuation());
    }
    else if (ch == '\n' || ch == ' ')
    {
      Token token = whitespace();
      if (token.type != TokenType::SKIP)
        tokenList.append(token);
    }

    else{
      if (ch != '\0'){
        LexerError(ErrorType::UnexpectedChar, "there is a unexpected char", lexer.line, lexer.column, source).report();
      }
    }
    
  }
  tokenList.append(Token(TokenType::ENDFILE, "", lexer.line, lexer.column));
  return tokenList;
}
