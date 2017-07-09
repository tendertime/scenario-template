#include<stdio.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<algorithm>
using namespace std;
int main()
{
    ifstream fin;
    //char a[2]={0};
    fin.open("./results/geant/res1.txt",ios_base::in);
    string s1,s2;
    int x=0;
    while(!fin.eof())
    {
        getline(fin,s1,'s');
        getline(fin,s2,'\n');
        const char *h=s2.c_str();
        x+=atol(h);
    }
    cout<<x<<endl;
    return 0;
}
