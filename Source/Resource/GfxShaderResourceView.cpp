
/*

	ShaderResourceViewをカプセル化する


*/




#include "stdafx.h"

#include "GfxShaderResourceView.h"
#include "DirectXTK/DDSTextureLoader.h"



namespace GfxLib
{


ShaderResourceView::ShaderResourceView()
	:m_pd3dDev( NULL )
	,m_pShaderResView( NULL )
{

}



ShaderResourceView::~ShaderResourceView()
{

	Finalize();

}


/*

	ファイルから読み込む
	通常、DDSファイルなどから生成する

*/
BOOL ShaderResourceView::InitializeFromFile( ID3D11Device* dev , const wchar_t* filepath )
{
	Finalize();

	m_pd3dDev = dev;
	

	// Load the Texture
	//HRESULT hr = D3DX11CreateShaderResourceViewFromFile( m_pd3dDev, filepath , NULL, NULL, m_pShaderResView.InitialAccept() , NULL );
	HRESULT hr = DirectX::CreateDDSTextureFromFile(m_pd3dDev, filepath,  NULL, m_pShaderResView.InitialAccept());

	return SUCCEEDED(hr);
}



/*

	ID3D11BufferからComputeShaderで使用可能な
	Structured またはRawバッファを作成する

*/
BOOL	ShaderResourceView::InitializeBufferEx(ID3D11Device* pDevice , ID3D11Buffer* pBuffer  )
{
	Finalize();

	D3D11_BUFFER_DESC descBuf;
	ZeroMemory( &descBuf, sizeof(descBuf) );
	pBuffer->GetDesc( &descBuf );


	UINT needFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
	if ( ( descBuf.BindFlags & needFlags ) != needFlags )
	{
		GFX_ASSERT( 0 , "Invalid Bind Flags!" );
		return FALSE;
	}


	D3D11_SHADER_RESOURCE_VIEW_DESC	srvDesc;
	ZeroMemory( &srvDesc , sizeof( srvDesc ) );
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
	srvDesc.BufferEx.FirstElement = 0;



	if ( descBuf.MiscFlags & D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS )
	{
		// This is a Raw Buffer
		srvDesc.Format = DXGI_FORMAT_R32_TYPELESS;
		srvDesc.BufferEx.Flags = D3D11_BUFFEREX_SRV_FLAG_RAW;
		srvDesc.BufferEx.NumElements = descBuf.ByteWidth / 4;
	} else if ( descBuf.MiscFlags & D3D11_RESOURCE_MISC_BUFFER_STRUCTURED )
	{
		// This is a Structured Buffer
		srvDesc.Format = DXGI_FORMAT_UNKNOWN;
		srvDesc.BufferEx.NumElements = descBuf.ByteWidth / descBuf.StructureByteStride;
	} else
	{
		GFX_ASSERT( 0 , "Invalid arg" );
		return FALSE;
	}

	HRESULT hr = pDevice->CreateShaderResourceView( pBuffer, &srvDesc, m_pShaderResView.InitialAccept() );


	if ( SUCCEEDED( hr ) )
	{
		m_pd3dDev = pDevice;
			
		return TRUE;
	}

	return FALSE;
	

}



/*

	Texture2Dリソースを元にリソースビューを作成する

*/
BOOL	ShaderResourceView::InitializeTexture2D( ID3D11Device* pDevice , ID3D11Texture2D* pTexture , DXGI_FORMAT format )
{
	Finalize();


	D3D11_TEXTURE2D_DESC texDesc;
	pTexture->GetDesc( &texDesc );


	D3D11_SHADER_RESOURCE_VIEW_DESC desc;
	ZeroMemory( &desc , sizeof( desc ) );

	desc.Format = format;
	desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	desc.Texture2D.MipLevels = texDesc.MipLevels;
	desc.Texture2D.MostDetailedMip = 0;


	HRESULT hr = pDevice->CreateShaderResourceView( pTexture , &desc , m_pShaderResView.InitialAccept() );

	if ( FAILED( hr ) ) 
	{
		GFX_ASSERT( 0 , "SRV Creation Failed" );
		Finalize();

		return FALSE;
	}



	return TRUE;
}




void	ShaderResourceView::Finalize()
{
	m_pd3dDev = NULL;
	m_pShaderResView = NULL;
}

}
