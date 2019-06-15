#ifndef IN_GAME_SCENE_H
#define IN_GAME_SCENE_H

#include "Background.h"
#include "Player.h"
#include "Scene.h"
#include "Target.h"
#include "TotalPoint.h"

namespace chargeshot
{
	class InGameScene :public Scene
	{
	public:
		InGameScene();
		~InGameScene();

	private:
		InGameScene(const InGameScene& inGameScene) = delete;
		InGameScene& operator=(InGameScene& inGameScene) = delete;

		void Initialize()override;
		void Finalize()override;

		void LoadResouces()override;
	};
}

#endif //!IN_GAME_SCENE_H