#pragma			once



/*

	シャドウマップリソースをカプセル化する

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