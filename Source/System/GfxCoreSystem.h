#pragma once


namespace GfxLib
{

	class CoreSystem
	{
	public:
		CoreSystem();
		~CoreSystem();


		BOOL	Initialize();
		void	Finalize();

		void	Update();

		ID3D11Device*			GetD3DDevice()			const	{	return m_pd3dDev;	}
		ID3D11DeviceContext*	GetImmediateContext()	const	{	return m_pImmedisateContext;	}

		float		GetFps()	const	{	return m_fFps;	}

	private:
		ID3D11Device* m_pd3dDev;
		ID3D11DeviceContext* m_pImmedisateContext;
		D3D_FEATURE_LEVEL	m_featureLevel;
		D3D_DRIVER_TYPE		m_driverType;


		UINT				m_nUpdateCount;
		UINT				m_nFrameCount;
		LARGE_INTEGER		m_lastFpsUpdateTime;
		float				m_fFps;

	};


}



