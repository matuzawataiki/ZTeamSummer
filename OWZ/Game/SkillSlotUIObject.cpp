#include "stdafx.h"
#include "SkillSlotUIObject.h"

void SkillSlotUIObfect::Init(float width, float height)
{
	ScreenSpaceUIObject::Init();

	m_width = width;
	m_height = height;

	AddChildren<ScreenSpaceUIObject>("icon");
	AddChildren<ScreenSpaceUIObject>("fill");
	AddChildren<ScreenSpaceUIObject>("frame");

	auto icon = std::dynamic_pointer_cast<ScreenSpaceUIObject>(GetChildren("icon"));
	auto cooldownGauge = std::dynamic_pointer_cast<ScreenSpaceUIObject>(GetChildren("fill"));
	auto frame = std::dynamic_pointer_cast<ScreenSpaceUIObject>(GetChildren("frame"));

	m_icon = icon;
	m_cooldownGauge = cooldownGauge;
	m_frame = frame;

	icon->Init("Assets/image/ui/skill/icon/.DDS", width, height);
	cooldownGauge->Init("Assets/image/ui/skill/cooldownGauge.DDS", width, height);
	frame->Init("Assets/image/ui/skill/skill_frame.DDS", width, height);

	m_cooldownGaugeTransform = cooldownGauge->GetComponent<ScreenUITransformComponent>().get();

	UpdateCooldownVisual();
}
