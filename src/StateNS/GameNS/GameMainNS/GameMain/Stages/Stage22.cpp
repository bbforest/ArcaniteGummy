#include "Stage22.h"
#include "Map.h"
#include "..\..\GameMain.h"
#include "..\Gimmick\ClearFlag.h"

#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Stage22::Stage22() :
StageChild(2, 2) //エリアの数: よこ，たて
{
	initialize();
}

Stage22::~Stage22()
{

}

void Stage22::initialize()
{
	//左上から右にpushしていく
	//StageID, 0から昇順, エリアの形
	this->maps.push_back(new Map(22, 0, MapPos::POS_LEFT_UP));
	this->maps.push_back(new Map(22, 1, MapPos::POS_LEFT_FREE));
	this->maps.push_back(new Map(22, 2, MapPos::POS_UP_FREE));
	this->maps.push_back(new Map(22, 3, MapPos::POS_SINGLE));

	flag = new ClearFlag(Vector2(2608, 1040));
	maps[1]->addGimmick(flag);

	//////時限式にしたい/////
	SwitchWithBlock* s = new SwitchWithBlock(64 * 32 + 16, 12 * 32 + 16);
	for (int i = 0; i < 6; i++)s->push_block(new Block(95 * 32 + 16, (27 + i) * 32 + 16, 1.0), false);
	maps[0]->addSwitchWithBlock(s);
	/////////////////////////

	SwitchWithBlock* s2 = new SwitchWithBlock(39 * 32 + 16, 3 * 32 + 16);
	for (int i = 0; i < 4; i++)s2->push_block(new Block((27 + i) * 32 + 16, 5 * 32 + 16, 1.0), false);
	maps[1]->addSwitchWithBlock(s2);

	SwitchWithBlock* s3 = new SwitchWithBlock(61 * 32 + 16, 9 * 32 + 16);
	for (int i = 0; i < 6; i++)s3->push_block(new Block(73 * 32 + 16, (27 + i) * 32 + 16, 1.0), false);
	maps[1]->addSwitchWithBlock(s3);

	SwitchWithBlock* s4 = new SwitchWithBlock(60 * 32 + 16, 43 * 32 + 16);
	for (int i = 0; i < 6; i++)s4->push_block(new Block(75 * 32 + 16, (27 + i) * 32 + 16, 1.0), false);
	maps[1]->addSwitchWithBlock(s4);



	startX = 144, startY = 704;
	//for Debug
	/*
	maps[0]->addEnemy(AllEnemies::BOSS_REISEN, 640, 1392);
	maps[0]->addEnemy(AllEnemies::ENE_AIRMZ, 540, 1392);
	maps[0]->addEnemy(AllEnemies::ENE_BROTH, 540, 1488);
	*/
	//maps[0]->addEnemy(AllEnemies::BOSS_JUNKO, 540, 1360);
}


void Stage22::update(GameMain* gameMain, PlayerChild* _player)
{
	standardUpdate(_player);

	//for Debug
	if(CheckHitKey(KEY_INPUT_1))
		gameMain->startConverse(22);
}

void Stage22::draw(const Vector2* _camera) const
{
	standardDraw(_camera);
}

bool Stage22::isClear() const
{
	return false;
}


}
}
}


