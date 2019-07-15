#ifndef TARGET_FACTORY_H
#define TARGET_FACTORY_H

#include <GameFramework.h>

#include "Target.h"
#include "ObjectIntegrator.h"
#include "PointChecker.h"

namespace chargeshot
{
	using namespace gameframework::collision;
	using gameframework::Singleton;
	using gameframework::tstring;

	class TargetFactory : public Singleton<TargetFactory>
	{
	public:
		friend Singleton<TargetFactory>;

		~TargetFactory();

		void Update();

	private:
		TargetFactory();

		TargetFactory(const TargetFactory& targetFactory) = delete;
		TargetFactory& operator=(const TargetFactory& targetFactory) = delete;

		void CreateNewTarget();

		PointChecker& m_rPointChecker = PointChecker::CreateAndGetRef();
	};
} 

#endif //!TARGET_FACTORY_H
