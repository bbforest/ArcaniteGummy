#pragma once

#include "..\..\..\..\Data.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class EnemyChild
{
public:
	virtual ~EnemyChild() {};
	virtual void update() = 0;
	virtual void draw() = 0;

	//この2つはいらないかもしれない
	virtual void move() = 0;
	virtual void attack() = 0;

protected:
	Vector2* point;
};



}
}
}