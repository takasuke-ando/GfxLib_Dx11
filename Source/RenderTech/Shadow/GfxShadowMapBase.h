#pragma			once



/*

	�V���h�E�}�b�v���\�[�X���J�v�Z��������

*/



namespace GfxLib
{

class		ShadowMapBase
{
public:
	ShadowMapBase();
	virtual ~ShadowMapBase();


	virtual void	BeginMakeShadowMap();
	virtual void	EndMakeShadowMap();


};


}