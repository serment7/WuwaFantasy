
#pragma once

#include"cStateMachine.h"
class cCondition;

//interface
class iObject
{

protected:
	int				nRefCount = 0;
	virtual	~iObject() {};
public:
	virtual D3DXMATRIXA16 GetWorldMatrix() PURE;
	void AddRef() { ++nRefCount; };
	void Release()
	{
		--nRefCount;
		if (nRefCount <= 0)
			delete this;
	};
};

//cObject
class cObject : public iObject
{
private:
	D3DXMATRIXA16	m_matS;
	D3DXMATRIXA16	m_matT;
	D3DXMATRIXA16	m_matR;

	D3DXMATRIXA16	m_matWorld;

	D3DXVECTOR3		m_vPos;
	D3DXVECTOR3		m_vBaseDir;
	D3DXVECTOR3		m_vDir;
	D3DXVECTOR3		m_vScale;

	float			m_fAngleY = 0.0f;

	bool			m_bUseAngle=false;
	bool			m_bCalcHeight = true;

public:
	cObject();
	virtual ~cObject();

	void SetScaling(const float& sx, const float& sy, const float& sz)
	{
		m_vScale.x = sx;
		m_vScale.y = sy;
		m_vScale.z = sz;
	}

	void SetRotation(float angle, char axis = 'y')
	{
		//stdafx�� enum�� �߰����ּŵ� ��
		if(axis == 'x')
		{
			D3DXMatrixRotationX(&m_matR, angle);			
		}
		else if(axis == 'z')
		{
			D3DXMatrixRotationZ(&m_matR, angle);
		}
		else
		{
			//D3DXMatrixRotationY(&m_matR, angle);
			m_fAngleY = angle;
		}
	}

	virtual void Update();
	virtual void Render() {};

	//Getter, Setter
	D3DXMATRIXA16 GetWorldMatrix() { return m_matWorld; }
	D3DXMATRIXA16 GetScalingMatrix() { return m_matS; }
	D3DXVECTOR3	GetVPos() { return m_vPos; }
	D3DXVECTOR3 GetVDir() { return m_vDir; }
	D3DXVECTOR3 GetVScale() { return m_vScale; }
	D3DXVECTOR3 SetVBaseDir() { return m_vBaseDir; }
	const int& GetCountRef() { return nRefCount; }

	void SetScalingMatrix( const D3DXMATRIXA16& matS ) { m_matS = matS; }
	void SetVPos( D3DXVECTOR3 vPos ) { m_vPos = vPos; }
	void SetVDir( D3DXVECTOR3 vDir ) { m_vDir = vDir; }
	void SetVBaseDir(D3DXVECTOR3 vDir) { m_vBaseDir = vDir; }
	const float&	GetRotationY() const;
	void			SetUseAngle(bool _bUseAngle);
	void			SetCalcHeight(bool _bCalcHeight);
};