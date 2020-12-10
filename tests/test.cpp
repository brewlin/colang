#include <iostream>
#include <string>
using namespace std;
int main(){
	//string name = "main.http.handler";
	string name = "main.handler";
    std::hash<std::string> hash_key;
    size_t hk = hash_key(name);
	printf("%zu \n",hk);
	cout << hk <<endl;
}
