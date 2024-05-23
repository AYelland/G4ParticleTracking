#include "MyPhysicsList.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

MyPhysicsList::MyPhysicsList() : G4VModularPhysicsList()
{
    devLog << "MyPhysicsList.cc" << std::endl;
    devLog << "" << std::endl;

    RegisterPhysics(new G4EmStandardPhysics());
    RegisterPhysics(new G4OpticalPhysics());
    RegisterPhysics(new G4DecayPhysics());
    RegisterPhysics(new G4HadronPhysicsQGSP_BERT());
    
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

MyPhysicsList::~MyPhysicsList()
{}