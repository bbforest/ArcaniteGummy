#pragma once

#include "PlayerChild.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class Sakuya : public PlayerChild
{
public:
	Sakuya(int, int);
	Sakuya(int, int, int);
	~Sakuya();
	PlayerChild* update(const StageChild*);

private:
	int attackTime;
	const int attackInterval = 10;//攻撃の間隔

	bool isStoppingTime;
	int stoppingTime;
	const int maxStoppingTime = 120;//時を止めていられる時間(フレーム数)

	void initialize();
	virtual void attack() override {}//仮想
	void attack(const StageChild*);
	int getAttackDx() const;
	void processAttack(const StageChild*);
	void processStopDynamics();

	void draw_other() const;
	virtual void loadImage() override;
	//攻撃方法の内部クラス
	class Knife : public Attack
	{
	public:
		Knife(const PlayerChild*, const StageChild*, int x, int y, int dx);
		~Knife();
		void update();

		void setStatus(Vector2, int dx);
		void hittedAction();

	private:
		int dx;
		bool up;
		const StageChild* stage;
	};
};




}
}
}