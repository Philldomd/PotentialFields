#include "Grid.h"

Grid::Grid()
{
	m_gridDim = XMFLOAT2(10.f, 10.f);
	for (int y = 0; y < 76; y++)
	{
		for (int x = 0; x < 102; x++)
		{
			m_cells.push_back(new Cell(XMFLOAT3(x*m_gridDim.x, y*m_gridDim.y, 0.f), XMFLOAT3(0.0f, 0.0f, 0.0f), m_gridDim));
		}
	}
}

Grid::~Grid()
{
	
}

void Grid::Shutdown()
{
	for (unsigned int i = 0; i < m_cells.size(); i++)
		delete m_cells[i];
	ShutdownBuffer();
	return;
}

void Grid::ShutdownBuffer()
{
	// Release the vertex buffer.
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}

bool Grid::Initialize(ID3D11Device* device)
{
	bool result;

	// Initialize the vertex and index buffer that hold the geometry.
	result = InitializeBuffer(device);
	if (!result)
	{
		return false;
	}

	return true;
}

bool Grid::InitializeBuffer(ID3D11Device* device)
{
	VertexType* vertices;
	D3D11_BUFFER_DESC vertexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData;
	HRESULT result;

	m_cellCount = m_cells.size();

	vertices = new VertexType[m_cellCount];
	if (!vertices)
	{
		return false;
	}

	// Load the vertex array with data.
	XMFLOAT3 pos;
	XMFLOAT3 color;
	for (unsigned int i = 0; i < m_cellCount; i++)
	{
		pos = m_cells.at(i)->getPosition();
		color = m_cells.at(i)->getColor();
		vertices[i].position = XMFLOAT3(pos.x, pos.y, pos.z);  // Bottom left.
		vertices[i].color = XMFLOAT4(color.x, color.y, color.z, 1.0f);
	}

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(VertexType)* m_cellCount;
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
	if (FAILED(result))
	{
		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;

	return true;
}

void Grid::Render(ID3D11DeviceContext* deviceContext)
{
	RenderBuffer(deviceContext);

	return;
}

void Grid::Update(VIEWS views,ID3D11DeviceContext* deviceContext)
{
	//borde ha en dt också egentligen
	D3D11_MAPPED_SUBRESOURCE updateData;
	ZeroMemory(&updateData, sizeof(updateData));

	VertexType* vertices = new VertexType[m_cellCount];


	//ta positioner från nån datastruktur som innehåller dom flyttade/ flytter på dom
	XMFLOAT3 pos;
	XMFLOAT3 color = XMFLOAT3(0,0,0);
	for (unsigned int i = 0; i < m_cellCount; i++)
	{
		pos = m_cells.at(i)->getPosition();
		if (views == VIEWS::FIELD)
			color = m_cells.at(i)->getColor();
		if (views == VIEWS::VEL)
		{
		//	XMVECTOR temp = XMVectorSet(1, 1,1,1);
		//	
		//	XMVECTOR vcol = XMLoadFloat2(&m_cells.at(i)->velocity);
		//	vcol += temp;
		//	vcol *= 0.5f;
			color.x = m_cells.at(i)->velocity.x;
			color.y = m_cells.at(i)->velocity.y;
		//	XMFLOAT2 tempc;
		//	XMStoreFloat2(&tempc, vcol);
		//	color = XMFLOAT3(tempc.x,tempc.y,0); //m_cells.at(i)->velocity;
		}
		vertices[i].position = pos;  // Bottom left.
		vertices[i].color = XMFLOAT4(color.x, color.y, color.z, 1.0f);
	}

	if (!FAILED(deviceContext->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &updateData)))
		memcpy(updateData.pData, (void**)&vertices[0], m_cellCount * sizeof(VertexType));

	deviceContext->Unmap(m_vertexBuffer, 0);

	delete[] vertices;
	vertices = 0;
}

void Grid::AddChargeAt(unsigned int i)
{
	XMFLOAT3* temp = &m_cells.at(i)->color;
	temp->y += 0.2f;
	
	if (temp->y > 1.0f)
		temp->y = 1.0f;

}

void Grid::DecreaseChargeAt(unsigned int i, float dt)
{
	XMFLOAT3* temp = &m_cells.at(i)->color;
	
	temp->y -= dt * 0.1f;
	if (temp->y < 0.0f)
		temp->y = 0.0f;
}


void Grid::RenderBuffer(ID3D11DeviceContext* deviceContext)
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

Grid::Cell* Grid::GetGridCell(unsigned int i)
{
	return m_cells.at(i);
}