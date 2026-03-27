#pragma once
#include "SoundTypes.h"


//サウンド用のハンドル名
using SoundHandle = uint32_t;
//無効なハンドル値
static constexpr SoundHandle INVALID_SOUND_HANDLE = 0xffffffff;

class SoundManager
{
private:
	//BMG用のサウンドソースインスタンスを保持
	SoundSource* m_bgm = nullptr;
	// SE用のサウンドソースインスタンスを保持
	std::map<SoundHandle, SoundSource*> m_seList;

	SoundHandle m_soundHandleCount = 0;


private:
	SoundManager();
	~SoundManager();


public:

	void Update();


public:

	void PlayBGM(const SoundKind kind);

	void StopBGM();

	SoundHandle PlaySE(const SoundKind kind, const bool isLood = false, const bool is3D = false);

	void StopSE(const SoundHandle handle);


	SoundSource* FindSE(const SoundHandle handle)
	{
		auto it = m_seList.find(handle);
		if (it != m_seList.end()) {
			return it->second;
		}
		K2_ASSERT(false, "削除済みか追加されていないSEにアクセスしようとしています。\n");
		return nullptr;
	}

public:

	static void CreateInstance()
	{
		if (m_instance == nullptr)
		{
			m_instance = new SoundManager();
		}
	}

	static SoundManager& Get()
	{
		return *m_instance;
	}

	static void DestroyInstance()
	{
		if (m_instance != nullptr)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}

private:

	static SoundManager* m_instance;
};

