%vwPump=indicatorDriven(vwPump,0);
function tr=indicatorDriven(vw,len)
	tr=vw.indicatorDriven.translation-[len 0 0];
	%ver
	a=cos(vw.Driven.rotation(4))*(-vw.Driven.center(1)+tr(1))+vw.Driven.center(1);
	b=sin(vw.Driven.rotation(4))*(-vw.Driven.center(1)+tr(1));
	tr=tr+vw.Driven.translation;
	tr=tr+[0 b 0];
	tr=[a tr(2) tr(3)];
	%hor
	a=cos(vw.DDriven.rotation(4))*(-vw.DrivenRR.translation(1)/2+tr(1))+vw.DrivenRR.translation(1)/2;
	b=-sin(vw.DDriven.rotation(4))*(-vw.DrivenRR.translation(1)/2+tr(1));
	tr=tr+vw.DDriven.translation;
	tr=tr+[0 0 b];
	tr=[a tr(2) tr(3)];
return ;