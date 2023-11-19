#pragma once

#include <stack>
#include <memory>

#include "State.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

namespace Engine
{
    class StateMan
    {
    public:
        StateMan();
        ~StateMan();

        void Add(std::unique_ptr<State> toAdd, bool replace = false);
        void PopCurrent();
        void ProcessStateChange();
        std::unique_ptr<State>& GetCurrent();

    private:
        std::stack<std::unique_ptr<State>> stateStack;
        std::unique_ptr<State> newState;

        bool add;
        bool replace;
        bool remove;
    };

}