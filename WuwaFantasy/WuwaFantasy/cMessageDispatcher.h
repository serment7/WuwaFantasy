#pragma once

#define g_pMessageDispatcher cMessageDispatcher::GetInstance()

inline bool operator==(const ST_PACKET& _packet1, const ST_PACKET& _packet2)
{
	return (fabs(_packet1.delayTime - _packet2.delayTime) < 0.01f) &&
		(_packet1.sender == _packet2.sender) &&
		(_packet1.receiver == _packet2.receiver) &&
		(_packet1.msg_type == _packet2.msg_type);
}

inline bool operator<(const ST_PACKET& _packet1, const ST_PACKET& _pakcet2)
{
	return  (_packet1.delayTime < _pakcet2.delayTime);
}

class cMessageDispatcher
{
private:
	typedef std::set<ST_PACKET>				MsgSet;

private:
	MsgSet		m_message;

public:
	cMessageDispatcher();
	~cMessageDispatcher();

	static cMessageDispatcher* GetInstance()
	{
		static cMessageDispatcher instance;
		return &instance;
	}

	void Update();
	void Dispatch(const size_t& _sender, const size_t& _receiver,const float& _delay, 
		Msg_Type _msg_type, void* _info);
	void Clear();
};
