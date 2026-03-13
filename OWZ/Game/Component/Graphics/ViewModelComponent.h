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

struct AnimationData
{
	const char* filePath;
	bool loopFlag;

	AnimationData(const char* f, bool l) :filePath(f),loopFlag(l){}

};

class ViewModelComponent : public Component
{
	appClass(ViewModelComponent);

private:
	std::unique_ptr<ModelRender> m_model;
	std::vector<AnimationData> m_animationData;
	AllocatedArray<AnimationClip> m_animations;
	ForwardLight m_forwardLight;

	bool m_drawFlag = false;

public:
	~ViewModelComponent();

	void Update() override;

	void SetModel(const char* filePath, bool isAnimation = false);

	void AddAnimation(const char* filePath,bool loopFlag = true);

	void PlayAnimation(int num);

	void Draw();

	void SetDrawFlag(bool drawFlag) {
		m_drawFlag = drawFlag;
	}

	bool IsDraw() const {
		return m_drawFlag;
	}
};

