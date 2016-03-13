



#include "stdafx.h"

#include "GfxRenderTargetStack.h"




namespace GfxLib
{


	RenderTargetStack::RenderTargetStack()
	{
		m_StackIndex = 0;
		ZeroMemory( m_aRTStack , sizeof( m_aRTStack ) );
	}



	RenderTargetStack::~RenderTargetStack()
	{
		Finalize();
	}



	BOOL RenderTargetStack::Initialize(  ID3D11DeviceContext *pDeviceContext )
	{
		Finalize();
		m_ptrDeviceContext = pDeviceContext;




		return TRUE;
	}



	void RenderTargetStack::Finalize()
	{
		GFX_ASSERT( m_StackIndex == 0 , "Push/Pop unmatch!!" );
		m_ptrDeviceContext = NULL;
	}


	/*

		レンダーターゲットのプッシュ

	*/
	void	RenderTargetStack::PushRenderTargets(
		UINT NumViews,
		ID3D11RenderTargetView *const *ppRenderTargetViews,
		ID3D11DepthStencilView *pDepthStencilView
		)
	{

		GFX_ASSERT( m_StackIndex < STACK_NUM , "Stack over..." );

		RENDERTARGETS	&rtsave = m_aRTStack[ m_StackIndex ];

		m_ptrDeviceContext->OMGetRenderTargets( ARRAYSIZE(rtsave.apRT) , rtsave.apRT , &rtsave.pDepth  );
		m_ptrDeviceContext->OMSetRenderTargets( NumViews , ppRenderTargetViews , pDepthStencilView );

		++m_StackIndex;

	}


	/*

		レンダーターゲットのポップ

	*/
	void	RenderTargetStack::PopRenderTargets()
	{
		GFX_ASSERT( m_StackIndex > 0 , "Push / Pop unmatch..." );

		--m_StackIndex;

		RENDERTARGETS	&rtsave = m_aRTStack[ m_StackIndex ];
		m_ptrDeviceContext->OMSetRenderTargets( ARRAYSIZE(rtsave.apRT) , rtsave.apRT , rtsave.pDepth  );


		GFX_RELEASE( rtsave.pDepth );
		for ( UINT i = 0 ; i < ARRAYSIZE(rtsave.apRT) ; ++i )
		{
			GFX_RELEASE( rtsave.apRT[i] );
		}

	}







}


