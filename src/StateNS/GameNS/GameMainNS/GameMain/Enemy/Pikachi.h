#pragma once

#include "..\..\..\..\..\Data.h"
#include "EnemyChild.h"
#include "..\Attack.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class Pikachi : public EnemyChild
{
public:
	Pikachi(int x, int y);
	~Pikachi();

	void update(const Stage* _stage,const Vector2* _camera);

private:
	//Character�̊֐�
	void hittedAction();

	//Enemychild�̊֐�
	void move(const Stage*, int& dx, int& dy);
	
	void loadImage() { images = LoadGraph("Data/Image/Pikachi.png"); mImage = images; imgLoad = true; }


	void initialize();

	int images;
	bool imgLoad = false;
	
	int mTime;

	int moveSpeed;
	bool preOnGround;
	void attack(const Stage*);
	void draw_other(const Vector2*)const override;

	//�U�����@�̓����N���X
	class Thunder : public Attack
	{
	public:
		Thunder(const Character*, const Stage*, int x, int y, int speed);
		~Thunder();
		void update();
		void setStatus(Vector2, int speed);
		void hittedAction();

	private:
		int dx;
		int dy;
		const Stage* stage;
	};

};




}
}
}