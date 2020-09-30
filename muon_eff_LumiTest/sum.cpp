void sum()
{
 TH1D *ZMass[9][3];
 double sum = 0;
 char name[100];
 TFile *file = new TFile("./EW_norm.root");
 for(int i=0;i<9;i++)
  for(int j=0;j<3;j++)
  {
   sprintf(name, "Id_ZMass_LeptonEta%d_Pt%d",i,j);
   ZMass[i][j] = (TH1D *)file->Get(name);
   cout<<ZMass[i][j]->Integral()<<endl;
   sum+=ZMass[i][j]->Integral();
  }
 cout<<sum<<endl;
}
