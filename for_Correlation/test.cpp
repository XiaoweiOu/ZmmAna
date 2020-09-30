void test()
{
 TFile *file = new TFile("MC_result/MC_Normal.root");
 TH1D *Forward_Zrapidity_eta_Pt[9][9][3][3];
 char name[100];

 for(int u=0;u<9;u++)
  for(int v=0;v<9;v++)
   for(int p=0;p<3;p++)
    for(int q=0;q<3;q++)
    {
     sprintf(name,"Zrapidity_eta%d%d_Pt%d%d",u,v,p,q);
     Forward_Zrapidity_eta_Pt[u][v][p][q] = (TH1D *)file->Get(name);
     cout<<name<<"   "<<Forward_Zrapidity_eta_Pt[u][v][p][q]->Integral()<<endl;
    }
}
