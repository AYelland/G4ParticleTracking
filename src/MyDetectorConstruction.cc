#include "MyDetectorConstruction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

MyDetectorConstruction::MyDetectorConstruction()
{
    devLog << "MyDetectorConstruction.cc" << std::endl;
    devLog << "" << std::endl;

    DefineMaterials();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

MyDetectorConstruction::~MyDetectorConstruction()
{
    // Delete all the Materials
    // #if USATMOSPHERE

    //     delete H;
    //     delete He;
    //     delete C;
    //     delete N;
    //     delete O;
    //     delete Ne;
    //     delete Ar;
    //     delete Kr;
    //     delete Xe;
    //     for (int i = 0; i < nLayers; i++) {
    //         delete N2[i];
    //         delete O2[i];
    //         delete CO2[i];
    //         delete CH4[i];
    //         delete H2[i];
    //         delete atmosphereMaterial[i];
    //     }
    //     delete[] N2;
    //     delete[] O2;
    //     delete[] CO2;
    //     delete[] CH4;
    //     delete[] H2;

    // #elif N2ATMOSPHERE

        // delete N;
        // for (int i = 0; i < nLayers; i++) {
        //     delete N2[i];
        //     delete atmosphereMaterial[i];
        // }
        // delete[] N2;

    // #endif

    // delete[] atmosphereMaterial;
    // delete wallMaterial;
    // delete worldMaterial;

    // Delete all the Sensitive Detectors
    // delete earthSD;
    // delete atmosphereSD;

    // Delete all the Volumes
    // for (int i = 0; i < nLayers; i++) {
    //     delete solidAtmosphere[i];
    //     delete logicAtmosphere[i];
    //     delete physAtmosphere[i];
    // }
    // delete[] solidAtmosphere;
    // delete[] logicAtmosphere;
    // delete[] physAtmosphere;

    // delete solidWall;
    // delete logicWall;
    // delete physWall;

    // delete solidWorld;
    // delete logicWorld;
    // delete physWorld;

    // Close the file stream if it's open
    // if (constructionDetails.is_open()) {
    //     constructionDetails.close();
    // }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void MyDetectorConstruction::DefineMaterials()
{
    G4NistManager* nist = G4NistManager::Instance();

    // World Material (w/ Properties)
    worldMaterial = nist -> FindOrBuildMaterial("G4_Galactic");

    // Wall Material (w/ Properties)
    wallMaterial = nist -> FindOrBuildMaterial("G4_Galactic"); 

    // Atmosphere Material (w/ Properties)
    USStandardAtmosphereReadin();
    #if USATMOSPHERE
        USStandardAtmosphereMaterials();
    #elif N2ATMOSPHERE
        NitrogenAtmosphereMaterials();
    #endif
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void MyDetectorConstruction::USStandardAtmosphereReadin()
{
    // Altitude, Density, Pressure, Temperature, Molar Weight (tab-deliminated)
    std::ifstream file("USStandardAtmosphere_1km.dat");
    if (!file.is_open()) {
        std::cerr << "Could not open the file." << std::endl;
    }

    std::string line;
    std::getline(file, line); // Skip the first line
    while (std::getline(file, line)) {
        size_t pos = 0;
        std::string delimiter = "\t"; // tab-delimited

        for (int i = 0; i < 4; ++i) {
            pos = line.find(delimiter);
            std::string token = line.substr(0, pos);
            G4double value = std::stod(token);
            switch (i) {
                case 0:
                    altitude.push_back(value*km);
                    break;
                case 1:
                    density.push_back(value*kg/m3);
                    break;
                case 2:
                    pressure.push_back(value*pascal);
                    break;
                case 3:
                    temperature.push_back(value*kelvin);
                    break;
                default:
                    break;
            }
            line.erase(0, pos + delimiter.length());
        }
        G4double lastValue = std::stod(line);
        molarWeight.push_back(lastValue*kg/mole);
    }

    // // Print the data to verify it was read correctly
    // for (size_t i = 0; i < altitude.size(); ++i) {
    //     std::cout << altitude[i] << "\t" << density[i] << "\t" << pressure[i] << "\t" << temperature[i] << "\t" << molarWeight[i] << std::endl;
    // }
    file.close();

    // Set Resolution of Atmosphere
    nLayers = altitude.size();

    for (G4int i = 0; i < nLayers-1; i++) {
    atmosphereLayerWidth.push_back(altitude[i+1]-altitude[i]);
    if (i == 0) {
        atmosphereLayerMaxAltitude.push_back(atmosphereLayerWidth[i]);
    } else {
        atmosphereLayerMaxAltitude.push_back(atmosphereLayerMaxAltitude[i-1] + atmosphereLayerWidth[i]);
    }
    }
    atmosphereLayerMaxAltitude.push_back(atmosphereLayerMaxAltitude[nLayers-2] + atmosphereLayerWidth[nLayers-2]);
    altitude.push_back(atmosphereLayerMaxAltitude[nLayers-1]);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void MyDetectorConstruction::USStandardAtmosphereMaterials()
{
  // Percentage Composition (by volume)
  // G4double volPercentN2  = 78.084*perCent;
  // G4double volPercentO2  = 20.9476*perCent;
  // G4double volPercentAr  = 0.934*perCent;
  // G4double volPercentCO2 = 0.0314*perCent;
  // G4double volPercentNe  = 0.001818*perCent;
  // G4double volPercentHe  = 0.000524*perCent;
  // G4double volPercentCH4 = 0.0002*perCent;
  // G4double volPercentKr  = 0.000114*perCent;
  // G4double volPercentH2  = 0.00005*perCent;
  // G4double volPercentXe  = 0.0000087*perCent; 

  // Percentage Composition (by mass)
  percentN2  = 75.511*perCent;
  percentO2  = 23.14*perCent;
  percentAr  = 1.29*perCent;
  percentCO2 = 0.063*perCent;
  percentNe  = 0.0013*perCent;
  percentHe  = 0.000074*perCent;
  percentCH4 = 0.0001*perCent;
  percentKr  = 0.00029*perCent;
  percentH2  = 0.000003*perCent;
  percentXe  = 0.00004*perCent; 
  
  // Elements & Molecules
  H  = new G4Element("Hydrogen", "H",   1, aH);
  He = new G4Element("Helium"  , "He",  2, aHe);
  C  = new G4Element("Carbon"  , "C",   6, aC);
  N  = new G4Element("Nitrogen", "N",   7, aN);
  O  = new G4Element("Oxygen"  , "O",   8, aO);
  Ne = new G4Element("Neon"    , "Ne", 10, aNe);
  Ar = new G4Element("Argon"   , "Ar", 18, aAr);
  Kr = new G4Element("Krypton" , "Kr", 36, aKr);
  Xe = new G4Element("Xenon"   , "Xe", 54, aXe);

  N2  = new G4Material*[nLayers];
  O2  = new G4Material*[nLayers];
  CO2 = new G4Material*[nLayers];
  CH4 = new G4Material*[nLayers];
  H2  = new G4Material*[nLayers];

  // Atmosphere Material
  atmosphereMaterial = new G4Material*[nLayers];

  for(G4int i = 0 ; i < nLayers ; i++)
  {
    std::stringstream stri;
    stri << std::setfill('0') << std::setw(3) << i;

    G4double densityN2 = density[i]*(seaLevelDensityN2/seaLevelDensityAir);
    N2[i]  = new G4Material("N2_"+stri.str(), densityN2, 1, kStateGas, temperature[i], pressure[i]);
    N2[i] -> AddElement(N, 2);

    G4double densityO2 = density[i]*(seaLevelDensityO2/seaLevelDensityAir);
    O2[i]  = new G4Material("O2_"+stri.str(), densityO2, 1, kStateGas, temperature[i], pressure[i]);
    O2[i] -> AddElement(O, 2);

    G4double densityCO2 = density[i]*(seaLevelDensityCO2/seaLevelDensityAir);
    CO2[i] = new G4Material("CO2_"+stri.str(), densityCO2, 2, kStateGas, temperature[i], pressure[i]);
    CO2[i] -> AddElement(C, 1);
    CO2[i] -> AddElement(O, 2);

    G4double densityCH4 = density[i]*(seaLevelDensityCH4/seaLevelDensityAir);
    CH4[i] = new G4Material("CH4_"+stri.str(), densityCH4, 2, kStateGas, temperature[i], pressure[i]);
    CH4[i] -> AddElement(C, 1);
    CH4[i] -> AddElement(H, 4);

    G4double densityH2 = density[i]*(seaLevelDensityH2/seaLevelDensityAir);
    H2[i]  = new G4Material("H2_"+stri.str(), densityH2, 1, kStateGas, temperature[i], pressure[i]);
    H2[i] -> AddElement(H, 2);

    atmosphereMaterial[i] = new G4Material("G4_AIR_"+stri.str(), density[i], 10, kStateGas, temperature[i], pressure[i]);
    atmosphereMaterial[i] -> AddMaterial(N2[i],  percentN2);
    atmosphereMaterial[i] -> AddMaterial(O2[i],  percentO2);
    atmosphereMaterial[i] -> AddElement (Ar,     percentAr);
    atmosphereMaterial[i] -> AddMaterial(CO2[i], percentCO2);
    atmosphereMaterial[i] -> AddElement (Ne,     percentNe);
    atmosphereMaterial[i] -> AddElement (He,     percentHe);
    atmosphereMaterial[i] -> AddMaterial(CH4[i], percentCH4);
    atmosphereMaterial[i] -> AddElement (Kr,     percentKr);
    atmosphereMaterial[i] -> AddMaterial(H2[i],  percentH2);
    atmosphereMaterial[i] -> AddElement (Xe,     percentXe);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void MyDetectorConstruction::NitrogenAtmosphereMaterials()
{
  // Percentage Composition (by volume)
  // G4double volPercentN2  = 100.*perCent;

  // Percentage Composition (by mass)
  percentN2  = 100.*perCent;
  
  // Elements & Molecules
  N  = new G4Element("Nitrogen", "N", 7, aN);
  N2  = new G4Material*[nLayers];

  // Atmosphere Material
  atmosphereMaterial = new G4Material*[nLayers];

  for(G4int i = 0 ; i < nLayers ; i++)
  {
    std::stringstream stri;
    stri << i;

    N2[i]  = new G4Material("N2_"+stri.str(), density[i], 1, kStateGas, temperature[i], pressure[i]);
    N2[i] -> AddElement(N, 2);

    atmosphereMaterial[i] = new G4Material("G4_AIR_"+stri.str(), density[i], 1, kStateGas, temperature[i], pressure[i]);
    atmosphereMaterial[i] -> AddMaterial(N2[i],  percentN2);
    // atmosphereMaterial[i] = worldMaterial;

  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void MyDetectorConstruction::ConstructSubVolumes()
{
  // Atmosphere Volumes
  solidAtmosphere = new G4Box*[nLayers];
  logicAtmosphere = new G4LogicalVolume*[nLayers];
  physAtmosphere = new G4VPhysicalVolume*[nLayers];

  zAtmosphere = atmosphereLayerWidth[0]/2;  

  devLog << "xAtmosphere: " << xAtmosphere << std::endl;
  devLog << "yAtmosphere: " << yAtmosphere << std::endl;
  devLog << "zAtmosphere: " << zAtmosphere << std::endl;
  devLog << "nLayers: " << nLayers << std::endl;

  for(G4int i = 0; i < nLayers; i++)
  {     
    // Create Volumes
    // devLog << "Center of Atmospheric Layer: " << i << "  " << (- (zAtmosphere * nLayers) + (2*i + 1)*zAtmosphere) << std::endl;
    
    solidAtmosphere[i] = new G4Box("solidAtmosphere_" + std::to_string(i), xAtmosphere, yAtmosphere, zAtmosphere);
    logicAtmosphere[i] = new G4LogicalVolume(solidAtmosphere[i], atmosphereMaterial[i], "logicAtmosphere_" + std::to_string(i));
    physAtmosphere[i] = new G4PVPlacement(0, G4ThreeVector(0., 0., - (zAtmosphere * nLayers) + (2*i + 1)*zAtmosphere), \
        logicAtmosphere[i], "physAtmosphere_" + std::to_string(i), logicWorld, false, i, true);
  };

  devLog << std::endl;
  
  // fScoringVolume = logicAtmosphere[i];

  // G4int i = 0;
  // solidAtmosphere[i] = new G4Box("solidAtmosphere", xAtmosphere, yAtmosphere, zAtmosphere);
  // logicAtmosphere[i] = new G4LogicalVolume(solidAtmosphere[i], atmosphereMaterial[i], "logicAtmosphere");
  // physAtmosphere[i] = new G4PVPlacement(0, \
  //   G4ThreeVector(0., 0., - (zAtmosphere * nLayers) + (2*i + 1)*zAtmosphere), \
  //   logicAtmosphere[i], "physAtmosphere", logicWorld, false, i, true);

  // Stopping Wall Volume
  zWall = 0.5*m;
  solidWall = new G4Box("solidWall", xWall, yWall, zWall);
  logicWall = new G4LogicalVolume(solidWall, wallMaterial, "logicWall");
  G4ThreeVector posWall(0., 0., - (zAtmosphere * nLayers) + (2*0 + 1)*zAtmosphere - (zAtmosphere + zWall));
  physWall = new G4PVPlacement(0, posWall, logicWall, "physWall", logicWorld, false, 0, true);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4VPhysicalVolume* MyDetectorConstruction::Construct()
{
    //Creating the World Volume
    solidWorld = new G4Box("solidWorld", xWorld, yWorld, zWorld); 
    logicWorld = new G4LogicalVolume(solidWorld, worldMaterial, "logicWorld");
    physWorld = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicWorld, "physWorld", 0, false, 0, true);    

    ConstructSubVolumes();
    PrintStatements();

    return physWorld;
    }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void MyDetectorConstruction::ConstructSDandField()
{
  devLog << "MyDetectorConstruction::ConstructSDandField()" << std::endl;

  earthSD = new MySensitiveDetector_Earth("earthSD");
  logicWall -> SetSensitiveDetector(earthSD);
  // logicEarth -> SetSensitiveDetector(earthSD);
  
  atmosphereSD = new MySensitiveDetector_Atmosphere("atmosphereSD");
  for(G4int i = 0; i < nLayers; i++)
    {logicAtmosphere[i] -> SetSensitiveDetector(atmosphereSD);};
  // logicAtmosphere[0] -> SetSensitiveDetector(atmosphereSD);

  // // Magnetic Field
  // G4MagneticField *dipoleMagneticField = new MyMagneticField();

  // // Magnetic Field Manager
  // G4FieldManager *globalFieldManager = G4TransportationManager::GetTransportationManager() -> GetFieldManager();
  // if (globalFieldManager) {
  //   globalFieldManager -> SetDetectorField(dipoleMagneticField);
  //   globalFieldManager -> CreateChordFinder(dipoleMagneticField);
  // }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void MyDetectorConstruction::PrintStatements()
{
  std::ofstream constructionDetails;
  #if HTCONDOR
    constructionDetails.open(devlog_dir+"/constructionDetails.log");
  #else 
    constructionDetails.open(devlog_dir+"/constructionDetails.log");
  #endif

  // General Layer Information
  constructionDetails << "Number of Layers: " << nLayers << std::endl;
  constructionDetails << std::endl;

  for (G4int i = 0; i < nLayers; i++) {
    constructionDetails << i << " Altitude (km):   " << altitude[i]*(1/km) << " - " << altitude[i+1]*(1/km) << std::endl;
    constructionDetails << i << "\t solidVolume Name:      " << solidAtmosphere[i] -> GetName() << std::endl;
    constructionDetails << i << "\t logicVolume Name:      " << logicAtmosphere[i] -> GetName() << std::endl;
    constructionDetails << i << "\t physVolume Name:       " << physAtmosphere[i] -> GetName() << std::endl;
    constructionDetails << i << "\t Layer Width (km):      " << atmosphereLayerWidth[i]*(1/km) << std::endl;
    constructionDetails << i << "\t Density (kg/m3):       " << atmosphereMaterial[i] -> GetDensity()*(m3/kg) << std::endl;
    constructionDetails << i << "\t Pressure (Pa):         " << atmosphereMaterial[i] -> GetPressure()*(1/pascal) << std::endl;
    constructionDetails << i << "\t Temperature (K):       " << atmosphereMaterial[i] -> GetTemperature()*(1/kelvin) << std::endl;
    constructionDetails << i << "\t Molar Weight (kg/mol): " << molarWeight[i]*(mole/kg) << std::endl;
    constructionDetails << i << "\t Elements:" << std::endl;

    const G4ElementVector* elements = atmosphereMaterial[i] -> GetElementVector();
    G4int numElements = atmosphereMaterial[i] -> GetNumberOfElements();
    for (G4int iel = 0; iel < numElements; ++iel) {
      G4String elementName = (*elements)[iel] -> GetName();
      G4double massFraction = atmosphereMaterial[i] -> GetFractionVector()[iel];
      constructionDetails << i << "\t\t" << elementName << "\t" << massFraction*100.0 << " %" << std::endl;
    }

    constructionDetails << i << "\t Materials:" << std::endl;

    std::map<G4Material*, G4double> materials = atmosphereMaterial[i] -> GetMatComponents();
    // G4int numComponents = materials.size();
    for (auto imat = materials.begin(); imat != materials.end(); ++imat) {
      G4String materialName = imat -> first -> GetName();
      G4double massFraction = imat -> second;
      constructionDetails << i << "\t\t" << materialName << "\t" << massFraction*100.0 << " %" << std::endl;
    }

    constructionDetails <<  "" << std::endl;
  }

  constructionDetails.close();
}