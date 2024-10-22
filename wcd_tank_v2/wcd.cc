#include <iostream>

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "construction.hh"
#include "physics.hh"
#include "action.hh"
#include "generator.hh"

int main(int argc, char ** argv)
{
    G4RunManager* runManager = new G4RunManager();

    runManager->SetUserInitialization(new MyDetectorConstruction());
    runManager->SetUserInitialization(new MyPhysicsList());
    runManager->SetUserInitialization(new MyActionInicialization());

    // Aquí decidimos si usar GPS o ParticleGun en función de los argumentos
    bool useGPS = (argc == 2);  // Usar GPS si se pasa un archivo .mac
    runManager->SetUserAction(new MyPrimaryGenerator(useGPS));

    runManager->Initialize();

    G4UIExecutive* ui = nullptr;
    if (argc == 1) {
        ui = new G4UIExecutive(argc, argv);
    }

    G4VisManager* visManager = new G4VisExecutive();
    visManager->Initialize();

    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    if (argc == 2) {
        // Cargar archivo .mac si se proporciona como argumento
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    } else {
        // Configuración de la visualización interactiva si no hay archivo .mac
        UImanager->ApplyCommand("/vis/open OGL");
        UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 1 0 0");
        UImanager->ApplyCommand("/vis/drawVolume");
        UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true");
        UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");
        UImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate");

        // Iniciar sesión interactiva
        ui->SessionStart();
    }

    // Finalización
    delete visManager;
    delete runManager;
    
    return 0;
}
