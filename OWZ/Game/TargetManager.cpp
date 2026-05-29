#include "stdafx.h"
#include "TargetManager.h"
#include "TargetBase.h"
#include "InGameObject/Object/StageObject.h"

TargetManager* TargetManager::m_instance = nullptr;

TargetManager::TargetManager() = default;

TargetManager::~TargetManager() = default;

void TargetManager::Init()
{
	m_mapLevel.Init("Assets/target/targetLevel.tkl", [&](LevelObjectData& objData) {
		if (objData.EqualObjectName(L"target") == true) {
			auto target = std::make_unique<TargetBase>();
			Vector3 position = objData.position;
			position.x *= -1;

			target->Init("Assets/target/target1.tkm", 10, position, objData.rotation);
			m_targets.push_back(std::move(target));
			return true;
		}
		if (objData.EqualObjectName(L"target2") == true) {
			auto target = std::make_unique<TargetBase>();
			Vector3 position = objData.position;
			position.x *= -1;

			target->Init("Assets/target/target2.tkm", 30, position, objData.rotation);
			m_targets.push_back(std::move(target));
			return true;
		}
		if (objData.EqualObjectName(L"target3") == true) {
			auto target = std::make_unique<TargetBase>();
			Vector3 position = objData.position;
			position.x *= -1;

			target->Init("Assets/target/target3.tkm", 50, position, objData.rotation);
			m_targets.push_back(std::move(target));
			return true;
		}
		if (objData.EqualObjectName(L"target4") == true) {
			auto target = std::make_unique<TargetBase>();
			Vector3 position = objData.position;
			position.x *= -1;

			target->Init("Assets/target/target4.tkm", 200, position, objData.rotation);
			m_targets.push_back(std::move(target));
			return true;
		}
		if (objData.EqualObjectName(L"stage") == true) {
			m_stage = std::make_unique<StageObject>();
			m_stage->Init(objData.position, objData.rotation);
			return true;
		}
		return false;
	});
}

void TargetManager::Update()
{
	for (auto& target : m_targets) {
		target->StartWrapper();
		target->UpdateWrapper();
		target->Render();
	}


	m_stage->StartWrapper();
	m_stage->UpdateWrapper();
	m_stage->Render();
}

