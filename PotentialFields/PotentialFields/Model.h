#pragma once

#include "Entity.h"
#include "GraphicEngine.h"
#include <vector>


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
	Entity* GetEntityAt(unsigned int);
	XMFLOAT2 GetEntitySize();

	//not sure if this should be here
	void UpdateEntities(ID3D11DeviceContext*);

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

private:
	ID3D11Buffer *m_vertexBuffer;
	int m_vertexCount;
	XMFLOAT2 m_modelSize;
};

