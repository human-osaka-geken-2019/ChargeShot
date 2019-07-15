#ifndef I_COLLIDER_H
#define I_COLLIDER_H

#include <GameFramework.h>

#include "ColliderKind.h"

namespace chargeshot
{
	using gameframework::Vertices;

	class ICollider
	{
	public:
		virtual ~ICollider() = default;

		virtual Vertices* GetVerticesPtr()const = 0;

		virtual COLLIDER_KIND GetColliderKind()const = 0;

		virtual D3DXVECTOR3 GetMovement()const = 0;

		virtual bool ShouldDestroyed()const = 0;
		virtual void SetShouldDestroyed(bool shouldDestroyed)  = 0;

	protected:
		ICollider() = default;

		virtual void RegisterOnCollisionChecker() = 0;

	private:
		ICollider(const ICollider& iColllider) = delete;
		ICollider& operator=(ICollider& iCollider) = delete;
	};
}

#endif // !I_COLLIDER_H
