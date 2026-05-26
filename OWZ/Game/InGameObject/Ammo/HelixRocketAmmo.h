#pragma once
#include "InGameObject/Ammo/AmmoBase.h"

class HelixBlast : public GameObject
{
private:
	bool m_isHit = false;

public:
	void Init(AmmoData ammoData);

	void HitAmmo(const HitResult& hitResult);

	bool IsHit() { return m_isHit; }

	void Reset();
private:

};

class HelixRocketAmmo : public AmmoBase
{
public:
	HelixRocketAmmo();
	~HelixRocketAmmo();

private:
	Vector3 m_moveDirectiron = Vector3::Zero;
	float m_speed = 0.0;
	float m_radius = 0.0f;
	float m_mass = 0.0f;

	bool m_isHit = false;

	TransformComponent* m_transform;

	HelixBlast* m_blast;

public:
	void Init(AmmoData ammoData)override;

	void GoAmmo(Vector3 moveDirection, Vector3 position) override;

	void Update()override;

private:
	void HitAmmo(const HitResult& hitResult);
};

