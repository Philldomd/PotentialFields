#pragma once

#include "GraphicEngine.h"

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class Graphic
{
public:
	Graphic();
	Graphic(const Graphic&);
	~Graphic();

	bool Initilize(int, int, HWND);
	void Shutdown();
	bool Frame();

private:
	bool Render();

private:

	GraphicEngine* m_DirectX;
};

