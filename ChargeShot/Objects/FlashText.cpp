#include "FlashText.h"

namespace chargeshot
{
	using gameframework::GameFrameworkFactory;

	FlashText::FlashText(const TCHAR* pFontKey, int flashFrameMax, UINT format) 
		:ObjectText(pFontKey, format), FLASH_FRAME_MAX(flashFrameMax)
	{

	}

	FlashText::FlashText(const TCHAR* pFontKey, int flashFrameMax, const D3DXVECTOR2& topLeft,
		const tstring& stream, UINT format, const Color& color)
		: ObjectText(pFontKey, topLeft, stream, format, color), FLASH_FRAME_MAX(flashFrameMax)
	{

	}

	FlashText::~FlashText()
	{

	}

	void FlashText::Update()
	{
		m_pStream->Flash(FLASH_FRAME_MAX, 0, 255);
	}
}
