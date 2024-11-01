#ifndef MyEventAction_h
#define MyEventAction_h

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "MySensitiveDetector.hh" // Incluir MySensitiveDetector
#include "SteppingAction.hh"       // Incluir SteppingAction

class MyEventAction : public G4UserEventAction {
public:
    MyEventAction(MySensitiveDetector* sensDet, SteppingAction* steppingAction);
    virtual ~MyEventAction() override;

    virtual void BeginOfEventAction(const G4Event* event) override;
    virtual void EndOfEventAction(const G4Event* event) override;

private:
    MySensitiveDetector* fSensitiveDetector; // Puntero al detector sensible
    SteppingAction* fSteppingAction;         // Puntero a SteppingAction
};

#endif
