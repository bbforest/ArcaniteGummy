#pragma once

#include "..\..\..\..\..\Data.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class Map;
class PlayerChild;
class GimmickChild;
class DynamicGimmickChild;
class SwitchWithBlock;
class GameMain;
class EnemyController;


//Stageの基底クラス
class StageChild
{
public:
	StageChild(int stage_max_x, int stage_max_y);
	virtual ~StageChild();
	virtual void update(GameMain*, PlayerChild*) = 0;
	virtual void draw(const Vector2* camera) const = 0;
	virtual bool isClear() const = 0;

	void standardUpdate(PlayerChild*);
	void standardDraw(const Vector2* camera) const;
	virtual void draw_front(const Vector2* camera) const;

	enum ChipType
	{
		TYPE_BACK				= 0b0000000001, //すり抜けられる
		TYPE_RIGID				= 0b0000000010, //すり抜けられない
		TYPE_RIDE				= 0b0000000100, //下からはすり抜け、上からはすり抜けられない
		TYPE_DOWN_SLANT_RIGHT	= 0b0000001000, //右上へ向けた斜めブロック, 上がブロックなし
		TYPE_DOWN_SLANT_LEFT	= 0b0000010000, //左上へ向けた斜めブロック, 上がブロックなし
		TYPE_UP_SLANT_RIGHT		= 0b0000100000, //右上へ向けた斜めブロック, 下がブロックなし
		TYPE_UP_SLANT_LEFT		= 0b0001000000, //左上へ向けた斜めブロック, 下がブロックなし
		TYPE_LADDER				= 0b0010000000, //はしご
		TYPE_LADDER_TOP			= 0b0100000000, //はしごの上
		TYPE_LESAL				= 0b1000000000, //あたったらしぬ。
	};

	virtual bool isRigid_down(ChipType _ct) const { return (_ct & 0b101100110) != 0; }//下にすり抜けられないブロック，床になる
	virtual bool isRigid_up(ChipType _ct)   const { return (_ct & 0b000011010) != 0; }//上にすり抜けられないブロック，天井になる
	virtual bool isSlant(ChipType _ct)		const { return (_ct & 0b001111000) != 0; }//斜めブロック

	ChipType getChipType(const Vector2&, bool isPlayer) const;
	ChipType getChipType(const Vector2&) const;
	ChipType getChipType(const RawVector2&, bool isPlayer) const;

	int getTopPosition(const Vector2*, const int& dy) const;//引数は今いる地点の座標にvectorRrateをかけたもの
	int getBottomPosition(const Vector2*, const int& dy) const;//引数は今いる地点の座標にvectorRrateをかけたもの

	vector< DynamicGimmickChild* > getDynamicGimmicks();
	vector< SwitchWithBlock* > getSwitchWithBlocks();
	EnemyController* getEController();

	enum HowStageMove
	{
		MOVE_NONE,

		MOVE_UP,
		MOVE_RIGHT,
		MOVE_LEFT,
		MOVE_DOWN,
	};

	void moveStage(HowStageMove);

protected:
	int mBackImg;

	unsigned now_stage_num;
	int stage_max_x;
	int stage_max_y;
	vector<Map*> maps;

	class Chip
	{
	public:
		Chip(ChipType _chipType) : mChipType(_chipType) {};
		~Chip() {};
		ChipType getChipType() const { return mChipType; }
		void setChipType(ChipType _chipType) { mChipType = _chipType; }
	private:
		ChipType mChipType;
	};

private:
	void initialize();


};


}
}
}