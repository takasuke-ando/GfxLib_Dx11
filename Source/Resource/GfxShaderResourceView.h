#pragma once
#include <Util\GfxD3DPtr.h>



namespace GfxLib
{
	class ShaderResourceView
	{
	public:

		ShaderResourceView();
		~ShaderResourceView();

		BOOL	InitializeFromFile( ID3D11Device* dev , const wchar_t* filepath );
		BOOL	InitializeBufferEx(ID3D11Device* dev , ID3D11Buffer*  );
		BOOL	InitializeTexture2D( ID3D11Device* dev , ID3D11Texture2D* , DXGI_FORMAT format  );

		void	Finalize();

		operator ID3D11ShaderResourceView *()	const {		return m_pShaderResView;	}

	private:

		D3DPtr< ID3D11Device >				m_pd3dDev;

		D3DPtr< ID3D11ShaderResourceView >	m_pShaderResView;


	};


}