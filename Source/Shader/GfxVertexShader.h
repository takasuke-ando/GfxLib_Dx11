#pragma once
#include "GfxShader.h"


namespace GfxLib
{


	class VertexShader : public Shader
	{


	public:
		VertexShader( );
		~VertexShader();

		BOOL	CreateFromFile(  ID3D11Device * dev , const wchar_t* fileName , LPCSTR entryPoint );
		void	Finalize();

		operator ID3D11VertexShader* ()   const {	return m_pVertexShader;	}
		const void*	GetBufferPointer()	const	{	return m_pShaderBlob->GetBufferPointer();	}
		UINT		GetBufferSize()		const	{	return m_pShaderBlob->GetBufferSize();		}

	private:

		ID3D11VertexShader *m_pVertexShader;
		ID3DBlob		*m_pShaderBlob;	
	};



}