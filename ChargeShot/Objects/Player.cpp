#include "Player.h"

namespace chargeshot
{
	using namespace gameframework;

	Player::Player(const D3DXVECTOR2& position) :Object2D(_T("PLAYER"))
	{
		FormVertices(position);
	}

	Player::~Player()
	{

	}

	void Player::FormVertices(const D3DXVECTOR2& position)
	{
		D3DXVECTOR2 centerVector2 = position;

		D3DXVECTOR3 centerVector3(centerVector2.x, centerVector2.y, 0.9f);

		m_pVertices->SetCenterAndSize(centerVector3, WindowMeasure::GetNormalize_x(4.0f));
	}

	void Player::Update()
	{
		m_pVertices->AddRotationZ(2.0f);

		static const auto SHOOT_KEY = DIK_RETURN;
		static const auto SHOOT_BUTTON = DirectX8Mouse::DIM_LEFT;

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

	void Player::LoadBullet()
	{
		if (m_pBullet) return;

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
		m_rGameFramework.Stop(_T("CHARGE"));
		m_rGameFramework.OneShotSimultaneous(_T("SHOOT"));

		if (!m_pBullet) return;

		m_pBullet->SetIsShot(true);

		m_pBullet = nullptr;
	}
}
