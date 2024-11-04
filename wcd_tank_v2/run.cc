#include "run.hh"

MyRunAction::MyRunAction()
{}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run*)
{
	auto *man = G4AnalysisManager::Instance();

	G4String filename = "/home/fabian/fabian/Simuladores/Geant4/SIM-G4/wcd_tank_v2/build/output.root";
	man->OpenFile(filename);

if (!man->IsOpenFile()) {
    G4cerr << "Error: No se pudo abrir el archivo para escritura." << G4endl;
}

G4cout << "Opening file: output.root" << G4endl;

	man->CreateNtuple("Hits", "Hits");
	man->CreateNtupleIColumn("fEvent");
	man->CreateNtupleDColumn("fX");
	man->CreateNtupleDColumn("fY");
	man->CreateNtupleDColumn("fZ");
	man->CreateNtupleIColumn("FotonTank");       // Nueva columna para contar fotones
    man->CreateNtupleDColumn("PMT");    // Nueva columna para la energía de los fotones
	man->FinishNtuple(0); 
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
	auto *man = G4AnalysisManager::Instance();

	man->Write();
	G4cout << "Datos escritos exitosamente." << G4endl;
	man->CloseFile();
	G4cout << "Closing file: output.root" << G4endl;

} 
