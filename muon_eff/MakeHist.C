#ifndef MAKEHIST_SOURCE
#define MAKEHIST_SOURCE

#include"State.h"

using namespace std;

void MakeHist::BookHist(const char *fName)
{//func_BookHist
 result = new TFile(fName,"RECREATE");

 Double_t x_eta[55] = {-3.2, -2.8, -2.6, -2.4, -2.3, -2.2, -2.1, -2, -1.9, -1.8, -1.7, -1.6, -1.5, -1.4, -1.3, -1.2, -1.1, -1, -0.9, -0.8, -0.7, -0.6, -0.5, -0.4, -0.3, -0.2, -0.1, 0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2, 2.1, 2.2, 2.3, 2.4, 2.6, 2.8, 3.2};
 
 Double_t x_pt[25] = {15,20,25,28,30,32,34,36,38,39,40,41,42,43,44,45,47,50,55,60,70,75,80,100,120};

 double x_eta_2D[10] = {-1.8,-1.4,-1.0,-0.6,-0.2,0.2,0.6,1.0,1.4,1.8};
 double x_pt_2D[4] = {15,30,50,200}; 

 //Initial plots
 
 char name[100];
 for(int i=0;i<9;i++)
  for(int j=0;j<3;j++)
  {
   sprintf(name,"Id_ZMass_LeptonEta%d_Pt%d",i,j);
   Id_ZMass_LeptonEta_Pt[i][j] = new TH1D(name,name,70,60,130);
   Id_ZMass_LeptonEta_Pt[i][j]->Sumw2();
  }


 Id_ZMass_deno = new TH1D("Id_ZMass_deno","Id_ZMass_deno",140,60,130);
 Id_ZMass_deno->Sumw2();
 Id_ZMass_nume = new TH1D("Id_ZMass_nume","Id_ZMass_nume",140,60,130);
 Id_ZMass_nume->Sumw2();

 Id_LeptonEta_deno = new TH1D("Id_LeptonEta_deno","Id_LeptonEta_deno",54,x_eta);
 Id_LeptonEta_deno->Sumw2();
 Id_LeptonEta_nume = new TH1D("Id_LeptonEta_nume","Id_LeptonEta_nume",54,x_eta);
 Id_LeptonEta_nume->Sumw2();
 
 Id_LeptonPt_deno = new TH1D("Id_LeptonPt_deno","Id_LeptonPt_deno",24,x_pt);
 Id_LeptonPt_deno->Sumw2();
 Id_LeptonPt_nume = new TH1D("Id_LeptonPt_nume","Id_LeptonPt_nume",24,x_pt);
 Id_LeptonPt_nume->Sumw2();

 Id_ZPt_deno = new TH1D("Id_ZPt_deno","Id_ZPt_deno",50,0,100);
 Id_ZPt_deno->Sumw2();
 Id_ZPt_nume = new TH1D("Id_ZPt_nume","Id_ZPt_nume",50,0,100);
 Id_ZPt_nume->Sumw2();

 Id_Zrapidity_deno = new TH1D("Id_Zrapidity_deno","Id_Zrapidity_deno",60,-3,3);
 Id_Zrapidity_deno->Sumw2();
 Id_Zrapidity_nume = new TH1D("Id_Zrapidity_nume","Id_Zrapidity_nume",60,-3,3);
 Id_Zrapidity_nume->Sumw2();

 Id_cos_theta_star_deno = new TH1D("Id_cos_theta_star_deno","Id_cos_theta_star_deno",50,-1,1);
 Id_cos_theta_star_deno->Sumw2();
 Id_cos_theta_star_nume = new TH1D("Id_cos_theta_star_nume","Id_cos_theta_star_nume",50,-1,1);
 Id_cos_theta_star_nume->Sumw2();

 Id_LeptonEta_Pt_deno = new TH2D("Id_LeptonEta_Pt_deno","Id_LeptonEta_Pt_deno",9,x_eta_2D,3,x_pt_2D);
 Id_LeptonEta_Pt_deno->Sumw2();
 Id_LeptonEta_Pt_nume = new TH2D("Id_LeptonEta_Pt_nume","Id_LeptonEta_Pt_nume",9,x_eta_2D,3,x_pt_2D);
 Id_LeptonEta_Pt_nume->Sumw2();
  

 Trk_ZMass_deno = new TH1D("Trk_ZMass_deno","Trk_ZMass_deno",140,60,130);
 Trk_ZMass_deno->Sumw2();
 Trk_ZMass_nume = new TH1D("Trk_ZMass_nume","Trk_ZMass_nume",140,60,130);
 Trk_ZMass_nume->Sumw2();

 Trk_LeptonEta_deno = new TH1D("Trk_LeptonEta_deno","Trk_LeptonEta_deno",54,x_eta);
 Trk_LeptonEta_deno->Sumw2();
 Trk_LeptonEta_nume = new TH1D("Trk_LeptonEta_nume","Trk_LeptonEta_nume",54,x_eta);
 Trk_LeptonEta_nume->Sumw2();

 Trk_LeptonPt_deno = new TH1D("Trk_LeptonPt_deno","Trk_LeptonPt_deno",24,x_pt);
 Trk_LeptonPt_deno->Sumw2();
 Trk_LeptonPt_nume = new TH1D("Trk_LeptonPt_nume","Trk_LeptonPt_nume",24,x_pt);
 Trk_LeptonPt_nume->Sumw2();

 Trk_ZPt_deno = new TH1D("Trk_ZPt_deno","Trk_ZPt_deno",50,0,100);
 Trk_ZPt_deno->Sumw2();
 Trk_ZPt_nume = new TH1D("Trk_ZPt_nume","Trk_ZPt_nume",50,0,100);
 Trk_ZPt_nume->Sumw2();

 Trk_Zrapidity_deno = new TH1D("Trk_Zrapidity_deno","Trk_Zrapidity_deno",60,-3,3);
 Trk_Zrapidity_deno->Sumw2();
 Trk_Zrapidity_nume = new TH1D("Trk_Zrapidity_nume","Trk_Zrapidity_nume",60,-3,3);
 Trk_Zrapidity_nume->Sumw2();

 Trk_cos_theta_star_deno = new TH1D("Trk_cos_theta_star_deno","Trk_cos_theta_star_deno",50,-1,1);
 Trk_cos_theta_star_deno->Sumw2();
 Trk_cos_theta_star_nume = new TH1D("Trk_cos_theta_star_nume","Trk_cos_theta_star_nume",50,-1,1);
 Trk_cos_theta_star_nume->Sumw2();

 Trk_LeptonEta_Pt_deno = new TH2D("Trk_LeptonEta_Pt_deno","Trk_LeptonEta_Pt_deno",9,x_eta_2D,3,x_pt_2D);
 Trk_LeptonEta_Pt_deno->Sumw2();
 Trk_LeptonEta_Pt_nume = new TH2D("Trk_LeptonEta_Pt_nume","Trk_LeptonEta_Pt_nume",9,x_eta_2D,3,x_pt_2D);
 Trk_LeptonEta_Pt_nume->Sumw2();


 Iso_ZMass_deno = new TH1D("Iso_ZMass_deno","Iso_ZMass_deno",140,60,130);
 Iso_ZMass_deno->Sumw2();
 Iso_ZMass_nume = new TH1D("Iso_ZMass_nume","Iso_ZMass_nume",140,60,130);
 Iso_ZMass_nume->Sumw2();

 Iso_LeptonEta_deno = new TH1D("Iso_LeptonEta_deno","Iso_LeptonEta_deno",54,x_eta);
 Iso_LeptonEta_deno->Sumw2();
 Iso_LeptonEta_nume = new TH1D("Iso_LeptonEta_nume","Iso_LeptonEta_nume",54,x_eta);
 Iso_LeptonEta_nume->Sumw2();

 Iso_LeptonPt_deno = new TH1D("Iso_LeptonPt_deno","Iso_LeptonPt_deno",24,x_pt);
 Iso_LeptonPt_deno->Sumw2();
 Iso_LeptonPt_nume = new TH1D("Iso_LeptonPt_nume","Iso_LeptonPt_nume",24,x_pt);
 Iso_LeptonPt_nume->Sumw2();

 Iso_ZPt_deno = new TH1D("Iso_ZPt_deno","Iso_ZPt_deno",50,0,100);
 Iso_ZPt_deno->Sumw2();
 Iso_ZPt_nume = new TH1D("Iso_ZPt_nume","Iso_ZPt_nume",50,0,100);
 Iso_ZPt_nume->Sumw2();

 Iso_Zrapidity_deno = new TH1D("Iso_Zrapidity_deno","Iso_Zrapidity_deno",60,-3,3);
 Iso_Zrapidity_deno->Sumw2();
 Iso_Zrapidity_nume = new TH1D("Iso_Zrapidity_nume","Iso_Zrapidity_nume",60,-3,3);
 Iso_Zrapidity_nume->Sumw2();

 Iso_cos_theta_star_deno = new TH1D("Iso_cos_theta_star_deno","Iso_cos_theta_star_deno",50,-1,1);
 Iso_cos_theta_star_deno->Sumw2();
 Iso_cos_theta_star_nume = new TH1D("Iso_cos_theta_star_nume","Iso_cos_theta_star_nume",50,-1,1);
 Iso_cos_theta_star_nume->Sumw2();

 Iso_LeptonEta_Pt_deno = new TH2D("Iso_LeptonEta_Pt_deno","Iso_LeptonEta_Pt_deno",9,x_eta_2D,3,x_pt_2D);
 Iso_LeptonEta_Pt_deno->Sumw2();
 Iso_LeptonEta_Pt_nume = new TH2D("Iso_LeptonEta_Pt_nume","Iso_LeptonEta_Pt_nume",9,x_eta_2D,3,x_pt_2D);
 Iso_LeptonEta_Pt_nume->Sumw2();

 Id_ZMass_25_30 = new TH1D("Id_ZMass_25_30","Id_ZMass_25_30",36,74,110);
 Id_ZMass_25_30->Sumw2();
}//func_BookHist

void MakeHist::SaveHist(void)
{//func_SaveHist
 result->Write();
}//func_SaveHist

#endif
