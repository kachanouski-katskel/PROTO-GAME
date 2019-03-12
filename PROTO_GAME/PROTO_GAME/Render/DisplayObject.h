#pragma once

namespace ProtoGame 
{

	class DisplayObject 
	{
	protected:
		void* m_sprite = nullptr;

		float m_scale = 1.0f;
		float m_alpha = 1.0f;
		float m_rotation = 0.0f;

		bool m_visible = false;

	public:
		DisplayObject(void* sprite);
		virtual ~DisplayObject();

		void setPos();
		void setAlpha(float alpha);
		void setScale(float scale);
		void setRotation(float rotation);
		void setVisible(bool visible);

		float getScale() const;
		float getRotation() const;
		float getAlpha() const;
		bool isVivible() const;
		//TODO: getPos() const;
		
		void* getSprite() const;
	};
}
