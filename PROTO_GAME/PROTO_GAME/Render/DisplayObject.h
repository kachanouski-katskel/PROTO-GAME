#pragma once
#include "Vec2.h"
#include <vector>

namespace sf
{
	class Sprite;
	class Texture;
	class Drawable;
}

namespace ProtoGame 
{
	enum class ZOrder
	{
		Z_DEFAULT,
		Z_BASTION,
		Z_HIGHLIGHT,
		Z_UNIT,
		Z_HPBAR,
		Z_CLOUD
	};

	class DisplayObject 
	{
	protected:
		sf::Sprite* m_sprite = nullptr;

		float m_scale = 1.0f;
		float m_alpha = 1.0f;
		float m_rotation = 0.0f;
		Vec2F m_position;
		const ZOrder m_zOrder = ZOrder::Z_DEFAULT;

		bool m_visible = false;

	public:
		DisplayObject(sf::Sprite* sprite, ZOrder zOrder = ZOrder::Z_DEFAULT);
		DisplayObject(sf::Texture* texture);
		virtual ~DisplayObject();

		virtual void setPosition(const Vec2F& position);
		virtual void setAlpha(float alpha);
		virtual void setScale(float scale);
		virtual void setRotation(float rotation);
		virtual void setVisible(bool visible);
		virtual void setColor(int r, int g, int b);

		virtual float getScale() const;
		virtual float getRotation() const;
		virtual float getAlpha() const;
		virtual bool isVivible() const;
		virtual Vec2F getPosition() const;
		virtual Vec2F getSize() const;
		virtual ZOrder getZOrder() const;
		
		sf::Sprite* getSprite() const;
		
		virtual std::vector<sf::Drawable*> getDrawables() const;
	};
}
