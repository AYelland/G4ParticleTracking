#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "Globals.hh"

// Unit Headers
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

// Volume Headers
#include "G4VUserDetectorConstruction.hh"
#include "G4Box.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"
#include "G4Polyline.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"

// Material Headers
#include "G4NistManager.hh"

// Messenger Headers
#include "G4GenericMessenger.hh"

// Visualization Headers
#include "G4VisManager.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

// User Headers
#include "MySensitiveDetector_Earth.hh"
#include "MySensitiveDetector_Atmosphere.hh"

#include <vector>


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    MyDetectorConstruction();
    ~MyDetectorConstruction();

    G4LogicalVolume *GetScoringVolume() const
      {return fScoringVolume;}

    // Detector Constructions
    virtual G4VPhysicalVolume* Construct();
    void ConstructSubVolumes();

  private:
    
    // Class Private Functions
    virtual void ConstructSDandField();
    void DefineMaterials();
    void USStandardAtmosphereReadin();
    void USStandardAtmosphereMaterials();
    void NitrogenAtmosphereMaterials();
    void PrintStatements();

    ////////////////////////////////////////
    // Physical Constants        
    // const G4double earthRadius = 6378.14*km;

    const G4double aH  = (1.00784/1000)*kg/mole;
    const G4double aHe = (4.002602/1000)*kg/mole;
    const G4double aC  = (12.011/1000)*kg/mole;
    const G4double aN  = (14.0067/1000)*kg/mole;
    const G4double aO  = (15.999/1000)*kg/mole;
    const G4double aNe = (20.1797/1000)*kg/mole;
    const G4double aAr = (39.948/1000)*kg/mole;
    const G4double aKr = (83.798/1000)*kg/mole;
    const G4double aXe = (131.293/1000)*kg/mole;

    // const G4double aN2  = 2.*(aN);
    // const G4double aO2  = 2.*(aO);
    // const G4double aCO2 = (aC) + 2.*(aO);
    // const G4double aCH4 = (aC) + 4.*(aH);
    // const G4double aH2  = 2.*(aH);

    // const G4double aAir = (28.9647/1000)*kg/mole;

    const G4double seaLevelDensityN2 = 0.0011606*g/cm3;
    const G4double seaLevelDensityO2 = 0.0014291*g/cm3;
    const G4double seaLevelDensityCO2 = 0.00187*g/cm3;
    const G4double seaLevelDensityCH4 = 0.000657*g/cm3;
    const G4double seaLevelDensityH2 = 0.00008988*g/cm3;

    const G4double seaLevelDensityAir = 0.001225*g/cm3;

    ////////////////////////////////////////
    // World Volume (Box)
    G4Box *solidWorld;
    const G4double xWorld = 50.*km;
    const G4double yWorld = 50.*km;
    const G4double zWorld = 550.*km;

    G4LogicalVolume *logicWorld;
    G4VPhysicalVolume *physWorld;

    // World Materials
    G4Material *worldMaterial;

    ////////////////////////////////////////
    // Atmosphere Parameters
    G4int nLayers;

    std::vector<G4double> atmosphereLayerWidth, atmosphereLayerMaxAltitude;
    std::vector<G4double> altitude, density, pressure, temperature, molarWeight;

    // Atmosphere Volume (Box)
    G4Box **solidAtmosphere;
    G4double xAtmosphere = xWorld;
    G4double yAtmosphere = yWorld;
    G4double zAtmosphere;

    // Atmospheric Volumes (Spherical Shells)
    // G4Sphere **solidAtmosphere;
    // G4double rAtmosphereInner;
    // G4double rAtmosphereOuter;
    // const G4double thetaAtmosphereStart = 0.;
    // const G4double thetaAtmosphereStop = pi;
    // const G4double phiAtmosphereStart = 0.;
    // const G4double phiAtmosphereStop = pi;

    G4LogicalVolume **logicAtmosphere;
    G4VPhysicalVolume **physAtmosphere;

    // Atmospheric Material
    G4Element *N, *O, *C, *He, *Ar, *Xe, *Ne, *H, *Kr;
    G4Material **N2, **O2, **CO2, **CH4, **H2, **atmosphereMaterial;

    G4double  percentN2, percentO2, percentAr, percentCO2, \
              percentNe, percentHe, percentCH4, percentKr, \
              percentH2, percentXe; // by mass
    
    ////////////////////////////////////////
    // Wall Volume (Box)
    G4Box *solidWall;
    const G4double xWall = xWorld;
    const G4double yWall = yWorld;
    G4double zWall;

    G4LogicalVolume *logicWall;
    G4VPhysicalVolume *physWall;

    G4Material *wallMaterial;

    ////////////////////////////////////////
    // Sensitive Detectors
    MySensitiveDetector_Earth *earthSD;
    MySensitiveDetector_Atmosphere *atmosphereSD;
    
    ////////////////////////////////////////
    // Scoring Variables
    G4LogicalVolume *fScoringVolume;    
};

#endif