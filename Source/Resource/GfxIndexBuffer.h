#pragma once
#include <Util\GfxD3DPtr.h>

namespace GfxLib
{

	class IndexBuffer
	{

	public:
		IndexBuffer( );
		~IndexBuffer();

		operator ID3D11Buffer*	const()	{	return m_pIndexBuffer;	}


		BOOL InitializeImmutable( ID3D11Device *  , const void* pdata , unsigned int size );
		void Finalize();

	private:
		D3DPtr<ID3D11Device>	m_pd3dDev;

		D3DPtr<ID3D11Buffer>	m_pIndexBuffer;
	};
}

