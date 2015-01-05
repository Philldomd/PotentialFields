#include "Model.h"


Model::Model(void)
{
	int i;
	m_vertexCount = 0;
	for (i = 0; i < 100; i++)
	{
		entities.push_back(new Entity(XMFLOAT2(768, 0)));
	}
}

Model::Model(const Model& other)
{
}

Model::~Model(void)
{
}

bool Model::Initialize(ID3D11Device* device)
{
	bool result;

	// Initialize the vertex and index buffer that hold the geometry.
	result = InitilizeBuffers(device);
	if(!result)
	{
		return false;
	}

	return true;
}

void Model::Shutdown()
{
	// Release the vertex and index buffer.
	ShutdownBuffers();

	return;
}

void Model::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphic pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return;
}

int Model::GetEntityCount()
{
	return m_vertexCount;
}

bool Model::InitilizeBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	D3D11_BUFFER_DESC vertexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData;
	HRESULT result;

	m_vertexCount = entities.size();

	vertices = new VertexType[m_vertexCount];
	if(!vertices)
	{
		return false;
	}

	// Load the vertex array with data.
	XMFLOAT2 pos;
	XMFLOAT3 color;
	for (int i = 0; i < m_vertexCount; i++)
	{
		pos = entities.at(i)->getPosition();
		color = entities.at(i)->getColor();
		vertices[i].position = XMFLOAT3(pos.x, pos.y, 0.0f);  // Bottom left.
		vertices[i].color = XMFLOAT4(color.x, color.y,color.z,1.0f);
	}

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete [] vertices;
	vertices = 0;

	return true;
}

void Model::ShutdownBuffers()
{
	// Release the vertex buffer.
	if(m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}
void Model::UpdateEntities(ID3D11DeviceContext* deviceContext)
{
	//borde ha en dt också egentligen
	D3D11_MAPPED_SUBRESOURCE updateData;
	ZeroMemory(&updateData, sizeof(updateData));

	VertexType* vertices = new VertexType[m_vertexCount];

	//ta positioner från nån datastruktur som innehåller dom flyttade/ flytter på dom
	XMFLOAT2 pos;
	XMVECTOR tpos;
	XMFLOAT3 color;
	for (int i = 0; i < m_vertexCount; i++)
	{
		tpos = XMLoadFloat2( &entities.at(i)->getPosition());
		tpos += XMLoadFloat2(&entities.at(i)->getVelocity())* 1.f;
		XMStoreFloat2(&pos, tpos);

		entities.at(i)->setPosition(pos);
		color = entities.at(i)->getColor();
		vertices[i].position = XMFLOAT3(pos.x, pos.y, 0.0f);  // Bottom left.
		vertices[i].color = XMFLOAT4(color.x, color.y, color.z, 1.0f);
	}

	if (!FAILED(deviceContext->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &updateData)))
		memcpy(updateData.pData, (void**)&vertices[0], m_vertexCount * sizeof(VertexType));

	deviceContext->Unmap(m_vertexBuffer, 0);

	delete[] vertices;
	vertices = 0;
}
void Model::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;


	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType); 
	offset = 0;
    
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	return;
}