




#include "stdafx.h"


#include "GfxRasterizerState.h"


namespace GfxLib
{

RasterizerState::RasterizerState()
{


}



RasterizerState::~RasterizerState()
{
	Finalize();
}



/*

	‰Šú‰»

*/

BOOL	RasterizerState::Initialize( ID3D11Device *pDev , const D3D11_RASTERIZER_DESC &Desc )
{

	Finalize();

	m_pD3DDevice = pDev;

	HRESULT hr = pDev->CreateRasterizerState( &Desc , m_pRasterState.InitialAccept() );


	return SUCCEEDED( hr );

}



void	RasterizerState::Finalize()
{
	m_pD3DDevice = NULL;
	m_pRasterState = NULL;

}

D3D11_RASTERIZER_DESC	RasterizerState::GetDefaultDesc()
{
	D3D11_RASTERIZER_DESC desc;
	ZeroMemory( &desc , sizeof( desc ) );

	desc.FillMode = D3D11_FILL_SOLID;
	desc.CullMode = D3D11_CULL_BACK;
	desc.FrontCounterClockwise = FALSE ;
	desc.DepthBias = 0;
	desc.SlopeScaledDepthBias = 0.f;
	desc.DepthBiasClamp = 0.f;
	desc.DepthClipEnable = TRUE;
	desc.ScissorEnable = FALSE;
	desc.MultisampleEnable = FALSE;
	desc.AntialiasedLineEnable = FALSE;

	

	return desc;

}



}

