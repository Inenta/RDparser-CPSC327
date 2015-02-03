//
//  main.cpp
//  RDParser
//
//  Created by Matthew Voegeli on 2/2/15.
//  Copyright (c) 2015 Matthew Voegeli. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <vector>
#include <cctype>
#include <String>
#include <fstream>
using namespace std;

enum TOKENTYPE {
    
    BOOLTRUE,
    BOOLFALSE,
    BICONDITIONAL,
    IMPLICATION,
    OR,
    AND,
    NEGATE,
    LEFTPAREN,
    RIGHTPAREN
    
};

struct Token
{
    TOKENTYPE type;
    char val;
};

void readFromFile();
void Eat(Token * tokens, int& index);
TOKENTYPE Peek(Token * tokens, int index);
bool BiconditionalExpression(Token * tokens, int& index);
bool ImplicationExpression(Token * tokens, int& index);

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}

void readFromFile()
{
    string line;
    ifstream myfile("TestParse.txt");
    if (myfile.is_open())
    {
        while(getline(myfile, line))
        {
            cout << line << '\n';
            //function call to evaluate it
        }
    }
    
    else
        cout << "Unable to open file";
    
    myfile.close();
}

//removes the token at index
void Eat(Token * tokens, int& index){
    index++;
}

//returns the next token from the list
TOKENTYPE Peek(Token * tokens, int index){
    return tokens[index].type;
}

bool BiconditionalExpression(Token * tokens, int& index){
    bool firstHalf = ImplicationExpression(tokens, index);
    if(Peek(tokens, index) == BICONDITIONAL){
        Eat(tokens, index);
        return firstHalf && BiconditionalExpression(tokens, index);
    } else {
        return firstHalf;
    }
}

bool ImplicationExpression(Token * tokens, int& index){
    return true;
}