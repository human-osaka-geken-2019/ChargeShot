#include "Bullet.h"

namespace chargeshot
{
	unsigned int Bullet::m_createNumber = 0;

	using gameframework::HoldEffect;

	Bullet::Bullet(const D3DXVECTOR3& startPosition)
		:Object2D(_T("BULLET"), true), m_movement(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{
		RegisterOnCollisionChecker();

		m_iColliderKey = CreateICollierKey();

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

	void Bullet::OnCollisionStay(const std::vector<tstring>& colliderCollidedKeys)
	{
		if (m_rPointChecker.AlreadyPassed(GetColliderKey())) return;

		for (auto collidedKey : colliderCollidedKeys)
		{
			if (collidedKey.find(_T("TARGET_WALL")) != tstring::npos) m_collidedWithWall = true;
		}

		if (!m_collidedWithWall) return;

		PerformCollided();
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
		if (m_collidedWithWall) return;

		m_pVertices->GetCenter() += CalculateMovement();

		auto effectPosition = m_pVertices->GetCenter();
		effectPosition.z = 0.0f;

		m_rGameFramework.RegisterGraphicEffect(new HoldEffect(effectPosition));
	}

	void Bullet::PerformCollided()
	{
		m_pVertices->SetColor(0x00FFFFFF);

		auto effectPosition = m_pVertices->GetCenter();
		effectPosition.z = 0.0f;

		m_rGameFramework.RegisterGraphicEffect(new CollidingEffect(effectPosition));

		SetShouldDestroyed(true);
	}

	bool Bullet::IsOutOfWindow()
	{
		float bulletLeftSidePosition = m_pVertices->GetCenter().x - 0.5f * m_pVertices->GetSize().m_width;

		return WindowMeasure::GetNormalizeX(100.0f) < bulletLeftSidePosition;
	}

	void Bullet::RegisterOnCollisionChecker()
	{
		++m_createNumber;

		CollisionChecker::CreateAndGetRef().Register(CreateICollierKey(), this, this);
	}

	tstring Bullet::CreateICollierKey()
	{
		tstring iColliderKey = _T("BULLET");

		iColliderKey += totstring(m_createNumber);

		return iColliderKey;
	}

	void Bullet::InstantiateCounter()
	{
		m_pChargeCounter = new Counter_sec(1.5f);
	}

	void Bullet::FormVertices(const D3DXVECTOR3& startPosition)
	{
		m_pVertices->SetCenterAndSize(startPosition, WindowMeasure::GetNormalize(1.0f));
	}
}
