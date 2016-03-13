
#include "stdafx.h"


#include "GfxUnorderedAccessView.h"




namespace GfxLib
{





UnorderedAccessView::UnorderedAccessView()
{

}



UnorderedAccessView::~UnorderedAccessView()
{
	Finalize();
}



/*

	UAVをバッファから初期化する

*/
BOOL	UnorderedAccessView::InitializeBuffer( ID3D11Device* pDevice , ID3D11Buffer *pBuffer )
{
	Finalize();

	D3D11_BUFFER_DESC descBuf;
	ZeroMemory( &descBuf, sizeof(descBuf) );
	pBuffer->GetDesc( &descBuf );

	D3D11_UNORDERED_ACCESS_VIEW_DESC desc;
	ZeroMemory( &desc, sizeof(desc) );
	desc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
	desc.Buffer.FirstElement = 0;

	if ( descBuf.MiscFlags & D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS )
	{
		// This is a Raw Buffer
		desc.Format = DXGI_FORMAT_R32_TYPELESS; // Format must be DXGI_FORMAT_R32_TYPELESS, when creating Raw Unordered Access View
		desc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_RAW;
		desc.Buffer.NumElements = descBuf.ByteWidth / 4; 
	} else if ( descBuf.MiscFlags & D3D11_RESOURCE_MISC_BUFFER_STRUCTURED )
	{
		// This is a Structured Buffer
		desc.Format = DXGI_FORMAT_UNKNOWN;      // Format must be must be DXGI_FORMAT_UNKNOWN, when creating a View of a Structured Buffer
		desc.Buffer.NumElements = descBuf.ByteWidth / descBuf.StructureByteStride; 
	} else
	{
		GFX_ASSERT( 0 , "Invalid parameter" );
		return FALSE;
	}

	HRESULT hr = pDevice->CreateUnorderedAccessView( pBuffer, &desc, m_pUAV.InitialAccept() );


	if ( SUCCEEDED( hr ) ) 
	{
		m_pD3DDevice = pDevice;
		return TRUE;
	}

	return FALSE;


}

/*

	AppendStructuredBufferとして使える形で初期化する


*/
BOOL	UnorderedAccessView::InitializeAppendableBuffer( ID3D11Device* pDevice , ID3D11Buffer *pBuffer )
{
	Finalize();

	D3D11_BUFFER_DESC descBuf;
	ZeroMemory( &descBuf, sizeof(descBuf) );
	pBuffer->GetDesc( &descBuf );

	D3D11_UNORDERED_ACCESS_VIEW_DESC desc;
	ZeroMemory( &desc, sizeof(desc) );
	desc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
	desc.Buffer.FirstElement = 0;


	/*
	RawバッファではAppend可能なバッファは作成できない
	if ( descBuf.MiscFlags & D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS )
	{
		// This is a Raw Buffer
		desc.Format = DXGI_FORMAT_R32_TYPELESS; // Format must be DXGI_FORMAT_R32_TYPELESS, when creating Raw Unordered Access View
		desc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_RAW | D3D11_BUFFER_UAV_FLAG_APPEND;
		desc.Buffer.NumElements = descBuf.ByteWidth / 4; 
	} else	
	*/
	if ( descBuf.MiscFlags & D3D11_RESOURCE_MISC_BUFFER_STRUCTURED )
	{
		// This is a Structured Buffer
		desc.Format = DXGI_FORMAT_UNKNOWN;      // Format must be must be DXGI_FORMAT_UNKNOWN, when creating a View of a Structured Buffer
		desc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_APPEND;
		desc.Buffer.NumElements = descBuf.ByteWidth / descBuf.StructureByteStride; 
	} else
	{
		GFX_ASSERT( 0 , "Invalid parameter" );
		return FALSE;
	}

	HRESULT hr = pDevice->CreateUnorderedAccessView( pBuffer, &desc, m_pUAV.InitialAccept() );


	if ( SUCCEEDED( hr ) ) 
	{
		m_pD3DDevice = pDevice;
		return TRUE;
	}

	GFX_ASSERT( 0 , "Failed UAV Creation" );
	return FALSE;




}



/*


	RWTexture2Dとしてコンピュートシェーダにバインドされる

*/
BOOL	UnorderedAccessView::InitializeTexture2D( ID3D11Device* pDevice , ID3D11Texture2D *pBuffer , DXGI_FORMAT format ,  UINT mipSlice )
{
	Finalize();


// 	D3D11_TEXTURE2D_DESC descBuf;
// 	ZeroMemory( &descBuf, sizeof(descBuf) );
// 	pBuffer->GetDesc( &descBuf );

	D3D11_UNORDERED_ACCESS_VIEW_DESC desc;
	ZeroMemory( &desc, sizeof(desc) );
	desc.Format = format;
	desc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;
	desc.Texture2D.MipSlice = mipSlice;


	HRESULT hr = pDevice->CreateUnorderedAccessView( pBuffer, &desc, m_pUAV.InitialAccept() );


	if ( SUCCEEDED( hr ) ) 
	{
		m_pD3DDevice = pDevice;
		return TRUE;
	}

	return FALSE;


}



void	UnorderedAccessView::Finalize()
{

	m_pD3DDevice = NULL;
	m_pUAV = NULL;

}




}


