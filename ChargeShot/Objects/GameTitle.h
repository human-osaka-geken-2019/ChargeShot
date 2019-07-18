#ifndef GAME_TITLE_H
#define GAME_TITLE_H

#include <GameFramework.h>

#include "QuakeCounter_sec.h"
#include "HoldEffect.h"
#include "Object.h"
#include "ObjectIntegrator.h"
#include "SceneSwitchMediator.h"
#include "WindowMeasure.h"

namespace chargeshot
{
	using namespace gameframework;

	class GameTitle :public Object
	{
	public:
		GameTitle()
		{
			InstantiateRotationCounter();
		}

		virtual ~GameTitle()
		{
			Finalize();
		}

		virtual void Update()override
		{
			if (m_rGameFramework.KeyboardIsPressed(DIK_RETURN))
			{
				SceneSwitchMediator::CreateAndGetRef().SendSwitchEvent(SCENE_KIND::IN_GAME);
			}

			m_pRotationCounter->Update();

			auto createEffect = [&](float radiusMax, float startRadius, float radiusMaximum)
			{
				D3DXVECTOR2 effectPositionRadius(radiusMax, 0.0f);
				algorithm::D3DXVec2RotationZ(&effectPositionRadius, startRadius + radiusMaximum * m_pRotationCounter->GetProcessingRatio());

				if (m_pRotationCounter->GetProcessingRatio() == 1.0f) m_pRotationCounter->Zero();

				auto center = WindowMeasure::GetNormalizeVector(50.0f);

				D3DXVECTOR3 effectPosition(center.x + effectPositionRadius.x, center.y + effectPositionRadius.y, 0.0f);

				m_rGameFramework.RegisterGraphicEffect(new HoldEffect(effectPosition, _T("白正方形")));
			};

			createEffect(WindowMeasure::GetNormalizeVector_x(5.0f).x, 0.0f, 360.0f);
			createEffect(WindowMeasure::GetNormalizeVector_x(10.0f).x, 45.0f, -360.0f);
			createEffect(WindowMeasure::GetNormalizeVector_x(15.0f).x, 90.0f, 360.0f);
		}

		virtual void Render()override
		{

		}
		
	protected:
		virtual void Finalize()override
		{
			delete m_pRotationCounter;
		}

		GameFramework& m_rGameFramework = GameFramework::CreateAndGetRef();

		ObjectIntegrator& m_rObjectIntegrator = ObjectIntegrator::CreateAndGetRef();

		void InstantiateRotationCounter()
		{
			m_pRotationCounter = new Counter_sec(1.5f);
		}

		Counter_sec* m_pRotationCounter = nullptr;

	private:
		GameTitle(const GameTitle& gameTitle) = delete;
		GameTitle& operator=(GameTitle& gameTitle) = delete;
	};
}

#endif // !GAME_TITLE_H
