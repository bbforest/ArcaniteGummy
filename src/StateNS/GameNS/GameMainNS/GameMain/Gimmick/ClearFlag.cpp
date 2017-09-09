#include "ClearFlag.h"
#include "..\Character.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


ClearFlag::ClearFlag(Vector2 _pos) : 
GimmickChild(_pos)
{
	initialize();
	
}

ClearFlag::~ClearFlag()
{

}

void ClearFlag::initialize()
{
	loadImage();
}

void ClearFlag::update()
{

}

void ClearFlag::draw(const Vector2* _camera) const
{
	standardDraw(_camera);
}

void ClearFlag::apply(Character* _character)
{
	this->isActive = false;
}

bool ClearFlag::isOverlap(int _sub_x, int _sub_y) const
{
	return
		this->pos.x() / CHIP_WIDTH  == _sub_x &&
		this->pos.y() / CHIP_HEIGHT == _sub_y;
}

bool ClearFlag::onActiveArea(const Vector2* _player) const
{
	return
		abs(this->pos.x() - _player->x()) <= CHIP_WIDTH / 2 &&
		abs(this->pos.y() - _player->y()) <= MyData::CHIP_HEIGHT;}

Stage::ChipType ClearFlag::getChipType() const
{
	return Stage::ChipType::TYPE_BACK;
}

//==============================================
//�����v���C�x�[�g�֐�
//==============================================
void ClearFlag::loadImage()
{
	mImage = LoadGraph("Data/Image/ClearFlag.png");
	assert(mImage != -1 && "�N���A�摜�ǂݍ��݃G���[�I");
}


}
}
}