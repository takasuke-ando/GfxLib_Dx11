



#include "stdafx.h"

#include "GfxIndexBuffer.h"



namespace GfxLib
{

	IndexBuffer::IndexBuffer( )
	{


	}

	IndexBuffer::~IndexBuffer()
	{
		Finalize();
	}

	/*
		•ÏX•s‰Â‚Æ‚µ‚Ä‰Šú‰»‚·‚é
	*/
	BOOL	IndexBuffer::InitializeImmutable( ID3D11Device *dev , const void* pdata , unsigned int size )
	{
		Finalize();
		
		m_pd3dDev = dev;

		D3D11_BUFFER_DESC bd = {0};

		bd.Usage = D3D11_USAGE_IMMUTABLE;
		bd.CPUAccessFlags = 0;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.ByteWidth = size;

		D3D11_SUBRESOURCE_DATA res = {0};
		res.pSysMem = pdata;
	
		HRESULT hr = m_pd3dDev->CreateBuffer( &bd , &res , m_pIndexBuffer.InitialAccept() );


		return SUCCEEDED( hr );

	}


	void IndexBuffer::Finalize()
	{

		m_pd3dDev = NULL;
		m_pIndexBuffer = NULL;
	}


}

