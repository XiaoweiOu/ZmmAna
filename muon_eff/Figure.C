#include"/lustre/AtlUser/xwou/plot_include/Figure.h"
int main()
{
 TH1D *DataMass;
 TH1D *BkgMass;
 TH1D *SignalMass;

 TFile *DataFile = new TFile("./result/data_result.root");
 TFile *BkgFile = new TFile("./EW_norm.root");

 char name[100];

 for(int i=0;i<9;i++)
  for(int j=0;j<3;j++)
  {
   sprintf(name, "./plot/Id_ZMass_LeptonEta%d_Pt%d.jpg",i,j);   
   Figure *result = new Figure(name, "M_{ll}/GeV", "Number of Events");
   result->SetMode("SIMPLE");

   sprintf(name, "Id_ZMass_LeptonEta%d_Pt%d",i,j); 
   DataMass = (TH1D *)DataFile->Get(name);
   BkgMass = (TH1D *)BkgFile->Get(name);
   SignalMass = (TH1D *)DataMass->Clone();
   SignalMass->Add(BkgMass,-1);
  
   sprintf(name, "Data_Mass_ProbeEtaBin%d_LeptonPtBin%d", i, j);
   result->SetInputFigure(1,DataMass, name);
   sprintf(name, "BKG_Mass_ProbeEtaBin%d_LeptonPtBin%d", i, j);
   result->SetInputFigure(2,BkgMass, name);
//   sprintf(name, "Signal_Mass_ProbeEtaBin%d_LeptonPtBin%d", i, j);
//   result->SetInputFigure(3,SignalMass, name);

   result->SetNotNorm();
   result->SetXrange(74, 110);
   result->SetRatiorange(0.4, 1.6);
   result->SetHeaderName("D0 Preliminary, 8.6 fb^{-1}");
   result->DrawFigure();
  }
 return 0;
}
