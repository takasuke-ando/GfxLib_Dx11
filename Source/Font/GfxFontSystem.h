#pragma		once
#include <Util\GfxD3DPtr.h>
#include <Shader\GfxVertexShader.h>
#include <Shader\GfxPixelShader.h>
#include <State\GfxBlendState.h>
#include <Resource\GfxInputLayout.h>
#include <Resource\GfxVertexBuffer.h>
#include <State\GfxDepthStencilState.h>
#include <State\GfxRasterizerState.h>
#include <State\GfxSamplerState.h>




namespace GfxLib
{


	struct FontVertex
	{
		XMFLOAT3	vPosition;
		XMCOLOR		vColor;
		XMFLOAT2	vTexCoord;
	};

	class DeviceContext;

	class	FontSystem
	{

	public:
		FontSystem();
		~FontSystem();

		BOOL	Initialize( ID3D11Device* pDevice );
		void	Finalize();


		//	フォント書き込み用動的頂点バッファの取得
		VertexBuffer&	GetFontVertexBuffer()		{		return m_VtxBuff;	}


		void			SetupStates( DeviceContext * ctx );

		VertexShader&	GetVertexShader()	{	return m_VertexShader;	}
		PixelShader&	GetPixelShader()	{	return m_PixelShader;	}
		BlendState&		GetBlendState()		{	return m_BlendState;	}	//!<	通常のブレンドステート
		InputLayout&	GetInputLayout()	{	return m_InputLayout;	}	//!<	入力レイアウト


	private:


		D3DPtr< ID3D11Device >	m_pD3DDevice;

		VertexShader			m_VertexShader;
		PixelShader				m_PixelShader;
		BlendState				m_BlendState;		//!<	通常のブレンドステート
		DepthStencilState		m_DepthStencilState;
		RasterizerState			m_RasterState;
		InputLayout				m_InputLayout;		//!<	入力レイアウト
		SamplerState			m_SamplerState;

		VertexBuffer			m_VtxBuff;			//!<	フォント書き込み用動的頂点バッファ

	};




}


