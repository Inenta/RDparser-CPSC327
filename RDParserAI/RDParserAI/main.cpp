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
bool OrExpression(Token * tokens, int& index);
bool AndExpression(Token * tokens, int& index);
bool NegateExpression(Token * tokens, int& index);
bool Expression(Token * tokens, int& index);
bool LiteralExpression(Token * tokens, int& index);
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
//This function is used as a grammer describes that of the '<=>' which is a biconditional.
bool BiconditionalExpression(Token * tokens, int& index){
    bool firstHalf = ImplicationExpression(tokens, index);
    if(Peek(tokens, index) == BICONDITIONAL){
        Eat(tokens, index);
        return firstHalf && BiconditionalExpression(tokens, index);
    } else
        return firstHalf;
}
//This function is used as a grammer describes that of the '=>' which is an Implication.
bool ImplicationExpression(Token * tokens, int& index){
    bool firstHalf = OrExpression(tokens, index);
    if (Peek(tokens, index) == IMPLICATION){
        Eat(tokens, index);
        return firstHalf && ImplicationExpression(tokens, index);
    }
    else
        return firstHalf;
}
//This function is used as a grammer describes that of the '|' which is an Or statement.
bool OrExpression(Token * tokens, int& index){
    //replace this return later
    return true;
}
//This function is used as a grammer describes that of the '&' which is an And statement.
bool AndExpression(Token * tokens, int& index) {
    bool firstHalf = NegateExpression(tokens, index);
    if(Peek(tokens, index) == AND){
        Eat(tokens, index);
        return firstHalf && AndExpression(tokens, index);
    } else
        return firstHalf;
}
//This function is used as a grammer describes that of the '~' which is a Negation.
bool NegateExpression(Token * tokens, int& index){
    //replace this return later
    return true;
}
//This function is used as a grammer describes that of the '(' and ')' which is used by a biconditional.
bool Expression(Token * tokens, int& index){
    //UMMM WHAT DO I PUT HERE? There's no first half?
    if(Peek(tokens, index) == LEFTPAREN){
        Eat(tokens, index);
        //returning function for now, Idk what to do
        return BiconditionalExpression(tokens, index);
    }
    else if(Peek(tokens, index) == RIGHTPAREN){
        Eat(tokens, index);
        //returning true for now, Idk what to do
        return true;
    }
    else
        //returning true for now, Idk what to do
        return true;
}
//This function is used as a grammer describes that of the 'true' or 'false which is as a true or false statement.
bool LiteralExpression(Token * tokens, int& index) {
    if(Peek(tokens, index) == BOOLTRUE){
        Eat(tokens, index);
        return true;
    } else if(Peek(tokens, index) == BOOLFALSE){
        Eat(tokens, index);
        return false;
    }
    //have to put this here... otherwise we get an error.
    return true;
}









