#include"/lustre/AtlUser/xwou/include/Efficiency.h"

void cal_eff_simple()
{
 TFile *data_file = new TFile("result/new/data_result.root");
 TFile *MC_file = new TFile("result/new/MC_0_result.root");
 TFile *result_file = new TFile("./cal_eff_simple.root","RECREATE");

 //angleL
 TH1D *data_Iso_LeptonEta_angleL_deno = (TH1D *)data_file->Get("Iso_LeptonEta_angleL_deno");
 TH1D *data_Iso_LeptonEta_angleL_nume = (TH1D *)data_file->Get("Iso_LeptonEta_angleL_nume");
 TH1D *data_Iso_LeptonEta_angleL_eff = (TH1D *)data_Iso_LeptonEta_angleL_deno->Clone("data_Iso_LeptonEta_angleL_eff");

 TH1D *MC_Iso_LeptonEta_angleL_deno = (TH1D *)MC_file->Get("Iso_LeptonEta_angleL_deno");
 TH1D *MC_Iso_LeptonEta_angleL_nume = (TH1D *)MC_file->Get("Iso_LeptonEta_angleL_nume");
 TH1D *MC_Iso_LeptonEta_angleL_eff = (TH1D *)MC_Iso_LeptonEta_angleL_deno->Clone("MC_Iso_LeptonEta_angleL_eff");

 oneD_eff(data_Iso_LeptonEta_angleL_nume,data_Iso_LeptonEta_angleL_deno,data_Iso_LeptonEta_angleL_eff);
 oneD_eff(MC_Iso_LeptonEta_angleL_nume,MC_Iso_LeptonEta_angleL_deno,MC_Iso_LeptonEta_angleL_eff);
 TH1D *scale_Iso_LeptonEta_angleL_eff = (TH1D *)data_Iso_LeptonEta_angleL_eff->Clone("scale_Iso_LeptonEta_angleL");
 scale_Iso_LeptonEta_angleL_eff->Divide(MC_Iso_LeptonEta_angleL_eff); 

 //angleS
 TH1D *data_Iso_LeptonEta_angleS_deno = (TH1D *)data_file->Get("Iso_LeptonEta_angleS_deno");
 TH1D *data_Iso_LeptonEta_angleS_nume = (TH1D *)data_file->Get("Iso_LeptonEta_angleS_nume");
 TH1D *data_Iso_LeptonEta_angleS_eff = (TH1D *)data_Iso_LeptonEta_angleS_deno->Clone("data_Iso_LeptonEta_angleS_eff");
 
 TH1D *MC_Iso_LeptonEta_angleS_deno = (TH1D *)MC_file->Get("Iso_LeptonEta_angleS_deno");
 TH1D *MC_Iso_LeptonEta_angleS_nume = (TH1D *)MC_file->Get("Iso_LeptonEta_angleS_nume");
 TH1D *MC_Iso_LeptonEta_angleS_eff = (TH1D *)MC_Iso_LeptonEta_angleS_deno->Clone("MC_Iso_LeptonEta_angleS_eff");
  
 oneD_eff(data_Iso_LeptonEta_angleS_nume,data_Iso_LeptonEta_angleS_deno,data_Iso_LeptonEta_angleS_eff);
 oneD_eff(MC_Iso_LeptonEta_angleS_nume,MC_Iso_LeptonEta_angleS_deno,MC_Iso_LeptonEta_angleS_eff);
 TH1D *scale_Iso_LeptonEta_angleS_eff = (TH1D *)data_Iso_LeptonEta_angleS_eff->Clone("scale_Iso_LeptonEta_angleS");
 scale_Iso_LeptonEta_angleS_eff->Divide(MC_Iso_LeptonEta_angleS_eff);

 //dependence:Zrapidity
 TH1D *data_Iso_Zrapidity_deno = (TH1D *)data_file->Get("Iso_Zrapidity_deno");
 TH1D *data_Iso_Zrapidity_nume = (TH1D *)data_file->Get("Iso_Zrapidity_nume");
 TH1D *data_Iso_Zrapidity_eff = (TH1D *)data_Iso_Zrapidity_deno->Clone("data_Iso_Zrapidity_eff");

 TH1D *MC_Iso_Zrapidity_deno = (TH1D *)MC_file->Get("Iso_Zrapidity_deno");
 TH1D *MC_Iso_Zrapidity_nume = (TH1D *)MC_file->Get("Iso_Zrapidity_nume");
 TH1D *MC_Iso_Zrapidity_eff = (TH1D *)MC_Iso_Zrapidity_deno->Clone("MC_Iso_Zrapidity_eff");

 data_Iso_Zrapidity_deno->Rebin(4);
 data_Iso_Zrapidity_nume->Rebin(4);
 data_Iso_Zrapidity_eff->Rebin(4);
 MC_Iso_Zrapidity_deno->Rebin(4);
 MC_Iso_Zrapidity_nume->Rebin(4);
 MC_Iso_Zrapidity_eff->Rebin(4);

 oneD_eff(data_Iso_Zrapidity_nume,data_Iso_Zrapidity_deno,data_Iso_Zrapidity_eff);
 oneD_eff(MC_Iso_Zrapidity_nume,MC_Iso_Zrapidity_deno,MC_Iso_Zrapidity_eff);
 TH1D *scale_Iso_Zrapidity_eff = (TH1D *)data_Iso_Zrapidity_eff->Clone("scale_Iso_Zrapidity");
 scale_Iso_Zrapidity_eff->Divide(MC_Iso_Zrapidity_eff);

 result_file->Write();
 result_file->Close();
}
