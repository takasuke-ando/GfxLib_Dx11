







#include "stdafx.h"

#include "GfxCamera.h"




namespace GfxLib
{



	Camera::Camera()
	{
		m_CameraPosture = XMMatrixIdentity();
		m_fNear = 0.1f;
		m_fFar = 1000.f;
		m_fFov = XMConvertToRadians( 45.f );
		m_Width =1280;
		m_Height = 720;
	}



	Camera::~Camera()
	{

		

	}



	/*

		プロジェクション行列を計算する

	*/
	XMMATRIX	Camera::ComputeProjMatrix() const
	{

		return XMMatrixPerspectiveFovLH( m_fFov , m_Width / (float)m_Height , m_fNear , m_fFar );

	}


	/*

		ビューマトリクスを計算する

	*/
	XMMATRIX	Camera::ComputeViewMatrix() const
	{
		XMVECTOR det;
		return XMMatrixInverse( &det , m_CameraPosture );
	}





}



