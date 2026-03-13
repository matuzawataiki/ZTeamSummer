#include "stdafx.h"
#include "ViewModelComponent.h"

ViewModelComponent::~ViewModelComponent()
{
}

void ViewModelComponent::Update()
{
	if (m_drawFlag) {
		m_model->Update();
	}
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

		m_animations.Create(m_animationData.size());
		int num = 0;
		for (auto it : m_animationData) {
			m_animations[num].Load(it.filePath);
			m_animations[num].SetLoopFlag(it.loopFlag);
			num++;
		}
	}
	m_forwardLight.direction = g_sceneLight->GetSceneLight().directionalLight->direction;
	m_forwardLight.color = g_sceneLight->GetSceneLight().directionalLight->color;
	m_forwardLight.position = Vector3::Zero;
	m_forwardLight.ambientcolor = g_sceneLight->GetSceneLight().ambinetLight;
	//シーンライト
	modelInitData.m_expandConstantBuffer = &m_forwardLight;
	modelInitData.m_expandConstantBufferSize = sizeof(ForwardLight);

	m_model->InitForwardRendering(modelInitData, m_animations.data(), m_animations.size());
	m_model->Update();
	m_drawFlag = true;
}

void ViewModelComponent::AddAnimation(const char* filePath, bool loopFlag)
{
	m_animationData.push_back(AnimationData(filePath, loopFlag));
}

void ViewModelComponent::PlayAnimation(int num)
{
	m_model->PlayAnimation(num);
}

void ViewModelComponent::Draw()
{
	if (!m_drawFlag) return;

	m_model->ForwardDraw();
}
