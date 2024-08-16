//-----------------------------------------------------------------------------
// MScreenEffectManager.cpp
//-----------------------------------------------------------------------------
#include "Client_PCH.h"
#include "MScreenEffectManager.h"
#include "MEffect.h"
#include "MScreenEffect.h"
#include "MEffectGeneratorTable.h"
#include "UIFunction.h"
#include "MInventory.h"

//-----------------------------------------------------------------------------
// Update
//-----------------------------------------------------------------------------
void		
MScreenEffectManager::Update()
{
	EFFECT_LIST::iterator iEffect = m_listEffect.begin();

	EFFECT_LIST::iterator iTemp;
	
//	POINT point;

	MEffect* pEffect;
	int count = m_listEffect.size();

	for (int i=0; i<count; i++)	
	{
		pEffect = *iEffect;

/*		if (pEffect->GetEffectType()==MEffect::EFFECT_SCREEN)
		{
			MScreenEffect* pScreenEffect = (MScreenEffect*)pEffect;
			
			const int invenX = pEffect->GetX(), invenY = pEffect->GetY();

			POINT grid_plus = { 0, 0 };

			const MItem* pItem = g_pInventory->GetItem( invenX, invenY );
			
			//---------------------------------------------------------------
			// �������� ������ ũ�⿡ ���� ����Ʈ�� �ٲ��.
			//---------------------------------------------------------------
			if (pItem!=NULL)
			{
				grid_plus.x = (pItem->GetGridWidth()-1)*30/2;	// �䤻���� �ϵ��ڵ�
				grid_plus.y = (pItem->GetGridHeight()-1)*30/2;	// �䤻���� �ϵ��ڵ�
			}
			//---------------------------------------
			// ���� ��ǥ�� �°� ����
			//---------------------------------------
			point = UI_GetInventoryGridPosition( invenX, invenY );
			pScreenEffect->SetScreenPosition(point.x, point.y);			
		}
*/
		//---------------------------------------
		//
		// update --> ���������� �� ���
		//
		//---------------------------------------
		if (pEffect->Update())
		{
			
			iEffect++;

			//-----------------------------------------------
			//
			// �� Effect�� ������ ���� LinkCount�� ���ؼ�
			// ���� ����Ǵ� Effect�� ������ �����ؾ� �Ѵ�.
			//
			// ����Frame�� EndLinkFrame�� �Ѿ ���
			//
			//-----------------------------------------------
			if (g_CurrentFrame >= pEffect->GetEndLinkFrame()
				&& pEffect->GetLinkSize() != 0)
			{
				// GenerateNext���� 
				// pEffect�� EffectTarget�� NULL�� ������ֱ� ������
				// ���⼭ ���� �ʿ� ����.
				(*g_pEffectGeneratorTable).GenerateNext( pEffect );

				// pEffect�� ������ �����ؾ� �ϹǷ� ����� �ȵȴ�.
			}			
		}
		//---------------------------------------
		//
		// �� �ż� ���� ���
		//
		//---------------------------------------
		else
		{
			iTemp = iEffect;
			iEffect++;
			
			//-----------------------------------------------
			// ���� ����Ǵ� Effect�� ������ �����ؾ� �Ѵ�.
			//-----------------------------------------------
			if (pEffect->GetLinkSize() != 0)
			{
				(*g_pEffectGeneratorTable).GenerateNext( pEffect );
			}
/*			else if(pEffect->GetEffectTarget() != NULL && pEffect->GetEffectTarget()->IsEnd())
			{
				//------------------------------------------------------------
				// pEffect�� ������ �����ؼ� Generate�Ѵ�.
				//------------------------------------------------------------
				MEffectTarget* pEffectTarget = pEffect->GetEffectTarget();
				
				if (pEffectTarget->IsExistResult())
				{
					MActionResult* pResult = pEffectTarget->GetResult();
					
					pEffectTarget->SetResultNULL();
					
#ifdef OUTPUT_DEBUG_EFFECT_GENERATOR
					DEBUG_ADD("Execute Result0");
#endif
					
					// ��� ����
					pResult->Execute();
					
					// �޸� ����
					delete pResult;			
				}
				
			}
*/
			//-----------------------------------------------
			// ����
			//-----------------------------------------------
			delete pEffect;

			// list���� �����Ѵ�.
			m_listEffect.erase(iTemp);
		}
	
	}
}

