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
		
		CheckIsSwitching();

		if (m_isSwitching)
		{
			ToFadeOut();
			
			return;
		}

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

		m_switchEventPost.m_nextSceneKind = SCENE_KIND::TITLE;

		Switch();
	}

	void SceneSwitcher::Finalize()
	{
		delete m_pScene;
	}

	void SceneSwitcher::Switch()
	{
		m_rGameFramework.ReleaseAllGraphicEffect();

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
			m_pScene = new TitleScene();

			break;

		case SCENE_KIND::HOME:
			//m_pScene = new HomeScene();

			break;

		case SCENE_KIND::IN_GAME:
			m_pScene = new InGameScene();

			break;

		case SCENE_KIND::RESULT:
			m_pScene = new ResultScene();

			break;

		default:
			break;
		}

		m_rObjectIntegrator.Register(m_pSceneFader = new SceneFader(), LAYER_KIND::FRONT, 0);
	}

	void SceneSwitcher::CheckIsSwitching()
	{
		m_isSwitching = gameframework::algorithm::Tertiary(m_pSceneFader->GetEnds(), false, true);
	}

	void SceneSwitcher::ToFadeOut()
	{
		m_pSceneFader->SetShouldFadeOut(true);
	}
}
