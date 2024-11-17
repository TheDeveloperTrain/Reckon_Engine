#pragma once
#include "Components/Component.h" 
#include "Components/Transform.h"
#include <optional>
#include <ReckonCore.h>
#include <string>
#include <vector>
#include <memory>

class RCK_API GameObject
{
public:
	// Default constructors
	GameObject();
	GameObject(std::string _name);
	GameObject(Transform initialTransform, std::string _name);


	std::optional<Component*> GetComponent(ComponentType type);
	void AddComponent(std::shared_ptr<Component> component);

	std::string name;
	std::shared_ptr<Transform> transform;

private:
	std::vector<std::shared_ptr<Component>> components;
};
