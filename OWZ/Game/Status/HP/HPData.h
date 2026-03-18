#pragma once


class HPData
{
public:
	HPData();
	~HPData();


	struct HPLayer
	{
		float m_currentHP;
		float m_maxHP;
	};


private:
	HPLayer m_overHP;		// 追加ライフ
	HPLayer m_shieldHP;		// シールド
	HPLayer m_armorHP;		// アーマー
	HPLayer m_baseHP;		// ライフ

	bool m_isDead = false;	// 死亡判定


public:
	/** HPの初期化(Jsonファイルから読み込んだ値をセット) */
	void Initialize(float base,float armor,float shield);


	/** ダメージを受ける処理 */
	void ApplyDamage(float damageAmount);


	/** 回復する処理 */
	void ApplyHeal(float healAmount);


	/** シールドやアーマー、追加ライフを考慮してダメージを処理する */
	float ProcessDamage(HPLayer& hplayer , float damageAmount);


	/** 死亡しているかの確認 */
	bool IsDead() const { return m_isDead; }


	/** 現在のHPの取得 */
	float GetCurrentHP() const { return m_baseHP.m_currentHP; }


	/** 最大HPの取得 */
	float GetMaxHP() const { return m_baseHP.m_maxHP; }


};