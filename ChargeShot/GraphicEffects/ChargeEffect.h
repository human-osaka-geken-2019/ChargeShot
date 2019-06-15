#ifndef CHARGE_EFFECT_H
#define CHARGE_EFFECT_H

#include <GameFramework.h>

#include "ScalingFlashAbsorbedSquare.h"

namespace chargeshot
{
	using namespace summonersaster;
	using gameframework::GraphicEffect;
	using gameframework::Degree;
	using gameframework::Vertices;

	class ChargeEffect :public GraphicEffect
	{
	public:
		ChargeEffect(const D3DXVECTOR3& occurencePosition, float radius, float radiusDifference, int requireFrameNum, int lifeLimit);

		virtual ~ChargeEffect();


		virtual void Update()override;
	};
}

#endif //!CHARGE_EFFECT_H
