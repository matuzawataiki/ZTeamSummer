#include "stdafx.h"
#include "SpriteComponent.h"
#include "UITransform.h"

bool SpriteComponent::Start()
{
	m_transform = GetOwner()->GetComponent<UITransformBase>();
	return true;
}

void SpriteComponent::Update()
{
	auto transform = m_transform.lock();
	if (!transform) {
		return;
	}


	// Transform‚Ì’l‚ğSpriteRender‚Ö”½‰f
	m_spriteRender.SetPosition(transform->GetRenderPosition());
	m_spriteRender.SetRotation(transform->GetRotation());
	m_spriteRender.SetScale(transform->GetScale());

	// Œ©‚½–Úİ’è
	m_spriteRender.SetPivot(m_pivot);
	m_spriteRender.SetMulColor(m_mulColor);

	m_spriteRender.Update();
}