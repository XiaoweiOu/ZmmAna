void draw_correlation()
{
 ifstream infile;
  infile.open("correlation.txt",ios::in);

 double skip;
 double etabin[15] = {-1.6,-1.2,-1.0,-0.8,-0.6,-0.4,-0.2,0,0.2,0.4,0.6,0.8,1.0,1.2,1.6};

 TH2D *plot = new TH2D("plot","plot",28,0,28,28,0,28);

 double setbin;
 for(int ii=0;ii<28;ii++)
  {
   infile>>skip;
   infile>>skip;

   if(ii<16)
    {
     for(int jj=0;jj<28;jj++)
      {
       if(jj<16) infile>>setbin;
       else setbin=0;
       plot->SetBinContent(ii+1, jj+1, setbin);  
      }
    }
   else
    { 
     for(int jj=0;jj<28;jj++)
      {
       infile>>setbin;
       plot->SetBinContent(ii+1, jj+1, setbin);
      }
    }
  }

 for(int ii=0;ii<28;ii++)
  for(int jj=0;jj<28;jj++)
   {
    if(jj>ii)
     {
      setbin = plot->GetBinContent(jj+1,ii+1);
      plot->SetBinContent(ii+1, jj+1, setbin);
     }
   }

 plot->Draw("COLZ");
}
