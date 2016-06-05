#pragma once
#include"cIState.h"

template <typename ENTITY_TYPE>
class cStateMachine
{
private:
	ENTITY_TYPE*			m_pOwner = nullptr;
	cIState<ENTITY_TYPE>*	m_pPreviousState = nullptr;
	cIState<ENTITY_TYPE>*	m_pCurrentState = nullptr;
	cIState<ENTITY_TYPE>*	m_pGlobalState = nullptr;

public:
	cStateMachine() {};
	cStateMachine(ENTITY_TYPE* _pOwner)
		:m_pOwner(_pOwner) {}
	~cStateMachine() {};

	void SetCurrentState(cIState<ENTITY_TYPE>* _currentState)
	{
		m_pCurrentState = _currentState;
	}
	void SetPreviousState(cIState<ENTITY_TYPE>* _privioustState)
	{
		m_pPreviousState = _privioustState;
	}
	void SetGlobalState(cIState<ENTITY_TYPE>* _globalState)
	{
		m_pGlobalState = _globalState;
	}

	void Update()
	{
		if (m_pGlobalState)
			m_pGlobalState->Execute(m_pOwner);
		
		if (m_pCurrentState)
			m_pCurrentState->Execute(m_pOwner);
	}

	bool MessageHandle(const ST_PACKET& msg) const
	{
		if (m_pCurrentState && m_pCurrentState->OnMessage(m_pOwner, msg))
		{
			return true;
		}

		if (m_pGlobalState && m_pGlobalState->OnMessage(m_pOwner, msg))
		{
			return true;
		}

		return false;
	}

	void  ChangeState(cIState<ENTITY_TYPE>* _pNewState)
	{
#ifdef _DEBUG
		assert(_pNewState && "ChangeState() received null ptr");
#endif
		m_pPreviousState = m_pCurrentState;
		m_pCurrentState->Exit(m_pOwner);

		m_pCurrentState = _pNewState;
		m_pCurrentState->Enter(m_pOwner);
	}

	void RevertState()
	{
		ChangeState(m_pPreviousState);
	}

	//returns true if the current state's type is equal to the type of the
	//class passed as a parameter. 
	//bool  isInState(const State<entity_type>& st)const
	//{
	//	if (typeid(*m_pCurrentState) == typeid(st)) return true;
	//	return false;
	//}

	//State<entity_type>*  CurrentState()  const { return m_pCurrentState; }
	//State<entity_type>*  GlobalState()   const { return m_pGlobalState; }
	//State<entity_type>*  PreviousState() const { return m_pPreviousState; }

	////only ever used during debugging to grab the name of the current state
	//std::string         GetNameOfCurrentState()const
	//{
	//	std::string s(typeid(*m_pCurrentState).name());

	//	//remove the 'class ' part from the front of the string
	//	if (s.size() > 5)
	//	{
	//		s.erase(0, 6);
	//	}

	//	return s;
	//}
};
