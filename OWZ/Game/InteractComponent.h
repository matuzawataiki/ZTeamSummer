#pragma once

enum EnInteractState {
    enIdle,         //待機
    enInteracting,  //インタラクト
    enActivated     //起動
};

class InteractComponent : public Component
{
public:
    InteractComponent();
    ~InteractComponent();

private:
    EnInteractState m_currentState=enIdle;
    float m_interactProgressTime = 0.0f;        // 現在の長押し時間
    const float REQUIRED_INTERACT_TIME = 2.0f;  // 起動に必要な時間
    float m_interactableDistance = 50.0f;       // アクセス可能な距離
    
    bool CheckPlayerDistance();                 // プレイヤーとの距離判定

public:
    void Update();
    void StartInteract();
    void CancelInteract();
    bool GetIsActivated() const;
};