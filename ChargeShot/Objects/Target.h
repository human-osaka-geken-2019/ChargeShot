#ifndef TARGET_H
#define TARGET_H

#include <GameFramework.h>

#include "ChargeEffect.h"
#include "CollisionChecker.h"
#include "Counter_sec.h"
#include "ICollider.h"
#include "IMovement.h"
#include "Object2D.h"
#include <QuakeCounter_sec.h>
#include "WindowMeasure.h"

namespace chargeshot
{
	class Target :public Object2D, public ICollider, public IMovement
	{
	public:
		Target(const D3DXVECTOR3& startPosition, const RectSize& size, float quakeTime_sec);

		virtual ~Target();

		virtual void Update()override;

		virtual Vertices* GetVerticesPtr()override;

		virtual COLLIDER_KIND GetColliderKind()override;

		virtual D3DXVECTOR3 GetMovement()override;

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

		virtual void RegisterOnCollisionChecker()override;

		QuakeCounter_sec* m_pQuakeMovingCounter = nullptr;

		COLLIDER_KIND m_colliderKind = COLLIDER_KIND::RECT;

		D3DXVECTOR3 m_movement;

	private:
		Target(const Target& target) = delete;
		Target& operator=(Target& target) = delete;

		void InstantiateCounter(float quakeTime_sec);

		void FormVertices(const D3DXVECTOR3& startPosition, const RectSize& size);
	};
}

#endif // !TARGET_H
