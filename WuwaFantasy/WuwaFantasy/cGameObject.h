
#pragma once
#include "cObject.h"
#include "cStatus.h"
#include "cSkinnedMesh.h"
#include "cWeaponSkinnedMesh.h"

const std::string MODEL_PATH = "./Resource/Model/";

class cCondition;
class cAction;

class cGameObject : public cObject
{
public:
	cStatus						m_pStatus;
	BOOL						m_isObject;

	cSkinnedMesh*				m_chrSkinnedMesh = nullptr;
	cWeaponSkinnedMesh*			m_objSkinnedMesh = nullptr;
	BoundingSphere				m_sphere;
	BoundingBox					m_box;

	cStateMachine*				m_pStateMachine=nullptr;
	std::list<cCondition*>		m_listCondition;

	size_t						m_unID = -1;
	size_t						m_unTag = -1;

	cAction*					m_pAction;
	bool						m_bAniUpdate = true;

public:
	cGameObject();
	virtual ~cGameObject();

	virtual void		Update();
	virtual void		Render();

	void SetID(const size_t& _id);
	void SetTag(const size_t& _tag);
	const size_t& GetID();
	const size_t& GetTag();

	cStatus&					GetStatus();
	cSkinnedMesh*				GetChrSkinnedMesh() { return m_chrSkinnedMesh; };
	cWeaponSkinnedMesh*			GetObjSkinnedMesh() { return m_objSkinnedMesh; };
	void						SetStateMachine(cStateMachine* _pStateMachine);
	cStateMachine*				GetStateMachine();
	const BoundingSphere&		GetBoundSphere();
	const BoundingBox&			GetBoundBox();

	void				AddCondition(cCondition* _pCondition);
	void				OnMessage(const ST_PACKET& _packet);

	virtual void		Setup() {};

	cAction*			GetAction();
	void				SetAniUpdate(bool d) { m_bAniUpdate = d; };

	void				SetBoundSphere(const BoundingSphere& _sphere);
	void				SetBoundBox(const BoundingBox& _box);
};