#include "run.hh"

MyRunAction::MyRunAction()
{}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run*)
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();

	man->OpenFile("/home/usuario/fabian/SIMULADORES/Geant4/SIM-G4/sim/build/output.root");
	G4cout << "void MyRunAction::BeginOfRunAction(const G4Run*)" <<G4endl;

	man->CreateNtuple("Hits", "Hits");
	man->CreateNtupleIColumn("fEvent");
	man->CreateNtupleDColumn("fX");
	man->CreateNtupleDColumn("fY");
	man->CreateNtupleDColumn("fZ");
	man->FinishNtuple(0); 
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	G4cout << "void MyRunAction::EndOfRunAction(const G4Run*)" <<G4endl;


	man->Write();
	man->CloseFile();
} 