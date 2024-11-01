#include "action.hh"
#include "SteppingAction.hh"
#include "event.hh" 
#include "generator.hh"
#include "run.hh"
#include "MySensitiveDetector.hh"

MyActionInitialization::MyActionInitialization() {}
MyActionInitialization::~MyActionInitialization() {}

void MyActionInitialization::Build() const {
    // Crear una instancia de SteppingAction
    auto* steppingAction = new SteppingAction();
    SetUserAction(steppingAction);

    // Crear una instancia del detector sensible
    auto* sensitiveDetector = new MySensitiveDetector("SensitiveDetector");

    // Crear una instancia de MyEventAction pasando SteppingAction y MySensitiveDetector
    auto* eventAction = new MyEventAction(sensitiveDetector, steppingAction);
    SetUserAction(eventAction);

    // Configurar el generador de partículas
    auto* generator = new MyPrimaryGenerator(true); // Cambiar a `generator.hh`
    SetUserAction(generator);

    // Configurar la acción de ejecución
    auto* runAction = new MyRunAction(); // Cambiar a `run.hh`
    SetUserAction(runAction);
}
