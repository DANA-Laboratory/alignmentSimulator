#include <feetcorrection.h>
#include <Inventor/SoDB.h>
#include <Inventor/SoInput.h>
#include <Inventor/SoOutput.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/VRMLnodes/SoVRMLText.h>
#include <Inventor/VRMLnodes/SoVRMLBox.h>
#include <Inventor/VRMLnodes/SoVRMLCylinder.h>
#include <Inventor/VRMLnodes/SoVRMLTransform.h>
#include <Inventor/actions/SoWriteAction.h>
#include <Inventor/actions/SoToVRML2Action.h>
#include <Inventor/VRMLnodes/SoVRMLTimeSensor.h>
#include <Inventor/VRMLnodes/SoVRMLPositionInterpolator.h>
#include <Inventor/VRMLnodes/SoVRMLOrientationInterpolator.h>
#include <Inventor/VRMLnodes/SoVRMLSphere.h>
#include <Inventor/VRMLnodes/SoVRMLShape.h>
#include <Inventor/VRMLnodes/SoVRMLMaterial.h>
#include <Inventor/VRMLnodes/SoVRMLAppearance.h>
#include <Inventor/VRMLnodes/SoVRMLExtrusion.h>
#include <sstream>
using namespace std;
class interface
{
	public:
		void	init(InitParams mInitParams);
		
		SbVec3f get_Drivencenter(void);
		SbVec3f get_Drivercenter(void);
		SbVec3f get_Driventranslation(void);
		SbVec3f get_Drivertranslation(void);
		SbVec3f get_DDriventranslation(void);
		SbVec3f get_DDrivertranslation(void);
		SbVec3f get_DDrivercenter(void);
		SbVec3f get_DDrivencenter(void);
		SbVec3f get_indicatorDriventranslation(void);
		SbVec3f get_indicatorDrivertranslation(void);
		SbVec3f get_DrivenEqtranslation(void);
		SbVec3f get_DriverEqtranslation(void);

		void set_Drivencenter(SbVec3f);
		void set_Drivercenter(SbVec3f);
		void set_Driventranslation(SbVec3f);
		void set_Drivertranslation(SbVec3f);
		void set_DDriventranslation(SbVec3f);
		void set_DDrivertranslation(SbVec3f);
		void set_DDrivercenter(SbVec3f);
		void set_DDrivencenter(SbVec3f);
		void set_indicatorDriventranslation(SbVec3f);//main
		void set_indicatorDrivertranslation(SbVec3f);//main
		void set_SpoolRotation(SbRotation);
		void set_SpoolCentre(SbVec3f);
		SoVRMLGroup* mVG;
	private:
		void set_DrivenEqtranslation(SbVec3f);//main
		void set_DriverEqtranslation(SbVec3f);//main

		void    initclc(float shiftx,float NShlenght,float RShlenght,float equiptHeight,float height,float Rrear,float right,float Nrear);
		void	initParameters(SolveType mSolveType,float rad,float ShaftEndGap,float Nrear,float Rrear,float right,float equiptHeight,float NShlenght,float RShlenght,float pSrad,float NClockPosition,float RClockPosition,float Hcsize,float Vcsize,float AdDblHcsize);
		void	initClock(float clockrad,float Hcsize,float Vcsize,float clockpositiononshaft);
		void	initDoubleClock(float clockrad,float Hcsize,float Vcsize,float clockpositiononshaft,float clockZRotation=0);
		void	initDrivenClock(float clockrad,float Hcsize,float Vcsize,float clockpositiononshaft);
		void	initNghalh(float height,float right);
		void	initStandDriven(float rad,float height,float rear,float right);
		void    initStandDriver(float rad,float height,float rear,float right,float shiftx);
		void    initPumpDriver(float equiptHeight,float height,float rear,float right,float shiftx);
		void    initPumpDriven(float equiptHeight,float height,float rear,float right);
		void    initPumpShaftDriver(float shiftx,float pSlenght,float pSrad);
		void    initPumpShaftDriven(float pSlenght,float pSrad,float equiptHeight,float height);
		void	initIndicDriven(float rad,float hei);
		void	initIndicDriver(float rad,float hei);
		void	initSpool(float ShaftEndGap,float pSrad,SoVRMLCylinder* mCyF);
		void    initShaftFlage(SoVRMLCylinder* mCyF,float NShlenght,float RShlenght);
		
		SbVec3f indicatorDriventranslation;
		SbVec3f indicatorDrivertranslation;
		SbVec3f Drivencenter;
		SbVec3f Drivercenter;
		SbVec3f Driventranslation;
		SbVec3f Drivertranslation;
		SbVec3f DDriventranslation;
		SbVec3f DDrivertranslation;
		SbVec3f DrivenEqtranslation;
		SbVec3f DriverEqtranslation;
		SbVec3f DDrivercenter;
		SbVec3f DDrivencenter;
		void setclc();
		SoVRMLTransform * getTran(const char* name);
		SoVRMLCylinder * getCy(const char* name);
		SoVRMLBox * getBox(const char* name);
		static char flag;
		SoVRMLTransform* mSpool;
		float spoolLenght;

		SbRotation mSpoolRotation;
		SbVec3f mSpoolCentre;
		SoSFColor*	drivercolor;
		SoSFColor*   drivencolor;
		SoSFColor*   spoolcolor;
};
