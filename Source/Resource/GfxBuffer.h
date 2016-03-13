#pragma		once
#include <Util\GfxD3DPtr.h>



namespace GfxLib
{

	class	Buffer
	{

	public:
		Buffer();
		~Buffer();


		BOOL	Initialize(
			ID3D11Device*	pDevice,
			const D3D11_BUFFER_DESC &Desc,
			const D3D11_SUBRESOURCE_DATA *pInitialData );

		BOOL	InitializeStructuredBuffer(
			ID3D11Device*	pDevice,
			UINT uElemntSize,
			UINT uElemntNum,
			UINT AdditionalBindFlags = 0 , 
			const VOID* pInitData = NULL
			);
		BOOL	InitializeRawBuffer(
			ID3D11Device*	pDevice,
			UINT uSize,
			UINT AdditionalBindFlags = 0 , 
			const VOID* pInitData = NULL
			);

		BOOL	InitializeIndirectArgsBuffer(
			ID3D11Device* pDevice , 
			UINT uByteSize , 
			UINT AdditionalBindFlags = 0 ,
			const VOID* pInitData = NULL 
			);



		void	Finalize();


		operator ID3D11Buffer*()	{	return m_pBuffer;	}


	private:

		D3DPtr< ID3D11Device >	m_pD3DDevice;
		D3DPtr< ID3D11Buffer >  m_pBuffer;


	};





}


