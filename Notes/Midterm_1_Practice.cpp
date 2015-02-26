#include <iostream>
using namespace std;

//reverse

//delete node


void arrayShift(int arr[], int length, int value){
	for(int a=0; a<length; a++){
		if(arr[a]==value){
			for(int c = a+1; c<length; c++){
				//cout<<arr[c]<<endl;
				arr[c-1]=arr[c];
			}
			length-=1;
			a-=1;
		}
	}
	for(int d = 0; d<length;d++){
		cout<<arr[d]<<endl;
	}
}

int main(){

	//deleteNode(head,4);
	int array[6] = {10,20,30,40,50,10};
	arrayShift(array,6,10);

}

