// event.hh

#ifndef MyEventAction_h
#define MyEventAction_h

#include "G4UserEventAction.hh"
#include "G4Event.hh"

// Necesitamos incluir la clase MySensitiveDetector
#include "MySensitiveDetector.hh"

class MyEventAction : public G4UserEventAction {
public:
    MyEventAction(MySensitiveDetector* sensDet);
    virtual ~MyEventAction() override;

    virtual void EndOfEventAction(const G4Event* event) override;

private:
    MySensitiveDetector* fSensitiveDetector; // Puntero al detector sensible
};

#endif
