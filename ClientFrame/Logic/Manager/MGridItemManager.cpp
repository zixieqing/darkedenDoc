//----------------------------------------------------------------------
// MGridItemManager.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MItem.h"
#include "MItemFinder.h"
#include "MGridItemManager.h"

//#include "DebugInfo.h"
//#define	new			DEBUG_NEW
//#define	delete		DEBUG_DELETE

//----------------------------------------------------------------------
//
// constructor / destructor
//
//----------------------------------------------------------------------
MGridItemManager::MGridItemManager()
{
	m_Width = 0;
	m_Height = 0;
	m_ItemGrid = NULL;
}

MGridItemManager::~MGridItemManager()
{
	Release();
}

//----------------------------------------------------------------------
//
// member functions
//
//----------------------------------------------------------------------
//----------------------------------------------------------------------
// Init
//----------------------------------------------------------------------
void		
MGridItemManager::Init(BYTE width, BYTE height)
{
	Release();

	if (width!=0 && height!=0)
	{
		m_Width = width;
		m_Height = height;

		// MItem* m_ItemGrid[m_Height][m_Width] �� �޸� ���
		m_ItemGrid = new MItem** [m_Height];

		for (int i=0; i<m_Height; i++)
		{
			m_ItemGrid[i] = new MItem* [m_Width];

			// NULL�� �ʱ�ȭ
			for (int j=0; j<m_Width; j++)
			{
				m_ItemGrid[i][j] = NULL;
			}
		}
	}
}

//----------------------------------------------------------------------
// Release
//----------------------------------------------------------------------
void		
MGridItemManager::Release()
{
	MItemManager::Release();


	if (m_ItemGrid!=NULL)
	{
		for (int i=0; i<m_Height; i++)
		{
			delete [] m_ItemGrid[i];
		}			

		delete [] m_ItemGrid;
		
		m_ItemGrid = NULL;

		m_Width = 0;
		m_Height = 0;
	}
}

//----------------------------------------------------------------------
// Find 
//----------------------------------------------------------------------
// pItem�� ���� �� �ִ� ������ grid��ġ�� ��´�.
// First-Fit�� �����ϸ� �ȴ�.
//----------------------------------------------------------------------
bool			
MGridItemManager::GetFitPosition(MItem* pItem, POINT& point)
{
	int width = pItem->GetGridWidth();
	int height = pItem->GetGridHeight();
	
	int x, y;
	int i, j;
	
	//---------------------------------------------------------
	// grid�� ���(x,y)�� pItem�� �߰��� �� �ִ��� �˻��غ���.
	//---------------------------------------------------------
	int yLimit = m_Height - height;
	int xLimit = m_Width - width;

	int yPlusHeight, xPlusWidth;

	for (x=0; x<=xLimit; x++)
	{
		xPlusWidth = x+width;
		
		for (y=0; y<=yLimit; y++)
		{			
			yPlusHeight = y+height;

			//---------------------------------------------------------
			// (x,y)�� ���� �� �ִ��� üũ..
			//---------------------------------------------------------
			bool bPlace = true;

			for (i=y; bPlace && i<yPlusHeight; i++)
			{
				for (j=x; bPlace && j<xPlusWidth; j++)
				{
					//---------------------------------------------------------
					// �̹� �ٸ� Item�� �ִ� grid�� �ϳ��� �ִٸ� �߰��� �� ����.
					//---------------------------------------------------------
					if (m_ItemGrid[i][j]!=NULL)
					{
						bPlace = false;

						// ������ üũ�� ��...
						//x = j + m_ItemGrid[i][j]->GetGridWidth() - 1;
						//y = i + m_ItemGrid[i][j]->GetGridHeight() - 1;

						break;
					}
				}
			}
			
			//---------------------------------------------------------
			// (x,y)�� ���� �� �ִ� ���
			//---------------------------------------------------------
			if (bPlace)
			{
				point.x = x;
				point.y = y;
				
				return true;
			}
		}
	}

	return false;
}

//----------------------------------------------------------------------
// Can Replace Item
//----------------------------------------------------------------------
// �����δ� Add or Replace�� �ǹ��Ѵ�.
// (x,y)�� pItem�� ���� �� �ְų�
// (x,y)�� ������ ��, �ٸ� �� �ϳ��� ��ü�� �� ���� true�̴�.
// pOldItem���� ��ü�� �� �ִ� ��쿡 ���� �ִ� item�� ����.(üũ��)
//----------------------------------------------------------------------
bool			
MGridItemManager::CanReplaceItem(MItem* pItem, BYTE x, BYTE y, MItem*& pOldItem)
{
	pOldItem = NULL;

	//---------------------------------------------------------
	// ItemGrid ��踦 �Ѿ�� ���..
	//---------------------------------------------------------
	if (x>=m_Width || y>=m_Height)
	{
		return false;
	}

	// (x,y)���� pItem�� ���� �ȿ� �ִ� Item���� üũ�غ���.
	int width = pItem->GetGridWidth();
	int height = pItem->GetGridHeight();

	int i,j;
	int yPlusHeight = y+height;
	int xPlusWidth = x+width;

	//---------------------------------------------------------
	// Grid�� ������ ����� ���
	//---------------------------------------------------------
	if (xPlusWidth > m_Width || yPlusHeight > m_Height)
	{
		return false;
	}

	//---------------------------------------------------------
	// pItem�� ��ġ�� ���� Item�� �ϳ��� �ְų�
	// ����� �Ѵ�.
	//---------------------------------------------------------
	MItem* pCheckItem = NULL;
	MItem* pCurrentCheckItem;

	for (i=y; i<yPlusHeight; i++)
	{
		for (j=x; j<xPlusWidth; j++)
		{
			//---------------------------------------------------------
			// �̹� �ٸ� Item�� �ִ� ���.
			//---------------------------------------------------------
			pCurrentCheckItem = m_ItemGrid[i][j];
			if (pCurrentCheckItem!=NULL)
			{
				if (pCheckItem==NULL)
				{
					//---------------------------------------------------------
					// �ϳ��� Item�� ����صд�.
					//---------------------------------------------------------
					pCheckItem = pCurrentCheckItem;				
				}
				else
				{
					//---------------------------------------------------------
					// �������� Item�� �����ϴ� ���
					//---------------------------------------------------------
					if (pCheckItem->GetID() != pCurrentCheckItem->GetID())
					{					
						return false;
					}
				}

				
			}
		}
	}

	// �ֵ��� ������.. �׳� �����ϸ� �ȴ�.
	pOldItem = pCheckItem;

	return true;
}

//----------------------------------------------------------------------
// Add
//----------------------------------------------------------------------
// pItem�� ������ grid��ġ�� �߰��Ѵ�.
// First-Fit�� �����ϸ� �ȴ�.
//----------------------------------------------------------------------
bool			
MGridItemManager::AddItem(MItem* pItem)
{
	int width = pItem->GetGridWidth();
	int height = pItem->GetGridHeight();

	
	int x, y;
	int i, j;
	
	//---------------------------------------------------------
	// grid�� ���(x,y)�� pItem�� �߰��� �� �ִ��� �˻��غ���.
	//---------------------------------------------------------
	int yLimit = m_Height - height;
	int xLimit = m_Width - width;

	int yPlusHeight, xPlusWidth;

	for (x=0; x<=xLimit; x++)
	{
		xPlusWidth = x+width;
		
		for (y=0; y<=yLimit; y++)	
		{			
			yPlusHeight = y+height;

			//---------------------------------------------------------
			// (x,y)�� ���� �� �ִ��� üũ..
			//---------------------------------------------------------
			bool bPlace = true;

			for (i=y; bPlace && i<yPlusHeight; i++)
			{
				for (j=x; bPlace && j<xPlusWidth; j++)
				{
					//---------------------------------------------------------
					// �̹� �ٸ� Item�� �ִ� grid�� �ϳ��� �ִٸ� �߰��� �� ����.
					//---------------------------------------------------------
					if (m_ItemGrid[i][j]!=NULL)
					{
						bPlace = false;

						// ������ üũ�� ��...
						y = i + m_ItemGrid[i][j]->GetGridHeight() - 1;
						
						break;
					}
				}
			}
			
			//---------------------------------------------------------
			// (x,y)�� ���� �� �ִ� ���
			//---------------------------------------------------------
			if (bPlace)
			{
				//---------------------------------------------------------
				// ������ map�� �߰���Ų��.
				// ����� �߰��Ǹ�. grid���� ǥ�ø� �Ѵ�.
				//---------------------------------------------------------
				if (MItemManager::AddItem( pItem ))
				{
					//---------------------------------------------------------
					// item�� grid��ǥ�� ����
					//---------------------------------------------------------
					pItem->SetGridXY( x, y );

					//---------------------------------------------------------
					// Grid�� ǥ��
					//---------------------------------------------------------
					for (i=y; i<yPlusHeight; i++)
					{
						for (j=x; j<xPlusWidth; j++)
						{
							m_ItemGrid[i][j] = pItem;
						}
					}

					return true;
				}
			}
		}
	}

	return false;
}

//----------------------------------------------------------------------
// Add
//----------------------------------------------------------------------
// pItem�� (x,y)�� �߰��Ѵ�.
//----------------------------------------------------------------------
bool			
MGridItemManager::AddItem(MItem* pItem, BYTE x, BYTE y)
{
	//---------------------------------------------------------
	// ItemGrid ��踦 �Ѿ�� ���..
	//---------------------------------------------------------
	if (x>=m_Width || y>=m_Height)
	{
		return false;
	}

	int width = pItem->GetGridWidth();
	int height = pItem->GetGridHeight();

	
	int i,j;
	int yPlusHeight = y+height;
	int xPlusWidth = x+width;

	//---------------------------------------------------------
	// Grid�� ������ ����� ���
	//---------------------------------------------------------
	if (xPlusWidth > m_Width || yPlusHeight > m_Height)
	{
		return false;
	}

	//---------------------------------------------------------
	// pItem�� ��ġ�� ���� ��� ����־�� �Ѵ�.
	//---------------------------------------------------------
	for (i=y; i<yPlusHeight; i++)
	{
		for (j=x; j<xPlusWidth; j++)
		{
			//---------------------------------------------------------
			// �̹� �ٸ� Item�� �ִ� grid�� �ϳ��� �ִٸ� �߰��� �� ����.
			//---------------------------------------------------------
			if (m_ItemGrid[i][j]!=NULL)
				return false;
		}
	}	

	//---------------------------------------------------------
	// ������ map�� �߰���Ų��.
	// ����� �߰��Ǹ�. grid���� ǥ�ø� �Ѵ�.
	//---------------------------------------------------------
	if (MItemManager::AddItem( pItem ))
	{
		//---------------------------------------------------------
		// item�� grid��ǥ�� ����
		//---------------------------------------------------------
		pItem->SetGridXY( x, y );

		//---------------------------------------------------------
		// Grid�� ǥ��
		//---------------------------------------------------------
		for (i=y; i<yPlusHeight; i++)
		{
			for (j=x; j<xPlusWidth; j++)
			{
				m_ItemGrid[i][j] = pItem;
			}
		}

		return true;
	}

	return false;	
}

//----------------------------------------------------------------------
// Get
//----------------------------------------------------------------------
// grid(x,y)�� item�� �о�´�.
//----------------------------------------------------------------------
MItem*	
MGridItemManager::GetItem(BYTE x, BYTE y) const
{
	//---------------------------------------------------------
	// ItemGrid ��踦 �Ѿ�� ���..
	//---------------------------------------------------------
	if (x>=m_Width || y>=m_Height)
	{
		return NULL;
	}

	return m_ItemGrid[y][x];
}

//----------------------------------------------------------------------
// Remove
//----------------------------------------------------------------------
// grid(x,y)�� item�� �����Ѵ�.
//----------------------------------------------------------------------
MItem*			
MGridItemManager::RemoveItem(BYTE x, BYTE y)
{
	//---------------------------------------------------------
	// ItemGrid ��踦 �Ѿ�� ���..
	//---------------------------------------------------------
	if (x>=m_Width || y>=m_Height)
	{
		return NULL;
	}

	MItem* pItem = m_ItemGrid[y][x];

	//---------------------------------------------------------
	// (x,y)�� item�� ���� ���..
	//---------------------------------------------------------
	if (pItem == NULL)
	{
		return NULL;
	}

	//---------------------------------------------------------	
	// ItemManager�� map���� �����Ѵ�.
	//---------------------------------------------------------	
	pItem = MItemManager::RemoveItem( pItem->GetID() );

	// ���� ���..
	if (pItem == NULL)
	{
		return NULL;
	}

	// grid�� pItem�� map�� pItem�� ��������
	// üũ ���ص� �ǰ���.. - -;

	//---------------------------------------------------------	
	// item�� �����ϴ� �� grid�� ������ ������� �Ѵ�.
	//---------------------------------------------------------
	// (x,y)�� grid ù��ġ��..
	x = pItem->GetGridX();
	y = pItem->GetGridY();
	int width = pItem->GetGridWidth();
	int height = pItem->GetGridHeight();

	int i,j;
	int yPlusHeight = y + height;
	int xPlusWidth = x + width;

	// �� grid�� NULL�� �����.
	for (i=y; i<yPlusHeight; i++)
	{
		for (j=x; j<xPlusWidth; j++)
		{
			m_ItemGrid[i][j] = NULL;				
		}
	}	

	//---------------------------------------------------------
	// ��ǥ�� �����ش�.
	//---------------------------------------------------------
	// ���� �ǹ� ���� �ڵ� ������.. - -;; �׳�..
	//---------------------------------------------------------
	//pItem->SetGridXY(0, 0);

	return pItem;
}

MItem *MGridItemManager::GetItem(TYPE_OBJECTID id) const
{
	return MItemManager::GetItem(id);
}

//----------------------------------------------------------------------
// Remove
//----------------------------------------------------------------------
// grid(x,y)�� item�� �����Ѵ�.
//----------------------------------------------------------------------
MItem*			
MGridItemManager::RemoveItem(TYPE_OBJECTID id)
{
	MItem* pItem = MItemManager::RemoveItem( id );

	//---------------------------------------------------------
	// �׷� id�� ���� item�� ���� ���
	//---------------------------------------------------------
	if (pItem==NULL)
	{
		return NULL;
	}

	//---------------------------------------------------------	
	// item�� �����ϴ� �� grid�� ������ ������� �Ѵ�.
	//---------------------------------------------------------
	int x	= pItem->GetGridX();
	int y	= pItem->GetGridY();
	int width = pItem->GetGridWidth();
	int height = pItem->GetGridHeight();

	int i,j;
	int yPlusHeight = y + height;
	int xPlusWidth = x + width;

	// �� grid�� NULL�� �����.
	for (i=y; i<yPlusHeight; i++)
	{
		for (j=x; j<xPlusWidth; j++)
		{
			m_ItemGrid[i][j] = NULL;				
		}
	}	

	//---------------------------------------------------------
	// ��ǥ�� �����ش�.
	//---------------------------------------------------------
	// ���� �ǹ� ���� �ڵ� ������.. - -;; �׳�..
	//---------------------------------------------------------
	//pItem->SetGridXY(0, 0);

	return pItem;
}

//----------------------------------------------------------------------
// Replace Item
//----------------------------------------------------------------------
// (x,y)��ġ���� pItem�� ũ�� �ȿ� �ִ� Item�� replace
// pOldItem�� ������ �ִ����� ����.
//----------------------------------------------------------------------
bool			
MGridItemManager::ReplaceItem(MItem* pItem, BYTE x, BYTE y, MItem*& pOldItem)
{
	pOldItem = NULL;

	//---------------------------------------------------------
	// ItemGrid ��踦 �Ѿ�� ���..
	//---------------------------------------------------------
	if (x>=m_Width || y>=m_Height)
	{
		return false;
	}	

	// (x,y)���� pItem�� ���� �ȿ� �ִ� Item���� üũ�غ���.
	int width = pItem->GetGridWidth();
	int height = pItem->GetGridHeight();

	int i,j;
	int yPlusHeight = y+height;
	int xPlusWidth = x+width;

	//---------------------------------------------------------
	// Grid�� ������ ����� ���
	//---------------------------------------------------------
	if (xPlusWidth > m_Width || yPlusHeight > m_Height)
	{
		return false;
	}

	//---------------------------------------------------------
	// pItem�� ��ġ�� ���� Item�� �ϳ��� �ְų�
	// ����� �Ѵ�.
	//---------------------------------------------------------
	MItem* pCheckItem = NULL;
	MItem* pCurrentCheckItem;

	for (i=y; i<yPlusHeight; i++)
	{
		for (j=x; j<xPlusWidth; j++)
		{
			//---------------------------------------------------------
			// �̹� �ٸ� Item�� �ִ� ���.
			//---------------------------------------------------------
			pCurrentCheckItem = m_ItemGrid[i][j];
			if (pCurrentCheckItem!=NULL)
			{
				if (pCheckItem==NULL)
				{
					//---------------------------------------------------------
					// �ϳ��� Item�� ����صд�.
					//---------------------------------------------------------
					pCheckItem = pCurrentCheckItem;				
				}
				else
				{
					//---------------------------------------------------------
					// �������� Item�� �����ϴ� ���
					//---------------------------------------------------------
					if (pCheckItem->GetID() != pCurrentCheckItem->GetID())
					{					
						return false;
					}
				}

				
			}
		}
	}

	//---------------------------------------------------------
	// pItem�� �߰��ҷ��� �ڸ��� �ٸ� Item�� �ϳ� �ִ� ���
	//---------------------------------------------------------
	// �� Item�� �����Ѵ�.
	//---------------------------------------------------------
	if (pCheckItem!=NULL)
	{
		//---------------------------------------------------------	
		// �ٸ� Item�� �����Ѵ�.
		//---------------------------------------------------------	
		// ItemManager�� map���� �����Ѵ�.
		//---------------------------------------------------------	
		if (MItemManager::RemoveItem( pCheckItem->GetID() ) == NULL)
		{
			return false;
		}

		// grid�� pItem�� map�� pItem�� ��������
		// üũ ���ص� �ǰ���.. - -;

		//---------------------------------------------------------	
		// item�� �����ϴ� �� grid�� ������ ������� �Ѵ�.
		//---------------------------------------------------------
		// (x,y)�� grid ù��ġ��..
		int ox = pCheckItem->GetGridX();
		int oy = pCheckItem->GetGridY();
		int owidth = pCheckItem->GetGridWidth();
		int oheight = pCheckItem->GetGridHeight();

		int oyPlusHeight = oy + oheight;
		int oxPlusWidth = ox + owidth;

		// �� grid�� NULL�� �����.
		for (i=oy; i<oyPlusHeight; i++)
		{
			for (j=ox; j<oxPlusWidth; j++)
			{
				m_ItemGrid[i][j] = NULL;				
			}
		}	

		// ���� �ǹ� ���� �ڵ� 
		//pCheckItem->SetGridXY(0, 0);

		// ������ �ִ� Item�� �Ѱ��ش�.
		pOldItem = pCheckItem;
	}

	//---------------------------------------------------------
	// pItem�� (x,y)�� �߰��Ѵ�.
	//---------------------------------------------------------
	// ������ map�� �߰���Ų��.
	// ����� �߰��Ǹ�. grid���� ǥ�ø� �Ѵ�.
	//---------------------------------------------------------
	if (MItemManager::AddItem( pItem ))
	{
		//---------------------------------------------------------
		// item�� grid��ǥ�� ����
		//---------------------------------------------------------
		pItem->SetGridXY( x, y );

		//---------------------------------------------------------
		// Grid�� ǥ��
		//---------------------------------------------------------
		for (i=y; i<yPlusHeight; i++)
		{
			for (j=x; j<xPlusWidth; j++)
			{
				m_ItemGrid[i][j] = pItem;
			}
		}
	}

	return true;
}

//----------------------------------------------------------------------
// Find Item Grid Order
//----------------------------------------------------------------------
// �������� ����������.. 
// ������ �Ʒ��� �˻�..
//----------------------------------------------------------------------
MItem*			
MGridItemManager::FindItemGridOrder( MItemFinder& itemFinder ) const
{
	int x, y;
	int i, j;	

	//---------------------------------------------------------
	// grid üũ��
	//---------------------------------------------------------	
	bool** bCheck = new bool* [m_Height];
	for (i=0; i<m_Height; i++)
	{
		bCheck[i] = new bool [m_Width];

		memset( bCheck[i], 0, m_Width );

		//for (int j=0; j<m_Width; j++)
		//{
		//	bCheck[i][j] = false;
		//}
	}
	
	//---------------------------------------------------------
	// grid�� ������� item�� �˻��غ���.
	//---------------------------------------------------------
	for (y=0; y<m_Height; y++)
	{
		for (x=0; x<m_Width; x++)	
		{		
			// �̹� üũ �ߴٸ�.. üũ���� �ʴ´�.
			if (bCheck[y][x])
			{
				continue;
			}

			MItem* pItem = m_ItemGrid[y][x];
			
			if (pItem!=NULL)
			{
				if (itemFinder( pItem ))
				{
					return pItem;
				}

				// �������� grid��ŭ�� üũ�Ѵ�.
				int maxY = y + pItem->GetGridHeight();
				int maxX = x + pItem->GetGridWidth();

				// �̹� item�� �� ��ǥ�̹Ƿ� grid�� ����� �ʴ´ٰ� �����Ѵ�.
				// ��ĭ¥���� üũ ���ص� �Ǵµ�.. �׳�..
				for (i=y; i<maxY; i++)
				{
					for (j=x; j<maxX; j++)
					{
						bCheck[i][j] = true;
					}
				}
			}
		}
	}

	//---------------------------------------------------------
	// üũ�� �����
	//---------------------------------------------------------
	if (bCheck!=NULL)
	{
		for (int i=0; i<m_Height; i++)
		{
			delete [] bCheck[i];
		}			

		delete [] bCheck;		
	}

	return false;
}

