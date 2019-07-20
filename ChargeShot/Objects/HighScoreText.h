#ifndef HIGH_SCORE_TEXT_H
#define HIGH_SCORE_TEXT_H

#include <GameFramework.h>

#include "ObjectText.h"
#include "PointChecker.h"
#include "WindowMeasure.h"

namespace chargeshot
{
	class HighScoreText :public ObjectText
	{
	public:
		HighScoreText(const TCHAR* pFontKey, const D3DXVECTOR2& position, DWORD format);

		~HighScoreText();

		void Update()override;

	protected:
		virtual void CreateHighScoreString();
		PointChecker& m_rPointChecker = PointChecker::CreateAndGetRef();

	private:
		HighScoreText(const HighScoreText& highScoreText) = delete;
		HighScoreText& operator=(HighScoreText& highScoreText) = delete;

		void InitializeeTopLeft(const D3DXVECTOR2& position);
	};
}

#endif // !HIGH_SCORE_TEXT_H
