#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleGun.hh"

class MyPrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
public:
    MyPrimaryGenerator(bool useGPS);  // Constructor con opción para usar GPS o ParticleGun
    ~MyPrimaryGenerator();

    virtual void GeneratePrimaries(G4Event*);
    
private:
    G4ParticleGun *fParticleGun;  // Mantén el ParticleGun
    G4GeneralParticleSource *fParticleSource;  // Agrega el GeneralParticleSource
    bool useGPS;  // Para decidir cuál usar
};

#endif
