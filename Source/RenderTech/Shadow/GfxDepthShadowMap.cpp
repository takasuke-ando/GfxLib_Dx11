/*

	GfxDepthShadowMap

	シャドウマップリソースをカプセル化する
	このクラスはシンプルな深度シャドウマップを保持する


*/


#include "stdafx.h"

#include "GfxDepthShadowMap.h"



namespace GfxLib
{


DepthShadowMap::DepthShadowMap()
{

}



DepthShadowMap::~DepthShadowMap()
{
	Finalize();
}



BOOL		DepthShadowMap::Initialize( ID3D11Device *pDev , UINT width , UINT height , DXGI_FORMAT depthFormat /* = DXGI_FORMAT_D24 */ )
{
	Finalize();


	DXGI_FORMAT	buffFormat = DXGI_FORMAT_UNKNOWN;
	DXGI_FORMAT srvFormat = DXGI_FORMAT_UNKNOWN;

	switch( depthFormat )
	{
	case DXGI_FORMAT_D24_UNORM_S8_UINT:
		buffFormat = DXGI_FORMAT_R24G8_TYPELESS;
		srvFormat = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
		break;
	case DXGI_FORMAT_D32_FLOAT:
		buffFormat = DXGI_FORMAT_R32_TYPELESS;
		srvFormat = DXGI_FORMAT_R32_FLOAT;
		break;
	case DXGI_FORMAT_D16_UNORM:
		buffFormat = DXGI_FORMAT_R16_TYPELESS;
		srvFormat = DXGI_FORMAT_R16_UNORM;
		break;
	default:
		GFX_ASSERT( 0 , "Unsupported Depth format" );
		return FALSE;
	}


	BOOL bOk = m_DepthTexture.Initialize( pDev , width , height , buffFormat , D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_DEPTH_STENCIL );

	if ( !bOk )
	{
		GFX_ASSERT( 0 , "Texture2D Initialize Failed" );
		return FALSE;
	}


	bOk = m_DepthSRV.InitializeTexture2D( pDev , m_DepthTexture , srvFormat );

	if ( !bOk )
	{
		GFX_ASSERT( 0 , "ShaderResourceView Initialize Failed" );
		return FALSE;
	}


	//	Initialize ok!


	return TRUE;

}





void		DepthShadowMap::Finalize()
{

	m_DepthStencil.Finalize();
	m_DepthSRV.Finalize();
	m_DepthTexture.Finalize();

}




}



