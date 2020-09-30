#include<fstream>
#include<iostream>
using namespace std;
int main()
{
 ifstream infile;
  infile.open("Number.txt",ios::in);

 double getnumber;
 double sum=0;
 while(infile>>getnumber)
  {
   sum = sum + getnumber;
  }

 cout<<sum<<endl;
 return 0;
}
