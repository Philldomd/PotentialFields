#pragma once

#include "Entity.h"
#include <d3d11.h>
#include <DirectXMath.h>
#include <vector>


using namespace DirectX;

class Model
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
	};
	std::vector<Entity*> entities;
public:
	Model();
	Model(const Model&);
	~Model();

	bool Initialize(ID3D11Device*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetEntityCount();

	//not sure if this should be here
	void UpdateEntities(ID3D11DeviceContext*);

private:
	bool InitilizeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

private:
	ID3D11Buffer *m_vertexBuffer;
	int m_vertexCount;
};

