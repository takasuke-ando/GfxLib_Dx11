
#include "stdafx.h"

#include "GfxVertexBuffer.h"



namespace GfxLib
{

	VertexBuffer::VertexBuffer()
		:m_pd3dDev( NULL )
		,m_pVertexBuffer( NULL )
		,m_nBufferSize( 0 )
	{

	}

	VertexBuffer::~VertexBuffer()
	{
		Finalize();
	}

	void VertexBuffer::Finalize()
	{
		m_pd3dDev = NULL;
		m_pVertexBuffer = NULL;
		m_nBufferSize = 0;
	}


	/*
		変更不可として初期化する
	*/
	BOOL	VertexBuffer::InitializeImmutable( ID3D11Device * pDevice , const void* pdata , unsigned int size )
	{
		Finalize();

		m_pd3dDev = pDevice;
		m_nBufferSize = size;

		D3D11_BUFFER_DESC bd = {0};

		bd.Usage = D3D11_USAGE_IMMUTABLE;
		bd.CPUAccessFlags = 0;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.ByteWidth = size;

		D3D11_SUBRESOURCE_DATA res = {0};
		res.pSysMem = pdata;
	
		HRESULT hr = m_pd3dDev->CreateBuffer( &bd , &res , m_pVertexBuffer.InitialAccept() );


		return SUCCEEDED( hr );

	}


	/*

		DYNAMICリソースとして初期化する
		Draw***Up系関数のエミュレート、
		CPUで書き込みを行う頂点バッファなどの為に作成する

		D3D11_MAP_WRITE_DISCARD or D3D11_MAP_WRITE_NO_OVERWRITE
	*/

	BOOL	VertexBuffer::InitializeDynamic( ID3D11Device * pDevice , unsigned int size )
	{
		Finalize();

		m_pd3dDev = pDevice;
		m_nBufferSize = size;


		D3D11_BUFFER_DESC bd = {0};

		bd.Usage			= D3D11_USAGE_DYNAMIC;
		bd.CPUAccessFlags	= D3D11_CPU_ACCESS_WRITE;
		bd.BindFlags		= D3D11_BIND_VERTEX_BUFFER;
		bd.ByteWidth		= size;

		
		HRESULT hr = m_pd3dDev->CreateBuffer( &bd , NULL , m_pVertexBuffer.InitialAccept() );


		return SUCCEEDED( hr );

	}



}
