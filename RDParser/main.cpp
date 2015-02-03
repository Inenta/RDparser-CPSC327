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

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}


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
void Eat(Token * tokens, int index){
    
}

//returns the next token from the list
TOKENTYPE Peek(Token * tokens){
    
}

bool BiconditionalExpression(Token * tokens){
    ImplicationExpression(tokens);
    if(Peek(tokens) == Token.BICONDITIONAL){
        Eat(tokens)
    }
}