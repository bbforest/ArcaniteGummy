#include "Enemychild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

EnemyChild::EnemyChild(int _hp, int _x, int _y, int _w, int _h,float _jump,int _jumpCount) : Character(_hp, _x, _y, _w, _h,_jump,_jumpCount)
{
	initialize();
}

EnemyChild::~EnemyChild()
{

}

void EnemyChild::initialize()
{
	this->mTime = 0;
	this->mIsAlive = true;
	this->mDirection = false;
}

void EnemyChild::draw(const Vector2* _camera) const
{
	//画面内にいなければreturn
	if (!mIsAlive)return;
	
	standardDraw(_camera, p, mImage, mDirection);
}

void EnemyChild::standardAction(const Stage* _stage)
{
	++mTime;
	checkIsAlive(_stage);
	if (!this->mIsAlive)return;

	processDamage();
	standardMove(_stage);
}


void EnemyChild::standardMove(const Stage* _stage)
{
	//やられているならreturn
	if (!mIsAlive)return;

	int dx = next_dx;
	int dy = next_dy;

	next_dx = next_dy = 0;


	//移動
	//引数は参照渡し
	this->move(_stage, dx, dy);

	p->raw_x += dx;
	p->raw_y += dy;
}


void EnemyChild::checkIsAlive(const Stage* _stage)
{
	mIsAlive &= (this->hpController.getHP() > 0);
	mIsAlive &= (this->p->raw_y % MyData::MAP_HEIGHT_RATE() < (this->p->raw_y + 10000) % MyData::MAP_HEIGHT_RATE());
	mIsAlive &= (this->p->raw_y % MyData::MAP_HEIGHT_RATE() > (this->p->raw_y - 10000) % MyData::MAP_HEIGHT_RATE());
}

void EnemyChild::processDamage()
{
	if (damaged)
	{
		++damagedTime;
		if (damagedTime < 3)hittedAction();
		if (damagedTime > 60)
		{
			damaged = false;
			damagedTime = 0;
		}
	}
}



}
}
}