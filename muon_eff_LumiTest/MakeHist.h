#ifndef MAKEHIST_HEADER
#define MAKEHIST_HEADER

#include"State.h"

class MakeHist
{
 public:
 //file for histgram saving
 TFile *result;

 //plot defination
 TH1D *Id_ZMass_deno;
 TH1D *Id_LeptonEta_deno;
 TH1D *Id_LeptonPt_deno;
 TH1D *Id_ZPt_deno;
 TH1D *Id_Zrapidity_deno;
 TH1D *Id_cos_theta_star_deno;
 TH2D *Id_LeptonEta_Pt_deno;

 TH1D *Id_ZMass_nume;
 TH1D *Id_LeptonEta_nume;
 TH1D *Id_LeptonPt_nume;
 TH1D *Id_ZPt_nume;
 TH1D *Id_Zrapidity_nume;
 TH1D *Id_cos_theta_star_nume;
 TH2D *Id_LeptonEta_Pt_nume;

 TH1D *Trk_ZMass_deno;
 TH1D *Trk_LeptonEta_deno;
 TH1D *Trk_LeptonPt_deno;
 TH1D *Trk_ZPt_deno;
 TH1D *Trk_Zrapidity_deno;
 TH1D *Trk_cos_theta_star_deno;
 TH2D *Trk_LeptonEta_Pt_deno;

 TH1D *Trk_ZMass_nume;
 TH1D *Trk_LeptonEta_nume;
 TH1D *Trk_LeptonPt_nume;
 TH1D *Trk_ZPt_nume;
 TH1D *Trk_Zrapidity_nume;
 TH1D *Trk_cos_theta_star_nume;
 TH2D *Trk_LeptonEta_Pt_nume;

 TH1D *Iso_ZMass_deno;
 TH1D *Iso_LeptonEta_deno;
 TH1D *Iso_LeptonEta_angleL_deno;
 TH1D *Iso_LeptonEta_angleS_deno;
 TH1D *Iso_LeptonPt_deno;
 TH1D *Iso_ZPt_deno;
 TH1D *Iso_Zrapidity_deno;
 TH1D *Iso_cos_theta_star_deno;
 TH2D *Iso_LeptonEta_Pt_deno;

 TH1D *Iso_ZMass_nume;
 TH1D *Iso_LeptonEta_nume;
 TH1D *Iso_LeptonEta_angleL_nume;
 TH1D *Iso_LeptonEta_angleS_nume;
 TH1D *Iso_LeptonPt_nume;
 TH1D *Iso_ZPt_nume;
 TH1D *Iso_Zrapidity_nume;
 TH1D *Iso_cos_theta_star_nume;
 TH2D *Iso_LeptonEta_Pt_nume;

 TH1D *Iso_Zrapidity_lumi1_angleL_deno;
 TH1D *Iso_Zrapidity_lumi2_angleL_deno;
 TH1D *Iso_Zrapidity_lumi3_angleL_deno;
 TH1D *Iso_Zrapidity_lumi1_angleS_deno;
 TH1D *Iso_Zrapidity_lumi2_angleS_deno;
 TH1D *Iso_Zrapidity_lumi3_angleS_deno; 
 TH1D *Iso_Zrapidity_lumi1_angleL_nume;
 TH1D *Iso_Zrapidity_lumi2_angleL_nume;
 TH1D *Iso_Zrapidity_lumi3_angleL_nume;
 TH1D *Iso_Zrapidity_lumi1_angleS_nume;
 TH1D *Iso_Zrapidity_lumi2_angleS_nume;
 TH1D *Iso_Zrapidity_lumi3_angleS_nume;

 TH1D *Id_ZMass_LeptonEta_Pt[9][3];

 TH1D *Id_ZMass_25_30;

 //function
 void BookHist(const char *fName);
 void SaveHist();
};

#endif
