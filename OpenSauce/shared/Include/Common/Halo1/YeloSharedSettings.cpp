/*
    Yelo: Open Sauce SDK

    Copyright (C) 2005-2010  Kornner Studios (http://kornner.com)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "Common/Precompile.hpp"
#include <Common/Halo1/YeloSharedSettings.hpp>

#include <direct.h>
#include <share.h>

namespace Yelo
{
	namespace Settings
	{
		static struct {
			char UserProfilePath[MAX_PATH];
			char OpenSauceProfilePath[MAX_PATH];
			char ReportsPath[MAX_PATH];
			char WorkingDirectoryPath[MAX_PATH];
		}Internal;

		cstring UserProfilePath()		{ return Internal.UserProfilePath; }
		cstring OpenSauceProfilePath()	{ return Internal.OpenSauceProfilePath; }
		cstring ReportsPath()			{ return Internal.ReportsPath; }
		cstring WorkingDirectoryPath()	{ return Internal.WorkingDirectoryPath; }

		void SharedInitialize(cstring profile_path)
		{
			if(profile_path[0] == '\0')
			{
				SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, 0, Internal.UserProfilePath);
				PathAppendA(Internal.UserProfilePath, "My Games\\Halo CE\\");
				profile_path = Internal.UserProfilePath;
			}
			else strcpy_s(Internal.UserProfilePath, profile_path);

			strcpy_s(Internal.OpenSauceProfilePath, profile_path);
			PathAppendA(Internal.OpenSauceProfilePath, "OpenSauce\\");
			_mkdir(Internal.OpenSauceProfilePath); // make the OpenSauce subdirectory

			strcpy_s(Internal.ReportsPath, Internal.OpenSauceProfilePath);
			PathAppendA(Internal.ReportsPath, "Reports\\");
			_mkdir(Internal.ReportsPath);

			_getcwd(Internal.WorkingDirectoryPath, MAX_PATH);
		}

		void SharedDispose()
		{
		}

		//////////////////////////////////////////////////////////////////////////

		bool GetSettingsFilePath(cstring filename, __out char file_path[MAX_PATH])
		{
			sprintf_s(file_path, MAX_PATH, "%s%s", Internal.OpenSauceProfilePath, filename);

			return PathFileExistsA(file_path) > 0;
		}

		FILE* CreateReport(cstring filename, bool append, bool text, bool shared)
		{
			char path[MAX_PATH];
			memset(path, 0, sizeof(path));

			strcpy_s(path, ReportsPath());
			strcat_s(path, filename);

			cstring mode;
			if(text)mode = append ? "at" : "wt";
			else	mode = append ? "ab" : "wb";

			FILE* ret = NULL;
			if(!shared)
				fopen_s(&ret, path, mode);
			else
				return _fsopen(filename, mode, _SH_DENYNO);

			return ret;
		}

		FILE* CreateUnicodeReport(wcstring filename, bool append, bool shared)
		{
			wchar_t path[MAX_PATH];
			memset(path, 0, sizeof(path));

			string_to_wstring(path, NUMBEROF(path), ReportsPath());
			wcscat_s(path, filename);

			wcstring mode = append ? L"at,ccs=UNICODE" : L"wt,ccs=UNICODE";

			FILE* ret = NULL;
			if(!shared)
				_wfopen_s(&ret, path, mode);
			else
				return _wfsopen(path, mode, _SH_DENYNO);

			return ret;
		}

		FILE* OpenSettings(cstring filename, bool text, bool open_for_writing)
		{
			char path[MAX_PATH];
			memset(path, 0, sizeof(path));

			strcpy_s(path, Internal.OpenSauceProfilePath);
			strcat_s(path, filename);

			cstring mode;
			if(open_for_writing)mode = text ? "wt" : "wb";
			else				mode = text ? "rt" : "rb";

			FILE* ret = NULL;
			fopen_s(&ret, path, mode);

			return ret;
		}


		TiXmlElement* GenericSettingsParse(TiXmlDocument& doc, char file_path[MAX_PATH], cstring branch_name)
		{
			TiXmlElement* result = NULL;
			if(doc.LoadFile(file_path))
			{
				TiXmlElement* root_element = doc.RootElement();

				if(root_element != NULL)
				{
					cstring value = root_element->Attribute("engine");

					if(value != NULL && !strcmp(value, "Halo1_CE"))
						result = branch_name != NULL ?
							root_element->FirstChildElement(branch_name) : root_element;
				}
			}

			return result;
		}
		TiXmlElement* GenericSettingsWrite(TiXmlDocument& doc, cstring root_name, cstring branch_name)
		{
			TiXmlElement* result;

			TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "utf-8", "");
				doc.LinkEndChild(decl);

			TiXmlElement* root_element = new TiXmlElement(root_name);
				doc.LinkEndChild(root_element);

			root_element->SetAttribute("engine", "Halo1_CE");

			if(branch_name != NULL)
			{
				TiXmlElement* element = new TiXmlElement(branch_name);
					root_element->LinkEndChild(element);

				result = element;
			}
			else result = root_element;

			return result;
		}

		bool ParseBoolean(cstring str)
		{
			bool result = false;

			if(str != NULL)
			{
				if( !_stricmp(str, "false") |
					!_stricmp(str, "off") |
					!strcmp (str, "0") )
					result = false;
				else if(!_stricmp(str, "true") |
					!_stricmp(str, "on") | 
					!strcmp (str, "1") )
					result = true;
			}

			return result;
		}

		void XmlReadReal3D(const TiXmlElement* element, real* r3d, const bool is_vector)
		{
			r3d[0] = r3d[1] = r3d[2] = 0.0f;

			if(element != NULL)
			{
				element->QueryFloatAttribute(is_vector ? "i" : "x", 
					&r3d[0]);
				element->QueryFloatAttribute(is_vector ? "j" : "y", 
					&r3d[1]);
				element->QueryFloatAttribute(is_vector ? "k" : "z", 
					&r3d[2]);
			}
		}

		void XmlWriteReal3D(TiXmlElement* element, real* r3d, const bool is_vector)
		{
			element->SetDoubleAttribute(is_vector ? "i" : "x", r3d[0]);
			element->SetDoubleAttribute(is_vector ? "j" : "y", r3d[1]);
			element->SetDoubleAttribute(is_vector ? "k" : "d", r3d[2]);
		}
	};
};