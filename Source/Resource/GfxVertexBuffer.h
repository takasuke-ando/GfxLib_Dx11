#pragma once
#include "Util\GfxD3DPtr.h"

namespace GfxLib
{

	class VertexBuffer
	{

	public:
		VertexBuffer();
		~VertexBuffer();

		BOOL	InitializeImmutable( ID3D11Device * pDevice , const void* pdata , unsigned int size );
		BOOL	InitializeDynamic( ID3D11Device * pDevice , unsigned int size );
		void	Finalize();

		UINT	GetBufferSize()	const	{	return m_nBufferSize;	}


		operator ID3D11Buffer	*()	const		{	return m_pVertexBuffer;	}

	private:


		D3DPtr< ID3D11Device > m_pd3dDev;
		D3DPtr< ID3D11Buffer > m_pVertexBuffer;

		UINT	m_nBufferSize;
	};
}

