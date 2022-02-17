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

//p1 stuff
//std::ofstream fout("outputfile.txt");
//p2 stuff
void debug(int& l, std::vector<std::string> lexemes, std::vector<std::string> tokens, std::ofstream& fout);
bool print_switch = false; // print case toggle
int z = 0;

int main() {
    lexer(f_open(), lexemest, tokenst);                     //calls lexer function
    std::ofstream fout(file);
    /*fout<<"      TOKEN        -    Lexeme   \n\n";        //header for output file to make it look neater
    for(int i = 0;i<lexemest.size();i++)                  //while function outputs results of parsed lexemes and their token names stored in lexemest and tokenst
    {
      fout << std::setw(13)<< tokenst[i] << "      =  " << std::setw(8) << lexemest[i] << "\n";    //setw organizes output and makes it look even and neat
    }*/ 

    //debug(l, lexemest, tokenst, fout);
    Statement(fout);

    lexemest.clear();                                 //clears lexemest
    tokenst.clear();                                  //clears tokenst
    fout.close();                                     //closes output file
    
    return 0;                                         //end of main function
}

void debug(int& l, std::vector<std::string> lexemes, std::vector<std::string> tokens, std::ofstream& fout){
    std::string a;
    std::cout << "Debug Function:\n\n";
    std::cout << "1. Expression Test: expr(l, lexemest, tokenst, fout)\n";
    std::cout << "2. Assignment Test: assignment(l, lexemest, tokenst, fout)\n";
    std::cout << "3. Declarative Test: decl(l, lexemest, tokenst, fout)\n\n";
    std::cout << "4. Assignment Statement Test: Statement(l, lexemest, tokenst, fout)\n\n";
    std::cout << "5. Declarative Statement Test: DecStatement(l, lexemest, tokenst, fout)\n\n";

    std::cout << "Type \"1\", \"2\", \"3\", \"4\", or \"5\" to run the respective function: ";
    std::cin >> a;
    std::cout << "\n\n";
    int b = std::stoi (a);

    switch (b){
        case 1:
            expr(l, lexemest, tokenst, fout);
            break;
        case 2:
            assignment(l, lexemest, tokenst, fout);
            break;
        case 3:
            decl(l, lexemest, tokenst, fout);
            break;
        case 4:
            Statement(fout);
            break;
        case 5:
            DecStatement(l, lexemest, tokenst, fout);
            break;
        default:
            std::cout << "Invalid option.\n";
    }
}

void Statement(std::ofstream& fout){
    int l = 0;

    while(z < lexemest.size()){
        if (DecStatement(l, lexemest, tokenst, fout)){
            print_switch = true;
            DecStatement(l, lexemest, tokenst, fout);
            print_switch = false;
        }
        else if(AssignStatement(l, lexemest, tokenst, fout)){
            print_switch = true;
            AssignStatement(l, lexemest, tokenst, fout);
            print_switch = false;
        }
        else{
            std::cout << "Error: Line is not a Declarative Statement or Assignment Statement.\n";
            std::cout << "\nz: " << z;
            std::cout << "\nlexemest[z]: " << lexemest[z];
            std::cout << "\ntokenst[z]: " << tokenst[z] << "\n\n";
            throw std::invalid_argument("Error: Line is not a Declarative Statement or Assignment Statement.\n");
        }
    }
}

//assignment statement rules
bool AssignStatement(int& l, std::vector<std::string> lexemes, std::vector<std::string> tokens, std::ofstream& fout){
    if (print_switch){
        fout << "<Statement> --> <Assign>\n>";
        std::cout << "<Statement> --> <Assign>\n>";
    }
    bool statementMatch = false;
    if (assignment(l, lexemes, tokens, fout)){
        statementMatch = true;
    }
    return statementMatch;
}

bool DecStatement(int& l, std::vector<std::string> lexemes, std::vector<std::string> tokens, std::ofstream& fout){
    if (print_switch){
        fout << "<Statement> --> <Declarative>\n";
        std::cout << "<Statement> --> <Declarative>\n";
    }
    bool DStatement = false;
    if (decl(l, lexemes, tokens, fout)){
        DStatement = true;
    }
    return DStatement;       
}

//function expr R1
bool expr(int& l, std::vector<std::string> lexemes, std::vector<std::string> tokens, std::ofstream& fout){
    if (print_switch){
        fout << "Expr --> <Term><Expr'>\n";
        std::cout << "Expr --> <Term><Expr'>";
    }
    bool exprMatch = false;     //set match to false
    if (term(l, lexemes,tokens,fout)){
        if(exprPrime(l, lexemes,tokens,fout)){
            exprMatch = true;
        }
    }
    return exprMatch;
}

//function expr' R2
bool exprPrime(int& l, std::vector<std::string> lexemes, std::vector<std::string> tokens, std::ofstream& fout){
    if (print_switch){
        fout << "<Exp'> --> +<Term><Exp'> | -<Term><Exp'> | epsilon\n";
        std::cout << "<Exp'> --> +<Term><Exp'> | -<Term><Exp'> | epsilon\n";
    }
    bool exprMatch = true;
    if (lexemes[l] == "+"){
        match(l,"+",lexemes,tokens,fout);
        if (term(l, lexemes,tokens,fout)) {
            if (exprPrime(l, lexemes,tokens,fout)){
                exprMatch = true;    //set to true when rule matches
            }
        }
    }
    else {
        if (lexemes[l] == "-"){
            match(l,"-",lexemes,tokens,fout);
            if (term(l, lexemes,tokens,fout)){
                if (exprPrime(l, lexemes,tokens,fout)){
                    exprMatch = true;
                    }
                }
            }
    }
    //else
        //if (checkChar ==  ){
          //  cout << "<Expr> --> ε" << endl;
            //exprMatch = true;
        //}
    return exprMatch;
}

//function Term R3
bool term(int& l, std::vector<std::string> lexemes, std::vector<std::string> tokens, std::ofstream& fout){
    if (print_switch){
        fout << "<Term> --> <Factor><Term'>\n";
        std::cout << "<Term> --> <Factor><Term'>\n";
    }
    bool termMatch = false;
    if (factor(l, lexemes,tokens,fout)){
        if (termPrime(l, lexemes,tokens,fout)){
            termMatch = true;
        }
    }
    return termMatch;
}



//function Term' R4 original
bool termPrime(int& l, std::vector<std::string> lexemes, std::vector<std::string> tokens, std::ofstream& fout){
    if (print_switch){
        fout << "<Term'> --> *<Factor><Term'> | /<Factor><Term'> | epsilon\n";
        std::cout << "<Term'> --> *<Factor><Term'> | /<Factor><Term'> | epsilon\n";
    }
    bool termPrimeMatch = true;
    if (lexemes[l] == "*"){
        match(l,"*",lexemes,tokens,fout);
        if (factor(l, lexemes,tokens,fout)){
            if (termPrime(l, lexemes,tokens,fout)){
                termPrimeMatch = true;
            }
        }
    }
    else if (lexemes[l] == "/"){
        match(l,"/",lexemes,tokens,fout);
        if (factor(l, lexemes,tokens,fout)){
            if (termPrime(l, lexemes,tokens,fout)){
                termPrimeMatch = true;
            }
        }
    }
    else {
        Empty(fout);
        termPrimeMatch = true;
    }
    return termPrimeMatch;
    //else
        //if (checkTerm == 'ε'){
          //  cout << "<Term'> --> ε" << endl;
            //exprMatch = true;
        //}
}
    
//function factor R5
bool factor(int& l, std::vector<std::string> lexemes, std::vector<std::string> tokens, std::ofstream& fout){
    if (print_switch){
        fout << "<Factor> --> (<Expr>) | <ID> | <Num>\n";
        std::cout << "<Factor> --> (<Expr>) | <ID> | <Num>\n";
    }
    bool factorMatch = false;
        if (lexemes[l] == "("){
            match(l,"(",lexemes,tokens,fout);
            if (expr(l,lexemes,tokens,fout)){
                if (lexemes[l]== ")"){
                    match(l,")",lexemes,tokens,fout);
                    factorMatch = true;
                }
            }
        }
        else if (ID(l, lexemes, tokens, fout)){
            factorMatch = true;
        }
        else if (Num(l, lexemes,tokens,fout)){
            factorMatch = true;
        }
        else{
            Empty(fout);
            factorMatch = true;
        }
    return factorMatch;
}

bool assignment(int& l, std::vector<std::string> lexemes, std::vector<std::string> tokens, std::ofstream& fout){
    if (print_switch){
        fout << "<Assign> --> <ID> = <Expression>;\n";
        std::cout << "<Assign> --> <ID> = <Expression>;\n";
    }
    bool assignMatch = false;
        if (ID(l, lexemes, tokens, fout)){
            if (lexemes[l]== "="){
                match(l,"=",lexemes,tokens,fout);
                if (expr(l, lexemes, tokens, fout)){
                    if (lexemes[l]== ";"){
                        match(l,";",lexemes,tokens,fout);
                        fout << "\n";
                        std::cout << "\n";
                        assignMatch = true;
                        z = l;
                   }
                }
            }
        }
    return assignMatch;
}

bool decl(int& l, std::vector<std::string> lexemes, std::vector<std::string> tokens, std::ofstream& fout){
    if (print_switch){
        fout << "<Declarative> --> <Type> <ID>;\n";
        std::cout << "<Declarative> --> <Type> <ID>;\n";
    }
    bool declareMatch = false;
        if (Type(l, lexemes, tokens, fout)){
            if (ID(l, lexemes, tokens, fout)){
                if (lexemes[l]== ";"){
                        match(l,";",lexemes,tokens,fout);
                        fout << "\n";
                        std::cout << "\n";
                        declareMatch = true;
                        z = l;
                   }
            }
        }
    return declareMatch;
}

//function factor R6
bool ID(int& l, std::vector<std::string> lexemes, std::vector<std::string> tokens, std::ofstream& fout){
    bool IDMatch = false;
    if (tokens[l]=="IDENTIFIER"){
        match(l,"IDENTIFIER",lexemes,tokens,fout);
        IDMatch = true;
    }
    //fout << "<ID> --> id\n";
    //std::cout << "<ID> --> id\n";
    return IDMatch;
}

// function factor R7
bool Num(int& l, std::vector<std::string> lexemes, std::vector<std::string> tokens, std::ofstream& fout){
    fout << "<Num> --> num\n";
    std::cout << "<Num> --> num\n";
    bool NumMatch = false;
    if (tokens[l]=="INTEGER"){
        match(l,"INTEGER",lexemes,tokens,fout);
        NumMatch = true;
    }
    return NumMatch;
}

bool Empty(std::ofstream& fout){
    if (print_switch){
        fout << "<Empty> --> epsilon\n";
        std::cout << "<Empty> --> epsilon\n";
    }
    return true;
}

bool Type(int& l, std::vector<std::string> lexemes, std::vector<std::string> tokens, std::ofstream& fout){
    bool TypeMatch = false;
    if (tokens[l]=="KEYWORD"){
        if (lexemes[l] == "bool" || (lexemes[l] == "float") || lexemes[l] == "int"){
            match(l,"KEYWORD",lexemes,tokens,fout);
            TypeMatch = true;
        }
    }
    if (print_switch){
        fout << "<Type> --> bool | float | int\n";
        std::cout << "<Type> --> bool | float | int\n";
    }
    return TypeMatch;
}

void match(int& l, std::string t, std::vector<std::string> lexemes, std::vector<std::string> tokens,std::ofstream& fout){//match is used when we are at a terminal(when we are returning true or false at a function without calling a function, based off a lexeme or token). If our function is non-terminal at a lexemes or token, we do not call match then.
    /*if(l!=0){
        std::cout<< "Tokens: " << tokens[l] << "          Lexemes:  " << lexemes[l] << "\n";
    }*/
    //std::cout<< " HERE: " << lexemes[l] << "\n";
    if(lexemes[l]==t || tokens[l]==t){//output tokens and lexemes in this if block?
        if(l<lexemes.size()){
            //std::cout<< "look ahead number: " << l << " \n"; //ALWAYS KEEP THIS LINE IN
            if (print_switch){
                fout << "Tokens: " << tokens[l] << "          Lexemes:  " << lexemes[l] << "\n";
                std::cout << "Tokens: " << tokens[l] << "          Lexemes:  " << lexemes[l] << "\n";
            }
        }
        l++;
    }
    else{
        printf("Error");
    }
    //std::cout<< tokens[l] << "\n";
}