#include <iostream>

void test(int *a){
	*a=1;
}
int main(){
	int a = 0;
	test(&a);
	std::cout<<a<<std::endl;
}