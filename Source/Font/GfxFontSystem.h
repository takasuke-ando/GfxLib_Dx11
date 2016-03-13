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


		//	�t�H���g�������ݗp���I���_�o�b�t�@�̎擾
		VertexBuffer&	GetFontVertexBuffer()		{		return m_VtxBuff;	}


		void			SetupStates( DeviceContext * ctx );

		VertexShader&	GetVertexShader()	{	return m_VertexShader;	}
		PixelShader&	GetPixelShader()	{	return m_PixelShader;	}
		BlendState&		GetBlendState()		{	return m_BlendState;	}	//!<	�ʏ�̃u�����h�X�e�[�g
		InputLayout&	GetInputLayout()	{	return m_InputLayout;	}	//!<	���̓��C�A�E�g


	private:


		D3DPtr< ID3D11Device >	m_pD3DDevice;

		VertexShader			m_VertexShader;
		PixelShader				m_PixelShader;
		BlendState				m_BlendState;		//!<	�ʏ�̃u�����h�X�e�[�g
		DepthStencilState		m_DepthStencilState;
		RasterizerState			m_RasterState;
		InputLayout				m_InputLayout;		//!<	���̓��C�A�E�g
		SamplerState			m_SamplerState;

		VertexBuffer			m_VtxBuff;			//!<	�t�H���g�������ݗp���I���_�o�b�t�@

	};




}


