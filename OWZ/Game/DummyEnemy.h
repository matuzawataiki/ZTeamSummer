#pragma once

// 本物のEnemyが完成するまでの仮
class DummyEnemy : public GameObject
{
public:
    DummyEnemy() { m_isDead = false; }
    ~DummyEnemy() {}

private:
    bool m_isDead;

public:
    void Update() override {
        // デバッグ用：Yボタンを押したら死んだことにする
        if (g_pad[0]->IsTrigger(enButtonY)) {
            m_isDead = true;
        }
    }

    // 管理者が確認するための関数
    bool IsDead() const { return m_isDead; }
};