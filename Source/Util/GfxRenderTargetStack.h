#pragma		once
#include "GfxD3DPtr.h"


namespace GfxLib
{

	class RenderTargetStack
	{
	public:
		RenderTargetStack();
		~RenderTargetStack();


		BOOL Initialize(  ID3D11DeviceContext *pDeviceContext );
		void Finalize();


		void	PushRenderTargets(
			UINT NumViews,
			ID3D11RenderTargetView *const *ppRenderTargetViews,
			ID3D11DepthStencilView *pDepthStencilView
		);
		void	PopRenderTargets();


	private:
		D3DPtr< ID3D11DeviceContext >	m_ptrDeviceContext;

		enum {
			STACK_NUM = 8,
		};


		int		m_StackIndex;
		struct RENDERTARGETS
		{
			ID3D11RenderTargetView*		apRT[ D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT ];
			ID3D11DepthStencilView*		pDepth;
		};

		RENDERTARGETS	m_aRTStack[ STACK_NUM ];


	};





}





