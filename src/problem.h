#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define pi 3.1415926535897932384
#define NUMBEROFPROBLEMS 9
#define SIZE1 0.8
#define SIZE2 0.06
#define ERR 1E-6
int getcharParam(const char * st,const char *sparam,char* s3);// extract parameter from a string 
float getfloatParam(const char * st,const char *sparam);// extract parameter from a string 
struct AlignValues
{
	float DriverRearVertical;
	float DriverRearHorizontal;
	float DriverFrontVertical;
	float DriverFrontHorizontal;
	float DrivenRearVertical;
	float DrivenRearHorizontal;
	float DrivenFrontVertical;
	float DrivenFrontHorizontal;
};
enum SolveType {SolveTypeRever, SolveTypeDouble, SolveTypeSpool ,SolveTypeFaceRim,SolveTypeTwoFace};
struct InitParams
{
	float rad;
	float height;
	float Rrear;
	float Nrear;
	float right;
	float equiptHeight;
	float pSrad;
	float clockrad;
	float Vcsize;
	float AdDblHcsize;
	float VFacecsize;
	float Hcsize;
	float ShaftEndGap;
	float NClockPOsitionOnShaft;
	float RClockPOsitionOnShaft;
	SolveType   mSolveType;
	float FlangToShaftFraction;
	float NShlenght;
	float RShlenght;
};
struct Restriction
{
	float IndicatorRotation[2];
	float sh_RRL;
	float sh_RRR;
	float sh_RFL;
	float sh_RFR;
	float sh_NFR;
	float sh_NFL;
	float sh_NRR;
	float sh_NRL;
	float cl_RRL[2];
	float cl_RRR[2];
	float cl_RFL[2];
	float cl_RFR[2];
	float cl_NFR[2];
	float cl_NFL[2];
	float cl_NRR[2];
	float cl_NRL[2];
};
class problem
{
	public:
		problem();
		AlignValues getAlignValues();
		int set_QUERY_STRING(char* tmp);
		char* get_ProblemName();
		InitParams mInitParams;
		char* she[6];
		char* clr[6];
		char* InNCOF;
		char* InCONF;
		char* SERVER_ADD_cgi;
		char* SERVER_ADD_login;
		char* SERVER_ADD_image;
		Restriction restriction;
		int clockscale;
	private:
		char* alg[9];	
		char value[7];
		char QUERY_STRING[512];
		static const char* HTMLtag[];
		AlignValues mis_AlignValues;
		AlignValues mov_AlignValues;
};