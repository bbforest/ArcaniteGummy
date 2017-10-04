#pragma once
#include "..\..\..\..\..\Data.h"
#include "..\Attack.h"
#include <vector>


namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class Character;


class Shot : public Attack {

public:
	Shot(const Character*, int x, int y, float angle, float speed, int damage);
	~Shot();
	virtual void update();
	void draw(const Vector2* camera) const override;
	void setStatus(Vector2, int status) { assert(!"Shot::setStatus <- この関数は呼ばれないはずだー"); };

	//第1引数にVector2::ZEROが来ると位置は更新されない angleは度数法
	void setStatus_2args(Vector2, int angle, int speed) override;
	void hittedAction() override {}
	void loadImage(char* path) { DeleteGraph(mImage); this->mImage = LoadGraph(path); assert(this->mImage != -1 && "Shot画像読み込みエラー!"); }


protected:

	float angle;
	int dx;
	int dy;
	int time;

	void initialize();

private:
	static bool imgLoad;
	void loadImage();

};

float sinf_degree(int degree);
float cosf_degree(int degree);

}
}
}