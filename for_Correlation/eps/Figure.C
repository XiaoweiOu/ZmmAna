#include"/lustre/AtlUser/xwou/plot_include/Figure.h"
int main()
{
 /*Figure *f1 = new Figure("data_ZMass.eps","Di-muon Mass/GeV","Number of Events");
 f1->SetMode("SINGLE");
 f1->SetInputFigure(1,"/lustre/AtlUser/xwou/ZmmAnaV3/Zmm/data_noCali/data_result.root","ZMass","data");
 f1->SetXrange(74,110);
 f1->SetHeaderName("DZero Internal");
 f1->DrawFigure();

 Figure *f2 = new Figure("data_ZPt.eps","Di-muon p_{t}/GeV","Number of Events");
 f2->SetMode("SINGLE");
 f2->SetInputFigure(1,"/lustre/AtlUser/xwou/ZmmAnaV3/Zmm/data_noCali/data_result.root","ZPt","data");
 f2->SetXrange(0,40);
 f2->SetHeaderName("DZero Internal");
 f2->DrawFigure();

 Figure *f3 = new Figure("data_Zrapidity.eps","Di-muon rapidity","Number of Events");
 f3->SetMode("SINGLE"); 
 f3->SetInputFigure(1,"/lustre/AtlUser/xwou/ZmmAnaV3/Zmm/data_noCali/data_result.root","Zrapidity","data");
 f3->SetXrange(-1.8,1.8);
 f3->SetHeaderName("DZero Internal");
 f3->DrawFigure();

 Figure *f4 = new Figure("data_muonPt.eps","muon p_{t}/GeV","Number of Events");
 f4->SetMode("SINGLE"); 
 f4->SetInputFigure(1,"/lustre/AtlUser/xwou/ZmmAnaV3/Zmm/data_noCali/data_result.root","LeptonPt","data");
 f4->SetXrange(15,80);
 f4->SetHeaderName("DZero Internal");
 f4->DrawFigure();

 Figure *f5 = new Figure("data_muonEta.eps","muon #eta","Number of Events");
 f5->SetMode("SINGLE");  
 f5->SetInputFigure(1,"/lustre/AtlUser/xwou/ZmmAnaV3/Zmm/data_noCali/data_result.root","LeptonEta","data");
 f5->SetXrange(-1.8,1.8);
 f5->SetHeaderName("DZero Internal");
 f5->DrawFigure();

 Figure *f14 = new Figure("data_costheta.eps","cos#theta^{*}","Number of Events");
 f14->SetMode("SINGLE");  
 f14->SetInputFigure(1,"/lustre/AtlUser/xwou/ZmmAnaV3/Zmm/data_noCali/data_result.root","cos_theta_star","data");
 f14->SetXrange(-1,1);
 f14->SetHeaderName("DZero Internal");
 f14->DrawFigure();*/

 /*Figure *f6 = new Figure("nocali_ZMass_compare_SN.eps","Di-muon Mass/GeV","Number of Events");
 f6->SetMode("RATIO");
 f6->SetInputFigure(1,"/lustre/AtlUser/xwou/ZmmAnaV3/Zmm/data_noCali/data_result.root","ZMass_SN","data");
 f6->SetInputFigure(2,"/lustre/AtlUser/xwou/ZmmAnaV3/Zmm/MC_noCali.root","ZMass_SN","MC");
 f6->SetXrange(74,110);
 f6->SetRatiorange(0,3);
 f6->SetHeaderName("DZero Internal");
 f6->DrawFigure();

 Figure *f19 = new Figure("nocali_ZMass_compare_SP.eps","Di-muon Mass/GeV","Number of Events");
 f19->SetMode("RATIO");
 f19->SetInputFigure(1,"/lustre/AtlUser/xwou/ZmmAnaV3/Zmm/data_noCali/data_result.root","ZMass_SP","data");
 f19->SetInputFigure(2,"/lustre/AtlUser/xwou/ZmmAnaV3/Zmm/MC_noCali.root","ZMass_SP","MC");
 f19->SetXrange(74,110);
 f19->SetRatiorange(0,3);
 f19->SetHeaderName("DZero Internal");
 f19->DrawFigure();*/

 /*Figure *f16 = new Figure("cali_ZMass_compare_SN.eps","Di-muon Mass/GeV","Number of Events");
 f16->SetMode("CHI");
 f16->SetInputFigure(1,"/lustre/AtlUser/xwou/ZmmAnaV3/Zmm/data_Normal/data_result.root","ZMass_SN","data");
 f16->SetInputFigure(2,"/lustre/AtlUser/xwou/ZmmAnaV3/Zmm/MC_Normal.root","ZMass_SN","MC");
 f16->SetXrange(74,110);
 f16->SetRatiorange(0,7);
 f16->SetHeaderName("DZero Internal");
 f16->DrawFigure();

 Figure *f17 = new Figure("cali_ZMass_compare_SP.eps","Di-muon Mass/GeV","Number of Events");
 f17->SetMode("CHI");
 f17->SetInputFigure(1,"/lustre/AtlUser/xwou/ZmmAnaV3/Zmm/data_Normal/data_result.root","ZMass_SP","data");
 f17->SetInputFigure(2,"/lustre/AtlUser/xwou/ZmmAnaV3/Zmm/MC_Normal.root","ZMass_SP","MC");
 f17->SetXrange(74,110);
 f17->SetRatiorange(0,3);
 f17->SetHeaderName("DZero Internal");
 f17->DrawFigure();*/

/* Figure *f20 = new Figure("ZMass_compare.eps","Di-muon Mass/GeV","Number of Events");
 f20->SetMode("RATIO");
 f20->SetInputFigure(1,"/lustre/AtlUser/xwou/ZmmAnaV3/Zmm/data_Normal/data_result.root","ZMass","data");
 f20->SetInputFigure(2,"/lustre/AtlUser/xwou/ZmmAnaV3/Zmm/MC_EffSystWeight.root","ZMass","MC");
 f20->SetXrange(74,110);
 f20->SetRatiorange(0.92,1.08);
 f20->SetHeaderName("DZero Internal");
 f20->DrawFigure();

 Figure *f7 = new Figure("Zrapidity_compare.eps","Di-muon rapidity","Number of Events");
 f7->SetMode("RATIO"); 
 f7->SetInputFigure(1,"/lustre/AtlUser/xwou/ZmmAnaV3/Zmm/data_Normal/data_result.root","Zrapidity","data");
 f7->SetInputFigure(2,"/lustre/AtlUser/xwou/ZmmAnaV3/Zmm/MC_EffSystWeight.root","Zrapidity","MC");
 f7->SetRatiorange(0.92,1.08);
 f7->SetXrange(-1.8,1.8);
 f7->SetHeaderName("DZero Internal");
 //f7->SetNotNorm();
 f7->MoveLegendPosition(0.2,0.3);
 f7->DrawFigure();

 Figure *f8 = new Figure("ZPt_compare.eps","Di-muon p_{t}/GeV","Number of Events");
 f8->SetMode("RATIO");
 f8->SetInputFigure(1,"/lustre/AtlUser/xwou/ZmmAnaV3/Zmm/data_Normal/data_result.root","ZPt","data");
 f8->SetInputFigure(2,"/lustre/AtlUser/xwou/ZmmAnaV3/Zmm/MC_EffSystWeight.root","ZPt","MC");
 f8->SetRatiorange(0.92,1.08);
 f8->SetXrange(0,40);
 f8->SetHeaderName("DZero Internal");
 //f8->SetNotNorm();
 f8->MoveLegendPosition(0.4,0);
 f8->DrawFigure();*/

 Figure *f9 = new Figure("muonPt_compare.eps","muon p_{t}/GeV","Number of Events");
 f9->SetMode("RATIO");
 f9->SetInputFigure(1,"/lustre/AtlUser/xwou/ZmmAnaV3/Zmm/data_Normal/data_result.root","LeptonPt","data");
 f9->SetInputFigure(2,"/lustre/AtlUser/xwou/ZmmAnaV3/Zmm/MC_EffSystWeight.root","LeptonPt","MC");
 f9->SetRatiorange(0.92,1.08);
 f9->SetXrange(15,80);
 f9->SetHeaderName("DZero Internal");
 //f9->SetNotNorm();
 f9->DrawFigure();

 /*Figure *f10 = new Figure("muonEta_compare.eps","muon #eta","Number of Events");
 f10->SetMode("RATIO");
 f10->SetInputFigure(1,"/lustre/AtlUser/xwou/ZmmAnaV3/Zmm/data_Normal/data_result.root","LeptonEta","data");
 f10->SetInputFigure(2,"/lustre/AtlUser/xwou/ZmmAnaV3/Zmm/MC_EffSystWeight.root","LeptonEta","MC");
 f10->SetRatiorange(0.92,1.08);
 f10->SetXrange(-1.8,1.8);
 f10->SetHeaderName("DZero Internal");
 //f10->SetNotNorm();
 f10->MoveLegendPosition(0.1,0.35);
 f10->DrawFigure();

 Figure *f13 = new Figure("costheta_compare.eps","cos#theta^{*}","Number of Events");
 f13->SetMode("RATIO");
 f13->SetInputFigure(1,"/lustre/AtlUser/xwou/ZmmAnaV3/Zmm/data_Normal/data_result.root","cos_theta_star","data");
 f13->SetInputFigure(2,"/lustre/AtlUser/xwou/ZmmAnaV3/Zmm/MC_EffSystWeight.root","cos_theta_star","MC");
 f13->SetRatiorange(0.92,1.08);
 f13->SetXrange(-1,1);
 f13->SetHeaderName("DZero Internal");
 f13->MoveLegendPosition(-0.01,-0.025);
 f13->DrawFigure();*/

/* Figure *f23 = new Figure("effcorr_Zrapidity.eps","Di-muon rapidity","Number of Events");
 f23->SetMode("RATIO");
 f23->SetInputFigure(1,"/lustre/AtlUser/xwou/ZmmAnaV3/Zmm/MC_Normal.root","Zrapidity","before");
 f23->SetInputFigure(2,"/lustre/AtlUser/xwou/ZmmAnaV3/Zmm/MC_EffSystWeight.root","Zrapidity","after");
 f23->SetRatiorange(0.92,1.08);
 f23->SetXrange(-1.8,1.8);
 f23->SetHeaderName("DZero Internal");
 f23->DrawFigure();

 Figure *f24 = new Figure("effcorr_muonEta.eps","muon #eta","Number of Events");
 f24->SetMode("RATIO");
 f24->SetInputFigure(1,"/lustre/AtlUser/xwou/ZmmAnaV3/Zmm/MC_Normal.root","LeptonEta","before");
 f24->SetInputFigure(2,"/lustre/AtlUser/xwou/ZmmAnaV3/Zmm/MC_EffSystWeight.root","LeptonEta","after");
 f24->SetRatiorange(0.92,1.08);
 f24->SetXrange(-1.8,1.8);
 f24->MoveLegendPosition(0.1,0.35);
 f24->SetHeaderName("DZero Internal");
 f24->DrawFigure();*/

 /*Figure *f25 = new Figure("data_effcorr_Zrapidity.eps","Di-muon rapidity","Number of Events");
 f25->SetMode("RATIO");
 f25->SetInputFigure(1,"/lustre/AtlUser/xwou/ZmmAnaV3/Zmm/data_Normal/data_result.root","Zrapidity","data");
 f25->SetInputFigure(2,"/lustre/AtlUser/xwou/ZmmAnaV3/Zmm/MC_EffSystWeight.root","Zrapidity","MC_corr");
 f25->SetRatiorange(0.92,1.08);
 f25->SetXrange(-1.8,1.8);
 f25->SetHeaderName("DZero Internal");
 f25->DrawFigure();

 Figure *f26 = new Figure("data_effcorr_muonEta.eps","muon #eta","Number of Events");
 f26->SetMode("RATIO");
 f26->SetInputFigure(1,"/lustre/AtlUser/xwou/ZmmAnaV3/Zmm/data_Normal/data_result.root","LeptonEta","data");
 f26->SetInputFigure(2,"/lustre/AtlUser/xwou/ZmmAnaV3/Zmm/MC_EffSystWeight.root","LeptonEta","MC_corr");
 f26->SetRatiorange(0.92,1.08);
 f26->SetXrange(-1.8,1.8);
 f26->MoveLegendPosition(0.1,0.35);
 f26->SetHeaderName("DZero Internal");
 f26->DrawFigure();*/
}
