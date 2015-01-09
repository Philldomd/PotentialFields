#include "Entity.h"

#include<cstdlib>

Entity::Entity(XMFLOAT2 HILO, XMFLOAT2 _size)
{
	
	position = XMFLOAT2(randomFunc(HILO.y, HILO.x), randomFunc(HILO.y, HILO.x));
	velocity = XMFLOAT2(/*randomFunc(-2, 2)*/1, randomFunc(-0.1,0.1));
	size = _size;
	color = XMFLOAT3(0.4f, 0.4f, 0.4f);
	box = AABB(position, XMFLOAT2(position.x + size.x, position.y + size.y));
}

Entity::Entity(XMFLOAT2 HILO)
{

	position = XMFLOAT2(randomFunc(HILO.y, HILO.x), randomFunc(HILO.y, HILO.x));
	velocity = XMFLOAT2(/*randomFunc(-2, 2)*/0.1, 0.9);
	size = XMFLOAT2(10,10);
	color = XMFLOAT3(0.4f, 0.4f, 0.4f);
	box = AABB(position, XMFLOAT2(position.x + size.x, position.y + size.y));
}

Entity::~Entity()
{
}

void Entity::setPosition(XMFLOAT2 _position)
{
	position = _position;
	if (_position.x > 1024)
		position.x = 0;

	if (_position.x < 0)
		position.x = 1024;

	if (_position.y > 768)
		position.y = 0;

	if (_position.y < 0)
		position.y = 768;
}

float Entity::randomFunc(float LO, float HI)
{
	float r3 = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
	return r3;
}

void Entity::setBoxPosition(XMFLOAT2 _position)
{
	XMFLOAT2 max;
	max.x = _position.x + size.x;
	max.y = _position.y + size.y;
	box.setMinMax(_position, max);
}
