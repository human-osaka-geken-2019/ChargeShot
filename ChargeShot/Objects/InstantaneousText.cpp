﻿#include "InstantaneousText.h"

namespace chargeshot
{
	InstantaneousText::InstantaneousText(const TCHAR* pFontKey, int flashFrameMax, const D3DXVECTOR2& topLeft,
		const tstring& stream, UINT format, const Color& color)
		:ObjectText(pFontKey, topLeft, stream, format, color), FLASH_FRAME_MAX(flashFrameMax)
	{

	}

	InstantaneousText::~InstantaneousText()
	{

	}

	void InstantaneousText::Update()
	{
		m_pStream->Flash(FLASH_FRAME_MAX, 0, 255);

		if (++m_flashFrameCount >= FLASH_FRAME_MAX)
		{
			m_shouldDestroyed = true;
		}
	}
}