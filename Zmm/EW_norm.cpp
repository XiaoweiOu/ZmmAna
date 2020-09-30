void EW_norm()
{
 int num;
// num=1;

 Double_t factor[18]={8600*7.78*0.3257*0.3257/3906590,8600*12.1/4571840,8600*3.9/4558100,8600*254.0/4604320,8600*1.91/4637040,8600*5885.63/171994000,8600*1673.98/86017300,8600*401.08/23174700,8600*96.74/9004110,8600*22.07/2291070,8600*13.75/4574480,8600*6.33/2327400,8600*2.25/1171900,8600*1.07/653490,8600*35.87/8987640,8600*19.83/4681180,8600*8.03/2318930,8600*3.75/1074560};

 TFile *file;
 TString s[18]={"ttbar","WW","WZ","Ztaotao_60_130","Ztaotao_130_250",
                "W0lp","W1lp","W2lp","W3lp","W4lp",
                "W2b0lp","W2b1lp","W2b2lp","W2b3lp",
                "W2c0lp","W2c1lp","W2c2lp","W2c3lp"};
 
 TH1D *plot_Zrapidity_F;
 TH1D *plot_Zrapidity_B;
 TH1D *Both_muon;
 TH1D *Oppo_muon;

 TString str;
 if(num==1)str="EW_norm_eff1.root";
 else if(num==2)str="EW_norm_eff2.root";
 else if(num==3)str="EW_norm_eff3.root";
 else str="EW_norm.root";
 TFile *file_write = new TFile(str,"RECREATE");

 TH1D *plot_all_Zrap_F = new TH1D("Zrapidity_F","Zrapidity_F",60,-3,3);
 TH1D *plot_all_Zrap_B = new TH1D("Zrapidity_B","Zrapidity_B",60,-3,3);
 plot_all_Zrap_F->Sumw2();
 plot_all_Zrap_B->Sumw2();

 double array[6]={0,0.2,0.6,1.0,1.4,1.8};
 TH1D *all_Both_muon = new TH1D("Both_muon","Both_muon",9,-1.8,1.8);
 TH1D *all_Oppo_muon = new TH1D("Oppo_muon","Oppo_muon",5,array);
 all_Both_muon->Sumw2();
 all_Oppo_muon->Sumw2();

 if(num==1)str="./EW_bkg_eff1/";
 else if(num==2)str="./EW_bkg_eff2/";
 else if(num==3)str="./EW_bkg_eff3/";
 else str="./EW_bkg/";

 double cal=0;//EWbkg total number
 for(int i=0;i<18;i++)
 {
  file = new TFile(str + s[i] + ".root");
  plot_Zrapidity_F = (TH1D *)file->Get("Zrapidity_F");
  plot_Zrapidity_B = (TH1D *)file->Get("Zrapidity_B");
  
  Both_muon = (TH1D *)file->Get("Both_muon");
  Oppo_muon = (TH1D *)file->Get("Oppo_muon");

  all_Both_muon->Add(Both_muon,factor[i]);
  all_Oppo_muon->Add(Oppo_muon,factor[i]);

  plot_all_Zrap_F->Add(plot_Zrapidity_F,factor[i]);
  plot_all_Zrap_B->Add(plot_Zrapidity_B,factor[i]);
  
  cout<<s[i]<<"   F:"<<factor[i]*plot_Zrapidity_F->Integral()<<"   B:"<<factor[i]*plot_Zrapidity_B->Integral()<<endl;
  cal+=factor[i]*plot_Zrapidity_F->Integral();
  cal+=factor[i]*plot_Zrapidity_B->Integral();
 }

 cout<<"total:"<<cal<<endl;
 file_write->Write();
 file_write->Close();
} 
