#ifndef SCENE_SWITCHER_H
#define SCENE_SWITCHER_H

#include <GameFramework.h>

#include "InGameScene.h"
#include "Object.h"
#include "ObjectIntegrator.h"
#include "ResultScene.h"
#include "Scene.h"
#include "SceneFader.h"
#include "SceneKind.h"
#include "SceneSwitchMediator.h"
#include "TitleScene.h"

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

		void CheckIsSwitching();

		void ToFadeOut();

		SCENE_KIND m_currentSceneKind = SCENE_KIND::IN_GAME;

		SwitchEvent m_switchEventPost;

		Scene* m_pScene = nullptr;

		SceneFader* m_pSceneFader = nullptr;
		
		bool m_isSwitching = false;

		ObjectIntegrator& m_rObjectIntegrator = ObjectIntegrator::CreateAndGetRef();

		GameFramework& m_rGameFramework = GameFramework::CreateAndGetRef();
	};
} 

#endif //!SCENE_SWITCHER_H
