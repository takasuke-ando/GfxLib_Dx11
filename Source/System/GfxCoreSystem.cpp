


#include "stdafx.h"

#include "GfxCoreSystem.h"

//test
//#include <d3d11_1.h>


namespace GfxLib
{



CoreSystem::CoreSystem()
	:m_pd3dDev( NULL )
	,m_pImmedisateContext( NULL )
	,m_featureLevel( D3D_FEATURE_LEVEL_11_0 )
	,m_driverType( D3D_DRIVER_TYPE_HARDWARE )
	,m_nUpdateCount( 0 )
	,m_nFrameCount( 0 )
	,m_fFps( 0 )
{

	QueryPerformanceCounter( &m_lastFpsUpdateTime );
}


CoreSystem::~CoreSystem()
{
	Finalize();
}


void CoreSystem::Finalize()
{
	GFX_RELEASE( m_pd3dDev );
	GFX_RELEASE( m_pImmedisateContext );

}



BOOL	CoreSystem::Initialize()
{

	Finalize();

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE( driverTypes );

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE( featureLevels );

// 	DXGI_SWAP_CHAIN_DESC sd;
// 	ZeroMemory( &sd, sizeof( sd ) );
// 	sd.BufferCount = 1;
// 	sd.BufferDesc.Width = width;
// 	sd.BufferDesc.Height = height;
// 	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
// 	sd.BufferDesc.RefreshRate.Numerator = 60;
// 	sd.BufferDesc.RefreshRate.Denominator = 1;
// 	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
// 	sd.OutputWindow = g_hWnd;
// 	sd.SampleDesc.Count = 1;
// 	sd.SampleDesc.Quality = 0;
// 	sd.Windowed = TRUE;

	HRESULT hr = E_FAIL;
	for( UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++ )
	{
		m_driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDevice( NULL, m_driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION,  &m_pd3dDev, &m_featureLevel, &m_pImmedisateContext );
		if( SUCCEEDED( hr ) )
			break;
	}
	if( FAILED( hr ) )
		return FALSE;

	/*
	ID3D11Device1* d3d11_Device1 = nullptr;
	m_pd3dDev->QueryInterface(__uuidof (ID3D11Device1), (void **)&d3d11_Device1);

	if (d3d11_Device1) {
		d3d11_Device1->Release();
	}
	*/



	return TRUE;
}



/*

	–ˆƒtƒŒ[ƒ€ŒÄ‚Ño‚µ‚Ä‚­‚¾‚³‚¢

*/
void	CoreSystem::Update()
{
	++m_nUpdateCount;
	++m_nFrameCount;


	LARGE_INTEGER current;
	QueryPerformanceCounter( &current );
	
	LARGE_INTEGER freq;
	QueryPerformanceFrequency( &freq );


	if ( current.QuadPart - m_lastFpsUpdateTime.QuadPart > freq.QuadPart )
	{

		double  period = (double)( current.QuadPart - m_lastFpsUpdateTime.QuadPart ) / (double)freq.QuadPart;


		m_fFps = float( m_nFrameCount / period );


		m_lastFpsUpdateTime = current;
		m_nFrameCount = 0;

	}

}




}