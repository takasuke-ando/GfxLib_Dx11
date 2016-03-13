#pragma		once




namespace GfxLib
{

	/*

		�t�H���g�`����s��
		�ʏ�A�X�^�b�N��ɐ�������

	*/

	class DeviceContext;
	class FontSystem;
	class FontData;
	struct FontVertex;

	class	FontRenderer
	{
	public:

		FontRenderer( GfxLib::DeviceContext *pContext , FontSystem* pSystem , FontData *pFontData );
		~FontRenderer();



		void	Begin();
		void	End();


		void	DrawText( float x , float y , const wchar_t *text );
		void	DrawFormatText( float x , float y , const wchar_t *text , ... );



	private:


		void	_SetPosition( float x , float y );
		void	_DrawText( const wchar_t * text );

		void	_InputVertices( const FontVertex [] , UINT vtxNum );

		void	_Begin();
		void	_End();

		void	_Flush();
		void	_AllocateBuffer();

		GfxLib::DeviceContext *m_pContext;

		FontData*	m_pFontData;
		FontSystem* m_pFontSystem;


		UINT	m_NestedBeginEndCount;

		D3D11_VIEWPORT	m_vp;

		FontVertex *m_pFontBuff;		//!<	�t�H���g�������ݐ�
		UINT		m_FontBuffRest;
		UINT		m_FontBuffWrote;	//!<	�������ݍςݒ��_��

		float		m_fFontPosX , m_fFontPosY;

	};



}




