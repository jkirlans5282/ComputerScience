#include <iostream>
using namespace std;

template <class T>
class Bucky{
	T first, second; //variables of unknown type
	public:
		Bucky(T a, T b){ //constructor
			first = a;
			second = b;
		}
		T bigger();
};

template <class T> //have to call again
T Bucky<T>::bigger(){ //<T> tells c++ functions template parameter is same as class kinda weird. 
	return(first>second?first:second);
}

template <class S> // handles all but chars.
class Spunky{
	public:
		Spunky(S x){
			cout<<x<<" is not a char\n";
		}
};

template<> // overloading Spunky this one only handles chars. 
class Spunky<char>{
	public:
		Spunky(char x){
			cout<<x<<" is char\n";
		}
};

int main(){
	Bucky <int> bo(60,105); //<int> specifies data type to substitute for T at runtime
	cout<<bo.bigger()<<"\n";
	Spunky<int> s(9);
	Spunky<char> b('h');

}