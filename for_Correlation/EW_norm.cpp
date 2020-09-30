void EW_norm()
{
 Double_t factor[18]={8600*7.78*0.3257*0.3257/3906590,8600*12.1/4571840,8600*3.9/4558100,8600*254.0/4604320,8600*1.91/4637040,8600*5885.63/171994000,8600*1673.98/86017300,8600*401.08/23174700,8600*96.74/9004110,8600*22.07/2291070,8600*13.75/4574480,8600*6.33/2327400,8600*2.25/1171900,8600*1.07/653490,8600*35.87/8987640,8600*19.83/4681180,8600*8.03/2318930,8600*3.75/1074560};

 TFile *file;
 TString s[18]={"ttbar","WW","WZ","Ztaotao_60_130","Ztaotao_130_250",
                "W0lp","W1lp","W2lp","W3lp","W4lp",
                "W2b0lp","W2b1lp","W2b2lp","W2b3lp",
                "W2c0lp","W2c1lp","W2c2lp","W2c3lp"};

 //help plots! 
 TH1D *plot_Zrapidity_F;
 TH1D *plot_Zrapidity_B;
 TH1D *Both_muon_F,*Both_muon_B;
 TH1D *Oppo_muon_F,*Oppo_muon_B;

 TFile *file_write = new TFile("EW_norm.root","RECREATE");

 TH1D *Forward_Both_muon_eta_Pt[9][9][3][3];//muon_eta:anti_muon_eta:muon_Pt:anti_muon_Pt
 TH1D *Backward_Both_muon_eta_Pt[9][9][3][3];
 TH1D *Forward_Oppo_muon_eta_Pt[9][9][3][3];
 TH1D *Backward_Oppo_muon_eta_Pt[9][9][3][3];

 TH1D *Forward_Zrapidity_eta_Pt[9][9][3][3];
 TH1D *Backward_Zrapidity_eta_Pt[9][9][3][3];

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
    }
 
 for(int i=0;i<18;i++)
 {
  cout<<"file"<<i+1<<endl;

  file = new TFile("./EW_bkg/" + s[i] + ".root");
  for(int u=0;u<9;u++)
   for(int v=0;v<9;v++)
    for(int p=0;p<3;p++)
     for(int q=0;q<3;q++)
     {
      sprintf(name,"Forward_Zrapidity_eta%d%d_Pt%d%d",u,v,p,q);
      plot_Zrapidity_F = (TH1D *)file->Get(name);
      Forward_Zrapidity_eta_Pt[u][v][p][q]->Add(plot_Zrapidity_F,factor[i]);
      sprintf(name,"Backward_Zrapidity_eta%d%d_Pt%d%d",u,v,p,q);
      plot_Zrapidity_B = (TH1D *)file->Get(name);
      Backward_Zrapidity_eta_Pt[u][v][p][q]->Add(plot_Zrapidity_B,factor[i]);
      
      sprintf(name,"Forward_Both_muon_eta%d%d_Pt%d%d",u,v,p,q);
      Both_muon_F = (TH1D *)file->Get(name);
      sprintf(name,"Backward_Both_muon_eta%d%d_Pt%d%d",u,v,p,q);
      Both_muon_B = (TH1D *)file->Get(name);
      sprintf(name,"Forward_Oppo_muon_eta%d%d_Pt%d%d",u,v,p,q);
      Oppo_muon_F = (TH1D *)file->Get(name);
      sprintf(name,"Backward_Oppo_muon_eta%d%d_Pt%d%d",u,v,p,q);
      Oppo_muon_B = (TH1D *)file->Get(name);     
      Forward_Both_muon_eta_Pt[u][v][p][q]->Add(Both_muon_F,factor[i]);
      Backward_Both_muon_eta_Pt[u][v][p][q]->Add(Both_muon_B,factor[i]);
      Forward_Oppo_muon_eta_Pt[u][v][p][q]->Add(Oppo_muon_F,factor[i]);
      Backward_Oppo_muon_eta_Pt[u][v][p][q]->Add(Oppo_muon_B,factor[i]);
     }
 }

 cout<<"finish reading files!"<<endl;

 file_write->Write();
 file_write->Close();
} 
