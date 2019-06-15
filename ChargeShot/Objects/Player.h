#ifndef PLAYER_H
#define PLAYER_H

#include <GameFramework.h>

#include "Bullet.h"
#include "ObjectIntegrator.h"
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
		virtual void LoadBullet();
		virtual void ChargeBullet();
		virtual void ShootBullet();

		Bullet* m_pBullet = nullptr;

		ObjectIntegrator& m_rObjectIntegrator = ObjectIntegrator::CreateAndGetRef();

	private:
		Player(const Player& player) = delete;
		Player& operator=(Player& player) = delete;

		void FormVertices(const D3DXVECTOR2& position);
	};
}

#endif // !PLAYER_H
