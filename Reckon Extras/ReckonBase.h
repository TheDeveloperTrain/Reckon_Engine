#pragma once
#include <ReckonCore.h>

class RCK_API ReckonBase
{
public:
    virtual void Start() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void FixedUpdate() = 0;
    virtual ~ReckonBase() = default;

    // Static method to ensure registration of derived classes
    static void RegisterInstance(ReckonBase* instance);

protected:
    ReckonBase();
};
