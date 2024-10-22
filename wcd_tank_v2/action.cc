#include "action.hh"

MyActionInicialization::MyActionInicialization()
{}

MyActionInicialization::~MyActionInicialization()
{}

void MyActionInicialization::Build() const
{
	MyPrimaryGenerator *generator = new MyPrimaryGenerator(true);
	SetUserAction(generator);

	MyRunAction *runAction = new MyRunAction();
	SetUserAction(runAction);
}