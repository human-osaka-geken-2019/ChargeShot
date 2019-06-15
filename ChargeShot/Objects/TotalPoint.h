#ifndef TOTAL_POINT_H
#define TOTAL_POINT_H

#include <GameFramework.h>

#include "ObjectText.h"
#include "PointChecker.h"
#include "WindowMeasure.h"

namespace chargeshot
{
	class TotalPoint :public ObjectText
	{
	public:
		TotalPoint(const TCHAR* pFontKey);

		~TotalPoint();

		void Update()override;

	private:
		TotalPoint(const TotalPoint& totalPoint) = delete;
		TotalPoint& operator=(TotalPoint& totalPoint) = delete;

		void SetTopLeft();

		PointChecker& m_rPointChecker = PointChecker::CreateAndGetRef();
	};
}

#endif // !TOTAL_POINT_H
