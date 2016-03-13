#pragma once
#include "GfxShader.h"


namespace GfxLib
{


	class	ComputeShader :
		Shader
	{

	public:
		ComputeShader();
		~ComputeShader();



		BOOL	CreateFromFile( ID3D11Device * dev ,const wchar_t* fileName , LPCSTR entryPoint );
		void	Finalize();

		operator ID3D11ComputeShader* ()   const {	return m_pComputeShader;	}

	private:

		D3DPtr< ID3D11ComputeShader > m_pComputeShader;


	};




}


