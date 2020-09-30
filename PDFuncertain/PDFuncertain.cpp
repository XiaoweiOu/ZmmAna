void PDFuncertain()
{
 TFile *file0 = new TFile("./result_CT14nnlo/Pythia_CT14_0_result.root");
 TH1D *Zrapidity_F0 = (TH1D *)file0->Get("Zrapidity_F");
 TH1D *Zrapidity_B0 = (TH1D *)file0->Get("Zrapidity_B");

 Zrapidity_F0->Rebin(4);
 Zrapidity_B0->Rebin(4);

 TFile *file;
 TH1D *Zrapidity_F_up,*Zrapidity_F_down;
 TH1D *Zrapidity_B_up,*Zrapidity_B_down;

 TH1D *uncertain_F = new TH1D("uncertain_F","uncertain_F",15,-3,3);
 TH1D *uncertain_B = new TH1D("uncertain_B","uncertain_B",15,-3,3);
 uncertain_F->Sumw2();
 uncertain_B->Sumw2();

 char name[100];
 for(int i=1;i<=28;i++)
 {
  sprintf(name,"./result_CT14nnlo/Pythia_CT14_%d_result.root",i*2-1);
  file = new TFile(name);
  Zrapidity_F_up = (TH1D *)file->Get("Zrapidity_F");
  Zrapidity_B_up = (TH1D *)file->Get("Zrapidity_B");

  sprintf(name,"./result_CT14nnlo/Pythia_CT14_%d_result.root",i*2);
  file = new TFile(name);
  Zrapidity_F_down = (TH1D *)file->Get("Zrapidity_F");
  Zrapidity_B_down = (TH1D *)file->Get("Zrapidity_B");

  Zrapidity_F_up->Rebin(4);
  Zrapidity_B_up->Rebin(4);
  Zrapidity_F_down->Rebin(4);
  Zrapidity_B_down->Rebin(4);

  Zrapidity_F_up->Add(Zrapidity_F_down,-1);
  Zrapidity_B_up->Add(Zrapidity_B_down,-1);
  Zrapidity_F_up->Scale(1./2);
  Zrapidity_B_up->Scale(1./2);
  Zrapidity_F_up->Multiply(Zrapidity_F_up);
  Zrapidity_B_up->Multiply(Zrapidity_B_up);
  uncertain_F->Add(Zrapidity_F_up);
  uncertain_B->Add(Zrapidity_B_up);
 }

 //sqrt
 for(int i=1;i<=15;i++)
 {
  uncertain_F->SetBinContent(i,sqrt(uncertain_F->GetBinContent(i)));
  uncertain_B->SetBinContent(i,sqrt(uncertain_B->GetBinContent(i)));
  Zrapidity_F0->SetBinError(i,uncertain_F->GetBinContent(i));
  Zrapidity_B0->SetBinError(i,uncertain_B->GetBinContent(i));
 }

 TFile *result = new TFile("PDFuncertain.root","RECREATE");
 uncertain_F->Write();
 uncertain_B->Write();

 double inte;
 inte = Zrapidity_F0->Integral() + Zrapidity_B0->Integral();
 Zrapidity_F0->Scale(1./inte);
 Zrapidity_B0->Scale(1./inte);

 Zrapidity_F0->Write();
 Zrapidity_B0->Write();
 result->Close();
}
