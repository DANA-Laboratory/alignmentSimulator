# include <Inventor/SbLinear.h>
#define pi 3.1415926535897932384
class L_P_I //find r(rx,ry,rz) which is on plane whith normal direction n(nx,ny,nz) and r0(r0x,r0y,r0z) on it and also r is on line b(bx,by,bz) and c(cx,cy,cz)
{
public:
	L_P_I(SbVec3f r0,SbVec3f n,SbVec3f b,SbVec3f c)
	{
		nx=n[0];
		ny=n[1];
		nz=n[2];
		cx=c[0];
		cy=c[1];
		cz=c[2];
		bx=b[0];
		by=b[1];
		bz=b[2];
		r0x=r0[0];
		r0y=r0[1];
		r0z=r0[2];
		r[0]=rx();
		r[1]=ry();
		r[2]=rz();
		SbVec3f dr=r-r0;
		a=sqrt(dr[1]*dr[1]+dr[2]*dr[2]);
		if (a==0.0)
			delta=0.0;
		else
			delta=atan((r0[2]-r[2])/(r0[1]-r[1])); 
		if ((r[1]-r0[1])<=0)
			a=a*-1;
	};
	SbVec3f r;
	float delta;
	float a; 
private:
	float rx()
	{
		return -1*(bx*cy*ny-by*cx*ny+bx*cz*nz-bz*cx*nz-bx*nx*r0x-bx*ny*r0y-bx*nz*r0z+cx*nx*r0x+cx*ny*r0y+cx*nz*r0z)/(bx*nx+by*ny+bz*nz-cx*nx-cy*ny-cz*nz);
	};
	float ry()
	{
		return (bx*cy*nx-by*cx*nx-by*cz*nz+bz*cy*nz+by*nx*r0x+by*ny*r0y+by*nz*r0z-cy*nx*r0x-cy*ny*r0y-cy*nz*r0z)/(bx*nx+by*ny+bz*nz-cx*nx-cy*ny-cz*nz);
	};
	float rz()
	{
		return (bx*cz*nx-bz*cx*nx+by*cz*ny-bz*cy*ny+bz*nx*r0x+bz*ny*r0y+bz*nz*r0z-cz*nx*r0x-cz*ny*r0y-cz*nz*r0z)/(bx*nx+by*ny+bz*nz-cx*nx-cy*ny-cz*nz);
	};
	float nx,ny,nz,cx,cy,cz,bx,by,bz,r0x,r0y,r0z;
};
