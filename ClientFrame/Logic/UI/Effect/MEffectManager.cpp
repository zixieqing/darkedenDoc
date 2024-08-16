//-----------------------------------------------------------------------------
// MEffectManager.cpp
//-----------------------------------------------------------------------------
#include "Client_PCH.h"
#include "MEffectManager.h"
#include "MEffect.h"

//-----------------------------------------------------------------------------
//
// constructor / destructor
//
//-----------------------------------------------------------------------------
MEffectManager::MEffectManager()
{
}

MEffectManager::~MEffectManager()
{
	Release();
}

//-----------------------------------------------------------------------------
//
// member functions
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Release
//-----------------------------------------------------------------------------
void		
MEffectManager::Release()
{
	EFFECT_LIST::iterator iEffect = m_listEffect.begin();

	// �� �����..
	while (iEffect != m_listEffect.end())
	{
		MEffect* pEffect = *iEffect;

		delete pEffect;

		iEffect ++;
	}

	m_listEffect.clear();
}

//-----------------------------------------------------------------------------
// Add Effect
//-----------------------------------------------------------------------------
void		
MEffectManager::AddEffect(MEffect* pEffect)
{
	if (pEffect != NULL)
	{
		// list�� �߰�
		m_listEffect.push_front( pEffect );
	}
}

//-----------------------------------------------------------------------------
// Update
//-----------------------------------------------------------------------------
/*
void		
MEffectManager::Update()
{
	EFFECT_LIST::iterator iEffect = m_listEffect.begin();

	while (iEffect != m_listEffect.end())
	{
		MEffect* pEffect = *iEffect;

		if (pEffect->Update())
		{
			// ����?�� ���
		}
		else
		{
			// Effect�� ���� ���(�� �̻� update�� �ʿ䰡 ���� ���)
		}

		iEffect ++;
	}
}
*/
