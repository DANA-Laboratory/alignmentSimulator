#include <problem.h>
class feetcorrection
{
	public:
		feetcorrection(InitParams mInitParams,float* clockVal);
		float InboardFeetOfDriver[2];
		float OutboardFeetOfDriver[2];
		float InboardFeetOfDriven[2];
		float OutboardFeetOfDriven[2];
	private:
		float inver_InboardFeetOfDriver(float b,float c,float x,float y);
		float inver_OutboardFeetOfDriver(float a,float b,float c,float x,float y);
		float inver_InboardFeetOfDriven(float c,float d,float x,float y);
		float inver_OutboardFeetOfDriven(float c,float d,float e,float x,float y);
		float facerim_InboardFeetOfDriver(const float b,const float c,const float f,const float y,const float h);
		float facerim_OutboardFeetOfDriver(const float f,const float a,const float b,const float c,const float h,const float y);
		float facerim_InboardFeetOfDriven(const float f,const float d,const float h,const float y);
		float facerim_OutboardFeetOfDriven(const float d,const float e,const float f,const float h,const float y);
		float doublerad_InboardFeetOfDriver(float f,float n,float c,float b);
		float doublerad_OutboardFeetOfDriver(float f,float n,float c,float a,float b);
		float doublerad_InboardFeetOfDriven(float f,float n,float c,float d);
		float doublerad_OutboardFeetOfDriven(float f,float n,float c,float d,float e);
		float shftTspool_InboardFeetOfDriver(float c,float d,float e,float f,float x,float y);
		float shftTspool_OutboardFeetOfDriver(float c,float d,float e,float f,float g,float x,float y);
		float shftTspool_InboardFeetOfDriven(float b,float c,float d,float e,float x,float y);
		float shftTspool_OutboardFeetOfDriven(float a,float b,float c,float d,float e,float x,float y);
};
