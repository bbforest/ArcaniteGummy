#pragma once

#include "..\..\..\..\..\Data.h"
#include "EnemyChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class Balloon : public EnemyChild
{
public:
	Balloon(int x, int y);
	~Balloon();

	void update(const StageChild* _stage, const Vector2* _camera);


private:
	int mTime;

	static bool imgLoad;
	static int images[8];
	void loadImage();

	//Characterの関数
	void hittedAction();

	//Enemychildの関数
	void move(const StageChild*, int& dx, int& dy);

	void initialize();

};



}
}
}