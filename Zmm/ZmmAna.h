#ifndef ZMMANA_HEADER
#define ZMMANA_HEADER

#include"State.h"

using namespace std;

//define class
class ZmmAna
{
 public:
  TTree *fChain;
  
  //declaration of leaf types
  Double_t        zdata_mc_q;
   Double_t        zdata_mc_x1;
   Double_t        zdata_mc_x2;
   Int_t           zdata_mc_flav1;
   Int_t           zdata_mc_flav2;
   Double_t        zdata_mc_vtxz;
   Double_t        zdata_mc_instlum;
   Int_t           zdata_mc_muon_Q[2];
   Double_t        zdata_mc_muon_E[2];
   Double_t        zdata_mc_evtwt;
   Double_t        zdata_mc_muon_px[2];
   Double_t        zdata_mc_muon_py[2];
   Double_t        zdata_mc_muon_pz[2];
   Double_t        zdata_mc_muon_eta[2];
   Double_t        zdata_mc_collin;
   Double_t        zdata_mc_Mass;
   Double_t        zdata_mc_ZPartMass;
   Double_t        zdata_mc_ZRapidity;
   Double_t        zdata_mc_ZPt;
   Double_t        zdata_mc_ZPx;
   Double_t        zdata_mc_ZPy;
   Double_t        zdata_mc_ZPz;
   Double_t        zdata_mc_ZE;
   Double_t        zdata_mc_xsect;
   Double_t        zdata_mc_rwt_vtx;
   Double_t        zdata_mc_rwt_zpt;
   Double_t        zdata_mc_rwt_mass;
   Int_t           zdata_event_type;
   Int_t           zdata_recoed;
   Int_t           zdata_RunNo;
   Int_t           zdata_EvtNo;
   Double_t        zdata_evtwt;
   Int_t           zdata_solenoid_P;
   Int_t           zdata_toroid_P;
   Double_t        zdata_vtxz;
   Double_t        zdata_instlum;
   Double_t        zdata_met_em[3];
   Double_t        zdata_metx[3];
   Double_t        zdata_mety[3];
   Double_t        zdata_metphi[3];
   Double_t        zdata_metset[3];
   Double_t        zdata_collin;
   Double_t        zdata_Mass;
   Double_t        zdata_z_pt;
   Double_t        zdata_z_rapidity;
   Int_t           zdata_single_trk_number;
   Int_t           zdata_muon_number;
   Int_t           zdata_muon_mark[20];
   Double_t        zdata_muon_pT[20];
   Double_t        zdata_muon_Eta[20];
   Double_t        zdata_muon_Phi[20];
   Int_t           zdata_muon_syst_nhit[20];
   Int_t           zdata_muon_syst_ndeck[20];
   Int_t           zdata_muon_syst_region[20];
   Int_t           zdata_muon_syst_octant[20];
   Double_t        zdata_muon_syst_chisqloc[20];
   Double_t        zdata_muon_syst_sctimeA[20];
   Double_t        zdata_muon_syst_sctimeB[20];
   Double_t        zdata_muon_syst_sctimeC[20];
   Double_t        zdata_muon_syst_xA[20];
   Double_t        zdata_muon_syst_yA[20];
   Double_t        zdata_muon_syst_zA[20];
   Int_t           zdata_muon_syst_bdl[20];
   Int_t           zdata_muon_mtc_nseg[20];
   Int_t           zdata_muon_mtc_ndof[20];
   Double_t        zdata_muon_mtc_deltaPhi[20];
   Double_t        zdata_muon_mtc_deltaEta[20];
   Double_t        zdata_muon_mtc_deltaDrift[20];
   Double_t        zdata_muon_mtc_chisq[20];
   Double_t        zdata_muon_mtc_zAtPca[20];
   Double_t        zdata_muon_mtc_impPar[20];
   Double_t        zdata_muon_mtc_impParSig[20];
   Double_t        zdata_muon_mtc_err_impPar[20];
   Double_t        zdata_muon_mtc_err_zAtPca[20];
   Double_t        zdata_muon_mtc_dca[20];
   Double_t        zdata_muon_mtc_deteta[20];
   Int_t           zdata_muon_calnLayer[20];
   Int_t           zdata_muon_nmtc[20];
   Double_t        zdata_muon_etrack_best[20];
   Double_t        zdata_muon_caleSig[20];
   Double_t        zdata_muon_calEta[20];
   Double_t        zdata_muon_calPhi[20];
   Double_t        zdata_muon_eloss[20];
   Int_t           zdata_muon_nTrk5[20];
   Double_t        zdata_muon_EInCone1[20];
   Double_t        zdata_muon_EInCone15[20];
   Double_t        zdata_muon_EInCone2[20];
   Double_t        zdata_muon_EInCone4[20];
   Double_t        zdata_muon_EInCone6[20];
   Double_t        zdata_muon_drJet5[20];
   Double_t        zdata_muon_etTrkCone5[20];
   Double_t        zdata_muon_etHalo[20];
   Int_t           zdata_muon_flg_isLoose[20];
   Int_t           zdata_muon_flg_isMedium[20];
   Int_t           zdata_muon_flg_isTight[20];
   Int_t           zdata_muon_flg_hasLocal[20];
   Int_t           zdata_muon_flg_hasCentral[20];
   Int_t           zdata_muon_flg_hasCal[20];
   Int_t           zdata_muon_flg_isMuonEventOK[20];
   Int_t           zdata_muon_flg_isCosmic[20];
   Int_t           zdata_muon_flg_isCosmicT[20];
   Int_t           zdata_muon_flg_isFixed[20];
   Int_t           zdata_muon_expWhitsA[20];
   Int_t           zdata_muon_expWhitsBC[20];
   Int_t           zdata_muon_expShitsA[20];
   Int_t           zdata_muon_expShitsBC[20];
   Double_t        zdata_muon_etTrkCone5_lowdr[20];
   Double_t        zdata_muon_etHalo_lowdr[20];
   Int_t           zdata_muon_trk_match[20];
   Double_t        zdata_muon_trk_pt[20];
   Double_t        zdata_muon_trk_px[20];
   Double_t        zdata_muon_trk_py[20];
   Double_t        zdata_muon_trk_pz[20];
   Double_t        zdata_muon_trk_E[20];
   Int_t           zdata_muon_trk_ncft[20];
   Int_t           zdata_muon_trk_nsmt[20];
   Int_t           zdata_muon_trk_charge[20];
   Double_t        zdata_muon_trk_chi2[20];
   Double_t        zdata_muon_trk_dca[20];
   Double_t        zdata_muon_trk_nocorr_dca[20];
   Double_t        zdata_muon_trk_z[20];
   Double_t        zdata_muon_trk_eta[20];
   Double_t        zdata_muon_trk_phi[20];
   Double_t        zdata_muon_trk_trkiso[20];
   Int_t           zdata_single_trk_mark[40];
   Double_t        zdata_single_trk_pt[40];
   Double_t        zdata_single_trk_px[40];
   Double_t        zdata_single_trk_py[40];
   Double_t        zdata_single_trk_pz[40];
   Double_t        zdata_single_trk_E[40];
   Int_t           zdata_single_trk_ncft[40];
   Int_t           zdata_single_trk_nsmt[40];
   Int_t           zdata_single_trk_charge[40];
   Double_t        zdata_single_trk_chi2[40];
   Double_t        zdata_single_trk_dca[40];
   Double_t        zdata_single_trk_nocorr_dca[40];
   Double_t        zdata_single_trk_z[40];
   Double_t        zdata_single_trk_eta[40];
   Double_t        zdata_single_trk_phi[40];
   Double_t        zdata_single_trk_trkiso[40];
   Double_t        zdata_single_trk_trkiso_rmvnoise[40];
   Double_t        zdata_single_trk_caliso[40];
   Int_t           zdata_single_trk_matchmuon[40];

   // List of branches
   TBranch        *b_mc_q;   //!
   TBranch        *b_mc_x1;   //!
   TBranch        *b_mc_x2;   //!
   TBranch        *b_mc_flav1;   //!
   TBranch        *b_mc_flav2;   //!
   TBranch        *b_mc_vtxz;   //!
   TBranch        *b_mc_instlum;   //!
   TBranch        *b_mc_muon_Q;   //!
   TBranch        *b_mc_muon_E;   //!
   TBranch        *b_mc_evtwt;   //!
   TBranch        *b_mc_muon_px;   //!
   TBranch        *b_mc_muon_py;   //!
   TBranch        *b_mc_muon_pz;   //!
   TBranch        *b_mc_muon_eta;   //!
   TBranch        *b_mc_collin;   //!
   TBranch        *b_mc_Mass;   //!
   TBranch        *b_mc_ZPartMass;   //!
   TBranch        *b_mc_ZRapidity;   //!
   TBranch        *b_mc_ZPt;   //!
   TBranch        *b_mc_ZPx;   //!
   TBranch        *b_mc_ZPy;   //!
   TBranch        *b_mc_ZPz;   //!
   TBranch        *b_mc_ZE;   //!
   TBranch        *b_mc_xsect;   //!
   TBranch        *b_mc_rwt_vtx;   //!
   TBranch        *b_mc_rwt_zpt;   //!
   TBranch        *b_mc_rwt_mass;   //!
   TBranch        *b_event_type;   //!
   TBranch        *b_recoed;   //!
   TBranch        *b_RunNo;   //!
   TBranch        *b_EvtNo;   //!
   TBranch        *b_evtwt;   //!
   TBranch        *b_solenoid_P;   //!
   TBranch        *b_toroid_P;   //!
   TBranch        *b_vtxz;   //!
   TBranch        *b_instlum;   //!
   TBranch        *b_met_em;   //!
   TBranch        *b_metx;   //!
   TBranch        *b_mety;   //!
   TBranch        *b_metphi;   //!
   TBranch        *b_metset;   //!
   TBranch        *b_collin;   //!
   TBranch        *b_Mass;   //!
   TBranch        *b_z_pt;   //!
   TBranch        *b_z_rapidity;   //!
   TBranch        *b_single_trk_number;   //!
   TBranch        *b_muon_number;   //!
   TBranch        *b_muon_mark;   //!
   TBranch        *b_muon_pT;   //!
   TBranch        *b_muon_Eta;   //!
   TBranch        *b_muon_Phi;   //!
   TBranch        *b_muon_syst_nhit;   //!
   TBranch        *b_muon_syst_ndeck;   //!
   TBranch        *b_muon_syst_region;   //!
   TBranch        *b_muon_syst_octant;   //!
   TBranch        *b_muon_syst_chisqloc;   //!
   TBranch        *b_muon_syst_sctimeA;   //!
   TBranch        *b_muon_syst_sctimeB;   //!
   TBranch        *b_muon_syst_sctimeC;   //!
   TBranch        *b_muon_syst_xA;   //!
   TBranch        *b_muon_syst_yA;   //!
   TBranch        *b_muon_syst_zA;   //!
   TBranch        *b_muon_syst_bdl;   //!
   TBranch        *b_muon_mtc_nseg;   //!
   TBranch        *b_muon_mtc_ndof;   //!
   TBranch        *b_muon_mtc_deltaPhi;   //!
   TBranch        *b_muon_mtc_deltaEta;   //!
   TBranch        *b_muon_mtc_deltaDrift;   //!
   TBranch        *b_muon_mtc_chisq;   //!
   TBranch        *b_muon_mtc_zAtPca;   //!
   TBranch        *b_muon_mtc_impPar;   //!
   TBranch        *b_muon_mtc_impParSig;   //!
   TBranch        *b_muon_mtc_err_impPar;   //!
   TBranch        *b_muon_mtc_err_zAtPca;   //!
   TBranch        *b_muon_mtc_dca;   //!
   TBranch        *b_muon_mtc_deteta;   //!
   TBranch        *b_muon_calnLayer;   //!
   TBranch        *b_muon_nmtc;   //!
   TBranch        *b_muon_etrack_best;   //!
   TBranch        *b_muon_caleSig;   //!
   TBranch        *b_muon_calEta;   //!
   TBranch        *b_muon_calPhi;   //!
   TBranch        *b_muon_eloss;   //!
   TBranch        *b_muon_nTrk5;   //!
   TBranch        *b_muon_EInCone1;   //!
   TBranch        *b_muon_EInCone15;   //!
   TBranch        *b_muon_EInCone2;   //!
   TBranch        *b_muon_EInCone4;   //!
   TBranch        *b_muon_EInCone6;   //!
   TBranch        *b_muon_drJet5;   //!
   TBranch        *b_muon_etTrkCone5;   //!
   TBranch        *b_muon_etHalo;   //!
   TBranch        *b_muon_flg_isLoose;   //!
   TBranch        *b_muon_flg_isMedium;   //!
   TBranch        *b_muon_flg_isTight;   //!
   TBranch        *b_muon_flg_hasLocal;   //!
   TBranch        *b_muon_flg_hasCentral;   //!
   TBranch        *b_muon_flg_hasCal;   //!
   TBranch        *b_muon_flg_isMuonEventOK;   //!
   TBranch        *b_muon_flg_isCosmic;   //!
   TBranch        *b_muon_flg_isCosmicT;   //!
   TBranch        *b_muon_flg_isFixed;   //!
   TBranch        *b_muon_expWhitsA;   //!
   TBranch        *b_muon_expWhitsBC;   //!
   TBranch        *b_muon_expShitsA;   //!
   TBranch        *b_muon_expShitsBC;   //!
   TBranch        *b_muon_etTrkCone5_lowdr;   //!
   TBranch        *b_muon_etHalo_lowdr;   //!
   TBranch        *b_muon_trk_match;   //!
   TBranch        *b_muon_trk_pt;   //!
   TBranch        *b_muon_trk_px;   //!
   TBranch        *b_muon_trk_py;   //!
   TBranch        *b_muon_trk_pz;   //!
   TBranch        *b_muon_trk_E;   //!
   TBranch        *b_muon_trk_ncft;   //!
   TBranch        *b_muon_trk_nsmt;   //!
   TBranch        *b_muon_trk_charge;   //!
   TBranch        *b_muon_trk_chi2;   //!
   TBranch        *b_muon_trk_dca;   //!
   TBranch        *b_muon_trk_nocorr_dca;   //!
   TBranch        *b_muon_trk_z;   //!
   TBranch        *b_muon_trk_eta;   //!
   TBranch        *b_muon_trk_phi;   //!
   TBranch        *b_muon_trk_trkiso;   //!
   TBranch        *b_single_trk_mark;   //!
   TBranch        *b_single_trk_pt;   //!
   TBranch        *b_single_trk_px;   //!
   TBranch        *b_single_trk_py;   //!
   TBranch        *b_single_trk_pz;   //!
   TBranch        *b_single_trk_E;   //!
   TBranch        *b_single_trk_ncft;   //!
   TBranch        *b_single_trk_nsmt;   //!
   TBranch        *b_single_trk_charge;   //!
   TBranch        *b_single_trk_chi2;   //!
   TBranch        *b_single_trk_dca;   //!
   TBranch        *b_single_trk_nocorr_dca;   //!
   TBranch        *b_single_trk_z;   //!
   TBranch        *b_single_trk_eta;   //!
   TBranch        *b_single_trk_phi;   //!
   TBranch        *b_single_trk_trkiso;   //!
   TBranch        *b_single_trk_trkiso_rmvnoise;   //!
   TBranch        *b_single_trk_caliso;   //!
   TBranch        *b_single_trk_matchmuon;   //! 
  
  //function
  ZmmAna(const char *FileList, const char *TypeName,const char *BagNo,string doWhat);
  virtual ~ZmmAna();
  virtual void Initial(const char *RootName,int RootNumber);
  virtual void Loop(const char *TypeName);
  virtual void End(int RootNumber);
  virtual void Finish(int RootNumber);
  virtual void Output();

  //control variable
  bool isRead;
  bool isData=false;
  bool isMC=false;//signal MC
  bool isEWMC=false;

  bool Is_EffNume=false;//no lumi-rwt
  bool Is_Fiducial=false;//trhth level cut
  bool Is_EffSystWeight=false;//add weight
  bool Is_noCali=false;
  bool Is_Normal=false;
  bool Is_Matrix=false;
  bool Is_SS=false;//QCD_num
  bool Is_QCDspectrum=false;
  bool Is_cali5=false;
  bool Is_cali1=false;
  bool Is_eff1=false;
  bool Is_eff2=false;
  bool Is_eff3=false;
 
  //counting number
  Double_t Sta_total_number;

  //one plus, one minus
  Double_t Sta_Nll;
  Double_t Sta_Nh1h1;
  Double_t Sta_Nh2h2;
  Double_t Sta_Nh3h3;
  Double_t Sta_Nh4h4;

  //pp:++ mm:--
  Double_t Sta_Nh1h1pp;
  Double_t Sta_Nh1h1mm;
  Double_t Sta_Nh2h2pp;
  Double_t Sta_Nh2h2mm;
  Double_t Sta_Nh3h3pp;
  Double_t Sta_Nh3h3mm;
  Double_t Sta_Nh4h4pp;
  Double_t Sta_Nh4h4mm;

  //rwt plots
  TH1D *_Lumi_new_file;
  TH2D *Zpt_2D_rwt;
  TH2D *Id_eff;
  TH2D *Trk_eff;
  TH2D *Iso_eff;
  TH1D *Id_eff_1D;
  TH1D *Trk_eff_1D;
  TH1D *Iso_eff_1D;
  TH2D *trigger_eff_etaphibin;

  TFile *f_alpha;//calibration
  TH1D *muon_SN;
  TH1D *muon_SP;
  TH1D *anti_muon_SN;
  TH1D *anti_muon_SP;

  //plots
  MakeHist *myHist;

  //random number
  TRandom3 r1,r2,r3;
};//class defination

inline ZmmAna::ZmmAna(const char *FileList,const char *TypeName,const char *BagNo,string doWhat)
{//func_ZmmAna

 //Initialize random number
 r1.SetSeed(1);
 r2.SetSeed(2);
 r3.SetSeed(3);

 //Initialize control variable
 TString InputName = (TString)TypeName;
 if(InputName=="data")
  isData=true;
 if(InputName=="MC")
  isMC=true;
 if(InputName=="EWMC")
  isEWMC=true;


 if(doWhat=="QCD_num")
  Is_SS=true;
 if(doWhat=="QCD_spectrum")
  Is_QCDspectrum=true;
 if(doWhat=="EffNume"&&isMC==true)
  Is_EffNume=true;//no lumi-rwt
 if(doWhat=="Fiducial"&&isMC==true)
  Is_Fiducial=true;//trhth level cut
 if(doWhat=="EffSystWeight"&&isMC==true)
  Is_EffSystWeight=true;//add weight
 if(doWhat=="noCali")
  Is_noCali=true;
 if(doWhat=="Normal")
  Is_Normal=true;
 if(doWhat=="Matrix" && isMC==true)
  Is_Matrix=true;
 if(doWhat=="cali5" && isMC==true)
  Is_cali5=true;
 if(doWhat=="cali1" && isMC==true)
  Is_cali1=true;

 //Initialize histograms
 myHist = new MakeHist();
 TString histName;

 if(isData == true && Is_Normal == true)
  histName = "./data_Normal/" + (TString)TypeName + (TString)BagNo +".root";
 if(isData == true && Is_noCali == true)
  histName = "./data_noCali/" + (TString)TypeName + (TString)BagNo +".root";

 if(Is_EffNume==true && isMC==true)
  histName = "MC_result/MC_foreff.root";
 if(Is_Fiducial==true && isMC==true)
  histName = "MC_result/MC_fiducial.root";
 if(Is_EffSystWeight==true && isMC==true)
  histName = "MC_result/MC_EffSystWeight.root";
 if(Is_noCali==true && isMC==true)
  histName = "MC_result/MC_noCali.root";
 if(Is_Normal==true && isMC==true)
  histName = "MC_result/MC_Normal.root";
 if(Is_Matrix==true && isMC==true)
  histName = "MC_result/MC_Matrix.root";
 if(Is_cali1==true && isMC==true)
  histName = "MC_result/MC_cali1.root";
 if(Is_cali5==true && isMC==true)
  histName = "MC_result/MC_cali5.root";

 if(Is_SS == true)
  histName = "./QCD_num/" + (TString)TypeName + "_" +(TString) BagNo + ".root";
 if(Is_QCDspectrum==true)
  histName = "./QCD_spectrum/" + (TString)TypeName + "_" +(TString) BagNo + ".root";

 if(isEWMC == true && Is_Normal == true)
  histName = "./EW_bkg/" + (TString) BagNo + ".root";
 
 myHist->BookHist(histName);

 //add additional efficiency correction!
 if(doWhat=="EffNume"&&isMC==true)
  Is_EffSystWeight=true;
 if(doWhat=="Fiducial"&&isMC==true)
  Is_EffSystWeight=true;
 if(doWhat=="Matrix")
  Is_EffSystWeight=true;
 if(doWhat=="cali1" || doWhat=="cali5")
 {
  Is_EffSystWeight=true;
  Is_Matrix=true;//use this file to calculate unfolding matrix
 }

 //Initialize counting number
 Sta_total_number=0;
 Sta_Nll=0;
 Sta_Nh1h1=0;
 Sta_Nh2h2=0;
 Sta_Nh3h3=0;
 Sta_Nh4h4=0;

 Sta_Nh1h1pp=0;
 Sta_Nh1h1mm=0;
 Sta_Nh2h2pp=0;
 Sta_Nh2h2mm=0;
 Sta_Nh3h3pp=0;
 Sta_Nh3h3mm=0;
 Sta_Nh4h4pp=0;
 Sta_Nh4h4mm=0;

 //Initialize calibration
 f_alpha = new TFile("/lustre/AtlUser/xwou/ZmmAna/migration/factor_alpha.root");
 if(isData == true)
 {
  muon_SN = (TH1D *)f_alpha->Get("data_muon_SN");
  muon_SP = (TH1D *)f_alpha->Get("data_muon_SP");
  anti_muon_SN = (TH1D *)f_alpha->Get("data_anti_muon_SN");
  anti_muon_SP = (TH1D *)f_alpha->Get("data_anti_muon_SP");
 }
 if(isMC == true)
 {
  muon_SN = (TH1D *)f_alpha->Get("MC_muon_SN");
  muon_SP = (TH1D *)f_alpha->Get("MC_muon_SP");
  anti_muon_SN = (TH1D *)f_alpha->Get("MC_anti_muon_SN");
  anti_muon_SP = (TH1D *)f_alpha->Get("MC_anti_muon_SP");
 }

 //initializing luminosity
 std::string lumi_new = "../include/Lum_reweight.C";
 std::string temp2 = string(".x ") + lumi_new;
 if(isEWMC == true)
 {
  temp2 = string(".x ") + "/lustre/AtlUser/xwou/ZmmAna/Zmm_bkg/LuminosityReweight/new/" + BagNo + "_MC_LumiReweight.C";
 
  string sub_str;
  sub_str.assign(BagNo,4);
  if(sub_str=="W0lp")
  temp2 = string(".x ") + "/lustre/AtlUser/xwou/ZmmAna/Zmm_bkg/LuminosityReweight/new/W0lp_MC_LumiReweight.C"; 
  if(sub_str=="W1lp")
  temp2 = string(".x ") + "/lustre/AtlUser/xwou/ZmmAna/Zmm_bkg/LuminosityReweight/new/W1lp_MC_LumiReweight.C"; 
 }
 gROOT->ProcessLine(temp2.c_str());
 if(isEWMC == true)
 {
  _Lumi_new_file = (TH1D *)gROOT->FindObject("LumiReweight");
 }
 if(isEWMC == false)_Lumi_new_file = (TH1D *)gROOT->FindObject("Lum_Scalefactor");
 _Lumi_new_file->SetName("Lumi_reweight_factor_new");
 
 //2D zpt reweighting
 temp2 = ".x ../include/Resbos_Pythia_ZPt_Y_Ratio.C";
 gROOT->ProcessLine(temp2.c_str());
 Zpt_2D_rwt = (TH2D *)gROOT->FindObject("_h_zypt");
     
 //trigger efficiency
 temp2 = ".x ../include/trigger_eff_etaphibin.cpp";
 gROOT->ProcessLine(temp2.c_str());
 trigger_eff_etaphibin = (TH2D *)gROOT->FindObject("eff_etaphibin");

 TFile *eff_file = new TFile("../mass_fitting/cal_eff.root");

 //Is_eff3 = true;

 if(Is_eff1==true)
  Id_eff = (TH2D *)eff_file->Get("scale_Id_LeptonEta_Pt_eff1");
 else if(Is_eff2==true)
  Id_eff = (TH2D *)eff_file->Get("scale_Id_LeptonEta_Pt_eff2");
 else if(Is_eff3==true) 
  Id_eff = (TH2D *)eff_file->Get("scale_Id_LeptonEta_Pt_eff3");
 else
  Id_eff = (TH2D *)eff_file->Get("scale_Id_LeptonEta_Pt_central");//central:(fit+MC)/2
  
}//func_ZmmAna

inline ZmmAna::~ZmmAna()
{
}

inline void ZmmAna::Initial(const char *RootName,int RootNumber)
{//func_Initial
 TFile *file = new TFile(RootName);
 TTree *orgTree = NULL;
 orgTree = (TTree *)gDirectory->Get("Ztree");

 fChain = orgTree;

 //tips for begin reading
 cout<<"Running:Starting Rootfile"<<RootNumber<<endl;

 //whether an empty tree
 isRead = true;
 double entryNumber;
 if(fChain==NULL)
 {
  isRead = false;
  cout<<"****** this file has no Ztree, skip to next!!! ******"<<endl;
  return;
 }
 if(fChain!=NULL)
  entryNumber = fChain->GetEntries();

 cout<<"entryNumber = "<<entryNumber<<endl;

 if(entryNumber==0)
 {
  isRead = false;
  cout<<"****** this tree has no event, skip to next!!! ******"<<endl;
  return;
 }
 
 //Set address of the tree
   fChain->SetBranchAddress("zdata_mc_q", &zdata_mc_q, &b_mc_q);
   fChain->SetBranchAddress("zdata_mc_x1", &zdata_mc_x1, &b_mc_x1);
   fChain->SetBranchAddress("zdata_mc_x2", &zdata_mc_x2, &b_mc_x2);
   fChain->SetBranchAddress("zdata_mc_flav1", &zdata_mc_flav1, &b_mc_flav1);
   fChain->SetBranchAddress("zdata_mc_flav2", &zdata_mc_flav2, &b_mc_flav2);
   fChain->SetBranchAddress("zdata_mc_vtxz", &zdata_mc_vtxz, &b_mc_vtxz);
   fChain->SetBranchAddress("zdata_mc_instlum", &zdata_mc_instlum, &b_mc_instlum);
   fChain->SetBranchAddress("zdata_mc_muon_Q", zdata_mc_muon_Q, &b_mc_muon_Q);
   fChain->SetBranchAddress("zdata_mc_muon_E", zdata_mc_muon_E, &b_mc_muon_E);
   fChain->SetBranchAddress("zdata_mc_evtwt", &zdata_mc_evtwt, &b_mc_evtwt);
   fChain->SetBranchAddress("zdata_mc_muon_px", zdata_mc_muon_px, &b_mc_muon_px);
   fChain->SetBranchAddress("zdata_mc_muon_py", zdata_mc_muon_py, &b_mc_muon_py);
   fChain->SetBranchAddress("zdata_mc_muon_pz", zdata_mc_muon_pz, &b_mc_muon_pz);
   fChain->SetBranchAddress("zdata_mc_muon_eta", zdata_mc_muon_eta, &b_mc_muon_eta);
   fChain->SetBranchAddress("zdata_mc_collin", &zdata_mc_collin, &b_mc_collin);
   fChain->SetBranchAddress("zdata_mc_Mass", &zdata_mc_Mass, &b_mc_Mass);
   fChain->SetBranchAddress("zdata_mc_ZPartMass", &zdata_mc_ZPartMass, &b_mc_ZPartMass);
   fChain->SetBranchAddress("zdata_mc_ZRapidity", &zdata_mc_ZRapidity, &b_mc_ZRapidity);
   fChain->SetBranchAddress("zdata_mc_ZPt", &zdata_mc_ZPt, &b_mc_ZPt);
   fChain->SetBranchAddress("zdata_mc_ZPx", &zdata_mc_ZPx, &b_mc_ZPy);
   fChain->SetBranchAddress("zdata_mc_ZPy", &zdata_mc_ZPy, &b_mc_ZPy);
   fChain->SetBranchAddress("zdata_mc_ZPz", &zdata_mc_ZPz, &b_mc_ZPz);
   fChain->SetBranchAddress("zdata_mc_ZE", &zdata_mc_ZE, &b_mc_ZE);
   fChain->SetBranchAddress("zdata_mc_xsect", &zdata_mc_xsect, &b_mc_xsect);
   fChain->SetBranchAddress("zdata_mc_rwt_vtx", &zdata_mc_rwt_vtx, &b_mc_rwt_vtx);
   fChain->SetBranchAddress("zdata_mc_rwt_zpt", &zdata_mc_rwt_zpt, &b_mc_rwt_zpt);
   fChain->SetBranchAddress("zdata_mc_rwt_mass", &zdata_mc_rwt_mass, &b_mc_rwt_mass);
   fChain->SetBranchAddress("zdata_event_type", &zdata_event_type, &b_event_type);
   fChain->SetBranchAddress("zdata_recoed", &zdata_recoed, &b_recoed);
   fChain->SetBranchAddress("zdata_RunNo", &zdata_RunNo, &b_RunNo);
   fChain->SetBranchAddress("zdata_EvtNo", &zdata_EvtNo, &b_EvtNo);
   fChain->SetBranchAddress("zdata_evtwt", &zdata_evtwt, &b_evtwt);
   fChain->SetBranchAddress("zdata_solenoid_P", &zdata_solenoid_P, &b_solenoid_P);
   fChain->SetBranchAddress("zdata_toroid_P", &zdata_toroid_P, &b_toroid_P);
   fChain->SetBranchAddress("zdata_vtxz", &zdata_vtxz, &b_vtxz);
   fChain->SetBranchAddress("zdata_instlum", &zdata_instlum, &b_instlum);
   fChain->SetBranchAddress("zdata_met_em", zdata_met_em, &b_met_em);
   fChain->SetBranchAddress("zdata_metx", zdata_metx, &b_metx);
   fChain->SetBranchAddress("zdata_mety", zdata_mety, &b_mety);
   fChain->SetBranchAddress("zdata_metphi", zdata_metphi, &b_metphi);
   fChain->SetBranchAddress("zdata_metset", zdata_metset, &b_metset);
   fChain->SetBranchAddress("zdata_collin", &zdata_collin, &b_collin);
   fChain->SetBranchAddress("zdata_Mass", &zdata_Mass, &b_Mass);
   fChain->SetBranchAddress("zdata_z_pt", &zdata_z_pt, &b_z_pt);
   fChain->SetBranchAddress("zdata_z_rapidity", &zdata_z_rapidity, &b_z_rapidity);
   fChain->SetBranchAddress("zdata_single_trk_number", &zdata_single_trk_number, &b_single_trk_number);
   fChain->SetBranchAddress("zdata_muon_number", &zdata_muon_number, &b_muon_number);
   fChain->SetBranchAddress("zdata_muon_mark", zdata_muon_mark, &b_muon_mark);
   fChain->SetBranchAddress("zdata_muon_pT", zdata_muon_pT, &b_muon_pT);
   fChain->SetBranchAddress("zdata_muon_Eta", zdata_muon_Eta, &b_muon_Eta);
   fChain->SetBranchAddress("zdata_muon_Phi", zdata_muon_Phi, &b_muon_Phi);
   fChain->SetBranchAddress("zdata_muon_syst_nhit", zdata_muon_syst_nhit, &b_muon_syst_nhit);
   fChain->SetBranchAddress("zdata_muon_syst_ndeck", zdata_muon_syst_ndeck, &b_muon_syst_ndeck);
   fChain->SetBranchAddress("zdata_muon_syst_region", zdata_muon_syst_region, &b_muon_syst_region);
   fChain->SetBranchAddress("zdata_muon_syst_octant", zdata_muon_syst_octant, &b_muon_syst_octant);
   fChain->SetBranchAddress("zdata_muon_syst_chisqloc", zdata_muon_syst_chisqloc, &b_muon_syst_chisqloc);
   fChain->SetBranchAddress("zdata_muon_syst_sctimeA", zdata_muon_syst_sctimeA, &b_muon_syst_sctimeA);
   fChain->SetBranchAddress("zdata_muon_syst_sctimeB", zdata_muon_syst_sctimeB, &b_muon_syst_sctimeB);
   fChain->SetBranchAddress("zdata_muon_syst_sctimeC", zdata_muon_syst_sctimeC, &b_muon_syst_sctimeC);
   fChain->SetBranchAddress("zdata_muon_syst_xA", zdata_muon_syst_xA, &b_muon_syst_xA);
   fChain->SetBranchAddress("zdata_muon_syst_yA", zdata_muon_syst_yA, &b_muon_syst_yA);
   fChain->SetBranchAddress("zdata_muon_syst_zA", zdata_muon_syst_zA, &b_muon_syst_zA);
   fChain->SetBranchAddress("zdata_muon_syst_bdl", zdata_muon_syst_bdl, &b_muon_syst_bdl);
   fChain->SetBranchAddress("zdata_muon_mtc_nseg", zdata_muon_mtc_nseg, &b_muon_mtc_nseg);
   fChain->SetBranchAddress("zdata_muon_mtc_ndof", zdata_muon_mtc_ndof, &b_muon_mtc_ndof);
   fChain->SetBranchAddress("zdata_muon_mtc_deltaPhi", zdata_muon_mtc_deltaPhi, &b_muon_mtc_deltaPhi);
   fChain->SetBranchAddress("zdata_muon_mtc_deltaEta", zdata_muon_mtc_deltaEta, &b_muon_mtc_deltaEta);
   fChain->SetBranchAddress("zdata_muon_mtc_deltaDrift", zdata_muon_mtc_deltaDrift, &b_muon_mtc_deltaDrift);
   fChain->SetBranchAddress("zdata_muon_mtc_chisq", zdata_muon_mtc_chisq, &b_muon_mtc_chisq);
   fChain->SetBranchAddress("zdata_muon_mtc_zAtPca", zdata_muon_mtc_zAtPca, &b_muon_mtc_zAtPca);
   fChain->SetBranchAddress("zdata_muon_mtc_impPar", zdata_muon_mtc_impPar, &b_muon_mtc_impPar);
   fChain->SetBranchAddress("zdata_muon_mtc_impParSig", zdata_muon_mtc_impParSig, &b_muon_mtc_impParSig);
   fChain->SetBranchAddress("zdata_muon_mtc_err_impPar", zdata_muon_mtc_err_impPar, &b_muon_mtc_err_impPar);
   fChain->SetBranchAddress("zdata_muon_mtc_err_zAtPca", zdata_muon_mtc_err_zAtPca, &b_muon_mtc_err_zAtPca);
   fChain->SetBranchAddress("zdata_muon_mtc_dca", zdata_muon_mtc_dca, &b_muon_mtc_dca);
   fChain->SetBranchAddress("zdata_muon_mtc_deteta", zdata_muon_mtc_deteta, &b_muon_mtc_deteta);
   fChain->SetBranchAddress("zdata_muon_calnLayer", zdata_muon_calnLayer, &b_muon_calnLayer);
   fChain->SetBranchAddress("zdata_muon_nmtc", zdata_muon_nmtc, &b_muon_nmtc);
   fChain->SetBranchAddress("zdata_muon_etrack_best", zdata_muon_etrack_best, &b_muon_etrack_best);
   fChain->SetBranchAddress("zdata_muon_caleSig", zdata_muon_caleSig, &b_muon_caleSig);
   fChain->SetBranchAddress("zdata_muon_calEta", zdata_muon_calEta, &b_muon_calEta);
   fChain->SetBranchAddress("zdata_muon_calPhi", zdata_muon_calPhi, &b_muon_calPhi);
   fChain->SetBranchAddress("zdata_muon_eloss", zdata_muon_eloss, &b_muon_eloss);
   fChain->SetBranchAddress("zdata_muon_nTrk5", zdata_muon_nTrk5, &b_muon_nTrk5);
   fChain->SetBranchAddress("zdata_muon_EInCone1", zdata_muon_EInCone1, &b_muon_EInCone1);
   fChain->SetBranchAddress("zdata_muon_EInCone15", zdata_muon_EInCone15, &b_muon_EInCone15);
   fChain->SetBranchAddress("zdata_muon_EInCone2", zdata_muon_EInCone2, &b_muon_EInCone2);
   fChain->SetBranchAddress("zdata_muon_EInCone4", zdata_muon_EInCone4, &b_muon_EInCone4);
   fChain->SetBranchAddress("zdata_muon_EInCone6", zdata_muon_EInCone6, &b_muon_EInCone6);
   fChain->SetBranchAddress("zdata_muon_drJet5", zdata_muon_drJet5, &b_muon_drJet5);
   fChain->SetBranchAddress("zdata_muon_etTrkCone5", zdata_muon_etTrkCone5, &b_muon_etTrkCone5);
   fChain->SetBranchAddress("zdata_muon_etHalo", zdata_muon_etHalo, &b_muon_etHalo);
   fChain->SetBranchAddress("zdata_muon_flg_isLoose", zdata_muon_flg_isLoose, &b_muon_flg_isLoose);
   fChain->SetBranchAddress("zdata_muon_flg_isMedium", zdata_muon_flg_isMedium, &b_muon_flg_isMedium);
   fChain->SetBranchAddress("zdata_muon_flg_isTight", zdata_muon_flg_isTight, &b_muon_flg_isTight);
   fChain->SetBranchAddress("zdata_muon_flg_hasLocal", zdata_muon_flg_hasLocal, &b_muon_flg_hasLocal);
   fChain->SetBranchAddress("zdata_muon_flg_hasCentral", zdata_muon_flg_hasCentral, &b_muon_flg_hasCentral);
   fChain->SetBranchAddress("zdata_muon_flg_hasCal", zdata_muon_flg_hasCal, &b_muon_flg_hasCal);
   fChain->SetBranchAddress("zdata_muon_flg_isMuonEventOK", zdata_muon_flg_isMuonEventOK, &b_muon_flg_isMuonEventOK);
   fChain->SetBranchAddress("zdata_muon_flg_isCosmic", zdata_muon_flg_isCosmic, &b_muon_flg_isCosmic);
   fChain->SetBranchAddress("zdata_muon_flg_isCosmicT", zdata_muon_flg_isCosmicT, &b_muon_flg_isCosmicT);
   fChain->SetBranchAddress("zdata_muon_flg_isFixed", zdata_muon_flg_isFixed, &b_muon_flg_isFixed);
   fChain->SetBranchAddress("zdata_muon_expWhitsA", zdata_muon_expWhitsA, &b_muon_expWhitsA);
   fChain->SetBranchAddress("zdata_muon_expWhitsBC", zdata_muon_expWhitsBC, &b_muon_expWhitsBC);
   fChain->SetBranchAddress("zdata_muon_expShitsA", zdata_muon_expShitsA, &b_muon_expShitsA);
   fChain->SetBranchAddress("zdata_muon_expShitsBC", zdata_muon_expShitsBC, &b_muon_expShitsBC);
   fChain->SetBranchAddress("zdata_muon_etTrkCone5_lowdr", zdata_muon_etTrkCone5_lowdr, &b_muon_etTrkCone5_lowdr);
   fChain->SetBranchAddress("zdata_muon_etHalo_lowdr", zdata_muon_etHalo_lowdr, &b_muon_etHalo_lowdr);
   fChain->SetBranchAddress("zdata_muon_trk_match", zdata_muon_trk_match, &b_muon_trk_match);
   fChain->SetBranchAddress("zdata_muon_trk_pt", zdata_muon_trk_pt, &b_muon_trk_pt);
   fChain->SetBranchAddress("zdata_muon_trk_px", zdata_muon_trk_px, &b_muon_trk_px);
   fChain->SetBranchAddress("zdata_muon_trk_py", zdata_muon_trk_py, &b_muon_trk_py);
   fChain->SetBranchAddress("zdata_muon_trk_pz", zdata_muon_trk_pz, &b_muon_trk_pz);
   fChain->SetBranchAddress("zdata_muon_trk_E", zdata_muon_trk_E, &b_muon_trk_E);
   fChain->SetBranchAddress("zdata_muon_trk_ncft", zdata_muon_trk_ncft, &b_muon_trk_ncft);
   fChain->SetBranchAddress("zdata_muon_trk_nsmt", zdata_muon_trk_nsmt, &b_muon_trk_nsmt);
   fChain->SetBranchAddress("zdata_muon_trk_charge", zdata_muon_trk_charge, &b_muon_trk_charge);
   fChain->SetBranchAddress("zdata_muon_trk_chi2", zdata_muon_trk_chi2, &b_muon_trk_chi2);
   fChain->SetBranchAddress("zdata_muon_trk_dca", zdata_muon_trk_dca, &b_muon_trk_dca);
   fChain->SetBranchAddress("zdata_muon_trk_nocorr_dca", zdata_muon_trk_nocorr_dca, &b_muon_trk_nocorr_dca);
   fChain->SetBranchAddress("zdata_muon_trk_z", zdata_muon_trk_z, &b_muon_trk_z);
   fChain->SetBranchAddress("zdata_muon_trk_eta", zdata_muon_trk_eta, &b_muon_trk_eta);
   fChain->SetBranchAddress("zdata_muon_trk_phi", zdata_muon_trk_phi, &b_muon_trk_phi);
   fChain->SetBranchAddress("zdata_muon_trk_trkiso", zdata_muon_trk_trkiso, &b_muon_trk_trkiso);
   fChain->SetBranchAddress("zdata_single_trk_mark", zdata_single_trk_mark, &b_single_trk_mark);
   fChain->SetBranchAddress("zdata_single_trk_pt", zdata_single_trk_pt, &b_single_trk_pt);
   fChain->SetBranchAddress("zdata_single_trk_px", zdata_single_trk_px, &b_single_trk_px);
   fChain->SetBranchAddress("zdata_single_trk_py", zdata_single_trk_py, &b_single_trk_py);
   fChain->SetBranchAddress("zdata_single_trk_pz", zdata_single_trk_pz, &b_single_trk_pz);
   fChain->SetBranchAddress("zdata_single_trk_E", zdata_single_trk_E, &b_single_trk_E);
   fChain->SetBranchAddress("zdata_single_trk_ncft", zdata_single_trk_ncft, &b_single_trk_ncft);
   fChain->SetBranchAddress("zdata_single_trk_nsmt", zdata_single_trk_nsmt, &b_single_trk_nsmt);
   fChain->SetBranchAddress("zdata_single_trk_charge", zdata_single_trk_charge, &b_single_trk_charge);
   fChain->SetBranchAddress("zdata_single_trk_chi2", zdata_single_trk_chi2, &b_single_trk_chi2);
   fChain->SetBranchAddress("zdata_single_trk_dca", zdata_single_trk_dca, &b_single_trk_dca);
   fChain->SetBranchAddress("zdata_single_trk_nocorr_dca", zdata_single_trk_nocorr_dca, &b_single_trk_nocorr_dca);
   fChain->SetBranchAddress("zdata_single_trk_z", zdata_single_trk_z, &b_single_trk_z);
   fChain->SetBranchAddress("zdata_single_trk_eta", zdata_single_trk_eta, &b_single_trk_eta);
   fChain->SetBranchAddress("zdata_single_trk_phi", zdata_single_trk_phi, &b_single_trk_phi);
   fChain->SetBranchAddress("zdata_single_trk_trkiso", zdata_single_trk_trkiso, &b_single_trk_trkiso);
   fChain->SetBranchAddress("zdata_single_trk_trkiso_rmvnoise", zdata_single_trk_trkiso_rmvnoise, &b_single_trk_trkiso_rmvnoise);
   fChain->SetBranchAddress("zdata_single_trk_caliso", zdata_single_trk_caliso, &b_single_trk_caliso);
   fChain->SetBranchAddress("zdata_single_trk_matchmuon", zdata_single_trk_matchmuon, &b_single_trk_matchmuon);
 
 return;
}//func_Initial

//finish analysis one rootfile
inline void ZmmAna::End(int RootNumber)
{//func_End
 if(isRead==false)
 {
  return;
 }

//output:free the current tree
 cout<<"Running: Free Rootfile"<<RootNumber<<endl;

 if(!fChain)
 {
  cout<<"!!!!!!!!!Big Error"<<RootNumber<<"!!!!!!!!"<<endl;
  return;
 }

 delete fChain->GetCurrentFile();
 }//func_End

//finish analysis all rootfiles
inline void ZmmAna::Finish(int RootNumber)
{//func_Finish
 cout<<endl;
 cout<<"Running:"<<RootNumber<<"files in total readed!"<<endl;

 //save histgram
 if(myHist)
 {
   myHist->SaveHist();
   delete myHist;
 }

 cout<<"Running: histgrams saved!"<<endl;
}//func_Finish

//output some statistic variables
inline void ZmmAna::Output(void)
{//func_Output
 cout<<endl;

 cout<<"total event number:"<<Sta_total_number<<endl;
}//func_Output
#endif
