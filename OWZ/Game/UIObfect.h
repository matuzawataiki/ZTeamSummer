#pragma once
#include"UITransform.h"
#include"SpriteComponent.h"

enum class UIVisualType
{
	None,// 見た目なし。(子のUIを持つだけのオブジェクトなど)
	Sprite
};

class UIObject :public nsK2EngineLow::GameObject
{
protected:
	UIVisualType m_visualType = UIVisualType::Sprite;
public:

	UIObject()
	{
	}

	virtual ~UIObject() noexcept = default;

	void Init(UIVisualType visualType = UIVisualType::Sprite)
	{
		m_visualType = visualType;
	}
};

class ScreenSpaceUIObject : public UIObject
{
private:

public:
	ScreenSpaceUIObject()
	{
	}

	void Init()
	{
		UIObject::Init(UIVisualType::None);
		AddComponent<ScreenUITransformComponent>();
	}

	void Init(
		const char* filePath,
		float w,
		float h,
		AlphaBlendMode alphaBlendMode = AlphaBlendMode_Trans)
	{
		UIObject::Init(UIVisualType::Sprite);

		//必要なコンポーネントを追加。
		AddComponent<ScreenUITransformComponent>();
		AddComponent<SpriteComponent>();

		auto sprite = GetComponent<SpriteComponent>();
		if (sprite != nullptr) {
			sprite->Init(filePath, w, h, alphaBlendMode);
		}
	}

	bool Start() override
	{

		return true;
	}

	void Render() override
	{
		auto sprite = GetComponent<SpriteComponent>();
		if (sprite != nullptr) {
			sprite->Render();
		}
	}

	virtual ~ScreenSpaceUIObject() noexcept = default;
};

class WorldSpaceUIObject : public UIObject
{
private:

public:

	WorldSpaceUIObject()
	{
	}

	void Init()
	{
		UIObject::Init(UIVisualType::None);
		AddComponent<WorldUITransformComponent>();
	}

	void Init(
		const char* filePath,
		float w,
		float h,
		AlphaBlendMode alphaBlendMode = AlphaBlendMode_Trans)
	{
		UIObject::Init(UIVisualType::Sprite);

		//必要なコンポーネントを追加。
		AddComponent<WorldUITransformComponent>();
		AddComponent<SpriteComponent>();

		auto sprite = GetComponent<SpriteComponent>();
		if (sprite != nullptr) {
			sprite->Init(filePath, w, h, alphaBlendMode);
		}

	}

	bool Start() override
	{
		return true;
	}

	void Render() override
	{
		auto sprite = GetComponent<SpriteComponent>();
		if (sprite != nullptr) {
			sprite->Render();
		}
	}

	virtual ~WorldSpaceUIObject() noexcept = default;
};



