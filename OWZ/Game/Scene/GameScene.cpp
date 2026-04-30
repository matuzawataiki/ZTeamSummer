#include "stdafx.h"
#include "GameScene.h"
#include "InGameObject/Character/Playable/Soldier.h"
#include "InGameObject/Object/StageObject.h"

GameScene::GameScene()
{
	testPlayer = new Soldier;
	testStage = new StageObject;	
	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	g_camera3D->SetFar(10000000000.0f);

}

GameScene::~GameScene()
{
}

void GameScene::Initialize()
{

}

void GameScene::Update(SceneManager& manager)
{
	testPlayer->StartWrapper();
	testPlayer->UpdateWrapper();

	testStage->StartWrapper();
	testStage->UpdateWrapper();

	if (g_pad[0]->IsTrigger(enButtonE)) {
		PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	}
	if (g_pad[0]->IsTrigger(enButtonQ)) {
		PhysicsWorld::GetInstance()->DisableDrawDebugWireFrame();
	}

}

void GameScene::Draw()
{
	testPlayer->Render();
	testStage->Render();
}

void GameScene::Finalize()
{
}
