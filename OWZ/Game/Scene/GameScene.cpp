#include "stdafx.h"
#include "GameScene.h"
#include "Scene/SceneManager.h"
#include "InGameObject/Character/Playable/Soldier.h"
#include "UISystem.h"
#include "UIObfect.cpp"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Initialize()
{
	//UI登録
	{
		auto crosshair = std::make_shared<ScreenSpaceUIObject>();
		crosshair->Init("Assets/image/ui/crosshair/crosshair.dds", 64.0f, 64.0f);

		auto transform = crosshair->GetComponent<ScreenUITransformComponent>();
		if (transform != nullptr) {
			transform->SetLocalPosition({ 960.0f, 540.0f, 0.0f });
		}

		UISystem::Get().GetCanvas(CanvasType::HUD).AddUI(crosshair);
	}

	// 破壊ミッションの生成と登録
	//DestructionMission* mission = new DestructionMission();
	//mission->AddTarget(m_tower);  // 1つ目を登録
	//mission->AddTarget(m_tower2); // 2つ目を登録

	// 管理を任せる
	//m_currentMission = mission;
}

void GameScene::Update(SceneManager& manager)
{

}

void GameScene::Draw()
{
}

void GameScene::Finalize()
{
}
