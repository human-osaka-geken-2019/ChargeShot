#include "HighScoreText.h"

namespace chargeshot
{
	HighScoreText::HighScoreText(const TCHAR* pFontKey, const D3DXVECTOR2& position, DWORD format)
		:ObjectText(pFontKey, format)
	{
		InitializeeTopLeft(position);
	}

	HighScoreText::~HighScoreText()
	{

	}

	void HighScoreText::Update()
	{
		CreateHighScoreString();
	}

	void HighScoreText::CreateHighScoreString()
	{
		SetStream(_T("HIGH SCORE: "));
		AddStream(totstring(PointChecker::CreateAndGetRef().GetHighScore()));
	}

	void HighScoreText::InitializeeTopLeft(const D3DXVECTOR2& position)
	{
		SetTopLeft(position);
	}
}
