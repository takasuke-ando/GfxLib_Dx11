/*


	フォントシステムを初期化する

	・ステートオブジェクトの作成
	・各種シェーダの読み込み
	などを行う


*/


#include "stdafx.h"
#include "GfxFontSystem.h"
#include <Device\GfxDeviceContext.h>



namespace GfxLib
{

	UINT	FontBuffSize = sizeof( FontVertex ) * 6 * 128;


FontSystem::FontSystem()
{

}


FontSystem::~FontSystem()
{

	Finalize();
	
}



/*


	pDevice:	D3Dデバイス


*/
BOOL	FontSystem::Initialize( ID3D11Device* pDevice )
{
	Finalize();


	{
		//	通常のブレンドステートを取得する
		D3D11_BLEND_DESC desc = BlendState::GetDefaultDesc();
		desc.RenderTarget[0].BlendEnable = TRUE;
		desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

		m_BlendState.Initialize( pDevice , desc );
	}

	{
		D3D11_DEPTH_STENCIL_DESC desc = DepthStencilState::GetDefaultDesc();
		desc.DepthEnable = FALSE;

		m_DepthStencilState.Initialize( pDevice , desc );
	}

	{
		D3D11_RASTERIZER_DESC desc = RasterizerState::GetDefaultDesc();
		desc.CullMode = D3D11_CULL_NONE;
		m_RasterState.Initialize( pDevice , desc );
	}

	{
		D3D11_SAMPLER_DESC desc = SamplerState::GetDefaultDesc();
		m_SamplerState.Initialize( pDevice , desc );
	}


	if ( !m_VertexShader.CreateFromFile( pDevice , L"Media\\Shader\\Font.fx" , "VS" ) )
	{
		return FALSE;
	}
	if ( !m_PixelShader.CreateFromFile( pDevice , L"Media\\Shader\\Font.fx" , "PS" ) )
	{
		return FALSE;
	}


	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR"   , 0 , DXGI_FORMAT_R8G8B8A8_UNORM , 0, 12,D3D11_INPUT_PER_VERTEX_DATA , 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE( layout );

	if ( !m_InputLayout.Initialize( pDevice , layout , numElements , &m_VertexShader ) )
	{
		return FALSE;
	}

	if ( !m_VtxBuff.InitializeDynamic( pDevice , FontBuffSize ) )
	{
		GFX_ASSERT( 0 , "Font Buffer Allocation Failed!" );
		return FALSE;
	}


	m_pD3DDevice=  pDevice;


	return TRUE;


}



void	FontSystem::Finalize()
{

	m_pD3DDevice = NULL;
	m_VertexShader.Finalize();
	m_PixelShader.Finalize();
	m_InputLayout.Finalize();
	m_DepthStencilState.Finalize();
	m_BlendState.Finalize();
	m_SamplerState.Finalize();
}




/*

	デバイスステートの設定を行う
	DeviceContextが当該スレッドに所有権がある限り
	このメソッドはスレッドセーフである


*/

void	FontSystem::SetupStates( DeviceContext * ctx )
{

	FLOAT BlendFactor[4] = { 1.f,1.f,1.f,1.f };
	ctx->PSSetShader( &m_PixelShader );
	ctx->PSSetSampler( 0 , &m_SamplerState );
	ctx->VSSetShader( &m_VertexShader );
	ctx->IASetInputLayout( &m_InputLayout );
	ctx->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	UINT stride = sizeof( FontVertex );
	UINT offset = 0;
	ID3D11Buffer *pBuffer = m_VtxBuff; 
	ctx->operator ID3D11DeviceContext*()->IASetVertexBuffers( 0 , 1 , &pBuffer , &stride, &offset  );

	//test
  	ctx->OMSetBlendState( &m_BlendState , BlendFactor );
  	ctx->OMSetDepthStencilState( &m_DepthStencilState , 0 );
 	ctx->RSSetState( &m_RasterState );

}








}

