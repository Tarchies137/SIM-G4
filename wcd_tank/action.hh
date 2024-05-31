#ifndef ACTION_HH
#define ACTION_HH

#include "G4VUserActionInitialization.hh"

#include "generator.hh"
#include "run.hh"

class MyActionInicialization : public G4VUserActionInitialization
{
public:
	MyActionInicialization();
	~MyActionInicialization();

	virtual void Build() const;
	
};

#endif