#pragma once

#include <stack>
#include <memory>

#include "State.hpp"

namespace Engine
{
	class StateMan
	{
	private:
		std::stack<std::unique_ptr<State>> m_stateStack;	//Afiseaza pointeri catre obiectul de stare
		std::unique_ptr<State> m_newState;	//Pointer care va stoca noua stare adaugata la stiva

			//Vor fi modificate prin metodele de aduagare si introducere
		bool m_add;
		bool m_replace;
		bool m_remove;

	public:
		StateMan();
		~StateMan();

		void Add(std::unique_ptr<State> toAdd, bool replace = false);	//replace -> daca vrem sa adaugam o stare noua, sau sa inlocuim cu una noua
		void PopCurrent();	//Va elimna starea curenta din stiva de stari
		void ProcessStateChange();	//Stiva de stare va fi modicata
		std::unique_ptr<State>& GetCurrent();	//Returneaza un pointer la obiectul de stare prin referinta
	};
}