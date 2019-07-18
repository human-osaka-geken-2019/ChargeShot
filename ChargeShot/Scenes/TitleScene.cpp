#include "TitleScene.h"

namespace chargeshot
{
	using namespace gameframework;

	TitleScene::TitleScene()
	{
		Initialize();
	}

	TitleScene::~TitleScene()
	{
		Finalize();
	}

	void TitleScene::Initialize()
	{
		m_rObjectIntegrator.Register(new Background(_T("BACKGROUND"), D3DXVECTOR2(0.1f, 0.0f)), LAYER_KIND::OPAQUENESS, -100);
		m_rObjectIntegrator.Register(new Background(_T("BACKGROUND_00"), D3DXVECTOR2(0.35f, 0.0f)), LAYER_KIND::OPAQUENESS, -99);
		m_rObjectIntegrator.Register(new Background(_T("BACKGROUND_01"), D3DXVECTOR2(0.4f, 0.0f)), LAYER_KIND::OPAQUENESS, -98);
		m_rObjectIntegrator.Register(new Background(_T("BACKGROUND_02"), D3DXVECTOR2(1.0f, 0.0f)), LAYER_KIND::OPAQUENESS, -97);
		m_rObjectIntegrator.Register(new Background(_T("BACKGROUND_03"), D3DXVECTOR2(0.0f, 0.0f)), LAYER_KIND::OPAQUENESS, -96);
		m_rObjectIntegrator.Register(new Background(_T("GAME_LOGO"), D3DXVECTOR2(0.0f, 0.0f)), LAYER_KIND::OPAQUENESS, -95);
		m_rObjectIntegrator.Register(new GameTitle(), LAYER_KIND::OPAQUENESS, -100);

		tstring creditStrings =
			_T("planer: haruraka tsujino\n\n")
			_T("artist: haruraka tsujino\n\n")
			_T("sound programer: masami sugao\n\n")
			_T("sound programer: toshiya matsuoka\n\n")
			_T("sound programer: harutaka tsujino\n\n")
			_T("backend programmer: haruraka tsujino\n\n")
			_T("application programmer: haruraka tsujino\n\n")
			_T("sound: å¯â âπÉâÉ{\n\n")
			_T("sound: ÉtÉäÅ[âπäyëfçﬁ H/MIX GALLERY óTòa èHéR");

		m_rObjectIntegrator.Register(
			new FlashText(_T("INPUT_PROMPT"), 120, WindowMeasure::GetNormalizeVector(50.0f, 55.0f), _T("press enter to start"), DT_CENTER), LAYER_KIND::UI, 0);
		m_rObjectIntegrator.Register(
			new ObjectText(_T("CREDIT"), WindowMeasure::GetNormalizeVector(99.9f, 99.9f), creditStrings, DT_RIGHT | DT_BOTTOM, 0xFFFFFFFF), LAYER_KIND::UI, 0);
		m_rObjectIntegrator.Register(
			new ObjectText(_T("HIGH_SCORE"), WindowMeasure::GetNormalizeVector(2.95f, 15.0f), _T("HIGH SCORE: 4580"), DT_LEFT |DT_BOTTOM), LAYER_KIND::UI, 0);

		LoadResouces();

		m_rGameFramework.LoopStart(_T("BGM_TITLE"));
	}

	void TitleScene::Finalize()
	{
		m_rGameFramework.Stop(_T("BGM_TITLE"));

		Sleep(800);

		CollisionChecker::CreateAndGetRef().ReleaseAll();

		PointChecker::CreateAndGetRef().Zero();
	}

	void TitleScene::LoadResouces()
	{
		m_rGameFramework.CreateTexture(_T("íÜãÛÇ´â~"), _T("Textures/íÜãÛÇ´â~.png"));
		m_rGameFramework.CreateTexture(_T("îíê≥ï˚å`"), _T("Textures/îíê≥ï˚å`.png"));

		m_rGameFramework.CreateTexture(_T("BACKGROUND"), _T("Textures/InGame_background.png"));
		m_rGameFramework.CreateTexture(_T("BACKGROUND_00"), _T("Textures/InGame_background00.png"));
		m_rGameFramework.CreateTexture(_T("BACKGROUND_01"), _T("Textures/InGame_background01.png"));
		m_rGameFramework.CreateTexture(_T("BACKGROUND_02"), _T("Textures/InGame_background02.png"));
		m_rGameFramework.CreateTexture(_T("BACKGROUND_03"), _T("Textures/InGame_background03.png"));

		CreateTexture(_T("GAME_LOGO"), _T("Textures/Title_gameLogo.png"));

		CreateFont(_T("HIGH_SCORE"), WindowMeasure::GetNormalize(1.3f, 4.2f), _T("IPAexñæí©"));
		CreateFont(_T("INPUT_PROMPT"), WindowMeasure::GetNormalize(0.9f, 3.0f), _T("IPAexñæí©"));
		CreateFont(_T("CREDIT"), WindowMeasure::GetNormalize(0.5f, 2.0f), _T("IPAexñæí©"));

		m_rGameFramework.AddFile(_T("Sounds/tw051.mp3"), _T("BGM_TITLE"), Sound::SoundType::BGM);
		m_rGameFramework.AddSimultaneousFile(_T("Sounds/Charge.mp3"), _T("CHARGE"), Sound::SoundType::SE);

		m_rGameFramework.SetVolume(50, Sound::SoundType::SE);
		m_rGameFramework.SetVolume(80, Sound::SoundType::BGM);
	}
}
