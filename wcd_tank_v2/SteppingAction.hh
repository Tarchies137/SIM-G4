#ifndef STEPPINGACTION_HH
#define STEPPINGACTION_HH

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"

class SteppingAction : public G4UserSteppingAction {
public:
    SteppingAction();
    virtual ~SteppingAction();

    virtual void UserSteppingAction(const G4Step* step);
    void ResetPhotonCount(); // Método para reiniciar el contador
    G4int GetPhotonCount() const; // Método para obtener el valor del contador

private:
    G4int numPhotonsGenerated; // Contador de fotones generados
};

#endif // STEPPINGACTION_HH
