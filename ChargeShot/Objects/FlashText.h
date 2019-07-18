#ifndef FLASH_TEXT_H
#define FLASH_TEXT_H

#include <GameFramework.h>

#include "ObjectText.h"

namespace chargeshot
{
	using gameframework::GameFramework;
	using gameframework::Color;
	using gameframework::Stream;
	using gameframework::tstring;

	class FlashText :public ObjectText
	{
	public:
		FlashText(const TCHAR* pFontKey, int flashFrameMax, UINT format = DT_CENTER);
		FlashText(const TCHAR* pFontKey, int flashFrameMax, const D3DXVECTOR2& topLeft,
			const tstring& stream, UINT format = DT_CENTER, const Color& color = 0xFFFFFFFF);

		virtual ~FlashText();

		virtual void Update()override;

	protected:
		const int FLASH_FRAME_MAX;

	private:
		FlashText(const FlashText& flashText) = delete;
		FlashText& operator=(FlashText& flashText) = delete;
	};
}

#endif // !FLASH_TEXT_H
