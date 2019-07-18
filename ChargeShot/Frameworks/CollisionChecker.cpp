#include "CollisionChecker.h"

namespace chargeshot
{
	using namespace gameframework;

	CollisionChecker::~CollisionChecker()
	{
		Finalize();
	}

	void CollisionChecker::Register(const tstring& iColliderKey, ICollider* pICollider, IOnCollisionStay* pIOnCollisionStay, IMovement* pIMovement)
	{
		m_collisionInformations.emplace(std::piecewise_construct,
			std::forward_as_tuple(iColliderKey),
			std::forward_as_tuple(pICollider, pIOnCollisionStay, pIMovement));
	}

	void CollisionChecker::Unregister(const tstring& iColliderKey)
	{
		m_collisionInformations.erase(iColliderKey);
	}

	void CollisionChecker::Update()
	{
		ReleaseDestroyed();

		ClearCollidesKeys();

		CheckAll();
	}

	CollisionInformation* CollisionChecker::GetCollisionInformationPtr(const tstring& iColliderKey)
	{
		if (m_collisionInformations.count(iColliderKey) == 0) return nullptr;

		return &m_collisionInformations[iColliderKey];
	}

	void CollisionChecker::ReleaseAll()
	{
		m_collisionInformations.clear();
	}

	void CollisionChecker::ReleaseDestroyed()
	{
		for (auto& rCollisionInformation : m_collisionInformations)
		{
			if (!rCollisionInformation.second.m_pICollider->ShouldDestroyed()) continue;

			m_collisionInformations.erase(rCollisionInformation.first);

			ReleaseDestroyed();

			return;
		}
	}

	void CollisionChecker::RunOnCollisionStay()
	{
		//OnCollisionStayでcollisionInformationが書き替えらる時のため
		auto collisionInformationsCopy = m_collisionInformations;

		for (auto& rCollisionInformation : collisionInformationsCopy)
		{
			auto pIOnCollisionStay = rCollisionInformation.second.m_pIOnCollisionStay;
			auto& collidedKeys = rCollisionInformation.second.m_colliderCollidedKeys;

			if (pIOnCollisionStay && collidedKeys.size() > 0)
			{
				pIOnCollisionStay->OnCollisionStay(rCollisionInformation.second.m_colliderCollidedKeys);
			}
		}
	}

	CollisionChecker::CollisionChecker()
	{

	}

	void CollisionChecker::Finalize()
	{
		ReleaseAll();
	}

	void CollisionChecker::ClearCollidesKeys()
	{
		for (auto& rCollisionInformation : m_collisionInformations)
		{
			rCollisionInformation.second.m_colliderCollidedKeys.clear();
		}
	}

	bool CollisionChecker::Checked(const tstring& colliderKey, const std::vector<tstring>& collidedKeys)
	{
		for (auto& rCollidedKey : collidedKeys)
		{
			if (rCollidedKey == colliderKey) return true;
		}

		return false;
	}

	void CollisionChecker::CheckAll()
	{
		for (auto& rCollidesInformation : m_collisionInformations)
		{
			for (auto& rCollidedInformation : m_collisionInformations)
			{
				if (rCollidesInformation.first == rCollidedInformation.first) continue;

				auto& rCollidesInformationValue = rCollidesInformation.second;
				auto& rCollidedInformationValue = rCollidedInformation.second;

				if (Checked(rCollidedInformation.first, rCollidesInformationValue.m_colliderCollidedKeys)) continue;

				if (!CheckDouble(rCollidesInformationValue.m_pICollider,
					rCollidedInformationValue.m_pICollider)) continue;

				rCollidesInformationValue.m_colliderCollidedKeys.push_back(rCollidedInformation.first);
				rCollidedInformationValue.m_colliderCollidedKeys.push_back(rCollidesInformation.first);
			}
		}
	}

	bool CollisionChecker::CheckDouble(ICollider* pICollides, ICollider* pICollided)
	{
		ICollider* pIColliders[] = { pICollides, pICollided };

		int indexMax = _countof(pIColliders) - 1;

		for (int i = 0; i <= indexMax; ++i)
		{
			if (CheckSingle(pIColliders[i], pIColliders[indexMax - i])) return true;
		}

		return false;
	}

	bool CollisionChecker::CheckSingle(ICollider* pICollides, ICollider* pICollided)
	{
		Vertices* pCollidesVertices = nullptr;
		GameFrameworkFactory::Create(&pCollidesVertices);

		auto& rCollidesVertices = *pICollides->GetVerticesPtr();

		pCollidesVertices->SetSize(rCollidesVertices.GetSize());

		bool collided = false;

		int divideNum = 3;

		auto collidesOneDivideMovement = pICollides->GetMovement() / static_cast<float>(divideNum);

		for (int i = divideNum; i >= 0; --i)
		{
			auto collidesMovement = static_cast<float>(i) * collidesOneDivideMovement;

			pCollidesVertices->SetCenter(rCollidesVertices.GetCenter() - collidesMovement);
			pCollidesVertices->SetRotationZ(0);

			if (pICollides->GetColliderKind() == COLLIDER_KIND::RECT &&
				pICollided->GetColliderKind() == COLLIDER_KIND::POINT)
			{
				collided = IsInner(*pCollidesVertices, pICollided->GetVerticesPtr()->GetCenter());
			}

			if (pICollides->GetColliderKind() == COLLIDER_KIND::RECT &&
				pICollided->GetColliderKind() == COLLIDER_KIND::RECT)
			{
				collided = Collides(*pCollidesVertices, *pICollided->GetVerticesPtr());
			}

			if (!collided) continue;

			if (!pICollides->GetIsKinetic()) break;

			pICollides->GetVerticesPtr()->SetCenter(pCollidesVertices->GetCenter());

			break;
		}

		delete pCollidesVertices;

		return collided;
	}

	CollisionInformation* CollisionChecker::SearchCollisionInformationPointer(const ICollider* pICollider)
	{
		for (auto& rInformation : m_collisionInformations)
		{
			if (rInformation.second.m_pICollider == pICollider) return &rInformation.second;
		}

		return nullptr;
	}
}
