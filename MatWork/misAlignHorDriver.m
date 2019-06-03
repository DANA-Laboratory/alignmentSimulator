%vwPump=misAlignHorDriver(vwPump,-0.2,0.2);
function misAlignVerDriver(vw,front,rear)
	H=(front-rear)/2;
	r=sqrt(vw.DriverEqBox.size(1)^2+vw.DriverEqBox.size(3)^2)/2;
	t=atan(vw.DriverEqBox.size(3)/vw.DriverEqBox.size(1));
    d=t+asin((H-r*sin(t))/r);
	x=r*(cos(t-d)-cos(t));
	xp=r*(cos(t)-cos(t+d));
	Hp=r*(sin(t+d)-sin(t));
    vw.DriverFL.translation=vw.DriverFL.translation+[-x 0 front];
    vw.DriverFR.translation=vw.DriverFR.translation+[xp 0 (front+rear)/2+Hp]; 
    vw.DriverRL.translation=vw.DriverRL.translation+[-xp 0 (front+rear)/2-Hp];
    vw.DriverRR.translation=vw.DriverRR.translation+[x 0 rear];
	vw.DDriver.center=vw.DriverEq.translation;
    ro=[0 1 0 d];
	vw.DDriver.rotation=ro;
    vw.DDriver.translation=vw.DDriver.translation+[0 0 (front+rear)/2];
return ;