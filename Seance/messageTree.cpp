#include "messageTree.h"
#include <fstream>

MessageTree::MessageTree(){
	root = NULL;
}

void MessageTree::AddMessageNode(MessageNode m){

}
MessageNode* MakeNode(std::string text,std::string phoneNumber, bool fromMe ){
	MessageNode *mn = new MessageNode;
	mn->text = text;
	mn->phoneNumber = phoneNumber;
	mn->fromMe = fromMe;
	return mn;
}
void MessageTree::BuildTreeFromFile(std::string fileName, char delimiter){
	std::ifstream file(fileName);
	std::string phoneNumber;
	std::string text;
	std::string fM;
	bool fromMe;
	if(!file){std::cout<<"File could not be opened\n";exit(0);}
	while(!file.eof()){
		getline(file, phoneNumber, delimiter);
		getline(file, text, delimiter);
		getline(file, fM); 													//default delimiter is \n except some of the messages have \n in them 
		fromMe = atoi(fM.c_str());
		std::cout<<text<<std::endl;
		//if(!fM.compare("1")||!fM.compare("0")){fromMe = atoi(fM.c_str())};  //true, is from me, false is not from me
		//else{text+=fM}														//if a from me string is not found then the fm is added to the text, and
	}
	return;
}
std::string IdentifyTextSubject(){
	return "";
}