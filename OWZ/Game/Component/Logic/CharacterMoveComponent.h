#pragma once

class StatusComponent;
class CharactorColliderComponent;
class CharacterMoveComponent : public Component
{
	appClass(CharacterMoveComponent)
private:
	StatusComponent* m_status = nullptr;
	CharactorColliderComponent* m_charactorCollider = nullptr;

public:


private:
	bool Start() override;
	void Update() override;

};

