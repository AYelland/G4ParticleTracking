#include "MySensitiveDetector_Earth.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

MySensitiveDetector_Earth::MySensitiveDetector_Earth(G4String nameOfDetector) : G4VSensitiveDetector(nameOfDetector)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

MySensitiveDetector_Earth::~MySensitiveDetector_Earth()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4bool MySensitiveDetector_Earth::ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist)
{
    // Track the Particles when Interacting with the Sensitive Detector
    G4Track* track = aStep -> GetTrack();
    track -> SetTrackStatus(fStopAndKill); // "Kill" the Particle upon Contact
    devLog << "Particle Killed: " << aStep -> GetTrack() -> GetParticleDefinition() -> GetParticleName() << std::endl;

    return 0;
}