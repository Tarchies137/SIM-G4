#include "generator.hh"
#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "Randomize.hh"  // Para G4UniformRand()
#include "CLHEP/Units/SystemOfUnits.h"  // Incluir las unidades de CLHEP

using namespace CLHEP;  // Usar el espacio de nombres para las unidades

MyPrimaryGenerator::MyPrimaryGenerator(bool useGPSOption)
    : useGPS(useGPSOption)
{
    if (useGPS) {
        // Si se usa el GPS
        fParticleSource = new G4GeneralParticleSource();
    } else {
        // Si se usa el ParticleGun
        fParticleGun = new G4ParticleGun(1);
    }
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    if (useGPS) {
        delete fParticleSource;
    } else {
        delete fParticleGun;
    }
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event* anEvent)
{
    if (useGPS) {
        // Usar GPS si está activado
        fParticleSource->GeneratePrimaryVertex(anEvent);
    } else {
        // Si no, usar ParticleGun (como en tu código original)
        G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
        G4String particleName = "mu-";
        G4ParticleDefinition *particle = particleTable->FindParticle(particleName);

        G4double x1 = 0 *m;
        G4double y1 = 3.*m;
        G4double z1 = 0;//3.*G4UniformRand()*m - 3*m;

        G4double x2 = 0 *m;
        G4double y2 = 1.2*m;
        G4double z2 = 0;//2.4*G4UniformRand()*m - 1.2*m;

        G4double x = x2 - x1;
        G4double y = y2 - y1;
        G4double z = z2 - z1;

        G4ThreeVector pos(x1, y1, z1);
        G4ThreeVector mom(x, y, z);

        fParticleGun->SetParticlePosition(pos);
        fParticleGun->SetParticleMomentumDirection(mom);
        fParticleGun->SetParticleMomentum(pow(10, 2 + 4 * G4UniformRand()) * MeV);
        fParticleGun->SetParticleDefinition(particle);

        fParticleGun->GeneratePrimaryVertex(anEvent);
    }
}
