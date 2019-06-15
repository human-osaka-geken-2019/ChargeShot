#ifndef COLLISION_INFORMATION_H
#define COLLISION_INFORMATION_H

#include <vector>

#include <GameFramework.h>

#include "ICollider.h"

namespace chargeshot
{
	using gameframework::tstring;

	struct CollisionInformation
	{
	public:
		CollisionInformation() = default;

		CollisionInformation(ICollider* pICollider);

		ICollider* m_pICollider = nullptr;

		std::vector<tstring> m_colliderCollidedKeys;
	};
}

#endif //!COLLISION_INFORMATION_H
