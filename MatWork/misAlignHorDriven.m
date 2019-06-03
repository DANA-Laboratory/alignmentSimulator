%vwPump=misAlignHorDriven(vwPump,-0.2,0.2);
function misAlignVerDriven(vw,front,rear)
	H=(front-rear)/2;
	r=sqrt(vw.DrivenEqBox.size(1)^2+vw.DrivenEqBox.size(3)^2)/2;
	t=atan(vw.DrivenEqBox.size(3)/vw.DrivenEqBox.size(1));
    d=t+asin((H-r*sin(t))/r);
	x=r*(cos(t-d)-cos(t));
	xp=r*(cos(t)-cos(t+d));
	Hp=r*(sin(t+d)-sin(t));
    vw.DrivenFL.translation=vw.DrivenFL.translation+[x 0 front];
    vw.DrivenFR.translation=vw.DrivenFR.translation+[-xp 0 (front+rear)/2+Hp]; 
    vw.DrivenRL.translation=vw.DrivenRL.translation+[xp 0 (front+rear)/2-Hp];
    vw.DrivenRR.translation=vw.DrivenRR.translation+[-x 0 rear];
	vw.DDriven.center=vw.DrivenEq.translation;
    ro=[0 1 0 -d];
	vw.DDriven.rotation=ro;
    vw.DDriven.translation=vw.DDriven.translation+[0 0 (front+rear)/2];
return ;