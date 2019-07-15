#ifndef RECT_H
#define RECT_H

#include <GameFramework.h>

#include "Object2D.h"
#include "WindowMeasure.h"

namespace chargeshot
{
	using gameframework::tstring;

	class Rect :public Object2D
	{
	public:
		Rect(const TCHAR* pTextureKey);

		virtual ~Rect();

		virtual void Update()override;

		inline virtual Vertices* GetVerticesPtr()
		{
			return m_pVertices;
		}

		inline virtual bool ShouldDestroyed()const override
		{
			return m_shouldDestroyed;
		}

		inline virtual void SetShouldDestroyed(bool shouldDestroyed)
		{
			m_shouldDestroyed = shouldDestroyed;
		}

	protected:
		virtual void Finalize()override;

	private:
		Rect(const Rect& rect) = delete;
		Rect& operator=(Rect& rect) = delete;
	};
}

#endif // !RECT_H
