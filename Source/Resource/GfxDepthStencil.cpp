



#include "stdafx.h"

#include "GfxDepthStencil.h"



namespace 
{






}




namespace GfxLib
{


DepthStencil::DepthStencil()
	:m_pD3DDevice( NULL )
	,m_pDepthStencil( NULL )
	,m_pShaderResView( NULL )
	,m_pDepthTexture( NULL )
{

}


DepthStencil::~DepthStencil()
{

	Finalize();
}



BOOL	DepthStencil::Initialize( ID3D11Device* pDevice , UINT width , UINT height , DXGI_FORMAT format  )
{
	Finalize();


	m_pD3DDevice = pDevice;
	HRESULT hr = E_FAIL;



	// Create depth stencil texture
	D3D11_TEXTURE2D_DESC descDepth;
	ZeroMemory( &descDepth, sizeof(descDepth) );
	descDepth.Width = width;
	descDepth.Height = height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = format;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;

	//	ShaderResourceViewとしてはBindしない
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL ;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	hr = m_pD3DDevice->CreateTexture2D( &descDepth, NULL, m_pDepthTexture.InitialAccept() );
	if( FAILED( hr ) )
	{
		Finalize();
		return FALSE;
	}

	// Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory( &descDSV, sizeof(descDSV) );
	descDSV.Format = format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	hr = m_pD3DDevice->CreateDepthStencilView( m_pDepthTexture, &descDSV, m_pDepthStencil.InitialAccept() );
	if( FAILED( hr ) )
	{
		Finalize();
		return FALSE;
	}




	return SUCCEEDED( hr );
}



/*

	ShaderResourceViewとしても使える形で初期化する

	depthFormat: 深度バッファフォーマット

*/
#if 0
BOOL	DepthStencil::InitializeShaderResourceView( ID3D11Device* pDevice , UINT width , UINT height , DXGI_FORMAT depthFormat )
{
	Finalize();

	m_pD3DDevice = pDevice;
	HRESULT hr = E_FAIL;


	DXGI_FORMAT BufferFormat;
	DXGI_FORMAT SRVFormat;

	switch( depthFormat )
	{
	case DXGI_FORMAT_D24_UNORM_S8_UINT:
		BufferFormat = DXGI_FORMAT_R24G8_TYPELESS;
		SRVFormat = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
		break;
	case DXGI_FORMAT_D16_UNORM:
		BufferFormat = DXGI_FORMAT_R16_TYPELESS;
		SRVFormat = DXGI_FORMAT_R16_UNORM;
		break;
	case DXGI_FORMAT_D32_FLOAT:
		BufferFormat = DXGI_FORMAT_R32_TYPELESS;
		SRVFormat = DXGI_FORMAT_R32_FLOAT;
		break;
	default:
		GFX_ASSERT( 0 , "Unsupported Depth Format!" );
		return FALSE;
	}
	

	// Create depth stencil texture
	D3D11_TEXTURE2D_DESC descDepth;
	ZeroMemory( &descDepth, sizeof(descDepth) );
	descDepth.Width = width;
	descDepth.Height = height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	//descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.Format = BufferFormat;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	//descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	hr = m_pD3DDevice->CreateTexture2D( &descDepth, NULL, m_pDepthTexture.InitialAccept() );
	if( FAILED( hr ) )
	{
		Finalize();
		return FALSE;
	}

	// Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory( &descDSV, sizeof(descDSV) );
	descDSV.Format = depthFormat;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	hr = m_pD3DDevice->CreateDepthStencilView( m_pDepthTexture, &descDSV, m_pDepthStencil.InitialAccept() );
	if( FAILED( hr ) )
	{
		Finalize();
		return FALSE;
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC descSRV;
	ZeroMemory( &descSRV , sizeof( descSRV ) );

	descSRV.Format = SRVFormat;
	descSRV.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	descSRV.Texture2D.MipLevels = 1;
	descSRV.Texture2D.MostDetailedMip = 0;

	hr  = m_pD3DDevice->CreateShaderResourceView( m_pDepthTexture , &descSRV , m_pShaderResView.InitialAccept() );

	if ( FAILED( hr ) )
	{
		Finalize();
		return FALSE;
	}

	return SUCCEEDED( hr );
}
#endif



/*

	Texture2Dリソースから深度ステンシルを作成する

*/
BOOL	DepthStencil::InitializeTexture2D( ID3D11Device* pDevice , ID3D11Texture2D* pTexture ,DXGI_FORMAT format , UINT mipSlice )
{

	Finalize();

	D3D11_DEPTH_STENCIL_VIEW_DESC desc;
	ZeroMemory( &desc , sizeof( desc ) );
	desc.Format = format;
	desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	desc.Texture2D.MipSlice = mipSlice;


	HRESULT hr = pDevice->CreateDepthStencilView( pTexture , &desc , m_pDepthStencil.InitialAccept() );

	if ( FAILED( hr ) )
	{
		GFX_ASSERT( 0 , "Create DepthStencilView Failed" );
		Finalize();

		return FALSE;
	}

	m_pD3DDevice = pDevice;

	return TRUE;

}



void	DepthStencil::Finalize()
{
	m_pD3DDevice = NULL;
	m_pDepthStencil = NULL;
	m_pShaderResView = NULL;
	m_pDepthTexture = NULL;
}


}

