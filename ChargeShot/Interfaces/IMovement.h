#ifndef I_MOVEMENT_H
#define I_MOVEMENT_H

#include <d3dx9.h>

namespace chargeshot
{
	class IMovement
	{
	public:
		virtual ~IMovement() = default;

		virtual D3DXVECTOR3 GetMovement()const = 0;

	protected:
		IMovement() = default;

		virtual D3DXVECTOR3 CalculateMovement() = 0;

		virtual void Move() = 0;

	private:
		IMovement(const IMovement& iMovement) = delete;
		IMovement& operator=(IMovement&iMovement) = delete;
	};
}

#endif // !I_MOVEMENT_H
