


#include "stdafx.h"


#include "GfxRenderTarget.h"



namespace GfxLib
{



	RenderTarget::RenderTarget()
		:m_pD3DDevice(NULL)
		,m_pRenderTarget(NULL)
		,m_pRenderTargetTexture(NULL)
		,m_pShaderResView( NULL )
	{



	}


	RenderTarget::~RenderTarget()
	{

		Finalize();

	}

	BOOL	RenderTarget::Initialize( ID3D11Device* pDevice , UINT width , UINT height , DXGI_FORMAT format )
	{
		Finalize();

		m_pD3DDevice = pDevice;

		// Create render Target texture
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
		descDepth.BindFlags = D3D11_BIND_RENDER_TARGET;
		descDepth.CPUAccessFlags = 0;
		descDepth.MiscFlags = 0;
		HRESULT hr = m_pD3DDevice->CreateTexture2D( &descDepth, NULL, m_pRenderTargetTexture.InitialAccept() );
		if( FAILED( hr ) )
		{
			Finalize();
			return FALSE;
		}


		// Create the depth stencil view
		D3D11_RENDER_TARGET_VIEW_DESC descRTV;
		ZeroMemory( &descRTV, sizeof(descRTV) );
		descRTV.Format = format;
		descRTV.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		descRTV.Texture2D.MipSlice = 0;
		hr = m_pD3DDevice->CreateRenderTargetView( m_pRenderTargetTexture, &descRTV, m_pRenderTarget.InitialAccept() );
		if( FAILED( hr ) )
		{
			Finalize();
			return FALSE;
		}


		return TRUE;

	}



	/*

		シェーダーリソースビューにアクセス可能な形で初期化する

	*/
	BOOL	RenderTarget::InitializeShaderResourceView( ID3D11Device* pDevice , UINT width , UINT height , DXGI_FORMAT format )
	{
		Finalize();


		m_pD3DDevice = pDevice;


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

		//	ShaderResourceViewとしてはBindする
		descDepth.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		descDepth.CPUAccessFlags = 0;
		descDepth.MiscFlags = 0;
		HRESULT hr = m_pD3DDevice->CreateTexture2D( &descDepth, NULL, m_pRenderTargetTexture.InitialAccept() );
		if( FAILED( hr ) )
		{
			Finalize();
			return FALSE;
		}

	
		// Create the depth stencil view
		D3D11_RENDER_TARGET_VIEW_DESC descRTV;
		ZeroMemory( &descRTV, sizeof(descRTV) );
		descRTV.Format = format;
		descRTV.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		descRTV.Texture2D.MipSlice = 0;
		hr = m_pD3DDevice->CreateRenderTargetView( m_pRenderTargetTexture, &descRTV, m_pRenderTarget.InitialAccept() );
		if( FAILED( hr ) )
		{
			Finalize();
			return FALSE;
		}


		D3D11_SHADER_RESOURCE_VIEW_DESC descSRV;
		ZeroMemory( &descSRV , sizeof( descSRV ) );

		descSRV.Format = format;
		descSRV.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		descSRV.Texture2D.MipLevels = 1;
		descSRV.Texture2D.MostDetailedMip = 0;

		hr  = m_pD3DDevice->CreateShaderResourceView( m_pRenderTargetTexture , &descSRV , m_pShaderResView.InitialAccept() );

		if ( FAILED( hr ) )
		{
			Finalize();
			return FALSE;
		}



		return TRUE;
	}


	BOOL	RenderTarget::InitializeAttach(
		ID3D11Device* pDevice , 
		ID3D11Texture2D* ptexture ,
		ID3D11RenderTargetView* rtv )
	{
		Finalize();

		m_pD3DDevice = pDevice;

		m_pRenderTarget			= rtv;
		m_pRenderTargetTexture = ptexture;



		return FALSE;
	}


	BOOL	RenderTarget::InitializeTexture2D( ID3D11Device* pDevice , ID3D11Texture2D* pTexture ,DXGI_FORMAT format, UINT mipSlice )
	{
		Finalize();

		D3D11_RENDER_TARGET_VIEW_DESC desc;
		ZeroMemory( &desc , sizeof( desc ) );
		desc.Format = format;
		desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MipSlice = mipSlice;


		HRESULT hr = pDevice->CreateRenderTargetView( pTexture , &desc , m_pRenderTarget.InitialAccept() );

		if ( FAILED( hr ) )
		{
			GFX_ASSERT( 0 , "Create RenderTargetView Failed" );
			Finalize();

			return FALSE;
		}

		m_pD3DDevice = pDevice;

		return TRUE;
	}



	void	RenderTarget::Finalize()
	{

		m_pD3DDevice = NULL;
		m_pRenderTarget = NULL;
		m_pRenderTargetTexture = NULL;

		m_pShaderResView = NULL;
	}

















}




