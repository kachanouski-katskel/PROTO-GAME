#pragma once
#include "HPBar.h"

namespace ProtoGame
{
	class HPChecker
	{
	protected:
		float m_hp = 0.0f;
		float m_defenceScale = 1.0f;
		float m_attackScale = 1.0f;

		HPBar m_hpBar;
	public:
		HPChecker()
		{
			enableHpBar(true);
		}

		virtual ~HPChecker() {}

		virtual bool isDead() const
		{
			return m_hp <= 0.0f;
		}
		virtual void setHP(const float & value)
		{
			m_hp = value;
			m_hpBar.setHp(m_hp);
		}
		virtual float getHP() const
		{
			return m_hp;
		}
		virtual void addHP(float value)
		{
			m_hp += value;
			m_hpBar.setHp(m_hp);
		}
		virtual void removeHP(float value)
		{
			m_hp -= value / m_defenceScale;
			m_hpBar.setHp(m_hp);
		}
		virtual void setMaxHP(const float & maxHP)
		{
			m_hpBar.setMaxHp(maxHP);
		}

		void enableHpBar(bool enable)
		{
			m_hpBar.setVisible(enable);
		}

		void setHpBarPosition(const Vec2F & position)
		{
			m_hpBar.setPosition(position);
		}

		void resetScales()
		{
			m_attackScale = 1.0f;
			m_defenceScale = 1.0f;
		}

		void scaleAttack(float scale)
		{
			m_attackScale *= scale;
		}

		void scaleDefence(float scale)
		{
			m_defenceScale *= scale;
		}

		float getAttackScale() const
		{
			return m_attackScale;
		}
	};
}
