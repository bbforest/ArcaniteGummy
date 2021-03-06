#include "Usagi.h"
#include "..\Stages\StageChild.h"



namespace StateNS {
namespace GameNS {
namespace GameMainNS{

bool Usagi::imgLoad = false;
int Usagi::images[8];

Usagi::Usagi(int _x, int _y) : EnemyChild(100, _x, _y, 32, 32)
{
	loadImage();

	initialize();
};


Usagi::~Usagi()
{
	//DeleteGraphはしない
}

void Usagi::initialize()
{
	this->mDirection = false;
	this->moveSpeed = -1000;

	this->mTime = 0;
	actState = ENE_ACT_WALK;
}

void Usagi::update(const StageChild* _stage,const Vector2* _camera)
{
	if (actState == ENE_ACT_DEAD && aTime >= 60)actState = ENE_ACT_WALK;
	aTime++;
	mTime++;

	standardAction(_stage);
	mImage = images[actState * 2 + (aTime / 10) % 2];
}

void Usagi::move(const StageChild* _stage, int& _dx, int& _dy)
{
	_dx = getHorizontalDiffer(_stage, moveSpeed, _dy < 0);
	_dy = getBottomDiffer(_stage, 2000, _dx > 0);

	//自分の右下のチップのChipTypeをゲット
	RawVector2 pos = RawVector2(p->x() + CHIP_WIDTH / 4, p->y() + CHIP_HEIGHT);
	StageChild::ChipType chip_under_right = _stage->getChipType(pos, true);

	//自分の左下のチップのChipTypeをゲット
	pos = RawVector2(p->x() - CHIP_WIDTH / 4, p->y() + CHIP_HEIGHT);
	StageChild::ChipType chip_under_left = _stage->getChipType(pos, true);

	//自分の前のチップのChipTypeをゲット
	pos = RawVector2(p->x() + CHIP_WIDTH / 4 * ((mDirection) ? 1: -1), p->y() - CHIP_HEIGHT / 2);
	StageChild::ChipType chipType_front = _stage->getChipType(pos, true);

	bool right_isCliff = _stage->isRigid_down(chip_under_right) | _stage->isSlant(chip_under_right);
	bool left_isCliff  = _stage->isRigid_down(chip_under_left)  | _stage->isSlant(chip_under_left);

	if( //崖
		(right_isCliff ^ left_isCliff) || 
		//壁
		chipType_front == StageChild::ChipType::TYPE_RIGID 
		)
	{
		//方向転換
		_dy = 0;
		mDirection = !mDirection;
		moveSpeed = -moveSpeed;
		this->p->raw_x += moveSpeed * 5;
	}
	else if(!(right_isCliff | left_isCliff))
	{
		//空中にいる
		_dy = getBottomDiffer(_stage, 4000, _dx > 0);
		_dx = 0;
	}
}


//==============================================
//内部プライベート関数
//==============================================
void Usagi::loadImage()
{
	if (!imgLoad)
	{
		int tmp = LoadDivGraph("Data/Image/Usagi.png", 8, 8, 1, 32, 32, images);
		assert(tmp != -1 && "Usagi画像読み込みエラー");
	}
	imgLoad = true;
}

void Usagi::hittedAction()
{
	aTime = 0;
	actState = ENE_ACT_DEAD;
}

}
}
}