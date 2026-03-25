#pragma once
#include <algorithm>
#include "UIObfect.h"

class ScreenSpaceBarUI : public ScreenSpaceUIObject
{
private:
	std::weak_ptr<ScreenSpaceUIObject> m_background;
	std::weak_ptr<ScreenSpaceUIObject> m_fill;
	std::weak_ptr<ScreenSpaceUIObject> m_frame;

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

		m_background = std::dynamic_pointer_cast<ScreenSpaceUIObject>(GetChildren("backgroundUI"));
		m_fill = std::dynamic_pointer_cast<ScreenSpaceUIObject>(GetChildren("fillUI"));
		m_frame = std::dynamic_pointer_cast<ScreenSpaceUIObject>(GetChildren("frameUI"));


		auto bg = m_background.lock();
		auto fill = m_fill.lock();
		auto frame = m_frame.lock();

		if (!bg || !fill || !frame) {
			return;
		}

		bg->Init(bgTex, width, height);
		fill->Init(fillTex, width, height);
		frame->Init(frameTex, width, height);

		auto bgTr = bg->GetComponent<ScreenUITransformComponent>();
		auto fillTr = fill->GetComponent<ScreenUITransformComponent>();
		auto frameTr = frame->GetComponent<ScreenUITransformComponent>();

		if (!bgTr || !fillTr || !frameTr) {
			return;
		}

		m_fillTransform = fillTr.get();

		// ç∂í[äÓèÄÇ≈å∏ÇÁÇµÇΩÇ¢ÇÃÇ≈ pivot Çç∂íÜâõÇ…Ç∑ÇÈ
		bgTr->SetPivot({ 0.0f, 0.5f });
		fillTr->SetPivot({ 0.0f, 0.5f });
		frameTr->SetPivot({ 0.0f, 0.5f });

		bgTr->SetLocalPosition({ 0.0f, 0.0f, 0.0f });
		fillTr->SetLocalPosition({ 0.0f, 0.0f, 0.0f });
		frameTr->SetLocalPosition({ 0.0f, 0.0f, 0.0f });

		bgTr->SetScale({ width, height, 1.0f });
		fillTr->SetScale({ width, height, 1.0f });
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
	std::weak_ptr<WorldSpaceUIObject> m_background;
	std::weak_ptr<WorldSpaceUIObject> m_fill;
	std::weak_ptr<WorldSpaceUIObject> m_frame;

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

		m_background = std::dynamic_pointer_cast<WorldSpaceUIObject>(GetChildren("backgroundUI"));
		m_fill = std::dynamic_pointer_cast<WorldSpaceUIObject>(GetChildren("fillUI"));
		m_frame = std::dynamic_pointer_cast<WorldSpaceUIObject>(GetChildren("frameUI"));

		auto bg = m_background.lock();
		auto fill = m_fill.lock();
		auto frame = m_frame.lock();

		if (!bg || !fill || !frame) {
			return;
		}

		bg->Init(bgTex, width, height);
		fill->Init(fillTex, width, height);
		frame->Init(frameTex, width, height);

		auto bgTr = bg->GetComponent<WorldUITransformComponent>();
		auto fillTr = fill->GetComponent<WorldUITransformComponent>();
		auto frameTr = frame->GetComponent<WorldUITransformComponent>();

		if (!bgTr || !fillTr || !frameTr) {
			return;
		}

		m_fillTransform = fillTr.get();

		bgTr->SetPivot({ 0.0f, 0.5f });
		fillTr->SetPivot({ 0.0f, 0.5f });
		frameTr->SetPivot({ 0.0f, 0.5f });

		bgTr->SetLocalPosition({ 0.0f, 0.0f, 0.0f });
		fillTr->SetLocalPosition({ 0.0f, 0.0f, 0.0f });
		frameTr->SetLocalPosition({ 0.0f, 0.0f, 0.0f });

		bgTr->SetScale({ width, height, 1.0f });
		fillTr->SetScale({ width, height, 1.0f });
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


