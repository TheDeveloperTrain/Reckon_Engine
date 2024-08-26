#include "GameObject.h"

GameObject::GameObject()
{
	name = "null";
}


GameObject::GameObject(std::string _name)
{
	name = _name;
}
GameObject::GameObject(Transform initialTransform, std::string _name)
{
	transform = initialTransform;
}

std::optional<Component> GameObject::GetComponent(ComponentType type)
{
	if (type == ComponentType::Transform)
	{
		return transform;
	}
	for (Component component : components)
	{
		if (component.type == type)
		{
			return component;
		}
	}
	return std::nullopt;
}