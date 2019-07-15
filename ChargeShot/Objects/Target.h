#ifndef TARGET_H
#define TARGET_H

#include <GameFramework.h>

#include "CollisionChecker.h"
#include "ICollider.h"
#include "LayerKind.h"
#include "IMovement.h"
#include "ObjectIntegrator.h"
#include "Object2D.h"
#include "QuakeCounter_sec.h"
#include "TargetWall.h"
#include "WindowMeasure.h"

namespace chargeshot
{
	class Target :public Object2D, public ICollider, public IMovement
	{
	public:
		Target(const D3DXVECTOR3& startPosition, const RectSize& size, float quakeTime_sec);

		virtual ~Target();

		virtual void Update()override;

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

		virtual inline void SetShouldDestroyed(bool shouldDestroyed)override
		{
			m_shouldDestroyed = shouldDestroyed;

			for (auto& rpWall : m_pWalls) rpWall->SetShouldDestroyed(shouldDestroyed);
		}

	protected:
		virtual void Finalize()override;

		virtual D3DXVECTOR3 CalculateMovement()override;
		virtual void Move()override;

		virtual void ChangeColorOnHit();

		virtual void FormWallVertices();

		const tstring I_COLLIDER_KEY = _T("TARGET");

		QuakeCounter_sec* m_pQuakeMovingCounter = nullptr;

		COLLIDER_KIND m_colliderKind = COLLIDER_KIND::RECT;

		CollisionInformation* m_pMyCollisionInformation = nullptr;

		D3DXVECTOR3 m_movement;

		TargetWall* m_pWalls[2];

		ObjectIntegrator& m_rObjectIntegrator = ObjectIntegrator::CreateAndGetRef();
	private:
		Target(const Target& target) = delete;
		Target& operator=(Target& target) = delete;

		void RegisterOnCollisionChecker()override;

		CollisionInformation* GetMyCollisionInformationPtr();
		
		void InstantiateCounter(float quakeTime_sec);

		void InstantiateWalls();

		void FormVertices(const D3DXVECTOR3& startPosition, const RectSize& size);
	};
}

#endif // !TARGET_H
