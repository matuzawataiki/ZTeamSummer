#pragma once
#include "CanvasComponent.h"
namespace nsK2EngineLow
{
	class CanvasComponent;
	class UIFactory
	{
	public:
		static GameObject* CreateScreenCanvas() {
			GameObject* canvas = new GameObject();
			canvas->AddComponent<CanvasComponent>(CanvasRenderMode::ScreenSpace);
			return canvas;
		}
		static GameObject* CreateWorldCanvas() {
			GameObject* canvas;
			canvas->AddComponent<CanvasComponent>(CanvasRenderMode::WorldSpace);
			return canvas;
		}
	};
}

