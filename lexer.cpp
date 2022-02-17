//
//  main.cpp
//  CPSC 323 Project 1
//
//  Created  on 2/15/21.
//
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <vector>
#include <iomanip>
#include "header.hpp"

//std::ofstream fout("outputfile.txt");
std::string file = "";                              
std::vector<std::string> lexemest;
std::vector<std::string> tokenst;

std::vector<std::string>keywords {"int","float","bool","True","False","if","else","then", "endif", "endelse", "whileend", "while", "do", "enddo", "for", "endfor", "STDinput", "STDoutput", "and", "or", "not"};   //list of accepted keywords
std::vector<std::string>operators {"*","+","-","=","/",">","<","%"};                //list of accepted operators
std::vector<std::string>separators {"(",")","{","}","[","]",",",".",":",";"};       //list of accepted separators

/*
int main() {
    std::string str1; 
    std::ofstream fout(file);
    str1 = f_open();
    
    lexer(str1, lexemest, tokenst);                     //calls lexer function
    fout<<"      TOKEN        -    Lexeme   \n\n";        //header for output file to make it look neater
    for(int i = 0;i<lexemest.size();i++)                  //while function outputs results of parsed lexemes and their token names stored in lexemest and tokenst
    {
      fout << std::setw(13)<< tokenst[i] << "      =  " << std::setw(8) << lexemest[i] << "\n";    //setw organizes output and makes it look even and neat
    }
    lexemest.clear();                                 //clears lexemest
    tokenst.clear();                                  //clears tokenst
    fout.close();                                     //closes output file

    return 0;                                         //end of main function
}
*/


std::string f_open(){
    std::string str;
    std::string str1;                                     /*I had to create two strings to read in and store input from file in, I'm not sure if there's an easier way to do this*/

    std::cout<< "Enter the full name of a file to be analyzed (file must be in the same directory as executable) and hit enter: ";  //prompts user to enter file name to be parsed
    std::cin >>file;                                         //file name entered is inputted to string
    std::ifstream fin(file);                                 //creates file object to open file to be parsed

    if(fin.is_open()){                                       // tests if file is open, outputs confirmation if it is
        std::cout<< "\nInput file \"" << file << "\" opened succesfully\n\n";
    }
    else{
        std::cout<< "\nInput file \"" << file << "\" could not be opened\n\n";      // if file is not able to open, outputs this to user
     // throw std::invalid_argument("Input file could not be opened\n");      //ignore this for now
    }
    while(getline(fin,str)){                                  //stores characters of inputted file into str1
        str1 += str;
    }

    std::cout<< "Enter the full name of the output file (in the same directory of the executable) and hit enter: ";
    std::cin >>file;
    std::ofstream fout(file);

    if(fout.is_open()){                                             // tests if file is open, outputs confirmation if it is
        std::cout<< "Output file \"" << file << "\" opened succesfully\n\n";
        }
        else{
            std::cout<< "Output file \"" << file << "\" could not be opened\n\n";         // if file is not able to open, outputs this to user
     //throw std::invalid_argument("Output file could not be opened\n");        //ignore this for now
        }

    if(fin.is_open())
        fin.close();                                      //closes input file

    return str1;
}

bool isoperator(std::string d, std::vector<std::string>op){        /* function takes a string with a character in it and a list of operators, then compares the two to test whether character is an operator */
    for(int i = 0;i<op.size();i++){
        if(d==op[i])
            return true;
        }
        return false;
}

bool isseparator(std::string e, std::vector<std::string>sep){     /* function takes a string with a character in it and a list of separators, then compares the two to test whether character is a separator */
    for(int i = 0;i<sep.size();i++){
        if(e==sep[i])
            return true;
        }
        return false;
}

int char_to_col(char c, std::vector<std::string>op, std::vector<std::string>sep){    /*matches character to column in 2D array. see table image in lexer for reference*/
    std::string cToS(1, c);      /*converts char c to string so that it can be tested against operators & separators.  Operators & separators are stored as strings, cannot directly compare chars to string types */
    if(isalpha(c)){//letters are designated in 1st column of fsmTable, column index #0, 2nd index of 2D array
      return 0;
    }
    else if(isdigit(c)){//digits are designated in 2nd column of fsmTable, column index #1, 2nd index of 2D array
      return 1;
    }
    else if(c=='.'){//periods are designated in 3rd column of fsmTable, column index #2, 2nd index of 2D array
      return 2;
    }
    else if(c=='_'){  //underscores are designated in 4th column of fsmTable, column index #3, 2nd index of 2D array
      return 3;
    }
    else if(c=='$'){  //dollar bills are designated in 5th column of fsmTable, column index #4, 2nd index of 2D array
      return 4;
    }
    else if(c=='!'){  //dollar bills are designated in 2nd column of fsmTable, column index #5, 2nd index of 2D array
      return 5;
    }
    else if(isoperator(cToS, op)){  //operators are designated in 2nd column of fsmTable, column index #6, 2nd index of 2D array
      return 6;
    }
    else if(isseparator(cToS, sep) ){ //separators are designated in 2nd column of fsmTable, column index #7, 2nd index of 2D array
      return 7;
    }
    else if(isspace(c)){          //whitespace is designated in 2nd column of fsmTable, column index #8, 2nd index of 2D array
      return 8;
    }
    else
      return 9;//formerly return 0
}

std::string rowName(int i){     //returns name of row (state) of a given number in the fsmTable
    if(i == 0){                //number 0 refers to the space state
        return "SPACE";
    }
    else if(i == 1){          //number 1 refers to the identifier state
        return "IDENTIFIER";
    }
    else if(i == 2){          //number 2 refers to the integer state
        return "INTEGER";
    }
    else if(i == 3){        //number 3 refers to the float state
        return "FLOAT";
    }
    else if(i == 4){        //number 4 refers to the float state
        return "OPERATOR";
    }
    else if(i == 5){        //number 5 refers to the float state
        return "SEPARATOR";
    }
    else if(i == 6){        //number 6 refers to the float state
        return "COMMENT";
    }
    else if(i == 7){        //number 7 refers to the float state
        return "INVALID";
    }
    else                      //this should never happen
        return "Not found";
}

void lexer(std::string s, std::vector<std::string>& lexemestack, std::vector<std::string>& tokenstack){    /*lexer function takes in string s to parse, puts results on lexemestack and tokenstack */
    //{SPACE = 0, IDENTIFIER = 1, INTEGER = 2, FLOAT = 3, OPERATOR = 4, SEPARATOR = 5, COMMENT = 6, INVALID TOKEN = 7}
    /* L = Letter, D = Digit, */
    /*
          ____|__L __D___.___  _ _____$____ ! ___Op_____Sep___space_____Inv_________
        S   0 |  1   2   5     7      7     6     4      5      0        7
        ID  1 |  1   1   5     1      1     6     4      5      0        7
        INT 2 |  7   2   3     7      7     6     4      5      0        7
        FL  3 |  7   3   5     7      7     6     4      5      0        7
        Op  4 |  1   2   5     7      7     6     4      5      0        7
        Sep 5 |  1   2   5     7      7     6     4      5      0        7
        COM 6 |  6   6   6     6      6     0     6      6      6        7
        INV 7 |  7   7   5     7      7     6     4      5      0        7

     */
    //KEYWORDS    = int, float, bool, True, False, if, else, then, endif, endelse, while, whileend, do, enddo, for, endfor, STDinput, STDoutput, and, or, not
    //IDENTIFIERS = legal identifiers must start with alphabetic character follow by digits, letters, underscore or $
    //SEPARATORS  = (){}[],.:;
    //OPERATORS   = *+-=/><%
    //comment block starts with a ! and ends with a ! (analyzer ignores these)
    //
    int fsmtable[8][10] = {{1,2,5,7,7,6,4,5,0,7},{1,1,5,1,1,6,4,5,0,7},{7,2,3,7,7,6,4,5,0,7},{7,3,5,7,7,6,4,5,0,7},
        {1,2,5,7,7,6,4,5,0,7},{1,2,5,7,7,6,4,5,0,7},{6,6,6,6,6,0,6,6,6,7}, {7,7,5,7,7,6,4,5,0,7}};  //implementation of fsmTable pictured above (formerly [8][9]
    std::string lexeme;         //string that will collect individual lexeme
    std::string token;          //string that will collect token name of lexemes
    int state = 0;              //initializes state variable so that it has a starting point
    int tempstate;              //used to compare former state to upcoming state.  helps us determine how to parse characters based off changing or unchanging states
    for(int i=0;i<s.size();i++){      //for loop does entire FSM parsing process
        tempstate = state;            //set tempstate to state (you can think of tempstate as previous state)
        int col = char_to_col(s[i], operators, separators);    //receive column index of character being read in
        state = fsmtable[state][col];                          /*we can determing what state our fsm will go into next based off our current state and the column of the next character read in */
        if(tempstate != 0 && (tempstate == state) && (tempstate != 4 && tempstate != 5 && tempstate != 6)){  //any state other than state operator, separator, or comment state stays in same state; unchanging
            lexeme.push_back(s[i]);                     /*any state other than operator, separator, or comment state can simply collect character of lexeme without outputting anything or naming token just yet*/
            if((i==s.size()-1)&&state!=0){                          /*our fsm works off of reading the next char in string- this if block helps avoid errors that occur at end of string*/
                lexemestack.push_back(lexeme);
                if(rowName(tempstate) == "IDENTIFIER"){         //tests lexeme if it's a keyword when we are an identifer state
                    std::string z = "N";
                    for(int j =0;j<keywords.size();j++){
                        if(lexeme==keywords[j]){
                            tokenstack.push_back("KEYWORD");
                            z = "A";
                            break;
                        }
                    }
                    if(z == "N"){
                        tokenstack.push_back(rowName(tempstate));
                    }
                }
                else{                                                  //if fsmTable is not in identifier state we just push back the token name onto vector
                    tokenstack.push_back(rowName(tempstate));
                }
            }
        }
        else if(state == 6 && tempstate == 6){  /*comment state stays in same state. comments shouldn't be outputted, we can collect chars in comments and delete them when we change states*/
            lexeme.push_back(s[i]);

        }
        else if(tempstate != 0 && (state == tempstate) && (state == 4 || state == 5)){   /*operator/ separator state stays in same state. we can just upload lexeme because it's a single char, and upload it's token name to the vector also */
            lexemestack.push_back(lexeme);
            tokenstack.push_back(rowName(state));
            lexeme.clear();
            lexeme.push_back(s[i]);
            if((i==s.size()-1)&&state!=0){                                 /*our fsm works off of reading the next char in string- this if block helps avoid errors that occur at end of string*/
                lexemestack.push_back(lexeme);
                tokenstack.push_back(rowName(tempstate));
            }
        }
        else if(tempstate != 0 && state != tempstate && tempstate != 6){   /*non whitespace & non comment state to any other state.*/
            lexemestack.push_back(lexeme);                //change of any of these states requires lexeme push back
            if(rowName(tempstate) == "IDENTIFIER"){             //tests identifier lexeme for keyword status
                std::string z = "N";
                for(int j =0;j<keywords.size();j++){
                    if(lexeme==keywords[j]){
                        tokenstack.push_back("KEYWORD");
                        z = "A";
                        break;
                    }
                }
                if(z == "N"){
                    tokenstack.push_back(rowName(tempstate));
                }
            }
            else{                                                  //if fsmTable is not in identifier state we just push back the token name onto vector
                tokenstack.push_back(rowName(tempstate));
            }
            lexeme.clear();                                         //clears lexeme to get it ready to read in lexeme from next state
            if(state != 0){                                       //we don't want to push back white space characters
                lexeme.push_back(s[i]);
            }
            if((i==s.size()-1)&&state!=0){                                  /*our fsm works off of reading the next char in string- this if block helps avoid errors that occur at end of string*/
                            lexemestack.push_back(lexeme);
                            tokenstack.push_back(rowName(state));
                        }
        }
        else if(tempstate == 6 && state != 6){   //comment state to some other state- delete everything collected in lexeme
            lexeme.clear();
        }
        else if(tempstate == 0 && state != tempstate){   //whitespace to some other state - s[i] is first character of new state
            lexeme.push_back(s[i]);
        }
        else if(tempstate == 0 && state == tempstate){  //whitespace to whitespace state, we do nothing but pass over this state
        }
    }
}