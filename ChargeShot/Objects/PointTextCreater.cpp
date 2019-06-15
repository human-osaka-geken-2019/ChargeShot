#include "PointTextCreater.h"

namespace chargeshot
{
	PointTextCreater::PointTextCreater(const TCHAR* pFontKey) 
		:ObjectText(pFontKey, DT_RIGHT)
	{
		SetTopLeft();
	}

	PointTextCreater::~PointTextCreater()
	{

	}

	void PointTextCreater::Update()
	{
		SetStream(_T("SCORE:"));
		AddStream(totstring(m_rPointChecker.GetTotalPoint()));

		if (!m_rPointChecker.IsPointGot()) return;

		auto pPointText = new InstantaneousText(_T("POINT_S"), 30,
			WindowMeasure::GetNormalizeVector(100.0f, 6.0f),
			_T("+") + totstring(m_rPointChecker.GetPoint()), DT_RIGHT);

		ObjectIntegrator::CreateAndGetRef().Register(pPointText, LAYER_KIND::UI, 100);
	}

	void PointTextCreater::SetTopLeft()
	{
		m_pStream->SetTopLeft(WindowMeasure::GetNormalizeVector(100.0f, 0.0f));
	}
}
