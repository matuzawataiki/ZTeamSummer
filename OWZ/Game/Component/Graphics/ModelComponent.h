#pragma once


class ModelComponent : public Component
{
	appClass(ModelComponent);

public:
	~ModelComponent();

private:
	std::unique_ptr<ModelRender>m_model;
	std::vector<AnimationData>m_animationData;
	AllocatedArray<AnimationClip> m_animations;

	bool m_isDraw = false;

public:
	void SetModel(const char* filePath, bool isAnimation = false);

	void AddAnimation(const char* filePath, bool loopFlag = true);

	void Draw();

	void SetDrawFlag(bool drawFlag) {
		m_isDraw = drawFlag;
	}

	bool IsDraw()const {
		return m_isDraw;
	}

	void SetPosition(const Vector3& position) {
		if (m_model) {
			m_model->SetPosition(position);
			m_model->Update(); // 座標を変えたらUpdateを呼ぶ
		}
	}

	Model& GetModel() { return m_model->GetModel(); }

private:
	void Update() override;
};

