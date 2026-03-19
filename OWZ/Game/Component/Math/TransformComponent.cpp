#include "stdafx.h"
#include "TransformComponent.h"

TransformComponent::TransformComponent()
{
	m_transform = std::make_shared<Transform>();
}

TransformComponent::~TransformComponent()
{
}

