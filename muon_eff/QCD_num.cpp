//attention!!!
/*QCD_num_F = QCD_num_B
* use "data_num" to calculate error!!!*/

void QCD_num()
{
 TString s[18]={"ttbar","WW","WZ","Ztaotao_60_130","Ztaotao_130_250",
                "W0lp","W1lp","W2lp","W3lp","W4lp",
                "W2b0lp","W2b1lp","W2b2lp","W2b3lp",
                "W2c0lp","W2c1lp","W2c2lp","W2c3lp"};

 Double_t factor[18] = {8600*7.78*0.3257*0.3257/3906590,8600*12.1/4571840,8600*3.9/4558100,8600*254.0/4604320,8600*1.91/4637040,8600*5885.63/171994000,8600*1673.98/86017300,8600*401.08/23174700,8600*96.74/9004110,8600*22.07/2291070,8600*13.75/4574480,8600*6.33/2327400,8600*2.25/1171900,8600*1.07/653490,8600*35.87/8987640,8600*19.83/4681180,8600*8.03/2318930,8600*3.75/1074560};

 TFile *data_file = new TFile("QCD_num/data_result.root");
 TFile *signalMC_file = new TFile("QCD_num/MC_0_result.root");

 TFile *file[18];
 for(int i=0;i<18;i++)
  file[i]= new TFile("QCD_num/" + s[i] + "_result.root");

 TFile *write_file = new TFile("QCD_num.root","RECREATE");
// TH1D *data_write = (TH1D *)plot_data->Clone("data_num");//data:use to calculate error!(100%)

 TH1D *plot_MC,*plot_data,*plot_signalMC;
 char name[100];
 TH1D *plot_all_ZMass[9][3];
 int count=0;

 for(int i=0;i<9;i++)
  for(int j=0;j<3;j++) 
  {
   sprintf(name,"Id_ZMass_LeptonEta%d_Pt%d",i,j);
   plot_all_ZMass[i][j] = new TH1D(name,name,70,60,130);

   plot_data = (TH1D *)data_file->Get(name);
   plot_signalMC = (TH1D *)signalMC_file->Get(name);
   plot_signalMC->Scale(8600*254/1.08782e+07);
   plot_all_ZMass[i][j]->Add(plot_data);
   plot_all_ZMass[i][j]->Add(plot_signalMC,-1);

   for(int k=0;k<18;k++)
   {
    plot_MC=(TH1D *)file[k]->Get(name);
    plot_all_ZMass[i][j]->Add(plot_MC,-factor[k]);    
   }

   count+=plot_all_ZMass[i][j]->Integral();
  }

 cout<<count<<endl;
 write_file->Write();
}
