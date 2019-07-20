#ifndef RESULT_POINT_TEXT_CREATER_H
#define RESULT_POINT_TEXT_CREATER_H

#include <GameFramework.h>

#include "Counter_sec.h"
#include "PointTextCreater.h"
#include "SceneFader.h"
#include "SceneSwitchMediator.h"

namespace chargeshot
{
	class ResultPointTextCreater :public PointTextCreater
	{
	public:
		ResultPointTextCreater(const TCHAR* pFontKey);

		~ResultPointTextCreater();

		void Update()override;

	protected:
		virtual void Finalize();

		virtual void CreateTotalScoreString()override;
		virtual void JudgeAndCreateScoreString();

		const int POINTS_NUM;

		bool m_stagingEnd = false;

		int m_currentPointsIndex = 0;
		int m_totalPoint = 0;

		Counter_sec* m_pCreateDelayCounter = nullptr;
		Counter_sec* m_pTotalScoreDispalyDelayCounter = nullptr;

	private:
		ResultPointTextCreater(const ResultPointTextCreater& resultPointTextCreater) = delete;
		ResultPointTextCreater& operator=(ResultPointTextCreater& resultPointTextCreater) = delete;

		bool PointStagingIsEnded();

		void InstantiateCounter();
	};
}

#endif // !RESULT_POINT_TEXT_CREATER_H
