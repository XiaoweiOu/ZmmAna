#include "/lustre/AtlUser/xwou/include/plot/Figure.h"
int main()
{
 TFile *file_data = new TFile("data_Normal/data_result.root");
 TH1D *plot_data = (TH1D *)file_data->Get("Zrapidity");
 TFile *file_MC = new TFile("MC_result/MC_Normal.root");
 TH1D *plot_MC = (TH1D *)file_MC->Get("Zrapidity");
 TFile *file_EWMC = new TFile("EW_norm.root");
 TH1D *plot_EWMC_F = (TH1D *)file_EWMC->Get("Zrapidity_F");
 TH1D *plot_EWMC_B = (TH1D *)file_EWMC->Get("Zrapidity_B");
 plot_EWMC_F->Add(plot_EWMC_B);
 TFile *file_QCD = new TFile("QCD_spectrum.root");
 TH1D *plot_QCD = (TH1D *)file_QCD->Get("Zrapidity");

 double inte = plot_data->Integral() - plot_EWMC_F->Integral() - plot_QCD->Integral();
 plot_MC->Scale(inte/plot_MC->Integral());

 for(int i=1;i<=plot_EWMC_F->GetNbinsX();i++)
 {
  plot_EWMC_F->SetBinError(i,0);
  plot_QCD->SetBinError(i,0);
  plot_MC->SetBinError(i,0);
 }

 Figure *result = new Figure("./background.eps", "Di-muon rapidity", "Number of Events");
 result->SetMode("HSTACK");
 result->SetInputFigure(1,plot_data,"data");
 result->SetInputFigure(2,plot_EWMC_F,"EWBKG");
 result->SetInputFigure(3,plot_QCD,"Multi-jet");
 result->SetInputFigure(4,plot_MC,"signal");
 result->SetXrange(-1.6,1.6);
 result->SetYrange(1e-2,1e5);
 result->SetRatiorange(0.9,1.1);
 result->Set_Yaxis_Log();
 result->MoveLegendPosition(0.25,0.1);
 result->DrawFigure();
}
