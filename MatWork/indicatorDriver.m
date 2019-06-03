%vwPump=indicatorDriver(vwPump,0);
function tr=indicatorDriver(vw,len)
	tr=vw.indicatorDriver.translation+[len 0 0];
	%ver
	a=vw.Driver.center(1)-cos(vw.Driver.rotation(4))*(vw.Driver.center(1)-tr(1));
	b=sin(vw.Driver.rotation(4))*(vw.Driver.center(1)-tr(1));
	tr=tr+vw.Driver.translation;
	tr=tr+[0 -b 0];
	tr=[a tr(2) tr(3)];
	%hor
	a=vw.DDriver.center(1)-cos(vw.DDriver.rotation(4))*(vw.DDriver.center(1)-tr(1));
	b=sin(vw.DDriver.rotation(4))*(vw.DDriver.center(1)-tr(1));
	tr=tr+vw.DDriver.translation;
	tr=tr+[0 0 b];
	tr=[a tr(2) tr(3)];
return ;