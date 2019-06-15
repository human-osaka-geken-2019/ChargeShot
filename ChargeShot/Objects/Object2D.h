#ifndef OBJECT_2D_H
#define OBJECT_2D_H

#include <GameFramework.h>

#include "Object.h"

namespace chargeshot
{
	using gameframework::GameFramework;
	using gameframework::Vertices;

	class Object2D :public Object
	{
	public:
		virtual ~Object2D();

		void Render()override;

		virtual inline bool ShouldDestroyed()const
		{
			return m_shouldDestroyed;
		}

	protected:
		Object2D(const TCHAR* pTextureKey = nullptr, bool isAdditionBlendMode = false);

		virtual void Finalize()override;

		GameFramework& m_rGameFramework = GameFramework::CreateAndGetRef();

		const TCHAR* pTEXTURE_KEY = nullptr;

		bool m_isAdditionBlendMode = false;

		Vertices* m_pVertices = nullptr;

	private:
		Object2D(const Object2D& object2D) = delete;
		Object2D& operator=(Object2D& object2D) = delete;

		void InstantiateVertices();
	};
}

#endif // !OBJECT_2D_H
