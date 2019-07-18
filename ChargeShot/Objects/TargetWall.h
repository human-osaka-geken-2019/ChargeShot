#ifndef TARGET_WALL_H
#define TARGET_WALL_H

#include <GameFramework.h>

#include "CollisionChecker.h"
#include "Counter_sec.h"
#include "ICollider.h"
#include "InstantaneousText.h"
#include "IOnCollisionStay.h"
#include "Object2D.h"
#include "PointChecker.h"
#include "WindowMeasure.h"

namespace chargeshot
{
	class TargetWall :public Object2D, public ICollider, public IOnCollisionStay
	{
	public:
		TargetWall(const tstring& iColliderKey);

		virtual ~TargetWall();

		virtual void Update()override;

		virtual bool GetCollided();

		virtual inline void SetMovement(D3DXVECTOR3 movement)
		{
			m_movement = movement;
		}

		virtual inline Vertices* GetVerticesPtr()const override
		{
			return m_pVertices;
		}

		virtual inline COLLIDER_KIND GetColliderKind()const override
		{
			return m_colliderKind;
		}

		virtual inline D3DXVECTOR3 GetMovement()const override
		{
			return m_movement;
		}

		virtual inline bool GetIsKinetic()const override
		{
			return false;
		}

		virtual inline bool ShouldDestroyed()const override
		{
			return m_shouldDestroyed;
		}

		virtual inline void SetShouldDestroyed(bool shouldDestroyed) override
		{
			m_shouldDestroyed = shouldDestroyed;
		}

		virtual inline tstring GetColliderKey()override
		{
			return I_COLLIDER_KEY;
		}

		virtual void OnCollisionStay(const std::vector<tstring>& colliderCollidedKeys)override;

	protected:
		virtual void Finalize()override;

		virtual void JudgeAndChangeColor();
		virtual void ChangeColor();

		virtual void CreateMissText();

		const tstring I_COLLIDER_KEY;

		const COLLIDER_KIND m_colliderKind = COLLIDER_KIND::RECT;

		D3DXVECTOR3 m_movement;

		PointChecker& m_rPointChecker = PointChecker::CreateAndGetRef();

		Counter_sec* m_pColorChangingDelayCounter = new Counter_sec(1.0f);

		const DWORD DEFAULT_COLOR = 0xFFFFFFFF;

	private:
		TargetWall(const TargetWall& targetWall) = delete;
		TargetWall& operator=(TargetWall& targetWall) = delete;

		void RegisterOnCollisionChecker()override;
	};
}

#endif // !TARGET_WALL_H
