


#include "stdafx.h"

#include "GfxDepthStencilState.h"



namespace GfxLib
{



DepthStencilState::DepthStencilState()
{


}



DepthStencilState::~DepthStencilState()
{


}



BOOL	DepthStencilState::Initialize( ID3D11Device *pDevice , const D3D11_DEPTH_STENCIL_DESC &desc  )
{
	Finalize();


	m_pD3DDevice = pDevice;


	HRESULT hr = pDevice->CreateDepthStencilState( &desc , m_pDepthStencilState.InitialAccept() );


	return SUCCEEDED( hr );

}



void	DepthStencilState::Finalize()
{

	m_pD3DDevice = NULL;
	m_pDepthStencilState = NULL;

}




D3D11_DEPTH_STENCIL_DESC		DepthStencilState::GetDefaultDesc()
{

	D3D11_DEPTH_STENCIL_DESC desc;
	ZeroMemory( &desc , sizeof( desc )) ;

	desc.DepthEnable		= TRUE; 
	desc.DepthWriteMask		= D3D11_DEPTH_WRITE_MASK_ALL;
	desc.DepthFunc			= D3D11_COMPARISON_LESS;
	desc.StencilEnable		= FALSE;
	desc.StencilReadMask	= D3D11_DEFAULT_STENCIL_READ_MASK;
	desc.StencilWriteMask	= D3D11_DEFAULT_STENCIL_WRITE_MASK;
	desc.FrontFace.StencilFunc			= D3D11_COMPARISON_ALWAYS;
	desc.FrontFace.StencilDepthFailOp	= D3D11_STENCIL_OP_KEEP;
	desc.FrontFace.StencilPassOp		= D3D11_STENCIL_OP_KEEP;
	desc.FrontFace.StencilFailOp		= D3D11_STENCIL_OP_KEEP;
	desc.BackFace.StencilFunc			= D3D11_COMPARISON_ALWAYS;
	desc.BackFace.StencilDepthFailOp	= D3D11_STENCIL_OP_KEEP;
	desc.BackFace.StencilPassOp			= D3D11_STENCIL_OP_KEEP;
	desc.BackFace.StencilFailOp			= D3D11_STENCIL_OP_KEEP;
	
	return desc;

}


}