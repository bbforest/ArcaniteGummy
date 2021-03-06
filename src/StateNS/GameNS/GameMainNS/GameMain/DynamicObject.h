#pragma once

#include "..\..\..\..\Data.h"


namespace StateNS {
namespace GameNS {

namespace GameMainNS{

class Collision;
class StageChild;

class DynamicObject
{
public:
	DynamicObject(int x, int y, int w, int h, float jump, int jumpCount);
	DynamicObject(int x, int y, int w, int h, float jump, int jumpCount, bool hasChild);
	virtual ~DynamicObject();
	virtual void hittedAction() = 0;
	const Vector2* getVector2() const { return p; }
	bool isHit(const DynamicObject*) const;

	Collision* collision = 0;

	void setJumpPower(float _x) { jumpPower = _x; }
	void setJumpCount(int _x) { nowJumpCount = _x; }

	const bool hasChild;

protected:
	Vector2* p = 0;

	//自機だけでなく敵もジャンプさせるのでここに書く
	const float maxJumpPower;
	const int maxJumpCount;
	float jumpPower;
	int nowJumpCount;
	int width;
	int height;

	int jump();
	int gravity();

	int getTopDiffer(const StageChild*, const int dy, bool moveLeft, bool isPlayer) const;
	int getBottomDiffer(const StageChild*, const int dy, bool moveLeft, bool isPlayer) const;
	int getHorizontalDiffer(const StageChild*, const int dx, bool moveUp, bool isPlayer) const;

	virtual bool onRigidBlock() const { return false; }

	//cameraを中心とした描画
	void standardDraw(const Vector2* camera, const int& image, const bool& direction) const;
	//拡大率指定版
	void standardDraw(const Vector2* camera, const double& scale, const int& image, const bool& direction) const;
};




}
}
}