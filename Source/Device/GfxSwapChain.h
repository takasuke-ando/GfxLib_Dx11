#pragma once
#include "../Resource\GfxRenderTarget.h"


namespace GfxLib
{


	class	SwapChain
	{
	public:
		SwapChain(  );
		~SwapChain();


		BOOL	Initialize( ID3D11Device* , HWND );
		void	Finalize();

		BOOL	Resize( UINT width , UINT height );

		BOOL	Present(
			UINT SyncInterval,
			UINT Flags
			);

		operator IDXGISwapChain *()			const	{	return m_pSwapChain;	}
		operator ID3D11RenderTargetView* () const	{	return m_pRenderTargetView;	}

		RenderTarget*	GetRenderTarget	(){	return &m_RenderTarget; }


	private:


		D3DPtr<ID3D11Device>			m_pd3dDev;
		D3DPtr<IDXGISwapChain>			m_pSwapChain;
		D3DPtr<ID3D11RenderTargetView>	m_pRenderTargetView;

		RenderTarget	m_RenderTarget;

	};



}


