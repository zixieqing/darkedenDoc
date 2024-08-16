//----------------------------------------------------------------------
// MNPCTable.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MNPCTable.h"
#include "MCreatureTable.h"

//----------------------------------------------------------------------
// Global
//----------------------------------------------------------------------
MNPCTable*			g_pNPCTable = NULL;


//----------------------------------------------------------------------
//
// NPC_INFO
//
//----------------------------------------------------------------------
//----------------------------------------------------------------------
// Release
//----------------------------------------------------------------------
void
NPC_INFO::Release()
{
	ListShopTemplateID.clear();
}

//----------------------------------------------------------------------
// Save To File
//----------------------------------------------------------------------
void		
NPC_INFO::SaveToFile(class ofstream& file)
{
	//--------------------------------------------------
	// ListShopTemplateID
	//--------------------------------------------------
	Name.SaveToFile(file);

	int size = ListShopTemplateID.size();
	
	file.write((const char*)&size, 4);

	SHOPTEMPLATEID_LIST::iterator iID = ListShopTemplateID.begin();

	while (iID != ListShopTemplateID.end())
	{
		unsigned int id = *iID;

		file.write((const char*)&id, 4);

		iID++;
	}	

	//--------------------------------------------------
	// Description
	//--------------------------------------------------
	Description.SaveToFile( file );
	file.write((const char*)&SpriteID, 4);
}

//----------------------------------------------------------------------
// Load From File
//----------------------------------------------------------------------
void		
NPC_INFO::LoadFromFile(class ifstream& file)
{
	Release();

	Name.LoadFromFile(file);
	//--------------------------------------------------
	// ListShopTemplateID
	//--------------------------------------------------
	int size;
	
	file.read((char*)&size, 4);

	unsigned int id;

	for (int i=0; i<size; i++)
	{			
		file.read((char*)&id, 4);

		ListShopTemplateID.push_back( id );
	}

	//--------------------------------------------------
	// Description
	//--------------------------------------------------
	Description.LoadFromFile( file );
	file.read((char*)&SpriteID, 4);
}

//----------------------------------------------------------------------
//
// MNPCTable
//
//----------------------------------------------------------------------
MNPCTable::MNPCTable()
{
}
		
MNPCTable::~MNPCTable()
{
//	Release();
}



//----------------------------------------------------------------------
//
// SERVERNPC_INFO
//
//----------------------------------------------------------------------
//----------------------------------------------------------------------
// Release
//----------------------------------------------------------------------
void
SERVERNPC_INFO::Release()
{
	ListShopTemplateID.clear();
}

//----------------------------------------------------------------------
// Save To File
//----------------------------------------------------------------------
void		
SERVERNPC_INFO::SaveToFile(class ofstream& file)
{
	//--------------------------------------------------
	// ListShopTemplateID
	//--------------------------------------------------
	Name.SaveToFile(file);

	int size = ListShopTemplateID.size();
	
	file.write((const char*)&size, 4);

	SHOPTEMPLATEID_LIST::iterator iID = ListShopTemplateID.begin();

	while (iID != ListShopTemplateID.end())
	{
		unsigned int id = *iID;

		file.write((const char*)&id, 4);

		iID++;
	}	

	//--------------------------------------------------
	// Description
	//--------------------------------------------------
	Description.SaveToFile( file );
}

//----------------------------------------------------------------------
// Load From File
//----------------------------------------------------------------------
void		
SERVERNPC_INFO::LoadFromFile(class ifstream& file)
{
	Release();

	Name.LoadFromFile(file);
	//--------------------------------------------------
	// ListShopTemplateID
	//--------------------------------------------------
	int size;
	
	file.read((char*)&size, 4);

	unsigned int id;

	for (int i=0; i<size; i++)
	{			
		file.read((char*)&id, 4);

		ListShopTemplateID.push_back( id );
	}

	//--------------------------------------------------
	// Description
	//--------------------------------------------------
	Description.LoadFromFile( file );	
}

//----------------------------------------------------------------------
//
// MSERVERNPCTable
//
//----------------------------------------------------------------------
MServerNPCTable::MServerNPCTable()
{
	NPCSPRITEID.clear();

	NPCSPRITEID[157] = 1;
	NPCSPRITEID[17] = 2;
	NPCSPRITEID[16] = 3;
	NPCSPRITEID[18] = 4;
	NPCSPRITEID[26] = 5;
	NPCSPRITEID[21] = 6;
	NPCSPRITEID[97] = 7;
	NPCSPRITEID[100] = 8;
	NPCSPRITEID[24] = 9;
	NPCSPRITEID[14] = 10;
	NPCSPRITEID[110] = 11;
	NPCSPRITEID[108] = 12;
	NPCSPRITEID[101] = 13;
	NPCSPRITEID[95] = 14;
	NPCSPRITEID[109] = 15;
	NPCSPRITEID[103] = 16;
	NPCSPRITEID[27] = 17;
	NPCSPRITEID[98] = 18;
	NPCSPRITEID[15] = 19;
	NPCSPRITEID[20] = 20;
	NPCSPRITEID[96] = 21;
	NPCSPRITEID[11] = 22;
	NPCSPRITEID[102] = 23;
	NPCSPRITEID[23] = 24;
	NPCSPRITEID[158] = 25;
	NPCSPRITEID[99] = 26;
	NPCSPRITEID[25] = 27;
	NPCSPRITEID[163] = 28;
	NPCSPRITEID[162] = 29;
	NPCSPRITEID[164] = 30;
	NPCSPRITEID[12] = 31;
	NPCSPRITEID[13] = 32;
	NPCSPRITEID[22] = 33;
	NPCSPRITEID[159] = 34;
	NPCSPRITEID[160] = 35;
	NPCSPRITEID[161] = 36;
	NPCSPRITEID[19] = 37;
	NPCSPRITEID[93] = 38;
	NPCSPRITEID[92] = 39;
	NPCSPRITEID[94] = 40;
	NPCSPRITEID[219] = 41;
	NPCSPRITEID[220] = 42;
	NPCSPRITEID[253] = 48;
	NPCSPRITEID[254] = 47;
	NPCSPRITEID[255] = 49;
	NPCSPRITEID[217] = 43;
	NPCSPRITEID[250] = 44;
	NPCSPRITEID[251] = 44;
	NPCSPRITEID[252] = 44;
	NPCSPRITEID[296] = 45;
	NPCSPRITEID[297] = 46;
	NPCSPRITEID[362] = 50;
	NPCSPRITEID[363] = 51;
	NPCSPRITEID[364] = 52;
	NPCSPRITEID[365] = 53;
	NPCSPRITEID[366] = 54;
	NPCSPRITEID[302] = 45;
	NPCSPRITEID[303] = 46;
	NPCSPRITEID[311] = 45;
	NPCSPRITEID[368] = 39;
	NPCSPRITEID[370] = 35;
	NPCSPRITEID[427] = 55;
	NPCSPRITEID[428] = 56;
	NPCSPRITEID[429] = 57;
	NPCSPRITEID[430] = 58;
	NPCSPRITEID[519] = 59;			//���ϸ�',       
	NPCSPRITEID[521] = 60;			//�˷�',         
	NPCSPRITEID[525] = 66;			//�ø��',       
	NPCSPRITEID[516] = 62;			//����',         
	NPCSPRITEID[518] = 63;			//����Ʈ����',   	
	NPCSPRITEID[522] = 64;			//�ֵ�',       
	NPCSPRITEID[523] = 65;			//��ѵ�',       
	NPCSPRITEID[524] = 61;			//�귻��',       
	NPCSPRITEID[520] = 67;			//�ƹ�',         
	NPCSPRITEID[517] = 68;			//����',    	

	// 69 - 72 �� ���� �һ���, ��, ��, ��ǥ�� 
	//
	NPCSPRITEID[551] = 70;
	NPCSPRITEID[553] = 72;
	NPCSPRITEID[555] = 69;
	NPCSPRITEID[557] = 71;
	
	NPCSPRITEID[634] = 78;		// Ŀ�Ǽ� ������
	NPCSPRITEID[635] = 75;		// �Ǵ�
	NPCSPRITEID[636] = 76;		// �������� ����
	NPCSPRITEID[637] = 77;		// �ҸӴ�
	NPCSPRITEID[638] = 73;		// �Ƹ�Ÿ
	NPCSPRITEID[639] = 74;		// ����Ƽ
	NPCSPRITEID[653] = 79;		// ���Ͼ�
	NPCSPRITEID[654] = 74;		// ����Ƽ
	NPCSPRITEID[655] = 80;		// ���׽���
	NPCSPRITEID[656] = 81;		// �ÿ���
	NPCSPRITEID[657] = 73;		// �Ƹ�Ÿ
	NPCSPRITEID[658] = 82;		// ȣ��
	
	NPCSPRITEID[676] = 85;		// ������
	NPCSPRITEID[677] = 86;		// ����Ͼ�
	NPCSPRITEID[678] = 87;		// �̱״Ͼ�
	NPCSPRITEID[679] = 88;		// �ο�
	NPCSPRITEID[680] = 89;		// ���̻���
	NPCSPRITEID[681] = 90;		// ��Ʈ����
		
}
		
MServerNPCTable::~MServerNPCTable()
{
//	Release();
}

int	MServerNPCTable::AffectToNPCTable(MNPCTable * npc)
{
	// ũ�Ⱑ ���ƾ� �Ѵ�.
	int ServerSize = size();

	TYPE_MAP::iterator iData = begin();
	
	int count=0;
	while(iData != end())
	{
		count++;
		unsigned id			 = (*iData).first;
		SERVERNPC_INFO* info = (*iData).second;
		
		NPC_INFO *ni = new NPC_INFO;
		ni->Name = info->Name;
		ni->Description		= info->Description;
		ni->ListShopTemplateID.clear();

		(*g_pCreatureTable)[id].Name = info->Name;

		std::list<unsigned int>::iterator iID = info->ListShopTemplateID.begin();
		while (iID != info->ListShopTemplateID.end())
		{		
			ni->ListShopTemplateID.push_back(*iID);
			iID++;
		}

		if(NPCSPRITEID.find(id) == NPCSPRITEID.end())
			ni->SpriteID = -1;
		else
			ni->SpriteID = NPCSPRITEID[id];
		
		npc->AddData(id, ni);

		iData++;
	}

	if( ServerSize != count )
	{
		return false;
	}
	return true;
}