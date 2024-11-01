#include "SteppingAction.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4OpticalPhoton.hh"
#include "G4VProcess.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

// Constructor
SteppingAction::SteppingAction() : G4UserSteppingAction(), numPhotonsGenerated(0) {}

// Destructor
SteppingAction::~SteppingAction() {}

// Reiniciar el contador de fotones generados
void SteppingAction::ResetPhotonCount() {
    numPhotonsGenerated = 0;
}

// Obtener el número de fotones generados
G4int SteppingAction::GetPhotonCount() const {
    return numPhotonsGenerated;
}

// Método para contar fotones Cherenkov generados en cada paso
void SteppingAction::UserSteppingAction(const G4Step* step) {
    // Verificamos si el paso es de un fotón óptico
    if (step->GetTrack()->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()) {
        // Verificamos que el proceso creador sea Cherenkov
        const G4VProcess* creatorProcess = step->GetTrack()->GetCreatorProcess();
        if (creatorProcess && creatorProcess->GetProcessName() == "Cerenkov") {
            numPhotonsGenerated++; // Incrementa el contador
            G4cout << "Fotón Cherenkov generado" << G4endl; // Mensaje de depuración
        }
    }
}
