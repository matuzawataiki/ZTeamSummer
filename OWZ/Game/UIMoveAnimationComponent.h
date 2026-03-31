#pragma once
#include "UITransform.h"
#include "UIAnimationUtil.h"

class UIMoveAnimationComponent : public Component
{
	appClass(UIMoveAnimationComponent);
private:
	UITransformBase* m_transform = nullptr;

	Vector3 m_startPosition = Vector3::Zero;
	Vector3 m_endPosition = Vector3::Zero;

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

		Vector3 pos = UIAnimationUtil::Lerp(m_startPosition, m_endPosition, easedT);
		m_transform->SetLocalPosition(pos);

		if (t >= 1.0f) {
			if (m_isLoop) {
				m_elapsed = 0.0f;
			}
			else {
				m_isPlaying = false;
				m_transform->SetLocalPosition(m_endPosition);
			}
		}
	}

public:
	void Play(const Vector3& startPos, const Vector3& endPos, float duration, bool isLoop = false)
	{
		m_startPosition = startPos;
		m_endPosition = endPos;
		m_duration = duration;
		m_elapsed = 0.0f;
		m_isLoop = isLoop;
		m_isPlaying = true;

		if (m_transform != nullptr) {
			m_transform->SetLocalPosition(m_startPosition);
		}
	}

	void Stop()
	{
		m_isPlaying = false;
	}

	bool IsPlaying() const
	{
		return m_isPlaying;
	}
};