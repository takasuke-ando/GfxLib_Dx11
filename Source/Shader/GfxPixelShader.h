#pragma once
#include "GfxShader.h"


namespace GfxLib
{


	class PixelShader : public Shader
	{


	public:
		PixelShader( );
		~PixelShader();


		BOOL CreateFromFile( ID3D11Device * dev ,const wchar_t* fileName , LPCSTR entryPoint );
		void	Finalize();

		operator ID3D11PixelShader* ()   const {	return m_pPixelShader;	}

	private:

		ID3D11PixelShader *m_pPixelShader;


	};



}