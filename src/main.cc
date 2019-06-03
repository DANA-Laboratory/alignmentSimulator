#include "doMisAlgn.h"
#include <staticConst.h>
#include <LinePlaneInter.cc>
#include <Cgicpphelper.h>
using namespace std;
char* mainpl(char* fname,InitParams mInitParams,float* clockVal);
void readHTMLfile(char* buf);
void readTablesRestriction(char* buf,const char* she,const char* clr);
void readTablesResults(char* buf,const char * res);
static char * buffer;
static size_t buffer_size = 0;
SbVec3f	indicatorDriven(float len,SbVec3f& t,float Nrear,float radius=0,float teta=0);
SbVec3f	indicatorDriver(float len,SbVec3f& t,float radius=0 ,float teta=0);
float	indicPosition(float delta,float teta,float r,float a,float b);
void getParam(char *, char *, char *);
static char buf[40000];
void printHeder();
void printFooter();
static void * buffer_realloc(void * bufptr, size_t size)
{
	buffer = (char *)realloc(bufptr, size);
	buffer_size = size;
	return buffer;
}
struct ClcResult
{
	float rotAngled;
	float rotAngle;
	float iP;
	float iPd;
	float x;
	SbRotation xd;
	float rotAngleFraction;
};
float iP0;
float iPd0;
int Maxindx;
float clockVal[8];
int main()
{  
	putenv(PLPLOT_HOME);
	putenv(PLPLOT_LIB);
	putenv(PLPLOT_DRV_DIR);
	static problem mP;
	//printHeder();
	//printf("getenv=%s",getenv("QUERY_STRING"));
	//printFooter();
	//return 0;

	/*no pass
	Cgicpphelper o;
	if(o.login(mP.SERVER_ADD_login,mP.SERVER_ADD_cgi)==0)
		return 0;
	*/
	static ClcResult* mClcResult;
	static doMisAlgn mdoMisAlgn;
	//char QT[]="http://172.18.1.111/bin/foobar_cpp?ClockScale=1000.0&SolveMethod=3&P_Cat=0&mov_rvr=0.0&mov_rhr=0.0&mov_rvf=0.0&mov_rhf=0.0&mov_nvr=0.0&mov_nhr=0.0&mov_nvf=0.0&mov_nhf=0.0&calcresults_Submit=%D9%86%D9%85%D8%A7%DB%8C%D8%B4+%D9%BE%D8%A7%D8%B3%D8%AE%D9%87%D8%A7%DB%8C+%D9%85%D8%AD%D8%A7%D8%B3%D8%A8%D9%87+%D8%B4%D8%AF%D9%87";
	int errCode=mP.set_QUERY_STRING (getenv("QUERY_STRING"));
	//int errCode=mP.set_QUERY_STRING (QT);
	if (errCode>=100)
	{
		if(errCode<103)
		{
			printHeder();
			printf("no restriction");
			printFooter();
			return(errCode);//no restriction
		}
		printf("Content-type: text/html\n\n");
		readTablesRestriction(buf,mP.she[errCode-103],mP.clr[errCode-103]);
		printf("%s",buf);
		return(errCode);
	};
	if (errCode==-1 || errCode==1 || errCode==2 || errCode==-2)//image//defualt//move ok//results
	{
		mP.mInitParams.ShaftEndGap=0.1;
		if(mP.mInitParams.mSolveType==SolveTypeSpool || mP.mInitParams.mSolveType==SolveTypeFaceRim)
		{
			mP.mInitParams.ShaftEndGap+=1.0;
			mP.mInitParams.RShlenght-=0.5;
			mP.mInitParams.NShlenght-=0.5;
			if(mP.mInitParams.mSolveType==SolveTypeFaceRim)
			{
				mP.mInitParams.FlangToShaftFraction*=2.0;
				mP.mInitParams.Vcsize*=1.4;
			}
		}
		if(mP.mInitParams.mSolveType==SolveTypeDouble)
		{
			mP.mInitParams.NShlenght+=0.5;
			mP.mInitParams.RShlenght-=0.5;
		}
		float tmplen;
		if (mP.mInitParams.NShlenght<mP.mInitParams.RShlenght)
			tmplen=0.15*mP.mInitParams.NShlenght;
		else
			tmplen=0.15*mP.mInitParams.RShlenght;
		if (mP.mInitParams.mSolveType==SolveTypeRever)
			tmplen*=2.0;
		mP.mInitParams.NClockPOsitionOnShaft=mP.mInitParams.NShlenght/2.0-tmplen;
		mP.mInitParams.RClockPOsitionOnShaft=mP.mInitParams.RShlenght/2.0-tmplen;
		if(mP.mInitParams.mSolveType==SolveTypeSpool)
			mP.mInitParams.Hcsize=2.0*tmplen;
		else
			mP.mInitParams.Hcsize=2.0*tmplen+mP.mInitParams.ShaftEndGap;
		mdoMisAlgn.myI.init(mP.mInitParams);
		mdoMisAlgn.misAlign(mP.getAlignValues(),mP.mInitParams.Nrear,mP.mInitParams.Rrear,mP.mInitParams.right);
		SbVec3f Driven_n;
		SbVec3f Driver_n;
		SbVec3f Driven_r0;
		SbVec3f Driver_r0;
		SbVec3f	Driven_End;
		SbVec3f	Driver_End;
		SbVec3f Driven_2P;
		SbVec3f Driver_2P;
		Driver_End=indicatorDriver(-mP.mInitParams.RShlenght*0.5,Driver_End);
		Driven_End=indicatorDriven(-mP.mInitParams.NShlenght*0.5,Driven_End,mP.mInitParams.Nrear);
		Driver_r0=indicatorDriver(-mP.mInitParams.RClockPOsitionOnShaft-mP.mInitParams.Hcsize,Driver_r0);
		Driven_r0=indicatorDriven(-mP.mInitParams.NClockPOsitionOnShaft-mP.mInitParams.Hcsize,Driven_r0,mP.mInitParams.Nrear);
		Driven_n=Driven_End-Driven_r0;
		Driver_n=Driver_End-Driver_r0;
		if(mP.mInitParams.mSolveType==SolveTypeSpool)
		{
			Driven_2P=Driver_End;
			Driver_2P=Driven_End;
		}
		else
		{
			Driven_2P=Driven_r0;
			Driver_2P=Driver_r0;
		}
		L_P_I mLPIDriver(Driver_r0,Driver_n,Driven_End,Driven_2P);
		SbVec3f Driver_r=mLPIDriver.r;
		float a,delta;
		a=mLPIDriver.a;
		delta=mLPIDriver.delta;
		float ad,deltad;
		SbVec3f Driven_r;
		if(mP.mInitParams.mSolveType==SolveTypeDouble)
		{
			Driver_r0=indicatorDriver(-mP.mInitParams.RClockPOsitionOnShaft-mP.mInitParams.Hcsize-mP.mInitParams.AdDblHcsize,Driver_r0);
			L_P_I mLPIDriverDouble(Driver_r0,Driver_n,Driven_End,Driven_r0);
			ad=mLPIDriverDouble.a;
			deltad=mLPIDriverDouble.delta;
			Driven_r=mLPIDriverDouble.r;
		}
		else
		{
			L_P_I mLPIDriven(Driven_r0,Driven_n,Driver_End,Driver_2P);
			ad=mLPIDriven.a;
			deltad=mLPIDriven.delta;
			Driven_r=mLPIDriven.r;
			//spool
			if(mP.mInitParams.mSolveType==SolveTypeSpool)
			{
				mdoMisAlgn.myI.set_SpoolRotation(SbRotation(SbVec3f(0.0,0.0,1.0),pi/2.0)*SbRotation(SbVec3f(1.0,0.0,0.0),Driver_End-Driven_End));
				mdoMisAlgn.myI.set_SpoolCentre(Driven_End+0.5*(Driver_End-Driven_End));
			}
			//spool
		}
		bool booli=true;
		float loop_start=(mP.restriction).IndicatorRotation[0];
		float loop_stop=(mP.restriction).IndicatorRotation[1];
		float step=pi/50.0;
		int point_count=1+(loop_stop-loop_start)/step;
		mClcResult=new ClcResult[point_count];
		mdoMisAlgn.myI.set_indicatorDrivertranslation(Driven_r0);
		mdoMisAlgn.myI.set_indicatorDriventranslation(Driven_r);
		int indx=0;
		for (float rotAngle=loop_start;rotAngle<=loop_stop;rotAngle+=step)
		{
			if(mP.mInitParams.mSolveType==SolveTypeDouble || mP.mInitParams.mSolveType==SolveTypeSpool)
				mClcResult[indx].rotAngled=rotAngle;
			else
				mClcResult[indx].rotAngled=rotAngle+pi;
			mClcResult[indx].rotAngle=rotAngle;
			if(mClcResult[indx].rotAngled>=2.0*pi)
				mClcResult[indx].rotAngled=mClcResult[indx].rotAngled-2.0*pi;
			//iP and x
			mClcResult[indx].iP=indicPosition(delta,pi/2.0-mClcResult[indx].rotAngle,mP.mInitParams.Vcsize,a,mP.mInitParams.pSrad);
			mClcResult[indx].x=asin(a/(mClcResult[indx].iP+mP.mInitParams.pSrad)*sin(delta+rotAngle));
			//iP and x
			//iPd and xd
			if(mP.mInitParams.mSolveType==SolveTypeFaceRim)
			{
				//face rim
				SbVec3f DrivenRim1;
				SbVec3f DrivenRim2;
				DrivenRim1=indicatorDriver(0.0,DrivenRim1,mP.mInitParams.VFacecsize,mClcResult[indx].rotAngled);
				DrivenRim2=indicatorDriver(-mP.mInitParams.Hcsize/2.0,DrivenRim2,mP.mInitParams.VFacecsize,mClcResult[indx].rotAngled);
				L_P_I mLPIFaceRim(Driven_End,Driven_n,DrivenRim1,DrivenRim2);
				mClcResult[indx].iPd=sqrt((mLPIFaceRim.r[0]-DrivenRim2[0])*(mLPIFaceRim.r[0]-DrivenRim2[0])+(mLPIFaceRim.r[1]-DrivenRim2[1])*(mLPIFaceRim.r[1]-DrivenRim2[1])+(mLPIFaceRim.r[2]-DrivenRim2[2])*(mLPIFaceRim.r[2]-DrivenRim2[2]));
				mClcResult[indx].xd=SbRotation(SbVec3f(0.0,0.0,1.0),-pi/2);
				//face rim
			}
			else
			{
					mClcResult[indx].iPd=indicPosition(deltad,pi/2.0-mClcResult[indx].rotAngled,mP.mInitParams.Vcsize,ad,mP.mInitParams.pSrad);
					mClcResult[indx].xd=SbRotation(SbVec3f(0.0,1.0,0.0),asin(ad/(mClcResult[indx].iPd+mP.mInitParams.pSrad)*sin(deltad+mClcResult[indx].rotAngled)));
			}
			//iPd and xd
			mClcResult[indx].rotAngleFraction=rotAngle/2.0/pi;
			if (booli)
			{
				iP0=mClcResult[indx].iP;
				iPd0=mClcResult[indx].iPd;
				booli=false;
			}
			if(rotAngle<=100*ERR && rotAngle>=-100*ERR)
			{
				clockVal[0]=(iP0-mClcResult[indx].iP);
				clockVal[1]=(iPd0-mClcResult[indx].iPd);
			}
			if(rotAngle<=pi/2.0+100*ERR && rotAngle>=pi/2.0-100*ERR)
			{
				clockVal[2]=(iP0-mClcResult[indx].iP);
				clockVal[3]=(iPd0-mClcResult[indx].iPd);
			}
			if(rotAngle<=pi+100*ERR && rotAngle>=pi-100*ERR)
			{
				clockVal[4]=(iP0-mClcResult[indx].iP);
				clockVal[5]=(iPd0-mClcResult[indx].iPd);
			}
			if(rotAngle<=3.0*pi/2.0+100*ERR && rotAngle>=3.0*pi/2.0-100*ERR)
			{
				clockVal[6]=(iP0-mClcResult[indx].iP);
				clockVal[7]=(iPd0-mClcResult[indx].iPd);
			}
			indx++;
		}
		Maxindx=indx;
		if (errCode==-1)//image
		{
			printf("Content-type: image/png\n\n");
			mainpl(mP.SERVER_ADD_image,mP.mInitParams,clockVal);
			//printHeder();
			//printf("%s%s%s","<img src='",mP.SERVER_ADD_image,"'>");
			//printFooter();
			return (errCode);
		}
		if (errCode==-2)//results
		{
			for(long index=0;index<8;index++)
				clockVal[index]=((int)(mP.clockscale*100.0*clockVal[index]))/(mP.clockscale*100.0);//dial indicators are not very good!
			feetcorrection mfc(mP.mInitParams,clockVal);
			char res[255];
			printf("Content-type: text/html\n\n");
			sprintf(res,"%s%+6.2f%s%+6.2f%s%+6.2f%s%+6.2f%s%+6.2f%s%+6.2f%s%+6.2f%s%+6.2f","RRH=",mfc.OutboardFeetOfDriver[1]*1000,"&RRV=",mfc.OutboardFeetOfDriver[0]*1000,"&RFH=",mfc.InboardFeetOfDriver[1]*1000,"&RFV=",mfc.InboardFeetOfDriver[0]*1000,"&NFH=",mfc.InboardFeetOfDriven[1]*1000,"&NFV=",mfc.InboardFeetOfDriven[0]*1000,"&NRH=",mfc.OutboardFeetOfDriven[1]*1000,"&NRV=",mfc.OutboardFeetOfDriven[0]*1000);
			readTablesResults(buf,res);
			printf("%s",buf);
			return(errCode);
		}
		else
		{
			int mOut;
			SoDB::init();
			SoInput in;
			SoOutput ou;
			SoWriteAction wa(&ou);
			if (in.openFile("Alignment.wrl")) {
				SoVRMLGroup *alignVRML = SoDB::readAllVRML(&in);
				alignVRML->ref();
				in.closeFile();
				if (alignVRML) {
					doMisAlgn::myI.mVG=alignVRML;
					doMisAlgn::myI.init(mP.mInitParams);
					mdoMisAlgn.misAlign(mP.getAlignValues(),mP.mInitParams.Nrear,mP.mInitParams.Rrear,mP.mInitParams.right);
					SoVRMLTimeSensor* timer=((SoVRMLTimeSensor *) SoNode::getByName("timer1"));
					SoVRMLPositionInterpolator* iDictranslation=(SoVRMLPositionInterpolator *) SoNode::getByName("iDictranslation");
					SoVRMLPositionInterpolator* DriveniDictranslation=(SoVRMLPositionInterpolator *) SoNode::getByName("DriveniDictranslation");
					SoVRMLOrientationInterpolator* clockrotation=(SoVRMLOrientationInterpolator *) SoNode::getByName("clockrotation");
					SoVRMLOrientationInterpolator* Drivenclockrotation=(SoVRMLOrientationInterpolator *) SoNode::getByName("Drivenclockrotation");
					SoVRMLOrientationInterpolator* DriverClockClamprotation=(SoVRMLOrientationInterpolator *) SoNode::getByName("DriverClockClamprotation");
					SoVRMLOrientationInterpolator* DrivenClockClamprotation=(SoVRMLOrientationInterpolator *) SoNode::getByName("DrivenClockClamprotation");
					SoVRMLOrientationInterpolator* idicatorrotation=(SoVRMLOrientationInterpolator *) SoNode::getByName("idicatorrotation");
					SoVRMLOrientationInterpolator* Drivenidicatorrotation=(SoVRMLOrientationInterpolator *) SoNode::getByName("Drivenidicatorrotation");
					int indx=0;
					while(indx<Maxindx)
					{
						float rotAngle=mClcResult[indx].rotAngle;
						float rotAngled=mClcResult[indx].rotAngled;
						float iP=mClcResult[indx].iP;
						float iPd=mClcResult[indx].iPd;
						float x=mClcResult[indx].x;
						SbRotation xd=mClcResult[indx].xd;
						float rotAngleFraction=mClcResult[indx].rotAngleFraction;
						(iDictranslation->key).set1Value(indx,rotAngleFraction);
						(iDictranslation->keyValue).set1Value(indx,SIZE1/2.0-iP,0.0,0.0);//-iP
						(DriveniDictranslation->key).set1Value(indx,rotAngleFraction);
						(DriveniDictranslation->keyValue).set1Value(indx,SIZE1/2.0-iPd,0.0,0.0);//-iPd
						(clockrotation->key).set1Value(indx,rotAngleFraction);
						(clockrotation->keyValue).set1Value(indx,SbVec3f(0.0,1.0,0.0),x);
						(Drivenclockrotation->key).set1Value(indx,rotAngleFraction);
						(Drivenclockrotation->keyValue).set1Value(indx,xd);
						(DriverClockClamprotation->key).set1Value(indx,rotAngleFraction);
						(DriverClockClamprotation->keyValue).set1Value(indx,SbVec3f(0.0,1.0,0.0),rotAngle);
						(DrivenClockClamprotation->key).set1Value(indx,rotAngleFraction);
						(DrivenClockClamprotation->keyValue).set1Value(indx,SbVec3f(0.0,1.0,0.0),rotAngled);
						(idicatorrotation->key).set1Value(indx,rotAngleFraction);
						(idicatorrotation->keyValue).set1Value(indx,SbVec3f(0.0,1.0,0.0),(iP-iP0)*2.0*pi*mP.clockscale);
						(Drivenidicatorrotation->key).set1Value(indx,rotAngleFraction);
						(Drivenidicatorrotation->keyValue).set1Value(indx,SbVec3f(0.0,1.0,0.0),(iPd-iPd0)*2.0*pi*mP.clockscale);
						indx++;
					}
					if(FILE_OUT)
					{
						ou.openFile("./MatWork/AlignmentOut.wrl");
						ou.setHeaderString("#VRML V2.0 utf8");				
						wa.apply(alignVRML);
						ou.closeFile();
					}
					else
					{
						buffer_size = 1024;
						buffer = (char *)malloc(buffer_size);
						ou.setBuffer(buffer, buffer_size, buffer_realloc);
						ou.setHeaderString("#VRML V2.0 utf8");
						wa.apply(alignVRML);
						SbString sBu(buffer);
						free(buffer);
						(void)fprintf(stdout, "Content-type: model/vrml\n");
						(void)fprintf(stdout, "Pragma: no-cache\n\n");
						(void)fprintf(stdout, "%s\n", sBu.getString());
					}
					alignVRML->unref();
					mOut=0;
				}
				else mOut=1;
			}
		}
	}
	else
	{
		if (errCode==0)//nothing send
		{
			printf("Content-type: text/html\n\n");
			readHTMLfile(buf);
			printf("%s",buf);
			return(errCode);
		}
		if (errCode>2)
		{
			printHeder();
			if (errCode==1)//never!
			{
				printf(" You have asked for model = %s .model loaded",mP.get_ProblemName());
			}
			if (errCode==2)//never!
			{
				printf(" move OK");
			}
			if (errCode==3)
			{
				printf(" You have asked for model = %s .model not exist",mP.get_ProblemName());
			}
			if (errCode==4)
			{
				printf(" invalid input");
			}
			if (errCode==5)
			{
				printf(" invalid parameter sended");
			}
			if (errCode==6)
			{
				printf(" restriction violation");
			}
			printFooter();
			return(errCode);
		}
		return 2;
	}
}
SbVec3f indicatorDriven(float len,SbVec3f& t,float Nrear,float radius,float teta)
{

	SbRotation rotYZ=SbRotation(SbVec3f(0.0,1.0,0.0),doMisAlgn::myP.roNH)*SbRotation(SbVec3f(0.0,0.0,1.0),doMisAlgn::myP.roNV);
	SbVec3f scr=doMisAlgn::myI.get_indicatorDriventranslation()+SbVec3f(-len,radius*cos(teta),-1*radius*sin(teta))-doMisAlgn::myI.get_Drivencenter();
	rotYZ.multVec(scr,t);
	t+=doMisAlgn::myI.get_DDriventranslation();
	t+=doMisAlgn::myI.get_Driventranslation();
	t+=doMisAlgn::myI.get_Drivencenter();
/*
	t=doMisAlgn::myI.get_indicatorDriventranslation()-SbVec3f(len,0.0,0.0);
	if(radius!=0)
		t+=SbVec3f(0.0,radius*cos(teta),-1*radius*sin(teta));
	//ver
	float tmpCT;
	tmpCT=doMisAlgn::myI.get_Drivencenter()[0];
	float a=cos(doMisAlgn::myP.roNV)*(-tmpCT+t[0])+tmpCT;
	float b=sin(doMisAlgn::myP.roNV)*(-tmpCT+t[0]);
	t+=doMisAlgn::myI.get_Driventranslation();
	t[1]+=b;
	t=SbVec3f(a,t[1],t[2]);
	//hor
	a=cos(doMisAlgn::myP.roNH)*(Nrear/2.0+t[0])-Nrear/2.0;
	b=-sin(doMisAlgn::myP.roNH)*(Nrear/2.0+t[0]);
	t+=doMisAlgn::myI.get_DDriventranslation();
	t[2]+=b;
	t[0]=a;
*/
	return t;
}
SbVec3f indicatorDriver(float len,SbVec3f& t,float radius ,float teta)
{

	SbRotation rotYZ=SbRotation(SbVec3f(0.0,1.0,0.0),doMisAlgn::myP.roRH)*SbRotation(SbVec3f(0.0,0.0,1.0),doMisAlgn::myP.roRV);
	SbVec3f scr=doMisAlgn::myI.get_indicatorDrivertranslation()+SbVec3f(len,radius*cos(teta),-1*radius*sin(teta))-doMisAlgn::myI.get_Drivercenter();
	rotYZ.multVec(scr,t);
	t+=doMisAlgn::myI.get_DDrivertranslation();
	t+=doMisAlgn::myI.get_Drivertranslation();
	t+=doMisAlgn::myI.get_Drivercenter();
/*
	t=doMisAlgn::myI.get_indicatorDrivertranslation()+SbVec3f(len,0.0,0.0);
	if(radius!=0)
		t+=SbVec3f(0.0,radius*cos(teta),-1*radius*sin(teta));
	//ver
	float tmpCT;
	tmpCT=doMisAlgn::myI.get_Drivercenter()[0];
	float a=tmpCT-cos(doMisAlgn::myP.roRV)*(tmpCT-t[0]);
	float b=sin(doMisAlgn::myP.roRV)*(tmpCT-t[0]);
	t=t+doMisAlgn::myI.get_Drivertranslation();
	t=t+SbVec3f(0.0,-b,0.0);
	t[0]=a;
	//hor
	tmpCT=doMisAlgn::myI.get_DDrivercenter()[0];
	a=tmpCT-cos(doMisAlgn::myP.roRH)*(tmpCT-t[0]);
	b=sin(doMisAlgn::myP.roRH)*(tmpCT-t[0]);
	t=t+doMisAlgn::myI.get_DDrivertranslation();
	t=t+SbVec3f(0.0,0.0,b);
	t[0]=a;
*/
	return t;
}
float indicPosition(float delta,float teta,float r,float a,float b)
{
	float x=sqrt(a*a+r*r+2*r*a*sin(delta-teta));
	x=x-b;
	return x;
}
void getParam(char * st, char *sparam, char *s3) // extract parameter from a string 
{
	char temp[25];
	int i,j;
	for (i = 0; i < (strlen(st)); i++)
	{
		if (sparam[0] == st[i])
		{
			j = 0;
			for (j = 0; j < strlen(sparam); j++)
				temp[j] = st[j+i];
			temp[j] = '\0';
		}


		if (strcmp(temp,sparam) == 0) {
			printf(" parameter found \n");
			i = i + j+1;  // upto = sign 
			j = 0;
			while ((st[i] != '&') && (st[i] != '\0')) {
				s3[j] = st[i] ;
				j++, i++;
			}
			s3[j] = '\0' ;
		}
	}
};
void printHeder()
{
	printf("Content-type: text/html\n\n");
	printf("<html>");
	printf("<HEAD> <TITLE> Alingment Simulator Model </TITLE> </HEAD>\n");
	printf("<BODY>\n");
};
void printFooter()
{
	printf("</BODY>\n");
	printf("</html>\n");
};