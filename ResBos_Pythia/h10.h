//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Apr 19 19:47:34 2019 by ROOT version 6.14/04
// from TTree h10/h10
// found on file: resbos.root
//////////////////////////////////////////////////////////

#ifndef h10_h
#define h10_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class h10 {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         Px_d1;//d1 is muon+
   Float_t         Py_d1;
   Float_t         Pz_d1;
   Float_t         E_d1;
   Float_t         Px_d2;//d2 is muon-
   Float_t         Py_d2;
   Float_t         Pz_d2;
   Float_t         E_d2;
   Float_t         Px_V;
   Float_t         Py_V;
   Float_t         Pz_V;
   Float_t         E_V;
   Float_t         WT00;

   // List of branches
   TBranch        *b_Px_d1;   //!
   TBranch        *b_Py_d1;   //!
   TBranch        *b_Pz_d1;   //!
   TBranch        *b_E_d1;   //!
   TBranch        *b_Px_d2;   //!
   TBranch        *b_Py_d2;   //!
   TBranch        *b_Pz_d2;   //!
   TBranch        *b_E_d2;   //!
   TBranch        *b_Px_V;   //!
   TBranch        *b_Py_V;   //!
   TBranch        *b_Pz_V;   //!
   TBranch        *b_E_V;   //!
   TBranch        *b_WT00;   //!

   h10(TTree *tree=0);
   virtual ~h10();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef h10_cxx
h10::h10(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("resbos.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("resbos.root");
      }
      f->GetObject("h10",tree);

   }
   Init(tree);
}

h10::~h10()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t h10::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t h10::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void h10::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Px_d1", &Px_d1, &b_Px_d1);
   fChain->SetBranchAddress("Py_d1", &Py_d1, &b_Py_d1);
   fChain->SetBranchAddress("Pz_d1", &Pz_d1, &b_Pz_d1);
   fChain->SetBranchAddress("E_d1", &E_d1, &b_E_d1);
   fChain->SetBranchAddress("Px_d2", &Px_d2, &b_Px_d2);
   fChain->SetBranchAddress("Py_d2", &Py_d2, &b_Py_d2);
   fChain->SetBranchAddress("Pz_d2", &Pz_d2, &b_Pz_d2);
   fChain->SetBranchAddress("E_d2", &E_d2, &b_E_d2);
   fChain->SetBranchAddress("Px_V", &Px_V, &b_Px_V);
   fChain->SetBranchAddress("Py_V", &Py_V, &b_Py_V);
   fChain->SetBranchAddress("Pz_V", &Pz_V, &b_Pz_V);
   fChain->SetBranchAddress("E_V", &E_V, &b_E_V);
   fChain->SetBranchAddress("WT00", &WT00, &b_WT00);
   Notify();
}

Bool_t h10::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void h10::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t h10::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef h10_cxx
