#include<stdio.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<algorithm>
#include<ctype.h>
using namespace std;
int main()
{
    ifstream fin;
    //char a[2]={0};
    fin.open("./xxx.txt",ios_base::in);
    string s1,s2;
    int x=0;
    while(!fin.eof())
    {
        getline(fin,s1,'n');
        getline(fin,s2,'\n');
        const char *h=s2.c_str();
        x+=atol(h);
    }
    fin.close();
    cout<<x<<endl<<endl;
    x=0;
    int a,m[50]={0};
    fin.open("./xxx.txt",ios_base::in);
    while(!fin.eof())
    {
        getline(fin,s1,'\n');
        const char *k=s1.c_str();
        a=0;
        if(isdigit(k[1]))
        {
            if(k[2]=='c')
            {
                for(int i=12;k[i]!='\0';i++)
                    a=a*10+k[i]-'0';
                m[(k[0]-'0')*10+k[1]-'0']=a;
            }
        }
        else
        {
            if(k[1]=='c')
            {
                for(int i=11;k[i]!='\0';i++)
                    a=a*10+k[i]-'0';
                m[k[0]-'0']=a;
            }
        }
        //cout<<a<<endl;
    }
    fin.close();
    for(int i=0;i<50;i++)
    {
        cout<<i<<" "<<m[i]<<endl;
        x+=m[i];
    }
    cout<<x<<endl;
    return 0;
}
