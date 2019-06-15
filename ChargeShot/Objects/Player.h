#ifndef PLAYER_H
#define PLAYER_H

#include <GameFramework.h>

#include "Bullet.h"
#include "Counter_sec.h"
#include "ObjectIntegrator.h"
#include "ObjectText.h"
#include "Object2D.h"
#include "WindowMeasure.h"

namespace chargeshot
{
	class Player :public Object2D
	{
	public:
		Player(const D3DXVECTOR2& position);
		virtual ~Player();

		virtual void Update()override;

	protected:
		void InstantiateCounter();
		void InstantiateRemainingBulletText();
		void FormVertices(const D3DXVECTOR2& position);

		virtual void LoadBullet();
		virtual void ChargeBullet();
		virtual void ShootBullet();

		void UpdateRemainingBulletNumText();

		Bullet* m_pBullet = nullptr;

		int m_remainingBulletNum = 20;

		ObjectText* m_pRemainingBulletNumText = nullptr;

		Counter_sec* m_pShotIntervalCounter = nullptr;

		ObjectIntegrator& m_rObjectIntegrator = ObjectIntegrator::CreateAndGetRef();

	private:
		Player(const Player& player) = delete;
		Player& operator=(Player& player) = delete;
	};
}

#endif // !PLAYER_H
