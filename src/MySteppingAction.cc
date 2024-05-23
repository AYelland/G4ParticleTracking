#include "MySteppingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

MySteppingAction::MySteppingAction(MyEventAction *eventAction)
{
  // devLog << "MySteppingAction.cc" << std::endl;
  
  fEventAction = eventAction;
  fPreviousVolume = nullptr;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

MySteppingAction::~MySteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void MySteppingAction::UserSteppingAction(const G4Step *step)
{
  fStep = step;

  // Kill Irrelevant Particle Tracks
  G4String fParticleName = fStep -> GetTrack() -> GetDefinition() -> GetParticleName();
  G4String fParticleType = fStep -> GetTrack() -> GetDefinition() -> GetParticleType();

  // // KILL OPTION 1: Kill all particles except protons and helium nuclei
  // if (fParticleName != "proton" && fParticleType != "nucleus") // fParticleName = "alpha" for 4He
  //                                                              // fParticleName = "He3" for 3He
  //                                                              // fParticleType = "baryon" for protons
  // {
  //     G4Track* fTrack = fStep -> GetTrack();
  //     fTrack -> SetTrackStatus(fStopAndKill); // "Kill" the particle track
  // }
  // G4int fAtomicNumber = fStep -> GetTrack() -> GetDefinition() -> GetAtomicNumber();
  // if (fAtomicNumber != 1 && fAtomicNumber != 2)
  // {
  //     G4Track* fTrack = fStep -> GetTrack();
  //     fTrack -> SetTrackStatus(fStopAndKill); // "Kill" the particle track
  // }

  // KILL OPTION 2: Kill all particles except protons and nuclei
  if (fParticleName != "proton" && fParticleName != "neutrons" && fParticleType != "nucleus")
  {
    G4Track* fTrack = fStep -> GetTrack();
    fTrack -> SetTrackStatus(fStopAndKill); // "Kill" the particle track
  }

  // // KILL OPTION 3: Kill all particles except baryons and nuclei
  // if (fParticleType != "baryon" && fParticleType != "nucleus" )
  // {
  //   G4Track* fTrack = fStep -> GetTrack();
  //   fTrack -> SetTrackStatus(fStopAndKill); // "Kill" the particle track
  // }


  // SAVE OPTION 1: Save Particle Data from First Step in New Volume
  fCurrentVolume = fStep -> GetPreStepPoint() -> GetTouchableHandle() -> GetVolume();
  if (fCurrentVolume != fPreviousVolume)
  {
    // devLog << "\t" << fParticleName << " has entered the " << fCurrentVolume -> GetName() << "layer." << std::endl;

    fEventAction -> SaveParticleData(fStep); // save particle data from previous volume
    fPreviousVolume = fCurrentVolume; // update previous volume
  }

  // // SAVE OPTION 2: Save Particle Data at Each Step for Specific Particles (too expensive)
  // fCurrentVolume = fStep -> GetPreStepPoint() -> GetTouchableHandle() -> GetVolume();
  // if (fParticleName == "proton" || fParticleName == "neutrons" || fParticleType == "nucleus")
  // {
  //   // devLog << "\t" << fParticleName << " has taken a step in the " << fCurrentVolume -> GetName() << "layer." << std::endl;
  //   fEventAction -> SaveParticleData(fStep); // save particle data from previous volume
  // }
}
