#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
	fParticleGun = new G4ParticleGun(1);
}
MyPrimaryGenerator::~MyPrimaryGenerator()
{
	delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event* anEvent)
{
//-----------------------------------------------
//-------Propiedades de la partícula (muón)
	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	G4String particleName = "mu+";
	G4ParticleDefinition *particle = particleTable->FindParticle(particleName);
//-----------------------------------------------
	G4double x = 0 ;
	G4double y = 2.;
	G4double z = 2.;

	G4ThreeVector pos(x*m,y*m,z*m);
	G4ThreeVector mom(-x,-y,-z);

	fParticleGun->SetParticlePosition(pos);
	fParticleGun->SetParticleMomentumDirection(-pos);
	fParticleGun->SetParticleMomentum(10*GeV);
	fParticleGun->SetParticleDefinition(particle);

	fParticleGun->GeneratePrimaryVertex(anEvent);
}