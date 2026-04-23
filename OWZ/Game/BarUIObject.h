#pragma once
#include <algorithm>
#include "UIObfect.h"

class ScreenSpaceBarUI : public ScreenSpaceUIObject
{
private:
	ScreenSpaceUIObject* m_background;
	ScreenSpaceUIObject* m_fill;
	ScreenSpaceUIObject* m_frame;

	ScreenUITransformComponent* m_fillTransform = nullptr;

	float m_maxWidth = 100.0f;
	float m_height = 16.0f;
	float m_rate = 1.0f;

public:


	void Init(
		const char* bgTex,
		const char* fillTex,
		const char* frameTex,
		float width,
		float height)
	{
		ScreenSpaceUIObject::Init(); // å©ÇΩñ⁄Ç»Çµêe

		m_maxWidth = width;
		m_height = height;

		AddChildren<ScreenSpaceUIObject>("backgroundUI");
		AddChildren<ScreenSpaceUIObject>("fillUI");
		AddChildren<ScreenSpaceUIObject>("frameUI");

		m_background = static_cast<ScreenSpaceUIObject*>(GetChildren("backgroundUI"));
		m_fill = static_cast<ScreenSpaceUIObject*>(GetChildren("fillUI"));
		m_frame = static_cast<ScreenSpaceUIObject*>(GetChildren("frameUI"));


		if (!m_background || !m_fill || !m_frame) {
			return;
		}

		m_background->Init(bgTex, width, height);
		m_fill->Init(fillTex, width, height);
		m_frame->Init(frameTex, width, height);

		auto bgTr = m_background->GetComponent<ScreenUITransformComponent>();
		m_fillTransform = m_fill->GetComponent<ScreenUITransformComponent>();
		auto frameTr = m_frame->GetComponent<ScreenUITransformComponent>();

		if (!bgTr || !m_fillTransform || !frameTr) {
			return;
		}

		// ç∂í[äÓèÄÇ≈å∏ÇÁÇµÇΩÇ¢ÇÃÇ≈ pivot Çç∂íÜâõÇ…Ç∑ÇÈ
		bgTr->SetPivot({ 0.0f, 0.5f });
		m_fillTransform->SetPivot({ 0.0f, 0.5f });
		frameTr->SetPivot({ 0.0f, 0.5f });

		bgTr->SetLocalPosition({ 0.0f, 0.0f, 0.0f });
		m_fillTransform->SetLocalPosition({ 0.0f, 0.0f, 0.0f });
		frameTr->SetLocalPosition({ 0.0f, 0.0f, 0.0f });

		bgTr->SetScale({ width, height, 1.0f });
		m_fillTransform->SetScale({ width, height, 1.0f });
		frameTr->SetScale({ width, height, 1.0f });

		SetRate(1.0f);
	}

	void SetRate(float rate)
	{
		if (rate < 0.0f) {
			rate = 0.0f;
		}
		else if (rate > 1.0f) {
			rate = 1.0f;
		}

		m_rate = rate;

		if (m_fillTransform == nullptr) {
			return;
		}

		// â°ïùÇäÑçáÇ≈ïœçX
		m_fillTransform->SetScale({ m_maxWidth * m_rate, m_height, 1.0f });
	}

	float GetRate() const
	{
		return m_rate;
	}
};

class WorldSpaceBarUI : public WorldSpaceUIObject
{
private:
	WorldSpaceUIObject* m_background;
	WorldSpaceUIObject* m_fill;
	WorldSpaceUIObject* m_frame;

	WorldUITransformComponent* m_fillTransform = nullptr;

	float m_maxWidth = 100.0f;
	float m_height = 16.0f;
	float m_rate = 1.0f;

public:
	void Init(
		const char* bgTex,
		const char* fillTex,
		const char* frameTex,
		float width,
		float height)
	{
		WorldSpaceUIObject::Init();

		m_maxWidth = width;
		m_height = height;

		AddChildren<WorldSpaceUIObject>("backgroundUI");
		AddChildren<WorldSpaceUIObject>("fillUI");
		AddChildren<WorldSpaceUIObject>("frameUI");

		m_background = static_cast<WorldSpaceUIObject*>(GetChildren("backgroundUI"));
		m_fill = static_cast<WorldSpaceUIObject*>(GetChildren("fillUI"));
		m_frame = static_cast<WorldSpaceUIObject*>(GetChildren("frameUI"));


		if (!m_background || !m_fill || !m_frame) {
			return;
		}

		m_background->Init(bgTex, width, height);
		m_fill->Init(fillTex, width, height);
		m_frame->Init(frameTex, width, height);

		auto bgTr = m_background->GetComponent<WorldUITransformComponent>();
		m_fillTransform = m_fill->GetComponent<WorldUITransformComponent>();
		auto frameTr = m_frame->GetComponent<WorldUITransformComponent>();

		if (!bgTr || !m_fillTransform || !frameTr) {
			return;
		}

		bgTr->SetPivot({ 0.0f, 0.5f });
		m_fillTransform->SetPivot({ 0.0f, 0.5f });
		frameTr->SetPivot({ 0.0f, 0.5f });

		bgTr->SetLocalPosition({ 0.0f, 0.0f, 0.0f });
		m_fillTransform->SetLocalPosition({ 0.0f, 0.0f, 0.0f });
		frameTr->SetLocalPosition({ 0.0f, 0.0f, 0.0f });

		bgTr->SetScale({ width, height, 1.0f });
		m_fillTransform->SetScale({ width, height, 1.0f });
		frameTr->SetScale({ width, height, 1.0f });

		SetRate(1.0f);
	}

	void SetRate(float rate)
	{
		if (rate < 0.0f) {
			rate = 0.0f;
		}
		else if (rate > 1.0f) {
			rate = 1.0f;
		}

		m_rate = rate;

		if (m_fillTransform == nullptr) {
			return;
		}

		m_fillTransform->SetScale({ m_maxWidth * m_rate, m_height, 1.0f });
	}

	float GetRate() const
	{
		return m_rate;
	}
};


