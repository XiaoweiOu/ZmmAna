#include"/lustre/AtlUser/xwou/include/plot/Figure.h"
#include<fstream>
using namespace std;
int main()
{
 fstream file1("syst_eff1.txt");
 fstream file2("syst_eff2.txt");
 TH1D *plot1 = new TH1D("syst_eff1","syst_eff1",9,-1.8,1.8);
 TH1D *plot2 = new TH1D("syst_eff2","syst_eff2",9,-1.8,1.8);

 double content,error;
 for(int i=1;i<=9;i++)
 {
  if(i==5)continue;
  file1>>content;
  file1>>error;
  plot1->SetBinContent(i,content);
  plot1->SetBinError(i,error);

  file2>>content;
  file2>>error;
  plot2->SetBinContent(i,content);
  plot2->SetBinError(i,error);
 }

 plot1->SetBinContent(5,1);
 plot2->SetBinContent(5,1);

 Figure *myF = new Figure("syst_eff_plot.eps","Di-muon rapidity","Overall efficiency");
 myF->SetMode("RATIO");
 myF->SetInputFigure(1,plot1,"bkg*1");
 myF->SetInputFigure(2,plot2,"bkg*2");
 myF->SetRatiorange(0.95,1.05);
 myF->SetYrange(0.8,1.2);
 myF->DrawFigure();
 
 return 0;
}
