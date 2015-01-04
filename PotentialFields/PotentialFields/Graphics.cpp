#include "Graphics.h"

Graphic::Graphic()
{
	m_DirectX = 0;
	m_Camera = 0;
	m_Model = 0;
	m_ShaderModel = 0;
}

Graphic::Graphic(const Graphic& other)
{

}

Graphic::~Graphic()
{}

bool Graphic::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;


	// Create the Direct3D object.
	m_DirectX = new GraphicEngine;
	if(!m_DirectX)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_DirectX->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new Camera;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -20.0f);
	
	// Create the model object.
	m_Model = new Model;
	if(!m_Model)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Model->Initialize(m_DirectX->GetDevice());
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the color shader object.
	m_ShaderModel = new ShaderModel;
	if(!m_ShaderModel)
	{
		return false;
	}

	// Initialize the color shader object.
	result = m_ShaderModel->Initialize(m_DirectX->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}

void Graphic::Shutdown()
{
	// Release the color shader object.
	if(m_ShaderModel)
	{
		m_ShaderModel->Shutdown();
		delete m_ShaderModel;
		m_ShaderModel = 0;
	}

	// Release the model object.
	if(m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}
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
	XMFLOAT4X4 viewMatrix, projectionMatrix, worldMatrix;
	bool result;


	// Clear the buffers to begin the scene.
	m_DirectX->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_DirectX->GetWorldMatrix(worldMatrix);
	m_DirectX->GetProjectionMatrix(projectionMatrix);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Model->Render(m_DirectX->GetDeviceContext());

	// Render the model using the color shader.
	result = m_ShaderModel->Render(m_DirectX->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
	if(!result)
	{
		return false;
	}

	m_DirectX->EndScene();

	return true;
}