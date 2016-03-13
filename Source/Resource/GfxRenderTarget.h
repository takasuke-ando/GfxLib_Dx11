#pragma	once
#include "../Util\GfxD3DPtr.h"



namespace GfxLib
{


	class	RenderTarget
	{

	public:

		RenderTarget();
		~RenderTarget();

		BOOL	Initialize( ID3D11Device* pDevice , UINT width , UINT height , DXGI_FORMAT format );
		BOOL	InitializeShaderResourceView( ID3D11Device* pDevice , UINT width , UINT height , DXGI_FORMAT format );
		BOOL	InitializeAttach( ID3D11Device* pDevice , ID3D11Texture2D* ptexture , ID3D11RenderTargetView* rtv );
		BOOL	InitializeTexture2D( ID3D11Device* pDevice , ID3D11Texture2D* ptexture ,DXGI_FORMAT format , UINT mipSlice = 0 );

		void	Finalize();

		operator ID3D11RenderTargetView*()	const	{	return	m_pRenderTarget;	}



	private:

		D3DPtr< ID3D11Device >				m_pD3DDevice;
		D3DPtr< ID3D11RenderTargetView >	m_pRenderTarget;
		D3DPtr< ID3D11Texture2D >			m_pRenderTargetTexture;
		D3DPtr<ID3D11ShaderResourceView>	m_pShaderResView;	//!<	InitializeResourceView‚Å‰Šú‰»‚µ‚½ê‡



	};




}



