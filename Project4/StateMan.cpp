//#include "StateMan.hpp"
//
//Engine::StateMan::StateMan::StateMan() : m_add(false), m_replace(false), m_remove(false)
//{
//}
//
//Engine::StateMan::StateMan::~StateMan()
//{
//}
//
//void Engine::StateMan::Add(unique_ptr<State> toAdd, bool replace = false)
//{
//	m_add = true;
//	m_newState = move(toAdd);
//
//	m_replace = replace;
//}
//void Engine::StateMan::PopCurrent()
//{
//	m_remove = true;
//}
//void Engine::StateMan::ProcessStateChange()
//{
//	if (m_remove && (!m_stateStack.empty()))
//	{
//		m_stateStack.pop();
//
//		if (!m_stateStack.empty())
//		{
//			m_stateStack.top()->Start();
//		}
//
//		m_remove = false;
//	}
//
//	if (m_add)
//	{
//		if (m_replace && (!m_stateStack.empty()))
//		{
//			m_stateStack.pop();
//			m_replace = false;
//		}
//
//		if (!m_stateStack.empty())
//		{
//			m_stateStack.top()->Pause();
//		}
//
//		m_stateStack.push(move(m_newState));
//		m_add = false;
//	}
//}
//unique_ptr<Engine::State> &Engine::StateMan::GetCurrent()
//{
//	return m_stateStack.top();
//;}