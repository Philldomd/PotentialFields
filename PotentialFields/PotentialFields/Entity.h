#pragma once
#include <DirectXMath.h>
using namespace DirectX;
class Entity
{
private:
	XMFLOAT2 position;
	XMFLOAT2 velocity;
	XMFLOAT3 color;
	float randomFunc(float, float);
public:
	Entity(XMFLOAT2);
	XMFLOAT2 getPosition() { return position; }
	XMFLOAT2 getVelocity() { return velocity; }
	XMFLOAT3 getColor()	{ return color; }
	void setColor(XMFLOAT3 _color) { color = _color; }
	void setPosition(XMFLOAT2);
	~Entity();
};

