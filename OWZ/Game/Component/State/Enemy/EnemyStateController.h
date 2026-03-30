#pragma once
#include "Component/State/StateControllerComponent.h"
#include "InGameObject/Character/Enemy/EnemyType.h"

class EnemyParameter;
class StateMachineComponent;


class EnemyStateController : public StateControllerComponent
{
	appClass(EnemyStateController);
public:
	EnemyStateController();
	~EnemyStateController();


	/** 敵の種類に応じた初期設定 */
	void SetupEnemy(EnemyType type);


	/** 更新処理 */
	void Update();


	/** 種類を返す */
	EnemyType GetEnemyType() const { return m_enemyType; }


	const EnemyParameter* GetCurrentEnemyParameter() const { return GetEnemyParameter(m_enemyType); }


private:
	/** エネミーの列挙型のタイプをここに持ってくる */
	EnemyType m_enemyType = EnemyType::Walk;
	const EnemyParameter* m_parameter = nullptr;


	/** プレイヤーが見つけたかどうか */
	bool CanSeePlayer() const;


	std::string EnemyTypeToString(EnemyType type) const;


	const EnemyParameter* GetEnemyParameter(EnemyType type)const;
};