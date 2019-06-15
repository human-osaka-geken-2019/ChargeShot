#ifndef COUNTER_SEC_H
#define COUNTER_SEC_H

#include <GameFramework.h>

namespace chargeshot
{
	using gameframework::GameFramework;

	class Counter_sec
	{
	public:
		Counter_sec(const float durationMax);
		~Counter_sec();

		virtual float GetProcessingRatio();

		virtual float Update();

		void Zero();

	protected:
		const float DURATION_MAX;
		float m_duration = 0.0f;

		GameFramework& m_rGameFramework = GameFramework::CreateAndGetRef();

	private:
		Counter_sec(const Counter_sec& counter_sec) = delete;
		Counter_sec& operator=(Counter_sec& counter_sec) = delete;
	};
}

#endif // !COUNTER_SEC_H
