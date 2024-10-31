#include "action.hh"

#include "event.hh" // Incluir el archivo de cabecera del EventAction

MyActionInitialization::MyActionInitialization()
{}

MyActionInitialization::~MyActionInitialization()
{}
void MyActionInitialization::Build() const
{
    MyPrimaryGenerator *generator = new MyPrimaryGenerator(true);
    SetUserAction(generator);

    MyRunAction *runAction = new MyRunAction();
    SetUserAction(runAction);

    // Crear una instancia del detector sensible
    auto *sensitiveDetector = new MySensitiveDetector("SensitiveDetector");

    // Crear el MyEventAction con el detector sensible
    MyEventAction *eventAction = new MyEventAction(sensitiveDetector);
    SetUserAction(eventAction);
}
