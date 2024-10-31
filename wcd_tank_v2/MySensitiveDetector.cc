#include "MySensitiveDetector.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"

// Constructor
MySensitiveDetector::MySensitiveDetector(const G4String& name)
    : G4VSensitiveDetector(name), numPhotons(0)
{}

// Destructor
MySensitiveDetector::~MySensitiveDetector() {}

// Inicializar el contador al inicio del evento
void MySensitiveDetector::Initialize(G4HCofThisEvent*) {
    numPhotons = 0;
}

// Procesar los hits y contar los fotones
G4bool MySensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory* /*hist*/) {
    if (step->GetTrack()->GetDefinition()->GetParticleName() == "opticalphoton") {
        numPhotons++;  // Incrementar el contador de fotones
    }
    return true;
}

// Método final del evento, si se requiere algún proceso adicional
void MySensitiveDetector::EndOfEvent(G4HCofThisEvent*) {
    // Este método puede ser útil si deseas realizar algún proceso al final del evento
}

// Implementación del método GetNumPhotons()
G4int MySensitiveDetector::GetNumPhotons() const {
    return numPhotons;
}
