#pragma once

class HP
{
public:
	virtual ~HP() = default;

private:
	float m_health;
	int m_maxHealth;

public:
	void SetHealth(int hp) { 
		m_health = hp; 
		m_maxHealth = hp;
	}

	virtual float AddDamege(float damege);

	virtual float AddArmorDamege(float damege);

	float AddHeel(float heel);

	float GetHealth() { return m_health; }
	float GetMaxHealth() { return m_maxHealth; }
};

class Life
{
public:
	enum EnLifeType
	{
		enNormal,
		enArmor,
		enShield,
		enLifeTypeNum
	};

private:
	std::array<HP, enLifeTypeNum> m_lifes;
	float m_damageTimer = 0;

public:
	void AddDamege(float damege);

	void AddHeel(float heel);

	void Init(int normal = 0, int armor = 0, int shield = 0) {
		m_lifes[enNormal].SetHealth(normal);
		m_lifes[enArmor].SetHealth(armor);
		m_lifes[enShield].SetHealth(shield);
	}

	void Update();

	int GetMaxHealth() {
		return m_lifes[enNormal].GetMaxHealth() + m_lifes[enArmor].GetMaxHealth() + m_lifes[enShield].GetMaxHealth();
	}

	float GetHealth(EnLifeType lifeType) {
		return m_lifes[lifeType].GetHealth();
	}

};