#pragma		once


/*

	
	カメラの姿勢制御や描画行列計算に必要な情報をカプセル化する
	あくまでカメラの情報を持っているだけであり、ビューポートカリングなどは別のクラスで行う


*/




namespace GfxLib
{



	class Camera
	{
	public:
		Camera();
		~Camera();


		void	SetCameraPosture( const CXMMATRIX mtx ){	m_CameraPosture = mtx;	}
		const XMMATRIX&	GetCameraPosture()		{	return m_CameraPosture;	}


		void	SetViewportSize( int width , int height )	{	m_Width = width ;	m_Height = height;	}



		XMMATRIX	ComputeProjMatrix() const;
		XMMATRIX	ComputeViewMatrix() const;


	private:

		XMMATRIX		m_CameraPosture;

		float			m_fFov;
		float			m_fNear;
		float			m_fFar;

		int				m_Width;		//	ビューポートサイズ
		int				m_Height;		//	ビューポート高さ



	};








}




