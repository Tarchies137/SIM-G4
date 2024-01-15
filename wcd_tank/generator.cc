#include "generator.hh"
#include "Randomize.hh"

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
//-------Definiendo partícula (muón)
	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	G4String particleName = "mu+";
	G4ParticleDefinition *particle = particleTable->FindParticle(particleName);
//-----------------------------------------------
// DEfiniedo parámetros de lazamiento
	G4double x1 = 0 *m;
	G4double y1 = 3.*m;
	G4double z1 = 3.*G4UniformRand()*m-3*m;

	G4double x2 = 0 *m;
	G4double y2 = 1.2*m;
	G4double z2 = 2.4*G4UniformRand()*m-1.2*m;

	G4double x = x2-x1 ;
	G4double y = y2-y1;
	G4double z = z2-z1;

	G4ThreeVector pos(x1,y1,z1);
	G4ThreeVector mom(x,y,z);

	fParticleGun->SetParticlePosition(pos);
	fParticleGun->SetParticleMomentumDirection(mom);
	fParticleGun->SetParticleMomentum(1000*MeV);
	fParticleGun->SetParticleDefinition(particle);

	fParticleGun->GeneratePrimaryVertex(anEvent);
}
