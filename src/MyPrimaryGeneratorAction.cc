#include "MyPrimaryGeneratorAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

MyPrimaryGeneratorAction::MyPrimaryGeneratorAction()
{
    // G4int Z = 2;                // atomic number
    // G4int A = 3;                // mass number
    // G4double charge = 2.*eplus; // charge
    // G4ParticleDefinition *particle = G4IonTable::GetIonTable() -> GetIon(Z, A);
    
    G4ParticleDefinition *particle = G4ParticleTable::GetParticleTable() -> FindParticle("proton");

    // Particle Position & Momentum
    G4ThreeVector pos(0.*m, 0.*m, 549.*km);
    G4ThreeVector mom(0., 0., -1.);
    G4float momMag = 100.*GeV;
    
    // Initialize Gun Properties
    fParticleGun = new G4ParticleGun(1);
    fParticleGun -> SetParticleDefinition(particle);
    fParticleGun -> SetParticlePosition(pos);
    fParticleGun -> SetParticleMomentum(momMag);
    fParticleGun -> SetParticleMomentumDirection(mom);
    // fParticleGun -> SetParticleCharge(charge);

    // Print Statements
    // devLog << "\t Particle Name:            " << particle -> GetParticleName() << std::endl;
    // devLog << "\t Particle Type:            " << particle -> GetParticleType() << std::endl;
    // devLog << "\t Atomic Number:            " << particle -> GetAtomicNumber() << std::endl;
    // devLog << "\t Mass Number:              " << particle -> GetAtomicMass() << std::endl;
    // devLog << "\t Charge:                   " << particle -> GetPDGCharge() << std::endl;
    // devLog << "\t Position (km):            " << pos*(1/km) << std::endl;
    // devLog << "\t Momentum Direction:       " << mom << std::endl;
    // devLog << "\t Momentum Magnitude (GeV): " << momMag*(1/GeV) << std::endl;
    // devLog << std::endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

MyPrimaryGeneratorAction::~MyPrimaryGeneratorAction()
{
    delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void MyPrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent)
{
    fParticleGun -> GeneratePrimaryVertex(anEvent);
}