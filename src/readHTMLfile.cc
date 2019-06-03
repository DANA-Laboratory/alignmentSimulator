#include <stdio.h>
#include <stdlib.h>
#include <string.h>
float getfloatParam(const char * st,const char *sparam) // extract parameter from a string 
{
	char s3[25]="999.999";
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
			i = i + j+1;  // upto = sign 
			j = 0;
			while ((st[i] != '&') && (st[i] != '\0')) {
				if((st[i]>'9' || st[i]<'0') && (st[i]!='.') && (st[i]!='-') && (st[i]!='+'))
					return 999.999;
				s3[j] = st[i] ;
				j++, i++;
			}
			s3[j] = '\0' ;
			return (atof(s3));
		}
	}
	return (atof(s3));
}
int getcharParam(const char * st,const char *sparam,char* s3) /* extract parameter from a string */
{
	s3[0]=0;
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
			i = i + j+1;  /* upto = sign */
			j = 0;
			while ((st[i] != '&') && (st[i] != '\0')) {
				s3[j] = st[i] ;
				j++, i++;
			}
			s3[j] = '\0' ;
			return strlen(s3);
		}
	}
	return 0;
}
int readClearanceTablefile(char* buf,const char* clr)
{
	FILE* rp;
	int i=0;char ch;
	if((rp=fopen("horizontalclearance.html","r"))==NULL)
		exit(0);
	while( feof(rp)== 0 )
	{
		if(buf[i-4]=='@')
		{
			char* tmpin=&(buf[i-3]);
			char* tmpou=&(buf[i-4]);
			i+=getcharParam(clr,tmpin,tmpou)-4;
		}
		else
			buf[i++]=fgetc(rp);
	}
	fclose(rp);
	return i-1;
}
int readSheemsTablefile(char* buf,const char* she)
{
	FILE* rp;
	int i=0;char ch;
	if((rp=fopen("sheemstable.html","r"))==NULL)
		exit(0);
	while( feof(rp)== 0 )
	{
		if(buf[i-4]=='@')
		{
			char* tmpin=&(buf[i-3]);
			char* tmpou=&(buf[i-4]);
			i+=getcharParam(she,tmpin,tmpou)-4;
		}
		else
			buf[i++]=fgetc(rp);
	}
	fclose(rp);
	return i-1;
}
void readTablesRestriction(char* buf,const char* she,const char* clr)
{
	char sheemstabletag[13]="@sheemstable";
	char horizontalclearance[21]="@horizontalclearance";
	FILE* rp;
	int i=0,j=0,k=0,klo=0;char ch;
	if((rp=fopen("tablesrestriction.html","r"))==NULL)
		exit(0);
	while( feof(rp)== 0 )
	{
		char* tmp=&(buf[i-12]);
		char* tmplo=&(buf[i-20]);
		int kk=strcmp(tmp,sheemstabletag);
		int kklo=strcmp(tmplo,horizontalclearance);
		if(kk==0)
			i+=readSheemsTablefile(tmp,she)-12;
		else
		{
			if(kklo==0)
				i+=readClearanceTablefile(tmplo,clr)-20;
			else
				buf[i++]=fgetc(rp);
		}
	}
	buf[i-1]='\0';
	fclose(rp);
	return;
}
void readHTMLfile(char* buf)
{
	FILE* rp;
	int i=0,j=0,k=0,klo=0;char ch;
	if((rp=fopen("index.html","r"))==NULL)
		exit(0);
	while( feof(rp)== 0 )
		buf[i++]=fgetc(rp);
	buf[i-1]='\0';
	fclose(rp);
	return;
}
void readTablesResults(char* buf,const char * res)
{
	FILE* rp;
	int i=0;char ch;
	if((rp=fopen("resultstable.html","r"))==NULL)
		exit(0);
	while( feof(rp)== 0 )
	{
		if(buf[i-4]=='@')
		{
			char* tmpin=&(buf[i-3]);
			char* tmpou=&(buf[i-4]);
			i+=getcharParam(res,tmpin,tmpou)-4;
		}
		else
			buf[i++]=fgetc(rp);
	}
	buf[i-2]='\0';
	fclose(rp);
	return ;
}