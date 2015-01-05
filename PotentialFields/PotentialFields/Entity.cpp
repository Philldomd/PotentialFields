#include "Entity.h"

#include<cstdlib>

Entity::Entity(XMFLOAT2 HILO)
{
	position = XMFLOAT2(randomFunc(HILO.y, HILO.x), randomFunc(HILO.y, HILO.x));
	velocity = XMFLOAT2(randomFunc(-2, 2), randomFunc(-2, 2));
	color = XMFLOAT3(0.4, 0.4, 0.4);
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
