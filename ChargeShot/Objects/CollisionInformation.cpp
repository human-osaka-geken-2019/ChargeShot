#include "CollisionInformation.h"

namespace chargeshot
{
	CollisionInformation::CollisionInformation(ICollider* pICollider, IOnCollisionStay* pIOnCollisionStay)
		:m_pICollider(pICollider), m_pIOnCollisionStay(pIOnCollisionStay)
	{

	}
}
