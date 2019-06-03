//---------------------------------------------------------------------------//
// $Id: x01.cc 10169 2009-07-20 21:12:55Z andrewross $
//---------------------------------------------------------------------------//
//
//---------------------------------------------------------------------------//
// Copyright (C) 2004  Andrew Ross <andrewr@coriolis.greenend.org.uk>
// Copyright (C) 2004  Alan W. Irwin
//
// This file is part of PLplot.
//
// PLplot is free software; you can redistribute it and/or modify
// it under the terms of the GNU Library General Public License as published by
// the Free Software Foundation; version 2 of the License.
//
// PLplot is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public License
// along with PLplot; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
//---------------------------------------------------------------------------//
//
//---------------------------------------------------------------------------//
// Implementation of PLplot example 1 in C++.
//---------------------------------------------------------------------------//
#include "problem.h"
#include <sys/stat.h>

//#include </home/reza/Downloads/plplot/include/plplot/plevent.h>
//#include </home/reza/Downloads/plplot/include/plplot/plstream.h>

#include <plplot/plevent.h>
#include <plplot/plstream.h>
#include <math.h>
static struct PlotDATA
{
	float R0;
	float R90;
	float R180;
	float R270;
	float N0;
	float N90;
	float N180;
	float N270;
	float RSO;
	float RSI;
	float NSO;
	float NSI;
	float NC;
	float RC;
	float RF;
	float NF;
	float RSP;
	float NSP;
	float NFace;
	SolveType mSolveType;
} mPlotDATA;
class x01 {
	public:
		x01(char* fname);
		void plot(int i);
	private:
		PLFLT *x ;
		PLFLT *y ;
		plstream *pls;
		const int YMAX,XMAX;
		float yscale,xscale;
		int intxscale,intyscale;
};
x01::x01(char* fname):YMAX(30),XMAX(180) 
{
	char templateName[100];
	strcpy(templateName,"..");
	strcat(templateName,fname);
	//FILE* curve=fopen(templateName,"w");	
	pls = new plstream();
	//pls->sfile(curve);
	pls->sfile(stdout);
	PLINT cMR[8]={255,0,190,150,255,0,0,0};
	PLINT cMG[8]={255,0,190,50,0,0,120,180};
	PLINT cMB[8]={255,0,190,50,0,255,0,0};
	pls->scmap0(cMR,cMG,cMB,8);
	pls->start("png",1,2);
	pls->fontld( 0 );
	pls->schr(0.0,0.8);
	pls->ssym(0.0,1.2);
	x = new PLFLT[101];
	y = new PLFLT[101];
	for (int i=0;i<50;i++)
	{
		y[i]=0.0;
		x[i]=0.0;
	}
	xscale=mPlotDATA.RF/(XMAX-4.0);
	intxscale=(int)(1000.0*xscale+0.5);
	xscale=intxscale/1000.0;
	x[0]=mPlotDATA.NF/xscale+2.0;
	x[1]=mPlotDATA.NSO/xscale+2.0;
	x[2]=mPlotDATA.NSI/xscale+2.0;
	x[3]=mPlotDATA.NC/xscale+2.0;
	x[4]=mPlotDATA.RC/xscale+2.0;
	x[5]=mPlotDATA.RSI/xscale+2.0;
	x[6]=mPlotDATA.RSO/xscale+2.0;
	x[7]=mPlotDATA.RF/xscale+2.0;
	x[8]=mPlotDATA.NSP/xscale+2.0;
	x[9]=mPlotDATA.RSP/xscale+2.0;
	plot(1);
	plot(0);
	delete pls;
};
void x01::plot(int i)
{
	float ftmp;
	PLINT space0 = 0;
	PLINT mark0 = 0;
	PLINT space1 = 1500;
	PLINT mark1 = 1500;
	pls->adv(i);
	pls->svpa(10,10+XMAX,10,10+2*YMAX);
	pls->wind( 0.0, XMAX, -1*YMAX, YMAX );
	pls->col0(1);
	pls->box("bcnst", 10, 10, "bcnstv", 10, 10);
	pls->styl(1, &mark1, &space1);
	pls->col0(2);
	pls->box("g", 5.0, 0, "g", 5.0, 0);
	pls->styl(0, &mark0, &space0);
	pls->box("g", 10.0, 0, "g", 10.0, 0);
	pls->styl(0, &mark0, &space0);
	pls->col0(3);
	if(i==0)
	{
		pls->mtex("t",-1.5,0.5,0.5,"Top View");
		pls->mtex("t",-3.5,0.5,0.5,"(3 Clock)");
	}
	else
		pls->mtex("t",-2,0.5,0.5,"Side View");
	pls->mtex("t",-2,0.1,0.5,"Driven");
	pls->mtex("t",-2,0.9,0.5,"Driver");
	if(i==1)
	{
		y[3]=(mPlotDATA.N0-mPlotDATA.N180)/2.0;//Up in negative AND Down is Pos
		y[4]=(mPlotDATA.R0-mPlotDATA.R180)/2.0;//Up in negative AND Down is Pos
	}
	else
	{
		y[3]=(mPlotDATA.N90-mPlotDATA.N270)/2.0;//Up in negative AND Down is Pos
		y[4]=(mPlotDATA.R90-mPlotDATA.R270)/2.0;//Up in negative AND Down is Pos
	}
	if(mPlotDATA.mSolveType==SolveTypeDouble)
	{
		yscale=fabs(((y[4]-y[3])/(x[4]-x[3])*(x[3]-x[0]))-y[3]);
		ftmp=fabs(y[3]);
		if(ftmp>yscale)
			yscale=ftmp;
		yscale/=(YMAX-2);
	}
	else
	{
		if(mPlotDATA.mSolveType==SolveTypeSpool)
		{
			y[3]*=-1;y[4]*=-1;
			yscale=fabs(((y[4]-y[8])/(x[4]-x[8])*(x[4]-x[0]))-y[4]);
			ftmp=fabs(((y[3]-y[9])/(x[3]-x[9])*(x[3]-x[7]))-y[3]);
			if(ftmp>yscale)
				yscale=ftmp;
			yscale/=(YMAX-2);
		}
		else
		{
			if(mPlotDATA.mSolveType==SolveTypeFaceRim)
			{
				float m=y[4]/(mPlotDATA.NFace/xscale);
				x[4]=x[3]/2.0;
				y[4]=y[3]+m*(x[3]-x[4]);
				yscale=fabs(m*(x[3]-x[0])+y[3]);
				ftmp=fabs(y[3]);
				if(ftmp>yscale)
					yscale=ftmp;
				yscale/=(YMAX-2);
			}
			else//reverse
			{
				yscale=fabs(y[3]/(x[4]-x[3])*(x[4]-x[0])/(YMAX-2));
				ftmp=fabs(y[4]/(x[4]-x[3])*(x[7]-x[3])/(YMAX-2));
				if(ftmp>yscale)
					yscale=ftmp;
			}
		}
	}
	yscale=(yscale<ERR and yscale>-ERR) ? 1:yscale;
	intyscale=(int)(1000.0*100.0*yscale+0.5);
	yscale=intyscale/100000.0;
	y[3]/=yscale;
	y[4]/=yscale;
	pls->col0(4);
	char str[100];
	sprintf(str,"%s%d%s","<scale:",intxscale,"/1>");
	pls->mtex("b",-2.0,0.5,0.5,str);
	sprintf(str,"%s%d%s","<1~",intyscale," mils>");
	pls->mtex("l",+4.5,0.5,0.5,str);
	pls->wid(2);//pen width
	pls->col0(5);
	pls->poin(1,&(x[0]),&(y[0]),124);//flage
	pls->poin(1,&(x[1]),&(y[1]),7);//stand
	pls->poin(1,&(x[2]),&(y[2]),7);//stand
	pls->poin(1,&(x[3]),&(y[3]),9);//clc
	pls->poin(1,&(x[4]),&(y[4]),9);//clc
	pls->poin(1,&(x[5]),&(y[5]),7);//stand
	pls->poin(1,&(x[6]),&(y[6]),7);//stand
	pls->poin(1,&(x[7]),&(y[7]),124);//flage
	if(mPlotDATA.mSolveType==SolveTypeSpool)
	{
		pls->poin(1,&(x[8]),&(y[8]),124);//SP
		pls->poin(1,&(x[9]),&(y[9]),124);//SP
	}
	pls->col0(6);
	if(mPlotDATA.mSolveType==SolveTypeDouble || mPlotDATA.mSolveType==SolveTypeFaceRim)
	{
		pls->lsty(1);
		PLFLT xn[]={x[0],x[3]};
		PLFLT yn[]={(x[0]-x[3])*(y[3]-y[4])/(x[3]-x[4])+y[3],y[3]};
		pls->line(2,xn,yn);
		pls->col0(7);
		PLFLT xr[]={x[5],x[7]};
		PLFLT yr[]={0,0};
		pls->line(2,xr,yr);
	}
	else
	{
		if(mPlotDATA.mSolveType==SolveTypeSpool)
		{
			PLFLT xn[]={x[0],x[8]};
			PLFLT yn[]={(y[8]-y[4])/(x[8]-x[4])*(x[0]-x[4])+y[4],y[8]};
			pls->line(2,xn,yn);
			pls->lsty(2);
			PLFLT xn0[]={x[4],x[8]};
			PLFLT yn0[]={y[4],y[8]};
			pls->line(2,xn0,yn0);
			pls->col0(7);
			PLFLT xr[]={x[7],x[9]};
			PLFLT yr[]={(y[9]-y[3])/(x[9]-x[3])*(x[7]-x[3])+y[3],y[9]};
			pls->lsty(1);
			pls->line(2,xr,yr);
			PLFLT xr0[]={x[3],x[9]};
			PLFLT yr0[]={y[3],y[9]};
			pls->lsty(2);
			pls->line(2,xr0,yr0);
		}
		else
		{
			PLFLT xn[]={x[0],x[3]};
			PLFLT yn[]={y[3]/(x[4]-x[3])*(x[4]-x[0]),y[3]};
			pls->line(2,xn,yn);
			pls->lsty(2);
			PLFLT xn0[]={x[3],x[4]};
			PLFLT yn0[]={y[3],0};
			pls->line(2,xn0,yn0);
			pls->col0(7);
			PLFLT xr[]={x[7],x[4]};
			PLFLT yr[]={y[4]/(x[4]-x[3])*(x[7]-x[3]),y[4]};
			pls->lsty(1);
			pls->line(2,xr,yr);
			PLFLT xr0[]={x[4],x[3]};
			PLFLT yr0[]={y[4],0};
			pls->lsty(2);
			pls->line(2,xr0,yr0);
		}
	}
	pls->wid(1);//pen width
};
char* mainpl(char* fname,InitParams mInitParams,float* clockVal)
{
	mPlotDATA.mSolveType=mInitParams.mSolveType;
	mPlotDATA.N0=clockVal[0];
	mPlotDATA.N180=clockVal[4];
	mPlotDATA.N90=clockVal[2];
	mPlotDATA.N270=clockVal[6];
	mPlotDATA.NF=0.0;
	mPlotDATA.NSO=0.0;
	mPlotDATA.NSI=mInitParams.Nrear;
	mPlotDATA.NC=mInitParams.Nrear+mInitParams.NShlenght+mInitParams.ShaftEndGap+mInitParams.RShlenght/2.0-mInitParams.RClockPOsitionOnShaft-mInitParams.Hcsize;
	if(mPlotDATA.mSolveType==SolveTypeDouble || mPlotDATA.mSolveType==SolveTypeSpool)
	{
		mPlotDATA.R0=clockVal[1];
		mPlotDATA.R180=clockVal[5];
		mPlotDATA.R90=clockVal[3];
		mPlotDATA.R270=clockVal[7];
		if(mPlotDATA.mSolveType==SolveTypeDouble)
			mPlotDATA.RC=mPlotDATA.NC-mInitParams.AdDblHcsize;
		else//SolveTypeSpool
			mPlotDATA.RC=mInitParams.Nrear+mInitParams.NShlenght/2.0+mInitParams.NClockPOsitionOnShaft+mInitParams.Hcsize;
	}
	else//reverse & facerim
	{
		mPlotDATA.R0=clockVal[5];
		mPlotDATA.R180=clockVal[1];
		mPlotDATA.R90=clockVal[7];
		mPlotDATA.R270=clockVal[3];
		if(mPlotDATA.mSolveType==SolveTypeFaceRim)
			mPlotDATA.NFace=mInitParams.VFacecsize;
		mPlotDATA.RC=mInitParams.Nrear+mInitParams.NShlenght/2.0+mInitParams.NClockPOsitionOnShaft+mInitParams.Hcsize;
	}
	mPlotDATA.RSI=mInitParams.Nrear+mInitParams.NShlenght+mInitParams.RShlenght+mInitParams.ShaftEndGap;
	mPlotDATA.RSO=mPlotDATA.RSI+mInitParams.Rrear;
	mPlotDATA.RF=mPlotDATA.RSO;
	if(mPlotDATA.mSolveType==SolveTypeSpool)
	{
		mPlotDATA.NSP=mPlotDATA.NSI+mInitParams.NShlenght;
		mPlotDATA.RSP=mPlotDATA.NSP+mInitParams.ShaftEndGap;
	}
	x01* mx01=new x01(fname);
	delete mx01;
	return fname;
}