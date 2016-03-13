


#include "stdafx.h"

#include "GfxPixelShader.h"





namespace GfxLib
{

	PixelShader::PixelShader(  )
		:Shader(  )
		,m_pPixelShader( NULL )
	{


	}
	PixelShader::~PixelShader()
	{
		GFX_RELEASE( m_pPixelShader );
	}

	BOOL PixelShader::CreateFromFile( ID3D11Device * dev , const wchar_t* fileName , LPCSTR entryPoint )
	{
		Finalize();

		m_pd3dDev = dev;


		ID3DBlob *blob = NULL;

		HRESULT hr = CompileShaderFromFile( fileName , entryPoint , "ps_5_0" , &blob );

		if ( FAILED( hr ) )
		{
			GFX_RELEASE(blob);
			return FALSE;
		}


		m_pd3dDev->CreatePixelShader( blob->GetBufferPointer() , blob->GetBufferSize() , NULL , &m_pPixelShader );

		if ( FAILED( hr ) )
		{
			GFX_RELEASE(blob);
			return FALSE;
		}

		GFX_RELEASE(blob);

		return TRUE;


	}

	void	PixelShader::Finalize()
	{
		GFX_RELEASE( m_pPixelShader );
	}


}

