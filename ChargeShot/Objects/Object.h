#ifndef OBJECT_H
#define OBJECT_H

namespace chargeshot
{
	class Object
	{
	public:
		virtual ~Object();

		virtual void Update() = 0;
		virtual void Render() = 0;

		virtual inline bool ShouldDestroyed()const
		{
			return m_shouldDestroyed;
		}

	protected:
		Object();

		virtual void Finalize() = 0;

		bool m_shouldDestroyed = false;

	private:
		Object(const Object& object) = delete;
		Object& operator=(Object& object) = delete;
	};
}

#endif // !OBJECT_H
