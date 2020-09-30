void gen_2d_numbers()
{
 TFile *datafile = new TFile("../Inputfiles/Rootfiles/MC_results_trigger.root");

 TH2D *plot;
 double bin1, bin2;
 double err1, err2;

 int counting=0;
 int ZYfix;
 double maxnumber;
 int maxindex;
 int maxeta1,maxeta2;
 ofstream outfile;
  outfile.open("trigger_selection_mc.txt",ios::out);

 maxnumber=0;
 maxeta1=0;
 maxeta2=0;
 char name[50];
 for(int iZY=0;iZY<14;iZY++)
  {
   outfile<<iZY<<endl;
   maxnumber = 0;
   sprintf(name, "%s%d", "LeptonEta_fixZY_",iZY);
   plot = (TH2D *)datafile->Get(name);
   for(int ii=0;ii<14;ii++)
    for(int jj=ii;jj<14;jj++)
     {
      bin1 = plot->GetBinContent(ii+1, jj+1);
      bin2 = plot->GetBinContent(jj+1, ii+1);
      err1 = plot->GetBinError(ii+1, jj+1);
      err2 = plot->GetBinError(jj+1, ii+1);
        if(ii==jj) outfile<<counting<<"  "<<ii<<"  "<<jj<<"  "<<bin1<<"  "<<err1<<endl;
        else outfile<<counting<<"  "<<ii<<"  "<<jj<<"  "<<bin1+bin2<<"  "<<sqrt(err1*err1+err2*err2)<<endl;
        if(ii!=jj && bin1+bin2>maxnumber)
         {
          maxnumber = bin1+bin2;
          maxindex = counting;
          maxeta1 = ii;
          maxeta2 = jj;
         }
        if(ii==jj && bin1>maxnumber)
         {
          maxnumber = bin1;
          maxindex = counting;
          maxeta1 = ii;
          maxeta2 = jj;
         }
        counting = counting + 1;       
     }
    outfile<<999111<<"  "<<maxnumber<<"  "<<maxindex<<"  "<<maxeta1<<"  "<<maxeta2<<endl<<endl;
  }
 outfile<<endl;
 outfile.close();
}
