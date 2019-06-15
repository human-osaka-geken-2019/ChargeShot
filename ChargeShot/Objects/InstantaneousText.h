#ifndef INSTANTANEOUS_TEXT_H
#define INSTANTANEOUS_TEXT_H

#include <GameFramework.h>

#include "ObjectText.h"
#include "PointChecker.h"
#include "WindowMeasure.h"

namespace chargeshot
{
	class InstantaneousText :public ObjectText
	{
	public:
		InstantaneousText(const TCHAR* pFontKey, int flashFrameMax, const D3DXVECTOR2& topLeft,
			const tstring& stream, UINT format = DT_CENTER, const Color& color = 0xFFFFFFFF);
		~InstantaneousText();

		virtual void Update()override;

	protected:
		const int FLASH_FRAME_MAX;
		int m_flashFrameCount = 0;

	private:
		InstantaneousText(const InstantaneousText& instantaneousText) = delete;
		InstantaneousText& operator=(InstantaneousText& instantaneousText) = delete;
	};
}

#endif // !INSTANTANEOUS_TEXT_H
