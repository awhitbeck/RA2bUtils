#ifndef FILLRA2BHISTO
#define FILLRA2BHISTO

#include "filler.h"
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

  fillRA2bHisto()
    : filler<TreeType>("fillRA2bHisto"){
    ntuple = 0;
    histo = new TH1F("test","test",20,0.,TMath::Pi());
  };
  
  fillRA2bHisto( TreeType* ntuple_ , 
		   TString histotag ,
		   TString weightbranch_ )
	     : filler<TreeType>("fillRA2bHisto")
	     {

	       ntuple = ntuple_;
	       weightbranch = weightbranch_;

	       histo = new TH1F("RA2bBins_"+histotag,"RA2bBins_"+histotag,72,0.5,72.5);
	       ntuple->fChain->SetBranchStatus("NJets",1);	       
	       ntuple->fChain->SetBranchStatus("BTags",1);
	       ntuple->fChain->SetBranchStatus("MHT",1);
	       ntuple->fChain->SetBranchStatus("HT",1);
	       ntuple->fChain->SetBranchStatus(weightbranch,1);
	       
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

    //--------------------- low jet multiplicity -------------------
    if( ntuple->NJets>=4 && ntuple->NJets<=6 ){
      if( ntuple->BTags==0 ){
	histo->Fill( 1 + HTMHTbin( ntuple->HT , ntuple->MHT ) );
      }
      if( ntuple->BTags==1 ){
	histo->Fill( 7 + HTMHTbin( ntuple->HT , ntuple->MHT ) );
      }
      if( ntuple->BTags==2 ){
	histo->Fill( 13 + HTMHTbin( ntuple->HT , ntuple->MHT ) );
      }
      if( ntuple->BTags>=3 ){
	histo->Fill( 19 + HTMHTbin( ntuple->HT , ntuple->MHT ) );
      }
    }else if( ntuple->NJets>=7 && ntuple->NJets<=8 ){
      //--------------------- med jet multiplicity -------------------
      if( ntuple->BTags==0 ){
	histo->Fill( 1 + HTMHTbin( ntuple->HT , ntuple->MHT ) );
      }
      if( ntuple->BTags==1 ){
	histo->Fill( 7 + HTMHTbin( ntuple->HT , ntuple->MHT ) );
      }
      if( ntuple->BTags==2 ){
	histo->Fill( 13 + HTMHTbin( ntuple->HT , ntuple->MHT ) );
      }
      if( ntuple->BTags>=3 ){
	histo->Fill( 19 + HTMHTbin( ntuple->HT , ntuple->MHT ) );
      }
    }else if( ntuple->NJets>=9 ){
      //--------------------- high jet multiplicity -------------------
      if( ntuple->BTags==0 ){
	histo->Fill( 1 + HTMHTbin( ntuple->HT , ntuple->MHT ) );
      }
      if( ntuple->BTags==1 ){
	histo->Fill( 7 + HTMHTbin( ntuple->HT , ntuple->MHT ) );
      }
      if( ntuple->BTags==2 ){
	histo->Fill( 13 + HTMHTbin( ntuple->HT , ntuple->MHT ) );
      }
      if( ntuple->BTags>=3 ){
	histo->Fill( 19 + HTMHTbin( ntuple->HT , ntuple->MHT ) );
      }
    }else{
      histo->Fill(0);
    }

    return true;

  };

};

#endif
