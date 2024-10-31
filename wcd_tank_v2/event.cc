// event.cc
#include "event.hh"
#include "G4AnalysisManager.hh"
#include "G4Event.hh"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"

// Constructor
MyEventAction::MyEventAction(MySensitiveDetector* sensDet)
    : fSensitiveDetector(sensDet)
{}

// Destructor
MyEventAction::~MyEventAction()
{}

void MyEventAction::EndOfEventAction(const G4Event* event)
{
    // Obtener el AnalysisManager
    auto *man = G4AnalysisManager::Instance();

    // Asignar el número de evento actual
    G4int fEvent = event->GetEventID();

    // Obtener la posición del primer track
    G4double fX = 0.0;
    G4double fY = 0.0;
    G4double fZ = 0.0;

    if (event->GetNumberOfPrimaryVertex() > 0) {
        G4PrimaryVertex* vertex = event->GetPrimaryVertex(0);
        fX = vertex->GetX0();
        fY = vertex->GetY0();
        fZ = vertex->GetZ0();
    }

    // Obtener el número real de fotones detectados desde MySensitiveDetector
    G4int numPhotons = fSensitiveDetector->GetNumPhotons();
    G4double photonEnergy = 2.0 * MeV; // Ejemplo: Energía de los fotones en MeV

    // Llenar las columnas de la ntupla con los datos obtenidos
    man->FillNtupleIColumn(0, fEvent);
    man->FillNtupleDColumn(1, fX);
    man->FillNtupleDColumn(2, fY);
    man->FillNtupleDColumn(3, fZ);
    man->FillNtupleIColumn(4, numPhotons);
    man->FillNtupleDColumn(5, photonEnergy);

    // Añadir la fila de datos
    man->AddNtupleRow();
}
