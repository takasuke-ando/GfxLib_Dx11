#pragma once
#include "../Resource/GfxConstantBuffer.h"
#include "../Resource/GfxRenderTarget.h"
#include "../Resource/GfxDepthStencil.h"
#include "../Resource/GfxInputLayout.h"
#include "../Resource/GfxIndexBuffer.h"
#include "../Resource/GfxShaderResourceView.h"
#include "../Shader/GfxPixelShader.h"
#include "../Shader/GfxVertexShader.h"
#include "../State/GfxSamplerState.h"
#include "../Resource/GfxVertexBuffer.h"
#include "State/GfxDepthStencilState.h"
#include "State/GfxRasterizerState.h"
#include "State/GfxBlendState.h"




namespace GfxLib
{


	inline void	DeviceContext::ClearRenderTargetView( RenderTarget* rt , const float color[4] )
	{
		m_pDeviceContext->ClearRenderTargetView( *rt , color );
	}

	inline void DeviceContext::ClearDepthStencilView( DepthStencil* ds , UINT ClearFlags , float depthClear , UINT8 StencilClear )
	{
		m_pDeviceContext->ClearDepthStencilView( *ds , ClearFlags , depthClear , StencilClear );
	}


	/*

		定数バッファの更新コマンドをコンテキストに登録する

	*/
	inline void	DeviceContext::UpdateConstantBuffer( ConstantBuffer *cb , UINT byteOffset , const void* data , UINT byteSize )
	{
		/*
		D3D11_BOX box = { 0 };
		box.left = byteOffset;
		box.right = byteOffset + byteSize;
		box.top = 0;
		box.bottom = 1;
		box.front = 0;
		box.back = 1;
		*/
		//	部分更新不可能

		if ( !cb->IsDynamic() )
		{
			GFX_ASSERT( byteSize == cb->GetByteSize() , "Invalid Byte Size" );
			m_pDeviceContext->UpdateSubresource( *cb , 0 , NULL , data , 0 , 0 );
		}else{

			GFX_ASSERT( byteOffset+byteSize <= cb->GetByteSize() , "Invalid Input Size" );
			D3D11_MAPPED_SUBRESOURCE mappedSR;
			HRESULT hr = m_pDeviceContext->Map( *cb , 0 , D3D11_MAP_WRITE_DISCARD , 0 , &mappedSR );
			if ( FAILED( hr ) )
			{
				return;
			}
			memcpy( byteOffset + (char*)mappedSR.pData , data , byteSize );
			m_pDeviceContext->Unmap( *cb , 0 );
		}
	}


	inline void DeviceContext::IASetInputLayout( InputLayout *layout )
	{
		m_pDeviceContext->IASetInputLayout( layout?layout->operator ID3D11InputLayout*():NULL );
	}

	inline void DeviceContext::IASetIndexBuffer( IndexBuffer *idxBuffer , DXGI_FORMAT Format,UINT Offset )
	{
		m_pDeviceContext->IASetIndexBuffer( idxBuffer?idxBuffer->operator ID3D11Buffer*	const():NULL , Format , Offset );
	}

	inline void DeviceContext::IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY Topology )
	{
		m_pDeviceContext->IASetPrimitiveTopology( Topology );
	}

	inline void DeviceContext::IASetVertexBuffers(  UINT StartSlot,  UINT NumBuffers,
		ID3D11Buffer *const *ppVertexBuffers,  const UINT *pStrides,
		const UINT *pOffsets)
	{
		m_pDeviceContext->IASetVertexBuffers( StartSlot , NumBuffers , ppVertexBuffers , pStrides , pOffsets );
	}

	inline void	DeviceContext::VSSetConstantBuffer( UINT slot , const ConstantBuffer *buf )
	{

		ID3D11Buffer *d3dBuff = *buf;
		m_pDeviceContext->VSSetConstantBuffers( slot , 1 , &d3dBuff );

	}


	inline void	DeviceContext::VSSetConstantBuffers( UINT slot , const ConstantBuffer *buf0 , const ConstantBuffer *buf1 )
	{

		ID3D11Buffer *d3dBuff[2] = {*buf0,*buf1};
		m_pDeviceContext->VSSetConstantBuffers( slot , 2 , d3dBuff );

	}

	inline void	DeviceContext::VSSetConstantBuffers( UINT slot , const ConstantBuffer *buf0 , const ConstantBuffer *buf1 , const ConstantBuffer *buf2 )
	{

		ID3D11Buffer *d3dBuff[3] = {*buf0,*buf1,*buf2};
		m_pDeviceContext->VSSetConstantBuffers( slot , 3 , d3dBuff );

	}


	inline void DeviceContext::VSSetShader( VertexShader *pVertexShader )
	{
		m_pDeviceContext->VSSetShader( pVertexShader?pVertexShader->operator ID3D11VertexShader*():NULL , NULL , 0 );
	}


	inline void	DeviceContext::PSSetConstantBuffer( UINT slot , const ConstantBuffer *buf )
	{

		ID3D11Buffer *d3dBuff = *buf;
		m_pDeviceContext->PSSetConstantBuffers( slot , 1 , &d3dBuff );

	}


	inline void	DeviceContext::PSSetConstantBuffers( UINT slot , const ConstantBuffer *buf0 , const ConstantBuffer *buf1 )
	{

		ID3D11Buffer *d3dBuff[2] = {*buf0,*buf1};
		m_pDeviceContext->PSSetConstantBuffers( slot , 2 , d3dBuff );

	}

	inline void	DeviceContext::PSSetConstantBuffers( UINT slot , const ConstantBuffer *buf0 , const ConstantBuffer *buf1 , const ConstantBuffer *buf2 )
	{

		ID3D11Buffer *d3dBuff[3] = {*buf0,*buf1,*buf2};
		m_pDeviceContext->PSSetConstantBuffers( slot , 3 , d3dBuff );

	}


	inline void DeviceContext::PSSetShader( PixelShader *pPixelShader )
	{
		m_pDeviceContext->PSSetShader( pPixelShader?pPixelShader->operator ID3D11PixelShader*():NULL , NULL , 0 );
	}


	inline void DeviceContext::PSSetShaderResource( UINT StartSlot , ShaderResourceView* rv )
	{
		ID3D11ShaderResourceView* srv = rv ? rv->operator ID3D11ShaderResourceView *():NULL;
		m_pDeviceContext->PSSetShaderResources( StartSlot , 1 , &srv );
	}

	inline void DeviceContext::PSSetShaderResource( UINT StartSlot , ID3D11ShaderResourceView* rv )
	{
		m_pDeviceContext->PSSetShaderResources( StartSlot , 1 , &rv );
	}


// 	inline void DeviceContext::PSSetShaderResources(  UINT StartSlot,  UINT NumViews,
// 		ShaderResourceView *const *ppShaderResourceViews)
// 	{
// 		const int NumViewAllocThreshold 
// 	}
	
	inline void DeviceContext::PSSetSampler( UINT StartSlot , SamplerState* sampler )
	{
		ID3D11SamplerState *samps = sampler?sampler->operator ID3D11SamplerState *():NULL;
		m_pDeviceContext->PSSetSamplers( StartSlot , 1 , &samps );
	}


	inline void	DeviceContext::OMSetRenderTarget( RenderTarget* rt , DepthStencil * depth )
	{

		ID3D11RenderTargetView *prtv =  rt?rt->operator ID3D11RenderTargetView*():NULL;
		m_pDeviceContext->OMSetRenderTargets( 1 , &prtv , depth?depth->operator ID3D11DepthStencilView*():NULL );

	}


	inline void DeviceContext::OMSetBlendState( BlendState * blendState ,  const FLOAT BlendFactor[4], UINT SampleMask  )
	{
		m_pDeviceContext->OMSetBlendState( blendState?blendState->operator ID3D11BlendState*():NULL , BlendFactor , SampleMask );
	}

	inline void DeviceContext::OMSetRenderTargets( UINT count ,RenderTarget* rts[] , DepthStencil* depth )
	{
		GFX_ASSERT( count <= D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT , "Render Target View over" );
		ID3D11RenderTargetView* rtv[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];

		for ( UINT n = 0 ; n < count ; ++n )
		{
			rtv[ n ] = rts[n]?rts[n]->operator ID3D11RenderTargetView*():NULL;
		}

		m_pDeviceContext->OMSetRenderTargets( count , rtv , depth?depth->operator ID3D11DepthStencilView*():NULL );

	}

	inline void DeviceContext::OMSetDepthStencilState( DepthStencilState* state , UINT stencilRef )
	{
		m_pDeviceContext->OMSetDepthStencilState( state?state->operator ID3D11DepthStencilState*():NULL , stencilRef );
	}

	inline void DeviceContext::OMPushRenderTargets( UINT count ,ID3D11RenderTargetView* rts[] , ID3D11DepthStencilView* depth )
	{
		m_RTStack.PushRenderTargets( count ,rts , depth );
	}

	inline void DeviceContext::OMPopRenderTargets()
	{
		m_RTStack.PopRenderTargets();
	}


	inline void DeviceContext::RSSetState( RasterizerState *rasterState )
	{
		m_pDeviceContext->RSSetState( rasterState?rasterState->operator ID3D11RasterizerState*():NULL );
	}

	inline void DeviceContext::RSSetViewports(  UINT NumViewports,  const D3D11_VIEWPORT *pViewports)
	{
		m_pDeviceContext->RSSetViewports( NumViewports , pViewports );
	}


	inline void DeviceContext::RSGetViewports(	UINT *pNumViewports,D3D11_VIEWPORT *pViewports	)
	{
		m_pDeviceContext->RSGetViewports( pNumViewports , pViewports );
	}


	inline void DeviceContext::CSSetShaderResource(  UINT StartSlot,  ID3D11ShaderResourceView  *pShaderResourceView)
	{
		ID3D11ShaderResourceView * apSRV[1] = 
		{
			pShaderResourceView
		};
		m_pDeviceContext->CSSetShaderResources( StartSlot , 1 , apSRV );
	}


	inline void DeviceContext::CSSetShaderResources(  UINT StartSlot,  ID3D11ShaderResourceView  *pSRV0 ,  ID3D11ShaderResourceView  *pSRV1 )
	{
		ID3D11ShaderResourceView * apSRV[2] = 
		{
			pSRV0,
			pSRV1,
		};
		m_pDeviceContext->CSSetShaderResources( StartSlot , 2 , apSRV );
	}

	inline void DeviceContext::CSSetShaderResources(  UINT StartSlot,  ID3D11ShaderResourceView  *pSRV0 ,  ID3D11ShaderResourceView  *pSRV1,  ID3D11ShaderResourceView  *pSRV2 )
	{
		ID3D11ShaderResourceView * apSRV[3] = 
		{
			pSRV0,
			pSRV1,
			pSRV2,
		};
		m_pDeviceContext->CSSetShaderResources( StartSlot , 3 , apSRV );
	}

	inline void DeviceContext::CSSetShaderResources(  UINT StartSlot,  ID3D11ShaderResourceView  *pSRV0 ,  ID3D11ShaderResourceView  *pSRV1,  ID3D11ShaderResourceView  *pSRV2,  ID3D11ShaderResourceView  *pSRV3 )
	{
		ID3D11ShaderResourceView * apSRV[4] = 
		{
			pSRV0,
			pSRV1,
			pSRV2,
			pSRV3,
		};
		m_pDeviceContext->CSSetShaderResources( StartSlot , 4 , apSRV );
	}


	inline void DeviceContext::CSSetShaderResources(  UINT StartSlot,  UINT NumViews,
		ID3D11ShaderResourceView *const *ppShaderResourceViews)
	{
		m_pDeviceContext->CSSetShaderResources( StartSlot , NumViews , 
			ppShaderResourceViews );
	}


	inline void DeviceContext::CSSetUnorderedAccessView( 
		UINT StartSlot,  
		ID3D11UnorderedAccessView * pUAV,
		const UINT UAVInitialCount)
	{
		ID3D11UnorderedAccessView *	apUAV[1] =
		{
			pUAV,
		};
		UINT aUAVInitialCounts[1] = 
		{
			UAVInitialCount,
		};
		m_pDeviceContext->CSSetUnorderedAccessViews( StartSlot , 1 , apUAV , aUAVInitialCounts );
	}

	inline void DeviceContext::CSSetUnorderedAccessViews(  UINT StartSlot,  UINT NumUAVs,
		ID3D11UnorderedAccessView * const *ppUnorderedAccessViews,
		const UINT *pUAVInitialCounts)
	{
		m_pDeviceContext->CSSetUnorderedAccessViews( StartSlot , NumUAVs , ppUnorderedAccessViews , pUAVInitialCounts );
	}


	inline void DeviceContext::CSSetShader(  ID3D11ComputeShader *pShader, 
		ID3D11ClassInstance *const *ppClassInstances,  UINT NumClassInstances)
	{
		m_pDeviceContext->CSSetShader( pShader , ppClassInstances , NumClassInstances );
	}



	inline void DeviceContext::DrawIndexed(  UINT IndexCount,  UINT StartIndexLocation, INT BaseVertexLocation )
	{

		m_pDeviceContext->DrawIndexed( IndexCount , StartIndexLocation , BaseVertexLocation );

	}
	
	inline void DeviceContext::Draw(  UINT VertexCount,  UINT StartVertexLocation )
	{

		m_pDeviceContext->Draw( VertexCount , StartVertexLocation );

	}



	inline void DeviceContext::Dispatch(  UINT ThreadGroupCountX,  UINT ThreadGroupCountY, UINT ThreadGroupCountZ)
	{
		m_pDeviceContext->Dispatch( ThreadGroupCountX , ThreadGroupCountY , ThreadGroupCountZ );
	}

	inline void DeviceContext::DispatchIndirect(
		ID3D11Buffer *pBufferForArgs,
		UINT AlignedOffsetForArgs
		)
	{
		m_pDeviceContext->DispatchIndirect( pBufferForArgs , AlignedOffsetForArgs );
	}



	inline BOOL	DeviceContext::Map( ID3D11Resource* pResource , UINT SubResource , D3D11_MAP map, UINT MapFlag , D3D11_MAPPED_SUBRESOURCE *pMapped )
	{

		HRESULT hr = m_pDeviceContext->Map( pResource , SubResource , map , MapFlag, pMapped );

		return SUCCEEDED( hr );
	}


	inline void DeviceContext::Unmap( ID3D11Resource* pResource , UINT SubResource )
	{

		m_pDeviceContext->Unmap( pResource , SubResource );

	}


	/*

		Dynamic指定された頂点バッファの書き込みを行う
		DeferredContext毎に、リソースに対する最初の呼び出しは
		bDiscard=TRUEにする必要がある


		bDiscard	TRUE:	DISCARDしてバッファ内容を破棄する
					FALSE:	DISCARDしない。現在GPUから参照されているバッファを書き換えない事は
							アプリケーション側が保障する必要がある

	*/
	inline void *DeviceContext::BeginWriteVertexBuffer( VertexBuffer * vb , BOOL bDiscard )
	{

		D3D11_MAPPED_SUBRESOURCE  mapped;

		HRESULT hr = m_pDeviceContext->Map( *vb , 0 , bDiscard?D3D11_MAP_WRITE_DISCARD:D3D11_MAP_WRITE_NO_OVERWRITE , 0 , &mapped );

		if ( SUCCEEDED( hr ) )	return mapped.pData;

		return NULL;

	}


	inline void	DeviceContext::EndWriteVertexBuffer( VertexBuffer *vb )
	{

		m_pDeviceContext->Unmap( *vb , 0 );

	}


	inline BOOL DeviceContext::FinishCommandList(  BOOL RestoreDeferredContextState,	ID3D11CommandList **ppCommandList)
	{
		HRESULT  hr = m_pDeviceContext->FinishCommandList( RestoreDeferredContextState , ppCommandList );

		return SUCCEEDED( hr );
	}


}






