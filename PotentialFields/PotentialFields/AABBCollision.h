#pragma once

#include<DirectXMath.h>

struct AABB
{
private:
	DirectX::XMFLOAT2 min;
	DirectX::XMFLOAT2 max;
public:
	AABB()
	{
		min = DirectX::XMFLOAT2(0.f, 0.f);
		max = DirectX::XMFLOAT2(10.f, 10.f);
	}
	AABB(DirectX::XMFLOAT2  _min, DirectX::XMFLOAT2  _max)
	{
		min = _min;
		max = _max;
	}
	const void setMinMax(DirectX::XMFLOAT2 _min, DirectX::XMFLOAT2 _max)
	{
		min = _min;
		max = _max;
	}
	const DirectX::XMFLOAT2  getMin() { return min; }
	const DirectX::XMFLOAT2  getMax() { return max; }
};

inline bool intersect(AABB &b1, AABB &b2)
{
	const DirectX::XMFLOAT2 b1Min = b1.getMin();
	const DirectX::XMFLOAT2 b1Max = b1.getMax();
	const DirectX::XMFLOAT2 b2Min = b2.getMin();
	const DirectX::XMFLOAT2 b2Max = b2.getMax();

	if (b1Min.x > b2Max.x || b1Max.x < b2Min.x)
		return false;
	if (b1Min.y > b2Max.y || b1Max.y < b2Min.y)
		return false;
	return true;
}