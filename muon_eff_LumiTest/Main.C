#include"State.h"

int main(int argc,char **argv)
{
 //usage output
 if(argc!=5)
 {
  cout<<"Warn:missing enough variables!!"<<endl;
  cout<<"ntuple_file_name MC/data/EWMC type lumix"<<endl;
  return 0;
 }
 
 //read in filelist
 ifstream infile;
 infile.open(argv[1],ios::in);
 int count=0;//recording the number of rootfile

 string str;
 //str="QCD_num";
 
 cout<<"********* ZmmAna begin! *********"<<endl;

 ZmmAna run(argv[1],argv[2],argv[3],argv[4],str);
 TString inputRoot;

 while(infile>>inputRoot)
 {
  count++;
  run.Initial(inputRoot,count);
  run.Loop(argv[4]);
  run.End(count);
 }
 run.Output();
 run.Finish(count);
 
 cout<<"********* ZmmAna finish! *********"<<endl;
 return 0;
}


