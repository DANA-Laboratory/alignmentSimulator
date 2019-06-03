#include "interface.h"
void	interface::init(InitParams mInitParams)
{
	if(flag==0)
	{
		initclc(mInitParams.RShlenght+mInitParams.NShlenght+mInitParams.ShaftEndGap,mInitParams.NShlenght,mInitParams.RShlenght,mInitParams.equiptHeight,mInitParams.height,mInitParams.Rrear,mInitParams.right,mInitParams.Nrear);
		flag=1;
	}
	else
	{
		drivercolor= new SoSFColor();
		drivencolor= new SoSFColor();
		spoolcolor=new SoSFColor();
		drivercolor->setValue(0.4,0.1,0.1);
		drivencolor->setValue(0.1,0.1,0.4);
		spoolcolor->setValue(0.3,0.8,0.8);
		flag=2;
		setclc();
		float tmpVsize;
		if(mInitParams.mSolveType==SolveTypeFaceRim)
			tmpVsize=mInitParams.VFacecsize;
		else
			tmpVsize=mInitParams.Vcsize;			
		initParameters(mInitParams.mSolveType,mInitParams.rad,mInitParams.ShaftEndGap,mInitParams.Nrear,mInitParams.Rrear,mInitParams.right,mInitParams.equiptHeight,mInitParams.NShlenght,mInitParams.RShlenght,mInitParams.pSrad,mInitParams.NClockPOsitionOnShaft+mInitParams.NShlenght/2,mInitParams.RClockPOsitionOnShaft+mInitParams.RShlenght/2,mInitParams.Hcsize,tmpVsize,mInitParams.AdDblHcsize);
		initStandDriven(mInitParams.rad,mInitParams.height,mInitParams.Nrear,mInitParams.right);
		initStandDriver(mInitParams.rad,mInitParams.height,mInitParams.Rrear,mInitParams.right,mInitParams.NShlenght+mInitParams.RShlenght+mInitParams.ShaftEndGap);
		initPumpDriver(mInitParams.equiptHeight,mInitParams.height,mInitParams.Rrear,mInitParams.right,mInitParams.NShlenght+mInitParams.RShlenght+mInitParams.ShaftEndGap);
		initPumpDriven(mInitParams.equiptHeight,mInitParams.height,mInitParams.Nrear,mInitParams.right);
		initPumpShaftDriver(mInitParams.NShlenght+mInitParams.RShlenght+mInitParams.ShaftEndGap,mInitParams.RShlenght,mInitParams.pSrad);
		initPumpShaftDriven(mInitParams.NShlenght,mInitParams.pSrad,mInitParams.equiptHeight,mInitParams.height);
		initClock(mInitParams.clockrad,mInitParams.Hcsize,mInitParams.Vcsize,mInitParams.RClockPOsitionOnShaft);
		if(mInitParams.mSolveType==SolveTypeDouble || mInitParams.mSolveType==SolveTypeFaceRim)//Both clocks on a shaft
		{
			if( mInitParams.mSolveType==SolveTypeFaceRim)
			{
				float clockZRotation=-pi/2;
				initDoubleClock(mInitParams.clockrad,mInitParams.Hcsize/2.0,mInitParams.VFacecsize,mInitParams.RClockPOsitionOnShaft,clockZRotation);
			}
			else
				initDoubleClock(mInitParams.clockrad,mInitParams.AdDblHcsize+mInitParams.Hcsize,mInitParams.Vcsize,mInitParams.RClockPOsitionOnShaft);
			SoVRMLTransform * mDrivenClockClamp=(getTran("DrivenClockClamp"));
			SoVRMLTransform * mDriverShaft=(getTran("DriverShaft"));
			SoVRMLTransform * mDrivenShaft=(getTran("DrivenShaft"));
			mDriverShaft->addChild(mDrivenClockClamp);
			mDrivenShaft->removeChild(mDrivenClockClamp);
		}
		else
			initDrivenClock(mInitParams.clockrad,mInitParams.Hcsize,mInitParams.Vcsize,mInitParams.NClockPOsitionOnShaft);
		SoVRMLCylinder* mCyF=new SoVRMLCylinder();
		mCyF->radius=mInitParams.FlangToShaftFraction*mInitParams.pSrad;
		initShaftFlage(mCyF,mInitParams.NShlenght,mInitParams.RShlenght);
		if(mInitParams.mSolveType==SolveTypeSpool)//add spool
		{
			initSpool(mInitParams.ShaftEndGap,mInitParams.pSrad,mCyF);
		}
		initIndicDriven(0.01,0.2*mInitParams.pSrad);
		initIndicDriver(0.01,0.2*mInitParams.pSrad);
		(getTran("BilCom")->translation).setValue(SbVec3f(0.0,-5.0*mInitParams.height,-1.0*mInitParams.height));
		initNghalh(mInitParams.height,mInitParams.right);
	}
	return;
}
void interface::initclc(float shiftx,float NShlenght,float RShlenght,float equiptHeight,float height,float Rrear,float right,float Nrear)
{
	set_DrivenEqtranslation(SbVec3f(-Nrear,equiptHeight/2.0+height/2.0,right/2.0));
	set_DriverEqtranslation(SbVec3f(shiftx,equiptHeight/2.0+height/2.0,right/2.0));
	set_indicatorDriventranslation(SbVec3f(NShlenght/2.0,(equiptHeight+height)/2.0,right/2));//??????!!!!!!!!!!
	set_indicatorDrivertranslation(SbVec3f(shiftx-RShlenght/2.0,(equiptHeight+height)/2.0,right/2));
}

void	interface::initParameters(SolveType mSolveType,float rad,float ShaftEndGap,float Nrear,float Rrear,float right,float equiptHeight,float NShlenght,float RShlenght,float pSrad,float NClockPosition,float RClockPosition,float Hcsize,float Vcsize,float AdDblHcsize)
{
	SbString tmp;
	int i=1;
	float tmpf,tmpfN,tmpfR;
	SoMFString msR;
	msR.copyFrom(((SoVRMLText *) mVG->getByName("DriverParameters"))->string);
	SoMFString msN;
	msN.copyFrom(((SoVRMLText *) mVG->getByName("DrivenParameters"))->string);
	while (i<10)
	{
		switch (i)
		{
			case 1:
				tmpfN=Nrear;
				tmpfR=Rrear;
				break;
			case 2:
				tmpf=equiptHeight;
				break;
			case 3:
				tmpf=right;
				break;
			case 4:
				tmpfN=NShlenght;
				tmpfR=RShlenght;
				break;
			case 5:
				tmpf=pSrad;
				break;
			case 6:
				//
				tmpfN=NClockPosition;
				tmpfR=RClockPosition;
				break;
			case 7:
				tmpf=Vcsize;
				break;
			case 8:
				//
				tmpfR=Hcsize;
				if(mSolveType==SolveTypeDouble)
					tmpfN=Hcsize+AdDblHcsize;
				else
					tmpfN=Hcsize;
				break;
			case 9:
				tmpf=ShaftEndGap;
				break;
		}
		if(i==8 && mSolveType==SolveTypeDouble)
			tmp="8-Near Clamp Length=";
		else
			tmp=msR[i];
		ostringstream s;
		if (i!=1 && i!=4 && i!=6 && i!=8)
			s<<tmpf;
		else
			s<<tmpfR;
		tmp+=s.str().c_str();
		(((SoVRMLText *) mVG->getByName("DriverParameters"))->string).set1Value(i,tmp);
		if(i==8 && mSolveType==SolveTypeDouble)
			tmp="8-Far Clamp Length=";
		else
			tmp=msN[i];
		s.seekp(ios_base::beg);
		if (i!=1 && i!=4 && i!=6 && i!=8)
			s<<tmpf;
		else
			if(i!=6 || mSolveType!=SolveTypeDouble)
				s<<tmpfN;
			else
				s<<"----";
		tmp+=s.str().c_str();
		(((SoVRMLText *) mVG->getByName("DrivenParameters"))->string).set1Value(i,tmp);
		i++;
	}
	return;
};
void	interface::initClock(float clockrad,float Hcsize,float Vcsize,float clockpositiononshaft)
{
	(getBox("hclampBox")->size).setValue(Vcsize,SIZE2,SIZE2);
	(getTran("hclamp")->translation).setValue(Vcsize/2,0.0,0.0);
	(getBox("vclampBox")->size).setValue(SIZE2,Hcsize,SIZE2);
	(getTran("vclamp")->translation).setValue(Vcsize,Hcsize/2.0,0.0);
	(getCy("cirCy")->radius).setValue(clockrad+1*0.2*clockrad);
	(getCy("cirCy")->height).setValue(0.2*0.2*clockrad);
	(getTran("circle")->rotation).setValue(SbVec3f(1.0,0.0,0.0),pi/2.0);
	(getTran("circle")->translation).setValue(0.0,0.0,0.18*clockrad);
	int i;
	SoVRMLParent* tmpPNode=(SoVRMLParent*) mVG->getByName("clock");
	SoSFColor colTire;
	colTire.setValue(0.3,0.8,0.8);
	SoSFColor colRoshn;
	colRoshn.setValue(0.3,0.2,0.2);
	for (i=0;i<10;i++)
	{
		SoVRMLTransform* tmpCNode=(SoVRMLTransform*)tmpPNode->getChild(i);
		tmpCNode->translation=SbVec3f(0.0,0.0,0.22*clockrad)+1.07*clockrad*SbVec3f(cos((i)*pi/5),sin((i)*pi/5),0)+clockrad*SbVec3f(-0.27,0.27,0)*clockrad;
		tmpCNode->scale=0.2*clockrad*(SbVec3f(1.0,1.0,1.0));
		(tmpCNode->rotation).setValue(SbVec3f(0.0,0.0,1.0),-pi/2.0);
	}
	SoVRMLSphere* sphChild[100];
	SoVRMLTransform* tranChild[100];
	SoVRMLShape* shChild[100];
	SoVRMLMaterial* maChild[100];
	SoVRMLAppearance* apChild[100];
	int j=0;
	float tmpRad=0;
	for (i=0;i<100;i++)
	{
		tranChild[i]=new SoVRMLTransform;
		shChild[i]=new SoVRMLShape;
		sphChild[i]=new SoVRMLSphere;
		apChild[i]=new SoVRMLAppearance;
		maChild[i]=new SoVRMLMaterial;
		if(i==j)
		{
			tmpRad=0.04*clockrad;
			j+=10;
			maChild[i]->diffuseColor=colTire;
		}
		else
		{
			tmpRad=0.015*clockrad;
			maChild[i]->diffuseColor=colRoshn;
		}
		tranChild[i]->translation=SbVec3f(0.0,0.0,0.25*clockrad)+0.92*clockrad*SbVec3f(cos((i)*pi/50.0),sin((i)*pi/50.0),0.0);
		sphChild[i]->radius=tmpRad;
		shChild[i]->geometry=sphChild[i];
		apChild[i]->material=maChild[i];
		shChild[i]->appearance=apChild[i];
		tranChild[i]->addChild(shChild[i]);
		tmpPNode->addChild(tranChild[i]);
	}
	(getBox("indicatorCy")->size).setValue(0.9*clockrad,SIZE2*clockrad,SIZE2*clockrad);
	(getTran("idicator")->translation).setValue(0.4*clockrad, 0.05*clockrad,0.0);
	SbVec3f tmpV=((getTran("idicator"))->center).getValue()-SbVec3f(0.4*clockrad,0.0,0.0);
	(getTran("idicator")->center).setValue(tmpV);
	(getBox("iDicCy")->size).setValue(SIZE1,SIZE2*clockrad,SIZE2*clockrad);
	(getTran("clock")->translation).setValue(Vcsize,Hcsize,0.0);
	(getTran("DriverClockClamp")->translation).setValue(SbVec3f(0.0,clockpositiononshaft,0.0));
	return;
};
void    interface::initDoubleClock(float clockrad,float Hcsize,float Vcsize,float clockpositiononshaft,float clockZRotation)
{
	(getBox("DrivenhclampBox")->size).setValue(Vcsize,SIZE2,SIZE2);
	(getTran("Drivenhclamp")->translation).setValue(Vcsize/2,0.0,0.0);
	(getBox("DrivenvclampBox")->size).setValue(SIZE2,Hcsize,SIZE2);
	(getTran("Drivenvclamp")->translation).setValue(Vcsize,Hcsize/2.0,0.0);
	(getCy("DrivencirCy")->radius).setValue(clockrad+1*0.2*clockrad);
	(getCy("DrivencirCy")->height).setValue(0.2*0.2*clockrad);
	(getTran("Drivencircle")->rotation).setValue(SbVec3f(1.0,0.0,0.0),pi/2.0);
	(getTran("Drivencircle")->translation).setValue(0.0,0.0,0.18*clockrad);
	int i;
	SoVRMLParent* tmpPNode=(SoVRMLParent*) mVG->getByName("Drivenclock");
	SoSFColor colTire;
	colTire.setValue(0.3,0.8,0.8);
	SoSFColor colRoshn;
	colRoshn.setValue(0.3,0.2,0.2);
	for (i=0;i<10;i++)
	{
		SoVRMLTransform* tmpCNode=(SoVRMLTransform*)tmpPNode->getChild(i);
		tmpCNode->translation=SbVec3f(0.0,0.0,0.22*clockrad)+1.07*clockrad*SbVec3f(cos((i)*pi/5),sin((i)*pi/5),0)+clockrad*SbVec3f(-0.27,0.27,0)*clockrad;
		tmpCNode->scale=0.2*clockrad*(SbVec3f(1.0,1.0,1.0));
		(tmpCNode->rotation).setValue(SbVec3f(0.0,0.0,1.0),-pi/2.0);
	}
	SoVRMLSphere* sphChild[100];
	SoVRMLTransform* tranChild[100];
	SoVRMLShape* shChild[100];
	SoVRMLMaterial* maChild[100];
	SoVRMLAppearance* apChild[100];
	int j=0;
	float tmpRad=0;
	for (i=0;i<100;i++)
	{
		tranChild[i]=new SoVRMLTransform;
		shChild[i]=new SoVRMLShape;
		sphChild[i]=new SoVRMLSphere;
		apChild[i]=new SoVRMLAppearance;
		maChild[i]=new SoVRMLMaterial;
		if(i==j)
		{
			tmpRad=0.04*clockrad;
			j+=10;
			maChild[i]->diffuseColor=colTire;
		}
		else
		{
			tmpRad=0.015*clockrad;
			maChild[i]->diffuseColor=colRoshn;
		}
		tranChild[i]->translation=SbVec3f(0.0,0.0,0.25*clockrad)+0.92*clockrad*SbVec3f(cos((i)*pi/50.0),sin((i)*pi/50.0),0.0);
		sphChild[i]->radius=tmpRad;
		shChild[i]->geometry=sphChild[i];
		apChild[i]->material=maChild[i];
		shChild[i]->appearance=apChild[i];
		tranChild[i]->addChild(shChild[i]);
		tmpPNode->addChild(tranChild[i]);
	}
	(getBox("DrivenindicatorCy")->size).setValue(0.9*clockrad,SIZE2*clockrad,SIZE2*clockrad);
	(getTran("Drivenidicator")->translation).setValue(0.4*clockrad, 0.05*clockrad,0.0);
	SbVec3f tmpV=((getTran("Drivenidicator"))->center).getValue()-SbVec3f(0.4*clockrad,0.0,0.0);
	(getTran("Drivenidicator")->center).setValue(tmpV);
	(getBox("DriveniDicCy")->size).setValue(SIZE1,SIZE2*clockrad,SIZE2*clockrad);
	(getTran("Drivenclock")->translation).setValue(Vcsize,Hcsize,0.0);
	(getTran("DrivenClockClamp")->translation).setValue(SbVec3f(0.0,clockpositiononshaft,0.0));
	if (clockZRotation!=0)
		(getTran("Drivenclock")->rotation).setValue(SbVec3f(0.0,0.0,1.0),clockZRotation);
	return;
};
void	interface::initDrivenClock(float clockrad,float Hcsize,float Vcsize,float clockpositiononshaft)
{
	Hcsize=-1*Hcsize;
	(getBox("DrivenhclampBox")->size).setValue(Vcsize,SIZE2,SIZE2);
	(getTran("Drivenhclamp")->translation).setValue(Vcsize/2,0.0,0.0);
	(getBox("DrivenvclampBox")->size).setValue(SIZE2,-1*Hcsize,SIZE2);
	(getTran("Drivenvclamp")->translation).setValue(Vcsize,Hcsize/2,0.0);
	(getCy("DrivencirCy")->radius).setValue(clockrad+1*0.2*clockrad);
	(getCy("DrivencirCy")->height).setValue(0.2*0.2*clockrad);
	(getTran("Drivencircle")->rotation).setValue(SbVec3f(1.0,0.0,0.0),pi/2.0);
	(getTran("Drivencircle")->translation).setValue(0.0,0.0,0.18*clockrad);
	int i;
	SoVRMLParent* tmpPNode=(SoVRMLParent*) mVG->getByName("Drivenclock");
	SoSFColor colTire;
	colTire.setValue(0.3,0.8,0.8);
	SoSFColor colRoshn;
	colRoshn.setValue(0.3,0.2,0.2);
	for (i=0;i<10;i++)
	{
		SoVRMLTransform* tmpCNode=(SoVRMLTransform*)tmpPNode->getChild(i);
		tmpCNode->translation=SbVec3f(0.0,0.0,0.22*clockrad)+1.07*clockrad*SbVec3f(cos((i)*pi/5),sin((i)*pi/5),0)+clockrad*SbVec3f(-0.27,0.27,0)*clockrad;
		tmpCNode->scale=0.2*clockrad*(SbVec3f(1.0,1.0,1.0));
		(tmpCNode->rotation).setValue(SbVec3f(0.0,0.0,1.0),-pi/2.0);
	}
	SoVRMLSphere* sphChild[100];
	SoVRMLTransform* tranChild[100];
	SoVRMLShape* shChild[100];
	SoVRMLMaterial* maChild[100];
	SoVRMLAppearance* apChild[100];
	int j=0;
	float tmpRad=0;
	for (i=0;i<100;i++)
	{
		tranChild[i]=new SoVRMLTransform;
		shChild[i]=new SoVRMLShape;
		sphChild[i]=new SoVRMLSphere;
		apChild[i]=new SoVRMLAppearance;
		maChild[i]=new SoVRMLMaterial;
		if(i==j)
		{
			tmpRad=0.04*clockrad;
			j+=10;
			maChild[i]->diffuseColor=colTire;
		}
		else
		{
			tmpRad=0.015*clockrad;
			maChild[i]->diffuseColor=colRoshn;
		}
		tranChild[i]->translation=SbVec3f(0.0,0.0,0.25*clockrad)+0.92*clockrad*SbVec3f(cos((i)*pi/50.0),sin((i)*pi/50.0),0.0);
		sphChild[i]->radius=tmpRad;
		shChild[i]->geometry=sphChild[i];
		apChild[i]->material=maChild[i];
		shChild[i]->appearance=apChild[i];
		tranChild[i]->addChild(shChild[i]);
		tmpPNode->addChild(tranChild[i]);
	}
	(getBox("DrivenindicatorCy")->size).setValue(0.9*clockrad,SIZE2*clockrad,SIZE2*clockrad);
	(getTran("Drivenidicator")->translation).setValue(0.4*clockrad,0.05*clockrad,0.0);
	SbVec3f tmpV=((getTran("Drivenidicator"))->center).getValue()-SbVec3f((float)0.4*clockrad,0.0,0.0);
	(getTran("Drivenidicator")->center).setValue(tmpV);
	(getBox("DriveniDicCy")->size).setValue(SIZE1,SIZE2*clockrad,SIZE2*clockrad);
	(getTran("Drivenclock")->translation).setValue(Vcsize,Hcsize,0.0);
	(getTran("DrivenClockClamp")->rotation).setValue(SbVec3f(0.0,1.0,0.0),pi);
	(getTran("DrivenClockClamp")->translation).setValue(SbVec3f(0.0,-clockpositiononshaft,0.0));
	return;
};
void	interface::initNghalh(float height,float right)
{
	const float rad=0.7;
	int i,j=0;float tmpRad;
	SoVRMLParent* tmpPNode=(SoVRMLParent*) mVG->getByName("nghalh");
	((getTran("nghalh"))->translation).setValue(0.0,height*4.0,right/2.0);
	(getCy("nghalh_Cy")->radius).setValue(rad);

	SoSFColor colTire;
	colTire.setValue(0.3,0.8,0.8);
	SoSFColor colRoshn;
	colRoshn.setValue(0.3,0.2,0.2);
	SoVRMLSphere* sphChild[36];
	SoVRMLTransform* tranChild[36];
	SoVRMLShape* shChild[36];
	SoVRMLMaterial* maChild[36];
	SoVRMLAppearance* apChild[36];
	for (i=0;i<36;i++)
	{
		tranChild[i]=new SoVRMLTransform;
		shChild[i]=new SoVRMLShape;
		sphChild[i]=new SoVRMLSphere;
		apChild[i]=new SoVRMLAppearance;
		maChild[i]=new SoVRMLMaterial;
		if(i==j)
		{
			tmpRad=0.04;
			j+=9;
			maChild[i]->diffuseColor=colTire;
		}
		else
		{
			tmpRad=0.015;
			maChild[i]->diffuseColor=colRoshn;
		}
		tranChild[i]->translation=SbVec3f(0.0,-0.02,0.0)+0.90*rad*SbVec3f(cos((i)*pi/18.0),0.0,sin((i)*pi/18.0));
		sphChild[i]->radius=tmpRad;
		shChild[i]->geometry=sphChild[i];
		apChild[i]->material=maChild[i];
		shChild[i]->appearance=apChild[i];
		tranChild[i]->addChild(shChild[i]);
		tmpPNode->addChild(tranChild[i]);
	}
	return;
};
void	interface::initStandDriven(float rad,float height,float rear,float right)
{
	(getCy("DrivenRRCy")->height).setValue(height);
	(getCy("DrivenRLCy")->height).setValue(height);
	(getCy("DrivenFLCy")->height).setValue(height);
	(getCy("DrivenFRCy")->height).setValue(height);
	(getCy("DrivenRRCy")->radius).setValue(rad);
	(getCy("DrivenRLCy")->radius).setValue(rad);
	(getCy("DrivenFLCy")->radius).setValue(rad);
	(getCy("DrivenFRCy")->radius).setValue(rad);
	(getTran("DrivenRL")->translation).setValue(-1.0*rear,0.0,0.0);
	(getTran("DrivenRR")->translation).setValue(SbVec3f(-1.0*rear,0.0,right));
	(getTran("DrivenFL")->translation).setValue(0.0,0.0,0.0);
	(getTran("DrivenFR")->translation).setValue(0.0,0.0,right);
	return;
};

void    interface::initStandDriver(float rad,float height,float rear,float right,float shiftx)
{
	(getCy("DriverRRCy")->height).setValue(height);
	(getCy("DriverRLCy")->height).setValue(height);
	(getCy("DriverFLCy")->height).setValue(height);
	(getCy("DriverFRCy")->height).setValue(height);
	(getCy("DriverRRCy")->radius).setValue(rad);
	(getCy("DriverRLCy")->radius).setValue(rad);
	(getCy("DriverFLCy")->radius).setValue(rad);
	(getCy("DriverFRCy")->radius).setValue(rad);
	(getTran("DriverRL")->translation).setValue(shiftx+rear,0.0,0.0);
	(getTran("DriverRR")->translation).setValue(SbVec3f(shiftx+rear,0.0,right));
	(getTran("DriverFL")->translation).setValue(shiftx,0.0,0.0);
	(getTran("DriverFR")->translation).setValue(shiftx,0.0,right);
	return;
};

void    interface::initPumpDriven(float equiptHeight,float height,float rear,float right)
{
	SoVRMLExtrusion* pump=(SoVRMLExtrusion *) (mVG->getByName("DrivenEqBox"));
	pump->beginCap.setValue(TRUE);
	pump->ccw.setValue(TRUE);
	pump->convex.setValue(TRUE);
	pump->creaseAngle.setValue(0);
	float fl[][2]={{equiptHeight*0.5,right*0.5},{0.7*equiptHeight,0},{0.5*equiptHeight,-right*0.5},{0.0,-right*0.7},{-0.5*equiptHeight,-right*0.5},{-0.7*equiptHeight,0.0},{-0.5*equiptHeight,0.5*right},{0.0,0.7*right},{0.5*equiptHeight,0.5*right}};
	pump->crossSection.setValues(0,9,fl);
	pump->endCap.setValue(TRUE);
	pump->orientation.setValue(SbVec3f (0,0,1),0);
	float fs[][2]={{0.9,0.9},{0.9,0.9},{0.5,0.5},{0.5,0.5}};
	pump->scale.setValues(0,4,fs);
	pump->solid.setValue(TRUE);
	float fl2[][3]={{0,0,0},{rear*0.35,0,0},{rear*0.4,0.0,0.0},{rear,0.0,0.0}};
	pump->spine.setValues(0,4,fl2);
	SoVRMLExtrusion* pumpPay=(SoVRMLExtrusion *) (mVG->getByName("DrivenEqPay"));
	pumpPay->beginCap.setValue(TRUE);
	pumpPay->ccw.setValue(TRUE);
	pumpPay->convex.setValue(TRUE);
	pumpPay->creaseAngle.setValue(0);
	float fly[][2]={{equiptHeight/2.0,right*0.5},{equiptHeight/2.0,-right*0.5},{-0.05*equiptHeight+equiptHeight/2.0,-right*0.5},{-equiptHeight*0.4+equiptHeight/2.0,-right*0.15},{-equiptHeight*0.4+equiptHeight/2.0,+right*0.15},{-0.05*equiptHeight+equiptHeight/2.0,0.5*right},{equiptHeight/2.0,0.5*right}};
	pumpPay->crossSection.setValues(0,7,fly);
	pumpPay->endCap.setValue(TRUE);
	pumpPay->orientation.setValue(SbVec3f (0,0,1),0);
	float fsy[][2]={{1.0,1.0},{1.0,1.0},{1.0,1.0},{1.0,1.0}};
	pumpPay->scale.setValues(0,4,fsy);
	pumpPay->solid.setValue(TRUE);
	float fl2y[][3]={{0,0,0},{rear*0.35,0,0},{rear*0.4,0.0,0.0},{rear,0.0,0.0}};
	pumpPay->spine.setValues(0,4,fl2y);
	return;
};
void    interface::initPumpDriver(float equiptHeight,float height,float rear,float right,float shiftx)
{
	SoVRMLExtrusion* motor=(SoVRMLExtrusion *) (mVG->getByName("DriverEqBox"));
	motor->beginCap.setValue(TRUE);
	motor->ccw.setValue(TRUE);
	motor->convex.setValue(TRUE);
	motor->creaseAngle.setValue(0);
	float fl[][2]={{equiptHeight*0.5,right*0.5},{0.7*equiptHeight,0},{0.5*equiptHeight,-right*0.5},{0.0,-right*0.7},{-0.5*equiptHeight,-right*0.5},{-0.7*equiptHeight,0.0},{-0.5*equiptHeight,0.5*right},{0.0,0.7*right},{0.5*equiptHeight,0.5*right}};
	motor->crossSection.setValues(0,9,fl);
	motor->endCap.setValue(TRUE);
	motor->orientation.setValue(SbVec3f (0,0,1),0);
	float fs[][2]={{0.8,0.8},{0.8,0.8},{0.8,0.8},{0.8,0.8}};
	motor->scale.setValues(0,4,fs);
	motor->solid.setValue(TRUE);
	float fl2[][3]={{0,0,0},{rear*0.35,0,0},{rear*0.4,0.0,0.0},{rear,0.0,0.0}};
	motor->spine.setValues(0,4,fl2);
	SoVRMLExtrusion* motorPay=(SoVRMLExtrusion *) (mVG->getByName("DriverEqPay"));
	motorPay->beginCap.setValue(TRUE);
	motorPay->ccw.setValue(TRUE);
	motorPay->convex.setValue(TRUE);
	motorPay->creaseAngle.setValue(0);
	float fly[][2]={{equiptHeight/2.0,right*0.5},{equiptHeight/2.0,-right*0.5},{-0.05*equiptHeight+equiptHeight/2.0,-right*0.5},{-equiptHeight*0.4+equiptHeight/2.0,-right*0.15},{-equiptHeight*0.4+equiptHeight/2.0,+right*0.15},{-0.05*equiptHeight+equiptHeight/2.0,0.5*right},{equiptHeight/2.0,0.5*right}};
	motorPay->crossSection.setValues(0,7,fly);
	motorPay->endCap.setValue(TRUE);
	motorPay->orientation.setValue(SbVec3f (0,0,1),0);
	float fsy[][2]={{1.0,1.0},{1.0,1.0},{1.0,1.0},{1.0,1.0}};
	motorPay->scale.setValues(0,4,fsy);
	motorPay->solid.setValue(TRUE);
	float fl2y[][3]={{0,0,0},{rear*0.35,0,0},{rear*0.4,0.0,0.0},{rear,0.0,0.0}};
	motorPay->spine.setValues(0,4,fl2y);
	return;
};
void    interface::initPumpShaftDriven(float pSlenght,float pSrad,float equiptHeight,float height)
{
	(getTran("DrivenShaft")->rotation).setValue(SbVec3f(0.0,0.0,1.0),pi/2.0);
	(getCy("DrivenShaftCy")->height).setValue(pSlenght);
	(getCy("DrivenShaftCy")->radius).setValue(pSrad);
	(getTran("DrivenShaft")->translation).setValue(SbVec3f(pSlenght/2,(equiptHeight+height)/2.0,(getTran("DrivenRR")->translation).getValue()[2]/2.0));
	return;
};
void    interface::initPumpShaftDriver(float shiftx,float pSlenght,float pSrad)
{
	(getTran("DriverShaft")->rotation).setValue(SbVec3f(0.0,0.0,1.0),pi/2.0);
	(getCy("DriverShaftCy")->height).setValue(pSlenght);
	(getCy("DriverShaftCy")->radius).setValue(pSrad);
	(getTran("DriverShaft")->translation).setValue(SbVec3f(shiftx-pSlenght/2.0,get_DriverEqtranslation()[1],(getTran("DriverRR")->translation).getValue()[2]/2.0));
	return;
};
void	interface::initIndicDriven(float rad,float hei)
{
	(getCy("indicatorDrivenCy")->radius).setValue(rad);
	(getCy("indicatorDrivenCy")->height).setValue(hei);
	return;
};

void	interface::initIndicDriver(float rad,float hei)
{   
	(getCy("indicatorDriverCy")->radius).setValue(rad);
	(getCy("indicatorDriverCy")->height).setValue(hei);
	return;
};
SbVec3f interface::get_indicatorDriventranslation()
{
	return indicatorDriventranslation;
};

SbVec3f interface::get_Drivencenter()
{
	return Drivencenter;
};
SbVec3f interface::get_Driventranslation()
{
	return Driventranslation;
};

SbVec3f interface::get_DDriventranslation()
{
	return DDriventranslation;
};
SbVec3f interface::get_indicatorDrivertranslation()
{
	return indicatorDrivertranslation;
};

SbVec3f interface::get_Drivercenter()
{
	return Drivercenter;
};
SbVec3f interface::get_Drivertranslation()
{
	return Drivertranslation;
};
SbVec3f interface::get_DDrivercenter()
{
	return DDrivercenter;
};
SbVec3f interface::get_DDrivencenter()
{
	return DDrivencenter;
};
SbVec3f interface::get_DDrivertranslation()
{
	return DDrivertranslation;
};
SbVec3f interface::get_DrivenEqtranslation()
{
	return DrivenEqtranslation;
};
SbVec3f interface::get_DriverEqtranslation()
{
	return DriverEqtranslation;
};
void interface::set_indicatorDriventranslation(SbVec3f in)
{
	indicatorDriventranslation=in;
	if(flag==2)
		(getTran("indicatorDriven")->translation).setValue(in);
};
void interface::set_Drivencenter(SbVec3f in)
{
	Drivencenter=in;
	if(flag==2)
		(getTran("Driven")->center).setValue(in);
};
void interface::set_Driventranslation(SbVec3f in)
{
	Driventranslation=in;
	if(flag==2)
		(getTran("Driven")->translation).setValue(in);
};

void interface::set_DDriventranslation(SbVec3f in)
{
	DDriventranslation=in;
	if(flag==2)
		(getTran("DDriven")->translation).setValue(in);
};
void interface::set_indicatorDrivertranslation(SbVec3f in)
{
	indicatorDrivertranslation=in;
	if(flag==2)
		(getTran("indicatorDriver")->translation).setValue(in);
};

void interface::set_Drivercenter(SbVec3f in)
{
	Drivercenter=in;
	if(flag==2)
		(getTran("Driver")->center).setValue(in);
};
void interface::set_Drivertranslation(SbVec3f in)
{
	Drivertranslation=in;
	if(flag==2)
		(getTran("Driver")->translation).setValue(in);
};
void interface::set_DDrivercenter(SbVec3f in)
{
	DDrivercenter=in;
	if(flag==2)
		(getTran("DDriver")->center).setValue(in);
};
void interface::set_DDrivencenter(SbVec3f in)
{
	DDrivencenter=in;
	if(flag==2)
		(getTran("DDriven")->center).setValue(in);
};
void interface::set_DDrivertranslation(SbVec3f in)
{
	DDrivertranslation=in;
	if(flag==2)
		(getTran("DDriver")->translation).setValue(in);
};
void interface::set_DrivenEqtranslation(SbVec3f in)
{
	DrivenEqtranslation=in;
	if(flag==2)
		(getTran("DrivenEq")->translation).setValue(in);
};
void interface::set_DriverEqtranslation(SbVec3f in)
{
	DriverEqtranslation=in;
	if(flag==2)
		(getTran("DriverEq")->translation).setValue(in);
};
void interface::setclc()
{
	(getTran("indicatorDriven")->translation).setValue(indicatorDriventranslation);
	(getTran("Driven")->center).setValue(Drivencenter);
	(getTran("Driven")->translation).setValue(Driventranslation);
	(getTran("DDriven")->translation).setValue(DDriventranslation);
	(getTran("indicatorDriver")->translation).setValue(indicatorDrivertranslation);
	(getTran("Driver")->center).setValue(Drivercenter);
	(getTran("Driver")->translation).setValue(Drivertranslation);
	(getTran("DDriver")->center).setValue(DDrivercenter);
	(getTran("DDriver")->translation).setValue(DDrivertranslation);
	(getTran("DrivenEq")->translation).setValue(DrivenEqtranslation);
	(getTran("DriverEq")->translation).setValue(DriverEqtranslation);
}
SoVRMLBox * interface::getBox(const char* name)
{
	return (SoVRMLBox *) mVG->getByName(name);
}
SoVRMLCylinder * interface::getCy(const char* name)
{
	return (SoVRMLCylinder *) mVG->getByName(name);
}
SoVRMLTransform * interface::getTran(const char* name)
{
	return (SoVRMLTransform *) mVG->getByName(name);
}
void interface::set_SpoolRotation(SbRotation in)
{
	mSpoolRotation=in;
}
void interface::set_SpoolCentre(SbVec3f in)
{
	mSpoolCentre=in;
}
void interface::initSpool(float ShaftEndGap,float pSrad,SoVRMLCylinder* mCyF)
{
	float SpoolToShaftFrac=0.8;
	SoVRMLShape* mSpShapeFR=new SoVRMLShape();
	SoVRMLShape* mSpShapeFL=new SoVRMLShape();
	SoVRMLAppearance* mApp=new SoVRMLAppearance();
	SoVRMLCylinder* mCy=new SoVRMLCylinder();
	SoVRMLShape* mShape=new SoVRMLShape();
	SoVRMLMaterial* mMat=new SoVRMLMaterial();
	mMat->diffuseColor=*spoolcolor;
	mApp->material=mMat;
	SoVRMLTransform* mSpTrnsFR=new SoVRMLTransform();
	SoVRMLTransform* mSpTrnsFL=new SoVRMLTransform();
	spoolLenght=ShaftEndGap*0.9;
	mShape->appearance=mApp;
	mSpShapeFR->appearance=mApp;
	mSpShapeFL->appearance=mApp;
	mSpShapeFL->geometry=mCyF;
	mSpShapeFR->geometry=mCyF;
	mCy->height=spoolLenght;
	mCy->radius=SpoolToShaftFrac*pSrad;
	mShape->geometry=mCy;
	SoVRMLTransform* mSpool=new SoVRMLTransform();
	(mSpool->translation).setValue(mSpoolCentre);
	(mSpool->rotation).setValue(mSpoolRotation);
	mSpool->addChild(mShape);
	mSpTrnsFR->addChild(mSpShapeFR);
	mSpTrnsFL->addChild(mSpShapeFL);
	mSpool->addChild(mSpTrnsFL);
	mSpool->addChild(mSpTrnsFR);
	(mSpTrnsFL->translation).setValue(SbVec3f(0.0,-0.5*spoolLenght+(mCyF->height).getValue()*0.5,0.0));
	(mSpTrnsFR->translation).setValue(SbVec3f(0.0,0.5*spoolLenght-(mCyF->height).getValue()*0.5,0.0));
	mVG->addChild(mSpool);
}
void interface::initShaftFlage(SoVRMLCylinder* mCyF,float NShlenght,float RShlenght)
{
	SoVRMLShape* mShapeFR=new SoVRMLShape();
	SoVRMLShape* mShapeFL=new SoVRMLShape();
	
	SoVRMLMaterial* mMatFL=new SoVRMLMaterial();
	SoVRMLMaterial* mMatFR=new SoVRMLMaterial();
	SoVRMLAppearance* mAppFR=new SoVRMLAppearance();
	SoVRMLAppearance* mAppFL=new SoVRMLAppearance();
	mMatFL->diffuseColor=*drivencolor;
	mMatFR->diffuseColor=*drivercolor;
	mAppFR->material=mMatFR;
	mAppFL->material=mMatFL;
	mShapeFL->appearance=mAppFL;
	mShapeFR->appearance=mAppFR;
	mCyF->height=0.3;
	mShapeFL->geometry=mCyF;
	mShapeFR->geometry=mCyF;
	SoVRMLTransform* mTrnsFR=new SoVRMLTransform();
	SoVRMLTransform* mTrnsFL=new SoVRMLTransform();
	(mTrnsFL->translation).setValue(SbVec3f(0.0,-0.5*NShlenght+(mCyF->height).getValue()*0.5,0.0));
	(mTrnsFR->translation).setValue(SbVec3f(0.0,0.5*RShlenght-(mCyF->height).getValue()*0.5,0.0));
	mTrnsFR->addChild(mShapeFR);
	mTrnsFL->addChild(mShapeFL);
	getTran("DriverShaft")->addChild(mTrnsFR);
	getTran("DrivenShaft")->addChild(mTrnsFL);
}