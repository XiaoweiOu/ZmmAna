#include"/lustre/AtlUser/xwou/include/Efficiency.h"

void cal_eff()
{
 TFile *data_file = new TFile("../muon_eff/result/data_result.root");
 TFile *MC_file = new TFile("../muon_eff/result/MC_0_result.root");
 TFile *EW_file = new TFile("../muon_eff/EW_norm.root");
 TFile *result_file = new TFile("./cal_eff.root","RECREATE");

 TH2D *data_Id_LeptonEta_Pt_deno = (TH2D *)data_file->Get("Id_LeptonEta_Pt_deno");
 TH2D *data_Id_LeptonEta_Pt_nume = (TH2D *)data_file->Get("Id_LeptonEta_Pt_nume");
 TH2D *data_Id_LeptonEta_Pt_eff_central = (TH2D *)data_Id_LeptonEta_Pt_deno->Clone("data_Id_LeptonEta_Pt_eff_central");
 TH2D *data_Id_LeptonEta_Pt_eff1 = (TH2D *)data_Id_LeptonEta_Pt_deno->Clone("data_Id_LeptonEta_Pt_eff1");
 TH2D *data_Id_LeptonEta_Pt_eff2 = (TH2D *)data_Id_LeptonEta_Pt_deno->Clone("data_Id_LeptonEta_Pt_eff2");
 TH2D *data_Id_LeptonEta_Pt_eff3 = (TH2D *)data_Id_LeptonEta_Pt_deno->Clone("data_Id_LeptonEta_Pt_eff3");

 TH2D *MC_Id_LeptonEta_Pt_deno = (TH2D *)MC_file->Get("Id_LeptonEta_Pt_deno");
 TH2D *MC_Id_LeptonEta_Pt_nume = (TH2D *)MC_file->Get("Id_LeptonEta_Pt_nume");
 TH2D *MC_Id_LeptonEta_Pt_eff = (TH2D *)MC_Id_LeptonEta_Pt_deno->Clone("MC_Id_LeptonEta_Pt_eff");

 TH2D *bkg = (TH2D *)data_Id_LeptonEta_Pt_deno->Clone("bkg");

 char name[100];
 TH1D *help_ZMass;
 for(int i=0;i<9;i++)
  for(int j=0;j<3;j++)
  {
   sprintf(name,"Id_ZMass_LeptonEta%d_Pt%d",i,j);
   help_ZMass = (TH1D *)EW_file->Get(name);
   bkg->SetBinContent(i+1,j+1,help_ZMass->Integral());
  }

 //2D efficiency
 fstream bkg_file("help.txt");
 TH2D *bkg_fit = (TH2D *)data_Id_LeptonEta_Pt_deno->Clone("bkg_fit");
 for(int i=1;i<=9;i++)
  for(int j=1;j<=3;j++)
  {
   string skip;
   bkg_file >> skip;
   double number;
   bkg_file >> number;
   bkg_fit->SetBinContent(i,j,number);
  }

 //central
 bkg_fit->Add(bkg);
 bkg_fit->Scale(0.5);//use:(bkg_fit+bkg_MC)/2
 twoD_eff(data_Id_LeptonEta_Pt_nume,data_Id_LeptonEta_Pt_deno,data_Id_LeptonEta_Pt_eff_central,bkg_fit);

 //1,2,3 times!
 twoD_eff(data_Id_LeptonEta_Pt_nume,data_Id_LeptonEta_Pt_deno,data_Id_LeptonEta_Pt_eff1,bkg);

 bkg->Scale(2);
 twoD_eff(data_Id_LeptonEta_Pt_nume,data_Id_LeptonEta_Pt_deno,data_Id_LeptonEta_Pt_eff2,bkg);
 bkg->Scale(1./2);

 bkg->Scale(3); 
 twoD_eff(data_Id_LeptonEta_Pt_nume,data_Id_LeptonEta_Pt_deno,data_Id_LeptonEta_Pt_eff3,bkg);
 bkg->Scale(1./3);

 twoD_eff(MC_Id_LeptonEta_Pt_nume,MC_Id_LeptonEta_Pt_deno,MC_Id_LeptonEta_Pt_eff);

 //scale
 TH2D *scale_Id_LeptonEta_Pt_eff_central = (TH2D *)data_Id_LeptonEta_Pt_eff_central->Clone("scale_Id_LeptonEta_Pt_central");
 TH2D *scale_Id_LeptonEta_Pt_eff1 = (TH2D *)data_Id_LeptonEta_Pt_eff1->Clone("scale_Id_LeptonEta_Pt_eff1");
 TH2D *scale_Id_LeptonEta_Pt_eff2 = (TH2D *)data_Id_LeptonEta_Pt_eff2->Clone("scale_Id_LeptonEta_Pt_eff2");
 TH2D *scale_Id_LeptonEta_Pt_eff3 = (TH2D *)data_Id_LeptonEta_Pt_eff3->Clone("scale_Id_LeptonEta_Pt_eff3");

 scale_Id_LeptonEta_Pt_eff_central->Divide(MC_Id_LeptonEta_Pt_eff); 
 scale_Id_LeptonEta_Pt_eff1->Divide(MC_Id_LeptonEta_Pt_eff);
 scale_Id_LeptonEta_Pt_eff2->Divide(MC_Id_LeptonEta_Pt_eff);
 scale_Id_LeptonEta_Pt_eff3->Divide(MC_Id_LeptonEta_Pt_eff);

 result_file->Write();
 result_file->Close();
}
