#include "Render.h"

using namespace ProtoGame;
Render* Render::g_instance = nullptr;

Render::Render() 
{

}

Render::~Render() 
{
}

void Render::update() 
{

}

Render* Render::getInstance() 
{
	if (g_instance == nullptr) {
		g_instance = new Render();
	}
	return g_instance;
}

void Render::destroyInstance() 
{
	delete g_instance;
	g_instance = nullptr;
}


