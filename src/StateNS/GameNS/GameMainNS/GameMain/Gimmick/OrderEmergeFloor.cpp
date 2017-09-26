#include "OrderEmergeFloor.h"

#include "..\Character.h"


//for Debug
#include "..\Collision.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


OrderEmergeFloor::OrderEmergeFloor(int _x, int _y, double _scale,int _order) :
DynamicGimmickChild(_x, _y, _scale)
{
	this->width  = (int)(32 * _scale);
	this->height = (int)(32 * _scale);
	this->order = _order;
	isEmerge = false;
	initialize();
}

OrderEmergeFloor::~OrderEmergeFloor()
{

}

void OrderEmergeFloor::initialize()
{
	
	loadImage();
	dy = 0;
}

void OrderEmergeFloor::update(const StageChild* _stage)
{

	mTime++;
	mTime %= 240;

	if (mTime >= order * 30)isEmerge = true;
	else isEmerge = false;

	//if (!isEmerge)return;
	standardMove(_stage);
	//this->dy = getBottomDiffer(_stage, 4000);
	//this->p->raw_y += this->dy;
}

void OrderEmergeFloor::draw(const Vector2* _camera) const
{
	if (!isEmerge)return;
	standardDraw(_camera, p, scale, mImage, mDirection);

	//for Debug
	//DrawFormatString(0, 50, BLACK, "%d %d", width, height);
	//DrawFormatString(300, 100, BLACK, "%lf", scale);
	DrawFormatString(300, 120, BLACK, "b: %d %d", collision->p->raw_x, collision->p->raw_y);


	int draw_x = 320 + p->x() - _camera->x();
	int draw_y = 240 + p->y() - _camera->y();

	DrawCircle(draw_x, draw_y, 5, GREEN);
	//DrawBox(draw_x, draw_y, draw_x + width, draw_y + height, BLACK, false);
}

void OrderEmergeFloor::apply(Character* _character)
{
	_character->moveCharacter(0.0f, (float)dy);
}

void OrderEmergeFloor::hittedAction()
{
//	if(isBreakable)this->isActive = false;
}

void OrderEmergeFloor::burnedAction()
{
	//TODO -> �A�j���[�V����������

	//�R�₳���Ə�����
	//this->isActive = false;
}

bool OrderEmergeFloor::isOverlap(const Vector2* _player) const
{
	if (!isEmerge)return false;
	return standardOverLap(_player);

	/*
	int tmp_w = this->width  * vectorRate / 2;
	int tmp_h = this->height * vectorRate / 2;

	return
		this->p->raw_x - tmp_w < _player->raw_x &&
		this->p->raw_x + tmp_w > _player->raw_x &&
		this->p->raw_y - tmp_h < _player->raw_y &&
		this->p->raw_y + tmp_h > _player->raw_y;
	*/

	/* Collision�̓����蔻��
	return
		this->p->raw_x			      < other->p->raw_x + other->width  &&
		this->p->raw_x + this->width  > other->p->raw_x					&&
		this->p->raw_y			      < other->p->raw_y + other->height &&
		this->p->raw_y + this->height > other->p->raw_y;
	*/
}

bool OrderEmergeFloor::onActiveArea(const Vector2* _player) const
{
	//for Debug
	return false;
}


//==============================================
//�����v���C�x�[�g�֐�
//==============================================
void OrderEmergeFloor::loadImage()
{
	this->mImage = LoadGraph("Data/Image/OrderEmergeFloor.png");
	assert(mImage != -1 && "OrderEmergeFloor�摜�ǂݍ��݃G���[!");
}


}
}
}