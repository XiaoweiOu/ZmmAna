#ifndef PROCESS_SOURCE
#define PROCESS_SOURCE

#include"State.h"

TMinuit *myMinuit;

Process::Process()
{
}

Process::Process(int eff_num)
{
 tag_eff_num = eff_num;
 if(tag_eff_num==1)str="eff1_";
 else if(tag_eff_num==2)str="eff2_";
 else if(tag_eff_num==3)str="eff3_";
 else str="";
}

Process::~Process()
{
}

void Process::Initial()
{
 //input plots!
 TFile *file_data = new TFile("../Zmm/data_Normal/data_result.root");
 TFile *file_MC_Normal = new TFile("../Zmm/MC_result/MC_Normal" + str + ".root");
 TFile *file_MC_Matrix = new TFile("../Zmm/MC_result/MC_Matrix" + str + ".root");
 TFile *file_MC_foreff = new TFile("../Zmm/MC_result/MC_foreff" + str + ".root");
 TFile *file_MC_fullphase = new TFile("/lustre/AtlUser/xwou/ZmmAnaV3/GeneLevel_eff/MC_result.root");
 TFile *file_EWMC = new TFile("../Zmm/EW_norm" + str + ".root");
 TFile *file_QCD = new TFile("../Zmm/QCD_spectrum" + str + ".root");

 Data_Forward = (TH1D *)file_data->Get("Zrapidity_F");
 Data_Backward = (TH1D *)file_data->Get("Zrapidity_B");

 Data_Forward->Rebin(4);
 Data_Backward->Rebin(4);

 EW_Forward = (TH1D *)file_EWMC->Get("Zrapidity_F");
 EW_Backward = (TH1D *)file_EWMC->Get("Zrapidity_B");
 QCD_Forward = (TH1D *)file_QCD->Get("Zrapidity_F");
 QCD_Backward = (TH1D *)file_QCD->Get("Zrapidity_B");

 EW_Forward->Rebin(4);
 EW_Backward->Rebin(4);
 QCD_Forward->Rebin(4);
 QCD_Backward->Rebin(4);

 num_true_reco = (TH2D *)file_MC_Matrix->Get("num_true_reco");
 num_true = (TH1D *)file_MC_Matrix->Get("num_true");
 num_true->Rebin(4);
 num_true_reco->Rebin2D(4,4);

 plot_reco = (TH1D *)file_MC_foreff->Get("Zrapidity_true");
 plot_true = (TH1D *)file_MC_fullphase->Get("Zmumu_Zrapidity");
 plot_reco->Rebin(4);
 plot_true->Rebin(4);

 //create plots!
 Matrix = new TH2D("Matrix","Matrix",15,-3,3,15,-3,3);
 Matrix_uncertain = new TH2D("Matrix_uncertain","Matrix_uncertain",15,-3,3,15,-3,3);
 Matrix->Sumw2();
 Matrix_uncertain->Sumw2();

 eff = new TH1D("eff","eff",15,-3,3);
 eff->Sumw2();

 DataBKG_Forward = new TH1D("DataBKG_Forward","DataBKG_Forward",15,-3,3);
 DataBKG_Forward->Sumw2();
 DataBKG_Backward = new TH1D("DataBKG_Backward","DataBKG_Backward",15,-3,3);
 DataBKG_Backward->Sumw2();
 DataMatrix_Forward = new TH1D("DataMatrix_Forward","DataMatrix_Forward",15,-3,3);
 DataMatrix_Forward->Sumw2();
 DataMatrix_Backward = new TH1D("DataMatrix_Backward","DataMatrix_Backward",15,-3,3);
 DataMatrix_Backward->Sumw2();

 //calculate unfolding matrix and uncertainty
 int i,j;
 double nume=0,deno=0,error_nume=0,error_deno=0,error;
 for(i=1;i<=15;i++)
  for(j=1;j<=15;j++)
  {
   nume = num_true_reco->GetBinContent(i,j);
   deno = num_true->GetBinContent(i);
   error_nume = num_true_reco->GetBinError(i,j);
   error_deno = num_true->GetBinError(i);

   if(deno!=0)
   {
    Matrix->SetBinContent(i,j,nume/deno);
    error = sqrt((deno-nume)*(deno-nume)*error_nume*error_nume/pow(deno,4) + nume*nume*(error_nume*error_nume+error_deno*error_deno)/pow(deno,4));
    Matrix_uncertain->SetBinContent(i,j,error);
   }
  }

 //calculate overall efficiency

 //normalize the integral of two plots to the same!
 //sum of weight:
 //signalMC(reco):1.08782e+07
 //full phase space(true):5,000,000
 plot_reco->Scale(5000000/1.08782e+07);

 Double_t bin_true,bin_reco,err_true,err_reco,seterr;
 for(i=1;i<=15;i++)
 {
  bin_true = plot_true->GetBinContent(i);
  bin_reco = plot_reco->GetBinContent(i);
  err_true = plot_true->GetBinError(i);
  err_reco = plot_reco->GetBinError(i);

  if(bin_true!=0 && bin_reco!=0)
  {
   eff->SetBinContent(i,bin_reco / bin_true);
   seterr = sqrt(pow(bin_true-bin_reco,2)*pow(err_reco,2)/pow(bin_true,4) + pow(bin_reco,2)*(err_true*err_true-err_reco*err_reco)/pow(bin_true,4));
   eff->SetBinError(i,seterr);
  }
 }

}

void myfcn(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
 Process *subtool = (Process *)myMinuit->GetObjectFit();

 TH1D *reco_Forward = subtool->DataBKG_Forward;
 TH1D *reco_Backward = subtool->DataBKG_Backward;
 TH2D *Matrix = subtool->Matrix;
 TH2D *Matrix_uncertain = subtool->Matrix_uncertain;

 Int_t i_truth, j_reco;
 Double_t R = 0; //matrix element
 Double_t content_F = 0, content_B = 0;

 double predict_Forward[15];
 double predict_Backward[15];

 //calculate predict:(sigma i)Rij x N_truth_i
 for(j_reco=1;j_reco<=15;j_reco++)
 {
  content_F = content_B = 0;
  for(i_truth=1;i_truth<=15;i_truth++)
  {
   R = Matrix->GetBinContent(i_truth,j_reco);//true in ith bin, reco in jth bin(probability)
   content_F += R*par[i_truth-1];//Ntruth[ith bin] -->> par[i-1]
   content_B += R*par[i_truth-1 + 15];//Ntruth[ith bin] -->> par[i-1]
  }
  predict_Forward[j_reco-1] = content_F;
  predict_Backward[j_reco-1] = content_B;
 }

 //calculate chisquare
 Double_t chisq = 0;
 Double_t num_reco,num_predict;
 int i;
 for(i=4;i<=12;i++)
 {
  num_reco = reco_Forward->GetBinContent(i);
  num_predict = predict_Forward[i-1];
  chisq += pow(num_reco-num_predict,2)/num_reco;

  num_reco = reco_Backward->GetBinContent(i);
  num_predict = predict_Backward[i-1];
  chisq += pow(num_reco-num_predict,2)/num_reco;
 }

 //test!
 //cout<<chisq<<endl;

 f = chisq;
}

void Process::Migration()
{
 myMinuit = new TMinuit(30);
 myMinuit->SetMaxIterations(100000);
 myMinuit->SetFCN(myfcn);
 if(tag_eff_num==1 || tag_eff_num==2 || tag_eff_num==3)
  myMinuit->SetObjectFit((TObject *)myPro[tag_eff_num-1]);
 else myMinuit->SetObjectFit((TObject *)myPro[0]);
 myMinuit->SetPrintLevel(-1);
 myMinuit->SetErrorDef(1.0);
 myMinuit->mncler();

 Int_t ierflg;
 Double_t arglist[10];
 arglist[0] = 1.0;
 myMinuit->mnexcm("SET ERR", arglist, 1, ierflg);

 char name[100];
 double StepSize = 1;

 for (int ipar = 0; ipar < 15; ipar++)
 { 
   sprintf(name, "%s%d", "Forward_par_", ipar);
   myMinuit->mnparm(ipar, name, Data_Forward->GetBinContent(ipar + 1), StepSize, 0, Data_Forward->GetBinContent(ipar + 1) * 3, ierflg);
   sprintf(name, "%s%d", "Backward_par_", ipar);
   myMinuit->mnparm(ipar + 15, name, Data_Backward->GetBinContent(ipar + 1), StepSize, 0, Data_Backward->GetBinContent(ipar + 1) * 3, ierflg);

   if(Data_Forward->GetBinContent(ipar+1) == 0)
    myMinuit->FixParameter(ipar);
 }

 arglist[0] = 10000;
 arglist[1] = 0.01;
 myMinuit->mnexcm("MIGRAD", arglist, 2, ierflg);

 for (int i = 0; i < 15; i++)
 {
  double value, error;
  myMinuit->GetParameter(i, value, error);
  DataMatrix_Forward->SetBinContent(i + 1, value);
  DataMatrix_Forward->SetBinError(i + 1, 0);

  myMinuit->GetParameter(i + 15, value, error);
  DataMatrix_Backward->SetBinContent(i + 1, value);
  DataMatrix_Backward->SetBinError(i + 1, 0);
 }
 
 //test!
 /*for(int i=0;i<15;i++)
 {
  cout<<DataMatrix_Forward->GetBinContent(i+1)<<endl;
 }
 cout<<endl<<endl;
 for(int i=0;i<15;i++)
 {
  cout<<DataMatrix_Backward->GetBinContent(i+1)<<endl;
 }*/

 delete myMinuit;
}

void Process::BkgSubtract()
{
 DataBKG_Forward = (TH1D *)Data_Forward->Clone("DataBKG_Forward");
 DataBKG_Forward->Add(EW_Forward,-1);
 DataBKG_Forward->Add(QCD_Forward,-1);
 DataBKG_Backward = (TH1D *)Data_Backward->Clone("DataBKG_Backward");
 DataBKG_Backward->Add(EW_Backward,-1);
 DataBKG_Backward->Add(QCD_Backward,-1);
}

void Process::OverEff()
{
 DataEff_Forward = (TH1D *)DataMatrix_Forward->Clone("DataEff_Forward");
 DataEff_Backward = (TH1D *)DataMatrix_Backward->Clone("DataEff_Backward");
 DataEff_Forward->Divide(eff);
 DataEff_Backward->Divide(eff);
}

void Process::Output()
{
 TFile *write_file = new TFile("Data_Final" + str + ".root","RECREATE");

 //Normalize!
 DataFinal_Forward = (TH1D *)DataEff_Forward->Clone("DataFinal_Forward");
 DataFinal_Backward = (TH1D *)DataEff_Backward->Clone("DataFinal_Backward");

 double inte = DataFinal_Forward->Integral()+DataFinal_Backward->Integral();

 DataFinal_Forward->Scale(1./inte);
 DataFinal_Backward->Scale(1./inte);

 //cout<<DataFinal_Forward->Integral()<<"   "<<DataFinal_Backward->Integral()<<endl;

 //draw plot
 /*th2d plot("Matrix.eps","truth-level di-muon rapidity","reco-level di-muon rapidity");
 plot.SetInputFigure(Matrix);
 plot.SetXrange(-1.8,1.8);
 plot.SetYrange(-1.8,1.8);
 plot.DrawTEXT(4);*/

 //write file
 DataFinal_Forward->Write();
 DataFinal_Backward->Write();
 Matrix->Write();
 Matrix_uncertain->Write();
 eff->Write();
 write_file->Close();
}
#endif
