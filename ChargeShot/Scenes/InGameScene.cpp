#include "InGameScene.h"

namespace chargeshot
{
	using namespace gameframework;

	InGameScene::InGameScene()
	{
		Initialize();
	}

	InGameScene::~InGameScene()
	{
		Finalize();
	}

	void InGameScene::Initialize()
	{
		PointChecker::CreateAndGetRef().Zero();

		m_rObjectIntegrator.Register(new Background(_T("BACKGROUND"), D3DXVECTOR2(0.1f, 0.0f)), LAYER_KIND::OPAQUENESS, -100);
		m_rObjectIntegrator.Register(new Background(_T("BACKGROUND_00"), D3DXVECTOR2(0.35f, 0.0f)), LAYER_KIND::OPAQUENESS, -99);
		m_rObjectIntegrator.Register(new Background(_T("BACKGROUND_01"), D3DXVECTOR2(0.4f, 0.0f)), LAYER_KIND::OPAQUENESS, -98);
		m_rObjectIntegrator.Register(new Background(_T("BACKGROUND_02"), D3DXVECTOR2(1.0f, 0.0f)), LAYER_KIND::OPAQUENESS, -97);
		m_rObjectIntegrator.Register(new Background(_T("BACKGROUND_03"), D3DXVECTOR2(0.0f, 0.0f)), LAYER_KIND::OPAQUENESS, -96);
		m_rObjectIntegrator.Register(new Background(_T("BACKGROUND_04"), D3DXVECTOR2(0.0f, 0.0f)), LAYER_KIND::OPAQUENESS, -95);
		m_rObjectIntegrator.Register(new PointTextCreater(_T("POINT_M")), LAYER_KIND::UI, 95);
		m_rObjectIntegrator.Register(new Player(WindowMeasure::GetNormalizeVector(5.0f, 50.f)), LAYER_KIND::OPAQUENESS, 0);
		m_rObjectIntegrator.Register(
			new Target(
				D3DXVECTOR3(WindowMeasure::GetNormalizeX(90.0f), 0.0f, 0.5f), WindowMeasure::GetNormalize(5.0f, 10.0f), 4.0f),
			LAYER_KIND::OPAQUENESS, 0);
		m_rObjectIntegrator.Register(
			new HighScoreText(_T("POINT_M"), WindowMeasure::GetNormalizeVector(99.5f, 1.0f), DT_RIGHT), LAYER_KIND::UI, 0);

		LoadResouces();

		m_rGameFramework.LoopStart(_T("BGM_IN_GAME"));
	}

	void InGameScene::Finalize()
	{
		m_rGameFramework.Stop(_T("BGM_IN_GAME"));

		Sleep(800);

		CollisionChecker::CreateAndGetRef().ReleaseAll();
	}

	void InGameScene::LoadResouces()
	{
		CreateTexture(_T("BACKGROUND_04"), _T("Textures/InGame_background04.png"));

		CreateTexture(_T("PLAYER"), _T("Textures/InGame_player2.png"));
		CreateTexture(_T("CHARGE_METER"), _T("Textures/InGame_chargeBit.png"));
		CreateTexture(_T("BULLET"), _T("Textures/InGame_bullet.png"));
		CreateTexture(_T("TARGET_WALL"), _T("Textures/InGame_target.png"));

		m_rGameFramework.CreateFont(_T("POINT_M"), WindowMeasure::GetNormalize(1.2f, 4.2f), _T("IPAex–¾’©"));
		m_rGameFramework.CreateFont(_T("POINT_L"), WindowMeasure::GetNormalize(10.0f, 33.0f), _T("IPAex–¾’©"));

		m_rGameFramework.AddFile(_T("Sounds/n28.mp3"), _T("BGM_IN_GAME"), Sound::SoundType::BGM);
		m_rGameFramework.AddSimultaneousFile(_T("Sounds/Charge.mp3"), _T("CHARGE"), Sound::SoundType::SE);
		m_rGameFramework.AddSimultaneousFile(_T("Sounds/Hit_M.mp3"), _T("HIT_M"), Sound::SoundType::SE);
		m_rGameFramework.AddSimultaneousFile(_T("Sounds/Shoot.mp3"), _T("SHOOT"), Sound::SoundType::SE);

		m_rGameFramework.SetVolume(50, Sound::SoundType::SE);
		m_rGameFramework.SetVolume(80, Sound::SoundType::BGM);
	}
}
