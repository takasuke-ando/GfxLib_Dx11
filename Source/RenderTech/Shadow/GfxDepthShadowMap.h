#pragma once
#include "GfxShadowMapBase.h"

#include "Resource\GfxDepthStencil.h"
#include "Resource\GfxShaderResourceView.h"
#include "Resource\GfxTeture2D.h"


/*

	�V���h�E�}�b�v���\�[�X���J�v�Z��������
	���̃N���X�̓V���v���Ȑ[�x�e�N�X�`���݂̂����o�b�t�@���J�v�Z��������

*/


namespace GfxLib
{




class DepthShadowMap :
	public ShadowMapBase
{

public:
	DepthShadowMap();
	virtual ~DepthShadowMap();


	BOOL		Initialize( ID3D11Device *pDev , UINT width , UINT height , DXGI_FORMAT depthFormat = DXGI_FORMAT_D24_UNORM_S8_UINT );
	void		Finalize();


private:
	

	//RenderTarget	m_ColorTarget;			//!<	�J���[�^�[�Q�b�g�B�v��Ȃ��H
	DepthStencil		m_DepthStencil;		//!<	�[�x�o�b�t�@
	ShaderResourceView	m_DepthSRV;
	Texture2D			m_DepthTexture;		//!<	�o�b�t�@



};



};
