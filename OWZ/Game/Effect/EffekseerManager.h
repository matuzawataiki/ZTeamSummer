#pragma once

//エフェクトを追加する
enum class eEffectType{
	//例）Explosion=100,
};

class EffekseerManager
{
	private:
		EffekseerManager(){}
		~EffekseerManager() {}

		//再生中のエフェクトハンドルを記憶するリスト
		std::vector<int>m_playingHandles;

public:
	static EffekseerManager* GetInstance()
	{
		static EffekseerManager instance;
		return &instance;
	}

	//ゲーム開始時によく使うエフェクトを一括登録する
	void LoadAllEffects();

	//名前でエフェクトを再生する
	int Play(eEffectType type, const Vector3&pos);

	//再生中のエフェクトを全て消去する
	void StopAll();
};

