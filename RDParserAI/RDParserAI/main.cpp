//
//  main.cpp
//  RDParser
//  This recursive descent parser is being used to evaluate logical terms to see if
//  a logical sentence is either true or false.
//  Created by Matthew Voegeli, Trevor Berreth, and Lucas Orlita on 2/2/15.
//  Copyright (c) 2015 Matthew Voegeli. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <vector>
#include <cctype>
#include <string>
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
//Prototypes
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
void Tokenizer(Token * tokens, const char *line, int size);

int main(int argc, const char * argv[]) {
    readFromFile();
}

void readFromFile()
{
    string line;
    ifstream myfile("TestParse.txt");
    if (myfile.is_open())
    {
        while(getline(myfile, line))
        {
			
            int index = 0;
            Token tokens [50];
            
            int size = line.size();
            Tokenizer(tokens, line.c_str(), size);
            bool boolVal = BiconditionalExpression(tokens, index);
			if(boolVal)
				cout << ": TRUE" << endl;
			else
				cout << ": FALSE" << endl;
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
        bool secondHalf = BiconditionalExpression(tokens, index);
		return ((firstHalf && secondHalf) || (!firstHalf && !secondHalf));
    } else
        return firstHalf;
}
//This function is used as a grammer describes that of the '=>' which is an Implication.
bool ImplicationExpression(Token * tokens, int& index){
    bool firstHalf = OrExpression(tokens, index);
    if (Peek(tokens, index) == IMPLICATION){
        Eat(tokens, index);
        return !firstHalf || ImplicationExpression(tokens, index);
    }
    else
        return firstHalf;
}
//This function is used as a grammer describes that of the '|' which is an Or statement.
bool OrExpression(Token * tokens, int& index){
    bool firstHalf = AndExpression(tokens, index);
    if(Peek(tokens, index) == OR){
        Eat(tokens, index);
        return firstHalf || OrExpression(tokens, index);
    }
    return firstHalf;
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
    if(Peek(tokens, index) == NEGATE){
        Eat(tokens, index);
        return !Expression(tokens, index);
    }
    return Expression(tokens, index);
}
//This function is used as a grammer describes that of the '(' and ')' which is used by a biconditional.
bool Expression(Token * tokens, int& index){
    if(Peek(tokens, index) == LEFTPAREN){
        Eat(tokens, index);
        bool exprVal = BiconditionalExpression(tokens, index);
        Eat(tokens, index);
        return exprVal;
    }
    else
        return LiteralExpression(tokens, index);
}
//This function is used as a grammer describes that of the 'true' or 'false' which is as a true or false statement.
bool LiteralExpression(Token * tokens, int& index) {
    if(Peek(tokens, index) == BOOLTRUE){
        Eat(tokens, index);
        return true;
    } else {
        Eat(tokens, index);
        return false;
    }
}
void Tokenizer(Token * tokens, const char *line, int size){
   
	//Used to take the string from a line of the file and make it an array of characters
	char logicalSentence[300];
	for (int i = 0; i < size; i++)
	{
		logicalSentence [i] = line[i];
	}
	
	int tokensIndex = 0;
	for (int j = 0; j < size - 1; j++)
	{
		if(logicalSentence[j] == 't')
		{
			Token token;
			token.type = BOOLTRUE;
			tokens[tokensIndex] = token;
			tokensIndex++;
			j += 3;
			cout << "T";
		} else if(logicalSentence[j] == 'f') {
			Token token;
			token.type = BOOLFALSE;
			tokens[tokensIndex] = token;
			tokensIndex++;
			j += 4;
			cout << "F";
		} else if(logicalSentence[j] == '~') {
			Token token;
			token.type = NEGATE;
			tokens[tokensIndex] = token;
			tokensIndex++;
			cout << "~";
		} else if(logicalSentence[j] == '&') {
			Token token;
			token.type = AND;
			tokens[tokensIndex] = token;
			tokensIndex++;
			cout << "&";
		} else if(logicalSentence[j] == '|') {
			Token token;
			token.type = OR;
			tokens[tokensIndex] = token;
			tokensIndex++;
			cout << "|";
		} else if(logicalSentence[j] == '=') {
			Token token;
			token.type = IMPLICATION;
			tokens[tokensIndex] = token;
			tokensIndex++;
			j++;
			cout << "=>";
		} else if(logicalSentence[j] == '<') {
			Token token;
			token.type = BICONDITIONAL;
			tokens[tokensIndex] = token;
			tokensIndex++;
			j += 2;
			cout << "<=>";
		} else if(logicalSentence[j] == '(') {
			Token token;
			token.type = LEFTPAREN;
			tokens[tokensIndex] = token;
			tokensIndex++;
			cout << "(";
		} else if(logicalSentence[j] == ')') {
			Token token;
			token.type = RIGHTPAREN;
			tokens[tokensIndex] = token;
			tokensIndex++;
			cout << ")";
		}
	}
}










