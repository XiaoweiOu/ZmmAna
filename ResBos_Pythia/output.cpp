void output()
{
 TFile *f_ResBos = new TFile("ResBos_result.root");
 TFile *f_Pythia = new TFile("Pythia_result.root");
 
 TH1D *ResBos_Both_muon = (TH1D *)f_ResBos->Get("Both_muon");
 TH1D *Pythia_Both_muon = (TH1D *)f_Pythia->Get("Both_muon");

 TH1D *ResBos_Oppo_muon = (TH1D *)f_ResBos->Get("Oppo_muon");
 TH1D *Pythia_Oppo_muon = (TH1D *)f_Pythia->Get("Oppo_muon");
 
 for(int i=1;i<=9;i++)
 cout<<ResBos_Both_muon->GetBinContent(i)<<",";
 cout<<endl;
 for(int i=1;i<=5;i++)
 cout<<ResBos_Oppo_muon->GetBinContent(i)<<",";

 cout<<endl<<endl;

 for(int i=1;i<=9;i++)
 cout<<Pythia_Both_muon->GetBinContent(i)<<",";
 cout<<endl;
 for(int i=1;i<=5;i++)
 cout<<Pythia_Oppo_muon->GetBinContent(i)<<",";
}
