#ifndef SCENE_SWITCHER_H
#define SCENE_SWITCHER_H

#include <GameFramework.h>

#include "InGameScene.h"
#include "Object.h"
#include "Scene.h"
#include "SceneKind.h"
#include "SceneSwitchMediator.h"

namespace chargeshot
{
	using gameframework::Singleton;
	
	class SceneSwitcher :public Singleton<SceneSwitcher>
	{
	public:
		friend Singleton<SceneSwitcher>;

		~SceneSwitcher();

		void Update();

	private:
		SceneSwitcher();

		SceneSwitcher(const SceneSwitcher& sceneSwitcher) = delete;
		SceneSwitcher& operator=(const SceneSwitcher& sceneSwitcher) = delete;

		void Initialize();
		void Finalize();

		void Switch();

		void CreateNextKindScene();

		SCENE_KIND m_currentSceneKind = SCENE_KIND::IN_GAME;

		SwitchEvent m_switchEventPost;

		Scene* m_pScene;
	};
} 

#endif //!SCENE_SWITCHER_H
