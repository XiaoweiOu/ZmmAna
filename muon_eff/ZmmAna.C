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
 
 //********************main code*********************//
 for(int ii=0;ii<Nentries;ii++)
 {
  fChain->GetEntry(ii);
  Sta_total_number++;

  Double_t total_weight;
  total_weight=1;
  
  int bin_zpt,bin_lumi;
  double test_weight_lumi;

  if(isMC==true || isEWMC==true)
  {

   if(isEWMC==false)
   {
    total_weight=zdata_mc_evtwt;
    //MC should be normalized to data
    total_weight=total_weight/zdata_mc_rwt_mass;

    bin_zpt = Zpt_2D_rwt->FindBin(zdata_mc_ZRapidity,zdata_mc_ZPt);
    total_weight = total_weight*(Zpt_2D_rwt->GetBinContent(bin_zpt))/zdata_mc_rwt_zpt;
   }
   
   bin_lumi = _Lumi_new_file->FindBin(zdata_instlum);
   test_weight_lumi = _Lumi_new_file->GetBinContent(bin_lumi);
   if(fabs(test_weight_lumi)>1e-100)//factor!=0
   total_weight = total_weight*_Lumi_new_file->GetBinContent(bin_lumi);
  }

  int isTag_Id,isTag_Trk,isTag_Iso,isProbe;
  TLorentzVector muon_tag,muon_probe,Zboson;

  for(int itag=0;itag<zdata_muon_number && itag<20;itag++)
  {//tag-muon
   isTag_Id = isTag_Trk = isTag_Iso = 1;

   //loose muon ID
   int nwhitA,nwhitBC,nshitA,nshitBC;
   int getmod;
   getmod = zdata_muon_syst_nhit[itag]%10000;
   nshitBC = (int)((zdata_muon_syst_nhit[itag] - getmod)/10000);
   getmod = zdata_muon_syst_nhit[itag]%1000;
   nshitA = (int)((zdata_muon_syst_nhit[itag] - 10000*nshitBC - getmod)/1000);
   getmod = zdata_muon_syst_nhit[itag]%10;
   nwhitBC = (int)((zdata_muon_syst_nhit[itag] - 10000*nshitBC - 1000*nshitA -getmod)/10);
   nwhitA = getmod; 

   if(zdata_muon_mtc_nseg[itag]==0)
    isTag_Id = isTag_Trk = isTag_Iso = 0;

   if(fabs(zdata_muon_mtc_nseg[itag])==3)
   {
    if(nwhitA<2 || nshitA<1 || nwhitBC<2 || nshitBC<1)
     isTag_Id = isTag_Trk = isTag_Iso = 0;
   }

   if(zdata_muon_mtc_nseg[itag]==2)
   {
    if(nshitBC<1 || nwhitBC<2)
     isTag_Id = isTag_Trk = isTag_Iso = 0;
   }

   if(zdata_muon_mtc_nseg[itag]==1)
   {
    if((nshitA+nshitBC)<1 || nwhitA<2)
     isTag_Id = isTag_Trk = isTag_Iso = 0;
   }

   //scintillator time
   
   if((nshitA + nwhitA)>0 && fabs(zdata_muon_syst_sctimeA[itag])>7)
    isTag_Id = 0;
   if((nshitA + nwhitA)==0 && fabs(zdata_muon_syst_sctimeB[itag])>7)
    isTag_Id = 0;

   //Pt
   if(zdata_muon_pT[itag]<30)
    isTag_Id = isTag_Trk = 0;
   if(zdata_muon_pT[itag]<20)
    isTag_Iso = 0;

   //track match
   if(zdata_muon_trk_match[itag]!=1)
    isTag_Id = isTag_Trk = isTag_Iso = 0;

   if(fabs(zdata_muon_trk_dca[itag])>0.02)
    isTag_Trk = 0;
   if(zdata_muon_trk_nsmt[itag]==0 && fabs(zdata_muon_trk_dca[itag])>0.2)
    isTag_Id = isTag_Iso = 0;
   if(zdata_muon_trk_nsmt[itag]>0 && fabs(zdata_muon_trk_dca[itag])>0.02)
    isTag_Id = isTag_Iso = 0;

   if(zdata_muon_trk_chi2[itag]>4)
    isTag_Id = 0;

   //tight isolation cut
   if(zdata_muon_etTrkCone5[itag]>3.5 || zdata_muon_etHalo[itag]>2.5)
    isTag_Id = isTag_Trk = 0;
   if(zdata_muon_etTrkCone5[itag]>2.5 || zdata_muon_etHalo[itag]>10)
    isTag_Iso = 0;


   //Analysis!!!
/*   if(zdata_muon_pT[itag]<20)
    isTag_Id = isTag_Trk = isTag_Iso = 0;
   
   if(zdata_muon_mark[itag]!=1)
    isTag_Id = isTag_Trk = isTag_Iso = 0;
   if(zdata_muon_mtc_nseg[itag]<1)
    isTag_Id = isTag_Trk = isTag_Iso = 0;
   if(zdata_muon_trk_match[itag]!=1)
    isTag_Id = isTag_Trk = isTag_Iso = 0;
   if(zdata_muon_trk_chi2[itag]>4)
    isTag_Id = isTag_Trk = isTag_Iso = 0;
   if(zdata_muon_trk_nsmt[itag]>0)
   {
    if(fabs(zdata_muon_trk_dca[itag])>0.012)
     isTag_Id = isTag_Trk = isTag_Iso = 0;
   }
   if(zdata_muon_trk_nsmt[itag]==0)
   {
    if(fabs(zdata_muon_trk_dca[itag])>0.2)
     isTag_Id = isTag_Trk = isTag_Iso = 0;
   }

   if( (zdata_muon_etTrkCone5[itag]/zdata_muon_pT[itag])>0.4)//track isolation
    isTag_Id = isTag_Trk = isTag_Iso = 0;
   if( ((zdata_muon_etHalo[itag]-0.005*zdata_instlum)/zdata_muon_pT[itag])>0.4 )//cal isolation
    isTag_Id = isTag_Trk = isTag_Iso = 0;*/

   muon_tag.SetPtEtaPhiM(zdata_muon_pT[itag],zdata_muon_Eta[itag],zdata_muon_Phi[itag],0);

   //find a tag for Id efficiency!
   if(isTag_Id==1)
   {//isTag

    //probe track for Id efficiency
    for(int iprobe=0;iprobe < zdata_single_trk_number&& iprobe<40;iprobe++)
    {//Probe track
    
     isProbe=1;

     if(zdata_single_trk_nsmt[iprobe]==0 && fabs(zdata_single_trk_dca[iprobe])>0.2)isProbe=0;
     if(zdata_single_trk_nsmt[iprobe]>0 && fabs(zdata_single_trk_dca[iprobe])>0.02)isProbe=0;
     if(zdata_single_trk_pt[iprobe]<15)isProbe=0;
  
     if(zdata_single_trk_trkiso[iprobe]>3.5)isProbe=0;
     if(zdata_single_trk_caliso[iprobe]>2.5)isProbe=0;

     /*if(zdata_single_trk_trkiso[iprobe]>1)isProbe=0;
     if(zdata_single_trk_caliso[iprobe]>1)isProbe=0;*/

     if(Is_SS==false)
      if((zdata_single_trk_charge[iprobe]*zdata_muon_trk_charge[itag])>0)isProbe=0;
     if(Is_SS==true)
      if((zdata_single_trk_charge[iprobe]*zdata_muon_trk_charge[itag])<0)isProbe=0;

     if(fabs(zdata_single_trk_z[iprobe]-zdata_muon_trk_z[itag])>2)isProbe=0;
   
     muon_probe.SetPtEtaPhiM(zdata_single_trk_pt[iprobe],zdata_single_trk_eta[iprobe],zdata_single_trk_phi[iprobe],0);
     if(muon_tag.DeltaR(muon_probe)<2)isProbe=0;

     double cos_theta,p1,p2;
     p1=sqrt(muon_tag.Px()*muon_tag.Px() + muon_tag.Py()*muon_tag.Py() + muon_tag.Pz()*muon_tag.Pz());
     p2=sqrt(muon_probe.Px()*muon_probe.Px() + muon_probe.Py()*muon_probe.Py() + muon_probe.Pz()*muon_probe.Pz());
     cos_theta = (muon_tag.Px()*muon_probe.Px() + muon_tag.Py()*muon_probe.Py() + muon_tag.Pz()*muon_probe.Pz())/(p1*p2);
     if(cos_theta<-0.99985)isProbe=0;
     
     Zboson = muon_tag + muon_probe;
     if(Zboson.M()<75 || Zboson.M()>107)isProbe=0;
  
     if(isProbe==1)
     {//isProbe

      //fill denominator plots!
      double star;//cos theta star
      star = 2*(muon_probe.E()*muon_tag.Pz()-muon_tag.E()*muon_probe.Pz())
              /(Zboson.M()*sqrt(Zboson.M()*Zboson.M() + Zboson.Pt()*Zboson.Pt()));
      myHist->Id_ZMass_deno->Fill(Zboson.M(),total_weight);
      myHist->Id_ZPt_deno->Fill(Zboson.Pt(),total_weight);
      myHist->Id_Zrapidity_deno->Fill(Zboson.Rapidity(),total_weight);
      myHist->Id_LeptonPt_deno->Fill(muon_probe.Pt(),total_weight);
      myHist->Id_LeptonEta_deno->Fill(muon_probe.Eta(),total_weight);
      myHist->Id_LeptonEta_Pt_deno->Fill(muon_probe.Eta(),muon_probe.Pt(),total_weight);
      myHist->Id_cos_theta_star_deno->Fill(star,total_weight);

      //mass fitting
      int bin_x,bin_y;
      bin_x = myHist->Id_LeptonEta_Pt_deno->GetXaxis()->FindBin(muon_probe.Eta());
      bin_y = myHist->Id_LeptonEta_Pt_deno->GetYaxis()->FindBin(muon_probe.Pt());
      if(bin_x<=9 && bin_x>=1 && bin_y<=3 && bin_y>=1)
       myHist->Id_ZMass_LeptonEta_Pt[bin_x-1][bin_y-1]->Fill(Zboson.M(),total_weight);

      if(muon_probe.Pt()>=25 && muon_probe.Pt()<=30 && muon_probe.Eta()>=-0.2 && muon_probe.Eta()<=0.2)
       myHist->Id_ZMass_25_30->Fill(Zboson.M(),total_weight);

      int matchmuon_index=zdata_single_trk_matchmuon[iprobe];

      if(zdata_single_trk_matchmuon[iprobe]!=-999 && zdata_muon_mtc_nseg[matchmuon_index]>0

      && zdata_muon_trk_match[iprobe]==1 && zdata_muon_trk_chi2[iprobe]<4
      &&((zdata_muon_trk_nsmt[iprobe]==0 && fabs(zdata_muon_trk_dca[iprobe])<0.2)
      || (zdata_muon_trk_nsmt[iprobe]>0 && fabs(zdata_muon_trk_dca[iprobe])<0.012))

      && (zdata_muon_etTrkCone5[iprobe]/muon_probe.Pt())<0.4//track isolation
      &&((zdata_muon_etHalo[iprobe]-0.005*zdata_instlum)/muon_probe.Pt())<0.4)
      {
       //fill numerator plots!
       myHist->Id_ZMass_nume->Fill(Zboson.M(),total_weight);
       myHist->Id_ZPt_nume->Fill(Zboson.Pt(),total_weight);
       myHist->Id_Zrapidity_nume->Fill(Zboson.Rapidity(),total_weight);
       myHist->Id_LeptonPt_nume->Fill(muon_probe.Pt(),total_weight);
       myHist->Id_LeptonEta_nume->Fill(muon_probe.Eta(),total_weight);
       myHist->Id_LeptonEta_Pt_nume->Fill(muon_probe.Eta(),muon_probe.Pt(),total_weight);
       myHist->Id_cos_theta_star_nume->Fill(star,total_weight);
       //fill numerator plots!
      }
     }//isProbe
    }//Probe track
   }//isTag

   //find a tag for track efficiency
   if(isTag_Trk==1)
   {//isTag

    //Probe muon for track efficiency
    for(int iprobe=0;iprobe<zdata_muon_number && iprobe<20;iprobe++)
    {//Probe muon

     isProbe=1;

     int nwhitA_probe,nwhitBC_probe,nshitA_probe,nshitBC_probe;
     int getmod_probe;
     getmod_probe = zdata_muon_syst_nhit[iprobe]%10000;
     nshitBC_probe = (int) ((zdata_muon_syst_nhit[iprobe] - getmod_probe)/10000);
     getmod_probe = zdata_muon_syst_nhit[iprobe]%1000;
     nshitA_probe = (int)fabs(((zdata_muon_syst_nhit[iprobe] - 10000*nshitBC_probe) - getmod_probe)/1000);
     getmod_probe = zdata_muon_syst_nhit[iprobe]%10;
     nwhitBC_probe = (int) fabs(fabs((zdata_muon_syst_nhit[iprobe] - 10000*nshitBC_probe) - 1000*nshitA_probe) -getmod_probe)/10;
     nwhitA_probe = getmod_probe;

     if(zdata_muon_mtc_nseg[iprobe]==0)isProbe=0;
     if(fabs(zdata_muon_mtc_nseg[iprobe]==3))
     {
      if((nwhitA_probe<2 || nshitA_probe<1 || nwhitBC_probe<2 || nshitBC_probe<1)) 
       isProbe=0;
     }
     if(fabs(zdata_muon_mtc_nseg[iprobe]==2))
     {
      if(nwhitBC_probe<2 || nshitBC_probe<1)
       isProbe=0;
     }
     if(fabs(zdata_muon_mtc_nseg[iprobe]==1))
     {
      if((nshitA_probe+nshitBC_probe)<1 || nwhitA_probe<2)
       isProbe=0;
     }

     if(zdata_muon_etHalo[iprobe]>2.5)isProbe=0;
     if(fabs(zdata_muon_syst_sctimeA[iprobe]-zdata_muon_syst_sctimeA[itag])>6
     || fabs(zdata_muon_syst_sctimeB[iprobe]-zdata_muon_syst_sctimeB[itag])>6) isProbe=false;
     
     if(zdata_muon_pT[iprobe]<15)isProbe=0;
     
     muon_probe.SetPtEtaPhiM(zdata_muon_pT[iprobe],zdata_muon_Eta[iprobe],zdata_muon_Phi[iprobe],0);
     if(muon_tag.DeltaR(muon_probe)<2)isProbe=0;
     
     Zboson = muon_tag + muon_probe;
     if(Zboson.M()<75 || Zboson.M()>107)isProbe=0;

     if(isProbe==1)
     {//isProbe

      //fill denominator plots!
      double star;//cos theta star
      star = 2*(muon_probe.E()*muon_tag.Pz()-muon_tag.E()*muon_probe.Pz())
              /(Zboson.M()*sqrt(Zboson.M()*Zboson.M() + Zboson.Pt()*Zboson.Pt()));

      myHist->Trk_ZMass_deno->Fill(Zboson.M(),total_weight);
      myHist->Trk_ZPt_deno->Fill(Zboson.Pt(),total_weight);
      myHist->Trk_Zrapidity_deno->Fill(Zboson.Rapidity(),total_weight);
      myHist->Trk_LeptonPt_deno->Fill(muon_probe.Pt(),total_weight);
      myHist->Trk_LeptonEta_deno->Fill(muon_probe.Eta(),total_weight);
      myHist->Trk_LeptonEta_Pt_deno->Fill(muon_probe.Eta(),muon_probe.Pt(),total_weight);
      myHist->Trk_cos_theta_star_deno->Fill(star,total_weight);

      if(zdata_muon_trk_match[iprobe]==1 && zdata_muon_trk_chi2[iprobe]<4
      &&((zdata_muon_trk_nsmt[iprobe]==0 && fabs(zdata_muon_trk_dca[iprobe])<0.2)
      || (zdata_muon_trk_nsmt[iprobe]>0 && fabs(zdata_muon_trk_dca[iprobe])<0.012)))
      {//fill numerator plots!
       myHist->Trk_ZMass_nume->Fill(Zboson.M(),total_weight);
       myHist->Trk_ZPt_nume->Fill(Zboson.Pt(),total_weight);
       myHist->Trk_Zrapidity_nume->Fill(Zboson.Rapidity(),total_weight);
       myHist->Trk_LeptonPt_nume->Fill(muon_probe.Pt(),total_weight);
       myHist->Trk_LeptonEta_nume->Fill(muon_probe.Eta(),total_weight);
       myHist->Trk_LeptonEta_Pt_nume->Fill(muon_probe.Eta(),muon_probe.Pt(),total_weight);
       myHist->Trk_cos_theta_star_nume->Fill(star,total_weight);
      }//fill numerator plots!

     }//isProbe

    }//Probe muon
   }//isTag

   //fine a tag for Isolation efficency!
   if(isTag_Iso==1)
   {//isTag
    
    for(int iprobe=0;iprobe<zdata_muon_number && iprobe<20;iprobe++)
    {//Probe muon

     isProbe=1;

     int nwhitA_probe,nwhitBC_probe,nshitA_probe,nshitBC_probe;
     int getmod_probe;
     getmod_probe = zdata_muon_syst_nhit[iprobe]%10000;
     nshitBC_probe = (int) ((zdata_muon_syst_nhit[iprobe] - getmod_probe)/10000);
     getmod_probe = zdata_muon_syst_nhit[iprobe]%1000;
     nshitA_probe = (int)fabs(((zdata_muon_syst_nhit[iprobe] - 10000*nshitBC_probe) - getmod_probe)/1000);
     getmod_probe = zdata_muon_syst_nhit[iprobe]%10;
     nwhitBC_probe = (int) fabs(fabs((zdata_muon_syst_nhit[iprobe] - 10000*nshitBC_probe) - 1000*nshitA_probe) -getmod_probe)/10;
     nwhitA_probe = getmod_probe;

     if(zdata_muon_mtc_nseg[iprobe]==0)isProbe=0;
     if(fabs(zdata_muon_mtc_nseg[iprobe]==3))
     {
      if((nwhitA_probe<2 || nshitA_probe<1 || nwhitBC_probe<2 || nshitBC_probe<1))
       isProbe=0;
     }
     if(fabs(zdata_muon_mtc_nseg[iprobe]==2))
     {
      if(nwhitBC_probe<2 || nshitBC_probe<1)
       isProbe=0;
     }
     if(fabs(zdata_muon_mtc_nseg[iprobe]==1))
     {
      if((nshitA_probe+nshitBC_probe)<1 || nwhitA_probe<2)
       isProbe=0;
     }

     if(zdata_muon_pT[iprobe]<15)isProbe=0;

     muon_probe.SetPtEtaPhiM(zdata_muon_pT[iprobe],zdata_muon_Eta[iprobe],zdata_muon_Phi[iprobe],0);
     if(muon_tag.DeltaR(muon_probe)<2)isProbe=0;
     if(fabs(zdata_muon_trk_z[iprobe]-zdata_muon_trk_z[itag])>2)isProbe=0;

     double cos_theta,p1,p2;
     p1=sqrt(muon_tag.Px()*muon_tag.Px() + muon_tag.Py()*muon_tag.Py() + muon_tag.Pz()*muon_tag.Pz());
     p2=sqrt(muon_probe.Px()*muon_probe.Px() + muon_probe.Py()*muon_probe.Py() + muon_probe.Pz()*muon_probe.Pz());
     cos_theta = (muon_tag.Px()*muon_probe.Px() + muon_tag.Py()*muon_probe.Py() + muon_tag.Pz()*muon_probe.Pz())/(p1*p2);
     if(cos_theta<-0.99985)isProbe=0;

     Zboson = muon_tag + muon_probe;
     if(Zboson.M()<75 || Zboson.M()>107)isProbe=0; 
    
     if(zdata_muon_trk_match[iprobe]!=1)isProbe=0;
     if(zdata_muon_trk_nsmt[iprobe]==0 && fabs(zdata_muon_trk_dca[iprobe])>0.2)isProbe=0;
     if(zdata_muon_trk_nsmt[iprobe]>0 && fabs(zdata_muon_trk_dca[iprobe])>0.02)isProbe=0;

     double star;//cos theta star
     star = 2*(muon_probe.E()*muon_tag.Pz()-muon_tag.E()*muon_probe.Pz())
             /(Zboson.M()*sqrt(Zboson.M()*Zboson.M() + Zboson.Pt()*Zboson.Pt()));
 
     if(isProbe==1)
     {
      myHist->Iso_ZMass_deno->Fill(Zboson.M(),total_weight);
      myHist->Iso_ZPt_deno->Fill(Zboson.Pt(),total_weight);
      myHist->Iso_Zrapidity_deno->Fill(Zboson.Rapidity(),total_weight);
      myHist->Iso_LeptonPt_deno->Fill(muon_probe.Pt(),total_weight);
      myHist->Iso_LeptonEta_deno->Fill(muon_probe.Eta(),total_weight);
      myHist->Iso_LeptonEta_Pt_deno->Fill(muon_probe.Eta(),muon_probe.Pt(),total_weight);
      myHist->Iso_cos_theta_star_deno->Fill(star,total_weight);
 
      if((zdata_muon_etTrkCone5[iprobe]/muon_probe.Pt())<0.4//track isolation
      &&((zdata_muon_etHalo[iprobe]-0.005*zdata_instlum)/muon_probe.Pt())<0.4)//cal isolation
      {
       //fill numerator plots!
       myHist->Iso_ZMass_nume->Fill(Zboson.M(),total_weight);
       myHist->Iso_ZPt_nume->Fill(Zboson.Pt(),total_weight);
       myHist->Iso_Zrapidity_nume->Fill(Zboson.Rapidity(),total_weight);
       myHist->Iso_LeptonPt_nume->Fill(muon_probe.Pt(),total_weight);
       myHist->Iso_LeptonEta_nume->Fill(muon_probe.Eta(),total_weight);
       myHist->Iso_LeptonEta_Pt_nume->Fill(muon_probe.Eta(),muon_probe.Pt(),total_weight);
       myHist->Iso_cos_theta_star_nume->Fill(star,total_weight);
       //fill numerator plots!
      }

     }
    }//Probe muon
   }//isTag

  }//tag-muon
 }
}//func_Loop

#endif
