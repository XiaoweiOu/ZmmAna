#ifndef ZMMANA_SOURCE
#define ZMMANA_SOURCE

#include"State.h"

void ZmmAna::Loop(const char *TypeName)
{//func_Loop
 if(isRead==false)
 {
  return;
 }

 if(fChain==NULL)return;

 //define event number in this tree
 Int_t Nentries = fChain->GetEntries();
 
 for(int ii=0;ii<Nentries;ii++)
 {
  fChain->GetEntry(ii);
  Sta_total_number++;

  TLorentzVector muon,anti_muon,Zboson,temp;
  if((string)TypeName=="ResBos")
  {
   anti_muon.SetPxPyPzE(Px_d1,Py_d1,Pz_d1,E_d1);
   muon.SetPxPyPzE(Px_d2,Py_d2,Pz_d2,E_d2);
   Zboson.SetPxPyPzE(Px_V,Py_V,Pz_V,E_V);
  }
  if((string)TypeName=="Pythia")
  {
   muon.SetPxPyPzE(ElectronPx,ElectronPy,ElectronPz,ElectronE);
   anti_muon.SetPxPyPzE(PositronPx,PositronPy,PositronPz,PositronE);
   Zboson.SetPxPyPzE(ZPx,ZPy,ZPz,ZE);
  }

  Double_t total_weight;
  total_weight = 1;

  if((string)TypeName=="ResBos")
  total_weight = WT00;

  if(fabs(muon.Eta()) > 1.6 || fabs(anti_muon.Eta()) > 1.6)
   continue;

  if(muon.Pt()<15)continue;
  if(anti_muon.Pt()<15)continue;
  if(Zboson.M()<74 || Zboson.M()>110)continue;

  //***************************************//
  //           fill histagrams!!!          //
  //***************************************//

  Double_t star;//cos theta star
  star = 2*(anti_muon.E()*muon.Pz()-muon.E()*anti_muon.Pz())
                   /(Zboson.M()*sqrt(Zboson.M()*Zboson.M() + Zboson.Pt()*Zboson.Pt()));

  //use it to estimate efficiency sysmetic uncertainty!!!!!!!!
   if(Zboson.Rapidity()<0.2 && Zboson.Rapidity()>-0.2)
   {
    if(fabs(muon.Eta())<0.2 && fabs(anti_muon.Eta())<0.2)myHist->Oppo_muon->Fill(fabs(muon.Eta()),total_weight);
    if(fabs(muon.Eta())>0.2 && fabs(muon.Eta())<0.6 &&
      fabs(anti_muon.Eta())>0.2 && fabs(anti_muon.Eta())<0.6)myHist->Oppo_muon->Fill(fabs(muon.Eta()),total_weight);
    if(fabs(muon.Eta())>0.6 && fabs(muon.Eta())<1.0 &&
      fabs(anti_muon.Eta())>0.6 && fabs(anti_muon.Eta())<1.0)myHist->Oppo_muon->Fill(fabs(muon.Eta()),total_weight);
    if(fabs(muon.Eta())>1.0 && fabs(muon.Eta())<1.4 &&
      fabs(anti_muon.Eta())>1.0 && fabs(anti_muon.Eta())<1.4)myHist->Oppo_muon->Fill(fabs(muon.Eta()),total_weight);
    if(fabs(muon.Eta())>1.4 && fabs(muon.Eta())<1.8 &&
      fabs(anti_muon.Eta())>1.4 && fabs(anti_muon.Eta())<1.8)myHist->Oppo_muon->Fill(fabs(muon.Eta()),total_weight);
   }

   
   if(muon.Eta()>0.2 && muon.Eta()<0.6 &&
      anti_muon.Eta()>0.2 && anti_muon.Eta()<0.6 &&
      Zboson.Rapidity()>0.2 && Zboson.Rapidity()<0.6)myHist->Both_muon->Fill(muon.Eta(),total_weight);
   if(muon.Eta()>0.6 && muon.Eta()<1.0 &&
      anti_muon.Eta()>0.6 && anti_muon.Eta()<1.0 &&
      Zboson.Rapidity()>0.6 && Zboson.Rapidity()<1.0)myHist->Both_muon->Fill(muon.Eta(),total_weight);
   if(muon.Eta()>1.0 && muon.Eta()<1.4 &&
      anti_muon.Eta()>1.0 && anti_muon.Eta()<1.4 &&
      Zboson.Rapidity()>1.0 && Zboson.Rapidity()<1.4)myHist->Both_muon->Fill(muon.Eta(),total_weight);
   if(muon.Eta()>1.4 && muon.Eta()<1.8 &&
      anti_muon.Eta()>1.4 && anti_muon.Eta()<1.8 &&
      Zboson.Rapidity()>1.4 && Zboson.Rapidity()<1.8)myHist->Both_muon->Fill(muon.Eta(),total_weight);

   if(-muon.Eta()>0.2 && -muon.Eta()<0.6 &&
      -anti_muon.Eta()>0.2 && -anti_muon.Eta()<0.6 &&
      -Zboson.Rapidity()>0.2 && -Zboson.Rapidity()<0.6)myHist->Both_muon->Fill(muon.Eta(),total_weight);
   if(-muon.Eta()>0.6 && -muon.Eta()<1.0 &&
      -anti_muon.Eta()>0.6 && -anti_muon.Eta()<1.0 &&
      -Zboson.Rapidity()>0.6 && -Zboson.Rapidity()<1.0)myHist->Both_muon->Fill(muon.Eta(),total_weight);
   if(-muon.Eta()>1.0 && -muon.Eta()<1.4 &&
      -anti_muon.Eta()>1.0 && -anti_muon.Eta()<1.4 &&
      -Zboson.Rapidity()>1.0 && -Zboson.Rapidity()<1.4)myHist->Both_muon->Fill(muon.Eta(),total_weight);
   if(-muon.Eta()>1.4 && -muon.Eta()<1.8 &&
      -anti_muon.Eta()>1.4 && -anti_muon.Eta()<1.8 &&
      -Zboson.Rapidity()>1.4 && -Zboson.Rapidity()<1.8)myHist->Both_muon->Fill(muon.Eta(),total_weight);

   //forward!
   if(star>0)
   {
   if(Zboson.Rapidity()<0.2 && Zboson.Rapidity()>-0.2)
   {
    if(fabs(muon.Eta())<0.2 && fabs(anti_muon.Eta())<0.2)myHist->Oppo_muon_F->Fill(fabs(muon.Eta()),total_weight);
    if(fabs(muon.Eta())>0.2 && fabs(muon.Eta())<0.6 &&
      fabs(anti_muon.Eta())>0.2 && fabs(anti_muon.Eta())<0.6)myHist->Oppo_muon_F->Fill(fabs(muon.Eta()),total_weight);
    if(fabs(muon.Eta())>0.6 && fabs(muon.Eta())<1.0 &&
      fabs(anti_muon.Eta())>0.6 && fabs(anti_muon.Eta())<1.0)myHist->Oppo_muon_F->Fill(fabs(muon.Eta()),total_weight);
    if(fabs(muon.Eta())>1.0 && fabs(muon.Eta())<1.4 &&
      fabs(anti_muon.Eta())>1.0 && fabs(anti_muon.Eta())<1.4)myHist->Oppo_muon_F->Fill(fabs(muon.Eta()),total_weight);
    if(fabs(muon.Eta())>1.4 && fabs(muon.Eta())<1.8 &&
      fabs(anti_muon.Eta())>1.4 && fabs(anti_muon.Eta())<1.8)myHist->Oppo_muon_F->Fill(fabs(muon.Eta()),total_weight);
   }


   if(muon.Eta()>0.2 && muon.Eta()<0.6 &&
      anti_muon.Eta()>0.2 && anti_muon.Eta()<0.6 &&
      Zboson.Rapidity()>0.2 && Zboson.Rapidity()<0.6)myHist->Both_muon_F->Fill(muon.Eta(),total_weight);
   if(muon.Eta()>0.6 && muon.Eta()<1.0 &&
      anti_muon.Eta()>0.6 && anti_muon.Eta()<1.0 &&
      Zboson.Rapidity()>0.6 && Zboson.Rapidity()<1.0)myHist->Both_muon_F->Fill(muon.Eta(),total_weight);
   if(muon.Eta()>1.0 && muon.Eta()<1.4 &&
      anti_muon.Eta()>1.0 && anti_muon.Eta()<1.4 &&
      Zboson.Rapidity()>1.0 && Zboson.Rapidity()<1.4)myHist->Both_muon_F->Fill(muon.Eta(),total_weight);
   if(muon.Eta()>1.4 && muon.Eta()<1.8 &&
      anti_muon.Eta()>1.4 && anti_muon.Eta()<1.8 &&
      Zboson.Rapidity()>1.4 && Zboson.Rapidity()<1.8)myHist->Both_muon_F->Fill(muon.Eta(),total_weight);

   if(-muon.Eta()>0.2 && -muon.Eta()<0.6 &&
      -anti_muon.Eta()>0.2 && -anti_muon.Eta()<0.6 &&
      -Zboson.Rapidity()>0.2 && -Zboson.Rapidity()<0.6)myHist->Both_muon_F->Fill(muon.Eta(),total_weight);
   if(-muon.Eta()>0.6 && -muon.Eta()<1.0 &&
      -anti_muon.Eta()>0.6 && -anti_muon.Eta()<1.0 &&
      -Zboson.Rapidity()>0.6 && -Zboson.Rapidity()<1.0)myHist->Both_muon_F->Fill(muon.Eta(),total_weight);
   if(-muon.Eta()>1.0 && -muon.Eta()<1.4 &&
      -anti_muon.Eta()>1.0 && -anti_muon.Eta()<1.4 &&
      -Zboson.Rapidity()>1.0 && -Zboson.Rapidity()<1.4)myHist->Both_muon_F->Fill(muon.Eta(),total_weight);
   if(-muon.Eta()>1.4 && -muon.Eta()<1.8 &&
      -anti_muon.Eta()>1.4 && -anti_muon.Eta()<1.8 &&
      -Zboson.Rapidity()>1.4 && -Zboson.Rapidity()<1.8)myHist->Both_muon_F->Fill(muon.Eta(),total_weight);
   }

   //backward!
   if(star<0)
   {
   if(Zboson.Rapidity()<0.2 && Zboson.Rapidity()>-0.2)
   {
    if(fabs(muon.Eta())<0.2 && fabs(anti_muon.Eta())<0.2)myHist->Oppo_muon_B->Fill(fabs(muon.Eta()),total_weight);
    if(fabs(muon.Eta())>0.2 && fabs(muon.Eta())<0.6 &&
      fabs(anti_muon.Eta())>0.2 && fabs(anti_muon.Eta())<0.6)myHist->Oppo_muon_B->Fill(fabs(muon.Eta()),total_weight);
    if(fabs(muon.Eta())>0.6 && fabs(muon.Eta())<1.0 &&
      fabs(anti_muon.Eta())>0.6 && fabs(anti_muon.Eta())<1.0)myHist->Oppo_muon_B->Fill(fabs(muon.Eta()),total_weight);
    if(fabs(muon.Eta())>1.0 && fabs(muon.Eta())<1.4 &&
      fabs(anti_muon.Eta())>1.0 && fabs(anti_muon.Eta())<1.4)myHist->Oppo_muon_B->Fill(fabs(muon.Eta()),total_weight);
    if(fabs(muon.Eta())>1.4 && fabs(muon.Eta())<1.8 &&
      fabs(anti_muon.Eta())>1.4 && fabs(anti_muon.Eta())<1.8)myHist->Oppo_muon_B->Fill(fabs(muon.Eta()),total_weight);
   }


   if(muon.Eta()>0.2 && muon.Eta()<0.6 &&
      anti_muon.Eta()>0.2 && anti_muon.Eta()<0.6 &&
      Zboson.Rapidity()>0.2 && Zboson.Rapidity()<0.6)myHist->Both_muon_B->Fill(muon.Eta(),total_weight);
   if(muon.Eta()>0.6 && muon.Eta()<1.0 &&
      anti_muon.Eta()>0.6 && anti_muon.Eta()<1.0 &&
      Zboson.Rapidity()>0.6 && Zboson.Rapidity()<1.0)myHist->Both_muon_B->Fill(muon.Eta(),total_weight);
   if(muon.Eta()>1.0 && muon.Eta()<1.4 &&
      anti_muon.Eta()>1.0 && anti_muon.Eta()<1.4 &&
      Zboson.Rapidity()>1.0 && Zboson.Rapidity()<1.4)myHist->Both_muon_B->Fill(muon.Eta(),total_weight);
   if(muon.Eta()>1.4 && muon.Eta()<1.8 &&
      anti_muon.Eta()>1.4 && anti_muon.Eta()<1.8 &&
      Zboson.Rapidity()>1.4 && Zboson.Rapidity()<1.8)myHist->Both_muon_B->Fill(muon.Eta(),total_weight);

   if(-muon.Eta()>0.2 && -muon.Eta()<0.6 &&
      -anti_muon.Eta()>0.2 && -anti_muon.Eta()<0.6 &&
      -Zboson.Rapidity()>0.2 && -Zboson.Rapidity()<0.6)myHist->Both_muon_B->Fill(muon.Eta(),total_weight);
   if(-muon.Eta()>0.6 && -muon.Eta()<1.0 &&
      -anti_muon.Eta()>0.6 && -anti_muon.Eta()<1.0 &&
      -Zboson.Rapidity()>0.6 && -Zboson.Rapidity()<1.0)myHist->Both_muon_B->Fill(muon.Eta(),total_weight);
   if(-muon.Eta()>1.0 && -muon.Eta()<1.4 &&
      -anti_muon.Eta()>1.0 && -anti_muon.Eta()<1.4 &&
      -Zboson.Rapidity()>1.0 && -Zboson.Rapidity()<1.4)myHist->Both_muon_B->Fill(muon.Eta(),total_weight);
   if(-muon.Eta()>1.4 && -muon.Eta()<1.8 &&
      -anti_muon.Eta()>1.4 && -anti_muon.Eta()<1.8 &&
      -Zboson.Rapidity()>1.4 && -Zboson.Rapidity()<1.8)myHist->Both_muon_B->Fill(muon.Eta(),total_weight);
   }
 
  if(star>0)myHist->Zrapidity_F->Fill(Zboson.Rapidity(),total_weight);
  if(star<0)myHist->Zrapidity_B->Fill(Zboson.Rapidity(),total_weight);

  if(star>0)myHist->ZMass_F->Fill(Zboson.M(),total_weight);
  if(star<0)myHist->ZMass_B->Fill(Zboson.M(),total_weight);

  myHist->ZMass->Fill(Zboson.M(),total_weight);
  myHist->LeptonEta->Fill(muon.Eta(),total_weight);
  myHist->LeptonEta->Fill(anti_muon.Eta(),total_weight);
  myHist->LeptonPt->Fill(muon.Pt(),total_weight);
  myHist->LeptonPt->Fill(anti_muon.Pt(),total_weight);
  myHist->Zrapidity->Fill(Zboson.Rapidity(),total_weight);
  myHist->ZPt->Fill(Zboson.Pt(),total_weight);
  myHist->cos_theta_star->Fill(star,total_weight);
 }
}//func_Loop

#endif
