#include "SceneSwitcher.h"

namespace chargeshot
{
	SceneSwitcher::~SceneSwitcher()
	{
		Finalize();
	}

	void SceneSwitcher::Update()
	{
		if (!m_switchEventPost.m_shouldSwitch) return;
		
		Switch();
	}

	SceneSwitcher::SceneSwitcher()
	{
		Initialize();
	}

	void SceneSwitcher::Initialize()
	{
		auto& rSceneSwitcherMediator = SceneSwitchMediator::CreateAndGetRef();

		rSceneSwitcherMediator.RegisterReceiver(&m_switchEventPost);

		m_switchEventPost.m_nextSceneKind = SCENE_KIND::IN_GAME;

		Switch();
	}

	void SceneSwitcher::Finalize()
	{
		delete m_pScene;
	}

	void SceneSwitcher::Switch()
	{
		delete m_pScene;

		CreateNextKindScene();

		m_currentSceneKind = m_switchEventPost.m_nextSceneKind;

		m_switchEventPost.m_shouldSwitch = false;
	}

	void SceneSwitcher::CreateNextKindScene()
	{
		switch (m_switchEventPost.m_nextSceneKind)
		{
		case SCENE_KIND::TITLE:
			//m_pScene = new TitleScene();

			break;

		case SCENE_KIND::HOME:
			//m_pScene = new HomeScene();

			break;

		case SCENE_KIND::IN_GAME:
			m_pScene = new InGameScene();

			break;

		case SCENE_KIND::RESULT:
			//m_pScene = new InGameScene();

			break;

		default:
			break;
		}
	}
}
