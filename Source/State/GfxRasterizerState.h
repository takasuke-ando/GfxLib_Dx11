#pragma once
#include <Util\GfxD3DPtr.h>

namespace GfxLib
{

	/*

		ID3D11RasterizerState‚ðƒJƒvƒZƒ‹‰»

	*/



	class	RasterizerState
	{
	public:
		RasterizerState();
		~RasterizerState();


		BOOL	Initialize( ID3D11Device * , const D3D11_RASTERIZER_DESC &Desc );
		void	Finalize();


		static D3D11_RASTERIZER_DESC	GetDefaultDesc();

		operator ID3D11RasterizerState*	()	const	{	return m_pRasterState;	}

	private:

		D3DPtr< ID3D11Device > m_pD3DDevice;
		D3DPtr< ID3D11RasterizerState >	m_pRasterState;



	};





}

