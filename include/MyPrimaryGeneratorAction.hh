#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "Globals.hh"

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4Geantino.hh"
#include "G4IonTable.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class MyPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    MyPrimaryGeneratorAction();
    ~MyPrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event*);

  private:
    G4ParticleGun *fParticleGun;
};

#endif 