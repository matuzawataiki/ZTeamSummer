#pragma once
#include"UIObfect.h"

class NumberSlotUIBaseObject;
class ScreenNumberSlotUIObject;
class WorldNumberSlotUIObject;
class NumberDisplayUIBaseObject : public UIObject
{
protected:
	std::vector<std::shared_ptr<NumberSlotUIBaseObject>> m_slots;
	int m_slotCount = 1;
	int m_value = 0;

public:
	virtual ~NumberDisplayUIBaseObject() noexcept = default;

	virtual void Init(int slotCount, float slotWidth, float slotHeight, float spacing) = 0;

	void SetValue(int value);
};

class ScreenNumberDisplayUIObject : public NumberDisplayUIBaseObject
{
public:
	void Init(int slotCount, float slotWidth, float slotHeight, float spacing) override;
};

class WorldNumberDisplayUIObject : public NumberDisplayUIBaseObject
{
public:
	void Init(int slotCount, float slotWidth, float slotHeight, float spacing) override;
};