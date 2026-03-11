#pragma once
struct ForwardLight
{
	Vector3 direction	= Vector3::Zero;
	int pad1 = 0;
	Vector4 color		= Vector4::White;
	int pad2 = 0;
	Vector3 position	= Vector3::Zero;
	int pad3 = 0;
	Vector3 ambientcolor = Vector3::Zero;
	int pad4 = 0;
};

class ViewModelComponent : public Component
{
	appClass(ViewModelComponent);

public:
	~ViewModelComponent();

private:
	std::unique_ptr<ModelRender> m_model;
	std::vector<AnimationData> m_animationData;
	AllocatedArray<AnimationClip> m_animations;
	Skeleton m_skeleton;
	ForwardLight m_forwardLight;

	bool m_isDraw = false;

public:
	void SetModel(const char* filePath, bool isAnimation = false);

	void AddAnimation(const char* filePath,bool loopFlag = true);

	void Draw();

	void SetDrawFlag(bool drawFlag) {
		m_isDraw = drawFlag;
	}

	bool IsDraw() const {
		return m_isDraw;
	}
};

