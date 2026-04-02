#pragma once
class StateMachineComponent;
class StateControllerComponent : public Component
{
	appClass(StateControllerComponent)
public:
	~StateControllerComponent();


protected:
	std::weak_ptr<StateMachineComponent> m_stateMachine;


};
