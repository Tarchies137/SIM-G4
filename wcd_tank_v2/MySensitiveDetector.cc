#include "MySensitiveDetector.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4OpticalPhoton.hh"
#include "G4ParticleDefinition.hh"
#include "G4VProcess.hh" 

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
G4bool MySensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory*) {
    // Verificamos si el paso corresponde a un fotón óptico
    if (step->GetTrack()->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()) {
        // Verificamos que el proceso creador sea Cherenkov
        const G4VProcess* creatorProcess = step->GetTrack()->GetCreatorProcess();
        if (creatorProcess && creatorProcess->GetProcessName() == "Cerenkov") {
             numPhotons++;
            // Verificar que el fotón esté en el volumen del PMT
            G4VPhysicalVolume* volume = step->GetPreStepPoint()->GetPhysicalVolume();
            if (volume) {
                G4cout << "Fotón en volumen: " << volume->GetName() << G4endl; // Imprime el nombre del volumen actual
            }
                
           /* if (volume && volume->GetName() == "physDetector") { // Verificar el nombre correcto del volumen
                numPhotons++; // Incrementar el contador
                G4cout << "Fotón Cherenkov detectado en el PMT" << G4endl;
            }*/
        }
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
