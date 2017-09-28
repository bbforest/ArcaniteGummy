#pragma once

#include "..\..\..\..\..\Data.h"
#include "EnemyChild.h"
#include "..\Attack.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class Broth : public EnemyChild
{
public:
	Broth(int x, int y);
	~Broth();

	void update(const StageChild* _stage,const Vector2* _camera);

private:
	//Characterの関数
	void hittedAction();

	//Enemychildの関数
	void move(const StageChild*, int& dx, int& dy);
	
	void loadImage() { images = LoadGraph("Data/Image/Broth.png"); mImage = images; imgLoad = true; }


	void initialize();

	int images;
	bool imgLoad = false;
	
	int mTime;

	int moveSpeed;
	bool preOnGround;
	void attack(const StageChild*);
	void draw_other(const Vector2*)const override;

	//攻撃方法の内部クラス
	class Hammer : public Attack
	{
	public:
		Hammer(const Character*, const StageChild*, int x, int y, int speed);
		~Hammer();
		void update();
		virtual void draw(const Vector2*) const override;
		void setStatus(Vector2, int speed);
		void hittedAction();

	private:
		int mTime;
		int dx;
		int dy;
		int sy;//初期座標

		const StageChild* stage;
	};

};




}
}
}