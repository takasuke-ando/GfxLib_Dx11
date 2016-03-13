



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


	���������s��


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

	�\�����o�b�t�@�Ƃ��ď���������

	uElementSize:			��v�f�̃T�C�Y
	uElementNum:			�v�f��
	AdditionalBindFlags:	�ǉ��̃o�C���h�t���O�B���_�o�b�t�@��V�F�[�_�[���\�[�X�Ƃ��čė��p����ꍇ�Ɏg�p����
	pInitData:				�������f�[�^�i�I�v�V�����j�B�w�肷��ꍇ��uElementSize * uElementNum �o�C�g�̃T�C�Y


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

	Raw�o�b�t�@�Ƃ��ď���������

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


	DispatchIndirect , Draw***Indirect�Ȃǂ̃��\�b�h�Ŏg�����Ƃ��\��
	�����o�b�t�@�Ƃ��ăo�b�t�@������������
	CopyStructureCount�Ȃǂ��g�p���ăo�b�t�@�J�E���^��UAV����R�s�[����


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



