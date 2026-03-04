#include "stdafx.h"
#include "ViewModelComponent.h"

ViewModelComponent::~ViewModelComponent()
{
}

void ViewModelComponent::SetModel(const char* filePath, bool isAnimation)
{
	m_model = std::make_unique<ModelRender>();

	ModelInitData modelInitData;
	modelInitData.m_tkmFilePath = filePath;
	modelInitData.m_fxFilePath = "Assets/shader/forwardModel.fx";
	modelInitData.m_vsEntryPointFunc = "VSMain";
	modelInitData.m_vsSkinEntryPointFunc = "VSMain";
	if (isAnimation) {
		// アニメーションあり。
		modelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";
		modelInitData.m_skeleton = &m_skeleton;
	}
	m_forwardLight.direction = g_sceneLight->GetSceneLight().directionalLight->direction;
	m_forwardLight.color = g_sceneLight->GetSceneLight().directionalLight->color;
	m_forwardLight.position = Vector3::Zero;
	m_forwardLight.ambientcolor = g_sceneLight->GetSceneLight().ambinetLight;
	//シーンライト
	modelInitData.m_expandConstantBuffer = &m_forwardLight;
	modelInitData.m_expandConstantBufferSize = sizeof(ForwardLight);
	m_model->InitForwardRendering(modelInitData);
	m_model->Update();
}

void ViewModelComponent::AddAnimation(const char* filePath, int num, bool isLoop)
{
	AnimationClip* animationClip = new AnimationClip;
	animationClip->Load(filePath);
	animationClip->SetLoopFlag(isLoop);

	m_animation.emplace(num, animationClip);
}

void ViewModelComponent::Draw(RenderContext& rc)
{
	m_model->ForwardDraw(rc);
}
