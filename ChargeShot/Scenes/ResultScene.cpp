#include "ResultScene.h"

namespace chargeshot
{
	using namespace gameframework;

	ResultScene::ResultScene()
	{
		Initialize();
	}

	ResultScene::~ResultScene()
	{
		Finalize();
	}

	void ResultScene::Initialize()
	{
		m_rObjectIntegrator.Register(new Background(_T("BACKGROUND"), D3DXVECTOR2(-0.1f, 0.0f)), LAYER_KIND::OPAQUENESS, -100);
		m_rObjectIntegrator.Register(new Background(_T("BACKGROUND_00"), D3DXVECTOR2(-0.35f, 0.0f)), LAYER_KIND::OPAQUENESS, -99);
		m_rObjectIntegrator.Register(new Background(_T("BACKGROUND_01"), D3DXVECTOR2(-0.4f, 0.0f)), LAYER_KIND::OPAQUENESS, -98);
		m_rObjectIntegrator.Register(new Background(_T("BACKGROUND_02"), D3DXVECTOR2(-1.0f, 0.0f)), LAYER_KIND::OPAQUENESS, -97);
		m_rObjectIntegrator.Register(new Background(_T("BACKGROUND_03"), D3DXVECTOR2(0.0f, 0.0f)), LAYER_KIND::OPAQUENESS, -96);
		m_rObjectIntegrator.Register(new Background(_T("BACKGROUND_RESULT"), D3DXVECTOR2(0.0f, 0.0f), 0.0f), LAYER_KIND::OPAQUENESS, -95);

		m_rObjectIntegrator.Register(new ResultPointTextCreater(_T("POINT_M")), LAYER_KIND::UI, 100);

		LoadResouces();

		m_rGameFramework.LoopStart(_T("BGM_RESULT"));
	}

	void ResultScene::Finalize()
	{
		m_rGameFramework.Stop(_T("BGM_RESULT"));

		Sleep(800);

		PointChecker::CreateAndGetRef().Zero();

		CollisionChecker::CreateAndGetRef().ReleaseAll();
	}

	void ResultScene::LoadResouces()
	{
		CreateTexture(_T("BACKGROUND_RESULT"), _T("Textures/Result_background.png"));
		
		CreateFont(_T("HIGH_SCORE_L"), WindowMeasure::GetNormalize(4.3f, 15.0f), _T("IPAex–¾’©"));

		m_rGameFramework.AddFile(_T("Sounds/Real.mp3"), _T("BGM_RESULT"), Sound::SoundType::BGM);

		m_rGameFramework.SetVolume(50, Sound::SoundType::SE);
		m_rGameFramework.SetVolume(80, Sound::SoundType::BGM);
	}
}
