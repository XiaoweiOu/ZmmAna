#include "/lustre/AtlUser/xwou/include/plot/th2d.h"

int main()
{
 th2d plot("Matrix.eps","truth-level di-muon rapidity","reco-level di-muon rapidity");
 plot.SetInputFigure("Data_Final.root","Matrix");
 plot.SetXrange(-1.8,1.8);
 plot.SetYrange(-1.8,1.8);
 plot.DrawTEXT(4);
 return 0;
}
