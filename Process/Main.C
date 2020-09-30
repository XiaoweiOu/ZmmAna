#include"State.h"

int main()
{
/* for(int i=0;i<3;i++)
 {
  myPro[i] = new Process(i+1);
  myPro[i]->Initial();
  myPro[i]->BkgSubtract();
  myPro[i]->Migration();
  myPro[i]->OverEff();
  myPro[i]->Output();
 }*/

 myPro[0] = new Process();
 myPro[0]->Initial();
 myPro[0]->BkgSubtract();
 myPro[0]->Migration();
 myPro[0]->OverEff();
 myPro[0]->Output();
 return 0;
}
