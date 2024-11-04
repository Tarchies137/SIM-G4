#include "construction.hh"
#include "MySensitiveDetector.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    G4NistManager *nist = G4NistManager::Instance();

    //-----------Constantes de los materiales ---------------
    G4double a, z, density;
    G4int nelements;

    G4Element* N = new G4Element("Nitrogen", "N", z=7 , a=14.01*g/mole);
    G4Element* H = new G4Element("Hydrogen", "H", z=1 , a=1.01*g/mole);
    G4Element* O = new G4Element("Oxygen"  , "O", z=8 , a=16.00*g/mole);

    G4Material *tankMat = new G4Material("tankMat", 1.000*g/cm3, 2);
    tankMat->AddElement(nist->FindOrBuildElement("H"),2);
    tankMat->AddElement(nist->FindOrBuildElement("O"),1);

    G4Element *C = nist->FindOrBuildElement("C");

    G4Material *Aerogel = new G4Material("Aerogel", 0.200*g/cm3, 3);
    Aerogel->AddElement(nist->FindOrBuildElement("Si"), 62.5*perCent);
    Aerogel->AddElement(nist->FindOrBuildElement("O"), 37.4*perCent);
    Aerogel->AddElement(C, 0.1*perCent);

/* G4Material* Tyvek = new G4Material("Tyvek", 0.94 * g / cm3, 2);
    Tyvek->AddElement(nist->FindOrBuildElement("H"), 4);
    Tyvek->AddElement(nist->FindOrBuildElement("C"), 2);*/
    G4Material* Tyvek = nist->FindOrBuildMaterial("G4_POLYETHYLENE");

    //-----------------------------------------------------------------------
    // Propiedades ópticas del material del estanque (tankMat)
    //-----------------------------------------------------------------------
    G4double energy[]={ 2.034*eV, 2.068*eV, 2.103*eV, 2.139*eV,
                2.177*eV, 2.216*eV, 2.256*eV, 2.298*eV,
                2.341*eV, 2.386*eV, 2.433*eV, 2.481*eV,
                2.532*eV, 2.585*eV, 2.640*eV, 2.697*eV,
                2.757*eV, 2.820*eV, 2.885*eV, 2.954*eV,
                3.026*eV, 3.102*eV, 3.181*eV, 3.265*eV,
                3.353*eV, 3.446*eV, 3.545*eV, 3.649*eV,	
                3.760*eV, 3.877*eV, 4.002*eV, 4.136*eV};

    const G4int nEntries = sizeof(energy)/sizeof(G4double);

    G4double rindexTank[] =
              { 1.3435, 1.344,  1.3445, 1.345,  1.3455,
                1.346,  1.3465, 1.347,  1.3475, 1.348,
                1.3485, 1.3492, 1.35,   1.3505, 1.351,
                1.3518, 1.3522, 1.3530, 1.3535, 1.354,
                1.3545, 1.355,  1.3555, 1.356,  1.3568,
                1.3572, 1.358,  1.3585, 1.359,  1.3595,
                1.36,   1.3608};

    assert(sizeof(rindexTank) == sizeof(energy));

    G4double absorptionCoefficient[] =
             {3.448*m,  4.082*m,  6.329*m,  9.174*m, 12.346*m, 13.889*m,
             15.152*m, 17.241*m, 18.868*m, 20.000*m, 26.316*m, 35.714*m,
             45.455*m, 47.619*m, 52.632*m, 52.632*m, 55.556*m, 52.632*m,
             52.632*m, 47.619*m, 45.455*m, 41.667*m, 37.037*m, 33.333*m,
             30.000*m, 28.500*m, 27.000*m, 24.500*m, 22.000*m, 19.500*m,
             17.500*m, 14.500*m};

    G4MaterialPropertiesTable *mptTank = new G4MaterialPropertiesTable();
    mptTank->AddProperty("RINDEX", energy, rindexTank, nEntries);
    mptTank->AddProperty("ABSLENGTH", energy, absorptionCoefficient, nEntries);
    tankMat->SetMaterialPropertiesTable(mptTank);

    //-----------------------------------------------------------------------
    // Volúmenes
    //-----------------------------------------------------------------------

    // Habitación: Caja de 3mx3mx3m con aire
    G4Box *solidWorld = new G4Box("solidWorld", 3*m, 3*m, 3*m);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, nist->FindOrBuildMaterial("G4_AIR"), "logicWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "physWorld", 0, false, 0, true);

    // Estanque: Estanque de 1.2m de diámetro y 1.2m de altura, contiene Agua
    G4Tubs *solidRadiator = new G4Tubs("solidRadiator", 0., 1.2*m, 1.2*m, 0., 2 * CLHEP::pi);
    G4LogicalVolume *logicRadiator = new G4LogicalVolume(solidRadiator, tankMat, "logicalRadiator");
    G4RotationMatrix* rotation = new G4RotationMatrix();
    rotation->rotateX(90. * degree); // Se rota para visualizarlo vertical
    G4VPhysicalVolume *physRadiator = new G4PVPlacement(rotation, G4ThreeVector(0., 0., 0.), logicRadiator, "physRadiator", logicWorld, false, 0, true);

    
    // Capa de Tyvek: Envuelve el estanque para reflexión
    G4Tubs *solidTyvek = new G4Tubs("solidTyvek", 1.2*m, 1.2*m + 0.01*mm, 1.2*m, 0., 2 * CLHEP::pi);
    G4LogicalVolume *logicTyvek = new G4LogicalVolume(solidTyvek, Tyvek, "logicalTyvek");
    G4VPhysicalVolume *physTyvek = new G4PVPlacement(rotation, G4ThreeVector(0., 0., 0.), logicTyvek, "physTyvek", logicWorld, false, 0, true);
// 
// Crear la superficie óptica para Tyvek
G4OpticalSurface* tyvekSurface = new G4OpticalSurface("TyvekSurface");
tyvekSurface->SetType(dielectric_metal); // Tipo de interfaz para simular la reflexión
tyvekSurface->SetFinish(ground);         // Acabado rugoso para reflectividad difusa
tyvekSurface->SetModel(unified);         // Modelo unificado de óptica

// Definir las propiedades ópticas de la superficie Tyvek
G4double photonEnergy[] = {2.0*eV, 3.5*eV};       // Rango de energías (ajusta según tu simulación)
const G4int nnEntries = sizeof(photonEnergy) / sizeof(G4double);

G4double reflectivity[] = {0.9, 0.9};             // 90% de reflectividad
G4double efficiency[] = {0.0, 0.0};               // Eficiencia de detección cero (no absorbente)

G4MaterialPropertiesTable* tyvekMPT = new G4MaterialPropertiesTable();
tyvekMPT->AddProperty("REFLECTIVITY", photonEnergy, reflectivity, nnEntries);
tyvekMPT->AddProperty("EFFICIENCY", photonEnergy, efficiency, nnEntries);
tyvekSurface->SetMaterialPropertiesTable(tyvekMPT);

// Crear la superficie de borde entre el agua y Tyvek
new G4LogicalBorderSurface("WaterTyvekSurface", physRadiator, physTyvek, tyvekSurface);

    //Detector: Tubo cilíndrico dentro del estanque para detectar fotones
    
   
    G4Tubs *solidDetector = new G4Tubs("solidDetector", 0., 0.15*m, 0.1*m, 0., 2 * CLHEP::pi);
    logicDetector = new G4LogicalVolume(solidDetector,tankMat, "logicDetector");
    logicDetector->SetSensitiveDetector(mySensitiveDetector);
    G4VPhysicalVolume *physDetector = new G4PVPlacement(rotation,G4ThreeVector(0, 0.9*m, 0), logicDetector, "physDetector", logicWorld, false, 0, true);

    return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()

 

{
    auto *sensDet = new MySensitiveDetector("PMT");
    G4SDManager::GetSDMpointer()->AddNewDetector(sensDet);

    // Asignar el detector sensible al volumen lógico del detector
    logicDetector->SetSensitiveDetector(sensDet);
}