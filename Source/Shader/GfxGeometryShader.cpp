


#include "stdafx.h"

#include "GfxGeometryShader.h"





namespace GfxLib
{

	GeometryShader::GeometryShader(  )
		:Shader(  )
		,m_pGeomShader( NULL )
	{


	}
	GeometryShader::~GeometryShader()
	{
		GFX_RELEASE( m_pGeomShader );
	}



	/*

		ファイルを読み込み、ジオメトリシェーダの初期化を行う


	*/
	BOOL GeometryShader::CreateFromFile( ID3D11Device * dev , const wchar_t* fileName , LPCSTR entryPoint )
	{
		Finalize();

		m_pd3dDev = dev;


		ID3DBlob *blob = NULL;

		HRESULT hr = CompileShaderFromFile( fileName , entryPoint , "gs_5_0" , &blob );

		if ( FAILED( hr ) )
		{
			GFX_RELEASE(blob);
			return FALSE;
		}


		m_pd3dDev->CreateGeometryShader( blob->GetBufferPointer() , blob->GetBufferSize() , NULL , &m_pGeomShader );

		if ( FAILED( hr ) )
		{
			GFX_RELEASE(blob);
			return FALSE;
		}

		GFX_RELEASE(blob);

		return TRUE;


	}

	void	GeometryShader::Finalize()
	{
		GFX_RELEASE( m_pGeomShader );
	}


}

