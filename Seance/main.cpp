#include <iostream>
#include <string>
#include <unistd.h> //getopt library
#include "messageTree.h"

bool training = false;
void DisplayHelpMessage(){
	std::cout<<"Seance usage:\n";
	std::cout<<"	-h display help text.\n";
	std::cout<<"	-t turn training mode on.\n";
	std::cout<<"	-d specify the delimiter used to seperate fields from the messages file. a char default is '`'\n";
	std::cout<<"	-f specify the file to use as the message file, default is ./messages.txt \n";
	std::cout<<"	-p load profile to you wish to talk to using their phone number \n";
	return;
}
int main(int argc, char ** argv){
	// if the program is run with a command line argument then use that as the filename to read in from
	// allows users to use their own csv formatted files.
	MessageTree *MT = new MessageTree();
	int flag;
	char delimiter = '`'; 					//default
	std::string filename="messages.txt";	//default I might change this to be generated with a bash script at a later date.

	while((flag=getopt(argc, argv, "thd:f:"))!=-1){
		switch(flag){
			case 't':{
				training = true;
				break;
			}case 'h':{
				DisplayHelpMessage();
				break;
			}case 'd':{
				delimiter = *optarg; //allows user to specify a delimiter character
				break;
			}
			case 'f':{
				filename=*optarg;
				break;
			}
			default:{
				break;
			}
		}
	}
	MT->BuildTreeFromFile(filename, delimiter);
	while(training){
		std::cout<<"Training Mode on\n";
		exit(0);
		//select random from tree.
		//add response to seperate file.
		//combine both files at runtime.
	}
	return 0;

}