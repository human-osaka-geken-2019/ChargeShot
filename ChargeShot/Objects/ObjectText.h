#ifndef OBJECT_TEXT_H
#define OBJECT_TEXT_H

#include <GameFramework.h>

#include "Object.h"

namespace chargeshot
{
	using gameframework::GameFramework;
	using gameframework::Color;
	using gameframework::Stream;
	using gameframework::tstring;

	class ObjectText :public Object
	{
	public:
		ObjectText(const TCHAR* pFontKey, UINT format = DT_CENTER);
		ObjectText(const TCHAR* pFontKey, const D3DXVECTOR2& topLeft,
			const tstring& stream, UINT format = DT_CENTER, const Color& color = 0xFFFFFFFF);

		virtual ~ObjectText();

		virtual void Update()override;
		void Render()override;

		void SetTopLeft(const D3DXVECTOR2& topLeft);

		void SetStream(const tstring& stream);
		void AddStream(const tstring& stream);

		void SetFormat(UINT format);

		void SetColor(const Color& color);

		virtual inline bool ShouldDestroyed()const
		{
			return m_shouldDestroyed;
		}

	protected:
		virtual void Finalize()override;

		GameFramework& m_rGameFramework = GameFramework::CreateAndGetRef();

		const TCHAR* m_pFontKey = nullptr;

		UINT m_format = DT_CENTER;

		Stream* m_pStream = nullptr;

	private:
		ObjectText(const ObjectText& objectText) = delete;
		ObjectText& operator=(ObjectText& objectText) = delete;

		void InstantiateStream();
	};
}

#endif // !OBJECT_TEXT_H
