#include "ObjectText.h"

namespace chargeshot
{
	using gameframework::GameFrameworkFactory;

	ObjectText::ObjectText(const TCHAR* pFontKey, UINT format)
		:pFONT_KEY(pFontKey), m_format(format)
	{
		InstantiateStream();
	}

	ObjectText::ObjectText(const TCHAR* pFontKey, const D3DXVECTOR2& topLeft,
		const tstring& stream, UINT format, const Color& color)
		:pFONT_KEY(pFontKey), m_format(format)
	{
		InstantiateStream();

		SetTopLeft(topLeft);
		SetStream(stream);
		SetColor(color);
	}

	ObjectText::~ObjectText()
	{
		Finalize();
	}

	void ObjectText::Update()
	{

	}

	void ObjectText::Render()
	{
		m_pStream->Render(m_rGameFramework.GetFont(pFONT_KEY), m_format);
	}

	void ObjectText::SetTopLeft(const D3DXVECTOR2& topLeft)
	{
		m_pStream->SetTopLeft(topLeft);
	}

	void ObjectText::SetColor(const Color& color)
	{
		m_pStream->SetColor(color);
	}

	void ObjectText::SetStream(const tstring& stream)
	{
		*m_pStream = stream;
	}

	void ObjectText::AddStream(const tstring& stream)
	{
		*m_pStream += stream;
	}

	void ObjectText::SetFormat(UINT format)
	{
		m_format = format;
	}

	void ObjectText::ObjectText::Finalize()
	{
		delete m_pStream;
	}

	void ObjectText::InstantiateStream()
	{
		GameFrameworkFactory::Create(&m_pStream);
	}
}
