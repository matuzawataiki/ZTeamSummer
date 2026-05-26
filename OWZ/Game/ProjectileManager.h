#pragma once
#include "Component/Skill/WeaponData.h"
#include "InGameObject/Ammo/AmmoBase.h"


class ProjectileManager : Noncopyable
{
	struct AmmoPool
	{
		std::vector<std::unique_ptr<AmmoBase>> ammoPool;
		int nextIndex = 0;
	};
	using AmmoPools = std::map<std::string, AmmoPool>;

private:
	ProjectileManager();
	~ProjectileManager();
	static ProjectileManager* m_instance;

private:
	AmmoPools m_ammoPools;

	int m_crrentAmmoNum = 0;

public:
	static void CreateInstance() {
		if (!m_instance) {
			m_instance = new ProjectileManager;
		}
	}
	static void DeleteInstance() {
		delete m_instance;
		m_instance = nullptr;
	}
	static ProjectileManager* GetInstance() {
		return m_instance;
	}

	void Update();

	void UseAmmo(std::string name, Vector3 moveDirection, Vector3 position);

	template <typename T>
	void RegistAmmo(AmmoData ammoData)
	{
		AmmoPool ammoPool;
		ammoPool.ammoPool.resize(ammoData.ammoPoolSize);
		for (int i = 0; i < ammoPool.ammoPool.size(); i++) {
			ammoPool.ammoPool.at(i) = std::make_unique<T>();
			ammoPool.ammoPool.at(i)->Deactivate();
			ammoPool.ammoPool.at(i)->Init(ammoData);

		}

		m_ammoPools.emplace(ammoData.ammoName, std::move(ammoPool));
	}

};

