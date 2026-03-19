#pragma once
namespace nsK2EngineLow {
	class UIObject :public GameObject
	{
	private:

	public:
		UIObject()
		{
		}
		virtual ~UIObject() = default;
	};

	class ScreenSpaceUIObfect : public UIObject
	{
	private:
	public:
		ScreenSpaceUIObfect()
		{
		}
		virtual ~ScreenSpaceUIObfect() = default;
	};

	class WorldSpaceUIObfect : public UIObject
	{
	private:
	public:
		WorldSpaceUIObfect()
		{
		}
		virtual ~WorldSpaceUIObfect() = default;

	};
}

