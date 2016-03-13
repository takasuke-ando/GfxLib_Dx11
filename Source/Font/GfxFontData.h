#pragma		once
#include <Util\GfxD3DPtr.h>
#include <Resource\GfxShaderResourceView.h>


/*

	�V���v���ȃr�b�g�}�b�v�t�H���g�`�惆�[�e�B���e�B

*/



namespace GfxLib
{

	class	FontData
	{
	public:
		FontData();
		~FontData();

		BOOL	Initialize( ID3D11Device *pDevice , const wchar_t * szTextureFilePath );
		void	Finalize();

		ShaderResourceView&		GetTexture()	{	return	m_FontTexture;	}

	private:

		D3DPtr< ID3D11Device >				m_pD3DDevice;
		
		ShaderResourceView					m_FontTexture;


	};

}



