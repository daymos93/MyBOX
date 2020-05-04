
#include "G4RunManager.hh"

#include "../inc/MyBOXEventAction.hh"
#include "MyBOXRun.hh"

MyBOXEventAction::MyBOXEventAction()
: G4UserEventAction(),
	fEdepPerEvt(0.0),
  fChTrackLengthPerEvt(0.0) {}


MyBOXEventAction::~MyBOXEventAction() {}


// Beore each event: reset per-event variables 
void MyBOXEventAction::BeginOfEventAction(const G4Event* /*anEvent*/) {
	fEdepPerEvt           = 0.0;
  fChTrackLengthPerEvt  = 0.0;	
}


// After each event:
// fill the data collected for this event into the Run global (thread local)
// data Run data object (i.e. into YourRun)  
void MyBOXEventAction::EndOfEventAction(const G4Event* /*anEvent*/) {
	// get the current Run object and cast it to MyBOXRun (because for sure this is its type)
	MyBOXRun* currentRun = static_cast< MyBOXRun* > ( G4RunManager::GetRunManager()->GetNonConstCurrentRun() );
    // add the quantities to the (thread local) run global YourRun object 
    currentRun->AddEnergyDepositPerEvent( fEdepPerEvt );
    currentRun->AddChTrackLengthPerEvent( fChTrackLengthPerEvt );
		currentRun->FillEdepHistogram( fEdepPerEvt );
}

