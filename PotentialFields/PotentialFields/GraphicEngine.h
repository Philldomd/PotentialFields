#pragma once

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

#include <dxgi.h>
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

class GraphicEngine
{
public:
	GraphicEngine();
	GraphicEngine(const GraphicEngine&);
	~GraphicEngine();

	bool Initialize(int, int, bool, HWND, bool, float, float);
	void Shutdown();

	void BeginScene(float, float, float, float);
	void EndScene();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

	void GetProjectionMatrix(XMFLOAT4X4&);
	void GetWorldMatrix(XMFLOAT4X4&);
	void GetOrthoMatrix(XMFLOAT4X4&);

	void GetVideoCardInfo(char*, int&);

private:
	bool m_vsync_enabled;
	int m_videoCardMemory;
	char m_videoCardDescription[128];
	IDXGISwapChain* m_swapChain;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
	ID3D11RenderTargetView* m_renderTargetView;
	ID3D11Texture2D* m_depthStencilBuffer;
	ID3D11DepthStencilState* m_depthStencilState;
	ID3D11DepthStencilView* m_depthStencilView;
	ID3D11RasterizerState* m_rasterState;
	XMFLOAT4X4 m_projectionMatrix;
	XMFLOAT4X4 m_worldMatrix;
	XMFLOAT4X4 m_orthoMatrix;
};
