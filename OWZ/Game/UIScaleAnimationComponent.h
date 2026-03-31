#pragma once
#include "UITransform.h"
#include "UIAnimationUtil.h"

class UIScaleAnimationComponent : public Component
{
	appClass(UIScaleAnimationComponent);
private:

	UITransformBase* m_transform = nullptr;

	Vector3 m_startScale = Vector3::One;
	Vector3 m_endScale = Vector3::One;

	float m_duration = 1.0f;
	float m_elapsed = 0.0f;

	bool m_isPlaying = false;
	bool m_isLoop = false;

public:
	bool Start() override
	{
		//コンポーネントはシェアードポイントだけど、オーナーがいるうちは
		// コンポーネントはいるのでわざわざウィークで持たず生ポインタで受け取っている。
		m_transform = GetOwner()->GetComponent<UITransformBase>().get();
		return true;
	}

	void Update() override
	{
		if (!m_isPlaying || m_transform == nullptr) {
			return;
		}

		m_elapsed += g_gameTime->GetFrameDeltaTime();

		float t = (m_duration <= 0.0f) ? 1.0f : (m_elapsed / m_duration);
		float easedT = UIAnimationUtil::EaseOutQuad(t);

		Vector3 scale = UIAnimationUtil::Lerp(m_startScale, m_endScale, easedT);
		m_transform->SetScale(scale);

		if (t >= 1.0f) {
			if (m_isLoop) {
				m_elapsed = 0.0f;
			}
			else {
				m_isPlaying = false;
				m_transform->SetScale(m_endScale);
			}
		}
	}

public:
	void Play(const Vector3& startScale, const Vector3& endScale, float duration, bool isLoop = false)
	{
		m_startScale = startScale;
		m_endScale = endScale;
		m_duration = duration;
		m_elapsed = 0.0f;
		m_isLoop = isLoop;
		m_isPlaying = true;

		if (m_transform != nullptr) {
			m_transform->SetScale(m_startScale);
		}
	}

	void Stop()
	{
		m_isPlaying = false;
	}
};