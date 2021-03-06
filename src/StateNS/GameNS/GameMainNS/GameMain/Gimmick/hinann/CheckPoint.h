#pragma once

#include "GimmickChild.h"



namespace StateNS {
namespace GameNS {


namespace GameMainNS{

class Child;

class CheckPoint : public GimmickChild
{
public:
	CheckPoint();
	~CheckPoint();
	void initialize();
	void update(PlayerChild*);
	void draw() const;
	bool isHit(const Vector2&) const;
	Stage::ChipType getChipType() const;

private:
};




}
}
}