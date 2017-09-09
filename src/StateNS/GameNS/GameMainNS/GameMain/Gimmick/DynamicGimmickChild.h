#pragma once

#include "..\..\..\..\..\Data.h"
#include "..\DynamicObject.h"
#include "..\Stage.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class PlayerChild;
class Character;

class DynamicGimmickChild : public DynamicObject
{
public:
	DynamicGimmickChild(int x, int y, double _scale);
	virtual ~DynamicGimmickChild();
	virtual void update(const Stage*) = 0;
	virtual void draw(const Vector2* camera) const = 0;
	virtual void apply(Character*) = 0;
	virtual void hittedAction() override = 0;
	virtual void burnedAction() = 0;

	//��ʏ�ŏd�Ȃ��Ă��邩�C�����蔻��p
	//�����̓}�b�v���Z�̒l
	virtual bool isOverlap(const Vector2* player) const = 0;

	//�Ώۂ��M�~�b�N�̌��ʔ͈͓��ɂ��邩
	//�����̓}�b�v���Z�̒l
	virtual bool onActiveArea(const Vector2*) const = 0;

	virtual Stage::ChipType getChipType() const = 0;

	//�����̏�[�̍��W��Ԃ�
	int getTopPosition() const { return p->raw_y - height * vectorRate / 2; }

	//��ʏ�ɕ\�����āA�X�V���邩�ǂ�����public�ϐ�
	bool isActive;

	//�M�~�b�N�̏�ɏ���Ă��邩�ǂ����̔���
	bool rideOnGimmick(const Vector2*) const;

	float getDX() const { return dx / (float)vectorRate; }
	float getDY() const { return dy / (float)vectorRate; }

protected:
	int dx;
	int dy;
	int mImage;
	bool mDirection;
	double scale;

	virtual void loadImage() = 0;

	void standardMove(const Stage*);
	bool standardOverLap(const Vector2*) const;
	int getTopDiffer(const Stage*, const int dy) const;
	int getBottomDiffer(const Stage*, const int dy) const;
	int getHorizontalDiffer(const Stage*, const int dx) const;

};




}
}
}