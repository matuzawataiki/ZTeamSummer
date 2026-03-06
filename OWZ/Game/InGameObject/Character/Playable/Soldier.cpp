#include "stdafx.h"
#include "Soldier.h"
#include "Component/Graphics/ViewModelComponent.h"

Soldier::Soldier()
{
	AddComponent<ViewModelComponent>();
}

Soldier::~Soldier()
{
}