#include "TotalPoint.h"

namespace chargeshot
{
	TotalPoint::TotalPoint(const TCHAR* pFontKey)
		:ObjectText(pFontKey, DT_RIGHT)
	{
		SetTopLeft();
	}

	TotalPoint::~TotalPoint()
	{

	}

	void TotalPoint::Update()
	{
		*m_pStream = totstring(m_rPointChecker.GetTotalPoint());
	}

	void TotalPoint::SetTopLeft()
	{
		m_pStream->SetTopLeft(WindowMeasure::GetNormalizeVector(100.0f, 0.0f));
	}
}
