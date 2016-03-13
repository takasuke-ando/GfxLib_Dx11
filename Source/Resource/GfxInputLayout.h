#pragma once
#include <Util\GfxD3DPtr.h>


namespace GfxLib
{

	class VertexShader;

	class InputLayout
	{

	public:
		InputLayout();
		~InputLayout();


		BOOL	Initialize( ID3D11Device* dev , const D3D11_INPUT_ELEMENT_DESC *layout ,  UINT layoutNum , const VertexShader * ); 
		void	Finalize();

		operator ID3D11InputLayout* ()	const {	return m_pInputLayout; }

	private:
		D3DPtr< ID3D11Device > m_pd3dDev;

		D3DPtr< ID3D11InputLayout> m_pInputLayout;

	};


}

