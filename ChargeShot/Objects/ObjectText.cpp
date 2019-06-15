#include "ObjectText.h"

namespace chargeshot
{
	using gameframework::GameFrameworkFactory;

	ObjectText::~ObjectText()
	{
		Finalize();
	}

	void ObjectText::Render()
	{
		m_pStream->Render(m_rGameFramework.GetFont(pFONT_KEY), m_format);
	}

	ObjectText::ObjectText(const TCHAR* pFontKey, UINT format)
		:pFONT_KEY(pFontKey), m_format(format)
	{
		InstantiateStream();
	}

	void ObjectText::Finalize()
	{
		delete m_pStream;
	}

	void ObjectText::InstantiateStream()
	{
		GameFrameworkFactory::Create(&m_pStream);
	}
}
