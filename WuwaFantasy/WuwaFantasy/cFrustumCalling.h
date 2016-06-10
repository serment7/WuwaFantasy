#pragma once

class cFrustumCalling
{
private:
	std::vector<D3DXVECTOR3> m_vecFrustum;
	std::vector<D3DXPLANE> m_vecIndex;

public:
	cFrustumCalling();
	~cFrustumCalling();

	void Setup();
	void Update(D3DXVECTOR3 vPos);
	void Render();

	BOOL IsitCulling(BoundingSphere* bs);

};

