
#pragma once
#include <Util\GfxD3DPtr.h>


namespace GfxLib
{

	/*
		
		2次元テクスチャリソースとして初期化する

	*/

	class Texture2D
	{
	public:
		Texture2D( );
		~Texture2D();


		BOOL	Initialize( ID3D11Device* pDevice ,  UINT width , UINT height , DXGI_FORMAT format , UINT bindFlags = D3D11_BIND_SHADER_RESOURCE );
		void	Finalize();

		operator ID3D11Texture2D*()		const	{	return m_pTexture;	}

	protected:
	private:

		D3DPtr< ID3D11Device >		m_pd3dDev;
		D3DPtr< ID3D11Texture2D >	m_pTexture;


	};



}
