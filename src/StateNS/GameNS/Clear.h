#pragma once

#include "GameChild.h"

namespace StateNS {

class Parent;

namespace GameNS {


class Clear : public Child
{
public:
	Clear();
	~Clear();
	void initialize();
	Child* update(StateNS::Parent*);
	void draw() const;

private:
	bool saved;
	int backImg;
	int images[32];
};



}
}