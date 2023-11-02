#include "construction.hh"
#include "G4Tubs.hh"
#include "G4VisAttributes.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    G4NistManager *nist = G4NistManager::Instance();
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_WATER");

    // Construye un cilindro en lugar de una caja
    G4Tubs *solidWorld = new G4Tubs("solidWorld", 0., 0.5*m, 0.5*m, 0., 360.*deg); // Aumentamos el número de segmentos a 100

    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");

    // Define atributos de visualización para mostrar una malla alrededor del volumen
    G4VisAttributes* visAttributes = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0)); // Blanco
    visAttributes->SetForceWireframe(true); // Modo alámbrico
    visAttributes->SetLineWidth(2.0); // Ancho de las líneas (ajusta según sea necesario)
    logicWorld->SetVisAttributes(visAttributes);

    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

    return physWorld;
}
