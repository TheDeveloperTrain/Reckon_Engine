#pragma once
#include "Component.h"
#include "Transform.h"
#include <vector>
#include <string>
#include <optional>
#include <ReckonCore.h>

class RCK_API GameObject
{
public:
	GameObject();
	GameObject(std::string _name);
    GameObject(Transform initialTransform, std::string _name);
	std::optional<Component> GetComponent(ComponentType type);
	std::string name;
	Transform transform;
private:
	std::vector<Component> components;
};

