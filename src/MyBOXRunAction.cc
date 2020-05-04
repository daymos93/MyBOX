
#include "MyBOXRunAction.hh"

#include "MyBOXPrimaryGeneratorAction.hh"
#include "MyBOXRun.hh"
#include "G4Run.hh"
#include "MyBOXRunActionMessenger.hh"

#include "Randomize.hh"
#include "../inc/MyBOXDetectorConstruction.hh"


MyBOXRunAction::MyBOXRunAction(MyBOXDetectorConstruction* det, MyBOXPrimaryGeneratorAction* prim)
:   G4UserRunAction(),
    fMyBOXDetector(det),
    fMyBOXPrimary(prim),
    fMyBOXRun(nullptr),
    fIsEdepHistogramUICmdInvoked(false) { 
  /* histo manager could be created here */ 
  // Create our own UI messenger object that will interact to this Run-Action
  // to set some properties that will be used to update YourRun object (generated 
  // by calling this Run-Action::GenerateRun method) in the BeginOfRunAction method.
//  fMessenger = new YourRunActionMessenger(this);
}

MyBOXRunAction::~MyBOXRunAction() {
  /* histo manager must be deleted here then*/ 
  // delete all dynamically allocated objects here 
//  delete fMessenger;
}


G4Run* MyBOXRunAction::GenerateRun() {
	fMyBOXRun = new MyBOXRun(fMyBOXDetector, fMyBOXPrimary);
	return fMyBOXRun;
}


void MyBOXRunAction::BeginOfRunAction(const G4Run* /*run*/) {
    // Show Rndm status (only for the Master thread)
//    if ( IsMaster() ) G4Random::showEngineStatus();
    //
    // Make sure that the Gun position is correct: the user can change the target
    // thickness between construction of objects and start of the run.  
    // note: primary generator is set in the CTR only for the Worker threads in the 
    //       ActionInitialization (left null for Master in the BuildForMaster())
    if ( fMyBOXPrimary ) {
        fMyBOXPrimary->UpdatePosition();
    }
    // Update the properties of the Energy-deposit histogram member of YourRun, 
    // that is already available at this point: Only if the user invoked the UI 
    // command /yourApp/runAction/edepHistoto set properties of the Edep-histo.
    if ( fIsEdepHistogramUICmdInvoked ) {
      // user defined the properties of the Edep-histo by invoking the UI command 
      fMyBOXRun->SetEdepHisto(fEdepHistFileName, fEdepHistMinEnergy,
                             fEdepHistMaxEnergy, fEdepHistNumBins);
    }                        
    //
    // G4AnalysisManager* analysisManager OpenFile
}


void MyBOXRunAction::EndOfRunAction(const G4Run*) {
    // Print Run summary (only for the Master thread)
    if ( IsMaster() ) { 
    	fMyBOXRun->EndOfRunSummary();
    }
    //
    // Show Rndm status (only for the Master thread)
//    if ( IsMaster() ) G4Random::showEngineStatus();
	//
	// G4AnalysisManager* analysisManager Write and CloseFile
}

