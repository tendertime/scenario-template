#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int main()
{
    ifstream fin;
    fin.open("topo.txt",ios_base::in);
    string s1,s2;
    while(!fin.eof())
    {
        getline(fin,s1,'\n');
        const char *k,*h;
        int t,id,i;
        k = s1.c_str();
        if(k[5]=='n')
        {
            id=k[15]=='"'?k[14]-'0':(k[14]-'0')*10+(k[15]-'0');
            cout<<id<<" ";
            getline(fin,s2,'\n');
            h=s2.c_str();
            while(h[5]!='/')
            {
                if(h[18]=='2'&&h[19]=='9')
                {
                    i=22;
                    while(h[i]!='<')
                        printf("%c",h[i++]);
                    cout<<"  ";
                }
                if(h[18]=='3'&&h[19]=='3')
                {
                    i=22;
                    while(h[i]!='<')
                        printf("%c",h[i++]);
                }
                getline(fin,s2,'\n');
                h=s2.c_str();
            }
            cout<<endl;
        }
        if(k[5]=='e')
        {
            if(k[19]=='"')
            {
               printf("%c ",k[18]);
               t=k[30]=='"'?k[29]-'0':(k[29]-'0')*10+(k[30]-'0');
            }
            else
            {
                printf("%c%c ",k[18],k[19]);
                t=k[31]=='"'?k[30]-'0':(k[30]-'0')*10+(k[31]-'0');
            }
            printf("%d\n",t);
        }
    }
    return 0;
}
