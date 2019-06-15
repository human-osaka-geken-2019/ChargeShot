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
		m_rObjectIntegrator.Register(new Background(_T("BACKGROUND"), D3DXVECTOR2(0.1f, 0.0f)), LAYER_KIND::OPAQUENESS, -100);
		m_rObjectIntegrator.Register(new Background(_T("BACKGROUND_00"), D3DXVECTOR2(0.35f, 0.0f)), LAYER_KIND::OPAQUENESS, -99);
		m_rObjectIntegrator.Register(new Background(_T("BACKGROUND_01"), D3DXVECTOR2(0.4f, 0.0f)), LAYER_KIND::OPAQUENESS, -98);
		m_rObjectIntegrator.Register(new Background(_T("BACKGROUND_02"), D3DXVECTOR2(1.0f, 0.0f)), LAYER_KIND::OPAQUENESS, -97);
		m_rObjectIntegrator.Register(new Background(_T("BACKGROUND_03"), D3DXVECTOR2(0.0f, 0.0f)), LAYER_KIND::OPAQUENESS, -96);
		m_rObjectIntegrator.Register(new TotalPoint(_T("POINT")), LAYER_KIND::UI, 100);
		//m_rObjectIntegrator.Register(new Player(WindowMeasure::GetNormalizeVector(5.0f, 30.f)), LAYER_KIND::OPAQUENESS, 0);
		m_rObjectIntegrator.Register(new Player(WindowMeasure::GetNormalizeVector(5.0f, 50.f)), LAYER_KIND::OPAQUENESS, 0);
		//m_rObjectIntegrator.Register(new Player(WindowMeasure::GetNormalizeVector(5.0f, 70.f)), LAYER_KIND::OPAQUENESS, 0);
		m_rObjectIntegrator.Register(
			new Target(
				D3DXVECTOR3(WindowMeasure::GetNormalizeX(90.0f), 0.0f, 0.9f), WindowMeasure::GetNormalize(5.0f, 10.0f), 3.0f),
			LAYER_KIND::OPAQUENESS, 0);

		LoadResouces();

		m_rGameFramework.LoopStart(_T("BGM"));
	}

	void InGameScene::Finalize()
	{
		
	}

	void InGameScene::LoadResouces()
	{
		CreateTexture(_T("BACKGROUND"), _T("Textures/InGame_background.png"));
		CreateTexture(_T("BACKGROUND_00"), _T("Textures/InGame_background00.png"));
		CreateTexture(_T("BACKGROUND_01"), _T("Textures/InGame_background01.png"));
		CreateTexture(_T("BACKGROUND_02"), _T("Textures/InGame_background02.png"));
		CreateTexture(_T("BACKGROUND_03"), _T("Textures/InGame_background03.png"));
		CreateTexture(_T("PLAYER"), _T("Textures/InGame_player.png"));
		CreateTexture(_T("BULLET"), _T("Textures/InGame_bullet.png"));
		CreateTexture(_T("BULLET_CHARGE"), _T("Textures/InGame_bulletCharge.png"));
		CreateTexture(_T("TARGET"), _T("Textures/InGame_target.png"));

		CreateTexture(_T("BACKGROUND_00"), _T("Textures/InGame_background.png"));
		CreateTexture(_T("BACKGROUND_01"), _T("Textures/InGame_background01.png"));
		CreateTexture(_T("BACKGROUND_02"), _T("Textures/InGame_background02.png"));
		CreateTexture(_T("BACKGROUND_03"), _T("Textures/InGame_background03.png"));

		CreateFont(_T("POINT"), WindowMeasure::GetNormalize(1.8f, 6.0f), _T("IPAex–¾’©"));

		m_rGameFramework.AddFile(_T("Sounds/n28.mp3"), _T("BGM"), Sound::SoundType::BGM);
		m_rGameFramework.AddSimultaneousFile(_T("Sounds/Charge.mp3"), _T("CHARGE"), Sound::SoundType::SE);
		m_rGameFramework.AddSimultaneousFile(_T("Sounds/Hit_M.mp3"), _T("HIT_M"), Sound::SoundType::SE);
		m_rGameFramework.AddSimultaneousFile(_T("Sounds/Shoot.mp3"), _T("SHOOT"), Sound::SoundType::SE);

		m_rGameFramework.SetVolume(50, Sound::SoundType::SE);
		m_rGameFramework.SetVolume(80, Sound::SoundType::BGM);
	}
}
