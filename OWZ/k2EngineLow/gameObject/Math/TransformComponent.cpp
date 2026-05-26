#include "k2EngineLowPreCompile.h"
#include "TransformComponent.h"

namespace nsK2EngineLow
{

	TransformComponent::TransformComponent()
	{
		m_transform = std::make_unique<Transform>();
	}

	TransformComponent::~TransformComponent()
	{}

}
