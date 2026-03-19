#pragma once
namespace nsK2EngineLow
{
	enum class CanvasRenderMode
	{
		ScreenSpace,
		WorldSpace
	};

	enum class CanvasType
	{
		WorldPersistent = 0,	// 頭上HPバーや名前など
		WorldEffect,		// ダメージ数字など一時表示
		HUD,
		Menu,
		Overlay,
		DebugCanvas,
		Count
	};

	class Canvas : public Component
	{
	private:
		CanvasRenderMode m_renderMode = CanvasRenderMode::ScreenSpace;

	public:
		Canvas(CanvasRenderMode renderMode) :m_renderMode(renderMode)
		{
		}
		~Canvas() = default;
	};

}

