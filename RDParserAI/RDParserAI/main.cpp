//  main.cpp
//  RDParser
//  This recursive descent parser is being used to evaluate logical terms to see if
//  a logical sentence is either true or false.
//
//  Created by Matthew Voegeli, Trevor Berreth, and Lucas Orlita on 2/2/15.
//
//  Copyright (c) 2015 Matthew Voegeli. All rights reserved.

#include <iostream>
#include <cstdio>
#include <vector>
#include <cctype>
#include <string>
#include <fstream>
using namespace std;

// Enum for all types of tokens within out grammar
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

enum NODETYPE {
    NODE_LITERAL,
	NODE_TRUE,
	NODE_FALSE,
    NODE_BICONDITIONAL,
    NODE_IMPLICATION,
    NODE_OR,
    NODE_AND,
    NODE_NEGATE,
    NODE_EXPRESSION
};

// Token Struct for __________
struct Token
{
    TOKENTYPE type;
    char val;
};

struct Node {
    NODETYPE type;
    Node *left;
    Node *right;
};

//Prototypes
void readFromFile();
void Eat(Token * tokens, int& index);
TOKENTYPE Peek(Token * tokens, int index);

Node* BiconditionalExpression(Token * tokens, int& index);
Node* ImplicationExpression(Token * tokens, int& index);
Node* OrExpression(Token * tokens, int& index);
Node* AndExpression(Token * tokens, int& index);
Node* NegateExpression(Token * tokens, int& index);
Node* Expression(Token * tokens, int& index);
Node* LiteralExpression(Token * tokens, int& index);

void Tokenizer(Token * tokens, std::string& line, int size);

bool Eval(Node *node);

int main(int argc, const char * argv[]) {
    readFromFile();
}

void readFromFile()
{
    std::string line;
    ifstream myfile("TestParser.txt");
    if (myfile.is_open())
    {
        while(getline(myfile, line))
        {
            int index = 0;
            int size = line.size();
            Node* headNode;
            Token tokens [50];
            Tokenizer(tokens, line, size); 			// Creates tokens from expression on a single line
            headNode = BiconditionalExpression(tokens, index);
            cout << line;
            bool boolVal = Eval(headNode);
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

//This function is used as a grammer d '<=>' which is a biconditional.
Node* BiconditionalExpression(Token * tokens, int& index){
    Node* node = new Node;
    node->type = NODE_BICONDITIONAL;
    node->left = ImplicationExpression(tokens, index);      //building of left half
    if(Peek(tokens, index) == BICONDITIONAL){ 				//if the next token is a biconditional
        Eat(tokens, index);
        node->right = BiconditionalExpression(tokens, index);
    }
    return node;
}

//This function is used as a grammer describes that of the '=>' which is an Implication.
Node* ImplicationExpression(Token * tokens, int& index){
    //cout << "In Impli" << endl;
    Node* node = new Node;
    node->type = NODE_IMPLICATION;
    node->left = OrExpression(tokens, index);               //building of left half
    if (Peek(tokens, index) == IMPLICATION){				//if the next token is an implication
        Eat(tokens, index);
        node->right = ImplicationExpression(tokens, index);
        
    }
    return node;
}

//This function is used as a grammer describes that of the '|' which is an Or statement.
Node* OrExpression(Token * tokens, int& index){
    Node* node = new Node;
    node->type = NODE_OR;
    node->left = AndExpression(tokens, index);      //building of left half
    if(Peek(tokens, index) == OR){					//if the next token is an or statement
        Eat(tokens, index);
        node->right = OrExpression(tokens, index);
    }
    return node;
}

//This function is used as a grammer describes that of the '&' which is an And statement.
Node* AndExpression(Token * tokens, int& index) {
    Node* node = new Node;
    node->type = NODE_AND;
    node->left =NegateExpression(tokens, index);    //building of left half
    if(Peek(tokens, index) == AND){					//if the next token is an and statement
        Eat(tokens, index);
        node->right = AndExpression(tokens, index);
    }
    return node;
}

//This function is used as a grammer describes that of the '~' which is a Negation.
Node* NegateExpression(Token * tokens, int& index){
    Node* node = new Node;
    node->type = NODE_NEGATE;
    
    if(Peek(tokens, index) == NEGATE){					//if the next token is a negation
        Eat(tokens, index);
        node->right = Expression(tokens, index);
    } else {
        node->left = Expression(tokens, index);
    }
    return node;
}

//This function is used as a grammer describes that of the '(' and ')' which is used by a biconditional.
Node* Expression(Token * tokens, int& index){
    Node* node = new Node;
    node->type = NODE_EXPRESSION;
    
    if(Peek(tokens, index) == LEFTPAREN){				//if the next token is a (
        Eat(tokens, index);
        node->left = BiconditionalExpression(tokens, index);
        Eat(tokens, index);
    } else {
		node->left = LiteralExpression(tokens, index);
	}
    return node;
}

//This function is used as a grammer describes that of the 'true' or 'false' which is as a true or false statement.
Node* LiteralExpression(Token * tokens, int& index) {
    Node* node = new Node;
    node->type = NODE_LITERAL;
    
    if(Peek(tokens, index) == BOOLTRUE){				//if the next token is a true token
        Eat(tokens, index);
        node->left = new Node;
		node->left->type = NODE_TRUE;
    } else {                                            //else the token is false
        Eat(tokens, index);
        node->left = new Node;
		node->left->type = NODE_FALSE;
    }
    return node;
}

//This function tokenizes a single line given to it at a time
void Tokenizer(Token * tokens, std::string& line, int size){
	//Used to take the string from a line of the file and make it an array of characters
	std:string logicalSentence(line);

	int tokensIndex = 0;
	for (int j = 0; j < size - 1; j++)
	{
		//checks for all types of tokens within the grammar
		if(logicalSentence[j] == 't')
		{
			Token token;
			token.type = BOOLTRUE;
			tokens[tokensIndex] = token;
			tokensIndex++;
			j += 3;
		} else if(logicalSentence[j] == 'f') {
			Token token;
			token.type = BOOLFALSE;
			tokens[tokensIndex] = token;
			tokensIndex++;
			j += 4;
		} else if(logicalSentence[j] == '~') {
			Token token;
			token.type = NEGATE;
			tokens[tokensIndex] = token;
			tokensIndex++;
		} else if(logicalSentence[j] == '&') {
			Token token;
			token.type = AND;
			tokens[tokensIndex] = token;
			tokensIndex++;
		} else if(logicalSentence[j] == '|') {
			Token token;
			token.type = OR;
			tokens[tokensIndex] = token;
			tokensIndex++;
		} else if(logicalSentence[j] == '=') {
			Token token;
			token.type = IMPLICATION;
			tokens[tokensIndex] = token;
			tokensIndex++;
			j++;
		} else if(logicalSentence[j] == '<') {
			Token token;
			token.type = BICONDITIONAL;
			tokens[tokensIndex] = token;
			tokensIndex++;
			j += 2;
		} else if(logicalSentence[j] == '(') {
			Token token;
			token.type = LEFTPAREN;
			tokens[tokensIndex] = token;
			tokensIndex++;
		} else if(logicalSentence[j] == ')') {
			Token token;
			token.type = RIGHTPAREN;
			tokens[tokensIndex] = token;
			tokensIndex++;
		}
	}
}
//This function evaluates the token tree.
bool Eval(Node *node){
	if(node->type == NODE_FALSE){
		return false;
        
	} else if (node->type == NODE_TRUE) {
		return true;
        
	} else if(node->right == NULL) {
		return Eval(node->left);
        
    } else if(node->type == NODE_NEGATE){
        return !Eval(node->right);
        
    } else {
		bool leftVal = Eval(node->left);
		bool rightVal = Eval(node->right);
        
		if(node->type == NODE_BICONDITIONAL){
			return ((leftVal && rightVal) || (!leftVal && !rightVal));
            
		} else if(node->type == NODE_IMPLICATION) {
			return !leftVal || rightVal;
            
		} else if(node->type == NODE_OR) {
			return leftVal || rightVal;
            
		} else if(node->type == NODE_AND) {
			return leftVal && rightVal;
            
		} else if(node->type == NODE_EXPRESSION) {
			return leftVal;
        
        } else {
			return leftVal;
		}
	}
}