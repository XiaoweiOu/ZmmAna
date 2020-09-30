#ifndef MAKEHIST_HEADER
#define MAKEHIST_HEADER

#include"State.h"

class MakeHist
{
 public:
 //file for histgram saving
 TFile *result;

 //plot defination
 //reco level plots
  TH1D *ZMass;
  TH1D *ZMass_SN;
  TH1D *ZMass_SP;

  TH1D *LeptonEta;
  TH1D *LeptonEta_SN;
  TH1D *LeptonEta_SP;

  TH1D *LeptonPt;
  TH1D *LeptonPt_SN;
  TH1D *LeptonPt_SP;

  TH1D *ZPt;
  TH1D *ZPt_SN;
  TH1D *ZPt_SP;

  TH1D *Zrapidity;
  TH1D *Zrapidity_SN;
  TH1D *Zrapidity_SP;
  TH1D *Zrapidity_F;
  TH1D *Zrapidity_B;

  TH1D *Zrapidity_SN_F;
  TH1D *Zrapidity_SP_F;
  TH1D *Zrapidity_SN_B;
  TH1D *Zrapidity_SP_B;

  TH1D *cos_theta_star;
  TH1D *high_LeptonEta;
  TH1D *low_LeptonEta;
  TH1D *high_LeptonPt;
  TH1D *low_LeptonPt;

  TH1D *ZMass_F;
  TH1D *ZMass_B;

  TH1D *luminosity;

  //calculate migration matrix
  TH1D *num_true;
  TH2D *num_true_reco;

  TH1D *SN_num_true;
  TH2D *SN_num_true_reco;
  TH1D *SP_num_true;
  TH2D *SP_num_true_reco;

  TH1D *F_SN_num_true;
  TH2D *F_SN_num_true_reco;
  TH1D *F_SP_num_true;
  TH2D *F_SP_num_true_reco;
  TH1D *B_SN_num_true;
  TH2D *B_SN_num_true_reco;
  TH1D *B_SP_num_true;
  TH2D *B_SP_num_true_reco;

  //truth level plots
  TH1D *ZMass_true;
  TH1D *LeptonEta_true;
  TH1D *LeptonPt_true;
  TH1D *ZPt_true;
  TH1D *Zrapidity_true;
  TH1D *high_LeptonEta_true;
  TH1D *low_LeptonEta_true;
  TH1D *high_LeptonPt_true;
  TH1D *low_LeptonPt_true;

  //additional
  TH3D *Zrap_muonEta;
  TH1D *Nii0;
  TH1D *Nii1;
  TH1D *Nii2;

  TH1D *Both_muon;
  TH1D *Both_muon_F;
  TH1D *Both_muon_B;
  TH1D *Oppo_muon;
  TH1D *Oppo_muon_F;
  TH1D *Oppo_muon_B;

 //function
 void BookHist(const char *fName);
 void SaveHist();
};

#endif
