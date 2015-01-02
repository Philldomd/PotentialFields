#include "Graphics.h"

Graphic::Graphic()
{
	m_DirectX = 0;
}

Graphic::Graphic(const Graphic& other)
{

}

Graphic::~Graphic()
{}

bool Graphic::Initilize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;

	//Create DirectX object
	m_DirectX = new GraphicEngine;
	if(!m_DirectX)
	{
		return false;
	}

	//Init
	result = m_DirectX->Initilize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, "Could not initilize Direct X 11", "Error", MB_OK);
		return false;
	}

	return true;
}

void Graphic::Shutdown()
{
	if(m_DirectX)
	{
		m_DirectX->Shutdown();
		delete m_DirectX;
		m_DirectX = 0;
	}

	return;
}

bool Graphic::Frame()
{
	bool result;

	//Render the graphic scene
	result = Render();
	if(!result)
	{
		return false;
	}

	return true;
}

bool Graphic::Render()
{
	//Clear
	m_DirectX->BeginScene(0.5f, 0.5f, 0.5f, 1.0f);

	//Render all
	m_DirectX->EndScene();

	return true;
}