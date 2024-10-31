#include "physics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"
#include "G4Cerenkov.hh"
#include "G4ProcessManager.hh"
#include "G4ProcessVector.hh"  // Para el idxPostStep

MyPhysicsList::MyPhysicsList() {
    // Registramos la física electromagnética
    RegisterPhysics(new G4EmStandardPhysics());

    // Registramos la física óptica
    RegisterPhysics(new G4OpticalPhysics());

    // Creamos el proceso de Cherenkov
    G4Cerenkov* theCherenkovProcess = new G4Cerenkov("Cerenkov");
    theCherenkovProcess->SetMaxNumPhotonsPerStep(300);      // Máximo de fotones por paso
    theCherenkovProcess->SetTrackSecondariesFirst(true);    // Para rastrear los fotones primero

    // Añadimos el proceso de Cherenkov a las partículas cargadas
    auto particleIterator = GetParticleIterator();
    particleIterator->reset();
    while ((*particleIterator)()) {
        G4ParticleDefinition* particle = particleIterator->value();
        G4ProcessManager* pmanager = particle->GetProcessManager();
        if (theCherenkovProcess->IsApplicable(*particle) && pmanager) {
            pmanager->AddProcess(theCherenkovProcess);
            pmanager->SetProcessOrdering(theCherenkovProcess, idxPostStep);
        }
    }
}

MyPhysicsList::~MyPhysicsList() {}
