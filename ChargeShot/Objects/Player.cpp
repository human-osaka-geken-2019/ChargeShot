#include "Player.h"

namespace chargeshot
{
	using namespace gameframework;
	using namespace gameframework::algorithm;

	Player::Player(const D3DXVECTOR2& position) :Object2D(_T("PLAYER"))
	{
		InstantiateCounter();
		
		InstantiateRemainingBulletText();

		InstantiateChargeMeters();

		FormVertices(position);
	}

	Player::~Player()
	{
		Finalize();
	}

	void Player::Update()
	{
		m_pVertices->AddRotationZ(2.0f);

		JudgeAndChangeScene();

		static const auto SHOOT_KEY = DIK_RETURN;
		static const auto SHOOT_BUTTON = DirectX8Mouse::DIM_LEFT;

		UpdateRemainingBulletNumText();

		m_pShotIntervalCounter->Update();

		FormChargeMetersVertices();

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

	void Player::Finalize()
	{
		delete m_pShotIntervalCounter;
	}

	void Player::JudgeAndChangeScene()
	{
		if (m_remainingBulletNum > 0) return;

		if (m_pSceneChageDelayCounter->Update() < 1.0f) return;

		SceneSwitchMediator::CreateAndGetRef().SendSwitchEvent(SCENE_KIND::RESULT);
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

	void Player::FormChargeMetersVertices()
	{
		static float rotationDegreeZ = 0.0f;

		RectSize mySize(m_pVertices->GetSize());
		RectSize bulletSize((m_pBullet)? m_pBullet->GetVerticesPtr()->GetSize() : mySize);
		RectSize biggerSize = algorithm::Tertiary(mySize.m_height > bulletSize.m_height, mySize, bulletSize);

		RectSize metersSize(WindowMeasure::GetNormalize_x(2.0f));

		float radiusDifference = 0.8f * biggerSize.m_width - m_chargeMeterRadius;
		float differenceSign = Tertiary(radiusDifference >= 0, +1.0f, -1.0f);
		const float RADIUS_DIFFERENCE_LIMIT = WindowMeasure::GetNormalizeVector_x(0.2f).x;
		m_chargeMeterRadius += Tertiary(fabsf(radiusDifference) > RADIUS_DIFFERENCE_LIMIT,
			differenceSign * RADIUS_DIFFERENCE_LIMIT, radiusDifference);
		D3DXVECTOR3 radiusVector(m_chargeMeterRadius, 0.0f, 0.0f);

		D3DXVECTOR3 myCenter(m_pVertices->GetCenter());

		float additionalDegree = 360 / _countof(m_pChargeMeters);

		for (auto& pMeter : m_pChargeMeters)
		{
			int index = static_cast<int>(&pMeter - &m_pChargeMeters[0]);

			D3DXVec3RotationZ(&radiusVector, (index == 0) ? rotationDegreeZ : additionalDegree);

			auto& rVertices = *pMeter->GetVerticesPtr();
			rVertices.SetCenterAndSize(myCenter + radiusVector, metersSize);
			rVertices.GetCenter().z = myCenter.z;

			rVertices.SetRotationZ(rotationDegreeZ + additionalDegree * index);
		}

		rotationDegreeZ += 5.0f;
	}

	void Player::InstantiateCounter()
	{
		m_pSceneChageDelayCounter = new Counter_sec(1.2f);
		m_pShotIntervalCounter = new Counter_sec(0.2f);
	}

	void Player::InstantiateRemainingBulletText()
	{
		m_pRemainingBulletNumText = new ObjectText(_T("POINT_M"),
			WindowMeasure::GetNormalizeVector(15.0f, 50.1f), _T(""), DT_LEFT);

		m_rObjectIntegrator.Register(m_pRemainingBulletNumText, LAYER_KIND::UI, 90);
	}

	void Player::InstantiateChargeMeters()
	{
		for (auto& rpChargeMeter : m_pChargeMeters)
		{
			rpChargeMeter = new Rect(_T("CHARGE_METER"));

			m_rObjectIntegrator.Register(rpChargeMeter, LAYER_KIND::OPAQUENESS, 1);
		}
	}

	void Player::FormVertices(const D3DXVECTOR2& position)
	{
		D3DXVECTOR2 centerVector2 = position;

		D3DXVECTOR3 centerVector3(centerVector2.x, centerVector2.y, 0.9f);

		m_pVertices->SetCenterAndSize(centerVector3, WindowMeasure::GetNormalize_x(4.0f));
	}
}
