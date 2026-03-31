#pragma once

class UITransformBase;
class SpriteComponent : public Component
{
	appClass(SpriteComponent);
public:
	void Init(const char* filePath, float w, float h,
		AlphaBlendMode alphaBlendMode = AlphaBlendMode_Trans)
	{
		m_spriteRender.Init(filePath, w, h, alphaBlendMode);
	}

	bool Start() override;

	void Update() override;

	void Render()
	{
		if (!m_isVisible) {
			return;
		}
		m_spriteRender.Draw();
	}

	void SetPivot(const Vector2& pivot)
	{
		m_pivot = pivot;
	}

	const Vector2& GetPivot() const
	{
		return m_pivot;
	}

	void SetMulColor(const Vector4& color)
	{
		m_mulColor = color;
	}

	const Vector4& GetMulColor() const
	{
		return m_mulColor;
	}

	void SetVisible(bool isVisible)
	{
		m_isVisible = isVisible;
	}

	bool IsVisible() const
	{
		return m_isVisible;
	}

private:
	SpriteRender         m_spriteRender;
	std::weak_ptr<UITransformBase> m_transform;

	Vector2              m_pivot = Sprite::DEFAULT_PIVOT;
	Vector4              m_mulColor = Vector4::White;
	bool                 m_isVisible = true;
};











