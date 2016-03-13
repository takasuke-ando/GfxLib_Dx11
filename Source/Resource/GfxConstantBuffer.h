#pragma once
#include <Util\GfxD3DPtr.h>


namespace GfxLib
{

	class ConstantBuffer
	{
	public:
		ConstantBuffer(  );
		~ConstantBuffer();


		BOOL	Initialize( ID3D11Device* pdev , unsigned int byteSize , BOOL bIsDynamic = FALSE );
		void	Finalize();

		operator ID3D11Buffer *() const {	return m_pConstantBuffer;	}

		UINT	GetByteSize()	const	{	return m_nByteSize;		}
		BOOL	IsDynamic()		const	{	return m_bIsDynamic;	}


	private:

		D3DPtr< ID3D11Device >	m_pd3dDev;
		D3DPtr< ID3D11Buffer >	m_pConstantBuffer;

		UINT			m_nByteSize;
		BOOL			m_bIsDynamic ;

	};

}