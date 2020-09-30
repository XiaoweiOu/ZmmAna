//attention!!!
/*QCD_num_F = QCD_num_B
* use "data_num" to calculate error!!!*/

void QCD_num()
{
 int num=0;//eff1

 TString str;
 if(num==1)str="QCD_num_eff1";
 else if(num==2)str="QCD_num_eff2";
 else if(num==3)str="QCD_num_eff3";
 else str="QCD_num";

 TString s[18]={"EWMC_ttbar","EWMC_WW","EWMC_WZ","EWMC_Ztaotao_60_130","EWMC_Ztaotao_130_250",
                "EWMC_W0lp","EWMC_W1lp","EWMC_W2lp","EWMC_W3lp","EWMC_W4lp",
                "EWMC_W2b0lp","EWMC_W2b1lp","EWMC_W2b2lp","EWMC_W2b3lp",
                "EWMC_W2c0lp","EWMC_W2c1lp","EWMC_W2c2lp","EWMC_W2c3lp"};

 Double_t factor[18] = {8600*7.78*0.3257*0.3257/3906590,8600*12.1/4571840,8600*3.9/4558100,8600*254.0/4604320,8600*1.91/4637040,8600*5885.63/171994000,8600*1673.98/86017300,8600*401.08/23174700,8600*96.74/9004110,8600*22.07/2291070,8600*13.75/4574480,8600*6.33/2327400,8600*2.25/1171900,8600*1.07/653490,8600*35.87/8987640,8600*19.83/4681180,8600*8.03/2318930,8600*3.75/1074560};

 TFile *data_file = new TFile(str+"/data_result.root");
 TFile *signalMC_file = new TFile(str+"/MC_0.root");
 TH1D *plot_data = (TH1D *)data_file->Get("Zrapidity");
 TH1D *plot_signalMC = (TH1D *)signalMC_file->Get("Zrapidity");
 TH1D *plot_data_Mass = (TH1D *)data_file->Get("ZMass");
 TH1D *plot_signalMC_Mass = (TH1D *)signalMC_file->Get("ZMass");
 plot_signalMC->Scale(8600*254/1.08782e+07);
 plot_signalMC_Mass->Scale(8600*254/1.08782e+07);
 
 TFile *write_file = new TFile(str+".root","RECREATE");
 TH1D *plot_write = new TH1D("QCD_num","QCD_num",60,-3,3);//data-signalMC-EWMC
 plot_write->Sumw2();
 TH1D *plot_write_Mass = new TH1D("QCD_num_Mass","QCD_num_Mass",140,60,130);//data-signalMC-EWMC
 plot_write_Mass->Sumw2();
 TH1D *data_write = (TH1D *)plot_data->Clone("data_num");//data:use to calculate error!(100%)

 plot_write->Add(plot_data);
 plot_write->Add(plot_signalMC,-1);
 plot_write_Mass->Add(plot_data_Mass);
 plot_write_Mass->Add(plot_signalMC_Mass,-1);

 TFile *file;
 TH1D *plot_MC,*plot_MC_Mass; 
 for(int j=0;j<18;j++)
 {
  file = new TFile(str+"/"+ s[j]+".root");
  plot_MC=(TH1D *)file->Get("Zrapidity");
  plot_write->Add(plot_MC,-factor[j]);
  plot_MC_Mass=(TH1D *)file->Get("ZMass");
  plot_write_Mass->Add(plot_MC_Mass,-factor[j]);
 }

 for(int i=1;i<=plot_write_Mass->GetNbinsX();i++)
 {
  if(plot_write_Mass->GetBinContent(i)<0)
  {
   plot_write_Mass->SetBinContent(i,0);
   plot_write_Mass->SetBinError(i,0);
  }
 }
 write_file->Write();
}
