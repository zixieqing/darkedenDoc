//----------------------------------------------------------------------
// MChatManager.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MChatManager.h"


#ifdef __GAME_CLIENT__
	#include "MGameStringTable.h"
	#include "UserOption.h"
#endif


//----------------------------------------------------------------------
// Global
//----------------------------------------------------------------------
MChatManager*		g_pChatManager = NULL;

//----------------------------------------------------------------------
// Static
//----------------------------------------------------------------------
char MChatManager::s_MaskString[256] = //"^^; -_-; !_!; o_O; *_*; m_m; u_u; p_q; =_=; -_+; $_$; v_v; Y_Y; o_o; O_O; w_w; #_#; ._.; n_n; &_&; @_@; 0_0; _-_; +_+; +_=; ~_~;";
		"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
		
char MChatManager::s_MaskString2[256] = 
		"#&*%!$#%&*@!%&$&#*&$@#*!%$&@#&*%!$#%&*@!%&$&#*&$@&#!%$*&%*#@#*!%$&@#&*%!$#%&*@!%&$&#*&$@#*!%$&@#&*!$#%&*@!%&$&#*&$@#*!%$&@#&*%!$#%&!$#%&*@!%&$&#*&$@#*!%$&@#&*%!$#%&*";
		//".....................................................................................................................................................................";

//----------------------------------------------------------------------
//
// constructor / destructor
// 
//----------------------------------------------------------------------
MChatManager::MChatManager()
{
	m_bIgnoreMode = false;
}

MChatManager::~MChatManager()
{
}

//----------------------------------------------------------------------
//
// member functions
//
//----------------------------------------------------------------------
//----------------------------------------------------------------------
// Save To File
//----------------------------------------------------------------------
void				
MChatManager::SaveToFile(const char* filename)
{
	class ofstream file(filename, ios::binary);

	m_mapCurseEng.SaveToFile( file );
	m_mapCurseKor1.SaveToFile( file );
	m_mapCurseKor2.SaveToFile( file );
	m_mapCurseKor3.SaveToFile( file );
	m_mapCurseKor4.SaveToFile( file );
	m_mapID.SaveToFile( file );
	
	file.close();
}

//----------------------------------------------------------------------
// Load From File
//----------------------------------------------------------------------
void				
MChatManager::LoadFromFile(const char* filename)
{
	class ifstream file(filename, ios::binary);

	m_mapCurseEng.LoadFromFile( file );
	m_mapCurseKor1.LoadFromFile( file );
	m_mapCurseKor2.LoadFromFile( file );
	m_mapCurseKor3.LoadFromFile( file );
	m_mapCurseKor4.LoadFromFile( file );
	m_mapID.LoadFromFile( file );

	file.close();
}

//----------------------------------------------------------------------
// Load From File Curse
//----------------------------------------------------------------------
// text file���� �� �б�
//----------------------------------------------------------------------
void				
MChatManager::LoadFromFileCurse(const char* filename)
{
	class ifstream file(filename, ios::nocreate);

	if (!file.is_open())
	{
		return;
	}

	char str[256];

	//-----------------------------------------------------
	// text file���� ����~~ �о���δ�.
	//-----------------------------------------------------
	while (!file.eof())
	{
		file >> str;

		bool bEng = true;
		bool bKor = true;

		char* strTemp = str;
		char ch;

		//-----------------------------------------------------
		// �ܾ �������� �ѱ����� �Ǵ��Ѵ�.
		//-----------------------------------------------------
		while (ch=*strTemp++)
		{
			//-----------------------------------------------------
			// �ѱ��� ���
			//-----------------------------------------------------
			if (ch & 0x80)
			{
				if (*strTemp=='\0')
				{
					bKor = false;
					break;
				}

				strTemp++;

				bEng = false;
			}
			//-----------------------------------------------------
			// ������ ���
			//-----------------------------------------------------
			else if (ch>='a' && ch<='z')
			{
				bKor = false;
			}
			//-----------------------------------------------------
			// �ƴϸ� .. ������.
			//-----------------------------------------------------
			else				
			{
				bEng = false;
				bKor = false;

				break;
			}
		}

		//-----------------------------------------------------
		// ����..��� �Ǵܵ� ���
		//-----------------------------------------------------
		if (bEng)
		{
			m_mapCurseEng.Add(str);
		}
		//-----------------------------------------------------
		// �ѱ�..�̶�� �Ǵܵ� ���
		//-----------------------------------------------------
		else if (bKor)
		{
			//-----------------------------------------------------
			// �ѱ� 1,2,3,4�ڸ� ����Ѵ�.
			//-----------------------------------------------------
			switch (strlen(str))
			{
				case 2 : m_mapCurseKor1.Add(str); break;
				case 4 : m_mapCurseKor2.Add(str); break;
				case 6 : m_mapCurseKor3.Add(str); break;
				case 8 : m_mapCurseKor4.Add(str); break;
			}
		}
	}

	file.close();
}

//----------------------------------------------------------------------
// Remove Curse
//----------------------------------------------------------------------
bool				
MChatManager::RemoveCurse(char* str, bool bForce) const
{
	#ifdef __GAME_CLIENT__
		if (!g_pUserOption->FilteringCurse && bForce == false || str==NULL)
		{
			return false;
		}
	#else
		if (str==NULL)
		{
			return false;
		}
	#endif


	bool existCurseEng = false;
	bool existCurseKor = false;

	int len = strlen(str);
	int i;
	int index;
	
	//const char* strMask = //"^^; -_-; !_!; o_O; *_*; m_m; u_u; p_q; =_=; -_+; $_$; v_v; Y_Y; o_o; O_O; w_w; #_#; ._.; n_n; &_&; @_@; 0_0; _-_; +_+; +_=; ~_~;";
	//	"#&*%!$#%&*@!%&$&#*&$@#*!%$&@#&*%!$#%&*@!%&$&#*&$@&#!%$*&%*#@#*!%$&@#&*%!$#%&*@!%&$&#*&$@#*!%$&@#&*%!$#%&*@!%&$&#*&$@#*!%$&@";

	//------------------------------------------------------------
	// �ʿ��� ���ڵ鸸 �ɷ��� string
	//------------------------------------------------------------
	char*	strFiltered = new char [len+1];		

	//------------------------------------------------------------
	// filter�� ���ڵ��� ���� string������ index
	//------------------------------------------------------------
	int*	indexFiltered = new int [len+1];		

	//------------------------------------------------------------
	// ������ �ƴ��� �Ǵ��Ѵ�.
	//------------------------------------------------------------
	//bool*	isCurse = new bool [len+1];
	BYTE*	isCurse = new BYTE [len+1];
	

	//------------------------------------------------------------
	//
	//					����� ���� 
	//
	//------------------------------------------------------------
	// ���ĺ��� �����... lower char����..
	// (!) string���� ���� ã�´�.	
	//------------------------------------------------------------
	// hi, hello! f.u.c.k!~~!
	// --> hihellofuck
	//	 ���� string�� index�� �������� �ٸ� ���ڷ� ġȯ�ϱⰡ ����.
	// 
	// ���� ���� ������ �������� �����ϱ�.. strstr�� �������ؾ��Ѵ�.	
	//------------------------------------------------------------
	char*	strFilteredPtr = strFiltered;
	int*	indexFilteredPtr = indexFiltered;
	BYTE*	isCursePtr = isCurse;
	
	char*	strOrg = str;	// üũ�� ���ؼ�..
	
	char	ch;
	const char toLower = 'a'-'A';

	//------------------------------------------------------------
	// ��� �ɷ����� �ҹ��ڷ� �ٲ۴�.
	//------------------------------------------------------------
	i = 0;
	index = 0;
	while (ch = *strOrg++)//, ch != '\0')
	{
		//----------------------------------------------
		// �ҹ����� ��� --> �״�� ����.
		//----------------------------------------------
		if (ch >= 'a' && ch <= 'z')
		{
			*strFilteredPtr++	= ch;
			*indexFilteredPtr++ = i;
			*isCursePtr++		= false;	// �ʱ�ȭ			
			index++;
		}		
		//----------------------------------------------
		// �빮���� ��� --> �ҹ��ڷ� �ٲ۴�.
		//----------------------------------------------
		else if (ch >= 'A' && ch <= 'Z')
		{
			*strFilteredPtr++	= ch + toLower;
			*indexFilteredPtr++ = i;
			*isCursePtr++		= false;	// �ʱ�ȭ
			index++;
		}
		
		//----------------------------------------------
		// �ٸ� ���� ���õǴ� �����̴�.
		//----------------------------------------------

		i++;
	}
	*strFilteredPtr = '\0';
	
	//------------------------------------------------------------
	// ��� �ִ� ��츸 ������� �����Ѵ�.
	//------------------------------------------------------------
	if (index!=0)
	{
		MStringMap::const_iterator iString = m_mapCurseEng.begin();
		
		//------------------------------------------------------------
		// ��� ��鿡 ���ؼ� �� ���Ѵ�... strFiltered�� �ִ���..
		//------------------------------------------------------------
		while (iString != m_mapCurseEng.end())
		{
			const MString* pString = iString->second;

			if (pString!=NULL)
			{
				strFilteredPtr = strFiltered;

				char* pFind = NULL;

				//---------------------------------------------------
				// strFiltered���� ���� ã�´�.
				//---------------------------------------------------
				while (pFind = strstr( strFilteredPtr, pString->GetString() ))
				{					
					int lenCurse = pString->GetLength();

					//---------------------------------------------------
					// ã������.. ǥ���صд�.
					//---------------------------------------------------
					// 2004, 10, 26, sobeit modify start - ������ ����
					//memset( isCurse+(pFind-strFilteredPtr), true, lenCurse);
					memset( isCurse+(pFind-strFilteredPtr), lenCurse, lenCurse);
					// 2004, 10, 26, sobeit modify end - ������ ����
					
					//---------------------------------------------------
					// ������ �˻��� ��ġ�� �����Ѵ�.
					//---------------------------------------------------
					strFilteredPtr = pFind + lenCurse;

					existCurseEng = true;	// �� �ִ�.
				}
			}

			iString++;
		}

		//------------------------------------------------------------
		// ã�Ƴ� ��鿡 mask�� �����.
		//------------------------------------------------------------
		for (i=0; i<index; i++)
		{
			if ( isCurse[i] )
			{
				// ���̸�.. ���� string ��ġ�� mask�� �����.
				str[ indexFiltered[i] ] = s_MaskString[ i ];
			}
		}

	}

	
	//------------------------------------------------------------
	// �ѱ�1��, �ѱ�2��, �ѱ�3�� ...  ���� ����..
	// �����̳� Ư������ skip�ϸ� ������⵵ ���ŵȴ�.
	// (1) ���̿� ���� ������ �忡�� string�� ã�´�.
	//------------------------------------------------------------
	//     ���� ����� �������� �ȵ�~~
	// --> ���̹�����������ȵ�
	//	 ���� string�� index�� �������� �ٸ� ���ڷ� ġȯ�ϱⰡ ����.
	//
	//1����( ��, ��, ��, ��, ��, ��, ��, ��, ��, ��, �� )
	//2����( ����, �̹�, ����, ���, ����, ����, ����, ���, �ȵ� )
	//3����(���̹�, �̹���, �����, ����, �����, ������, ������, �����, ��ȵ�)
	//4����.... ���
	//
	// ��ȸ�� : O( stringLength * (log(1���ڿ��) + ... + log(n���ڿ��)) )
	//
	// ����) 40�� * (log(1000��)+log(1000��)+log(1000��)) = 40*30 = 120
	//
	//------------------------------------------------------------
	strFilteredPtr = strFiltered;
	indexFilteredPtr = indexFiltered;
	isCursePtr = isCurse;
	
	strOrg = str;	// üũ�� ���ؼ�..
	
	//------------------------------------------------------------
	// �ѱ۸� �ɷ�����.
	//------------------------------------------------------------
	i = 0;
	index = 0;
	while (ch = *strOrg++)//, ch != '\0')
	{
		//----------------------------------------------
		// �ѱ��� ���..
		//----------------------------------------------
		if (ch & 0x80)
		{
			char chNext = *strOrg++;

			//----------------------------------------------
			// 2 byte�̹Ƿ�.. ���� byte�� üũ�Ѵ�.
			//----------------------------------------------
			if (chNext=='\0')
			{
				// ���� �� byte�� ���� ���
				break;
			}
			
			//----------------------------------------------
			// �������� �ѱ� ����(2bytes)�� �ִ� ���
			//----------------------------------------------
			*strFilteredPtr++	= ch;
			*indexFilteredPtr++ = i++;
			*isCursePtr++		= false;	// �ʱ�ȭ

			*strFilteredPtr++	= chNext;
			*indexFilteredPtr++ = i;
			*isCursePtr++		= false;	// �ʱ�ȭ

			index+=2;
		}		
	
		//----------------------------------------------
		// �ٸ� ���� ���õǴ� �����̴�.
		//----------------------------------------------

		i++;
	}
	*strFilteredPtr = '\0';

	//------------------------------------------------------------
	// ���ڼ��� ����.. �ѱۿ��� �����Ѵ�.
	//------------------------------------------------------------
	if (RemoveCurseKorean(strFiltered, 2, m_mapCurseKor1, isCurse))
	{
		existCurseKor = true;	// �� �ִ�.
	}

	if (RemoveCurseKorean(strFiltered, 4, m_mapCurseKor2, isCurse))
	{
		existCurseKor = true;	// �� �ִ�.
	}

	if (RemoveCurseKorean(strFiltered, 6, m_mapCurseKor3, isCurse))
	{
		existCurseKor = true;	// �� �ִ�.
	}

	if (RemoveCurseKorean(strFiltered, 8, m_mapCurseKor4, isCurse))
	{
		existCurseKor = true;	// �� �ִ�.
	}

	//------------------------------------------------------------
	// �ѱ� ���� �ִٸ�..
	//------------------------------------------------------------
	if (existCurseKor)
	{
		//------------------------------------------------------------
		// ã�Ƴ� ��鿡 mask�� �����.
		//------------------------------------------------------------
		
		for (i=0; i<index; i++)
		{
			if ( isCurse[i] )
			{
				// 2004, 10, 26, sobeit modify start - ������ ����
				
#ifdef __GAME_CLIENT__
				int j = 0;
				switch(isCurse[i])
				{
				case 2:
					{
						char* pChangeString = (*g_pGameStringTable)[UI_STRING_MESSAGE_REMOVE_CURSE_1].GetString();
						for(j = 0; j<(*g_pGameStringTable)[UI_STRING_MESSAGE_REMOVE_CURSE_1].GetLength() ; j++)
						{
							if( (i+j) < len && indexFiltered[i+j] < len && indexFiltered[i+j]>-1)
								str[ indexFiltered[i+j] ] = pChangeString[j];
						}
					}
					i+= 1;
					break;
				case 4:
					{
						char* pChangeString = (*g_pGameStringTable)[UI_STRING_MESSAGE_REMOVE_CURSE_2].GetString();
						for(j = 0; j<(*g_pGameStringTable)[UI_STRING_MESSAGE_REMOVE_CURSE_2].GetLength() ; j++)
						{
							if( (i+j) < len && indexFiltered[i+j] < len && indexFiltered[i+j]>-1)
								str[ indexFiltered[i+j] ] = pChangeString[j];
						}
					}
					i+= 3;
					break;
				case 6:
					{
						char* pChangeString = (*g_pGameStringTable)[UI_STRING_MESSAGE_REMOVE_CURSE_3].GetString();
						for(j = 0; j<(*g_pGameStringTable)[UI_STRING_MESSAGE_REMOVE_CURSE_3].GetLength() ; j++)
						{
							if( (i+j) < len && indexFiltered[i+j] < len && indexFiltered[i+j]>-1)
								str[ indexFiltered[i+j] ] = pChangeString[j];
						}
					}
					i+= 5;
					break;
				case 8:
					{
						char* pChangeString = (*g_pGameStringTable)[UI_STRING_MESSAGE_REMOVE_CURSE_4].GetString();
						for(j = 0; j<(*g_pGameStringTable)[UI_STRING_MESSAGE_REMOVE_CURSE_4].GetLength() ; j++)
						{
							if( (i+j) < len && indexFiltered[i+j] < len && indexFiltered[i+j]>-1)
								str[ indexFiltered[i+j] ] = pChangeString[j];
						}
					}
					i+= 7;
					break;
				default:
					str[ indexFiltered[i] ] = s_MaskString[ i ];
					break;
				}
#else
				// ���̸�.. ���� string ��ġ�� mask�� �����.
				str[ indexFiltered[i] ] = s_MaskString[ i ];
#endif

				// 2004, 10, 26, sobeit modify end - ������ ����
			}
		}
	}

	delete [] strFiltered;
	delete [] indexFiltered;
	delete [] isCurse;	

	//------------------------------------------------------------
	// ������̳� �ѱۿ��� �ִٸ�...
	//------------------------------------------------------------
	if (existCurseEng || existCurseKor)
	{
		return true;
	}

	return false;
}

//----------------------------------------------------------------------
// RemoveCurseKorean
//----------------------------------------------------------------------
// strKor	: �ѱ۸� ����ִ� string(����,Ư������,����,�����ѱ�.. ���� ����!)
// lenCurse : �˻��Ϸ��� ���� ������ ���� byte��(�ѱ��̹Ƿ� 2�� ������� �Ѵ�)
// mapCurse : ����� ����ִ� MStringMap. ���� ������ ��鸸 �ִ�.
// isCurse	: ���� �ִ� ��ġ�� ����
//----------------------------------------------------------------------
// --> ���̹�����������ȵ�
//1����( ��, ��, ��, ��, ��, ��, ��, ��, ��, ��, �� )
//2����( ����, �̹�, ����, ���, ����, ����, ����, ���, �ȵ� )
//3����(���̹�, �̹���, �����, ����, �����, ������, ������, �����, ��ȵ�)
//----------------------------------------------------------------------
bool				
MChatManager::RemoveCurseKorean(const char* strKor, 
								int byteCurse, const MStringMap& mapCurse, 
								BYTE* isCurse) const
{
	int len = strlen(strKor);

	//---------------------------------------------------------
	// string ���̰� ª�� ���
	//---------------------------------------------------------
	if (len < byteCurse)
	{
		return false;
	}

	bool existCurse = false;

	//---------------------------------------------------------
	// üũ�ϸ鼭 NULL�� ��� ������.. copy�ؼ� ����Ѵ�.
	//---------------------------------------------------------
	char* strCheck = new char [len+1];
	strcpy( strCheck, strKor );
	
	char* strCheckPtr = strCheck;
	
	int maxCheck = len - (byteCurse-2);

	for (int i=0; i<maxCheck; i+=2)
	{
		//---------------------------------------------------------
		// �ʿ��� �κб��� üũ�ϱ� ���ؼ� NULL�� ��´�.
		//---------------------------------------------------------
		char* strCheckNull = strCheckPtr + byteCurse;
		char previousNull = *strCheckNull;
		*strCheckNull = '\0';

		//---------------------------------------------------------
		// ������ �ܾ ��map�� �ִ��� ã�ƺ���.
		//---------------------------------------------------------
		MStringMap::const_iterator iString = mapCurse.find( &MString(strCheckPtr) );

		//---------------------------------------------------------
		// ���� ��� (���� ���ϱ�? - -;)
		//---------------------------------------------------------
		if (iString != mapCurse.end())
		{
			// �� ���̸�ŭ.. ���̶�� üũ�صд�.
			// 2004, 10, 26, sobeit modify start - ������ ����
			//memset( isCurse+(strCheckPtr-strCheck), true, byteCurse);
			memset( isCurse+(strCheckPtr-strCheck), byteCurse, byteCurse);
			// 2004, 10, 26, sobeit modify end - ������ ����

			existCurse = true;
		}		
	
		//---------------------------------------------------------
		// NULL�� �ص� �κ��� ������� ������.
		//---------------------------------------------------------
		*strCheckNull = previousNull;

		strCheckPtr += 2;
	}

	delete [] strCheck;

	return existCurse;
}

//----------------------------------------------------------------------
// Add Mask
//----------------------------------------------------------------------
// str�� ���������� percent�� Ȯ���� mask�� �����.
// �ϴ�, s_MaskString2�� ����Ѵ�. - -;
// percent�� 0~100 
// 0�̸� �� ����ũ�ǰ�, 100�̸� �ϳ��� ����ũ���� �ʴ´�.
//----------------------------------------------------------------------
void
MChatManager::AddMask(char* str, int percent) const
{
#ifdef OUTPUT_DEBUG
	percent = max( percent, 75 );
#endif

	if (percent >= 100)
	{
		return;
	}

	char ch;

	// 0 ~ 100 --> 0 ~ 63
	int pro = percent * 63 / 100;
	
	int index = rand() & 0x0F;

	while (ch = *str, ch != NULL)
	{
		int maskLen = 0;

		//-------------------------------------------------------
		// ������ ���� �����Ѵ�.
		//-------------------------------------------------------
		if (ch==' ')
		{			
		}
		//-------------------------------------------------------
		// �ѱ��� ���
		//-------------------------------------------------------
		else if (ch & 0x80)
		{
			maskLen = 2;			
		}
		//-------------------------------------------------------
		// �� ����.
		//-------------------------------------------------------
		else 
		{
			maskLen = 1;
		}		

		//-------------------------------------------------------
		// Mask�ұ�?
		//-------------------------------------------------------
		if (maskLen!=0)
		{
			int bMask = (rand() & 0x3F) >= pro;	// ����~

			if (bMask)
			{
				for (int i=0; i<maskLen; i++)
				{
					if (*str != NULL)
					{			
						*str = s_MaskString2[index++];
						str++;
					}					
				}
			}
			else
			{
				str += maskLen;
			}
		}
		else
		{
			str++;
		}
	}	
}
