#ifndef header
#define header
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <vector>
#include <iomanip>

extern std::string f_open(void);
// extern std::ofstream fout("outputfile.txt");                    //creates file object to write out results into
extern std::string file;                               //creates string to hold name of file to be parsed

extern std::vector<std::string> lexemest;                  /*creates vector to pass into lexer function.  result of parsed lexemes from str1 will go in here*/
extern std::vector<std::string> tokenst;                   /*creates vector to pass into lexer function.  name of tokens of parsed lexemes from str1 will go in here*/

extern std::vector<std::string> keywords;   //list of accepted keywords
extern std::vector<std::string> operators;                //list of accepted operators
extern std::vector<std::string> separators;       //list of accepted separators

int char_to_col(char c, std::vector<std::string>op, std::vector<std::string>sep);  /*returns the column an inputted character is in so we can identify next state to be transitioned into in FSM (table located in lexer() )*/
std::string rowName(int i);                                                       //returns the row name in table of inputted character
bool isoperator(std::string d, std::vector<std::string>op);                       //returns true if character is an operator
bool isseparator(std::string e, std::vector<std::string>sep);                     //returns true if character is a separator

extern void lexer(std::string s, std::vector<std::string>& lexemestack, std::vector<std::string>& tokenstack);  //parses the input string

void Statement(std::ofstream& fout);
bool AssignStatement(int& l, std::vector<std::string> lexemes, std::vector<std::string> tokens, std::ofstream& fout);
bool DecStatement(int& l, std::vector<std::string> lexemes, std::vector<std::string> tokens, std::ofstream& fout);

bool expr(int& l, std::vector<std::string> lexemes, std::vector<std::string> tokens, std::ofstream& fout);
bool exprPrime(int& l, std::vector<std::string> lexemes, std::vector<std::string> tokens, std::ofstream& fout);
bool term(int& l, std::vector<std::string> lexemes, std::vector<std::string> tokens, std::ofstream& fout);
bool termPrime(int& l, std::vector<std::string> lexemes, std::vector<std::string> tokens, std::ofstream& fout);
bool factor(int& l, std::vector<std::string> lexemes, std::vector<std::string> tokens, std::ofstream& fout);
bool assignment(int& l, std::vector<std::string> lexemes, std::vector<std::string> tokens, std::ofstream& fout);
bool decl(int& l, std::vector<std::string> lexemes, std::vector<std::string> tokens, std::ofstream& fout);

bool ID(int& l, std::vector<std::string> lexemes, std::vector<std::string> tokens, std::ofstream& fout);
bool Num(int& l, std::vector<std::string> lexemes, std::vector<std::string> tokens, std::ofstream& fout);
bool Empty(std::ofstream& fout);
bool Type(int& l, std::vector<std::string> lexemes, std::vector<std::string> tokens, std::ofstream& fout);

void match(int& l, std::string t, std::vector<std::string> lexemes, std::vector<std::string> tokens,std::ofstream& fout);//match is used when we are at a terminal(when we are returning true or false at a function without calling a function, based off a lexeme or token). If our function is non-terminal at a lexemes or token, we do not call match then.

#endif