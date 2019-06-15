#ifndef QUAKE_COUNTER_SEC_H
#define QUAKE_COUNTER_SEC_H

#include "Counter_sec.h"

namespace chargeshot
{
	class QuakeCounter_sec :public Counter_sec
	{
	public:
		QuakeCounter_sec(const float durationMax);

		~QuakeCounter_sec();

		virtual float Update()override;

	protected:
		virtual void NormalizeWithinRange();

		bool m_shouldIncreased = true;

	private:
		QuakeCounter_sec(const QuakeCounter_sec& quakeCounter_sec) = delete;
		QuakeCounter_sec& operator=(QuakeCounter_sec& quakeCounter_sec) = delete;
	};
}

#endif // !QUAKE_COUNTER_SEC_H
