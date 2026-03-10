#pragma once
class Transform
{
public:
	Transform();
	~Transform();

private:
	Vector3		m_localPosition = Vector3::Zero;
	Quaternion	m_localRotation = Quaternion::Identity;
	Vector3		m_localScale = Vector3::One;

	std::shared_ptr<Transform> m_parent;
	std::vector<std::shared_ptr<Transform>> m_children;

	Matrix m_worldMatrix;
	bool m_isDirty;

public:
	void Update()  {
		if (m_isDirty) {
			UpdateWorldMatrix();
			m_isDirty = false;
		}
	}

	void SetDirty() {
		if (!m_isDirty) {
			m_isDirty = true;
			for (auto childern : m_children) {
				childern->SetDirty();
			}
		}
	}

	Vector3 GetLocalPosition() const { return m_localPosition; }
	void SetLocalPosition(const Vector3& position) {
		m_localPosition.Set(position);
		SetDirty();
	}
	void AddLocalPsition(const Vector3& position) {
		m_localPosition.Add(position);
		SetDirty();
	}

	Quaternion GetLocalRotation() const { return m_localRotation; }
	void SetLocalRotation(const Quaternion& rotation) {
		m_localRotation.Set(rotation);
		SetDirty();
	}
	void AddLocalRotation(const Quaternion& rotation) {
		m_localRotation.Add(rotation);
		SetDirty();
	}

	Vector3 GetLocalScale() const { return m_localScale; }
	void SetLocalScale(const Vector3& scale) {
		m_localScale.Set(scale);
		SetDirty();
	}
	void AddLocalScale(const Vector3& scale) {
		m_localScale.Add(scale);
		SetDirty();
	}

	void SetParent(std::shared_ptr<Transform> parent, std::shared_ptr<Transform> children);

	std::shared_ptr<Transform> GetParent()const { return m_parent; }

	Matrix GetLocalMatrix() {
		Matrix tMatrix, rMatrix, sMatrix;
		tMatrix.MakeTranslation(m_localPosition);
		rMatrix.MakeRotationFromQuaternion(m_localRotation);
		sMatrix.MakeScaling(m_localScale);
		return tMatrix * rMatrix * sMatrix;
	}

	Matrix GetWorldMatrix() {
		Update();
		return m_worldMatrix;
	}

	void UpdateWorldMatrix() {
		if (m_parent) {
			m_worldMatrix = m_parent->GetWorldMatrix() * GetLocalMatrix();
		}
		else {
			m_worldMatrix = GetLocalMatrix();
		}
	}

	Vector3 GetPosition() {
		Update();
		return m_worldMatrix.GetTranslation();
	}

	Quaternion GetRotation() {
		Update();
		return m_worldMatrix.GetRotation();
	}

	Vector3 GetScale() {
		Update();
		return m_worldMatrix.GetScale();
	}

};

