
/*

	定数バッファをラップ

*/



#include "stdafx.h"


#include "GfxConstantBuffer.h"




namespace GfxLib
{





ConstantBuffer::ConstantBuffer( )
	:m_pd3dDev(NULL)
	,m_pConstantBuffer( NULL )
	,m_nByteSize( 0 )
	,m_bIsDynamic( FALSE )
{

}



ConstantBuffer::~ConstantBuffer()
{
// 	GFX_RELEASE( m_pd3dDev );
// 	GFX_RELEASE( m_pConstantBuffer );
// 	m_nByteSize = 0;
	Finalize();
}



BOOL	ConstantBuffer::Initialize(ID3D11Device* pdev  ,  unsigned int byteSize , BOOL bIsDynamic )
{

	/*
		bIsDynamic
			定数バッファをDynamicとして使用する
			動きはするがあまり効率的ではないはず

	*/


	Finalize();

	D3D11_BUFFER_DESC bd = {0};
	bd.ByteWidth = byteSize;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	if ( bIsDynamic )
	{
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}else{
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.CPUAccessFlags = 0;
	}
	
	m_nByteSize = byteSize;
	m_bIsDynamic = bIsDynamic;

	HRESULT hr = pdev->CreateBuffer( &bd , NULL , m_pConstantBuffer.InitialAccept() );

	if (  SUCCEEDED( hr ) )
	{
		m_pd3dDev = pdev;

		return TRUE;
	}

	GFX_ASSERT( 0 , "Create Buffer Failed" );

	return FALSE;
}


void	ConstantBuffer::Finalize()
{
	m_pd3dDev  = NULL;
	m_pConstantBuffer  = NULL;
	m_nByteSize = 0;
}



};