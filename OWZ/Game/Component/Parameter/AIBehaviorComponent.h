#pragma once
#include "gameObject/Component.h"
#include "Parameter/General/AIBehaviorParameter.h"
#include "Component/Math/TransformComponent.h"
#include <cfloat>
#include <cmath>


class AIBehaviorComponent : public Component
{
	appClass(AIBehaviorComponent)
public:
	explicit AIBehaviorComponent(const AIBehaviorParameter* param) : m_param(param) {}


	void SetPlayerTransform(std::weak_ptr<TransformComponent> t) {}


	float CalcDistanceToPlayer(std::shared_ptr<TransformComponent> myTransform) const;


	bool IsPlayerInDetectionRange(std::shared_ptr<TransformComponent> myTransform) const;


	bool IsPlayerLost(std::shared_ptr<TransformComponent> myTransform) const;


private:
	bool Start() override { return true; }
	void Update() override {}


private:
	const AIBehaviorParameter* m_param;
	std::weak_ptr<TransformComponent> m_playerTransform;

	
};
