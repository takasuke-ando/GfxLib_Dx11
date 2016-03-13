



#include "stdafx.h"



#include "GfxTeture2D.h"



namespace GfxLib
{


Texture2D::Texture2D()
{




}
Texture2D::~Texture2D()
{
	Finalize();
}


/*

	‰Šú‰»‚·‚é

*/
BOOL	Texture2D::Initialize( ID3D11Device* pDevice ,  UINT width , UINT height , DXGI_FORMAT format , UINT bindFlags)
{
	Finalize();


	// Create depth stencil texture
	D3D11_TEXTURE2D_DESC descTeture;
	ZeroMemory( &descTeture, sizeof(descTeture) );
	descTeture.Width = width;
	descTeture.Height = height;
	descTeture.MipLevels = 1;
	descTeture.ArraySize = 1;
	descTeture.Format = format;
	descTeture.SampleDesc.Count = 1;
	descTeture.SampleDesc.Quality = 0;
	descTeture.Usage = D3D11_USAGE_DEFAULT;

	descTeture.BindFlags = bindFlags;
	descTeture.CPUAccessFlags = 0;
	descTeture.MiscFlags = 0;
	HRESULT hr = pDevice->CreateTexture2D( &descTeture, NULL, m_pTexture.InitialAccept() );
	if( FAILED( hr ) )
	{
		GFX_ASSERT( 0 , "Texture Creation Failed" );
			
		Finalize();
		return FALSE;
	}


	m_pd3dDev = pDevice;


	return TRUE;


}


void	Texture2D::Finalize()
{

	m_pd3dDev = NULL;
	m_pTexture = NULL;

}




}






