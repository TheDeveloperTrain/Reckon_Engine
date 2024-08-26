// Sandbox.h
#pragma once

#include <ReckonBase.h>
#include <ReckonCore.h>
#include <iostream>

class Sandbox : public ReckonBase
{
public:
    Sandbox();

    void Start() override;
    void Update(float deltaTime) override;
    void FixedUpdate() override;

private:
    static Sandbox instance; // Static instance for automatic registration
};
