#pragma once
#include <Util\GfxD3DPtr.h>


namespace GfxLib
{

	class BlendState
	{
	public:

		BlendState();
		~BlendState();


		void	Finalize();	//	îjä¸

		//	èâä˙âª
		BOOL	Initialize( ID3D11Device* pdev , const D3D11_BLEND_DESC &bd );
		BOOL	Initialize( ID3D11Device* pdev , const D3D11_RENDER_TARGET_BLEND_DESC &trb , BOOL AlphaToCoverageEnable );
		BOOL	Initialize( ID3D11Device* pdev , const D3D11_RENDER_TARGET_BLEND_DESC trb[8] , BOOL AlphaToCoverageEnable  );


		static D3D11_BLEND_DESC		GetDefaultDesc();

		operator ID3D11BlendState*()  const	{	return m_pBlendState;	}


	private:
		D3DPtr< ID3D11Device > m_pd3dDev;

		D3DPtr< ID3D11BlendState > m_pBlendState;
	};

}