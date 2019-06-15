#include "PointChecker.h"

namespace chargeshot
{
	using namespace gameframework;

	PointChecker::~PointChecker()
	{

	}

	void PointChecker::Update()
	{
		m_isPointGot = false;

		GetKeyTargetCollided();

		CheckIsBulletInnerInTarget();

		CalculatePoint();

		if (!m_isPointGot) return;

		GameFramework::CreateAndGetRef().OneShotSimultaneous(_T("HIT_M"));

		CreateNewTarget();
	}

	bool PointChecker::IsPointGot()const
	{
		return m_isPointGot;
	}

	unsigned int PointChecker::GetPoint()const
	{
		return m_point;
	}

	unsigned int PointChecker::GetTotalPoint()const
	{
		return m_totalPoint;
	}

	void PointChecker::Zero()
	{
		m_totalPoint = m_point = 0;

		m_keysTargetAlreadyCorrided.clear();
		m_keysTargetAlreadyCorrided.shrink_to_fit();
	}

	PointChecker::PointChecker()
	{

	}

	void PointChecker::GetKeyTargetCollided()
	{
		auto pTargetInformation =
			m_rCollisionChecker.GetCollisionInformationPtr(_T("TARGET"));

		m_pTargetICollider = pTargetInformation->m_pICollider;

		m_pTargetVerticesTmp = pTargetInformation->m_pICollider->GetVerticesPtr();

		auto& rCollidedKeys = pTargetInformation->m_colliderCollidedKeys;

		m_keysTargetNewlyCorrided.clear();

		for (auto& rCollidedKey : rCollidedKeys)
		{
			if (AlreadyChecked(rCollidedKey)) continue;

			m_keysTargetNewlyCorrided.push_back(rCollidedKey);
		}

		return;
	}
	
	void PointChecker::CreateNewTarget()
	{
		m_pTargetICollider->SetShouldDestroyed(true);
		m_rCollisionChecker.ReleaseDestroyed();

		auto pTargetTmp = new Target(
			D3DXVECTOR3(WindowMeasure::GetNormalizeX(90.0f), 0.0f, 0.9f),
			WindowMeasure::GetNormalize(5.0f, static_cast<float>(rand() % 45) + 3.0f),
			static_cast<float>(rand() % 3) + 2.0f);

		ObjectIntegrator::CreateAndGetRef().Register(
			pTargetTmp,
			LAYER_KIND::OPAQUENESS, 0);
	}

	bool PointChecker::AlreadyChecked(const tstring& collidedKey)
	{
		for (auto& rCollidedKey : m_keysTargetAlreadyCorrided)
		{
			if (rCollidedKey == collidedKey) return true;
		}

		m_keysTargetAlreadyCorrided.push_back(collidedKey);

		return false;
	}

	void PointChecker::CheckIsBulletInnerInTarget()
	{
		m_pBulletVerticesTmp.clear();

		if (m_keysTargetNewlyCorrided.size() == 0) return;

		for (auto& rKeysCollided : m_keysTargetNewlyCorrided)
		{
			auto pBulletInformation =
				m_rCollisionChecker.GetCollisionInformationPtr(rKeysCollided);

			auto pBulletVerticesTmp = pBulletInformation->m_pICollider->GetVerticesPtr();

			auto distanceCenters = fabsf(pBulletVerticesTmp->GetCenter().y - m_pTargetVerticesTmp->GetCenter().y);

			if (0.5f * pBulletVerticesTmp->GetSize().m_height >
				0.5f * m_pTargetVerticesTmp->GetSize().m_height - distanceCenters) continue;

			m_pBulletVerticesTmp[rKeysCollided] = pBulletVerticesTmp;
		}

		return;
	}

	unsigned int PointChecker::CalculatePointByBulletSize(Vertices* pVertices)
	{
		auto sizeRatio = pVertices->GetSize().m_height /
			m_pTargetVerticesTmp->GetSize().m_height;

		return static_cast<unsigned int>(500 * sizeRatio);
	}

	void PointChecker::CalculatePoint()
	{
		for (auto& rpVertices : m_pBulletVerticesTmp)
		{
			m_point = CalculatePointByBulletSize(rpVertices.second);

			m_totalPoint += m_point;

			m_isPointGot = true;
		}
	}
}
