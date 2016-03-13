




#include "stdafx.h"

#include "GfxDrawContext.h"




namespace GfxLib
{



	DrawContext::DrawContext( DeviceContext& dev )
		:m_DeviceContext( dev )
	{

	}


	DrawContext::~DrawContext()
	{

	}


	BOOL	DrawContext::Initialize( DeviceContext& deviceContext )
	{



		return TRUE;
	}


	void	DrawContext::Finalize()
	{

	}








}





