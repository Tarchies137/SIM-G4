// event.cc
#include "event.hh"
#include "G4AnalysisManager.hh"
#include "G4Event.hh"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"
#include "SteppingAction.hh"
#include "MySensitiveDetector.hh"

// Constructor
MyEventAction::MyEventAction(MySensitiveDetector* sensDet, SteppingAction* steppingAction)
    : fSensitiveDetector(sensDet), fSteppingAction(steppingAction) {}
// Destructor
MyEventAction::~MyEventAction()
{}

void MyEventAction::BeginOfEventAction(const G4Event*) {
    fSteppingAction->ResetPhotonCount();
}
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
    G4double primaryEnergy = 0;

    if (event->GetNumberOfPrimaryVertex() > 0) {
        G4PrimaryVertex* vertex = event->GetPrimaryVertex(0);
        fX = vertex->GetX0();
        fY = vertex->GetY0();
        fZ = vertex->GetZ0();
       if (vertex->GetPrimary() != nullptr) {
        G4PrimaryParticle* primaryParticle = vertex->GetPrimary();
        primaryEnergy = primaryParticle->GetTotalEnergy(); // Esto te da la energía de la partícula primaria
    }
}
    // Obtener el número real de fotones detectados desde MySensitiveDetector
    
    G4double photonEnergy = 2.0 * MeV; // Ejemplo: Energía de los fotones en MeV
        // Obtener el número de fotones generados desde SteppingAction
    G4int numPhotonsGenerated = fSteppingAction->GetPhotonCount();

    G4int NPhotonPMT = fSensitiveDetector->GetNumPhotonsPMT();


    // Llenar las columnas de la ntupla con los datos obtenidos
    man->FillNtupleIColumn(0, fEvent);
    man->FillNtupleDColumn(1, fX);
    man->FillNtupleDColumn(2, fY);
    man->FillNtupleDColumn(3, fZ);
    man->FillNtupleIColumn(4, numPhotonsGenerated);
    man->FillNtupleDColumn(5, primaryEnergy);

    // Añadir la fila de datos
    man->AddNtupleRow();
}
