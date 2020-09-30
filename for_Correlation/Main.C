#include"State.h"

int main(int argc,char **argv)
{
 //usage output
 if(argc!=4)
 {
  cout<<"Warn:missing enough variables!!"<<endl;
  cout<<"ntuple_file_name MC/data/EWMC BagNo"<<endl;
  cout<<"MC:BagNo=0"<<endl;
  cout<<"EWMC:BagNo=ttbar,W0lp..."<<endl;
  cout<<"QCD_num:BagNo=data,MC,ttbar,W0lp,..."<<endl;
  
  return 0;
 }
 
 //read in filelist
 ifstream infile;
 infile.open(argv[1],ios::in);
 int count=0;//recording the number of rootfile
 
 cout<<"********* ZmmAna begin! *********"<<endl;

 //do what?
 string str;
 str="EffNume";
 if(str!="Normal" && str!="noCali" && str!="EffSystWeight" && str!="Fiducial" && str!="EffNume" && str!="Matrix" && str!="QCD_num" && str!="QCD_spectrum" && str!="cali1" && str!="cali5" && str!="cali2" && str!="cali3")
 {
  cout<<"********* error:running mode has problem!!! *********";
  return 0;
 }
 //EffSystWeight:add additional eff correction!


 cout<<"********* Attention:it is   "<<str<<"   running now********"<<endl;
 ZmmAna run(argv[1],argv[2],argv[3],str);
 TString inputRoot;

 while(infile>>inputRoot)
 {
  count++;
  run.Initial(inputRoot,count);
  run.Loop(argv[2]);
  run.End(count);
 }
 run.Output();
 run.Finish(count);
 
 cout<<"********* ZmmAna finish! *********"<<endl;
 return 0;
}


