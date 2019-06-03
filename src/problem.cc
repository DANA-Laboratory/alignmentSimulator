#include <problem.h>
problem::problem()
{
	const int varcount=26;
	char str[255];
	char varname[varcount][7]={"alg1_1","alg1_2","alg1_3","alg2_1","alg2_2","alg2_3","alg3_1","alg3_2","alg3_3","she2_1","she2_2","she2_3","she3_1","she3_2","she3_3","clr2_1","clr2_2","clr2_3","clr3_1","clr3_2","clr3_3","InCONF","InNCOF","SPcgib","SPlogi","SPimag"};
	FILE* cnf=fopen("config","r");
	char** refS[varcount]={&(alg[0]),&(alg[1]),&(alg[2]),&(alg[3]),&(alg[4]),&(alg[5]),&(alg[6]),&(alg[7]),&(alg[8]),&(she[0]),&(she[1]),&(she[2]),&(she[3]),&(she[4]),&(she[5]),&(clr[0]),&(clr[1]),&(clr[2]),&(clr[3]),&(clr[4]),&(clr[5]),&InCONF,&InNCOF,&SERVER_ADD_cgi,&SERVER_ADD_login,&SERVER_ADD_image};
	int ind;
	do
	{
		ind=-1;
		do
		{
			ind++;
			str[ind]=fgetc(cnf);
		}while(str[ind]!='\n' && str[ind]!=EOF);
		int j=0;
		while(j<varcount)
		{
			if(strncmp(str,varname[j],sizeof(varname[j])-1)==0)
			{
				strcpy(str,&str[sizeof(varname[j])-1]);
				if (str[0]=='=' && str[1]=='\"')
				{
					strcpy(str,&str[2]);
					int ii=0;
					while(str[ii]!='\"')
						ii++;
					str[ii]=0;
					*(refS[j])=new char[ii+1];
					strcpy(*(refS[j]),str);
				}
			}
			j++;
		}
	}while(str[ind]!=EOF);
	fclose(cnf);
	mInitParams.rad=getfloatParam(InCONF,"rad");
	mInitParams.height=getfloatParam(InCONF,"height");
	mInitParams.Rrear=getfloatParam(InCONF,"Rrear");
	mInitParams.Nrear=getfloatParam(InCONF,"Nrear");
	mInitParams.right=getfloatParam(InCONF,"right");
	mInitParams.equiptHeight=getfloatParam(InCONF,"equiptHeight");
	mInitParams.pSrad=getfloatParam(InCONF,"pSrad");
	mInitParams.clockrad=getfloatParam(InCONF,"clockrad");
	mInitParams.VFacecsize=getfloatParam(InCONF,"VFacecsize");
	mInitParams.AdDblHcsize=getfloatParam(InCONF,"AdDblHcsize");
	mInitParams.FlangToShaftFraction=getfloatParam(InCONF,"FlangToShaftFraction");
	mInitParams.NShlenght=getfloatParam(InNCOF,"NShlenght");
	mInitParams.RShlenght=getfloatParam(InNCOF,"RShlenght");
	mInitParams.Vcsize=getfloatParam(InNCOF,"Vcsize");
	mInitParams.ShaftEndGap=getfloatParam(InNCOF,"ShaftEndGap");
	mInitParams.NClockPOsitionOnShaft=getfloatParam(InNCOF,"NClockPOsitionOnShaft");
	mInitParams.RClockPOsitionOnShaft=getfloatParam(InNCOF,"RClockPOsitionOnShaft");
	mInitParams.Hcsize=getfloatParam(InNCOF,"Hcsize");
	mInitParams.mSolveType=SolveTypeDouble;

	mis_AlignValues.DriverRearVertical=0.0;
	mis_AlignValues.DriverRearHorizontal=0.0;
	mis_AlignValues.DriverFrontVertical=0.0;
	mis_AlignValues.DriverFrontHorizontal=0.0;
	mis_AlignValues.DrivenRearVertical=0.0;
	mis_AlignValues.DrivenRearHorizontal=0.0;
	mis_AlignValues.DrivenFrontVertical=0.0;
	mis_AlignValues.DrivenFrontHorizontal=0.0;	
	mov_AlignValues.DriverRearVertical=0.0;
	mov_AlignValues.DriverRearHorizontal=0.0;
	mov_AlignValues.DriverFrontVertical=0.0;
	mov_AlignValues.DriverFrontHorizontal=0.0;
	mov_AlignValues.DrivenRearVertical=0.0;
	mov_AlignValues.DrivenRearHorizontal=0.0;
	mov_AlignValues.DrivenFrontVertical=0.0;
	mov_AlignValues.DrivenFrontHorizontal=0.0;	
	QUERY_STRING[0]=0;
	
}
AlignValues problem::getAlignValues()
{
	AlignValues addAlignValues;
	addAlignValues.DriverRearVertical=mis_AlignValues.DriverRearVertical+mov_AlignValues.DriverRearVertical;
	addAlignValues.DriverRearHorizontal=-1*(mis_AlignValues.DriverRearHorizontal+mov_AlignValues.DriverRearHorizontal);
	addAlignValues.DriverFrontVertical=mis_AlignValues.DriverFrontVertical+mov_AlignValues.DriverFrontVertical;
	addAlignValues.DriverFrontHorizontal=-1*(mis_AlignValues.DriverFrontHorizontal+mov_AlignValues.DriverFrontHorizontal);
	addAlignValues.DrivenRearVertical=mis_AlignValues.DrivenRearVertical+mov_AlignValues.DrivenRearVertical;
	addAlignValues.DrivenRearHorizontal=-1*(mis_AlignValues.DrivenRearHorizontal+mov_AlignValues.DrivenRearHorizontal);
	addAlignValues.DrivenFrontVertical=mis_AlignValues.DrivenFrontVertical+mov_AlignValues.DrivenFrontVertical;
	addAlignValues.DrivenFrontHorizontal=-1*(mis_AlignValues.DrivenFrontHorizontal+mov_AlignValues.DrivenFrontHorizontal);
	return addAlignValues;
}
int problem::set_QUERY_STRING(char* tmp)
{
	
	if(tmp==NULL)
		return 0;//nothing send
	strcpy(QUERY_STRING,tmp);
	if (QUERY_STRING[0]==0)
		return 0;//nothing send
	char tmpCh[250];
	getcharParam(QUERY_STRING,HTMLtag[30],tmpCh);
	mInitParams.mSolveType=(SolveType)atoi(tmpCh);
	getcharParam(QUERY_STRING,HTMLtag[18],value);
	int fileNum=atoi(value);
	if(getcharParam(QUERY_STRING,HTMLtag[29],tmpCh)>0)
		return (100+fileNum);//show restriction table
	clockscale=getfloatParam (QUERY_STRING,"ClockScale");
	if(fileNum>NUMBEROFPROBLEMS-1 || fileNum<0)
		return 3;//model not exist
	mis_AlignValues.DriverRearVertical=getfloatParam(alg[fileNum],HTMLtag[0]);
	mis_AlignValues.DriverRearHorizontal=getfloatParam(alg[fileNum],HTMLtag[1]);
	mis_AlignValues.DriverFrontVertical=getfloatParam(alg[fileNum],HTMLtag[2]);
	mis_AlignValues.DriverFrontHorizontal=getfloatParam(alg[fileNum],HTMLtag[3]);
	mis_AlignValues.DrivenRearVertical=getfloatParam(alg[fileNum],HTMLtag[4]);
	mis_AlignValues.DrivenRearHorizontal=getfloatParam(alg[fileNum],HTMLtag[5]);
	mis_AlignValues.DrivenFrontVertical=getfloatParam(alg[fileNum],HTMLtag[6]);
	mis_AlignValues.DrivenFrontHorizontal=getfloatParam(alg[fileNum],HTMLtag[7]);	
	if(fileNum>2)//restrictions
	{
		restriction.sh_RRL=getfloatParam(she[fileNum-3],"RRL")/1000.0;
		restriction.sh_RRR=getfloatParam(she[fileNum-3],"RRR")/1000.0;
		restriction.sh_RFL=getfloatParam(she[fileNum-3],"RFL")/1000.0;
		restriction.sh_RFR=getfloatParam(she[fileNum-3],"RFR")/1000.0;
		restriction.sh_NFR=getfloatParam(she[fileNum-3],"NFR")/1000.0;
		restriction.sh_NFL=getfloatParam(she[fileNum-3],"NFL")/1000.0;
		restriction.sh_NRR=getfloatParam(she[fileNum-3],"NRR")/1000.0;
		restriction.sh_NRL=getfloatParam(she[fileNum-3],"NRL")/1000.0;
		for (int l=0;l<8;l++)
		{
			getcharParam (clr[fileNum-3],HTMLtag[l+19],tmpCh);
			float a,b;
			int ll=0;
			char ca[22];
			char cb[22];
			int ica=0;
			int icb=0;
			ca[ica]='\0';
			cb[icb]='\0';
			bool next=false;
			while (ll<24)
			{
				char ch=tmpCh[ll];
				if(ch==',')
					next=true;
				else
					if(ch!='[' && ch!=']')
						if (next)
						{
							cb[++icb]='\0';
							strcat(cb,&ch);
						}
						else
						{
							ca[++ica]='\0';
							strcat(ca,&ch);			
						}
				ll++;
			}
			a=atof(ca)/1000.0;
			b=atof(cb)/1000.0;
			switch  (l)
			{
				case 0:
					restriction.cl_RRL[0]=a;
					restriction.cl_RRL[1]=b;				
					break;
				case 1:
					restriction.cl_RRR[0]=a;
					restriction.cl_RRR[1]=b;				
					break;
				case 2:
					restriction.cl_RFL[0]=a;
					restriction.cl_RFL[1]=b;				
					break;
				case 3:
					restriction.cl_RFR[0]=a;
					restriction.cl_RFR[1]=b;				
					break;
				case 4:
					restriction.cl_NFR[0]=a;
					restriction.cl_NFR[1]=b;				
					break;
				case 5:
					restriction.cl_NFL[0]=a;
					restriction.cl_NFL[1]=b;				
					break;
				case 6:
					restriction.cl_NRR[0]=a;
					restriction.cl_NRR[1]=b;				
					break;
				case 7:
					restriction.cl_NRL[0]=a;
					restriction.cl_NRL[1]=b;				
					break;		
			}
		}
	}
	if(fileNum>5)
	{
		restriction.IndicatorRotation[0]=0;
		restriction.IndicatorRotation[1]=pi;
	}
	else
	{
		restriction.IndicatorRotation[0]=0;
		restriction.IndicatorRotation[1]=2*pi;
	}
	if(getcharParam(QUERY_STRING,HTMLtag[16],tmpCh)>0)
		return 1;//suc
	if(getcharParam(QUERY_STRING,HTMLtag[31],tmpCh)>0)
		return -2;//show results
	if(getcharParam(QUERY_STRING,HTMLtag[28],tmpCh)>0)
		return -1;//image
	else
		if(getcharParam(QUERY_STRING,HTMLtag[17],tmpCh)>0)
	{
		int i=8;
		while(i<16)
			if(getfloatParam(QUERY_STRING,HTMLtag[i])>100 || getfloatParam(QUERY_STRING,HTMLtag[i++])<-100)
			return 4;//invalid input
		mov_AlignValues.DriverRearVertical=getfloatParam(QUERY_STRING,HTMLtag[8])/1000.0;
		mov_AlignValues.DriverRearHorizontal=getfloatParam(QUERY_STRING,HTMLtag[9])/1000.0;
		mov_AlignValues.DriverFrontVertical=getfloatParam(QUERY_STRING,HTMLtag[10])/1000.0;
		mov_AlignValues.DriverFrontHorizontal=getfloatParam(QUERY_STRING,HTMLtag[11])/1000.0;
		mov_AlignValues.DrivenRearVertical=getfloatParam(QUERY_STRING,HTMLtag[12])/1000.0;
		mov_AlignValues.DrivenRearHorizontal=getfloatParam(QUERY_STRING,HTMLtag[13])/1000.0;
		mov_AlignValues.DrivenFrontVertical=getfloatParam(QUERY_STRING,HTMLtag[14])/1000.0;
		mov_AlignValues.DrivenFrontHorizontal=getfloatParam(QUERY_STRING,HTMLtag[15])/1000.0;
		//check restrictions
		if(fileNum>2)
		{
			bool b1=mov_AlignValues.DriverRearVertical*-1>restriction.sh_RRL || mov_AlignValues.DriverRearVertical*-1>restriction.sh_RRR;
			bool b2=mov_AlignValues.DriverFrontVertical*-1>restriction.sh_RFL || mov_AlignValues.DriverFrontVertical*-1>restriction.sh_RFR;
			bool b3=mov_AlignValues.DrivenRearVertical*-1>restriction.sh_NRL || mov_AlignValues.DrivenRearVertical*-1>restriction.sh_NRR;
			bool b4=mov_AlignValues.DrivenFrontVertical*-1>restriction.sh_NFL || mov_AlignValues.DrivenFrontVertical*-1>restriction.sh_NFR;
			if (b1 || b2 || b3 || b4)
				return 6;//restriction violation
			b1=mov_AlignValues.DriverRearHorizontal*-1>restriction.cl_RRL[0] || mov_AlignValues.DriverRearHorizontal>restriction.cl_RRL[1];
			b2=mov_AlignValues.DriverFrontHorizontal*-1>restriction.cl_RFL[0] || mov_AlignValues.DriverFrontHorizontal>restriction.cl_RFL[1];
			b3=mov_AlignValues.DrivenRearHorizontal*-1>restriction.cl_NRL[0] || mov_AlignValues.DrivenRearHorizontal>restriction.cl_NRL[1];
			b4=mov_AlignValues.DrivenFrontHorizontal*-1>restriction.cl_NFL[0] || mov_AlignValues.DrivenFrontHorizontal>restriction.cl_NFL[1];
			if(b1 || b2 || b3 || b4)//check horizontal by clr
				return 6;//restriction violation
			b1=mov_AlignValues.DriverRearHorizontal*-1>restriction.cl_RRR[0] || mov_AlignValues.DriverRearHorizontal>restriction.cl_RRR[1];
			b2=mov_AlignValues.DriverFrontHorizontal*-1>restriction.cl_RFR[0] || mov_AlignValues.DriverFrontHorizontal>restriction.cl_RFR[1];
			b3=mov_AlignValues.DrivenRearHorizontal*-1>restriction.cl_NRR[0] || mov_AlignValues.DrivenRearHorizontal>restriction.cl_NRR[1];
			b4=mov_AlignValues.DrivenFrontHorizontal*-1>restriction.cl_NFR[0] || mov_AlignValues.DrivenFrontHorizontal>restriction.cl_NFR[1];
			if(b1 || b2 || b3 || b4)//check horizontal by clr
				return 6;//restriction violation
			if(fileNum>5)//check movable
			{
				if ((mov_AlignValues.DrivenRearVertical!=0)||(mov_AlignValues.DrivenRearHorizontal!=0)||(mov_AlignValues.DrivenFrontVertical!=0)||(mov_AlignValues.DrivenFrontHorizontal)!=0)
					return 6;//restriction violation
			}
		}
		return 2;//movs ok
	}
	return 5;//invalid param sended
}
char* problem::get_ProblemName()
{
	return(value);
}
