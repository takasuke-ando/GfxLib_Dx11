


#include "Stdafx.h"
#include "GfxVertexShader.h"





namespace GfxLib
{

	VertexShader::VertexShader( )
		:Shader()
		,m_pVertexShader( NULL )
		,m_pShaderBlob( NULL )
	{


	}
	VertexShader::~VertexShader()
	{
		GFX_RELEASE(m_pVertexShader);
		GFX_RELEASE(m_pShaderBlob );
	}



	/*
		ƒtƒ@ƒCƒ‹‚©‚ç“Ç‚Ýž‚ñ‚Åì¬
	*/

	BOOL VertexShader::CreateFromFile(   ID3D11Device * dev , const wchar_t* fileName , LPCSTR entryPoint )
	{
		Finalize();

		m_pd3dDev = dev;

		ID3DBlob *blob = NULL;

		HRESULT hr = CompileShaderFromFile( fileName , entryPoint , "vs_5_0" , &blob );

		if ( FAILED( hr ) )
		{
			GFX_RELEASE( m_pShaderBlob );
				return FALSE;
		}


		m_pd3dDev->CreateVertexShader( blob->GetBufferPointer() , blob->GetBufferSize() , NULL , &m_pVertexShader );


		if ( FAILED( hr ) )
		{
			GFX_RELEASE( m_pShaderBlob );
			return FALSE;
		}

		m_pShaderBlob = blob;	//	release‚¹‚¸


		return TRUE;

	}


	void VertexShader::Finalize()
	{

		GFX_RELEASE( m_pVertexShader );
		GFX_RELEASE( m_pShaderBlob );

	}

}

