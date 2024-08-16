//----------------------------------------------------------------------
// ProfileManager.h
//----------------------------------------------------------------------
// ĳ���͵��� �� ������ �����Ѵ�.
//
// ������ �����Ǵ°�.. ĳ���� ȭ���� �ִ�/����/��û�ض�.. �����̰�,
// ���� ���.. ȭ�� �̸��� �о �ܺο��� ��~ ����ϸ� �ȴ�.
//
// ���α׷��� ����ɶ� �������� �� ���� �����̹Ƿ�.. ������ ���� �ʿ����.
//
//
// [ȭ�� ���� ���]
//
// ����ڰ� *.bmp�� profile�� �־�дٰ� �ϰ�..
// � ĳ���� profile�� �ʿ��ϸ� 'ĳ����.bmp'�� ������
// 'ĳ����.spr'�� �����ؼ� profile�� �־�ΰ�.. ����ϸ� �ȴ�.
//
// ���ﶧ�� spr�� �� ����� �ȴ�.
//
// Profile.Get(name)���� 
//     �� client�� name.spr�� ���ٸ�..
//        �ٸ� client�� ��û�� �ؾ��Ѵ�.
//
//----------------------------------------------------------------------

#ifndef __PROFILE_MANAGER_H__
#define __PROFILE_MANAGER_H__


#pragma warning(disable:4786)

#include <map>
#include <string>

//----------------------------------------------------------------------
// ProfileManager
//----------------------------------------------------------------------
class ProfileManager {
	public :
		enum HAS_PROFILE
		{

		};

	public :
		typedef std::map<std::string, std::string>		PROFILE_MAP;

		typedef std::map<std::string, int>				REQUIRE_MAP;
		
	public :
		ProfileManager();
		~ProfileManager();

		//-------------------------------------------------------------
		// Delete / Init Profiles - Profile ���丮 ����
		//-------------------------------------------------------------
		static void		DeleteProfiles();
		static void		InitProfiles();		

		//-------------------------------------------------------------
		// Release
		//-------------------------------------------------------------
		void				Release();		

		//-------------------------------------------------------------
		// Add / Remove Profile
		//-------------------------------------------------------------
		bool			HasProfile(const char* pName) const;
		void			RequestProfile(const char* pName);
		void			AddProfile(const char* pName, const char* pFilename);		
		bool			RemoveProfile(const char* pName);

		//-------------------------------------------------------------
		// ������ �ƿ� Profile�� ���� ���
		//-------------------------------------------------------------
		bool			HasProfileNULL(const char* pName) const;
		void			AddProfileNULL(const char* pName);

		//-------------------------------------------------------------
		// Get
		//-------------------------------------------------------------
		const char*		GetFilename(const char* pName) const;


		//-------------------------------------------------------------
		// Require
		//-------------------------------------------------------------
		void			AddRequire(const char* pName);
		bool			HasRequire(const char* pName) const;
		bool			RemoveRequire(const char* pName);
		void			ReleaseRequire();

		void			Update();
		
	protected :
		//----------------------------------------------------------------------
		// Lock / Unlock
		//----------------------------------------------------------------------
		void		Lock()					{ EnterCriticalSection(&m_Lock); }
		void		Unlock()				{ LeaveCriticalSection(&m_Lock); }

	private :
		PROFILE_MAP		m_Profiles;

		REQUIRE_MAP		m_Requires;

		CRITICAL_SECTION		m_Lock;
};

extern ProfileManager*		g_pProfileManager;


#endif



