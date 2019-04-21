#pragma once

namespace ProtoGame
{
	class HPChecker
	{
	protected:
		float m_hp = 0.0f;
	public:
		virtual ~HPChecker() {}

		virtual bool isDead() const
		{
			return m_hp <= 0.0f;
		}
		virtual float getHP() const
		{
			return m_hp;
		}
		virtual void addHP(float value)
		{
			m_hp += value;
		}
		virtual void removeHP(float value)
		{
			m_hp -= value;
		}
	};
}
