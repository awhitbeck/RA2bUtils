#ifndef FILLRA2BHISTO
#define FILLRA2BHISTO

#include "AnalysisTools/src/filler.h"
#include <iostream>
#include <string>
#include <cassert>

#include "TLeaf.h"
#include "TString.h"
#include "TLorentzVector.h"

using namespace std;

template <class TreeType> class fillRA2bHisto : public filler<TreeType> {

public : 

  TH1F* histo;
  TreeType* ntuple;
  TString weightbranch;
  bool zinvCR;

  fillRA2bHisto()
    : filler<TreeType>("fillRA2bHisto"){
    ntuple = 0;
    histo = new TH1F("test","test",20,0.,TMath::Pi());
  };
  
  fillRA2bHisto( TreeType* ntuple_ , 
		 TString histotag ,
		 TString weightbranch_ ,
		 bool zinvCR_ = false )
	     : filler<TreeType>("fillRA2bHisto")
	     {

	       ntuple = ntuple_;
	       weightbranch = weightbranch_;
	       zinvCR = zinvCR_;

	       histo = new TH1F("RA2bBins_"+histotag,"RA2bBins_"+histotag,72,0.5,72.5);

	       if( ! zinvCR ){
		 ntuple->fChain->SetBranchStatus("NJets",1);	       
		 ntuple->fChain->SetBranchStatus("BTags",1);
		 ntuple->fChain->SetBranchStatus("MHT",1);
		 ntuple->fChain->SetBranchStatus("HT",1);
		 ntuple->fChain->SetBranchStatus(weightbranch,1);
	       }else{
		 ntuple->fChain->SetBranchStatus("NJetsclean",1);	       
		 ntuple->fChain->SetBranchStatus("BTagsclean",1);
		 ntuple->fChain->SetBranchStatus("MHTclean",1);
		 ntuple->fChain->SetBranchStatus("HTclean",1);
		 ntuple->fChain->SetBranchStatus(weightbranch,1);
	       }
    
	     };

  int HTMHTbin( double HT, double MHT ){
    
    if( MHT < 200 || HT < 500 ) return -999;

    if( MHT > 200 && MHT < 500 ){
      if( HT > 500 && HT < 800 ) return 0;
      if( HT > 800 && HT < 1200 ) return 1; 
      if( HT > 1200 ) return 2;
    }else if( MHT > 500 && MHT < 750 ){ 
      if( HT > 500 && HT < 1200 ) return 3; 
      if( HT > 1200 ) return 4;
    }else if( MHT > 750 ){
      if( HT > 800 ) return 5;
    }
    
    return -999;

  }

  bool process( ) override {

    double HT,MHT;
    int NJets,BTags;

    if( ! zinvCR ){
      HT = ntuple->HT;
      MHT = ntuple->MHT;
      NJets = ntuple->NJets;
      BTags = ntuple->BTags;
    }else{
      HT = ntuple->HT;
      MHT = ntuple->MHT;
      NJets = ntuple->NJets;
      BTags = ntuple->BTags;
    }

    //--------------------- low jet multiplicity -------------------
    if( NJets>=4 && NJets<=6 ){
      if( BTags==0 ){
	histo->Fill( 1 + HTMHTbin( HT , MHT ) );
      }
      if( BTags==1 ){
	histo->Fill( 7 + HTMHTbin( HT , MHT ) );
      }
      if( BTags==2 ){
	histo->Fill( 13 + HTMHTbin( HT , MHT ) );
      }
      if( BTags>=3 ){
	histo->Fill( 19 + HTMHTbin( HT , MHT ) );
      }
    }else if( NJets>=7 && NJets<=8 ){
      //--------------------- med jet multiplicity -------------------
      if( BTags==0 ){
	histo->Fill( 1 + HTMHTbin( HT , MHT ) );
      }
      if( BTags==1 ){
	histo->Fill( 7 + HTMHTbin( HT , MHT ) );
      }
      if( BTags==2 ){
	histo->Fill( 13 + HTMHTbin( HT , MHT ) );
      }
      if( BTags>=3 ){
	histo->Fill( 19 + HTMHTbin( HT , MHT ) );
      }
    }else if( NJets>=9 ){
      //--------------------- high jet multiplicity -------------------
      if( BTags==0 ){
	histo->Fill( 1 + HTMHTbin( HT , MHT ) );
      }
      if( BTags==1 ){
	histo->Fill( 7 + HTMHTbin( HT , MHT ) );
      }
      if( BTags==2 ){
	histo->Fill( 13 + HTMHTbin( HT , MHT ) );
      }
      if( BTags>=3 ){
	histo->Fill( 19 + HTMHTbin( HT , MHT ) );
      }
    }else{
      histo->Fill(0);
    }

    return true;

  };

};

#endif
