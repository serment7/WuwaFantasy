#pragma once

#define g_pTimeManager cTimeManager::GetInstance()

class cTimeManager
{
private:
	LARGE_INTEGER timeStart;
	LARGE_INTEGER timeEnd;
	LARGE_INTEGER timerFreq;
	float			fDeltaTime;
	DWORD			dwCurrentTime;
public:
	cTimeManager();
	virtual ~cTimeManager();

	static cTimeManager* GetInstance()
	{
		static cTimeManager instance;
		return &instance;
	}
	void Update();
	const float& GetDeltaTime();
	const DWORD& GetCurTime();
};