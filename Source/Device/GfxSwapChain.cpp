


#include "stdafx.h"


#include "GfxSwapChain.h"

namespace
{
	UINT BufferCount = 2;
	DXGI_FORMAT BufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;

}


namespace GfxLib
{



SwapChain::SwapChain()
{

}



SwapChain::~SwapChain()
{
	Finalize();
}


BOOL	SwapChain::Initialize( ID3D11Device* dev,  HWND  hwnd )
{
	Finalize();


	m_pd3dDev = dev;
	
	RECT rc;
	GetClientRect( hwnd, &rc );
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;


	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory( &sd, sizeof( sd ) );
	sd.BufferCount = BufferCount;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = BufferFormat;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hwnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD ;
	sd.Flags = 0 ;


	IDXGIDevice * pDXGIDevice = NULL; 
	HRESULT hr = m_pd3dDev->QueryInterface(__uuidof(IDXGIDevice), (void **)&pDXGIDevice);
	IDXGIAdapter * pDXGIAdapter = NULL;
	hr = pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void **)&pDXGIAdapter); 
	IDXGIFactory * pIDXGIFactory = NULL;
	pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void **)&pIDXGIFactory);       


	hr=	pIDXGIFactory->CreateSwapChain( m_pd3dDev , &sd , m_pSwapChain.InitialAccept() );

	pDXGIDevice->Release();
	pDXGIAdapter->Release();
	pIDXGIFactory->Release();


	if ( FAILED( hr ) )
		return FALSE;


	// Create a render target view
	ID3D11Texture2D* pBackBuffer = NULL;
	hr = m_pSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&pBackBuffer );
	if ( SUCCEEDED( hr ) )
	{

		hr = m_pd3dDev->CreateRenderTargetView( pBackBuffer, NULL, m_pRenderTargetView.InitialAccept() );
		m_RenderTarget.InitializeAttach( m_pd3dDev , pBackBuffer , m_pRenderTargetView );
		pBackBuffer->Release();
	}


	return TRUE;


}



void	SwapChain::Finalize()
{

	m_pSwapChain = NULL;
	m_pd3dDev = NULL;
	m_pRenderTargetView = NULL;;
	m_RenderTarget.Finalize();

}




BOOL	SwapChain::Resize( UINT width , UINT height )
{

	if ( !m_pSwapChain )
	{
		return FALSE;
	}


	//GFX_RELEASE( m_pRenderTargetView );
	m_pRenderTargetView = NULL;
	m_RenderTarget.Finalize();

	m_pSwapChain->ResizeBuffers( BufferCount , width , height , BufferFormat , 0 );


	ID3D11Texture2D* pBackBuffer = NULL;
	HRESULT hr = m_pSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&pBackBuffer );
	if ( SUCCEEDED( hr ) )
	{
		hr = m_pd3dDev->CreateRenderTargetView( pBackBuffer, NULL, m_pRenderTargetView.InitialAccept() );
		m_RenderTarget.InitializeAttach( m_pd3dDev , pBackBuffer , m_pRenderTargetView );
		pBackBuffer->Release();
	}


	return TRUE;

}


BOOL	SwapChain::Present(
	UINT SyncInterval,
	UINT Flags
	)
{

	return SUCCEEDED( m_pSwapChain->Present( SyncInterval , Flags ) );

}



}
