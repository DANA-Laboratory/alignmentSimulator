#include "doMisAlgn.h"
void    doMisAlgn::misAlign(AlignValues mAlignValues,float NeqXsize,float ReqXsize,float eqZsize)
{
	if (flag)
	{
		myI.set_DDrivercenter(myI.get_DriverEqtranslation()+SbVec3f(ReqXsize/2.0,0.0,0.0));
		myI.set_Drivercenter(myI.get_DriverEqtranslation()+SbVec3f(ReqXsize/2.0,0.0,0.0));
		myI.set_DDrivencenter(myI.get_DriverEqtranslation()+SbVec3f(NeqXsize/2.0,0.0,0.0));
		myI.set_Drivencenter(myI.get_DrivenEqtranslation()+SbVec3f(NeqXsize/2.0,0.0,0.0));
		if((mAlignValues.DriverFrontHorizontal<-ERR || mAlignValues.DriverFrontHorizontal>ERR) || (mAlignValues.DriverRearHorizontal<-ERR || mAlignValues.DriverRearHorizontal>ERR))
			clcAlignHorDriver(mAlignValues.DriverFrontHorizontal,mAlignValues.DriverRearHorizontal,ReqXsize,eqZsize);
		if((mAlignValues.DriverFrontVertical<-ERR || mAlignValues.DriverFrontVertical>ERR) || (mAlignValues.DriverRearVertical<-ERR || mAlignValues.DriverRearVertical>ERR))
			clcAlignVerDriver(mAlignValues.DriverFrontVertical,mAlignValues.DriverRearVertical,ReqXsize);
		if((mAlignValues.DrivenFrontHorizontal<-ERR || mAlignValues.DrivenFrontHorizontal>ERR) || (mAlignValues.DrivenRearHorizontal<-ERR || mAlignValues.DrivenRearHorizontal>ERR))
			clcAlignHorDriven(mAlignValues.DrivenFrontHorizontal,mAlignValues.DrivenRearHorizontal,NeqXsize,eqZsize);
		if((mAlignValues.DrivenFrontVertical<-ERR || mAlignValues.DrivenFrontVertical>ERR) || (mAlignValues.DrivenRearVertical<-ERR || mAlignValues.DrivenRearVertical>ERR))
			clcAlignVerDriven(mAlignValues.DrivenFrontVertical,mAlignValues.DrivenRearVertical,NeqXsize);
		flag=false;
	}
	else
	{
		if((mAlignValues.DriverFrontHorizontal<-ERR || mAlignValues.DriverFrontHorizontal>ERR) || (mAlignValues.DriverRearHorizontal<-ERR || mAlignValues.DriverRearHorizontal>ERR))
			misAlignHorDriver(mAlignValues.DriverFrontHorizontal,mAlignValues.DriverRearHorizontal,ReqXsize,eqZsize);
		if((mAlignValues.DriverFrontVertical<-ERR || mAlignValues.DriverFrontVertical>ERR) || (mAlignValues.DriverRearVertical<-ERR || mAlignValues.DriverRearVertical>ERR))
			misAlignVerDriver(mAlignValues.DriverFrontVertical,mAlignValues.DriverRearVertical,ReqXsize);
		if((mAlignValues.DrivenFrontHorizontal<-ERR || mAlignValues.DrivenFrontHorizontal>ERR) || (mAlignValues.DrivenRearHorizontal<-ERR || mAlignValues.DrivenRearHorizontal>ERR))
			misAlignHorDriven(mAlignValues.DrivenFrontHorizontal,mAlignValues.DrivenRearHorizontal,NeqXsize,eqZsize);
		if((mAlignValues.DrivenFrontVertical<-ERR || mAlignValues.DrivenFrontVertical>ERR) || (mAlignValues.DrivenRearVertical<-ERR || mAlignValues.DrivenRearVertical>ERR))
			misAlignVerDriven(mAlignValues.DrivenFrontVertical,mAlignValues.DrivenRearVertical,NeqXsize);
	}
};
void	doMisAlgn::misAlignVerDriver(float front,float rear,float eqXsize)
{
	((SoVRMLCylinder *) SoNode::getByName("DriverFLCy"))->height=(((SoVRMLCylinder *) SoNode::getByName("DriverFLCy"))->height).getValue()+front;
	((SoVRMLTransform *) SoNode::getByName("DriverFL"))->translation=(((SoVRMLTransform *) SoNode::getByName("DriverFL"))->translation).getValue()+SbVec3f(0.0,front/2,0.0);
	((SoVRMLCylinder *) SoNode::getByName("DriverFRCy"))->height=(((SoVRMLCylinder *) SoNode::getByName("DriverFRCy"))->height).getValue()+front;
	((SoVRMLTransform *) SoNode::getByName("DriverFR"))->translation=(((SoVRMLTransform *) SoNode::getByName("DriverFR"))->translation).getValue()+SbVec3f(0.0,front/2,0.0);
	((SoVRMLCylinder *) SoNode::getByName("DriverRLCy"))->height=(((SoVRMLCylinder *) SoNode::getByName("DriverRLCy"))->height).getValue()+rear;
	((SoVRMLTransform *) SoNode::getByName("DriverRL"))->translation=(((SoVRMLTransform *) SoNode::getByName("DriverRL"))->translation).getValue()+SbVec3f(0.0,rear/2.0,0.0);
	((SoVRMLCylinder *) SoNode::getByName("DriverRRCy"))->height=(((SoVRMLCylinder *) SoNode::getByName("DriverRRCy"))->height).getValue()+rear;
	((SoVRMLTransform *) SoNode::getByName("DriverRR"))->translation=(((SoVRMLTransform *) SoNode::getByName("DriverRR"))->translation).getValue()+SbVec3f(0.0,rear/2.0,0.0);
	SbRotation ro(SbVec3f(0.0,0.0,1.0),myP.roRV);
	(((SoVRMLTransform *) SoNode::getByName("Driver"))->rotation).setValue(ro);
	return ;
};
void	doMisAlgn::clcAlignVerDriver(float front,float rear,float eqXsize)
{
	myI.set_Drivertranslation(myI.get_Drivertranslation()+SbVec3f(0.0,(front+rear)/2.0,0.0));
	myP.roRV=atan((rear-front)/eqXsize);
	return ;
};
void doMisAlgn::misAlignVerDriven(float front,float rear,float eqXsize)
{
	((SoVRMLCylinder *) SoNode::getByName("DrivenFLCy"))->height=(((SoVRMLCylinder *) SoNode::getByName("DrivenFLCy"))->height).getValue()+front;
	((SoVRMLTransform *) SoNode::getByName("DrivenFL"))->translation=(((SoVRMLTransform *) SoNode::getByName("DrivenFL"))->translation).getValue()+SbVec3f(0.0,front/2.0,0.0);
	((SoVRMLCylinder *) SoNode::getByName("DrivenFRCy"))->height=(((SoVRMLCylinder *) SoNode::getByName("DrivenFRCy"))->height).getValue()+front;
	((SoVRMLTransform *) SoNode::getByName("DrivenFR"))->translation=(((SoVRMLTransform *) SoNode::getByName("DrivenFR"))->translation).getValue()+SbVec3f(0.0,front/2.0,0.0);
	((SoVRMLCylinder *) SoNode::getByName("DrivenRLCy"))->height=(((SoVRMLCylinder *) SoNode::getByName("DrivenRLCy"))->height).getValue()+rear;
	((SoVRMLTransform *) SoNode::getByName("DrivenRL"))->translation=(((SoVRMLTransform *) SoNode::getByName("DrivenRL"))->translation).getValue()+SbVec3f(0.0,rear/2.0,0.0);
	((SoVRMLCylinder *) SoNode::getByName("DrivenRRCy"))->height=(((SoVRMLCylinder *) SoNode::getByName("DrivenRRCy"))->height).getValue()+rear;
	((SoVRMLTransform *) SoNode::getByName("DrivenRR"))->translation=(((SoVRMLTransform *) SoNode::getByName("DrivenRR"))->translation).getValue()+SbVec3f(0.0,rear/2.0,0.0);
	SbRotation ro(SbVec3f(0.0,0.0,1.0),myP.roNV);
	(((SoVRMLTransform *) SoNode::getByName("Driven"))->rotation).setValue(ro);
	return ;
};
void doMisAlgn::clcAlignVerDriven(float front,float rear,float eqXsize)
{
	myI.set_Driventranslation(myI.get_Driventranslation()+SbVec3f(0.0,(front+rear)/2.0,0.0));
	myP.roNV=atan((front-rear)/eqXsize);
	return ;
};
void doMisAlgn::misAlignHorDriver(float front,float rear,float eqXsize,float eqZsize)
{
	float H=(front-rear)/2;
	float r=sqrt(eqXsize*eqXsize+eqZsize*eqZsize)/2;
	float t=atan(eqZsize/eqXsize);
	float x=r*(cos(t-myP.roRH)-cos(t));
	float xp=r*(cos(t)-cos(t+myP.roRH));
	float Hp=r*(sin(t+myP.roRH)-sin(t));
	((SoVRMLTransform *) SoNode::getByName("DriverFL"))->translation=(((SoVRMLTransform *) SoNode::getByName("DriverFL"))->translation).getValue()+SbVec3f(-1*x,0.0,front);
	((SoVRMLTransform *) SoNode::getByName("DriverFR"))->translation=(((SoVRMLTransform *) SoNode::getByName("DriverFR"))->translation).getValue()+SbVec3f(xp,0.0,(front+rear)/2+Hp); 
	((SoVRMLTransform *) SoNode::getByName("DriverRL"))->translation=(((SoVRMLTransform *) SoNode::getByName("DriverRL"))->translation).getValue()+SbVec3f(-1*xp,0.0,(front+rear)/2-Hp);
	((SoVRMLTransform *) SoNode::getByName("DriverRR"))->translation=(((SoVRMLTransform *) SoNode::getByName("DriverRR"))->translation).getValue()+SbVec3f(x,0.0,rear);
	SbRotation ro(SbVec3f(0.0,1.0,0.0),myP.roRH);
	(((SoVRMLTransform *) SoNode::getByName("DDriver"))->rotation).setValue(ro);
	return ;
};
void doMisAlgn::clcAlignHorDriver(float front,float rear,float eqXsize,float eqZsize)
{
	float H=(front-rear)/2;
	float r=sqrt(eqXsize*eqXsize+eqZsize*eqZsize)/2;
	float t=atan(eqZsize/eqXsize);
	myP.roRH=t+asin((H-r*sin(t))/r);
	myI.set_DDrivertranslation(myI.get_DDrivertranslation()+SbVec3f(0.0,0.0,(front+rear)/2));
	return ;
};
void	doMisAlgn::misAlignHorDriven(float front,float rear,float eqXsize,float eqZsize)
{
	float H=(front-rear)/2;
	float r=sqrt(eqXsize*eqXsize+eqZsize*eqZsize)/2;
	float t=atan(eqZsize/eqXsize);
	float x=r*(cos(t+myP.roNH)-cos(t));
	float xp=r*(cos(t)-cos(t-myP.roNH));
	float Hp=r*(sin(t-myP.roNH)-sin(t));
	((SoVRMLTransform *) SoNode::getByName("DrivenFL"))->translation=(((SoVRMLTransform *) SoNode::getByName("DrivenFL"))->translation).getValue()+SbVec3f(x,0.0,front);
	((SoVRMLTransform *) SoNode::getByName("DrivenFR"))->translation=(((SoVRMLTransform *) SoNode::getByName("DrivenFR"))->translation).getValue()+SbVec3f(-1*xp,0.0,(front+rear)/2+Hp); 
	((SoVRMLTransform *) SoNode::getByName("DrivenRL"))->translation=(((SoVRMLTransform *) SoNode::getByName("DrivenRL"))->translation).getValue()+SbVec3f(xp,0.0,(front+rear)/2-Hp);
	((SoVRMLTransform *) SoNode::getByName("DrivenRR"))->translation=(((SoVRMLTransform *) SoNode::getByName("DrivenRR"))->translation).getValue()+SbVec3f(-1*x,0.0,rear);
	((SoVRMLTransform *) SoNode::getByName("DDriven"))->center=((SoVRMLTransform *) SoNode::getByName("DrivenEq"))->translation.getValue()+SbVec3f(eqXsize/2.0,0.0,0.0);
	SbRotation ro(SbVec3f(0.0,1.0,0.0),myP.roNH);
	(((SoVRMLTransform *) SoNode::getByName("DDriven"))->rotation).setValue(ro);
	return ;
};
void	doMisAlgn::clcAlignHorDriven(float front,float rear,float eqXsize,float eqZsize)
{
	float H=(front-rear)/2;
	float r=sqrt(eqXsize*eqXsize+eqZsize*eqZsize)/2;
	float t=atan(eqZsize/eqXsize);
	myP.roNH=-1*(t+asin((H-r*sin(t))/r));
	myI.set_DDriventranslation(myI.get_DDriventranslation()+SbVec3f(0.0,0.0,(front+rear)/2));
	return ;
};