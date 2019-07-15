#include "TargetFactory.h"

namespace chargeshot
{
	using namespace gameframework;

	TargetFactory::~TargetFactory()
	{

	}

	void TargetFactory::Update()
	{
		if (!m_rPointChecker.IsPointGot()) return;

		CreateNewTarget();
	}
	
	TargetFactory::TargetFactory()
	{

	}

	void TargetFactory::CreateNewTarget()
	{
		auto pTargetTmp = new Target(
			D3DXVECTOR3(WindowMeasure::GetNormalizeX(90.0f), 0.0f, 0.5f),
			WindowMeasure::GetNormalize(5.0f, static_cast<float>(rand() % 45) + 3.0f),
			static_cast<float>(rand() % 3) + 2.0f);

		ObjectIntegrator::CreateAndGetRef().Register(
			pTargetTmp,
			LAYER_KIND::OPAQUENESS, 0);
	}
}
