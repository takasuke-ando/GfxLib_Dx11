#pragma		once
#include <Util\GfxD3DPtr.h>


namespace GfxLib
{


	/*

		ID3D11DepthStencilState‚ðƒJƒvƒZƒ‹‰»

	*/


	class	DepthStencilState
	{


	public:
		DepthStencilState();
		~DepthStencilState();


		BOOL	Initialize( ID3D11Device *pDevice , const D3D11_DEPTH_STENCIL_DESC &desc  );
		void	Finalize();


		static D3D11_DEPTH_STENCIL_DESC		GetDefaultDesc();

		operator ID3D11DepthStencilState* ()	const {	return m_pDepthStencilState;	}


	private:

		D3DPtr< ID3D11Device >				m_pD3DDevice;
		D3DPtr< ID3D11DepthStencilState >	m_pDepthStencilState;




	};








}
