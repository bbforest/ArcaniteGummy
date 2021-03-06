#include "Stage12.h"
#include "Map.h"
#include "..\..\GameMain.h"
#include "..\Gimmick\ClearFlag.h"
#include "..\Gimmick\Guide.h"
#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Stage12::Stage12() :
StageChild(2, 2) //エリアの数: よこ，たて
{
	initialize();
}

Stage12::~Stage12()
{
	DeleteGraph(imageReisen);
	sound->deleteSound("bgm1");
}

void Stage12::initialize()
{
	//雲のエフェクトを横に流れるようにする
	this->drawEffect = true;
	this->backDrawType = DRAW_HORIZONTAL;
	this->setEffectImage("Data/Image/effect_cloud.png");

	this->setBackImage("Data/Image/back1.jpg");
	sound->setSound("Data/Sound/stage1.wav", "bgm1");
	sound->setVolume("bgm1", 0.7f);
	sound->playSound("bgm1", LOOP, false);

	//変更できるキャラクターを設定
	this->changeableCharacter |= CHARA_MOKOU;


	//左上から右にpushしていく
	//StageID, 0から昇順, エリアの形
	this->maps.push_back(new Map(12, 0, MapPos::POS_RIGHT_FREE));
	this->maps.push_back(new Map(12, 1, MapPos::POS_RIGHT_UP));
	this->maps.push_back(new Map(12, 2, MapPos::POS_SINGLE));
	this->maps.push_back(new Map(12, 3, MapPos::POS_UP_FREE));

	vector<string> message
	{
		"当たると痛そうなトゲだ",
		"注意して進むんだぞ"
	};

	Guide* guide = new Guide(10 * 32 + 16, 46 * 32 + 16, message);
	maps[0]->addGimmick(guide);

	vector<string> message2
	{
		"攻撃するか",
		"触れることで",
		"スイッチの切り替えが",
		"できるぞ"
	};

	Guide* guide2 = new Guide(60 * 32 + 16, 40 * 32 + 16, message2);
	maps[1]->addGimmick(guide2);


	flag = new ClearFlag(Vector2(80, 1424));
	maps[3]->addGimmick(flag);

	SwitchWithBlock* s = new SwitchWithBlock(68 * 32 + 16, 40 * 32 + 16);
	for (int i = 0; i < 8;i++)s->push_block(new Block((75+i)*32+16, 38*32+16, 1.0, BlockType::TYPE_SWITCH), true);
	maps[1]->addSwitchWithBlock(s);
	SwitchWithBlock* s2 = new SwitchWithBlock(46 * 32 + 16, 34 * 32 + 16, 1);
	for (int i = 0; i < 8; i++)s2->push_block(new Block(42 * 32 + 16, (37 + i) * 32 + 16, 1.0, BlockType::TYPE_LOCK), false);
	maps[3]->addSwitchWithBlock(s2);


	startX = 208, startY = 1472;
	converseFlag0 = true;
	converseFlag0fin = false;
	imageReisen = LoadGraph("Data/Image/haribote_reisen.png");
	//復活
	bool restart = findRestartPoint();
	//復活したら会話フラグを折る
	if (restart)
	{
		converseFlag0 = false;
		converseFlag0fin = true;
	}
}


void Stage12::update(GameMain* gameMain, PlayerChild* _player)
{
	updateConverse(gameMain, _player);
	standardUpdate(_player);
}

void Stage12::updateConverse(GameMain* gameMain, PlayerChild* _player) 
{
	if (!converseFlag0 && !converseFlag0fin)converseFlag0fin = true;
	if (converseFlag0)
	{
		gameMain->startConverse(120);
		converseFlag0 = false;
	}
}

void Stage12::draw(const Vector2* _camera) const
{
	standardDraw(_camera);
	if(!converseFlag0fin)DrawRotaGraph(320, 352, 1.0, 0.0, imageReisen, TRUE);
}

bool Stage12::isClear() const
{
	return !flag->isActive;
}


}
}
}


