#pragma once
#include "Util\GfxRenderTargetStack.h"




namespace GfxLib
{

	//	前方参照
	class ConstantBuffer;
	class RenderTarget;
	class DepthStencil;
	class InputLayout;
	class IndexBuffer;
	class PixelShader;
	class VertexShader;
	class VertexBuffer;
	class ShaderResourceView;
	class SamplerState;
	class DepthStencilState;
	class RasterizerState;
	class BlendState;

	class DeviceContext
	{

	public:


		DeviceContext( ID3D11Device* );
		DeviceContext( ID3D11Device* , ID3D11DeviceContext *);
		~DeviceContext();

		operator ID3D11DeviceContext*()	const	{	return	m_pDeviceContext;	}

		BOOL	CreateDeferredContext();
		BOOL	CreateImmediateContext();


		inline void	ClearRenderTargetView( RenderTarget* rt , const float color[4] );
		inline void ClearDepthStencilView( DepthStencil* ds , UINT ClearFlags , float depthClear = 1.f , UINT8 StencilClear = 0 );


		inline void	UpdateConstantBuffer( ConstantBuffer *cb , UINT byteOffset , const void* data , UINT byteSize );

		inline void IASetInputLayout( InputLayout *layout );
		inline void IASetIndexBuffer( IndexBuffer *idxBuffer , DXGI_FORMAT Format,UINT Offset );
		inline void IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY Topology );
		inline void IASetVertexBuffers(  UINT StartSlot,  UINT NumBuffers,
			ID3D11Buffer *const *ppVertexBuffers,  const UINT *pStrides,
			const UINT *pOffsets);

		inline void	VSSetConstantBuffer( UINT slot , const ConstantBuffer * );
		inline void	VSSetConstantBuffers( UINT slot , const ConstantBuffer * , const ConstantBuffer * );
		inline void	VSSetConstantBuffers( UINT slot , const ConstantBuffer * , const ConstantBuffer * , const ConstantBuffer * );

		inline void VSSetShader( VertexShader *pVertexShader );

		inline void	PSSetConstantBuffer( UINT slot , const ConstantBuffer * );
		inline void	PSSetConstantBuffers( UINT slot , const ConstantBuffer * , const ConstantBuffer * );
		inline void	PSSetConstantBuffers( UINT slot , const ConstantBuffer * , const ConstantBuffer * , const ConstantBuffer * );

		inline void PSSetShader( PixelShader *pPixelShader );

		inline void PSSetShaderResource( UINT StartSlot , ShaderResourceView* rv );
		inline void PSSetShaderResource( UINT StartSlot , ID3D11ShaderResourceView* rv );
		inline void PSSetShaderResources(  UINT StartSlot,  UINT NumViews,
			ShaderResourceView *const *ppShaderResourceViews);
		inline void PSSetSampler( UINT StartSlot , SamplerState* sampler );

		inline void	OMSetRenderTarget( RenderTarget* rt , DepthStencil *depth );
		inline void OMSetRenderTargets( UINT count ,RenderTarget* rts[] , DepthStencil* depth );
		inline void OMSetBlendState( BlendState * blendState ,  const FLOAT BlendFactor[4], UINT SampleMask = 0xffffffff );
		inline void OMSetDepthStencilState( DepthStencilState* state , UINT stencilRef = 0);

		//	push/pop
		inline void OMPushRenderTargets( UINT count ,ID3D11RenderTargetView* rts[] , ID3D11DepthStencilView* depth );
		inline void OMPopRenderTargets();
		

		inline void RSSetState( RasterizerState *rasterState );
		inline void RSSetViewports(  UINT NumViewports,  const D3D11_VIEWPORT *pViewports);
		inline void RSGetViewports(	UINT *pNumViewports,D3D11_VIEWPORT *pViewports	);


		inline void CSSetShaderResource(  UINT StartSlot,  ID3D11ShaderResourceView  *pShaderResourceViews);
		inline void CSSetShaderResources(  UINT StartSlot,  ID3D11ShaderResourceView  *pSRV0 ,  ID3D11ShaderResourceView  *pSRV1 );
		inline void CSSetShaderResources(  UINT StartSlot,  ID3D11ShaderResourceView  *pSRV0 ,  ID3D11ShaderResourceView  *pSRV1,  ID3D11ShaderResourceView  *pSRV2 );
		inline void CSSetShaderResources(  UINT StartSlot,  ID3D11ShaderResourceView  *pSRV0 ,  ID3D11ShaderResourceView  *pSRV1,  ID3D11ShaderResourceView  *pSRV2,  ID3D11ShaderResourceView  *pSRV3 );

		inline void CSSetShaderResources(  UINT StartSlot,  UINT NumViews,
			ID3D11ShaderResourceView *const *ppShaderResourceViews);

		inline void CSSetUnorderedAccessView(  UINT StartSlot,  
			ID3D11UnorderedAccessView * pUAV,
			const UINT UAVInitialCount = -1 );
		inline void CSSetUnorderedAccessViews(  UINT StartSlot,  UINT NumUAVs,
			ID3D11UnorderedAccessView * const *ppUnorderedAccessViews,
			const UINT *pUAVInitialCounts = NULL );

		inline void CSSetShader(  ID3D11ComputeShader *pShader, 
			ID3D11ClassInstance *const *ppClassInstances = NULL ,  UINT NumClassInstances = NULL );


		inline void DrawIndexed(  UINT IndexCount,  UINT StartIndexLocation, INT BaseVertexLocation);
		inline void Draw(  UINT VertexCount,  UINT StartVertexLocation );


		inline void Dispatch(  UINT ThreadGroupCountX,  UINT ThreadGroupCountY = 1, UINT ThreadGroupCountZ = 1);
		inline void DispatchIndirect(
			ID3D11Buffer *pBufferForArgs,
			UINT AlignedOffsetForArgs = 0
			);


		inline BOOL	Map( ID3D11Resource* pResource , UINT SubResource , D3D11_MAP , UINT MapFlag , D3D11_MAPPED_SUBRESOURCE *pMapped );
		inline void Unmap( ID3D11Resource* pResource , UINT SubResource );

		//	バッファ書き込みユーティリティ
		inline void *BeginWriteVertexBuffer( VertexBuffer * vb , BOOL bDiscard );
		inline void	EndWriteVertexBuffer( VertexBuffer * vb );

		inline BOOL FinishCommandList(  BOOL RestoreDeferredContextState,	ID3D11CommandList **ppCommandList);

	private:

		ID3D11Device*			m_pd3dDev;
		ID3D11DeviceContext*	m_pDeviceContext;

		RenderTargetStack		m_RTStack;



	};


}


#include "GfxDeviceContext.inl"


