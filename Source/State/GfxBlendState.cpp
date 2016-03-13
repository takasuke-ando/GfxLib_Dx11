

#include "stdafx.h"


#include "GfxBlendState.h"




namespace GfxLib
{



BlendState::BlendState( )
	:m_pd3dDev( NULL )
	,m_pBlendState( NULL )
{


}


BlendState::~BlendState()
{
	Finalize();
}


void BlendState::Finalize()
{
	m_pd3dDev = NULL;
	m_pBlendState  = NULL;
}


BOOL	BlendState::Initialize( ID3D11Device* pdev , const D3D11_BLEND_DESC &bd )
{
	Finalize();

	m_pd3dDev = pdev;
	HRESULT hr = m_pd3dDev->CreateBlendState( &bd , m_pBlendState.InitialAccept() );

	if ( FAILED( hr ) ) 
		return FALSE;


	return TRUE;
}



/*
	初期化
	trb			ターゲットのブレンド情報
	AtCEnable	AlphaToCoverage有効
*/


BOOL	BlendState::Initialize( ID3D11Device* pdev , const D3D11_RENDER_TARGET_BLEND_DESC &trb , BOOL AtCEnable )
{

	D3D11_BLEND_DESC bd = {0};


	bd.AlphaToCoverageEnable = AtCEnable;
	bd.IndependentBlendEnable = FALSE;
	bd.RenderTarget[0] = trb;

	return Initialize( pdev , bd );
}


/*
	初期化
	trb			ターゲットのブレンド情報
	AtCEnable	AlphaToCoverage有効
*/


BOOL	BlendState::Initialize( ID3D11Device* pdev , const D3D11_RENDER_TARGET_BLEND_DESC trb[8] , BOOL AtCEnable )
{

	D3D11_BLEND_DESC bd = {0};
	

	bd.AlphaToCoverageEnable = AtCEnable;
	bd.IndependentBlendEnable = TRUE;
	for ( int i = 0 ; i < ARRAYSIZE( bd.RenderTarget ) ; ++i )
		bd.RenderTarget[i] = trb[i];

	return Initialize( pdev , bd );


}



/*

	デフォルトのブレンドデスクを取得する
	これはデバイスにNULLを指定したときと同じ結果が得られる

*/

D3D11_BLEND_DESC		BlendState::GetDefaultDesc()
{

	D3D11_BLEND_DESC   blendDesc;
	ZeroMemory( &blendDesc, sizeof( blendDesc ) );

	blendDesc.AlphaToCoverageEnable = FALSE;
	blendDesc.IndependentBlendEnable = FALSE;


	for ( int i = 0 ; i < ARRAYSIZE( blendDesc.RenderTarget ) ; ++i )
	{
		 D3D11_RENDER_TARGET_BLEND_DESC &rt = blendDesc.RenderTarget[ i ];

		 rt.BlendEnable 			=   FALSE;
		 rt.SrcBlend 				=   D3D11_BLEND_ONE ;
		 rt.DestBlend 				=   D3D11_BLEND_ZERO ;
		 rt.BlendOp 				=   D3D11_BLEND_OP_ADD;
		 rt.SrcBlendAlpha 			=   D3D11_BLEND_ONE;
		 rt.DestBlendAlpha			=   D3D11_BLEND_ZERO;
		 rt.BlendOpAlpha 			=   D3D11_BLEND_OP_ADD;
		 rt.RenderTargetWriteMask   =   D3D11_COLOR_WRITE_ENABLE_ALL;
	}

	return blendDesc;

}




}