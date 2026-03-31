#pragma once
#include "SpriteComponent.h"
#include "UIAnimationUtil.h"

class UIColorAnimationComponent : public Component
{
	appClass(UIColorAnimationComponent);
private:
	SpriteComponent* m_sprite = nullptr;

	Vector4 m_startColor = Vector4(1, 1, 1, 1);
	Vector4 m_endColor = Vector4(1, 1, 1, 1);

	float m_duration = 1.0f;
	float m_elapsed = 0.0f;

	bool m_isPlaying = false;
	bool m_isLoop = false;

public:
	bool Start() override
	{
		//コンポーネントはシェアードポイントだけど、オーナーがいるうちは
		// コンポーネントはいるのでわざわざウィークで持たず生ポインタで受け取っている。
		// NOTE:もしコンポーネントを自由に取り外しできるようにする
		//設計に変えるなら、ここもウィークに変えないといけない。
		m_sprite = GetOwner()->GetComponent<SpriteComponent>().get();
		return true;
	}

	void Update() override
	{
		if (!m_isPlaying || m_sprite == nullptr) {
			return;
		}

		m_elapsed += g_gameTime->GetFrameDeltaTime();

		float t = (m_duration <= 0.0f) ? 1.0f : (m_elapsed / m_duration);
		float easedT = UIAnimationUtil::EaseInOutQuad(t);

		Vector4 color = UIAnimationUtil::Lerp(m_startColor, m_endColor, easedT);
		m_sprite->SetMulColor(color);

		if (t >= 1.0f) {
			if (m_isLoop) {
				m_elapsed = 0.0f;
			}
			else {
				m_isPlaying = false;
				m_sprite->SetMulColor(m_endColor);
			}
		}
	}

public:
	void Play(const Vector4& startColor, const Vector4& endColor, float duration, bool isLoop = false)
	{
		m_startColor = startColor;
		m_endColor = endColor;
		m_duration = duration;
		m_elapsed = 0.0f;
		m_isLoop = isLoop;
		m_isPlaying = true;

		if (m_sprite != nullptr) {
			m_sprite->SetMulColor(m_startColor);
		}
	}

	void Stop()
	{
		m_isPlaying = false;
	}
};