#pragma once
#include "Canvas.h"

class Canvas;
class UIFactory
{
public:
	static GameObject* CreateScreenCanvas() {
		GameObject* canvas = new GameObject();
		canvas->AddComponent<Canvas>(CanvasRenderMode::ScreenSpace);
		return canvas;
	}
	static GameObject* CreateWorldCanvas() {
		GameObject* canvas;
		canvas->AddComponent<Canvas>(CanvasRenderMode::WorldSpace);
		return canvas;
	}
};


