#ifndef PHYSICS_HH
#define PHYSICS_HH

#include "Globals.hh"

#include "G4VModularPhysicsList.hh"
#include "G4PhysListFactory.hh"

#include "G4OpticalPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4DecayPhysics.hh"
// #include "G4RadioactiveDecayPhysics.hh"
#include "G4HadronPhysicsQGSP_BERT.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class MyPhysicsList : public G4VModularPhysicsList
{
  public:
    MyPhysicsList();
    ~MyPhysicsList();
};

#endif