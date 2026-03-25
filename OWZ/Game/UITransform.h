#pragma once

class UITransformBase :public Component
{
protected:
	Vector3 m_localPosition = Vector3::Zero;			//
	Vector3 m_renderPosition = Vector3::Zero;   // 最終的に表示する画面の座標。
	Vector3 m_scale = Vector3::One;
	Vector2 m_pivot = { 0.5f, 0.5f };
	Quaternion m_rotation = Quaternion::Identity;
	bool m_isDirty = true;

public:
	virtual ~UITransformBase() = default;
	virtual void UpdateTransform() = 0;

	void SetLocalPosition(const Vector3& pos)
	{
		m_localPosition = pos;
		m_isDirty = true;
	}

	void SetPivot(const Vector2& pivot)
	{
		m_pivot = pivot;
		m_isDirty = true;
	}

	void SetScale(const Vector3& size)
	{
		m_scale = size;
		m_isDirty = true;
	}

	void AddPosition(const Vector3& pos)
	{
		m_localPosition += pos;
		m_isDirty = true;
	}

	void AddScale(const Vector3& size)
	{
		m_scale += size;
		m_isDirty = true;
	}

	Vector3 GetLocalPosition() const
	{
		return m_localPosition;
	}

	Vector2 GetPivot() const
	{
		return m_pivot;
	}

	Vector3 GetScale() const
	{
		return m_scale;
	}

	Quaternion GetRotation() const
	{
		return m_rotation;
	}

	Vector3 GetRenderPosition() const
	{
		return m_renderPosition;
	}

};

class WorldUITransformComponent :public UITransformBase
{
private:
	bool    m_isVisible = true;
public:

	void UpdateTransform() override
	{
		Matrix view = g_camera3D->GetViewMatrix();
		Matrix proj = g_camera3D->GetProjectionMatrix();

		// ワールド座標をクリップ座標に変換
		Vector4 worldPos(m_localPosition.x, m_localPosition.y, m_localPosition.z, 1.0f);
		Vector4 clipPos = worldPos;
		view.Apply(clipPos);
		proj.Apply(clipPos);

		// カメラの後ろにある
		if (clipPos.w <= 0.0f)
		{
			m_isVisible = false;
			return;
		}

		// NDC座標に変換
		float invW = 1.0f / clipPos.w;
		float ndcX = clipPos.x * invW;
		float ndcY = clipPos.y * invW;
		float ndcZ = clipPos.z * invW;

		// 画面外なら非表示
		if (ndcX < -1.0f || ndcX > 1.0f ||
			ndcY < -1.0f || ndcY > 1.0f ||
			ndcZ < 0.0f || ndcZ > 1.0f)
		{
			m_isVisible = false;
			return;
		}

		m_isVisible = true;

		// NDC(-1～1) -> スクリーン座標
		m_renderPosition.x = ((ndcX + 1.0f) * 0.5f) * FRAME_BUFFER_W;
		m_renderPosition.y = ((1.0f - ndcY) * 0.5f) * FRAME_BUFFER_H;
		m_renderPosition.z = 0.0f;

		m_isDirty = false;
	}

	void Update() override
	{
		UpdateTransform();
	}

};

class ScreenUITransformComponent :public UITransformBase
{
private:


public:


	void UpdateTransform() override
	{

	}

	void Update() override
	{
	}


};
