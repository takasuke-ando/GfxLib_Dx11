


#include "stdafx.h"


#include "GfxInputLayout.h"
#include "../Shader/GfxVertexShader.h"


namespace GfxLib
{


InputLayout::InputLayout( )
	:m_pd3dDev( NULL )
	,m_pInputLayout( NULL )
{


}


InputLayout::~InputLayout()
{
// 
// 	GFX_RELEASE( m_pd3dDev );
// 	GFX_RELEASE( m_pInputLayout );
	Finalize();
}


BOOL	InputLayout::Initialize( ID3D11Device* dev, const D3D11_INPUT_ELEMENT_DESC *layout ,  UINT layoutNum , 
	const VertexShader *vertexBuffer )
{
	//GFX_RELEASE( m_pInputLayout );
	m_pInputLayout = NULL;

	m_pd3dDev = dev;

	HRESULT hr = m_pd3dDev->CreateInputLayout(
		layout , layoutNum , 
		vertexBuffer->GetBufferPointer() , vertexBuffer->GetBufferSize() ,
		m_pInputLayout.InitialAccept() );


	return SUCCEEDED( hr );

}

void	InputLayout::Finalize()
{


	m_pd3dDev = NULL;
	m_pInputLayout = NULL;

}



}


