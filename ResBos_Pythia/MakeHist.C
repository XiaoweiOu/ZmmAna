#ifndef MAKEHIST_SOURCE
#define MAKEHIST_SOURCE

#include"State.h"

using namespace std;

void MakeHist::BookHist(const char *fName)
{//func_BookHist
 result = new TFile(fName,"RECREATE");
 
 //Initial plots
 ZMass = new TH1D("ZMass","ZMass",140,60,130);
 ZMass->Sumw2();

 ZMass_SN = new TH1D("ZMass_SN","ZMass_SN",140,60,130);
 ZMass_SN->Sumw2();

 ZMass_SP = new TH1D("ZMass_SP","ZMass_SP",140,60,130);
 ZMass_SP->Sumw2();

 LeptonEta = new TH1D("LeptonEta","LeptonEta",60,-3,3);
 LeptonEta->Sumw2();

 LeptonEta_SN = new TH1D("LeptonEta_SN","LeptonEta_SN",60,-3,3);
 LeptonEta_SN->Sumw2();

 LeptonEta_SP = new TH1D("LeptonEta_SP","LeptonEta_SP",60,-3,3);
 LeptonEta_SP->Sumw2();

 LeptonPt = new TH1D("LeptonPt","LeptonPt",50,0,100);
 LeptonPt->Sumw2();

 LeptonPt_SN = new TH1D("LeptonPt_SN","LeptonPt_SN",50,0,100);
 LeptonPt_SN->Sumw2();

 LeptonPt_SP = new TH1D("LeptonPt_SP","LeptonPt_SP",50,0,100);
 LeptonPt_SP->Sumw2();

 ZPt = new TH1D("ZPt","ZPt",50,0,50);
 ZPt->Sumw2();

 ZPt_SN = new TH1D("ZPt_SN","ZPt_SN",50,0,50);
 ZPt_SN->Sumw2();

 ZPt_SP = new TH1D("ZPt_SP","ZPt_SP",50,0,50);
 ZPt_SP->Sumw2();

 Zrapidity = new TH1D("Zrapidity","Zrapidity",60,-3,3);
 Zrapidity->Sumw2();

 Zrapidity_SN = new TH1D("Zrapidity_SN","Zrapidity_SN",60,-3,3);
 Zrapidity_SN->Sumw2();

 Zrapidity_SP = new TH1D("Zrapidity_SP","Zrapidity_SP",60,-3,3);
 Zrapidity_SP->Sumw2();

 Zrapidity_SN_F = new TH1D("Zrapidity_SN_F","Zrapidity_SN_F",60,-3,3);
 Zrapidity_SN_F->Sumw2();

 Zrapidity_SP_F = new TH1D("Zrapidity_SP_F","Zrapidity_SP_F",60,-3,3);
 Zrapidity_SP_F->Sumw2();

 Zrapidity_SN_B = new TH1D("Zrapidity_SN_B","Zrapidity_SN_B",60,-3,3);
 Zrapidity_SN_B->Sumw2();

 Zrapidity_SP_B = new TH1D("Zrapidity_SP_B","Zrapidity_SP_B",60,-3,3);
 Zrapidity_SP_B->Sumw2();

 Zrapidity_F = new TH1D("Zrapidity_F","Zrapidity_F",60,-3,3);
 Zrapidity_F->Sumw2();

 Zrapidity_B = new TH1D("Zrapidity_B","Zrapidity_B",60,-3,3);
 Zrapidity_B->Sumw2();

 cos_theta_star = new TH1D("cos_theta_star","cos_theta_star",50,-1,1);
 cos_theta_star->Sumw2();

 high_LeptonEta = new TH1D("high_LeptonEta","high_LeptonEta",60,-3,3);
 high_LeptonEta->Sumw2();

 low_LeptonEta = new TH1D("low_LeptonEta","low_LeptonEta",60,-3,3);
 low_LeptonEta->Sumw2();

 high_LeptonPt = new TH1D("high_LeptonPt","high_LeptonPt",50,0,100);
 high_LeptonPt->Sumw2();

 low_LeptonPt = new TH1D("low_LeptonPt","low_LeptonPt",50,0,100);
 low_LeptonPt->Sumw2();

 //Zrapidity for four circumstances
 ZMass_F = new TH1D("ZMass_F","ZMass_F",140,60,130);
 ZMass_F->Sumw2();

 ZMass_B = new TH1D("ZMass_B","ZMass_B",140,60,130);
 ZMass_B->Sumw2();

 luminosity = new TH1D("luminosity","luminosity",100,0,10);
 luminosity->Sumw2();

 //use to calculate unfolding matrix
 num_true = new TH1D("num_true","num_true",60,-3,3);
 num_true->Sumw2();

 num_true_reco = new TH2D("num_true_reco","num_true_reco",60,-3,3,60,-3,3);
 num_true_reco->Sumw2();

 SN_num_true = new TH1D("SN_num_true","SN_num_true",60,-3,3);
 SN_num_true ->Sumw2();

 SN_num_true_reco = new TH2D("SN_num_true_reco","SN_num_true_reco",60,-3,3,60,-3,3);
 SN_num_true_reco->Sumw2();

 SP_num_true = new TH1D("SP_num_true","SP_num_true",60,-3,3);
 SP_num_true ->Sumw2();

 SP_num_true_reco = new TH2D("SP_num_true_reco","SP_num_true_reco",60,-3,3,60,-3,3);
 SP_num_true_reco->Sumw2();

 F_SN_num_true = new TH1D("F_SN_num_true","F_SN_num_true",60,-3,3);
 F_SN_num_true ->Sumw2();

 F_SN_num_true_reco = new TH2D("F_SN_num_true_reco","F_SN_num_true_reco",60,-3,3,60,-3,3);
 F_SN_num_true_reco->Sumw2();

 F_SP_num_true = new TH1D("F_SP_num_true","F_SP_num_true",60,-3,3);
 F_SP_num_true ->Sumw2();

 F_SP_num_true_reco = new TH2D("F_SP_num_true_reco","F_SP_num_true_reco",60,-3,3,60,-3,3);
 F_SP_num_true_reco->Sumw2();

 B_SN_num_true = new TH1D("B_SN_num_true","B_SN_num_true",60,-3,3);
 B_SN_num_true ->Sumw2();

 B_SN_num_true_reco = new TH2D("B_SN_num_true_reco","B_SN_num_true_reco",60,-3,3,60,-3,3);
 B_SN_num_true_reco->Sumw2();

 B_SP_num_true = new TH1D("B_SP_num_true","B_SP_num_true",60,-3,3);
 B_SP_num_true ->Sumw2();

 B_SP_num_true_reco = new TH2D("B_SP_num_true_reco","B_SP_num_true_reco",60,-3,3,60,-3,3);
 B_SP_num_true_reco->Sumw2();


 //truth-level plots
 ZMass_true = new TH1D("ZMass_true","ZMass_true",140,60,130);
 ZMass_true->Sumw2();

 LeptonEta_true = new TH1D("LeptonEta_true","LeptonEta_true",60,-3,3);
 LeptonEta_true->Sumw2();

 LeptonPt_true = new TH1D("LeptonPt_true","LeptonPt_true",50,0,100);
 LeptonPt_true->Sumw2();

 ZPt_true = new TH1D("ZPt_true","ZPt_true",50,0,50);
 ZPt_true->Sumw2();

 Zrapidity_true = new TH1D("Zrapidity_true","Zrapidity_true",60,-3,3);
 Zrapidity_true->Sumw2();

 high_LeptonEta_true = new TH1D("high_LeptonEta_true","high_LeptonEta_true",60,-3,3);
 high_LeptonEta_true->Sumw2();

 low_LeptonEta_true = new TH1D("low_LeptonEta_true","low_LeptonEta_true",60,-3,3);
 low_LeptonEta_true->Sumw2();

 high_LeptonPt_true = new TH1D("high_LeptonPt_true","high_LeptonPt_true",50,0,100);
 high_LeptonPt_true->Sumw2();

 low_LeptonPt_true = new TH1D("low_LeptonPt_true","low_LeptonPt_true",50,0,100);
 low_LeptonPt_true->Sumw2();

 Double_t x[10]={-1.8,-1.4,-1.0,-0.6,-0.2,0.2,0.6,1.0,1.4,1.8};
 Double_t y[6]={0,0.2,0.6,1.0,1.4,1.8};

 Zrap_muonEta = new TH3D("Zrap_muonEta","Zrap_muonEta",15,-3,3,15,-3,3,15,-3,3);
 Zrap_muonEta->Sumw2();

 Nii0 = new TH1D("Nii0","Nii0",18,-1.8,1.8);
 Nii0->Sumw2();

 Nii1 = new TH1D("Nii1","Nii1",18,-1.8,1.8);
 Nii1->Sumw2();

 Nii2 = new TH1D("Nii2","Nii2",18,-1.8,1.8);
 Nii2->Sumw2();

 Both_muon = new TH1D("Both_muon","Both_muon",9,-1.8,1.8);
 Both_muon->Sumw2();

 Oppo_muon = new TH1D("Oppo_muon","Oppo_muon",5,y);
 Oppo_muon->Sumw2();

 Both_muon_F = new TH1D("Both_muon_F","Both_muon_F",9,-1.8,1.8);
 Both_muon_F->Sumw2();

 Oppo_muon_F = new TH1D("Oppo_muon_F","Oppo_muon_F",5,y);
 Oppo_muon_F->Sumw2();

 Both_muon_B = new TH1D("Both_muon_B","Both_muon_B",9,-1.8,1.8);
 Both_muon_B->Sumw2();

 Oppo_muon_B = new TH1D("Oppo_muon_B","Oppo_muon_B",5,y);
 Oppo_muon_B->Sumw2();
}//func_BookHist

void MakeHist::SaveHist(void)
{//func_SaveHist
 result->Write();
}//func_SaveHist

#endif
