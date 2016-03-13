#pragma once
#include <Util\GfxD3DPtr.h>



namespace GfxLib
{
	class Shader
	{
	public:
		~Shader();

	protected:
		Shader();



		HRESULT CompileShaderFromFile( const wchar_t* filePath , LPCSTR entryPoint ,
			 LPCSTR shaderModel , ID3DBlob** ppBlobOut );



	protected:


		D3DPtr< ID3D11Device > m_pd3dDev;



	};
}