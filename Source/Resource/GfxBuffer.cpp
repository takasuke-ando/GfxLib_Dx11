



#include "stdafx.h"
#include "GfxBuffer.h"




namespace GfxLib
{



Buffer::Buffer()
{

}


Buffer::~Buffer()
{
	Finalize();
}


void	Buffer::Finalize()
{

	m_pD3DDevice = NULL;
	m_pBuffer = NULL;

}



/*


	初期化を行う


*/


BOOL	Buffer::Initialize(
	ID3D11Device*	pDevice,
	const D3D11_BUFFER_DESC &Desc,
	const D3D11_SUBRESOURCE_DATA *pInitialData )
{
	Finalize();

	HRESULT hr = pDevice->CreateBuffer( &Desc , pInitialData , m_pBuffer.InitialAccept() );

	if ( SUCCEEDED( hr ) ) 
	{
		m_pD3DDevice = pDevice;
		return TRUE;
	}

	return FALSE;

}



/*

	構造化バッファとして初期化する

	uElementSize:			一要素のサイズ
	uElementNum:			要素数
	AdditionalBindFlags:	追加のバインドフラグ。頂点バッファやシェーダーリソースとして再利用する場合に使用する
	pInitData:				初期化データ（オプション）。指定する場合はuElementSize * uElementNum バイトのサイズ


*/
BOOL	Buffer::InitializeStructuredBuffer(
	ID3D11Device*	pDevice,
	UINT uElementSize,
	UINT uElementNum,
	UINT AdditionalBindFlags /* = 0 */ , 
	const VOID* pInitData    /* = NULL */

	)
{

	D3D11_BUFFER_DESC	desc;
	ZeroMemory( &desc , sizeof( desc ) );

	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_UNORDERED_ACCESS | AdditionalBindFlags;
	desc.ByteWidth = uElementSize * uElementNum;
	desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	desc.StructureByteStride = uElementSize;


	if ( pInitData )
	{
		D3D11_SUBRESOURCE_DATA InitData  = {0};
		InitData.pSysMem = pInitData;

		return Initialize( pDevice , desc , &InitData );

	}else {

		return Initialize( pDevice , desc , NULL );

	}


}



/*

	Rawバッファとして初期化する

*/
BOOL	Buffer::InitializeRawBuffer(
	ID3D11Device*	pDevice,
	UINT uSize,
	UINT AdditionalBindFlags /*= 0*/ , 
	const VOID* pInitData /*= NULL */
	)
{


	D3D11_BUFFER_DESC	desc;
	ZeroMemory( &desc , sizeof( desc ) );

	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_UNORDERED_ACCESS | AdditionalBindFlags;
	desc.ByteWidth = uSize;
	desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS;


	if ( pInitData )
	{
		D3D11_SUBRESOURCE_DATA InitData  = {0};
		InitData.pSysMem = pInitData;

		return Initialize( pDevice , desc , &InitData );

	}else {

		return Initialize( pDevice , desc , NULL );

	}




}



/*


	DispatchIndirect , Draw***Indirectなどのメソッドで使うことが可能な
	引数バッファとしてバッファを初期化する
	CopyStructureCountなどを使用してバッファカウンタをUAVからコピーする


*/
BOOL	Buffer::InitializeIndirectArgsBuffer(
	ID3D11Device* pDevice , 
	UINT uByteSize , 
	UINT AdditionalBindFlags /* = 0 */ ,
	const VOID* pInitData /* = NULL */
	)
{

	D3D11_BUFFER_DESC	desc;
	ZeroMemory( &desc , sizeof( desc ) );

	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = AdditionalBindFlags;
	desc.ByteWidth = uByteSize;
	desc.MiscFlags = D3D11_RESOURCE_MISC_DRAWINDIRECT_ARGS;

	if ( AdditionalBindFlags & D3D11_BIND_UNORDERED_ACCESS )
	{
		desc.MiscFlags |= D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS;
	}

	if ( pInitData )
	{
		D3D11_SUBRESOURCE_DATA InitData  = {0};
		InitData.pSysMem = pInitData;

		return Initialize( pDevice , desc , &InitData );

	}else {

		return Initialize( pDevice , desc , NULL );

	}

}



}



