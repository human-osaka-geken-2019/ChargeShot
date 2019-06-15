#ifndef BULLET_H
#define BULLET_H

#include <GameFramework.h>

#include "ChargeEffect.h"
#include "CollisionChecker.h"
#include "Counter_sec.h"
#include "ICollider.h"
#include "IMovement.h"
#include "Object2D.h"
#include "WindowMeasure.h"

namespace chargeshot
{
	class Bullet :public Object2D, public ICollider, public IMovement
	{
	public:
		explicit Bullet(const D3DXVECTOR3& startPosition);

		virtual ~Bullet();

		virtual void Update()override;

		virtual void Charge();

		float GetChargeRatio();

		virtual Vertices* GetVerticesPtr()override;

		virtual COLLIDER_KIND GetColliderKind()override;

		virtual D3DXVECTOR3 GetMovement()override;

		void SetIsShot(bool isShot);

		virtual inline bool ShouldDestroyed()const
		{
			return m_shouldDestroyed;
		}

		virtual inline void SetShouldDestroyed(bool shouldDestroyed)
		{
			m_shouldDestroyed = shouldDestroyed;
		}

	protected:
		virtual void Finalize()override;

		virtual D3DXVECTOR3 CalculateMovement()override;
		virtual void Move()override;

		bool IsOutOfWindow();

		virtual void RegisterOnCollisionChecker()override;

		Counter_sec* m_pChargeCounter = nullptr;

		bool m_isShot = false;

		COLLIDER_KIND m_colliderKind = COLLIDER_KIND::POINT;

		D3DXVECTOR3 m_movement;

		static unsigned int m_createNumber;

	private:
		Bullet(const Bullet& bullet) = delete;
		Bullet& operator=(Bullet& bullet) = delete;

		void InstantiateCounter();
		
		void FormVertices(const D3DXVECTOR3& startPosition);
	};
}

#endif // !BULLET_H
