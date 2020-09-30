void test()
{
 TRandom3 *MyR = new TRandom3(12345);
 for(int ii=0;ii<1000;ii++)
  {
   cout<<MyR->Rndm()<<endl;
  }
}
