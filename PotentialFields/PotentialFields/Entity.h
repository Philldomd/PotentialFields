#pragma once

#include "AABBCollision.h"
using namespace DirectX;
class Entity
{
private:
	XMFLOAT2 position, velocity, size;
	XMFLOAT3 color;
	AABB box;
	float randomFunc(float, float);
public:
	Entity(XMFLOAT2, XMFLOAT2);
	Entity(XMFLOAT2 HILO);
	XMFLOAT2 getPosition() { return position; }
	XMFLOAT2 getVelocity() { return velocity; }
	XMFLOAT3 getColor()	{ return color; }
	AABB getAABB(){ return box; }
	void setColor(XMFLOAT3 _color) { color = _color; }
	void setPosition(XMFLOAT2);
	void setBoxPosition(XMFLOAT2);
	~Entity();
};

