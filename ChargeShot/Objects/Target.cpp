#include "Target.h"

namespace chargeshot
{
	Target::Target(const D3DXVECTOR3& startPosition, const RectSize& size, float quakeTime_sec)
		:Object2D(_T("TARGET")), m_movement(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{
		RegisterOnCollisionChecker();

		InstantiateCounter(quakeTime_sec);

		FormVertices(startPosition, size);
	}

	Target::~Target()
	{
		Finalize();
	}

	void Target::Update()
	{
		Move();
	}

	Vertices* Target::GetVerticesPtr()
	{
		return m_pVertices;
	}

	COLLIDER_KIND Target::GetColliderKind()
	{
		return m_colliderKind;
	}

	D3DXVECTOR3 Target::GetMovement()
	{
		return m_movement;
	}
	
	void Target::Finalize()
	{
		delete m_pQuakeMovingCounter;
	}

	D3DXVECTOR3 Target::CalculateMovement()
	{
		m_movement = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_movement.y =
			WindowMeasure::GetNormalizeY(100.0f * m_pQuakeMovingCounter->Update()) - 
			m_pVertices->GetCenter().y;

		return m_movement;
	}

	void Target::Move()
	{
		m_pVertices->GetCenter() += CalculateMovement();
	}
	
	void Target::RegisterOnCollisionChecker()
	{
		CollisionChecker::CreateAndGetRef().Register(_T("TARGET"), this);
	}

	void Target::InstantiateCounter(float quakeTime_sec)
	{
		m_pQuakeMovingCounter = new QuakeCounter_sec(quakeTime_sec);
	}

	void Target::FormVertices(const D3DXVECTOR3& startPosition, const RectSize& size)
	{
		m_pVertices->SetCenterAndSize(startPosition, size);
	}
}
