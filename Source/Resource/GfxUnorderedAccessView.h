#pragma		once
#include <Util\GfxD3DPtr.h>


namespace GfxLib
{


	class	UnorderedAccessView
	{
	public:

		UnorderedAccessView();
		~UnorderedAccessView();


		BOOL	InitializeBuffer( ID3D11Device* pDevice , ID3D11Buffer * );
		BOOL	InitializeTexture2D( ID3D11Device* pDevice , ID3D11Texture2D * ,DXGI_FORMAT format ,  UINT mipSlice = 0 );
		BOOL	InitializeAppendableBuffer( ID3D11Device* pDevice , ID3D11Buffer * );

		void	Finalize();

		operator ID3D11UnorderedAccessView*()	const	{	return m_pUAV;	}
	private:

		D3DPtr< ID3D11Device >				m_pD3DDevice;
		D3DPtr< ID3D11UnorderedAccessView >	m_pUAV;




	};




}

