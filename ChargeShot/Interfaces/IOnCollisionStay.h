#ifndef I_ON_COLLISION_STAY_H
#define I_ON_COLLISION_STAY_H

#include <GameFramework.h>

#include "CollisionInformation.h"

namespace chargeshot
{
	using gameframework::Vertices;
	using gameframework::tstring;

	class IOnCollisionStay
	{
	public:
		virtual ~IOnCollisionStay() = default;

		virtual tstring GetColliderKey() = 0;

		virtual void OnCollisionStay(const std::vector<tstring>& colliderCollidedKeys) = 0;
	
	protected:
		IOnCollisionStay() = default;

		virtual void RegisterOnCollisionChecker() = 0;

	private:
		IOnCollisionStay(const IOnCollisionStay& iOnCollisionStay) = delete;
		IOnCollisionStay& operator=(IOnCollisionStay& iOnCollisionStay) = delete;
	};
}

#endif // !I_ON_COLLISION_STAY_H
