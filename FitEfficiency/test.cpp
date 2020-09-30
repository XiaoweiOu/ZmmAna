void test()
{
 double testarray[2][2][2];
 for(int ii=0;ii<2;ii++)
  for(int jj=0;jj<2;jj++)
   for(int kk=0;kk<2;kk++)
    {
     testarray[ii][jj][kk] = ii*100+jj*10+kk;
     cout<<ii<<"  "<<jj<<"  "<<kk<<"  :"<<testarray[ii][jj][kk]<<endl;
    }
}
