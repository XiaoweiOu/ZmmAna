void QCD_spectrum()
{
 int num;
// num=3;//eff1
 
 TString str;
 if(num==1)str="_eff1";
 else if(num==2)str="_eff2";
 else if(num==3)str="_eff3";
 else str="";

 TFile *file_write = new TFile("QCD_spectrum"+str+".root","RECREATE");
 TH1D *write_Zrap = new TH1D("Zrapidity","Zrapidity",60,-3,3);
 TH1D *write_Zrap_F = new TH1D("Zrapidity_F","Zrapidity_F",60,-3,3);
 TH1D *write_Zrap_B = new TH1D("Zrapidity_B","Zrapidity_B",60,-3,3);
 write_Zrap->Sumw2();
 write_Zrap_F->Sumw2();
 write_Zrap_B->Sumw2();
 double array[6]={0,0.2,0.6,1.0,1.4,1.8};
 TH1D *write_Both_muon = new TH1D("Both_muon","Both_muon",9,-1.8,1.8);
 TH1D *write_Oppo_muon = new TH1D("Oppo_muon","Oppo_muon",5,array);
 write_Both_muon->Sumw2();
 write_Oppo_muon->Sumw2();
 
 TFile *f = new TFile ("./QCD_spectrum/data_result.root");
 TH1D *plot_Zrap = (TH1D *)f->Get("Zrapidity");
 TH1D *plot_Zrap_F = (TH1D *)f->Get("Zrapidity_F");
 TH1D *plot_Zrap_B = (TH1D *)f->Get("Zrapidity_B");
 TH1D *Both_muon = (TH1D *)f->Get("Both_muon");
 TH1D *Oppo_muon = (TH1D *)f->Get("Oppo_muon");
 
 Double_t all,all_F,all_B;
 all = plot_Zrap->Integral();
 all_F = plot_Zrap_F->Integral();
 all_B = plot_Zrap_B->Integral();

 TFile *file_num = new TFile("QCD_num"+str+".root");
 TH1D *p_QCD_num = (TH1D *)file_num->Get("QCD_num");
 TH1D *data_num = (TH1D *)file_num->Get("data_num");
 double QCD_num = p_QCD_num->Integral();
 double error_num = data_num->Integral();//data:largest number as error!
 double QCD_num_F,QCD_num_B,error_num_F,error_num_B;
 QCD_num_F = QCD_num_B = QCD_num/2;
 error_num_F = error_num_B = error_num/2;

 write_Both_muon->Add(Both_muon,QCD_num/all);
 write_Oppo_muon->Add(Oppo_muon,QCD_num/all);
 write_Zrap->Add(plot_Zrap,QCD_num/all);
 write_Zrap_F->Add(plot_Zrap_F,QCD_num_F/all_F);
 write_Zrap_B->Add(plot_Zrap_B,QCD_num_B/all_B);

 for(int i=0;i<60;i++)
 {
  Double_t content;
  content = write_Zrap->GetBinContent(i);
  if(content < 2.5)//sometimes you cannot select multijet event in the boundary!
  {
   write_Zrap->SetBinContent(i,2.5);
   write_Zrap->SetBinError(i,sqrt(2.5));
  }

  content = write_Zrap_F->GetBinContent(i);
  if(content < 1.25)//sometimes you cannot select multijet event in the boundary!
  {
   write_Zrap_F->SetBinContent(i,1.25);
   write_Zrap_F->SetBinError(i,sqrt(1.25));
  }

  content = write_Zrap_B->GetBinContent(i);
  if(content < 1.25)//sometimes you cannot select multijet event in the boundary!
  {
   write_Zrap_B->SetBinContent(i,1.25);
   write_Zrap_B->SetBinError(i,sqrt(1.25));
  }
 }

 file_write->Write();
 file_write->Close();
}
