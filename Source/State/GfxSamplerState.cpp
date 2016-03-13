

#include "stdafx.h"


#include "GfxSamplerState.h"





namespace GfxLib
{



	SamplerState::SamplerState( )
		:m_pd3dDev( NULL )
		,m_pSamplerState( NULL )
	{



	}
	SamplerState::~SamplerState()
	{
		Finalize();
	}


	BOOL	SamplerState::Initialize( ID3D11Device* pdev, const D3D11_SAMPLER_DESC &bd )
	{

		GFX_RELEASE( m_pSamplerState );
		HRESULT hr = pdev->CreateSamplerState( &bd , m_pSamplerState.InitialAccept() );

		if ( FAILED( hr ) ) 
			return FALSE;

		m_pd3dDev = pdev;

		return TRUE;

	}

	void	SamplerState::Finalize()
	{
		m_pd3dDev = NULL;
		m_pSamplerState = NULL;
	}



	/*

		デフォルトの設定を返す
		SetSamplerState( NULL )を行ったときと同じ情報を返すようにしている

	*/
	D3D11_SAMPLER_DESC	SamplerState::GetDefaultDesc()
	{
		D3D11_SAMPLER_DESC desc;
		ZeroMemory( &desc , sizeof( desc ) );


		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR    ;
		desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP    ;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.MinLOD   = (-FLT_MAX) ;
		desc.MaxLOD = (FLT_MAX) ;
		desc.MipLODBias = 0.f;
		desc.MaxAnisotropy = 16;
		desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		//desc.BorderColor = float4(0.0f,0.0f,0.0f,0.0f) 


		return desc;


	}

}
