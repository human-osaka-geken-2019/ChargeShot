#include "PointChecker.h"

namespace chargeshot
{
	using namespace gameframework;

	PointChecker::~PointChecker()
	{
		WriteHighPoint();
	}

	void PointChecker::Update()
	{
		UpdateHighPoint();
		
		m_isPointGot = false;

		GetKeyTargetCollided();

		CheckIsBulletInnerInTarget();

		CalculatePoint();

		if (!m_isPointGot) return;

		ReadyForCreatingNewTarget();
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

	bool PointChecker::AlreadyCorrided(const tstring& keys)
	{
		for (auto& rKey : m_keysTargetAlreadyCorrided)
		{
			if (rKey == keys) return true;
		}

		return false;
	}

	bool PointChecker::AlreadyPassed(const tstring& keys)
	{
		for (auto& rKey : m_keysTargetAlreadyPassed)
		{
			if (rKey == keys) return true;
		}

		return false;
	}

	void PointChecker::Zero()
	{
		m_totalPoint = m_point = 0;

		m_updatedHighPoint = false;

		m_keysTargetAlreadyCorrided.clear();

		m_keysTargetAlreadyPassed.clear();

		m_points.clear();
	}

	PointChecker::PointChecker()
	{
		LoadHighPoint();
	}

	void PointChecker::GetKeyTargetCollided()
	{
		auto pTargetInformation =
			m_rCollisionChecker.GetCollisionInformationPtr(_T("TARGET"));

		if (!pTargetInformation) return;

		m_pTargetICollider = pTargetInformation->m_pICollider;

		m_pTargetVerticesTmp = pTargetInformation->m_pICollider->GetVerticesPtr();

		auto& rCollidedKeys = pTargetInformation->m_colliderCollidedKeys;

		m_keysTargetNewlyCorrided.clear();

		for (auto& rCollidedKey : rCollidedKeys)
		{
			if (rCollidedKey.find(_T("BULLET")) == std::string::npos) continue;

			if (AlreadyChecked(rCollidedKey)) continue;

			m_keysTargetNewlyCorrided.push_back(rCollidedKey);
		}

		return;
	}
	
	void PointChecker::ReadyForCreatingNewTarget()
	{
		m_pTargetICollider->SetShouldDestroyed(true);
		m_rCollisionChecker.ReleaseDestroyed();
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

			auto isPlus = algorithm::Tertiary(pBulletVerticesTmp->GetCenter().y - m_pTargetVerticesTmp->GetCenter().y >= 0, true, false);

			if (0.5f * pBulletVerticesTmp->GetSize().m_height >
				0.5f * m_pTargetVerticesTmp->GetSize().m_height - distanceCenters)
			{
				tstring colliderKeys[] = 
				{
					m_keysTargetNewlyCorrided[0],
					algorithm::Tertiary(isPlus, _T("TARGET_WALL_TOP"), _T("TARGET_WALL_BOTTOM"))
				};

				for (int i = 0; i < _countof(colliderKeys); ++i)
				{
					m_rCollisionChecker.GetCollisionInformationPtr(colliderKeys[1 - i])->m_colliderCollidedKeys.push_back(colliderKeys[i]);
				}

				continue;
			}

			m_pBulletVerticesTmp[rKeysCollided] = pBulletVerticesTmp;

			m_keysTargetAlreadyPassed.push_back(rKeysCollided);
		}

		return;
	}

	unsigned int PointChecker::CalculatePointByBulletSize(Vertices* pVertices)
	{
		auto sizeRatio = pVertices->GetSize().m_height /
			m_pTargetVerticesTmp->GetSize().m_height;

		return static_cast<unsigned int>(POINT_MAX * sizeRatio);
	}

	void PointChecker::CalculatePoint()
	{
		for (auto& rpVertices : m_pBulletVerticesTmp)
		{
			m_point = CalculatePointByBulletSize(rpVertices.second);

			m_points.push_back(m_point);

			m_totalPoint += m_point;

			m_isPointGot = true;
		}
	}

	void PointChecker::UpdateHighPoint()
	{
		if (m_totalPoint <= m_highPoint) return;
	
		m_highPoint = m_totalPoint;

		m_updatedHighPoint = true;
	}

	void PointChecker::LoadHighPoint()
	{
		std::ifstream ifs("HighScore.txt");
		std::string highScore;

		getline(ifs, highScore);

		auto ss = std::istringstream(highScore);

		ss >> m_highPoint;
	}

	void PointChecker::WriteHighPoint()
	{
		std::ofstream ofs("HighScore.txt");

		ofs << m_highPoint << std::endl;
	}
}
