#include "stdafx.h"
#include "ModelComponent.h"

ModelComponent::~ModelComponent()
{
}

void ModelComponent::SetModel(const char* filePath, bool isAnimation)  
{  
	m_model = std::make_unique<ModelRender>();  

	if (isAnimation) {   
		/**アニメーションがある場合はロードしておく*/
		m_animations.Create(m_animationData.size());
		int num = 0;
		for (auto it : m_animationData) {
			m_animations[num].Load(it.filePath);
			m_animations[num].SetLoopFlag(it.loopFlag);
			num++;
		}

		m_model->Init(filePath,m_animations.data(),m_animations.size());
	}  
	else {  
		m_model->Init(filePath);
	}

	m_model->Update();  
}

void ModelComponent::AddAnimation(const char* filePath, int num, bool loopFlag)
{
	m_animationData.push_back(AnimationData(filePath, loopFlag));
}

void ModelComponent::Draw()
{
	m_model->Draw();
}