
#include "../inc/MyBOXPrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4Event.hh" 
#include "G4ParticleTable.hh"
#include "../inc/MyBOXDetectorConstruction.hh"

MyBOXPrimaryGeneratorAction::MyBOXPrimaryGeneratorAction(MyBOXDetectorConstruction* det)
:   G4VUserPrimaryGeneratorAction(),
    fMyBOXDetector(det),
    fParticleGun(nullptr) {
    // create the particle-gun object
    G4int nParticle = 1;
    fParticleGun    = new G4ParticleGun(nParticle);
    SetDefaultKinematic();
}


MyBOXPrimaryGeneratorAction::~MyBOXPrimaryGeneratorAction() {
    delete fParticleGun;
}


void MyBOXPrimaryGeneratorAction::GeneratePrimaries(G4Event* evt) {
	fParticleGun->GeneratePrimaryVertex(evt);
}


void MyBOXPrimaryGeneratorAction::SetDefaultKinematic() {
    //
    // default primary particle: 30 [MeV] e- perpendicular to the target
	G4ParticleDefinition* part = G4ParticleTable::GetParticleTable()->FindParticle( "e-" );
    fParticleGun->SetParticleDefinition( part );
    fParticleGun->SetParticleMomentumDirection( G4ThreeVector(1., 0., 0.) );
    fParticleGun->SetParticleEnergy( 30.*CLHEP::MeV );
    UpdatePosition();
}


// needs to be invoked for all workers at the begining of the run: user might 
// have changed the target thickness
void MyBOXPrimaryGeneratorAction::UpdatePosition() {
    fParticleGun->SetParticlePosition( 
        G4ThreeVector( fMyBOXDetector->GetGunXPosition(), 0.0, 0.0 ) );
}


const G4String& MyBOXPrimaryGeneratorAction::GetParticleName() const {
	return fParticleGun->GetParticleDefinition()->GetParticleName();
}


G4double MyBOXPrimaryGeneratorAction::GetParticleEnergy() const {
	return fParticleGun->GetParticleEnergy();
}
