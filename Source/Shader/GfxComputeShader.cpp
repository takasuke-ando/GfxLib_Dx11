


#include "stdafx.h"
#include "GfxComputeShader.h"


namespace GfxLib
{


ComputeShader::ComputeShader()
{

}



ComputeShader::~ComputeShader()
{


}



BOOL	ComputeShader::CreateFromFile( ID3D11Device * dev ,const wchar_t* fileName , LPCSTR entryPoint )
{
	Finalize();



	ID3DBlob *blob = NULL;

	HRESULT hr = CompileShaderFromFile( fileName , entryPoint , "cs_5_0" , &blob );

	if ( FAILED( hr ) )
	{
		GFX_RELEASE(blob);
		return FALSE;
	}

	m_pd3dDev = dev;
	m_pd3dDev->CreateComputeShader( blob->GetBufferPointer() , blob->GetBufferSize() , NULL , m_pComputeShader.InitialAccept() );

	if ( FAILED( hr ) )
	{
		GFX_RELEASE(blob);
		return FALSE;
	}

	GFX_RELEASE(blob);

	return TRUE;


}



void	ComputeShader::Finalize()
{

	m_pd3dDev = NULL;
	m_pComputeShader = NULL;

}



}