void smallplots()
{
  double NData_ZRapidity[9] = {10415, 41057, 65439, 81358, 86362, 80733, 64979, 40505, 10350};
  double NData_LeptonEta[5] = {7286, 12662, 9715, 7731, 1736};
  double NData_Left = 47232;
  double NEWBKG_ZRapidity[9] = {9.64, 56.51, 111.36, 160.95, 176.49, 160.00, 109.20, 47.54, 6.97};
  double NEWBKG_LeptonEta[5] = {14.8404, 24.0173, 16.4333, 9.56841, 0.541317};
  double NEWBKG_Left;
  double NQCDBKG_ZRapidity[9] = {6.07, 24.27, 230.57, 715.99, 952.63, 837.35, 206.30, 36.41, 0};
  double NQCDBKG_LeptonEta[5] = {109.593, 114.09, 82.7589, 37.2638, 3.10341};
  double NQCDBKG_Left;

  double NMCTruth_ZRapidity[9];
  double NMCTruth_LeptonEta[5] = {7286, 12586.37, 9306.71, 7500.79, 1798.22};

  double TheoryRatio[5] = {1.0173, 1.00363, 0.993691, 0.992367, 0.980238};

  TFile *write = new TFile("smallplots.root", "RECREATE");

  double bindiv[6] = {0, 0.2, 0.6, 1.0, 1.4, 1.8};
  TH1D *Data_LeptonEta = new TH1D("Data_LeptonEta","Data_LeptonEta", 5, bindiv);
  Data_LeptonEta->Sumw2();

  TH1D *MC_LeptonEta = new TH1D("MC_LeptonEta","MC_LeptonEta", 5, bindiv);
  MC_LeptonEta->Sumw2();

  TH1D *Ratio_LeptonEta = new TH1D("Ratio_LeptonEta","Ratio_LeptonEta", 5, bindiv);
  Ratio_LeptonEta->Sumw2();

  for(int i=0;i<5;i++)
  { 
      Data_LeptonEta->SetBinContent(i+1, NData_LeptonEta[i]);
      Data_LeptonEta->SetBinError(i+1,0);
      MC_LeptonEta->SetBinContent(i+1, NMCTruth_LeptonEta[i]);
      MC_LeptonEta->SetBinError(i+1,0);
      Ratio_LeptonEta->SetBinContent(i+1, sqrt(NData_LeptonEta[i] / NMCTruth_LeptonEta[i] * NMCTruth_LeptonEta[0] / NData_LeptonEta[0]));
      Ratio_LeptonEta->SetBinError(i+1, 0);
  }

  write->Write();
  write->Close();

}
