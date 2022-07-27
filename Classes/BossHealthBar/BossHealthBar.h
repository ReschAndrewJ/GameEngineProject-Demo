#ifndef BOSS_HEALTH_BAR
#define BOSS_HEALTH_BAR

#include "../HealthDisplayAbstract/HealthDisplayAbstract.h"

const auto OBJECT_CLASS_BOSS_HEALTH_BAR = "BossHealthBar";



class BossHealthBar : public virtual HealthDisplayAbstract {
private:
	std::unordered_map <std::string, Object*>* objectsContainerPtr;
public:
	BossHealthBar();
	virtual ~BossHealthBar();

	static void process_func(Object*, float);


private:
	std::string bossId;
};


#endif