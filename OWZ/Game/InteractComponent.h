#pragma once

enum EnInteractState {
    enIdle,         //待機
    enInteracting,  //インタラクト
    enActivated     //起動
};

class InteractComponent : public Component
{
    appClass(InteractComponent);

public:
    InteractComponent();
    ~InteractComponent();

private:
    EnInteractState m_currentState=enIdle;
    float m_interactProgressTime = 0.0f;        // 現在の長押し時間
    
    void Update();

    bool CheckPlayerDistanceAndDirection();                 // プレイヤーとの距離と向き判定

public:
    void StartInteract();
    void CancelInteract();
    bool GetIsActivated() const;
};