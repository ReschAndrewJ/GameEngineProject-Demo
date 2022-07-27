#define GAME_MAIN
#ifdef GAME_MAIN

#include <time.h>

#include "../_GameEngineSrc/Engines/Main/Main_Engine.h"
#include "KeysToPoll.h"

#include "../Classes/GameContainer/GameContainer.h"
#include "../Classes/StageControl/StageControl.h"

#include "../Classes/Stage_Survival/Stage_Survival.h"
#include "../Classes/StageBorder/StageBorder.h"
#include "../Classes/DespawnBox/DespawnBox.h"
#include "../Classes/Stage_Boss/Stage_Boss.h"

#include "../Classes/Timer/Timer.h"

#include "../Classes/SingleCallSound/SingleCallSound.h"

#include "../Classes/SpawnInfo/SpawnInfo.h"
#include "../Classes/Spawner/Spawner.h"
#include "../Classes/MovingSpawner/MovingSpawner.h"
#include "../Classes/RandPosSpawner/RandPosSpawner.h"

#include "../Classes/Player_TypeA/Player_TypeA.h"

#include "../Classes/EnemyA/EnemyA.h"
#include "../Classes/EnemyB/EnemyB.h"
#include "../Classes/EnemyC/EnemyC.h"

#include "../Classes/Boss/Boss.h"

#include "../Classes/TypeABullet/TypeABullet.h"

#include "../Classes/HealthBarContainer/HealthBarContainer.h"
#include "../Classes/PlayerHealthDisplay/PlayerHealthDisplay.h"
#include "../Classes/BossHealthBar/BossHealthBar.h"

#include "../Classes/Menu/Menu.h"


int WinMain() {
	srand(time(0));

	Main_Engine e;
	engine_start_info start{};
	start.aspectRatioHeight = 1;
	start.aspectRatioWidth = 1;
	start.windowWidth = 700;
	start.windowHeight = 700;
	start.windowTitle = "GameEngineDemo";
	start.enforceAspectRatio = false;
	start.keysToPoll = keys::keysToPoll;
	
	start.AddedObjectCreateFunctions = {
		{OBJECT_CLASS_STAGE_CONTROL,[] { return (Object*)new StageControl(); }},
		{OBJECT_CLASS_STAGE_SURVIVAL, [] { return (Object*)new Stage_Survival(); }},
		{OBJECT_CLASS_STAGE_BORDER, [] {return (Object*)new StageBorder(); }},
		{OBJECT_CLASS_TIMER, [] {return (Object*)new Timer(); }},
		{OBJECT_CLASS_SINGLE_CALL_SOUND, [] {return (Object*)new SingleCallSound(); }},
		{OBJECT_CLASS_SPAWN_INFO, [] {return (Object*)new SpawnInfo(); }},
		{OBJECT_CLASS_SPAWNER, [] {return (Object*)new Spawner(); }},
		{OBJECT_CLASS_PLAYER_TYPE_A, [] {return (Object*)new Player_TypeA(); }},
		{OBJECT_CLASS_ENEMY_A, [] {return (Object*)new EnemyA(); }},
		{OBJECT_CLASS_TYPE_A_BULLET, [] {return (Object*)new TypeABullet(); }},
		{OBJECT_CLASS_PLAYER_HEALTH_DISPLAY, [] {return (Object*)new PlayerHealthDisplay(); }},
		{OBJECT_CLASS_MENU, [] {return (Object*)new Menu(); }},
		{OBJECT_CLASS_GAME_CONTAINER, [] {return (Object*)new GameContainer(); }},
		{OBJECT_CLASS_DESPAWN_BOX, [] {return (Object*)new DespawnBox(); }},
		{OBJECT_CLASS_ENEMY_B, [] {return (Object*)new EnemyB(); }},
		{OBJECT_CLASS_ENEMY_C, [] {return (Object*)new EnemyC(); }},
		{OBJECT_CLASS_MOVING_SPAWNER, [] {return (Object*)new MovingSpawner(); }},
		{OBJECT_CLASS_STAGE_BOSS, [] {return (Object*)new Stage_Boss(); }},
		{OBJECT_CLASS_BOSS, [] {return (Object*)new Boss(); }},
		{OBJECT_CLASS_BOSS_HEALTH_BAR, [] {return (Object*)new BossHealthBar(); }},
		{OBJECT_CLASS_RAND_POS_SPAWNER, [] {return (Object*)new RandPosSpawner(); }},
		{OBJECT_CLASS_HEALTH_BAR_CONTAINER, [] {return (Object*)new HealthBarContainer(); }}
	};
	start.rootObject_filePath = "Resources/InstanceFiles/Menu.inst";
	start.rootObject_objectName = "Top";
	e.start(start);


}


#endif