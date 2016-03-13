#pragma once
#include "GfxShadowMapBase.h"

#include "Resource\GfxDepthStencil.h"
#include "Resource\GfxShaderResourceView.h"
#include "Resource\GfxTeture2D.h"


/*

	シャドウマップリソースをカプセル化する
	このクラスはシンプルな深度テクスチャのみを持つバッファをカプセル化する

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
	

	//RenderTarget	m_ColorTarget;			//!<	カラーターゲット。要らない？
	DepthStencil		m_DepthStencil;		//!<	深度バッファ
	ShaderResourceView	m_DepthSRV;
	Texture2D			m_DepthTexture;		//!<	バッファ



};



};
