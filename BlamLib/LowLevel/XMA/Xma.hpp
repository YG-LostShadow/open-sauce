/*
	Based on "xma_parse" code written by HCS (http://hcs64.com/contact.html)
	Permission pending response.
*/
#pragma once

__CPP_CODE_START__
//#ifndef LOWLEVEL_NO_X360
#pragma comment (lib, "C:\\Program Files (x86)\\Microsoft Xbox 360 SDK\\lib\\win32\\vs2008\\xmaencoder.lib")

// Define some xmaencoder.lib extern objects that we need for decoding...
class CXMATarget
{
	PAD32; PAD32;
public:
	virtual HRESULT __stdcall DecodeWave(LPCWSTR xma_file, LPCWSTR pcm_file);
	virtual HRESULT __stdcall EncodeWave(); // I'm not going to sit here and defe the params, frig off Randy
	virtual ~CXMATarget();
}; BOOST_STATIC_ASSERT( sizeof(CXMATarget) == 0xC );

extern "C"
{
	CXMATarget* CreateXMATarget(CXMATarget*& out_obj);
	void FreeXMATarget(CXMATarget* obj);
};
//#endif
__CPP_CODE_END__

__MCPP_CODE_START__

namespace LowLevel { namespace Xma {

	public mcpp_struct RebuildParameters
	{
		mcpp_uint Offset;
		mcpp_uint BlockSize;
		mcpp_int Channels;
		mcpp_int Version;

		mcpp_bool Strict;
		mcpp_bool IgnorePacketSkip;
	};

	public mcpp_class Interface
	{
	mcpp_public
		static mcpp_readonly array<mcpp_byte>^ kMonoFooter = mcpp_new array<mcpp_byte> {
			0x58, 0x4D, 0x41, 0x32, 0x2C, 0x00, 0x00, 0x00, 0x04, 
			0x01, 0x00, 0xFF, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 
			0x8A, 0x00, 0x00, 0x00, 0xAB, 0xD2, 0x00, 0x00, 0x10, 
			0xD6, 0x00, 0x00, 0x3D, 0x14, 0x00, 0x01, 0x00, 0x00, 
			0x00, 0x00, 0x8A, 0x00, 0x00, 0x00, 0x88, 0x80, 0x00, 
			0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x73, 0x65, 
			0x65, 0x6B, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8A, 
			0x00
		};
		static mcpp_readonly array<mcpp_byte>^ kStereoFooter = mcpp_new array<mcpp_byte> {
			0x58, 0x4D, 0x41, 0x32, 0x2C, 0x00, 0x00, 0x00, 0x04, 
			0x01, 0x00, 0xFF, 0x00, 0x00, 0x01, 0x80, 0x00, 0x01, 
			0x0F, 0x80, 0x00, 0x00, 0xAC, 0x44, 0x00, 0x00, 0x10, 
			0xD6, 0x00, 0x00, 0x3D, 0x14, 0x00, 0x01, 0x00, 0x00, 
			0x00, 0x01, 0x10, 0x00, 0x00, 0x01, 0x0E, 0x00, 0x00, 
			0x00, 0x00, 0x01, 0x02, 0x00, 0x02, 0x01, 0x73, 0x65, 
			0x65, 0x6B, 0x04, 0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 
			0x00
		};

		static mcpp_bool Decode(mcpp_string^ xma_file, mcpp_string^ pcm_file);
		static array<mcpp_byte>^ Rebuild(array<mcpp_byte>^ buffer, RebuildParameters params);
		static bool Rebuild(mcpp_string^ in_file, mcpp_string^ out_file, mcpp_string^ rebuild_file, 
			RebuildParameters params);
	};

}; };

__MCPP_CODE_END__