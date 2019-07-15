#ifndef COLLISION_CHECKER_H
#define COLLISION_CHECKER_H

#include <unordered_map>
#include <vector>

#include <GameFramework.h>

#include "CollisionInformation.h"
#include "ICollider.h"
#include "IOnCollisionStay.h"
#include "Object.h"

namespace chargeshot
{
	using namespace gameframework::collision;
	using gameframework::Singleton;
	using gameframework::tstring;

	class CollisionChecker : public Singleton<CollisionChecker>
	{
	public:
		friend Singleton<CollisionChecker>;

		~CollisionChecker();

		void Register(const tstring& iColliderKey, ICollider* pICollider, IOnCollisionStay* pIOnCollisionStay = nullptr);

		void Update();

		void RunOnCollisionStay();

		CollisionInformation* GetCollisionInformationPtr(const tstring& iColliderKey);

		void ReleaseAll();

		void ReleaseDestroyed();

	private:
		CollisionChecker();

		CollisionChecker(const CollisionChecker& collisionChecker) = delete;
		CollisionChecker& operator=(const CollisionChecker& collisionChecker) = delete;

		void Finalize();

		void ClearCollidesKeys();

		bool Checked(const tstring& colliderKey, const std::vector<tstring>& collidedKeys);

		void CheckAll();
		bool CheckDouble(ICollider* pICollides, ICollider* pICollided);
		bool CheckSingle(ICollider* pICollides, ICollider* pICollided);

		std::unordered_map<tstring, CollisionInformation> m_collisionInformations;
	};
} 

#endif //!COLLISION_CHECKER_H
