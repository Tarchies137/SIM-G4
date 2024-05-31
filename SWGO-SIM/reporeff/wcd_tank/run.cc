#include "run.hh"

MyRunAction::MyRunAction()
{}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run*)
{
	auto *man = G4AnalysisManager::Instance();

	G4String filename = "output.root";
	man->OpenFile(filename);

	man->CreateNtuple("Hits", "Hits");
	man->CreateNtupleIColumn("fEvent");
	man->CreateNtupleDColumn("fX");
	man->CreateNtupleDColumn("fY");
	man->CreateNtupleDColumn("fZ");
	//man->CreateNtupleIColumn("NumPhotons");       // Nueva columna para contar fotones
    	//man->CreateNtupleDColumn("PhotonEnergy");    // Nueva columna para la energía de los fotones
	man->FinishNtuple(0); 
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
	auto *man = G4AnalysisManager::Instance();

	man->Write();
	man->CloseFile();
} 
