#pragma once
#include "Component/Status/HP.h"

class Buff
{
public:
	Buff(std::function<void(const GameObject*)> start, std::function<void(const GameObject*)> update, float time, GameObject* target):
		m_start(std::move(start)),
		m_update(std::move(update)),
		m_buffTime(time),
		m_target(target)
	{}

private:
	float m_buffTime;
	GameObject* m_target;
	bool m_isDead = false;
	bool m_isStart = false;

	std::function<void(const GameObject*)> m_start;
	std::function<void(const GameObject*)> m_update;

public:
	void Update();

};

class BuffList
{
public:
	~BuffList();

private:
	std::map<std::string, std::unique_ptr<Buff>> m_buffList;

public:
	void Update();
	bool AddBuff(std::string name);

};

class StatusComponent : public Component
{
	appClass(StatusComponent)
public:
	StatusComponent() = default;
	~StatusComponent() = default;

private:
	Life m_hp;
	float m_speed;
	float m_speedBonus;
	float m_attacPower;

public:
	void Init(Vector3 hp, float speed, float attacPower);

	Life* GetHP() { return &m_hp; }

	float GetSpeed()const { return m_speed; }
	
	float GetAttacPower()const { return m_attacPower; }

	void SetSpeedBonus(float speedBonus) { m_speedBonus; }

	float GetSpeedBonus()const { return m_speedBonus; }



};