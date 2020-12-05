#include "Package.cpp"

void Package::asmgen()
{
    #include<iostream>
#include<fstream>

using namespace std;

int main(int argc,char **argv){
    ofstream out("./log",ios::app);
    if(out.fail()){
        cout<<"error\n";
    }
    out<<"myid:"<<myid<<endl;
    out<<"procnum:"<<procnum<<endl;
    out.close();
    ofstream out("./log",ios::app)
}