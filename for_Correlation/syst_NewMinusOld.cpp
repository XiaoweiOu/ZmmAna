void syst_NewMinusOld()
{
 ifstream f_new("syst_eff_new.txt");
 ifstream f_old("syst_eff.txt");

 double skip,number_new,number_old;

 for(int i=1;i<=8;i++)
 {
  f_new >> number_new;
  f_old >> number_old;
  f_new >> skip;
  f_old >> skip;

  if(i==1)cout<<"+:"<<endl;
  if(i==5)cout<<"-:"<<endl;
  cout << number_new - number_old << endl;
 }
}
