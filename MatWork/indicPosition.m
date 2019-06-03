function x=indicPosition(delta,teta,r,a,b)
	x=sqrt(a^2+r^2+2*r*a*sin(delta-teta));
	x=x-b;
return;