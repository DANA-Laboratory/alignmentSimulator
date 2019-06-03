#include <feetcorrection.h>
feetcorrection::feetcorrection(InitParams mInitParams,float* clockVal)
{
	
	if(mInitParams.mSolveType==SolveTypeRever)
	{
		//reverse math
		//a driver length (in)
		//e driven length (in)
		//b driver front feet to clock (in)
		//c between clocks (in)
		//d driven front feet to clock (in)
		//x one half of driver rim reading (mils)
		//y one half of driven rim reading (mils)	
		float a=mInitParams.Rrear;
		float e=mInitParams.Nrear;
		float b=mInitParams.RShlenght+mInitParams.NShlenght/2.0+mInitParams.ShaftEndGap-(mInitParams.NClockPOsitionOnShaft+mInitParams.Hcsize);
		float c=b-mInitParams.RClockPOsitionOnShaft+mInitParams.Hcsize-mInitParams.RShlenght/2.0;
		float d=mInitParams.NShlenght+mInitParams.RShlenght/2.0+mInitParams.ShaftEndGap-(mInitParams.RClockPOsitionOnShaft+mInitParams.Hcsize);
		float x[2]={(clockVal[1]-clockVal[5])/2.0,(clockVal[3]-clockVal[7])/2.0};
		float y[2]={(clockVal[4]-clockVal[0])/2.0,(clockVal[6]-clockVal[2])/2.0};
		for (int ii=0;ii<2;ii++)
		{
			InboardFeetOfDriver[ii]=inver_InboardFeetOfDriver(b,c,x[ii],y[ii]);
			OutboardFeetOfDriver[ii]=inver_OutboardFeetOfDriver(a,b,c,x[ii],y[ii]);
			InboardFeetOfDriven[ii]=inver_InboardFeetOfDriven(c,d,x[ii],y[ii]);
			OutboardFeetOfDriven[ii]=inver_OutboardFeetOfDriven(c,d,e,x[ii],y[ii]);
		}
	}
	else
		if(mInitParams.mSolveType==SolveTypeDouble)
	{
		//a driver length (in)
		//e driven length (in)
		//b driver front feet to first clock (in)
		//c between clocks (in)
		//d driven front feet to second clock (in)
		//n one half of near nim reading (mils)
		//f one half of far rim reading (mils)		
		float c=mInitParams.AdDblHcsize;
		float a=mInitParams.Rrear;
		float e=mInitParams.Nrear;
		float b=mInitParams.RShlenght/2.0+mInitParams.RClockPOsitionOnShaft+mInitParams.Hcsize;
		float d=mInitParams.RShlenght+mInitParams.NShlenght+mInitParams.ShaftEndGap-b-mInitParams.AdDblHcsize;
		float f[2]={(clockVal[5]-clockVal[1])/2.0,(clockVal[7]-clockVal[3])/2.0};
		float n[2]={(clockVal[4]-clockVal[0])/2.0,(clockVal[6]-clockVal[2])/2.0};
		for (int ii=0;ii<2;ii++)
		{
			InboardFeetOfDriver[ii]=doublerad_InboardFeetOfDriver(f[ii],n[ii],c,b);
			OutboardFeetOfDriver[ii]=doublerad_OutboardFeetOfDriver(f[ii],n[ii],c,a,b);
			InboardFeetOfDriven[ii]=doublerad_InboardFeetOfDriven(f[ii],n[ii],c,d);
			OutboardFeetOfDriven[ii]=doublerad_OutboardFeetOfDriven(f[ii],n[ii],c,d,e);
		}
	}
	else
		if(mInitParams.mSolveType==SolveTypeSpool)
	{
		float a=mInitParams.Nrear;
		float g=mInitParams.Rrear;
		float b=mInitParams.NShlenght;
		float f=mInitParams.RShlenght;
		float c=mInitParams.Hcsize-mInitParams.NShlenght/2.0+mInitParams.NClockPOsitionOnShaft;
		float e=mInitParams.Hcsize-mInitParams.RShlenght/2.0+mInitParams.RClockPOsitionOnShaft;
		float d=mInitParams.ShaftEndGap+mInitParams.RShlenght+mInitParams.NShlenght-b-c-e-f;
		float x[2]={(clockVal[5]-clockVal[1])/2.0,(clockVal[7]-clockVal[3])/2.0};
		float y[2]={(clockVal[4]-clockVal[0])/2.0,(clockVal[6]-clockVal[2])/2.0};
		for (int ii=0;ii<2;ii++)
		{			
			InboardFeetOfDriver[ii]=shftTspool_InboardFeetOfDriver(c,d,e,f,x[ii],y[ii]);
			OutboardFeetOfDriver[ii]=shftTspool_OutboardFeetOfDriver(c,d,e,f,g,x[ii],y[ii]);
			InboardFeetOfDriven[ii]=shftTspool_InboardFeetOfDriven(b,c,d,e,x[ii],y[ii]);
			OutboardFeetOfDriven[ii]=shftTspool_OutboardFeetOfDriven(a,b,c,d,e,x[ii],y[ii]);
		}
	}
	else
		if(mInitParams.mSolveType==SolveTypeFaceRim)
	{
		float h=2.0*mInitParams.VFacecsize;//diameter of face reading
		float a=mInitParams.Rrear;
		float e=mInitParams.Nrear;
		float c=mInitParams.Hcsize;
		float b=mInitParams.RClockPOsitionOnShaft+mInitParams.RShlenght/2.0;
		float d=mInitParams.ShaftEndGap+mInitParams.RShlenght+mInitParams.NShlenght-c-b;
		float f[2]={(clockVal[1]-clockVal[5]),(clockVal[3]-clockVal[7])};
		float y[2]={(clockVal[4]-clockVal[0])/2.0,(clockVal[6]-clockVal[2])/2.0};

		for (int ii=0;ii<2;ii++)
		{
			InboardFeetOfDriver[ii]=facerim_InboardFeetOfDriver(b,c,f[ii],y[ii],h);
			OutboardFeetOfDriver[ii]=facerim_OutboardFeetOfDriver(f[ii],a,b,c,h,y[ii]);
			InboardFeetOfDriven[ii]=facerim_InboardFeetOfDriven(f[ii],d,h,y[ii]);
			OutboardFeetOfDriven[ii]=facerim_OutboardFeetOfDriven(d,e,f[ii],h,y[ii]);
		}
	}
	InboardFeetOfDriver[0]=(InboardFeetOfDriver[0]<ERR && InboardFeetOfDriver[0]>-ERR) ? 0:InboardFeetOfDriver[0];
	OutboardFeetOfDriver[0]=(OutboardFeetOfDriver[0]<ERR && OutboardFeetOfDriver[0]>-ERR) ? 0:OutboardFeetOfDriver[0];
	InboardFeetOfDriven[0]=(InboardFeetOfDriven[0]<ERR && InboardFeetOfDriven[0]>-ERR) ? 0:InboardFeetOfDriven[0];
	OutboardFeetOfDriven[0]=(OutboardFeetOfDriven[0]<ERR && OutboardFeetOfDriven[0]>-ERR) ? 0:OutboardFeetOfDriven[0];
	InboardFeetOfDriver[1]=(InboardFeetOfDriver[1]<ERR && InboardFeetOfDriver[1]>-ERR) ? 0:InboardFeetOfDriver[1];
	OutboardFeetOfDriver[1]=(OutboardFeetOfDriver[1]<ERR && OutboardFeetOfDriver[1]>-ERR) ? 0:OutboardFeetOfDriver[1];
	InboardFeetOfDriven[1]=(InboardFeetOfDriven[1]<ERR && InboardFeetOfDriven[1]>-ERR) ? 0:InboardFeetOfDriven[1];
	OutboardFeetOfDriven[1]=(OutboardFeetOfDriven[1]<ERR && OutboardFeetOfDriven[1]>-ERR) ? 0:OutboardFeetOfDriven[1];
}
float feetcorrection::inver_InboardFeetOfDriver(float b,float c,float x,float y)
{
	return((b+c)*(x+y)/c-y);
};
float feetcorrection::inver_OutboardFeetOfDriver(float a,float b,float c,float x,float y)
{
	return((a+b+c)*(x+y)/c-y);
};
float feetcorrection::inver_InboardFeetOfDriven(float c,float d,float x,float y)
{
	return((d+c)*(x+y)/c-x);
};
float feetcorrection::inver_OutboardFeetOfDriven(float c,float d,float e,float x,float y)
{
	return((c+d+e)*(x+y)/c-x);
};
//face rim math
//a driver length (in)
//e driven length (in)
//b driver front feet to clock clamp (in)
//c between clocks (in)
//d driven front feet to clock (in)
//x face reading (mils)
//y one half of rim reading (mils)

float feetcorrection::facerim_InboardFeetOfDriver(const float b,const float c,const float f,const float y,const float h)
{
	return((b+c)*f/h-y);
};
float feetcorrection::facerim_OutboardFeetOfDriver(const float f,const float a,const float b,const float c,const float h,const float y)
{
	return(f*(a+b+c)/h-y);
};
float feetcorrection::facerim_InboardFeetOfDriven(const float f,const float d,const float h,const float y)
{
	return(f*d/h+y);
};
float feetcorrection::facerim_OutboardFeetOfDriven(const float d,const float e,const float f,const float h,const float y)
{
	return((d+e)*f/h+y);
};
//************
float feetcorrection::doublerad_InboardFeetOfDriver(float f,float n,float c,float b)
{
	return((b+c)*(f-n)/c-f);
};
float feetcorrection::doublerad_OutboardFeetOfDriver(float f,float n,float c,float a,float b)
{
	return((a+b+c)*(f-n)/c-f);
};
float feetcorrection::doublerad_InboardFeetOfDriven(float f,float n,float c,float d)
{
	return((c+d)*(f-n)/c+n);
};
float feetcorrection::doublerad_OutboardFeetOfDriven(float f,float n,float c,float d,float e)
{
	return((c+d+e)*(f-n)/c+n);
};
//shaft to spool
//a driver length (in)
//g driven length (in)
//b driver front feet to spool (in)
//d between clocks (in)
//c spool to clock (in)
//e spool to clock (in)
//f driver front to spool (in)
//x half of driven to spool rim (mils)
//y half of driver to spool rim (mils)
float feetcorrection::shftTspool_InboardFeetOfDriver(float c,float d,float e,float f,float x,float y)
{
	return((c+d+e+f)*x/c+f*(y/e));
};
float feetcorrection::shftTspool_OutboardFeetOfDriver(float c,float d,float e,float f,float g,float x,float y)
{
	return((c+d+e+f+g)*x/c+(f+g)*(y/e));
};
float feetcorrection::shftTspool_InboardFeetOfDriven(float b,float c,float d,float e,float x,float y)
{
	return((b+c+d+e)*y/e+b*(x/c));
};
float feetcorrection::shftTspool_OutboardFeetOfDriven(float a,float b,float c,float d,float e,float x,float y)
{
	return((a+b+c+d+e)*y/e+(a+b)*(x/c));
};

