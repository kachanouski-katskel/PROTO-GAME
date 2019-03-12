#pragma once
#include "Vec2.h"

namespace sf
{
	class Sprite;
	class Texture;
}

namespace ProtoGame 
{
	class DisplayObject 
	{
	protected:
		sf::Sprite* m_sprite = nullptr;

		float m_scale = 1.0f;
		float m_alpha = 1.0f;
		float m_rotation = 0.0f;
		Vec2F m_position;

		bool m_visible = false;

	public:
		DisplayObject(sf::Sprite* sprite);
		DisplayObject(sf::Texture* texture);
		virtual ~DisplayObject();

		void setPosition(const Vec2F& position);
		void setAlpha(float alpha);
		void setScale(float scale);
		void setRotation(float rotation);
		void setVisible(bool visible);

		float getScale() const;
		float getRotation() const;
		float getAlpha() const;
		bool isVivible() const;
		Vec2F getPosition() const;
		
		sf::Sprite* getSprite() const;
	};
}
