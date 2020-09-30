void EW_norm()
{
 Double_t factor[18]={8600*7.78*0.3257*0.3257/3906590,8600*12.1/4571840,8600*3.9/4558100,8600*254.0/4604320,8600*1.91/4637040,8600*5885.63/171994000,8600*1673.98/86017300,8600*401.08/23174700,8600*96.74/9004110,8600*22.07/2291070,8600*13.75/4574480,8600*6.33/2327400,8600*2.25/1171900,8600*1.07/653490,8600*35.87/8987640,8600*19.83/4681180,8600*8.03/2318930,8600*3.75/1074560};

 TFile *file[18];
 TString s[18]={"ttbar","WW","WZ","Ztaotao_60_130","Ztaotao_130_250",
                "W0lp","W1lp","W2lp","W3lp","W4lp",
                "W2b0lp","W2b1lp","W2b2lp","W2b3lp",
                "W2c0lp","W2c1lp","W2c2lp","W2c3lp"};

 for(int ilumi=1;ilumi<=3;ilumi++)
 {
 char lumix[50];
 sprintf(lumix,"lumi%d",ilumi);

 int i,j,k;
 for(i=0;i<18;i++)
  file[i]= new TFile("./result_EW/" + s[i] +"_"+ (TString)lumix + "_result.root");

 TFile *file_write = new TFile("EW_norm_"+(TString)lumix+".root","RECREATE");
 TH1D *Id_ZMass_LeptonEta_Pt[9][3][18];
 TH1D *plot_all_ZMass[9][3];

 char name[100];

 double count=0,count_SM=0,count_Wjet=0;
 for(i=0;i<9;i++)
  for(j=0;j<3;j++) 
  {
   sprintf(name,"Id_ZMass_LeptonEta%d_Pt%d",i,j);
   plot_all_ZMass[i][j] = new TH1D(name,name,70,60,130);
   for(k=0;k<18;k++)
   {
    Id_ZMass_LeptonEta_Pt[i][j][k] = (TH1D *)file[k]->Get(name); 
    plot_all_ZMass[i][j]->Add(Id_ZMass_LeptonEta_Pt[i][j][k],factor[k]);

    if(k<=4)count_SM+=Id_ZMass_LeptonEta_Pt[i][j][k]->Integral()*factor[k];
    else count_Wjet+=Id_ZMass_LeptonEta_Pt[i][j][k]->Integral()*factor[k];
   }

   count+=plot_all_ZMass[i][j]->Integral();
  }

 cout<<count<<endl;
 cout<<count_SM<<endl;
 cout<<count_Wjet<<endl;
 file_write->Write();
 }
}
