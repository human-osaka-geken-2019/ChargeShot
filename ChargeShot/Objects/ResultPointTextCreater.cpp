#include "ResultPointTextCreater.h"

namespace chargeshot
{
	ResultPointTextCreater::ResultPointTextCreater(const TCHAR* pFontKey)
		:PointTextCreater(pFontKey), POINTS_NUM(static_cast<int>(m_rPointChecker.GetPointsPointer()->size()))
	{
		InstantiateCounter();
	}

	ResultPointTextCreater::~ResultPointTextCreater()
	{
		Finalize();
	}

	void ResultPointTextCreater::Update()
	{
		if (SceneFader::GetStagingFinished())
		{
			JudgeAndCreateScoreString();
		}

		CreateTotalScoreString();
	}

	void ResultPointTextCreater::Finalize()
	{
		delete m_pCreateDelayCounter;
		delete m_pTotalScoreDispalyDelayCounter;
	}

	void ResultPointTextCreater::CreateTotalScoreString()
	{
		SetStream(_T("SCORE:"));
		AddStream(totstring(m_totalPoint));

		if (!PointStagingIsEnded()) return;

		if (m_pTotalScoreDispalyDelayCounter->Update() < 1.0f) return;

		D3DXVECTOR2 topLeft = WindowMeasure::GetNormalizeVector(50.0f, 45.0f);

		if (m_rPointChecker.GetUpdatedHighPoint())
		{
			SetStream(_T("New Best!!\nSCORE:"));
			AddStream(totstring(m_rPointChecker.GetTotalPoint()));

			topLeft.y -= WindowMeasure::GetNormalizeY(8.0f);
		}

		static_cast<ObjectText*>(this)->SetTopLeft(topLeft);

		m_format = DT_CENTER;
		m_pFontKey = _T("HIGH_SCORE_L");

		if (m_rGameFramework.KeyboardIsPressed(DIK_RETURN))
		{
			SceneSwitchMediator::GetRef().SendSwitchEvent(SCENE_KIND::TITLE);
		}

		if (m_stagingEnd) return;

		GameFramework::CreateAndGetRef().OneShotSimultaneous(_T("HIT_M"));

		m_stagingEnd = true;
	}

	void ResultPointTextCreater::JudgeAndCreateScoreString()
	{
		if (m_pCreateDelayCounter->Update() < 1.0f) return;

		m_pCreateDelayCounter->Zero();

		if (PointStagingIsEnded()) return;

		auto& rPoints = *m_rPointChecker.GetPointsPointer();
		auto point = rPoints.at(m_currentPointsIndex++);

		m_totalPoint += point;

		CreateScoreString(point, 30);
	}

	bool ResultPointTextCreater::PointStagingIsEnded()
	{
		return m_currentPointsIndex >= POINTS_NUM;
	}

	void ResultPointTextCreater::InstantiateCounter()
	{
		m_pCreateDelayCounter = new Counter_sec(0.4f);
		m_pTotalScoreDispalyDelayCounter = new Counter_sec(0.6f);
	}
}
