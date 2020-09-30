#ifndef ZMMANA_SOURCE
#define ZMMANA_SOURCE

#include"State.h"

double L_calculate(double trk_z,double eta)
{
 double theta,zp,h;
 int f;
 theta = 2*atan(exp(-eta));
 if(theta > PI/2)f=-1;
 if(theta < PI/2)f=1;
 zp = 126.0-(f*trk_z);
 h = zp*fabs(tan(theta));
 if(h>51.43)return 51.43;
 if(h<51.43)return h;
}

void ZmmAna::Loop(const char *TypeName)
{//func_Loop

 if(isRead==false)
 {
  return;
 }

 if(fChain==NULL)return;

 //define event number in this tree
 Int_t Nentries = fChain->GetEntries();
 
 //********************main code*********************//
 //                                                  //
 //                                                  //                                   
 //                                                  //
 //         xwou wrote it on 2018/10/16 at USTC      //
 //                                                  //
 //                                                  //
 //                                                  //
 //**************************************************//
 for(int ii=0;ii<Nentries;ii++)
 {
  fChain->GetEntry(ii);
  Sta_total_number++;
  myHist->luminosity->Fill(zdata_instlum);

  TLorentzVector true_muon,true_anti_muon,true_Zboson,temp;
  true_muon.SetPxPyPzE(zdata_mc_muon_px[0],zdata_mc_muon_py[0],zdata_mc_muon_pz[0],zdata_mc_muon_E[0]);
  true_anti_muon.SetPxPyPzE(zdata_mc_muon_px[1],zdata_mc_muon_py[1],zdata_mc_muon_pz[1],zdata_mc_muon_E[1]);
  if(zdata_mc_muon_Q[0]>0)
  {
   temp = true_muon;
   true_muon = true_anti_muon;
   true_anti_muon = temp;
  }  
  true_Zboson = true_muon + true_anti_muon;  

  Double_t total_weight;
  total_weight=1;
  
  int bin_zpt,bin_lumi;
  double test_weight_lumi;

  if(isMC==true)
  {
   total_weight=zdata_mc_evtwt;
   //total_weight=total_weight/zdata_mc_rwt_mass;//if add this,MC can normalize to data!

   bin_zpt = Zpt_2D_rwt->FindBin(zdata_mc_ZRapidity,zdata_mc_ZPt);
   total_weight = total_weight*(Zpt_2D_rwt->GetBinContent(bin_zpt))/zdata_mc_rwt_zpt;

   //do not use lumi-rwt to calculate overall efficiency
   if(Is_EffNume==false)
   {
    bin_lumi = _Lumi_new_file->FindBin(zdata_instlum);
    test_weight_lumi = _Lumi_new_file->GetBinContent(bin_lumi);

    if(fabs(test_weight_lumi)>=1e-100)//factor!=0
    total_weight = total_weight*_Lumi_new_file->GetBinContent(bin_lumi);
   }
  }
  if(isEWMC==true)
  {
   bin_lumi = _Lumi_new_file->FindBin(zdata_instlum);
   test_weight_lumi = _Lumi_new_file->GetBinContent(bin_lumi);

   if(fabs(test_weight_lumi)>=1e-100)
   total_weight = total_weight*test_weight_lumi;
  }

  TLorentzVector EWobject[20];
  int LepSub=-1,AntiLepSub=-1;
  bool flag[20];
  
  //selections of EM objects
  for(int p=0;p<zdata_muon_number && p<20;p++)
  {
   EWobject[p].SetPtEtaPhiM(zdata_muon_pT[p],zdata_muon_Eta[p],zdata_muon_Phi[p],0);
   flag[p]=1;
   
   if(Is_noCali==true || isEWMC==true || Is_SS==true || Is_QCDspectrum==true)//no cali use pt cut at here!
   {
    if(zdata_muon_pT[p]<15)flag[p]=0;
   }
   if(zdata_muon_mark[p]!=1)flag[p]=0;
   if(zdata_muon_mtc_nseg[p]<1)flag[p]=0;
   if(zdata_muon_trk_match[p]!=1)flag[p]=0;
   if(zdata_muon_trk_chi2[p]>4)flag[p]=0;
   if(zdata_muon_trk_nsmt[p]>0)
   {
    if(fabs(zdata_muon_trk_dca[p])>0.012)flag[p]=0;
   }
   if(zdata_muon_trk_nsmt[p]==0)
   {
    if(fabs(zdata_muon_trk_dca[p])>0.2)flag[p]=0;
   }

   if(Is_QCDspectrum == false)
   {
    if( (zdata_muon_etTrkCone5[p]/EWobject[p].Pt())>0.4)flag[p]=0;//track isolation
    if( ((zdata_muon_etHalo[p]-0.005*zdata_instlum)/EWobject[p].Pt())>0.4 )flag[p]=0;//cal isolation 
   }
   if(Is_QCDspectrum == true)
   {
    if( (zdata_muon_etTrkCone5[p]/EWobject[p].Pt())<=0.4)flag[p]=0;//track isolation
    if( ((zdata_muon_etHalo[p]-0.005*zdata_instlum)/EWobject[p].Pt())<=0.4 )flag[p]=0;//cal isolation
   }
  }

  for(int i=0;i<zdata_muon_number;i++)
   if(flag[i]==1)
   {
    LepSub=i;
    break;
   }
  for(int i=0;i<zdata_muon_number;i++)
   if(flag[i]==1 && i!=LepSub)
   {
    AntiLepSub=i;
    break;
   }

  if(LepSub==-1 || AntiLepSub==-1)
   continue;//two good muons!!!
  
  if(Is_SS == true)
  {
   if(zdata_muon_trk_charge[LepSub]!=zdata_muon_trk_charge[AntiLepSub])
    continue;//same sign selection!!!
  }
  if(Is_SS == false)
  {
   if(zdata_muon_trk_charge[LepSub]==zdata_muon_trk_charge[AntiLepSub])
    continue;
  }

  if(zdata_muon_trk_charge[LepSub]==1)
  {
   int change;
   change = LepSub;
   LepSub = AntiLepSub;
   AntiLepSub = change;
  }

  TLorentzVector muon,anti_muon,Zboson;
  muon = EWobject[LepSub];
  anti_muon = EWobject[AntiLepSub];
  Zboson = muon+anti_muon;

  //event selections
  if(zdata_muon_trk_nsmt[LepSub]>=2 && zdata_muon_trk_nsmt[AntiLepSub]>=2)
   if(fabs(zdata_muon_trk_z[LepSub]-zdata_muon_trk_z[AntiLepSub])>1)continue;
  if(zdata_muon_trk_nsmt[LepSub]>=2 && zdata_muon_trk_nsmt[AntiLepSub]<2)
   if(fabs(zdata_muon_trk_z[LepSub]-zdata_muon_trk_z[AntiLepSub])>1.5)continue;
  if(zdata_muon_trk_nsmt[LepSub]<2 && zdata_muon_trk_nsmt[AntiLepSub]>=2)
   if(fabs(zdata_muon_trk_z[LepSub]-zdata_muon_trk_z[AntiLepSub])>1.5)continue;
  if(zdata_muon_trk_nsmt[LepSub]<2 && zdata_muon_trk_nsmt[AntiLepSub]<2)
   if(fabs(zdata_muon_trk_z[LepSub]-zdata_muon_trk_z[AntiLepSub])>2)continue;

  Double_t p1,p2,cos_theta;
  p1=sqrt(muon.Px()*muon.Px() + muon.Py()*muon.Py() + muon.Pz()*muon.Pz());
  p2=sqrt(anti_muon.Px()*anti_muon.Px() + anti_muon.Py()*anti_muon.Py() + anti_muon.Pz()*anti_muon.Pz());
  cos_theta = (muon.Px()*anti_muon.Px() + muon.Py()*anti_muon.Py() + muon.Pz()*anti_muon.Pz())/(p1*p2);
  if(cos_theta<-0.99985)continue;

  // events type
  if(fabs(muon.Eta()) > 1.6 || fabs(anti_muon.Eta()) > 1.6)
   continue;
  if(fabs(zdata_muon_mtc_deteta[LepSub])>1.6 || fabs(zdata_muon_mtc_deteta[AntiLepSub])>1.6)
   continue;

  //truth and reco matched muons
  if(Is_Matrix==true)
  {
   Double_t dR1,dR2;
   dR1 = muon.DeltaR(true_muon);
   dR2 = anti_muon.DeltaR(true_anti_muon);
   if(dR1>0.3 || dR2>0.3)continue;
  }

  //Missing ET
/*  if(Is_SS==true)
  {
   if(zdata_met_em[0]<20)continue;
  }*/

  if(Is_noCali==false && isEWMC==false && Is_SS==false && Is_QCDspectrum==false)
  {
  //**************calibrations***************//
  //*****************************************//
  //*****************************************//
  Double_t ratio;//q/Pt
  Double_t S_SP = 1.00262,A_SP = 1.74e-3,B_SP = 1.01e-2,C_SP = 5.02e-2,D_SP = 6.14e-3;
  Double_t S_SN = 1.00191,A_SN = 1.75e-3,B_SN = 1.02e-2,C_SN = 5.23e-2,D_SN = 6.03e-3;
  Double_t U,N1,N2;
  Double_t L_Lep,L_AntiLep;
  int bin_alpha;
  Double_t content_alpha;

  L_Lep = L_calculate(zdata_muon_trk_z[LepSub],muon.Eta());
  //!!!!!!!!!!!!!!!!!! first step !!!!!!!!!!!!!!!!!!!!!//
  if(isMC == true)
  {
   //random number!!!
   U = r1.Uniform(0,1);
   N1 = r2.Gaus(0,1);
   N2 = r3.Gaus(0,1);
 
   if(zdata_solenoid_P>0)//Solenoid positive
   {
    if(U>C_SP)
    ratio = zdata_muon_trk_charge[LepSub]/muon.Pt()*S_SP + pow(51.69/L_Lep,2)*
        ( A_SP*N1 + B_SP*N2*sqrt(cosh(muon.Eta())) / muon.Pt() );

    if(U<C_SP)
    ratio = zdata_muon_trk_charge[LepSub]/muon.Pt()*S_SP + pow(51.69/L_Lep,2)*
        ( D_SP*N1 + B_SP*N2*sqrt(cosh(muon.Eta())) / muon.Pt() );
   }
   if(zdata_solenoid_P<=0)//Solenoid negative
   {
    if(U>C_SN)
    ratio = zdata_muon_trk_charge[LepSub]/muon.Pt()*S_SN + pow(51.69/L_Lep,2)*
        ( A_SN*N1 + B_SN*N2*sqrt(cosh(muon.Eta())) / muon.Pt() );
    if(U<C_SN)
    ratio = zdata_muon_trk_charge[LepSub]/muon.Pt()*S_SN + pow(51.69/L_Lep,2)*
        ( D_SN*N1 + B_SN*N2*sqrt(cosh(muon.Eta())) / muon.Pt() );
   }

   muon.SetPtEtaPhiM(zdata_muon_trk_charge[LepSub]/ratio,muon.Eta(),muon.Phi(),0);
  }

  //!!!!!!!!!!!! second step !!!!!!!!!!!!!// 
  if(zdata_solenoid_P>0)//SP
  {
    bin_alpha = muon_SP->FindBin(muon.Eta());
    content_alpha = muon_SP->GetBinContent(bin_alpha);
  }
  if(zdata_solenoid_P<=0)//SN
  {
    bin_alpha = muon_SN->FindBin(muon.Eta());
    content_alpha = muon_SN->GetBinContent(bin_alpha);
  }
  muon = muon*content_alpha;

  L_AntiLep = L_calculate(zdata_muon_trk_z[AntiLepSub],anti_muon.Eta());
  //!!!!!!!!!!!!!!!!!! first step !!!!!!!!!!!!!!!!!!!!!//
  if(isMC == true)
  {
   //random number!!!
   U = r1.Uniform(0,1);
   N1 = r2.Gaus(0,1);
   N2 = r3.Gaus(0,1);

   if(zdata_solenoid_P>0)//Solenoid positive
   {
    if(U>C_SP)
    ratio = zdata_muon_trk_charge[AntiLepSub]/anti_muon.Pt()*S_SP + pow(51.69/L_AntiLep,2)*
        ( A_SP*N1 + B_SP*N2*sqrt(cosh(anti_muon.Eta())) / anti_muon.Pt() );

    if(U<C_SP)
    ratio = zdata_muon_trk_charge[AntiLepSub]/anti_muon.Pt()*S_SP + pow(51.69/L_AntiLep,2)*
        ( D_SP*N1 + B_SP*N2*sqrt(cosh(anti_muon.Eta())) / anti_muon.Pt() );
   }
   if(zdata_solenoid_P<=0)//Solenoid negative
   {
    if(U>C_SN)
    ratio = zdata_muon_trk_charge[AntiLepSub]/anti_muon.Pt()*S_SN + pow(51.69/L_AntiLep,2)*
        ( A_SN*N1 + B_SN*N2*sqrt(cosh(anti_muon.Eta())) / anti_muon.Pt() );
    if(U<C_SN)
    ratio = zdata_muon_trk_charge[AntiLepSub]/anti_muon.Pt()*S_SN + pow(51.69/L_AntiLep,2)*
        ( D_SN*N1 + B_SN*N2*sqrt(cosh(anti_muon.Eta())) / anti_muon.Pt() );
   }
   anti_muon.SetPtEtaPhiM(zdata_muon_trk_charge[AntiLepSub]/ratio,anti_muon.Eta(),anti_muon.Phi(),0);
  }

  //!!!!!!!!!!!! second step !!!!!!!!!!!!!// 
  if(zdata_solenoid_P>0)//SP
  {
    bin_alpha = anti_muon_SP->FindBin(anti_muon.Eta());
    content_alpha = anti_muon_SP->GetBinContent(bin_alpha);
  }
  if(zdata_solenoid_P<=0)//SN
  {
    bin_alpha = anti_muon_SN->FindBin(anti_muon.Eta());
    content_alpha = anti_muon_SN->GetBinContent(bin_alpha);
  }
  anti_muon = anti_muon*content_alpha;

  Zboson = muon + anti_muon;
  }

  //use to estimate systematic uncertainty from calibration
  if(Is_cali1==true)
  {
   muon = muon*1.0001;
   anti_muon = anti_muon*1.0001;  
  }
  if(Is_cali5==true)
  {
   muon = muon*1.00005;
   anti_muon = anti_muon*0.99995;
  }

  //add pt, mass cut!!!
  if(muon.Pt()<15 || anti_muon.Pt()<15)continue; 

  //mass window!
  if(Zboson.M()<74 || Zboson.M()>110)continue;

  //test the fiducial correction!
  if(Is_Fiducial==true)
  {
   if(true_muon.Pt()<15)continue;
   if(true_anti_muon.Pt()<15)continue;
   if(zdata_mc_ZPartMass<74 || zdata_mc_ZPartMass>110)continue;
   if(fabs(true_muon.Eta()) > 1.8 || fabs(true_anti_muon.Eta()) > 1.8)
    continue;
   if(fabs(true_muon.Eta()) > 1.6 && fabs(true_anti_muon.Eta()) > 1.6)
    continue;
  }

  //cut finish!!!

  //!!!!!!!!!!!!!!!!efficiency!!!!!!!!!!!!!!!!//
  //******************************************//
  //******************************************//
 
  double trigger_eff1,trigger_eff2;
  double scalefactor=1;
  if(isMC==true || isEWMC ==true)
  {
     scalefactor = scalefactor*(Id_eff->GetBinContent(Id_eff->FindBin(muon.Eta(),muon.Pt())))*(Id_eff->GetBinContent(Id_eff->FindBin(anti_muon.Eta(),anti_muon.Pt())));

    Double_t muon_phi,anti_muon_phi;
    if(muon.Phi()<0)muon_phi = muon.Phi()+2*PI;
     else muon_phi = muon.Phi();
    if(anti_muon.Phi()<0)anti_muon_phi = anti_muon.Phi()+2*PI;
     else anti_muon_phi = anti_muon.Phi();

    if(fabs(zdata_muon_mtc_deteta[LepSub])<1.6)
     trigger_eff1=trigger_eff_etaphibin->GetBinContent(trigger_eff_etaphibin->FindBin(zdata_muon_mtc_deteta[LepSub],muon_phi));
    else if(zdata_muon_mtc_deteta[LepSub]>0 && zdata_muon_mtc_deteta[LepSub]<1.8)
     trigger_eff1=0.28294;
    else if(zdata_muon_mtc_deteta[LepSub]<0 && zdata_muon_mtc_deteta[LepSub]>-1.8)
     trigger_eff1=0.33187;
    else
     trigger_eff1=1;

    if(fabs(zdata_muon_mtc_deteta[AntiLepSub])<1.6)
     trigger_eff2=trigger_eff_etaphibin->GetBinContent(trigger_eff_etaphibin->FindBin(zdata_muon_mtc_deteta[AntiLepSub],anti_muon_phi));
    else if(zdata_muon_mtc_deteta[AntiLepSub]>0 && zdata_muon_mtc_deteta[AntiLepSub]<1.8)
     trigger_eff2=0.28294;
    else if(zdata_muon_mtc_deteta[AntiLepSub]<0 && zdata_muon_mtc_deteta[AntiLepSub]>-1.8)
     trigger_eff2=0.33187;
    else
     trigger_eff2=1;
    scalefactor=scalefactor*(1-(1-trigger_eff1)*(1-trigger_eff2));
  }
  total_weight=total_weight*scalefactor;

  //weight test: use to estimate efficiency sysmetic uncertainty!
  if(Is_EffSystWeight==true){
   /*double effp[4]={1.0172,1.0608,1.0354,1.0053};
   double effm[4]={1.0247,1.0613,1.0504,1.0211};*/

   double effp[4]={1.0116,1.0451,1.0290,1.0232};
   double effm[4]={1.0227,1.0452,1.0461,1.0296};

   if(muon.Eta()>0.2 && muon.Eta()<0.6)total_weight = total_weight*effp[0];
   if(muon.Eta()>0.6 && muon.Eta()<1.0)total_weight = total_weight*effp[1];
   if(muon.Eta()>1.0 && muon.Eta()<1.4)total_weight = total_weight*effp[2];
   if(muon.Eta()>1.4 && muon.Eta()<1.8)total_weight = total_weight*effp[3];

   if(-muon.Eta()>0.2 && -muon.Eta()<0.6)total_weight = total_weight*effm[0];
   if(-muon.Eta()>0.6 && -muon.Eta()<1.0)total_weight = total_weight*effm[1];
   if(-muon.Eta()>1.0 && -muon.Eta()<1.4)total_weight = total_weight*effm[2];
   if(-muon.Eta()>1.4 && -muon.Eta()<1.8)total_weight = total_weight*effm[3];

   if(anti_muon.Eta()>0.2 && anti_muon.Eta()<0.6)total_weight = total_weight*effp[0];
   if(anti_muon.Eta()>0.6 && anti_muon.Eta()<1.0)total_weight = total_weight*effp[1];
   if(anti_muon.Eta()>1.0 && anti_muon.Eta()<1.4)total_weight = total_weight*effp[2];
   if(anti_muon.Eta()>1.4 && anti_muon.Eta()<1.8)total_weight = total_weight*effp[3];

   if(-anti_muon.Eta()>0.2 && -anti_muon.Eta()<0.6)total_weight = total_weight*effm[0];
   if(-anti_muon.Eta()>0.6 && -anti_muon.Eta()<1.0)total_weight = total_weight*effm[1];
   if(-anti_muon.Eta()>1.0 && -anti_muon.Eta()<1.4)total_weight = total_weight*effm[2];
   if(-anti_muon.Eta()>1.4 && -anti_muon.Eta()<1.8)total_weight = total_weight*effm[3];
  }

  //***************************************//
  //           fill histagrams!!!          //
  //***************************************//

  //test!
  if(Zboson.Rapidity()>1.4 && Zboson.Rapidity()<1.8)
   myHist->muon_antimuon_P->Fill(muon.Eta(),anti_muon.Eta(),total_weight);
  if(-Zboson.Rapidity()>1.4 && -Zboson.Rapidity()<1.8)
   myHist->muon_antimuon_N->Fill(muon.Eta(),anti_muon.Eta(),total_weight);
  if(Zboson.Rapidity()>1.4 && Zboson.Rapidity()<1.8)
  {
   myHist->muon_Pt_etaP->Fill(muon.Eta(),total_weight);
   myHist->muon_Pt_etaP->Fill(anti_muon.Eta(),total_weight);
  }
  if(-Zboson.Rapidity()>1.4 && -Zboson.Rapidity()<1.8)
  { 
   myHist->muon_Pt_etaN->Fill(muon.Eta(),total_weight);
   myHist->muon_Pt_etaN->Fill(anti_muon.Eta(),total_weight);
  }

  if((muon.Eta()>-0.2 && muon.Eta()<0.2 && muon.Pt()>25 && muon.Pt()<30)
  || (anti_muon.Eta()>-0.2 && anti_muon.Eta()<0.2 && anti_muon.Pt()>25 && anti_muon.Pt()<30))
  myHist->ZMass_eta0_Pt->Fill(Zboson.M(),total_weight);
  //test end!

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
 
   //new method!!!
   //first:Z rapidity locate in which bin?
  /* int Y_bin,EtaBin_muon,EtaBin_anti_muon;
   Y_bin=floor((Zboson.Rapidity()+1.8)/0.2)+1;//1,2,3,...,18
   EtaBin_muon=floor((muon.Eta()+1.8)/0.2)+1;
   EtaBin_anti_muon=floor((anti_muon.Eta()+1.8)/0.2)+1;

   if(EtaBin_muon==Y_bin && EtaBin_anti_muon==Y_bin)//Nii
    myHist->Nii0->Fill(Zboson.Rapidity(),total_weight);

   if((EtaBin_muon==(Y_bin+1)&&EtaBin_anti_muon==(Y_bin-1))
    ||(EtaBin_muon==(Y_bin-1)&&EtaBin_anti_muon==(Y_bin+1)))//N(i-1)(i+1)
    myHist->Nii1->Fill(Zboson.Rapidity(),total_weight);

   if((EtaBin_muon==(Y_bin+2)&&EtaBin_anti_muon==(Y_bin-2))
    ||(EtaBin_muon==(Y_bin-2)&&EtaBin_anti_muon==(Y_bin+2)))//N[i-2](i+2)
    myHist->Nii2->Fill(Zboson.Rapidity(),total_weight);*/

  if(star>0)myHist->Zrapidity_F->Fill(Zboson.Rapidity(),total_weight);
  if(star<0)myHist->Zrapidity_B->Fill(Zboson.Rapidity(),total_weight);

  if(zdata_solenoid_P>0)//SP
  {
   myHist->ZMass_SP->Fill(Zboson.M(),total_weight);
   myHist->Zrapidity_SP->Fill(Zboson.Rapidity(),total_weight);
   myHist->ZPt_SP->Fill(Zboson.Pt(),total_weight);
   myHist->LeptonEta_SP->Fill(muon.Eta(),total_weight);
   myHist->LeptonEta_SP->Fill(anti_muon.Eta(),total_weight);
   myHist->LeptonPt_SP->Fill(muon.Pt(),total_weight);
   myHist->LeptonPt_SP->Fill(anti_muon.Pt(),total_weight);

   myHist->SP_num_true->Fill(zdata_mc_ZRapidity,total_weight);
   myHist->SP_num_true_reco->Fill(zdata_mc_ZRapidity,Zboson.Rapidity(),total_weight);   
   if(star>0)
   {
    myHist->F_SP->Fill(Zboson.M(),total_weight);
    myHist->F_SP_num_true->Fill(zdata_mc_ZRapidity,total_weight);
    myHist->F_SP_num_true_reco->Fill(zdata_mc_ZRapidity,Zboson.Rapidity(),total_weight);
    myHist->Zrapidity_SP_F->Fill(Zboson.Rapidity(),total_weight);
   }
   if(star<0)
   {
    myHist->B_SP->Fill(Zboson.M(),total_weight);
    myHist->B_SP_num_true->Fill(zdata_mc_ZRapidity,total_weight);
    myHist->B_SP_num_true_reco->Fill(zdata_mc_ZRapidity,Zboson.Rapidity(),total_weight);
    myHist->Zrapidity_SP_B->Fill(Zboson.Rapidity(),total_weight);
   }
  }
  if(zdata_solenoid_P<=0)//SN
  {
   myHist->ZMass_SN->Fill(Zboson.M(),total_weight);
   myHist->Zrapidity_SN->Fill(Zboson.Rapidity(),total_weight);
   myHist->ZPt_SN->Fill(Zboson.Pt(),total_weight);
   myHist->LeptonEta_SN->Fill(muon.Eta(),total_weight);
   myHist->LeptonEta_SN->Fill(anti_muon.Eta(),total_weight);
   myHist->LeptonPt_SN->Fill(muon.Pt(),total_weight);
   myHist->LeptonPt_SN->Fill(anti_muon.Pt(),total_weight);

   myHist->SN_num_true->Fill(zdata_mc_ZRapidity,total_weight);
   myHist->SN_num_true_reco->Fill(zdata_mc_ZRapidity,Zboson.Rapidity(),total_weight);
   if(star>0)
   {
    myHist->F_SN->Fill(Zboson.M(),total_weight);
    myHist->F_SN_num_true->Fill(zdata_mc_ZRapidity,total_weight);
    myHist->F_SN_num_true_reco->Fill(zdata_mc_ZRapidity,Zboson.Rapidity(),total_weight);
    myHist->Zrapidity_SN_F->Fill(Zboson.Rapidity(),total_weight);
   }
   if(star<0)
   {
    myHist->B_SN->Fill(Zboson.M(),total_weight);
    myHist->B_SN_num_true->Fill(zdata_mc_ZRapidity,total_weight);
    myHist->B_SN_num_true_reco->Fill(zdata_mc_ZRapidity,Zboson.Rapidity(),total_weight);
    myHist->Zrapidity_SN_B->Fill(Zboson.Rapidity(),total_weight);
   }
  }

  myHist->num_true->Fill(zdata_mc_ZRapidity,total_weight);
  myHist->num_true_reco->Fill(zdata_mc_ZRapidity,Zboson.Rapidity(),total_weight);

  myHist->ZMass->Fill(Zboson.M(),total_weight);

  //this plot is a little diffirent!
  //D_ij_alpha = (alpha,i,j) + (alpha,j,i)
  myHist->Zrap_muonEta->Fill(true_Zboson.Rapidity(),muon.Eta(),anti_muon.Eta(),total_weight);
  myHist->LeptonEta->Fill(muon.Eta(),total_weight);
  myHist->LeptonEta->Fill(anti_muon.Eta(),total_weight);
  myHist->LeptonPt->Fill(muon.Pt(),total_weight);
  myHist->LeptonPt->Fill(anti_muon.Pt(),total_weight);
  myHist->Zrapidity->Fill(Zboson.Rapidity(),total_weight);
  myHist->ZPt->Fill(Zboson.Pt(),total_weight);
  myHist->cos_theta_star->Fill(star,total_weight);

  //leading or subleading lepton eta or lepton pT, truth level and reco level
  //reco level
  if(muon.Eta()>anti_muon.Eta())
  {
   myHist->high_LeptonEta->Fill(muon.Eta(),total_weight);
   myHist->low_LeptonEta->Fill(anti_muon.Eta(),total_weight);
  }
  if(muon.Eta()<=anti_muon.Eta())
  {
   myHist->high_LeptonEta->Fill(anti_muon.Eta(),total_weight);
   myHist->low_LeptonEta->Fill(muon.Eta(),total_weight);
  }
  if(muon.Pt()>anti_muon.Pt())
  {
   myHist->high_LeptonPt->Fill(muon.Pt(),total_weight);
   myHist->low_LeptonPt->Fill(anti_muon.Pt(),total_weight);
  }
  if(muon.Pt()<=anti_muon.Pt())
  {
   myHist->high_LeptonPt->Fill(anti_muon.Pt(),total_weight);
   myHist->low_LeptonPt->Fill(muon.Pt(),total_weight);
  }

  //truth level
  if(true_muon.Eta()>true_anti_muon.Eta())
  {
   myHist->high_LeptonEta_true->Fill(true_muon.Eta(),total_weight);
   myHist->low_LeptonEta_true->Fill(true_anti_muon.Eta(),total_weight);
  }
  if(true_muon.Eta()<=true_anti_muon.Eta())
  {
   myHist->high_LeptonEta_true->Fill(true_anti_muon.Eta(),total_weight);
   myHist->low_LeptonEta_true->Fill(true_muon.Eta(),total_weight);
  }
  if(true_muon.Pt()>true_anti_muon.Pt())
  {
   myHist->high_LeptonPt_true->Fill(true_muon.Pt(),total_weight);
   myHist->low_LeptonPt_true->Fill(true_anti_muon.Pt(),total_weight);
  }
  if(true_muon.Pt()<=true_anti_muon.Pt())
  {
   myHist->high_LeptonPt_true->Fill(true_anti_muon.Pt(),total_weight);
   myHist->low_LeptonPt_true->Fill(true_muon.Pt(),total_weight);
  }

  myHist->ZMass_true->Fill(zdata_mc_ZPartMass,total_weight);
  myHist->LeptonEta_true->Fill(true_muon.Eta(),total_weight);
  myHist->LeptonEta_true->Fill(true_anti_muon.Eta(),total_weight);
  myHist->LeptonPt_true->Fill(true_muon.Pt(),total_weight);
  myHist->LeptonPt_true->Fill(true_anti_muon.Pt(),total_weight);
  myHist->Zrapidity_true->Fill(zdata_mc_ZRapidity,total_weight);
  myHist->ZPt_true->Fill(zdata_mc_ZPt,total_weight);

 }
}//func_Loop

#endif
