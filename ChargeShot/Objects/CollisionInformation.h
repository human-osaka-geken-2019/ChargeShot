#ifndef COLLISION_INFORMATION_H
#define COLLISION_INFORMATION_H

#include <vector>

#include <GameFramework.h>

#include "ICollider.h"
#include "IOnCollisionStay.h"

namespace chargeshot
{
	using gameframework::tstring;

	struct CollisionInformation
	{
	public:
		CollisionInformation() = default;

		CollisionInformation(ICollider* pICollider, IOnCollisionStay* pIOnCollisionStay = nullptr);

		ICollider* m_pICollider = nullptr;

		IOnCollisionStay* m_pIOnCollisionStay = nullptr;

		std::vector<tstring> m_colliderCollidedKeys;
	};
}

#endif //!COLLISION_INFORMATION_H
