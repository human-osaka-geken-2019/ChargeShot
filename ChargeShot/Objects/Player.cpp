#include "Player.h"

namespace chargeshot
{
	using namespace gameframework;

	Player::Player(const D3DXVECTOR2& position) :Object2D(_T("PLAYER"))
	{
		InstantiateCounter();
		
		InstantiateRemainingBulletText();

		FormVertices(position);
	}

	Player::~Player()
	{

	}

	void Player::Update()
	{
		m_pVertices->AddRotationZ(2.0f);

		static const auto SHOOT_KEY = DIK_RETURN;
		static const auto SHOOT_BUTTON = DirectX8Mouse::DIM_LEFT;

		UpdateRemainingBulletNumText();

		m_pShotIntervalCounter->Update();

		if (m_rGameFramework.KeyboardIsPressed(SHOOT_KEY) ||
			m_rGameFramework.MouseIsPressed(SHOOT_BUTTON))
		{
			LoadBullet();

			return;
		}

		if (m_rGameFramework.KeyboardIsHeld(SHOOT_KEY) ||
			m_rGameFramework.MouseIsHeld(SHOOT_BUTTON))
		{
			ChargeBullet();

			return;
		}

		if (m_rGameFramework.KeyboardIsReleased(SHOOT_KEY) ||
			m_rGameFramework.MouseIsReleased(SHOOT_BUTTON))
		{
			ShootBullet();

			return;
		}
	}

	void Player::InstantiateCounter()
	{
		m_pShotIntervalCounter = new Counter_sec(0.2f);
	}

	void Player::InstantiateRemainingBulletText()
	{
		m_pRemainingBulletNumText = new ObjectText(_T("POINT"),
			WindowMeasure::GetNormalizeVector(0.0f, 0.0f), _T(""), DT_LEFT);

		m_rObjectIntegrator.Register(m_pRemainingBulletNumText, LAYER_KIND::UI, 100);
	}

	void Player::FormVertices(const D3DXVECTOR2& position)
	{
		D3DXVECTOR2 centerVector2 = position;

		D3DXVECTOR3 centerVector3(centerVector2.x, centerVector2.y, 0.9f);

		m_pVertices->SetCenterAndSize(centerVector3, WindowMeasure::GetNormalize_x(4.0f));
	}

	void Player::LoadBullet()
	{
		if (m_pBullet) return;

		if (m_pShotIntervalCounter->GetProcessingRatio() != 1.0f) return;

		if (m_remainingBulletNum <= 0) return;

		m_rGameFramework.OneShotSimultaneous(_T("CHARGE"));

		m_pBullet = new Bullet(m_pVertices->GetCenter());

		m_rObjectIntegrator.Register(m_pBullet, LAYER_KIND::TRANSPARENCY, 0);
	}

	void Player::ChargeBullet()
	{
		if (!m_pBullet) return;

		m_pBullet->Charge();

		m_pVertices->AddRotationZ(9.0f);
	}

	void Player::ShootBullet()
	{
		if (!m_pBullet) return;

		m_pBullet->SetIsShot(true);

		m_pBullet = nullptr;

		m_rGameFramework.Stop(_T("CHARGE"));
		m_rGameFramework.OneShotSimultaneous(_T("SHOOT"));

		--m_remainingBulletNum;

		m_pShotIntervalCounter->Zero();
	}

	void Player::UpdateRemainingBulletNumText()
	{
		m_pRemainingBulletNumText->SetStream(_T("AMMO:"));

		tstring bulletNumString = totstring(m_remainingBulletNum);
		m_pRemainingBulletNumText->AddStream(bulletNumString);
	}
}
