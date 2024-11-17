#include "GameObject.h"
#include "Components/MeshRenderer.h"

GameObject::GameObject()
{
	name = "null";
	Transform _transform = Transform();
	transform = std::make_shared<Transform>(_transform);
}

GameObject::GameObject(std::string _name)
{
	name = _name;
	Transform _transform = Transform();
	transform = std::make_shared<Transform>(_transform);
}

GameObject::GameObject(Transform initialTransform, std::string _name)
{
	name = _name;
	transform = std::make_shared<Transform>(initialTransform);
}


// Component methods
std::optional<Component*> GameObject::GetComponent(ComponentType type)
{
	if (type == ComponentType::Transform && transform)
	{
		return transform.get();
	}
	for (auto& component : components)
	{
		if (component->type == type)
		{
			return component.get();
		}
	}
	return std::nullopt;
}

void GameObject::AddComponent(std::shared_ptr<Component> component)
{
	components.push_back(std::move(component));
}
