#include "MySensitiveDetector_Atmosphere.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

MySensitiveDetector_Atmosphere::MySensitiveDetector_Atmosphere(G4String nameOfDetector) : G4VSensitiveDetector(nameOfDetector)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

MySensitiveDetector_Atmosphere::~MySensitiveDetector_Atmosphere()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4bool MySensitiveDetector_Atmosphere::ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist)
{    
    // G4VPhysicalVolume* fCurrentVolume = aStep -> GetPreStepPoint() -> GetTouchableHandle() -> GetVolume();
    // if (fCurrentVolume -> GetName() == "physAtmosphere_40") {
    //     G4Track* track = aStep -> GetTrack();
    //     track -> SetTrackStatus(fStopAndKill); // "Kill" the Particle upon Contact
    //     devLog << "Particle Killed" << std::endl;
    // }
    return 0;
}