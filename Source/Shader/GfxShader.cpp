

#include "stdafx.h"



#include "GfxShader.h"



namespace GfxLib
{




	Shader::Shader()
		:m_pd3dDev( NULL )
	{

	}



	Shader::~Shader()
	{

		m_pd3dDev = NULL;

	}
	
	HRESULT Shader::CompileShaderFromFile( 
		const wchar_t* szFileName ,
		LPCSTR szEntryPoint ,
		LPCSTR szShaderModel ,
		ID3DBlob** ppBlobOut )
	{

		HRESULT hr = S_OK;

		DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
		// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
		// Setting this flag improves the shader debugging experience, but still allows 
		// the shaders to be optimized and to run exactly the way they will run in 
		// the release configuration of this program.
		dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

		ID3DBlob* pErrorBlob;
#if 0
		hr = D3DX11CompileFromFileW( szFileName, NULL, NULL, szEntryPoint, szShaderModel, 
			dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL );
#endif
		hr = D3DCompileFromFile(szFileName, NULL, NULL, szEntryPoint, szShaderModel,
			dwShaderFlags, 0, ppBlobOut, &pErrorBlob);

		if( FAILED(hr) )
		{
			if( pErrorBlob != NULL )
				OutputDebugStringA( (char*)pErrorBlob->GetBufferPointer() );
			if( pErrorBlob ) pErrorBlob->Release();
			GFX_ASSERT( 0 , "Failed Compile Shader" );
			return hr;
		}
		if( pErrorBlob ) pErrorBlob->Release();

		return S_OK;
	
	}

}


