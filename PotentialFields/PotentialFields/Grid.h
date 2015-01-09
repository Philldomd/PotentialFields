#include "GraphicEngine.h"
#include "AABBCollision.h"
#include <vector>

class Grid
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT4 color;

		/*VertexType(XMFLOAT3 pos, XMFLOAT4 col)
		{
			position = pos;
			color = col;
		}*/
	};
	
	struct Cell
	{
		XMFLOAT3 position;
		XMFLOAT3 color;
		XMFLOAT2 velocity;
		float numberOfEntries;
		AABB box;
		Cell(XMFLOAT3 _position, XMFLOAT3 _color, XMFLOAT2 _dim)
		{
			numberOfEntries = 0;
			velocity = XMFLOAT2(0, 0);
			position = _position;
			color = _color;
			box = AABB(XMFLOAT2(_position.x, _position.y), XMFLOAT2(_position.x + _dim.x, _position.y + _dim.y));
		}
		XMFLOAT3 getPosition() { return position; }
		XMFLOAT3 getColor() { return color; }
	};
	ID3D11Buffer* m_vertexBuffer;
	std::vector<Cell*> m_cells;
	unsigned int m_cellCount;
	XMFLOAT2 m_gridDim;

public:
	Grid();
	bool Initialize(ID3D11Device*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);
	void Update(VIEWS,ID3D11DeviceContext*);
	unsigned int GetCellCount(){ return m_cellCount; };
	XMFLOAT2 GetGridDim(){ return m_gridDim; };
	Cell* GetGridCell(unsigned int);
	void AddChargeAt(unsigned int);
	void DecreaseChargeAt(unsigned int, float dt);
	Grid(const Grid&);
	~Grid();

private:
	void ShutdownBuffer();
	bool InitializeBuffer(ID3D11Device*);
	void RenderBuffer(ID3D11DeviceContext*);
};