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
	bool m_isDestroyRequested = false;
public:

	UIObject()
	{
	}

	virtual ~UIObject() noexcept = default;

	void Init()
	{
		m_visualType = UIVisualType::None;
	}

	void Init(
		const char* filePath,
		float w,
		float h,
		AlphaBlendMode alphaBlendMode = AlphaBlendMode_Trans
	)
	{
		m_visualType = UIVisualType::Sprite;

		auto sprite = AddComponent<SpriteComponent>();;
		if (sprite != nullptr) {
			sprite->Init(filePath, w, h, alphaBlendMode);
		}
	}

	void Render() override
	{
		if (m_visualType == UIVisualType::None)return;

		auto sprite = GetComponent<SpriteComponent>();
		if (sprite != nullptr) {
			sprite->Render();
		}
	}

	/// <summary>
	/// このUIオブジェクトを破棄したい時に呼びます。
	/// このUIオブジェクトを消すことをリクエストします。
	/// そのリクエストを見てキャンバスが削除します。
	/// </summary>
	void RequestDestroy()
	{
		if (m_isDestroyRequested) {
			return;
		}

		m_isDestroyRequested = true;
		Deactivate();
	}

	bool IsDestroyRequested() const
	{
		return m_isDestroyRequested;
	}

	UIVisualType GetVisualType() const
	{
		return m_visualType;
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
		UIObject::Init();
		AddComponent<ScreenUITransformComponent>();
	}

	void Init(
		const char* filePath,
		float w,
		float h,
		AlphaBlendMode alphaBlendMode = AlphaBlendMode_Trans)
	{
		UIObject::Init(filePath, w, h, alphaBlendMode);

		//必要なコンポーネントを追加。
		AddComponent<ScreenUITransformComponent>();

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
		UIObject::Init();
		AddComponent<WorldUITransformComponent>();
	}

	void Init(
		const char* filePath,
		float w,
		float h,
		AlphaBlendMode alphaBlendMode = AlphaBlendMode_Trans)
	{
		UIObject::Init(filePath, w, h, alphaBlendMode);

		//必要なコンポーネントを追加。
		AddComponent<WorldUITransformComponent>();
	}

	virtual ~WorldSpaceUIObject() noexcept = default;
};



