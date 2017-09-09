#include "Play.h"
#include "Clear.h"
#include "GameMainNS\GameMain.h"
#include "GameMainNS\GameMainChild.h"

#include "..\StateParent.h"

#include "..\..\Data.h"
#include "..\..\KeyInput.h"



namespace StateNS {
namespace GameNS {

Play::Play()
{
	initialize();
}

Play::~Play()
{
	SAFE_DELETE(gameMain);
}

void Play::initialize()
{
	gameMain = new GameMainNS::GameMain();
	mNextSeq = NextSequence::SEQ_NONE;
}

Child* Play::update(Parent* _parent)
{
	Child* next = this;
	gameMain = gameMain->update(this);

	if (Input_X())
	{
		SAFE_DELETE(gameMain);
	}

	if (mNextSeq != SEQ_NONE)
	{
		switch (mNextSeq)
		{
		case SEQ_TITLE: _parent->moveTo(_parent->NextSequence::SEQ_TITLE);
		case SEQ_CLEAR: next = new Clear();
			/*
			TODO 他の遷移も書く
			*/
		}
	}
	mNextSeq = SEQ_NONE;

	return next;
}

void Play::draw() const
{
	gameMain->draw();
}

void Play::moveTo(NextSequence _next)
{
	mNextSeq = _next;
}




}
}