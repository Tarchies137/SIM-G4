#ifndef MySensitiveDetector_h
#define MySensitiveDetector_h

#include "G4VSensitiveDetector.hh"
#include "G4Step.hh"
#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh" // Asegúrate de incluir esto

class MySensitiveDetector : public G4VSensitiveDetector {
public:
    MySensitiveDetector(const G4String& name);
    virtual ~MySensitiveDetector() override;

    // Métodos principales
    virtual void Initialize(G4HCofThisEvent*) override;
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* hist) override; // Declaración correcta
    virtual void EndOfEvent(G4HCofThisEvent*) override;

    // Nuevo método para obtener el número de fotones detectados
    G4int GetNumPhotons() const;

private:
    G4int numPhotons;  // Contador para los fotones detectados
};

#endif
