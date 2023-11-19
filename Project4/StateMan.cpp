#include "StateMan.hpp"

Engine::StateMan::StateMan() : add(false), replace(false), remove(false)
{
}

Engine::StateMan::~StateMan()
{
}

void Engine::StateMan::Add(std::unique_ptr<State> toAdd, bool replace)
{
    add = true;
    newState = std::move(toAdd);

    replace = replace;
}

void Engine::StateMan::PopCurrent()
{
    remove = true;
}

void Engine::StateMan::ProcessStateChange()
{
    if (remove && (!stateStack.empty()))
    {
        stateStack.pop();

        if (!stateStack.empty())
        {
            stateStack.top()->Start();
        }

        remove = false;
    }

    if (add)
    {
        if (replace && (!stateStack.empty()))
        {
            stateStack.pop();
            replace = false;
        }

        if (!stateStack.empty())
        {
            stateStack.top()->Pause();
        }

        stateStack.push(std::move(newState));
        stateStack.top()->Init();
        stateStack.top()->Start();
        add = false;
    }
}

std::unique_ptr<Engine::State>& Engine::StateMan::GetCurrent()
{
    return stateStack.top();
}