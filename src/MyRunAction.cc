#include "MyRunAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

MyRunAction::MyRunAction()
{
    // devLog << "\t Output Directory: " << outputDirectory << std::endl;
    // devLog << "\t Output File: " << outputFile << std::endl;

    // // Initialize Analysis Manager
    G4AnalysisManager* man = G4AnalysisManager::Instance();

    // Create NTuple for Hit Positions
    man -> CreateNtuple("LayerParticles", "LayerParticles");
    man -> CreateNtupleIColumn("fLayerNumber");
    man -> CreateNtupleIColumn("fEventID");
    man -> CreateNtupleIColumn("fTrackID");
    man -> CreateNtupleSColumn("fParticleName");
    man -> CreateNtupleSColumn("fParticleType");
    man -> CreateNtupleDColumn("fPosX");
    man -> CreateNtupleDColumn("fPosY");
    man -> CreateNtupleDColumn("fPosZ");
    man -> CreateNtupleDColumn("fMomX");
    man -> CreateNtupleDColumn("fMomY");
    man -> CreateNtupleDColumn("fMomZ");
    man -> CreateNtupleIColumn("fZ");
    man -> CreateNtupleIColumn("fA");
    man -> CreateNtupleIColumn("fQ");
    man -> CreateNtupleDColumn("fE");
    man -> CreateNtupleDColumn("fEdep");
    man -> FinishNtuple(0);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

MyRunAction::~MyRunAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void MyRunAction::BeginOfRunAction(const G4Run* run)
{
    // Initialize Analysis Manager
    G4AnalysisManager* man = G4AnalysisManager::Instance();

    //Get Run ID
    G4int runID = run -> GetRunID();
    std::stringstream strRunID;
    strRunID << runID;
    
    // #if HE3
    //     G4String subfilename = "helium3";
    // #elif HE4
    //     G4String subfilename = "helium4";
    // #else
    //     G4String subfilename = "output";
    // #endif

    #if MULTITHREADING
        G4String filename  = outputFile+"_MTrun"+strRunID.str();
    #else
        G4String filename  = outputFile+"_STrun"+strRunID.str();
    #endif
    // devLog << "\t Complete Output Root Filename: " << outputDirectory+"/"+filename+".root" << std::endl;
    man -> OpenFile(outputDirectory+"/"+filename+".root");

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void MyRunAction::EndOfRunAction(const G4Run*)
{
    // Save analysis manager
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man -> Write();
    man -> CloseFile();
}
