﻿#ifndef POINT_TEXT_CREATER_H
#define POINT_TEXT_CREATER_H

#include <GameFramework.h>

#include "ObjectText.h"
#include "PointChecker.h"
#include "InstantaneousText.h"
#include "WindowMeasure.h"

namespace chargeshot
{
	class PointTextCreater :public ObjectText
	{
	public:
		PointTextCreater(const TCHAR* pFontKey);

		~PointTextCreater();

		void Update()override;

	private:
		PointTextCreater(const PointTextCreater& pointTextCreater) = delete;
		PointTextCreater& operator=(PointTextCreater& pointTextCreater) = delete;

		void SetTopLeft();

		PointChecker& m_rPointChecker = PointChecker::CreateAndGetRef();
	};
}

#endif // !POINT_TEXT_CREATER_H