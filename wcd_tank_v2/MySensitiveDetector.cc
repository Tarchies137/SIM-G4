#include "MySensitiveDetector.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4OpticalPhoton.hh"
#include "G4VProcess.hh"

// Constructor
MySensitiveDetector::MySensitiveDetector(const G4String& name)
    : G4VSensitiveDetector(name), NPhotonPMT(0)
{}

// Destructor
MySensitiveDetector::~MySensitiveDetector() {}

// Inicializar el contador al inicio del evento
void MySensitiveDetector::Initialize(G4HCofThisEvent*) {
    NPhotonPMT = 0;
}

// Procesar los hits y contar los fotones en el PMT
G4bool MySensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory*) {
    if (step->GetTrack()->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()) {
        G4VPhysicalVolume* volume = step->GetPreStepPoint()->GetPhysicalVolume();
        if (volume) {
            G4cout << "Fotón en volumen: " << volume->GetName() << G4endl; // Imprime el nombre del volumen actual
        }
        
        if (volume && volume->GetName() == "physDetector") {
            NPhotonPMT++;
            G4cout << "Fotón Cherenkov detectado en el PMT" << G4endl;
        }
    }
    return true;
}
// Método final del evento, si se requiere algún proceso adicional
void MySensitiveDetector::EndOfEvent(G4HCofThisEvent*) {
    // Este método es opcional si deseas realizar procesos adicionales al final del evento
}

// Método para obtener el número de fotones detectados en el PMT
G4int MySensitiveDetector::GetNumPhotonsPMT() const {
    return NPhotonPMT;
}
