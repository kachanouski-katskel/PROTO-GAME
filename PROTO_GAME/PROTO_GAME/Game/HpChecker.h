#pragma once

namespace ProtoGame
{
	class HPChecker
	{
		int m_hp = 0;
	public:
		virtual bool isDead() const
		{
			return m_hp <= 0;
		}
		virtual int getHP() const
		{
			return m_hp;
		}
		virtual void addHP(int value)
		{
			m_hp += value;
		}
		virtual void removeHP(int value)
		{
			m_hp -= value;
		}
	};
}
