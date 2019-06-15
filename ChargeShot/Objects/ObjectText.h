#ifndef OBJECT_TEXT_H
#define OBJECT_TEXT_H

#include <GameFramework.h>

#include "Object.h"

namespace chargeshot
{
	using gameframework::GameFramework;
	using gameframework::Stream;

	class ObjectText :public Object
	{
	public:
		virtual ~ObjectText();

		void Render()override;

		virtual inline bool ShouldDestroyed()const
		{
			return m_shouldDestroyed;
		}

	protected:
		ObjectText(const TCHAR* pFontKey, UINT format = DT_CENTER);

		virtual void Finalize()override;

		GameFramework& m_rGameFramework = GameFramework::CreateAndGetRef();

		const TCHAR* pFONT_KEY = nullptr;

		UINT m_format = DT_CENTER;

		Stream* m_pStream = nullptr;

	private:
		ObjectText(const ObjectText& objectText) = delete;
		ObjectText& operator=(ObjectText& objectText) = delete;

		void InstantiateStream();
	};
}

#endif // !OBJECT_TEXT_H
