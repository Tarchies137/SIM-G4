#include "action.hh"

MyActionInicialization::MyActionInicialization()
{}

MyActionInicialization::~MyActionInicialization()
{}

void MyActionInicialization::Build() const
{
	MyPrimaryGenerator *generator = new MyPrimaryGenerator();
	SetUserAction(generator);

	MyRunAction *runAction = new MyRunAction();
	SetUserAction(runAction);
}