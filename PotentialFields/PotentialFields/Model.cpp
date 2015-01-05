#include "Model.h"


Model::Model(void)
{
	m_vertexCount = 0;
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

	m_vertexCount = 4;

	vertices = new VertexType[m_vertexCount];
	if(!vertices)
	{
		return false;
	}

	// Load the vertex array with data.
	vertices[0].position = XMFLOAT3(250.0f, 400.0f, 0.0f);  // Bottom left.
	vertices[0].color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);

	vertices[1].position = XMFLOAT3(1000.0f, 700.0f, 0.0f);  // Top middle.
	vertices[1].color = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

	vertices[2].position = XMFLOAT3(1.0f, 500.0f, 0.0f);  // Bottom right.
	vertices[2].color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);

	vertices[3].position = XMFLOAT3(1.0f, 1.0f, 0.0f);  // Top middle.
	vertices[3].color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);

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
	D3D11_MAPPED_SUBRESOURCE updateData;
	ZeroMemory(&updateData, sizeof(updateData));

	VertexType* vertices = new VertexType[m_vertexCount];

	//ta positioner från nån datastruktur som innehåller dom flyttade/ flytter på dom
	vertices[0].position = XMFLOAT3(250.0f, 400.0f, 0.0f);  // Bottom left.
	vertices[0].color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);

	vertices[1].position = XMFLOAT3(1000.0f, 700.0f, 0.0f);  // Top middle.
	vertices[1].color = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

	vertices[2].position = XMFLOAT3(1.0f, 500.0f, 0.0f);  // Bottom right.
	vertices[2].color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);

	vertices[3].position = XMFLOAT3(1.0f, 1.0f, 0.0f);  // Top middle.
	vertices[3].color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);

	if (!FAILED(deviceContext->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &updateData)))
		memcpy(updateData.pData, (void**)&vertices[0], 4 * sizeof(VertexType));

	deviceContext->Unmap(m_vertexBuffer, 0);
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