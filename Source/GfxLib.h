// GfxLib.h

#pragma once

#include <assert.h>


#define		GFX_RELEASE( ptr )		if ( ptr )	{	(ptr)->Release(); (ptr)=NULL;	}

#define		GFX_ASSERT( exp , ... )		{	assert(exp);	}



