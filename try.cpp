#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <string>
/*
  std::ofstream fout;
  fout.open("result.txt",std::ios_base::out);
  if(fout.is_open())
  {
   for(std::vector<std::pair<uint32_t,uint32_t>>::iterator i=results.begin();i!=results.end(); ++i)
    {
      fout<<(*i).first<<(*i).second;
    }
  }
 fout.close();
*/
int main()
{
    std::vector<std::pair<long,long> > list;
    std::ifstream fin("result.txt");
    //fin.open("result.txt",std::ios_base::in);
    while(fin)
    {
        //std::pair<long,long> xx;
        std::string xx;
        getline(fin,xx,'\n');
        std::cout<<xx<<std::endl;
    }
    return 0;
}
