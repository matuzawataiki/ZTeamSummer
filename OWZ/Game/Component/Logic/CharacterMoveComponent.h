#pragma once

class StatusComponent;
class RigidBodyComponent;
class CharacterMoveComponent : public Component
{
	appClass(CharacterMoveComponent)
private:
	StatusComponent* m_status = nullptr;
	RigidBodyComponent* m_rigidBody = nullptr;

public:


private:
	bool Start() override;
	void Update() override;

};

