#include "Object2D.h"

namespace chargeshot
{
	using gameframework::GameFrameworkFactory;

	Object2D::~Object2D()
	{
		Finalize();
	}

	void Object2D::Render()
	{
		if (m_isAdditionBlendMode) m_rGameFramework.ToAddtionBlendMode();

		m_pVertices->Render(m_rGameFramework.GetTexture(pTEXTURE_KEY));

		if (m_isAdditionBlendMode) m_rGameFramework.ToDefaultBlendMode();
	}

	Object2D::Object2D(const TCHAR* pTextureKey, bool isAdditionBlendMode)
		:pTEXTURE_KEY(pTextureKey), m_isAdditionBlendMode(isAdditionBlendMode)
	{
		InstantiateVertices();
	}

	void Object2D::Finalize()
	{
		delete m_pVertices;
	}

	void Object2D::InstantiateVertices()
	{
		GameFrameworkFactory::Create(&m_pVertices);
	}
}
