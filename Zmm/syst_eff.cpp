void syst_eff()
{
 //pp:three particles are all in positive bin!
 //mm:
 //normal:opposite!
 int num;
 //num=3;
 TString str;
 if(num==1)str="_eff1";
 else if(num==2)str="_eff2";
 else if(num==3)str="_eff3";
 else str="";

 TFile *MC_file = new TFile("MC_result/MC_Normal" + str + ".root");
 TFile *data_file = new TFile("data_Normal/data_result.root");
 TFile *EW_file = new TFile("EW_norm"+str+".root");
 TFile *QCD_file = new TFile("QCD_spectrum"+str+".root");

 TH1D *MC_Both_muon = (TH1D *)MC_file->Get("Both_muon");
 TH1D *MC_Oppo_muon = (TH1D *)MC_file->Get("Oppo_muon");
 TH1D *data_Both_muon = (TH1D *)data_file->Get("Both_muon");
 TH1D *data_Oppo_muon = (TH1D *)data_file->Get("Oppo_muon");
 TH1D *EW_Both_muon = (TH1D *)EW_file->Get("Both_muon");
 TH1D *EW_Oppo_muon = (TH1D *)EW_file->Get("Oppo_muon");
 TH1D *QCD_Both_muon = (TH1D *)QCD_file->Get("Both_muon");
 TH1D *QCD_Oppo_muon = (TH1D *)QCD_file->Get("Oppo_muon");

 double MC[5],MCpp[5],MCmm[5];
 double data[5],datapp[5],datamm[5];
 double EW[5],EWpp[5],EWmm[5];
 double QCD[5],QCDpp[5],QCDmm[5];

 for(int ii=1;ii<=5;ii++)
 {
  MC[ii-1] = MC_Oppo_muon->GetBinContent(ii);
  MCpp[ii-1] = MC_Both_muon->GetBinContent(ii+4);
  MCmm[ii-1] = MC_Both_muon->GetBinContent(6-ii);

  data[ii-1] = data_Oppo_muon->GetBinContent(ii);
  datapp[ii-1] = data_Both_muon->GetBinContent(ii+4);
  datamm[ii-1] = data_Both_muon->GetBinContent(6-ii);

  EW[ii-1] = EW_Oppo_muon->GetBinContent(ii);
  EWpp[ii-1] = EW_Both_muon->GetBinContent(ii+4);
  EWmm[ii-1] = EW_Both_muon->GetBinContent(6-ii);

  QCD[ii-1] = QCD_Oppo_muon->GetBinContent(ii);
  QCDpp[ii-1] = QCD_Both_muon->GetBinContent(ii+4);
  QCDmm[ii-1] = QCD_Both_muon->GetBinContent(6-ii);
 }

 //background subtraction!
 for(int j=0;j<5;j++)
 {
  data[j] = data[j]-EW[j]-QCD[j];
  datapp[j] = datapp[j]-EWpp[j]-QCDpp[j];  
  datamm[j] = datamm[j]-EWmm[j]-QCDmm[j];  
 }

 double effp[5],effm[5];//0:no use!
 double error_effp[5],error_effm[5];

 int i;
 double x,y,error_x,error_y;
 for(i=1;i<=4;i++)
 {
  x = (data[i]/MC[i])/(data[0]/MC[0]);//effp[i]*effm[i]=x
  y = (datapp[i]/MCpp[i])/(datamm[i]/MCmm[i]);//pow(effp[i]/effm[i],2)=y
  error_x = sqrt(pow(MC[0]/MC[i]/data[0],2)*data[i] + pow(data[i]/data[0]/MC[i],2)*MC[0] + pow(data[i]*MC[0]/(data[0]*data[0]*MC[i]),2)*data[0]
               + pow(data[i]*MC[0]/(data[0]*MC[i]*MC[i]),2)*MC[i]);
  error_y = sqrt(pow(MCmm[i]/MCpp[i]/datamm[i],2)*datapp[i] + pow(datapp[i]/datamm[i]/MCpp[i],2)*MCmm[i] + pow(datapp[i]*MCmm[i]/(datamm[i]*datamm[i]*MCpp[i]),2)*datamm[i]
               + pow(datapp[i]*MCmm[i]/(datamm[i]*MCpp[i]*MCpp[i]),2)*MCpp[i]);

  effp[i]=pow(x*x*y,0.25);
  error_effp[i] = sqrt(pow(2*x*y*error_x,2) + pow(x*x*error_y,2));
  effm[i]=pow(x*x/y,0.25);
  error_effm[i] = sqrt(pow(2*x/y*error_x,2) + pow(x*x/y/y*error_y,2));
 }

 ofstream write("syst_eff" + str+ ".txt");
 for(i=1;i<=4;i++)
 write<<fixed<<setprecision(4)<<effp[i]<<"   "<<error_effp[i]<<endl; 
 write<<endl<<endl;
 for(i=1;i<=4;i++)
 write<<effm[i]<<"   "<<error_effm[i]<<endl;
 
 for(i=1;i<=4;i++)
 cout<<fixed<<setprecision(4)<<effp[i]<<",";
 cout<<endl<<endl;
 for(i=1;i<=4;i++)
 cout<<effm[i]<<",";
}
