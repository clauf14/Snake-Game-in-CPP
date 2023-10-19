#pragma once

#include <SFML/System/Time.hpp>

namespace Engine 
{
	class State
	{				//Vom mostenii de aici
	public:
		State() {};
		virtual ~State() {};
				//Medote pentru Strari
		virtual void Init() = 0;    //Configurarea unei stari (config textului sprite-urilot si a pozitia)
		virtual void ProcessInput() = 0;	//Evenimente (apasarea tastelor si clicurile de mouse)
		virtual void Update(sf::Time deltaTime) = 0;	//Se fac modificari in stare (recalcularea poztiei sprite si acctualizarea textelor)
		virtual void Draw() = 0;	//Atrage sprite-urile si textul starii pe fereastra de randare

		virtual void Pause() = 0;	//Intrerupe si porneste stari
		virtual void Start() = 0;
	};
}
