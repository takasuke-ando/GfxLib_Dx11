#pragma once

#include "../Util\GfxD3DPtr.h"


namespace GfxLib
{



	class	DepthStencil
	{
	public:
		DepthStencil();
		~DepthStencil();


		BOOL	Initialize(ID3D11Device* pDevice ,  UINT width , UINT height , DXGI_FORMAT format  );
		//BOOL	InitializeShaderResourceView( ID3D11Device* pDevice , UINT width , UINT height , DXGI_FORMAT format  );
		BOOL	InitializeTexture2D( ID3D11Device* pDevice , ID3D11Texture2D* ptexture ,DXGI_FORMAT format , UINT mipSlice = 0 );


		void	Finalize();


		operator ID3D11DepthStencilView* ()		const	{	return m_pDepthStencil;		}
		//operator ID3D11ShaderResourceView* ()	const	{	return m_pShaderResView;	}

	private:

		D3DPtr<ID3D11Device>			m_pD3DDevice;
		D3DPtr<ID3D11DepthStencilView>		m_pDepthStencil;
		D3DPtr<ID3D11Texture2D>				m_pDepthTexture;
		D3DPtr<ID3D11ShaderResourceView>	m_pShaderResView;	//!<	InitializeResourceView‚Å‰Šú‰»‚µ‚½ê‡

	};



}




