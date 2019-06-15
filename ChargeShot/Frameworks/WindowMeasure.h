#ifndef WINDOW_MEASURE_H
#define WINDOW_MEASURE_H

#include <d3dx9.h>

#include <GameFramework.h>

namespace chargeshot
{
	using gameframework::RectSize;

	class WindowMeasure
	{
	public:
		inline static RectSize GetNormalize(RectSize numerator)
		{
			InitializeWindowSize();

			RectSize windowSize(m_windowSize.m_width * GetRatio(numerator.m_width), 
				m_windowSize.m_height * GetRatio(numerator.m_height));

			return windowSize;
		}

		inline static D3DXVECTOR2 GetNormalizeVector(RectSize numerator)
		{
			InitializeWindowSize();

			D3DXVECTOR2 windowSizeVector(m_windowSize.m_width * GetRatio(numerator.m_width),
				m_windowSize.m_height * GetRatio(numerator.m_height));

			return windowSizeVector;
		}

		inline static RectSize GetNormalize(D3DXVECTOR2 numerator)
		{
			InitializeWindowSize();

			RectSize windowSize(m_windowSize.m_width * GetRatio(numerator.x),
				m_windowSize.m_height * GetRatio(numerator.y));

			return windowSize;
		}

		inline static D3DXVECTOR2 GetNormalizeVector(D3DXVECTOR2 numerator)
		{
			InitializeWindowSize();

			D3DXVECTOR2 windowSizeVector(m_windowSize.m_width * GetRatio(numerator.x),
				m_windowSize.m_height * GetRatio(numerator.y));

			return windowSizeVector;
		}

		inline static RectSize GetNormalize(float x, float y)
		{
			return GetNormalize(D3DXVECTOR2(x, y));
		}

		inline static D3DXVECTOR2 GetNormalizeVector(float x, float y)
		{
			return GetNormalizeVector(D3DXVECTOR2(x, y));
		}

		inline static RectSize GetNormalize(float numerator)
		{
			return GetNormalize(numerator, numerator);
		}

		inline static D3DXVECTOR2 GetNormalizeVector(float numerator)
		{
			return GetNormalizeVector(numerator, numerator);
		}

		inline static RectSize GetNormalize()
		{
			return GetNormalize(DENOMINATOR);
		}

		inline static D3DXVECTOR2 GetNormalizeVector()
		{
			return GetNormalizeVector(DENOMINATOR);
		}

		inline static RectSize GetNormalize_x(float x)
		{
			float size_x = m_windowSize.m_width * GetRatio(x);

			return RectSize(size_x, size_x);
		}

		inline static D3DXVECTOR2 GetNormalizeVector_x(float x)
		{
			float vector_x = m_windowSize.m_width * GetRatio(x);

			return D3DXVECTOR2(vector_x, vector_x);
		}

		inline static RectSize GetNormalize_y(float y)
		{
			float size_y = m_windowSize.m_height * GetRatio(y);

			return RectSize(size_y, size_y);
		}

		inline static D3DXVECTOR2 GetNormalizeVector_y(float y)
		{
			float vector_y = m_windowSize.m_height * GetRatio(y);

			return D3DXVECTOR2(vector_y, vector_y);
		}

		inline static float GetNormalizeY(float y)
		{
			return m_windowSize.m_height * GetRatio(y);
		}

		inline static float GetNormalizeX(float x)
		{
			return m_windowSize.m_width * GetRatio(x);
		}

		static const float DENOMINATOR;

	private:
		WindowMeasure() = delete;
		~WindowMeasure() = delete;
		WindowMeasure(const WindowMeasure& windowMeasure) = delete;
		WindowMeasure& operator=(WindowMeasure& windowMeasure) = delete;

		inline static void InitializeWindowSize()
		{
			if (m_windowSizeVector != D3DXVECTOR2(0.0f, 0.0f)) return;

			gameframework::WindowParam::GetWindowSize(&m_windowSize);

			m_windowSizeVector.x = m_windowSize.m_width;
			m_windowSizeVector.y = m_windowSize.m_height;
		}

		inline static float GetRatio(float numerator)
		{
			return numerator / DENOMINATOR;
		}

		static RectSize m_windowSize;
		static D3DXVECTOR2 m_windowSizeVector;
	};
}

#endif // !WINDOW_MEASURE_H
