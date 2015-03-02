#include <iostream>
using namespace std;

struct node
{
	int data;
	node * next;
};
void removeNode(node *head, int value){
	node * temp = new node;
	node * prev = new node;
	temp = head;
	while(temp !=NULL){
		if(temp->data==value){
			prev->next=temp->next;
			break;
		}
		prev = temp;
		temp = temp->next;
	}
}
bool isPalindrome(node *head, node * tail){
	while( head !=NULL && tail!=NULL){
		if(head->data != tail->data){
			return false;
		}
		head = head->next;
		tail = tail->previous;
	}
	return true;
}
int main(){


	return 0;

}