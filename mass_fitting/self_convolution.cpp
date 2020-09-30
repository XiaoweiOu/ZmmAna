void self_convolution()
{
 double par[4];
 par[0] = 0.02;
 par[1] = -2;
 par[2] = 1;

 TFile *file = new TFile("../muon_eff/result/MC_result.root");
 TH1D *h1 = (TH1D *)file->Get("ZMass_LeptonEta1_Pt4");
 //TFile *write_file = new TFile("self_convolution.root","RECREATE");
 TH1D *h1_after = (TH1D *)h1->Clone("ZMass_LeptonEta1_Pt4");

 TFile *file_data = new TFile("../muon_eff/result/data_result.root");
 TH1D *h1_data = (TH1D *)file_data->Get("ZMass_LeptonEta1_Pt4");

 double sum,inum,bin_low,bin_up,mi,di,ProGaus,SignalValue,bin_x;

 for(int j=1;j<=h1->GetNbinsX();j++)
 {
  sum = 0;
  bin_x = h1->GetBinCenter(j);

  for (int ibin = 1; ibin <= (h1->GetNbinsX()); ibin++)
  {
   inum = h1->GetBinContent(ibin);
   bin_low = h1->GetXaxis()->GetBinLowEdge(ibin);
   bin_up = h1->GetXaxis()->GetBinUpEdge(ibin);
   mi = (bin_low + bin_up) / 2;
   di = bin_up - bin_low;
   ProGaus = TMath::Gaus(bin_x - mi, par[1], par[2]);
   sum = sum + ProGaus * di * inum;
  } 

  SignalValue = sum * par[0];
  h1_after->SetBinContent(j,SignalValue);

  //cout<<h1->GetBinContent(j)<<"   "<<h1_after->GetBinContent(j)<<endl;
 }

 //h1->Scale(h1_after->Integral()/h1->Integral());
 //h1->Draw();
 cout<<h1_after->Integral()<<endl;
 h1_after->SetLineColor(2);
 h1_after->SetMarkerColor(2);
 h1_after->Draw();
 //h1_data->Scale(h1_after->Integral()/h1_data->Integral());
 //h1_data->SetLineColor(3);
 //h1_data->SetLineColor(3);
 //h1_data->Draw("SAME");

 //write_file->Write();
}
