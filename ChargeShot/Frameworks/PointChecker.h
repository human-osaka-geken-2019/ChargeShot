#ifndef POINT_CHECKER_H
#define POINT_CHECKER_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <GameFramework.h>

#include "CollisionChecker.h"
#include "ObjectIntegrator.h"

namespace chargeshot
{
	using namespace gameframework::collision;
	using gameframework::Singleton;
	using gameframework::tstring;

	class PointChecker : public Singleton<PointChecker>
	{
	public:
		friend Singleton<PointChecker>;

		~PointChecker();

		void Update();

		bool IsPointGot()const;

		unsigned int GetPoint()const;

		unsigned int GetTotalPoint()const;

		bool AlreadyCorrided(const tstring& keys);
		
		bool AlreadyPassed(const tstring& keys);

		inline std::vector<int>* GetPointsPointer()
		{
			return &m_points;
		}

		inline unsigned int GetHighScore()const
		{
			return m_highPoint;
		}

		inline bool GetUpdatedHighPoint()const
		{
			return m_updatedHighPoint;
		}

		void Zero();

		static const unsigned int POINT_MAX = 500;

	private:
		PointChecker();

		PointChecker(const PointChecker& pointChecker) = delete;
		PointChecker& operator=(const PointChecker& pointChecker) = delete;

		void GetKeyTargetCollided();

		void ReadyForCreatingNewTarget();

		bool AlreadyChecked(const tstring& collidedKey);

		void CheckIsBulletInnerInTarget();

		unsigned int CalculatePointByBulletSize(Vertices* pVertices);

		void CalculatePoint();

		void UpdateHighPoint();

		void LoadHighPoint();
		void WriteHighPoint();

		ICollider* m_pTargetICollider = nullptr;

		std::unordered_map<tstring, Vertices*> m_pBulletVerticesTmp;
		Vertices* m_pTargetVerticesTmp = nullptr;

		CollisionChecker& m_rCollisionChecker = CollisionChecker::CreateAndGetRef();

		std::vector<tstring> m_keysTargetNewlyCorrided;
		std::vector<tstring> m_KeysInTarget;

		std::vector<tstring> m_keysTargetAlreadyCorrided;
		std::vector<tstring> m_keysTargetAlreadyPassed;

		std::vector<int> m_points;

		unsigned int m_point = 0;
		unsigned int m_totalPoint = 0;

		unsigned int m_highPoint = 0;
		bool m_updatedHighPoint = false;

		bool m_isPointGot = false;
	};
} 

#endif //!POINT_CHECKER_H
