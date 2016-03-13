#pragma		once


/*

	
	�J�����̎p�������`��s��v�Z�ɕK�v�ȏ����J�v�Z��������
	�����܂ŃJ�����̏��������Ă��邾���ł���A�r���[�|�[�g�J�����O�Ȃǂ͕ʂ̃N���X�ōs��


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

		int				m_Width;		//	�r���[�|�[�g�T�C�Y
		int				m_Height;		//	�r���[�|�[�g����



	};








}




