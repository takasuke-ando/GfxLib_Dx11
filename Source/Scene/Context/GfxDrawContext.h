#pragma		once
#include "Device\GfxDeviceContext.h"



namespace GfxLib
{


	class DrawContext
	{

	public:
		DrawContext( DeviceContext& dev );
		~DrawContext();


		BOOL	Initialize( DeviceContext& deviceContext );
		void	Finalize();

	private:

		 DeviceContext&		m_DeviceContext ;


	};






}




