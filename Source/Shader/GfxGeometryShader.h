#pragma		once

#include "GfxShader.h"


namespace GfxLib
{


	class GeometryShader : public Shader
	{


	public:
		GeometryShader( );
		~GeometryShader();


		BOOL	CreateFromFile( ID3D11Device * dev ,const wchar_t* fileName , LPCSTR entryPoint );
		void	Finalize();

		operator ID3D11GeometryShader* ()   const {	return m_pGeomShader;	}

	private:

		ID3D11GeometryShader *m_pGeomShader;



	};



}

