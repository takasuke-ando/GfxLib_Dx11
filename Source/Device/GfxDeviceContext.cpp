


#include "stdafx.h"


#include "GfxDeviceContext.h"



namespace GfxLib
{


DeviceContext::DeviceContext( ID3D11Device* dev )
	:m_pd3dDev( dev )
	,m_pDeviceContext( NULL )
{
	m_pd3dDev->AddRef();

}

DeviceContext::DeviceContext( ID3D11Device* dev, ID3D11DeviceContext * ctx)
	:m_pd3dDev( dev )
	,m_pDeviceContext( ctx )
{
	m_pd3dDev->AddRef();
	m_pDeviceContext->AddRef();

	m_RTStack.Initialize( m_pDeviceContext );
}


DeviceContext::~DeviceContext()
{
	m_RTStack.Finalize();
	GFX_RELEASE( m_pd3dDev );
	GFX_RELEASE( m_pDeviceContext );
}


BOOL	DeviceContext::CreateDeferredContext()
{

	GFX_ASSERT( m_pDeviceContext ==  NULL , "Already created!" );

	GFX_RELEASE( m_pDeviceContext );

	HRESULT hr = m_pd3dDev->CreateDeferredContext(0, &m_pDeviceContext );
	if ( FAILED( hr ) )
		return FALSE;

	m_RTStack.Initialize( m_pDeviceContext );

	return TRUE;


}



BOOL	DeviceContext::CreateImmediateContext()
{
	GFX_ASSERT( m_pDeviceContext ==  NULL , "Already created!" );

	GFX_RELEASE( m_pDeviceContext );

	m_pd3dDev->GetImmediateContext( &m_pDeviceContext );

	m_RTStack.Initialize( m_pDeviceContext );


	return TRUE;

}



}