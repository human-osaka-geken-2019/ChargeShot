#include "CollisionInformation.h"

namespace chargeshot
{
	CollisionInformation::CollisionInformation(ICollider* pICollider, IOnCollisionStay* pIOnCollisionStay, IMovement* pIMovement)
		:m_pICollider(pICollider), m_pIOnCollisionStay(pIOnCollisionStay), m_pIMovement(pIMovement)
	{

	}
}
