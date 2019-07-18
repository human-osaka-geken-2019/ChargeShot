#include "PointTextCreater.h"

namespace chargeshot
{
	PointTextCreater::PointTextCreater(const TCHAR* pFontKey) 
		:ObjectText(pFontKey, DT_LEFT)
	{
		SetTopLeft();
		SetGradeTexts();
	}

	PointTextCreater::~PointTextCreater()
	{

	}

	void PointTextCreater::CreateTotalScoreString()
	{
		SetStream(_T("SCORE:"));
		AddStream(totstring(m_rPointChecker.GetTotalPoint()));
	}

	void PointTextCreater::CreateScoreString(int point, int flashFrameMax)
	{
		GameFramework::CreateAndGetRef().OneShotSimultaneous(_T("HIT_M"));

		auto pPointText = new InstantaneousText(_T("POINT_L"), flashFrameMax,
			WindowMeasure::GetNormalizeVector(60.0f, 35.0f),
			_T("+") + totstring(point), DT_CENTER);

		ObjectIntegrator::CreateAndGetRef().Register(pPointText, LAYER_KIND::UI, 90);

		auto gradeText = m_gradeTexts[(static_cast<size_t>(point) - 1) / (PointChecker::POINT_MAX / m_gradeTexts.size())];

		auto pPointEvalutionText = new InstantaneousText(_T("POINT_M"), flashFrameMax,
			WindowMeasure::GetNormalizeVector(60.0f, 65.0f), gradeText);

		ObjectIntegrator::CreateAndGetRef().Register(pPointEvalutionText, LAYER_KIND::UI, 90);
	}

	void PointTextCreater::Update()
	{
		CreateTotalScoreString();

		if (!m_rPointChecker.IsPointGot()) return;

		CreateScoreString(m_rPointChecker.GetPoint(), 50);
	}

	void PointTextCreater::SetTopLeft()
	{
		m_pStream->SetTopLeft(WindowMeasure::GetNormalizeVector(15.0f, 46.0f));
	}

	void PointTextCreater::SetGradeTexts()
	{
		m_gradeTexts.push_back(_T("BAD"));
		m_gradeTexts.push_back(_T("GOOD"));
		m_gradeTexts.push_back(_T("GREAT"));
		m_gradeTexts.push_back(_T("EXCELLENT"));
	}
}
