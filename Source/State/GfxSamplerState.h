#pragma once
#include <Util\GfxD3DPtr.h>


namespace GfxLib
{

	class SamplerState
	{
	public:

		SamplerState( );
		~SamplerState();


		BOOL	Initialize( ID3D11Device* pdev , const D3D11_SAMPLER_DESC &bd );
		void	Finalize();


		operator ID3D11SamplerState *()	const	{	return m_pSamplerState;	}


		static D3D11_SAMPLER_DESC	GetDefaultDesc();


	private:
		D3DPtr< ID3D11Device > m_pd3dDev;

		D3DPtr< ID3D11SamplerState > m_pSamplerState;
	};

}