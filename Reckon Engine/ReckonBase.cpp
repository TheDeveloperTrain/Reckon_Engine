#include "ReckonBase.h"
#include "GameRegistry.h"

void ReckonBase::Start() { }
void ReckonBase::Update(float deltaTime) { }
void ReckonBase::FixedUpdate() {}

ReckonBase::ReckonBase()
{
    GameRegistry::RegisterClass(this);
}

void ReckonBase::RegisterInstance(ReckonBase* instance)
{
    GameRegistry::RegisterClass(instance);
}
