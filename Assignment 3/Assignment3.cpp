#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

struct city
{
	std::string message;
	std::string name;
	city *next;
};

void printNetWorkPath(city *head)
{
	city *currentCity = head;
	currentCity=currentCity->next; //ignores head
	std::cout<<"===CURRENT PATH==="<< std::endl;
	if(currentCity->next==NULL){return;}
	while(currentCity->next!=NULL){
		std::cout<<currentCity->name<<" -> ";
		currentCity=currentCity->next;
	}
	std::cout<<" NULL"<<std::endl;
	std::cout<<"================="<<std::endl;
}
city *buildNetwork()
{
	//return head, build network 
	std::string startingCities[12] = {"HEAD","Los Angeles", "Phoenix", "Denver", "Dallas", "St. Louis", "Chicago", "Atlanta", "Washington, D.C.", "New York", "Boston"};
	city * currentCity = NULL;
	city * head        = new city;
	for(int i = 11; i>=0; i--){

		city * c = new city;
		c->next = currentCity;
		c->name=startingCities[i];
		currentCity = c;
	}
	head = currentCity;
	printNetWorkPath(head);
	return head;
}
city *addCity(city *head, city *previous, std::string cityName){
	/*Add a new	city to the linked list between	the	city	*previous	and	the	city	that	
	follows	it	in	the	network.	The	name	of	the	new	city	is	in	the	argument	cityName.	
	Return	the	head	of	the	linked	list.	
	*/
	city * currentCity = head;
	while(currentCity->next!=NULL){
		if(currentCity->next == previous){
			city * c = new city;
			c->name = cityName;
			c->next = currentCity->next;
			currentCity->next = c;
			break;
		}
		currentCity = currentCity->next;
	}
	return head;
}
city *deleteCity(city *head, std::string cityName){
	/*Delete	the	city	in	the	linked	list	with	the	specified	name.	Return	the	head	of	the	
	linked	list.	
	*/
	city * currentCity = head;

	while(true){
		if(currentCity->next == NULL){break;}
		else
		{
			if(!currentCity->next->name.compare(cityName)){
				city *temp = currentCity->next->next;
				delete currentCity->next;
				currentCity->next = temp; //since im not doing a double linked list this isn't as clean
				delete temp;
			}
			currentCity = currentCity->next;
		}
	}	

	return head;
}
void transmitMsg(city *head){
	/*Open	the	file	messageLn.txt	and	transmit	the	message	between	all	cities	in	the	
	network	word	by	word.	A	word	needs	to	be	received	at	the	end	of	the	network	
	before	sending	the	next	word.	Only	one	city	can	hold	the	message	at	a	time;	as	soon	
	as	it	is	passed	to	the	next	city,	it	needs	to	be	deleted	from	the	sender	city.	
	*/
	std::ifstream inFile("messageln.txt");
	if(inFile.fail()){std::cout<<"error"<<std::endl;}
	std::string currentString,currentWord;
	int start = 0;
	int end;
	city * currentCity= head;
	while(!inFile.eof()){
		getline(inFile, currentString);
		std::cout<<currentString<<std::endl;
		while(currentString.find(" ")!= -1){
			end = currentString.find(" ");
			currentWord=currentString.substr(start, end);
			currentString.erase(start,end+1);
			while(currentCity->next != NULL){
				currentCity->message = currentWord;
				currentCity->next->message = currentCity->message;
				currentCity->message = "";
				currentCity=currentCity->next;
			}
			currentCity=head;
		}
	}

}
city *deleteEntireNetwork(city *head){
	/*This	function	deletes	all	cities	in	the	network	starting	at	the	head	city.	The	
	function	should	return	NULL	by	returning	the	next	pointer	of	the	last	city	deleted.	
	*/
	if(head->next == NULL){return head;} // RECURSION BITCHES YEAH
	else{
		deleteEntireNetwork(head->next);
		delete head;
	}
	city * h = new city;
	return h;
}
city * findCityByName(city * head,	std::string name){
	while(head->next != NULL){
		if(!head->name.compare(name)){break;}
		head = head->next;
	}
	return head;
};
int main(){
	city * head;
	while(true){
		std::cout << "======Main Menu=====" << std::endl;
        std::cout << "1. Build Network" << std::endl;
        std::cout << "2. Print Network Path" << std::endl;
        std::cout << "3. Transmit Message Coast-To-Coast" << std::endl;
        std::cout << "4. Add City" << std::endl;
        std::cout << "5. Delete City" << std::endl;
        std::cout << "6. Clear Network" <<std::endl;   
        std::cout << "7. Quit";
        
        int selection;
        std::cin >> selection;
        std::cout << std::endl;

        switch (selection){
            case 1:
                head = buildNetwork(); //DONE
                break;
            case 2:
                printNetWorkPath(head); // SEGFAULT WHEN HEAD IS NULL
                break;
            case 3:
                transmitMsg(head);     //Done
                break;
            case 4:
            {
            	std::string previousName; 
            	std::string newCity;
            	std::cout <<"Previous City: "<<std::endl;
            	std::cin>>previousName;
            	std::cout <<"City to add: "<<std::endl;
            	std::cin>>newCity;
            	std::cout<<std::endl;
            	city * previousCity = findCityByName(head, previousName); //DONE
            	addCity(head, previousCity, newCity);
               	break;
            } 
            case 5:{
            	std::string cityName;
            	std::cout<<"Remove which city: "<<std::endl;
            	std::cin>>cityName;
                head = deleteCity(head, cityName); //DONE
                break;
            }
            case 6:
            	head = deleteEntireNetwork(head); //DONE
            break;
            case 7:
                std::cout<<"Goodbye!"<<std::endl;
                return 0;

                break;

        }
        
	}
	return 0;
}