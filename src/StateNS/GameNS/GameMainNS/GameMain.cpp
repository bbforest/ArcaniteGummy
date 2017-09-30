#include "GameMain.h"

#include "Converse.h"

#include "GameMain\Stages\StageChild.h"
#include "GameMain\Stages\AllStages.h"
#include "GameMain\System.h"
#include "GameMain\Player\Mokou.h"
#include "GameMain\Player\Sakuya.h"
#include "GameMain\Player\Nue.h"

#include "GameMain\Enemy\EnemyController.h"
#include "GameMain\Enemy\EnemyChild.h"

#include "GameMain\Gimmick\DynamicGimmickChild.h"
#include "GameMain\Gimmick\Block.h"
#include "GameMain\Gimmick\Switches\SwitchWithBlock.h"

#include "..\..\..\Data.h"
#include "..\..\..\KeyInput.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{


GameMain::GameMain(int _n){
	stageID = _n;
	initialize();
}

GameMain::~GameMain()
{
	SAFE_DELETE(mStage);
	SAFE_DELETE(mPlayer);
	SAFE_DELETE(mSystem);
}

void GameMain::initialize()
{
	mStage = getNextStage(stageID);

	mPlayer = new Nue(96, 1500, 100);
	mSystem = new System();

	mEController = mStage->getEController();
	mEController->setPlayerPos(mPlayer->getVector2());

	converseNum = 0;

	stopDynamicObject = StopType::TYPE_NONE;
}

Child* GameMain::update(GameParent* _parent)
{
	Child* next = this;
	
	//マップ移動していたら
	StageChild::HowStageMove nextMove = mPlayer->getStageMove();
	if (nextMove != StageChild::HowStageMove::MOVE_NONE)
	{
		mStage->moveStage(mPlayer->getStageMove());
		this->mEController = mStage->getEController();
		mEController->setPlayerPos(mPlayer->getVector2());
	}
	

	//時が止まっているか更新
	stopDynamicObject = mPlayer->getStopDynamicObject();

	//DynamicObjectを更新
	if(stopDynamicObject == StopType::TYPE_NONE)updateDynamics(mStage);

	//Playerのupdate
	PlayerChild* nextPlayer = mPlayer->update(mStage);

	//Player交代
	if (nextPlayer != mPlayer)
	{
		SAFE_DELETE(mPlayer);
		mPlayer = nextPlayer;
		this->mEController = mStage->getEController();
		mEController->setPlayerPos(mPlayer->getVector2());
	}

	//衝突判定
	processCollision(mStage);


	//Systemのupdate
	mSystem->update();

	//会話パート
	if(converseNum != 0)
		next = new Converse(this, converseNum);
	converseNum = 0;


	//for Debug
	mPlayer->hpController.recover(1);
	//if (Input_D())_parent->moveTo(_parent->SEQ_OVER);

	//クリア
	if (mStage->isClear())
	{
		_parent->moveTo(_parent->NextSequence::SEQ_CLEAR);
	}

	return next;
}

void GameMain::draw() const
{
	if (stopDynamicObject == StopType::TYPE_SAKUYA)
	{
		DrawBox(0, 0, 640, 480, WHITE, true);
		SetDrawBlendMode(DX_BLENDMODE_SUB, 200);
	}
	mStage->draw(mPlayer->getCamera());
	mEController->draw(mPlayer->getCamera());

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 200);

	mPlayer->draw();

	mStage->draw_front(mPlayer->getCamera());

	mSystem->draw(mPlayer->getVector2());
}

void GameMain::setFilter(FilterType _f) { mSystem->setFilter(_f); }

//==============================================
//内部プライベート関数
//==============================================
void GameMain::updateDynamics(StageChild* stage)
{
	//enemyのupdate
	mEController->update(stage, mPlayer->getCamera());

	//Stageのupdate
	stage->update(this, mPlayer);
}

void GameMain::processCollision(StageChild* _stage)
{
	//TODO -> 高速化したい
	//違うステージのものは処理しないとか

	//敵
	auto enemies = mEController->getEnemies();

	//プレイヤーの攻撃
	auto p_attacks = mPlayer->getAttacks();

	//敵の攻撃
	//mEController->processCollision(mPlayer);

	for (auto& enemy : enemies)
	{
		if (!enemy->isAlive())continue;

		//プレイヤーと敵の衝突
		if (mPlayer->isHit(enemy))
		{
			mPlayer->hpController.damage(5);
		}

		//敵の攻撃とプレイヤーの衝突
		//敵いChildがある場合はEnemyChildの方で対応済み
		for (auto& eAttack : enemy->getAttacks())
		{
			if (eAttack->isActive && mPlayer->isHit(eAttack)) 
			{
				mPlayer->hpController.damage(eAttack->getDamageValue());
			}
		}

		//プレイヤーの攻撃と敵の衝突
		for (auto& attack : p_attacks)
		{
			if (attack->isActive)
			{
				if (attack->isHit(enemy))
				{
					enemy->hpController.damage(attack->getDamageValue());
					enemy->hittedAction();
					attack->hittedAction();
				}
				//敵がComposite等で本体以外にも実態を持っていたら
				if (enemy->hasChild)
				{
					for (auto& eChild : enemy->getChilds())
					{
						if (attack->isHit(eChild))
						{
							eChild->hpController.damage(attack->getDamageValue());
							eChild->hittedAction();
							attack->hittedAction();
						}
					}
				}
			}
		}

		
	}

	//DynamicGimmick
	auto d_gimmicks = _stage->getDynamicGimmicks();

	for (auto& gimmick : d_gimmicks)
	{
		if (!gimmick->isActive)continue;

		//プレイヤーとDynamicGimmickの衝突
		if (mPlayer->isHit(gimmick))
		{

		}

		//プレイヤーの攻撃とDynamicGimmickの衝突
		for (auto& attack : p_attacks)
		{
			if (attack->isActive && attack->isHit(gimmick))
			{
				gimmick->hittedAction();
				attack->hittedAction();

				if (attack->id == ObjectID::A_FIRE)
					gimmick->burnedAction();
			}
		}
	}
}

StageChild* GameMain::getNextStage(int stageID)
{
	if (stageID == 11)return new Stage11();
	if (stageID == 12)return new Stage12();
	if (stageID == 13)return new Stage13();
	if (stageID == 21)return new Stage21();
	if (stageID == 22)return new Stage22();
	if (stageID == 23)return new Stage23();
	if (stageID == 31)return new Stage31();
	if (stageID == 32)return new Stage32();
	if (stageID == 33)return new Stage33();
	//if (stageID == 41)return new Stage41();
	//if (stageID == 42)return new Stage42();
	//if (stageID == 43)return new Stage43();

	/*
	以下，同様の処理を書く
	*/

	//ここにはこない
	assert(!"不正なStageID");
	return NULL;
}


}
}
}