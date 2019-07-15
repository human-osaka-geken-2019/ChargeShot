#include "TargetWall.h"

namespace chargeshot
{
	using gameframework::Color;

	TargetWall::TargetWall(const tstring& iColliderKey)
		:Object2D(_T("TARGET_WALL")), m_movement(D3DXVECTOR3(0.0f, 0.0f, 0.0f)), I_COLLIDER_KEY(iColliderKey)
	{
		RegisterOnCollisionChecker();
	}

	TargetWall::~TargetWall()
	{
		Finalize();
	}

	void TargetWall::Update()
	{
		JudgeAndChangeColor();
	}
	void TargetWall::OnCollisionStay(const std::vector<tstring>& colliderCollidedKeys)
	{
		bool collidedWithBullet = false;

		for (auto collidedKey : colliderCollidedKeys)
		{
			if (collidedKey.find(_T("BULLET")) != tstring::npos) collidedWithBullet = true;

			if (m_rPointChecker.AlreadyPassed(collidedKey)) collidedWithBullet = false;
		}

		if (!collidedWithBullet) return;

		ChangeColor();

		CreateMissText();
	}

	void TargetWall::Finalize()
	{
		delete m_pColorChangingDelayCounter;
	}

	void TargetWall::JudgeAndChangeColor()
	{
		auto& rColor = m_pVertices->GetColor();

		const auto DEFAULT_COLOR = 0xFFFFFFFF;

		if (rColor.GetColorCode() == DEFAULT_COLOR) return;

		if (m_pColorChangingDelayCounter->Update() != 1.0f) return;

		m_pColorChangingDelayCounter->Zero();

		m_pVertices->SetColor(DEFAULT_COLOR);
	}

	void TargetWall::ChangeColor()
	{
		m_pVertices->SetColor(0xFF333333);
	}

	void TargetWall::CreateMissText()
	{
		auto pMissText = new InstantaneousText(_T("POINT_L"), 50,
			WindowMeasure::GetNormalizeVector(60.0f, 35.0f),
			_T("MISS"), DT_CENTER);

		ObjectIntegrator::CreateAndGetRef().Register(pMissText, LAYER_KIND::UI, 100);
	}

	void TargetWall::RegisterOnCollisionChecker()
	{
		CollisionChecker::CreateAndGetRef().Register(I_COLLIDER_KEY, this, this);
	}
}
