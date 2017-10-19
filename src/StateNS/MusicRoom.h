#pragma once

#include "StateChild.h"


namespace StateNS {


class MusicRoom : public Child{
public:
	MusicRoom();
	~MusicRoom();
	void initialize();
	Child* update(GrandParent*);
	void draw() const;

private:
	int mBackImg;

};




}