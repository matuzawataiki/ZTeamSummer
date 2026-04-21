#pragma once
#include "InGameObject/Ammo/AmmoBase.h"

struct AmmoData;
class NormalAmmo : public AmmoBase
{
public:
	NormalAmmo() = default;
	~NormalAmmo() = default;

private:
	Vector3 m_moveDirectiron = Vector3::Zero;
	float m_speed = 0.0;
	float m_radius = 0.0f;
	float m_range = 0.0f;
	float m_mass = 0.0f;
	
public:
	void Init(AmmoData ammoData) override;

	void GoAmmo(Vector3 moveDirection,Vector3 position) override;

private:
	void Update();
};

