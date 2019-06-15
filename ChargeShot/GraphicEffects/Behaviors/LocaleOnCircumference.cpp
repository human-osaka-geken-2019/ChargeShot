#include "LocaleOnCircumference.h"	

namespace summonersaster
{
	using namespace gameframework;

	LocaleOnCircumference::LocaleOnCircumference(const D3DXVECTOR3& basePos, float radius, float radiusDifference, float startDegreeOnRightVec, float degreeWidth)
	{
		m_baseCenter = basePos;

		std::uniform_real_distribution<float> radiusDistribution(radius, radius + radiusDifference);
		D3DXVECTOR3 distance(radiusDistribution(m_randEngine), 0.0f, 0.0f);

		std::uniform_real_distribution<float> degreeDistribution(startDegreeOnRightVec, startDegreeOnRightVec + degreeWidth);

		m_degreeToDecidePosition = degreeDistribution(m_randEngine);

		gameframework::algorithm::D3DXVec3RotationZ(&distance, m_degreeToDecidePosition);
	
		m_pos = m_baseCenter + distance;
	}

	LocaleOnCircumference::~LocaleOnCircumference()
	{

	}

	void LocaleOnCircumference::Impart(Vertices* pVertices)
	{
		D3DXVECTOR3& rVerticesCenter = pVertices->GetCenter();

		rVerticesCenter = m_pos;

		pVertices->SetRotationZ(m_degreeToDecidePosition);

		m_isEnd = true;
	}
}
