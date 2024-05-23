#include "MyEventAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

MyEventAction::MyEventAction(MyRunAction*)
{
    // TFile *file = new TFile(outputFile.c_str(), "READ");

    // // Check if the file is open successfully
    // if (!file || file->IsZombie()) {
    //     std::cerr << "Error: Could not open the file!" << std::endl;
    //     return;
    // }
    // else {
    //     // Access the top-level directory in the file
    //     TDirectory *directory = file->GetDirectory("");

    //     // Check if the directory exists
    //     if (!directory) {
    //         std::cerr << "Error: Directory not found!" << std::endl;
    //         return;
    //     }
    //     else {
    //         // List the contents of the directory using the ls command
    //         directory->ls();

    //         // Close the file
    //         file->Close();
    //     }
    // }

    // gDirectory -> ls("all");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

MyEventAction::~MyEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void MyEventAction::BeginOfEventAction(const G4Event*)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void MyEventAction::EndOfEventAction(const G4Event*)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void MyEventAction::SaveParticleData(const G4Step* step)
{
    // This could be placed in the "BeginOfEventAction" or the 
    // "EndOfEventAction" methods, but it is placed here to
    // demonstrate the use of the "SaveParticleData" method
    // in the "MySteppingAction" class.

    const G4Step *fStep = step;

    // Initialize Analysis Manager
    G4AnalysisManager *fMan = G4AnalysisManager::Instance();

    // Get Event ID & Detector Number
    const G4VTouchable* fTouchable = fStep -> GetPreStepPoint() -> GetTouchable();
    G4int fLayerNumber = fTouchable -> GetVolume() -> GetCopyNo();
    G4int fEventID = G4RunManager::GetRunManager() -> GetCurrentEvent() -> GetEventID();

    // Get Track ID
    G4int fTrackID = fStep -> GetTrack() -> GetTrackID();

    // Get Position Data (from Pre-Step Point)
    G4ThreeVector fPos = fStep -> GetPreStepPoint() -> GetPosition(); // there is also a "GetLocalTime()", relative to particle
    
    G4double fPosX = fPos[0];
    G4double fPosY = fPos[1];
    G4double fPosZ = fPos[2];

    // G4double fPosR = std::sqrt(fPosX*fPosX + fPosY*fPosY + fPosZ*fPosZ);
    // G4double fPosTheta = std::acos(fPosZ/fPosR);
    // G4double fPosPhi = std::atan2(fPosY, fPosX);

    // Get Momentum Data (from Pre-Step Point)
    G4ThreeVector fMom = fStep -> GetPreStepPoint() -> GetMomentum();

    G4double fMomX = fMom[0];
    G4double fMomY = fMom[1];
    G4double fMomZ = fMom[2];

    // G4double fMomR = std::sqrt(fMomX*fMomX + fMomY*fMomY + fMomZ*fMomZ);
    // G4double fMomTheta = std::acos(fMomZ/fMomR);
    // G4double fMomPhi = std::atan2(fMomY, fMomX);

    // Get Particle Property Data (from Track & Pre-Step Point)
    G4ParticleDefinition* fParticle = fStep -> GetTrack() -> GetDefinition();
    
    G4String fParticleName = fParticle -> GetParticleName();
    G4String fParticleType = fParticle -> GetParticleType();
    G4int fAtomicNumber = fParticle -> GetAtomicNumber();
    G4int fMassNumber = fParticle -> GetAtomicMass();
    G4int fCharge = (fParticle -> GetPDGCharge())/eplus;

    G4double fKineticEnergy = fStep -> GetPreStepPoint() -> GetKineticEnergy();
    G4double fEnergyDeposition = fStep -> GetTotalEnergyDeposit();

    // Fill NTuple
    fMan -> FillNtupleIColumn(0, 0, fLayerNumber);
    fMan -> FillNtupleIColumn(0, 1, fEventID);
    fMan -> FillNtupleIColumn(0, 2, fTrackID);
    fMan -> FillNtupleSColumn(0, 3, fParticleName);
    fMan -> FillNtupleSColumn(0, 4, fParticleType);
    fMan -> FillNtupleDColumn(0, 5, fPosX);
    fMan -> FillNtupleDColumn(0, 6, fPosY);
    fMan -> FillNtupleDColumn(0, 7, fPosZ);  
    fMan -> FillNtupleDColumn(0, 8, fMomX);
    fMan -> FillNtupleDColumn(0, 9, fMomY);
    fMan -> FillNtupleDColumn(0, 10, fMomZ);
    fMan -> FillNtupleIColumn(0, 11, fAtomicNumber);
    fMan -> FillNtupleIColumn(0, 12, fMassNumber);
    fMan -> FillNtupleIColumn(0, 13, fCharge);
    fMan -> FillNtupleDColumn(0, 14, fKineticEnergy);
    fMan -> FillNtupleDColumn(0, 15, fEnergyDeposition);
    fMan -> AddNtupleRow(0);

    // Print Statements
    // devLog << "\t Event ID: " << fEventID << std::endl;
    // devLog << "\t \t Layer Number:     " << fLayerNumber << std::endl;
    // devLog << "\t \t Particle Name:    " << fParticleName << std::endl;
    // devLog << "\t \t Atomic Number:    " << fAtomicNumber << std::endl;.
    // devLog << "\t \t Mass Number:      " << fMassNumber << std::endl;.
    // devLog << "\t \t Position (km):    " << fPosR << std::endl;.
    // devLog << "\t \t Kin. Energy (Gev):" << fKineticEnergy << std::endl;
    // devLog << "\t \t Energy Dep (Gev): " << fEnergyDeposition << std::endl;.
    // devLog << std::endl;
}
