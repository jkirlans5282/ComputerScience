#include <iostream>
using namespace std;
#ifndef MESSAGETREE_H
#define MESSAGETREE_H


//               B-{responses}
//              / \
// {responses}-A   C-{responses}
// 
// Is this really the best way to organize them?
// Would be nice to categorize the responses by object and type of sentance.
// 
// 

struct responseStruct{
    string text = NULL;
    string sentanceType= NULL;
    responseStruct * next= NULL;
    string sentaceObject= NULL;
};

struct MessageNode{
	string text; 				 //check against user entered text.
	string phoneNumber;
	bool fromMe; 
	responseStruct * response=NULL; //will be a linked list to all other optional responses
	MessageNode * right=NULL;
	MessageNode * left=NULL;
    string sentanceType=NULL;    // identify types? What patterns am I looking for. 
    string sentanceObject = NULL:
};

class MessageTree
{
    public:
        MessageTree();
        ~MessageTree();
        void AddMessageNode(MessageNode);
        void BuildTreeFromFile(string,char);
        MessageNode *root;
    protected:
    private:
};

#endif // MESSAGETREE_H