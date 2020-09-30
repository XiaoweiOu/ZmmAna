#include"State.h"

int main(int argc,char **argv)
{
 //usage output
 if(argc!=4)
 {
  cout<<"Warn:missing enough variables!!"<<endl;
  cout<<"ntuple_file_name ResBos/Pythia TypeName"<<endl;
  
  return 0;
 }
 
 //read in filelist
 ifstream infile;
 infile.open(argv[1],ios::in);
 int count=0;//recording the number of rootfile
 
 cout<<"********* ZmmAna begin! *********"<<endl;

 //do what?
 ZmmAna run(argv[1],argv[2],argv[3]);
 TString inputRoot;

 while(infile>>inputRoot)
 {
  count++;
  run.Initial(inputRoot,count,argv[2]);
  run.Loop(argv[2]);
  run.End(count);
 }
 run.Output();
 run.Finish(count);
 
 cout<<"********* ZmmAna finish! *********"<<endl;
 return 0;
}


