﻿#ifndef POINT_CHECKER_H
#define POINT_CHECKER_H

#include <vector>

#include <GameFramework.h>

#include "CollisionChecker.h"
#include "Target.h"
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

		void Zero();

	private:
		PointChecker();

		PointChecker(const PointChecker& pointChecker) = delete;
		PointChecker& operator=(const PointChecker& pointChecker) = delete;

		void GetKeyTargetCollided();

		void CreateNewTarget();

		bool AlreadyChecked(const tstring& collidedKey);

		void CheckIsBulletInnerInTarget();

		unsigned int CalculatePointByBulletSize(Vertices* pVertices);

		void CalculatePoint();

		ICollider* m_pTargetICollider = nullptr;

		std::unordered_map<tstring, Vertices*> m_pBulletVerticesTmp;
		Vertices* m_pTargetVerticesTmp = nullptr;

		CollisionChecker& m_rCollisionChecker = CollisionChecker::CreateAndGetRef();

		std::vector<tstring> m_keysTargetNewlyCorrided;
		std::vector<tstring> m_KeysInTarget;

		std::vector<tstring> m_keysTargetAlreadyCorrided;

		unsigned int m_point = 0;
		unsigned int m_totalPoint = 0;

		bool m_isPointGot = false;
	};
} 

#endif //!POINT_CHECKER_H