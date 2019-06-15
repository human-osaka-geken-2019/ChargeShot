#include "Bullet.h"

namespace chargeshot
{
	unsigned int Bullet::m_createNumber = 0;

	Bullet::Bullet(const D3DXVECTOR3& startPosition)
		:Object2D(_T("BULLET"), true), m_movement(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{
		RegisterOnCollisionChecker();

		InstantiateCounter();
		FormVertices(startPosition);
	}

	Bullet::~Bullet()
	{
		Finalize();
	}

	void Bullet::Update()
	{
		m_pVertices->AddRotationZ(15.0f);

		if (!m_isShot) return;

		Move();

		if (IsOutOfWindow()) m_shouldDestroyed = true;
	}

	void Bullet::Charge()
	{
		static const float SCALING_MAX = WindowMeasure::GetNormalizeX(20.0f);

		RectSize size = RectSize(SCALING_MAX, SCALING_MAX) * m_pChargeCounter->Update();
		m_pVertices->SetSize(size);

		m_rGameFramework.RegisterGraphicEffect(
			new ChargeEffect(m_pVertices->GetCenter(), 
				WindowMeasure::GetNormalizeX(20.0f), WindowMeasure::GetNormalizeX(1.0f),
				50, 35));
	}

	float Bullet::GetChargeRatio()
	{
		return m_pChargeCounter->GetProcessingRatio();
	}

	Vertices* Bullet::GetVerticesPtr()
	{
		return m_pVertices;
	}

	COLLIDER_KIND Bullet::GetColliderKind()
	{
		return m_colliderKind;
	}

	D3DXVECTOR3 Bullet::GetMovement()
	{
		return m_movement;
	}

	void Bullet::SetIsShot(bool isShot)
	{
		m_isShot = isShot;
	}

	void Bullet::Finalize()
	{
		delete m_pChargeCounter;
	}

	D3DXVECTOR3 Bullet::CalculateMovement()
	{
		static const D3DXVECTOR3 MOVEMENT_sec(WindowMeasure::GetNormalizeX(200.0f), 0.0f, 0.0f);

		return m_movement = MOVEMENT_sec * m_rGameFramework.DeltaTime_sec();
	}

	void Bullet::Move()
	{
		m_pVertices->GetCenter() += CalculateMovement();
	}

	bool Bullet::IsOutOfWindow()
	{
		float bulletLeftSidePosition = m_pVertices->GetCenter().x - 0.5f * m_pVertices->GetSize().m_width;

		return WindowMeasure::GetNormalizeX(100.0f) < bulletLeftSidePosition;
	}

	void Bullet::RegisterOnCollisionChecker()
	{
		tstring colliderKey = _T("BULLET");

		colliderKey += totstring(m_createNumber);

		CollisionChecker::CreateAndGetRef().Register(colliderKey, this);

		++m_createNumber;
	}

	void Bullet::InstantiateCounter()
	{
		m_pChargeCounter = new Counter_sec(1.5f);
	}

	void Bullet::FormVertices(const D3DXVECTOR3& startPosition)
	{
		m_pVertices->SetCenter(startPosition);
	}
}
