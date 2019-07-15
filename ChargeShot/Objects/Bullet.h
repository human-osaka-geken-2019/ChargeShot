#ifndef BULLET_H
#define BULLET_H

#include <GameFramework.h>

#include "ChargeEffect.h"
#include "CollidingEffect.h"
#include "CollisionChecker.h"
#include "Counter_sec.h"
#include "HoldEffect.h"
#include "ICollider.h"
#include "IMovement.h"
#include "IOnCollisionStay.h"
#include "Object2D.h"
#include "PointChecker.h"
#include "WindowMeasure.h"

namespace chargeshot
{
	class Bullet :public Object2D, public ICollider, public IMovement, public IOnCollisionStay
	{
	public:
		explicit Bullet(const D3DXVECTOR3& startPosition);

		virtual ~Bullet();

		virtual void Update()override;

		virtual void Charge();

		virtual inline float GetChargeRatio()const
		{
			return m_pChargeCounter->GetProcessingRatio();
		}

		virtual inline void SetIsShot(bool isShot)
		{
			m_isShot = isShot;
		}

		virtual inline Vertices* GetVerticesPtr()const
		{
			return m_pVertices;
		}

		virtual inline COLLIDER_KIND GetColliderKind()const
		{
			return m_colliderKind;
		}
		
		virtual inline D3DXVECTOR3 GetMovement()const
		{
			return m_movement;
		}

		virtual inline bool ShouldDestroyed()const override
		{
			return m_shouldDestroyed;
		}

		virtual inline void SetShouldDestroyed(bool shouldDestroyed)
		{
			m_shouldDestroyed = shouldDestroyed;
		}

		virtual inline tstring GetColliderKey()override
		{
			return m_iColliderKey;
		}

		virtual void OnCollisionStay(const std::vector<tstring>& colliderCollidedKeys)override;

	protected:
		virtual void Finalize()override;

		virtual D3DXVECTOR3 CalculateMovement()override;
		virtual void Move()override;

		virtual void PerformCollided();

		bool IsOutOfWindow();

		Counter_sec* m_pChargeCounter = nullptr;

		bool m_isShot = false;

		bool m_collidedWithWall = false;

		COLLIDER_KIND m_colliderKind = COLLIDER_KIND::RECT;

		D3DXVECTOR3 m_movement;

		static unsigned int m_createNumber;

		tstring m_iColliderKey;

		CollisionInformation* m_pMyCollisionInformation = nullptr;

		PointChecker& m_rPointChecker = PointChecker::CreateAndGetRef();

	private:
		Bullet(const Bullet& bullet) = delete;
		Bullet& operator=(Bullet& bullet) = delete;
		
		void RegisterOnCollisionChecker()override;

		tstring CreateICollierKey();

		void InstantiateCounter();
		
		void FormVertices(const D3DXVECTOR3& startPosition);
	};
}

#endif // !BULLET_H
