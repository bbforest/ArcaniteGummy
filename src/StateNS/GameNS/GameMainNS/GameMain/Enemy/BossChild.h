#pragma once

#include "..\..\..\..\..\Data.h"
#include "..\Character.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class BossChild : public Character
{
public:
	BossChild(int hp, int x, int y, int w, int h,float jump,int jumpCount);
	virtual ~BossChild();
	virtual void update(const Stage*) = 0;
	void draw(const Vector2* camera) const;
	bool isAlive() const { return mIsAlive; }

protected:
	int mTime;
	int mImage;
	bool mDirection;

	//dx と dy に移動量を入れる
	virtual void move(const Stage*, int& dx, int& dy) = 0;
	virtual void loadImage() = 0;

	void standardAction(const Stage* _stage);

private:
	bool mIsAlive;

	void initialize();
	void standardMove(const Stage* stage);
	void checkIsAlive(const Stage* stage);
	void processDamage();



};



}
}
}