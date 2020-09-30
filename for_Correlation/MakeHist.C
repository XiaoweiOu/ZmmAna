#ifndef MAKEHIST_SOURCE
#define MAKEHIST_SOURCE

#include"State.h"

using namespace std;

void MakeHist::BookHist(const char *fName)
{//func_BookHist
 result = new TFile(fName,"RECREATE");
 
 Double_t y[6]={0,0.2,0.6,1.0,1.4,1.8};

 char name[100];
 for(int u=0;u<9;u++)
  for(int v=0;v<9;v++)
   for(int p=0;p<3;p++)
    for(int q=0;q<3;q++)
    {
     sprintf(name,"Forward_Both_muon_eta%d%d_Pt%d%d",u,v,p,q);
     Forward_Both_muon_eta_Pt[u][v][p][q] = new TH1D(name,name,9,-1.8,1.8);
     sprintf(name,"Backward_Both_muon_eta%d%d_Pt%d%d",u,v,p,q);
     Backward_Both_muon_eta_Pt[u][v][p][q] = new TH1D(name,name,9,-1.8,1.8);
     sprintf(name,"Forward_Oppo_muon_eta%d%d_Pt%d%d",u,v,p,q);
     Forward_Oppo_muon_eta_Pt[u][v][p][q] = new TH1D(name,name,5,y);
     sprintf(name,"Backward_Oppo_muon_eta%d%d_Pt%d%d",u,v,p,q);
     Backward_Oppo_muon_eta_Pt[u][v][p][q] = new TH1D(name,name,5,y);

     Forward_Both_muon_eta_Pt[u][v][p][q]->Sumw2();
     Backward_Both_muon_eta_Pt[u][v][p][q]->Sumw2();
     Forward_Oppo_muon_eta_Pt[u][v][p][q]->Sumw2();
     Backward_Oppo_muon_eta_Pt[u][v][p][q]->Sumw2();

     sprintf(name,"Forward_Zrapidity_eta%d%d_Pt%d%d",u,v,p,q);
     Forward_Zrapidity_eta_Pt[u][v][p][q] = new TH1D(name,name,9,-1.8,1.8);
     sprintf(name,"Backward_Zrapidity_eta%d%d_Pt%d%d",u,v,p,q);
     Backward_Zrapidity_eta_Pt[u][v][p][q] = new TH1D(name,name,9,-1.8,1.8);
 
     Forward_Zrapidity_eta_Pt[u][v][p][q]->Sumw2();
     Backward_Zrapidity_eta_Pt[u][v][p][q]->Sumw2();

     sprintf(name,"num_true_eta%d%d_Pt%d%d",u,v,p,q);
     num_true_eta_Pt[u][v][p][q] = new TH1D(name,name,9,-1.8,1.8);
     sprintf(name,"num_true_reco_eta%d%d_Pt%d%d",u,v,p,q);
     num_true_reco_eta_Pt[u][v][p][q] = new TH2D(name,name,9,-1.8,1.8,9,-1.8,1.8);
 
     num_true_eta_Pt[u][v][p][q]->Sumw2();
     num_true_reco_eta_Pt[u][v][p][q]->Sumw2();
    }

}//func_BookHist

void MakeHist::SaveHist(void)
{//func_SaveHist
 result->Write();
}//func_SaveHist

#endif
