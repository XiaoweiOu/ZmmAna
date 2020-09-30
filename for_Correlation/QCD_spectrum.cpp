void QCD_spectrum()
{
 TFile *f = new TFile ("../Zmm/QCD_spectrum/data_result.root");
 TH1D *plot_Zrap = (TH1D *)f->Get("Zrapidity");
 Double_t all;
 all = plot_Zrap->Integral();

 TFile *file_num = new TFile("../Zmm/QCD_num.root");
 TH1D *p_QCD_num = (TH1D *)file_num->Get("QCD_num");
 double QCD_num = p_QCD_num->Integral();

 TFile *file_write = new TFile("QCD_spectrum.root","RECREATE");
 TH1D *Both_muon_eta_Pt[9][9][3][3];
 TH1D *Oppo_muon_eta_Pt[9][9][3][3];
 TH1D *Zrapidity_eta_Pt[9][9][3][3];
 Double_t y[6]={0,0.2,0.6,1.0,1.4,1.8};
 char name[100];
 for(int u=0;u<9;u++)
  for(int v=0;v<9;v++)
   for(int p=0;p<3;p++)
    for(int q=0;q<3;q++)
    {
     sprintf(name,"Both_muon_eta%d%d_Pt%d%d",u,v,p,q);
     Both_muon_eta_Pt[u][v][p][q] = new TH1D(name,name,9,-1.8,1.8);
     sprintf(name,"Oppo_muon_eta%d%d_Pt%d%d",u,v,p,q);
     Oppo_muon_eta_Pt[u][v][p][q] = new TH1D(name,name,5,y);
     Both_muon_eta_Pt[u][v][p][q]->Sumw2();
     Oppo_muon_eta_Pt[u][v][p][q]->Sumw2();
     
     sprintf(name,"Zrapidity_eta%d%d_Pt%d%d",u,v,p,q);
     Zrapidity_eta_Pt[u][v][p][q] = new TH1D(name,name,9,-1.8,1.8);
     Zrapidity_eta_Pt[u][v][p][q]->Sumw2();
    }

 TFile *file = new TFile("./QCD_spectrum/data_result.root");
 //help plots! 
 TH1D *plot_Zrapidity_F;
 TH1D *plot_Zrapidity_B;
 TH1D *Both_muon_F,*Both_muon_B;
 TH1D *Oppo_muon_F,*Oppo_muon_B;
 for(int u=0;u<9;u++)
  for(int v=0;v<9;v++)
   for(int p=0;p<3;p++)
    for(int q=0;q<3;q++)
    {
     sprintf(name,"Forward_Zrapidity_eta%d%d_Pt%d%d",u,v,p,q);
     plot_Zrapidity_F = (TH1D *)file->Get(name);
     sprintf(name,"Backward_Zrapidity_eta%d%d_Pt%d%d",u,v,p,q);
     plot_Zrapidity_B = (TH1D *)file->Get(name);

     Zrapidity_eta_Pt[u][v][p][q]->Add(plot_Zrapidity_F,QCD_num/all);
     Zrapidity_eta_Pt[u][v][p][q]->Add(plot_Zrapidity_B,QCD_num/all);

     sprintf(name,"Forward_Both_muon_eta%d%d_Pt%d%d",u,v,p,q);
     Both_muon_F = (TH1D *)file->Get(name);
     sprintf(name,"Backward_Both_muon_eta%d%d_Pt%d%d",u,v,p,q);
     Both_muon_B = (TH1D *)file->Get(name);
     sprintf(name,"Forward_Oppo_muon_eta%d%d_Pt%d%d",u,v,p,q);
     Oppo_muon_F = (TH1D *)file->Get(name);
     sprintf(name,"Backward_Oppo_muon_eta%d%d_Pt%d%d",u,v,p,q);
     Oppo_muon_B = (TH1D *)file->Get(name);
     Both_muon_eta_Pt[u][v][p][q]->Add(Both_muon_F,QCD_num/all);
     Both_muon_eta_Pt[u][v][p][q]->Add(Both_muon_B,QCD_num/all);
     Oppo_muon_eta_Pt[u][v][p][q]->Add(Oppo_muon_F,QCD_num/all);
     Oppo_muon_eta_Pt[u][v][p][q]->Add(Oppo_muon_B,QCD_num/all);
    }

 file_write->Write();
 file_write->Close();
}
