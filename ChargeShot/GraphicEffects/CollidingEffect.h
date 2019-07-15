#ifndef COLLIDING_EFFECT_H
#define COLLIDING_EFFECT_H

#include <GameFramework.h>

#include "ScalingFlashAbsorbedSquare.h"

namespace chargeshot
{
	using namespace summonersaster;
	using gameframework::GraphicEffect;
	using gameframework::Degree;
	using gameframework::Vertices;

	class CollidingEffect :public GraphicEffect
	{
	public:
		CollidingEffect(const D3DXVECTOR3& occurencePosition);

		virtual ~CollidingEffect();


		virtual void Update()override;
	};
}

#endif //!COLLIDING_EFFECT_H
