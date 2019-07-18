#include "Target.h"

namespace chargeshot
{
	Target::Target(const D3DXVECTOR3& startPosition, const RectSize& size, float quakeTime_sec)
		:Object2D(nullptr), m_movement(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{
		RegisterOnCollisionChecker();

		InstantiateCounter(quakeTime_sec);

		InstantiateWalls();

		FormVertices(startPosition, size);

		m_pMyCollisionInformation = GetMyCollisionInformationPtr();
	}

	Target::~Target()
	{
		Finalize();
	}

	void Target::Update()
	{
		ZeroMovement();

		if (WallIsCollided()) return;

		CalculateMovement();

		Move();
	}
	
	void Target::Move()
	{
		m_pVertices->GetCenter() += m_movement;

		FormWallVertices();
	}

	void Target::Finalize()
	{
		delete m_pQuakeMovingCounter;
	}

	D3DXVECTOR3 Target::CalculateMovement()
	{
		m_movement.y =
			WindowMeasure::GetNormalizeY(100.0f * m_pQuakeMovingCounter->Update()) - 
			m_pVertices->GetCenter().y;

		for (auto& rpWall : m_pWalls)
		{
			rpWall->SetMovement(m_movement);
		}

		return m_movement;
	}

	void Target::FormWallVertices()
	{
		D3DXVECTOR3 myCenter(m_pVertices->GetCenter());
		RectSize mySize(m_pVertices->GetSize());
		float myLeft = myCenter.x - 0.5f * mySize.m_width;
		float myHalfHeight = 0.5f * mySize.m_height;

		RectSize wallSize(mySize.m_width, WindowMeasure::GetNormalizeY(100.0f));

		D3DXVECTOR3 myTopLeft(myLeft, myCenter.y + myHalfHeight, myCenter.z);
		m_pWalls[0]->GetVerticesPtr()->SetPosByTopLeft(myTopLeft, wallSize);

		D3DXVECTOR3 myBottomLeft(myLeft, myCenter.y - myHalfHeight, myCenter.z);
		m_pWalls[1]->GetVerticesPtr()->SetPosBybottomLeft(myBottomLeft, wallSize);
	}
	
	void Target::ZeroMovement()
	{
		m_movement = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	bool Target::WallIsCollided()
	{
		for (auto& rpWall : m_pWalls)
		{
			if (rpWall->GetCollided()) return true;
		}

		return false;
	}

	void Target::RegisterOnCollisionChecker()
	{
		CollisionChecker::CreateAndGetRef().Register(I_COLLIDER_KEY, this, nullptr, this);
	}

	CollisionInformation* Target::GetMyCollisionInformationPtr()
	{
		return CollisionChecker::GetRef().GetCollisionInformationPtr(I_COLLIDER_KEY);
	}

	void Target::InstantiateCounter(float quakeTime_sec)
	{
		m_pQuakeMovingCounter = new QuakeCounter_sec(quakeTime_sec);
	}

	void Target::InstantiateWalls()
	{
		m_pWalls[0] = new TargetWall(_T("TARGET_WALL_TOP"));
		m_pWalls[1] = new TargetWall(_T("TARGET_WALL_BOTTOM"));

		for (auto& rpWall : m_pWalls)
		{
			m_rObjectIntegrator.Register(rpWall, LAYER_KIND::OPAQUENESS, 0);
		}
	}

	void Target::FormVertices(const D3DXVECTOR3& startPosition, const RectSize& size)
	{
		m_pVertices->SetCenterAndSize(startPosition, size);
		m_pVertices->SetColor(0x00FFFFFF);
	}
}
