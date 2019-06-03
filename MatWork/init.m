%vwPump=init('Alignment.wrl',0.2,0.5,3,2,1,2,0.1,0.5);
function vwPump=init(vwFilename,rad,height,rear,right,equiptHeight,pSlenght,pSrad,clockrad,Hcsize,Vcsize)
    vwPump = vrworld(vwFilename);
    open(vwPump);
	initParameters(vwPump,rad,height,rear,right,equiptHeight,pSlenght,pSrad,clockrad,Hcsize,Vcsize);
	initClock(vwPump,clockrad,Hcsize,Vcsize);
	initDrivenClock(vwPump,clockrad,Hcsize,Vcsize);
	initStandDriven(vwPump,rad,height,rear,right);
    initStandDriver(vwPump,rad,height,rear,right,pSlenght*2.2);
    initPumpDriver(vwPump,equiptHeight);
    initPumpDriven(vwPump,equiptHeight);
    initPumpShaftDriver(vwPump,pSlenght,pSrad);
    initPumpShaftDriven(vwPump,pSlenght,pSrad);
	initIndicDriven(vwPump,0.01,0.2*pSrad,pSlenght);
	initIndicDriver(vwPump,0.01,0.2*pSrad,pSlenght);
	vwPump.BilCom.translation=[0 -10*height -height];;
return;
function initParameters(vwPump,rad,height,rear,right,equiptHeight,pSlenght,pSrad,clockrad,Hcsize,Vcsize)
	ns=vwPump.DrivenParameters.string;
	nr=vwPump.DriverParameters.string;
	vwPump.DriverParameters.string=[nr(1),strcat(nr(2),num2str(rear)),strcat(nr(3),num2str(equiptHeight)),strcat(nr(4),num2str(right)),strcat(nr(5),num2str(pSlenght)),strcat(nr(6),num2str(rear)),strcat(nr(7),num2str(rear)),strcat(nr(8),num2str(rear)),strcat(nr(9),num2str(rear)),strcat(nr(10),num2str(rear))];
	vwPump.DrivenParameters.string=[ns(1),strcat(ns(2),num2str(rear)),strcat(ns(3),num2str(equiptHeight)),strcat(ns(4),num2str(right)),strcat(ns(5),num2str(pSlenght)),strcat(ns(6),num2str(rear)),strcat(ns(7),num2str(rear)),strcat(ns(8),num2str(rear)),strcat(ns(9),num2str(rear)),strcat(ns(10),num2str(rear))];
return
function initPumpShaftDriven(vwPump,lenght,rad)
    vwPump.DrivenShaft.rotation=[0 0 1 pi/2];
    vwPump.DrivenShaftCy.height=lenght;
    vwPump.DrivenShaftCy.radius=rad;
    vwPump.DrivenShaft.translation=[lenght/2 vwPump.DrivenEq.translation(2) vwPump.DrivenRR.translation(3)/2];
return;
function initPumpShaftDriver(vwPump,lenght,rad)
    vwPump.DriverShaft.rotation=[0 0 1 pi/2];
    vwPump.DriverShaftCy.height=lenght;
    vwPump.DriverShaftCy.radius=rad;
    vwPump.DriverShaft.translation=[vwPump.DriverFL.translation(1)-lenght/2 vwPump.DriverEq.translation(2) vwPump.DriverRR.translation(3)/2];
return;
function initStandDriven(vwPump,rad,height,rear,right)
    vwPump.DrivenRRCy.height=height;
    vwPump.DrivenRLCy.height=height;
    vwPump.DrivenFLCy.height=height;
    vwPump.DrivenFRCy.height=height;
    vwPump.DrivenRRCy.radius=rad;
    vwPump.DrivenRLCy.radius=rad;
    vwPump.DrivenFLCy.radius=rad;
    vwPump.DrivenFRCy.radius=rad;
    vwPump.DrivenRL.translation=[-1*rear 0 0];
    vwPump.DrivenRR.translation=[-1*rear 0 right];
    vwPump.DrivenFL.translation=[0 0 0];
    vwPump.DrivenFR.translation=[0 0 right];
return;
function initStandDriver(vwPump,rad,height,rear,right,shiftx)
    vwPump.DriverRRCy.height=height;
    vwPump.DriverRLCy.height=height;
    vwPump.DriverFLCy.height=height;
    vwPump.DriverFRCy.height=height;
    vwPump.DriverRRCy.radius=rad;
    vwPump.DriverRLCy.radius=rad;
    vwPump.DriverFLCy.radius=rad;
    vwPump.DriverFRCy.radius=rad;
    vwPump.DriverRL.translation=[rear+shiftx 0 0];
    vwPump.DriverRR.translation=[rear+shiftx 0 right];
    vwPump.DriverFL.translation=[shiftx 0 0];
    vwPump.DriverFR.translation=[shiftx 0 right];
return;
function initPumpDriven(vwPump,height)
    vwPump.DrivenEq.translation=vwPump.DrivenRR.translation/2+[0 height/2+vwPump.DrivenRRCy.height/2 0];
    vwPump.DrivenEqBox.size=[-1*vwPump.DrivenRR.translation(1) height vwPump.DrivenRR.translation(3)];
return;
function initPumpDriver(vwPump,height)
    vwPump.DriverEq.translation=vwPump.DriverRR.translation/2+[vwPump.DriverFR.translation(1)/2 height/2+vwPump.DriverRRCy.height/2 0];
    vwPump.DriverEqBox.size=[vwPump.DriverRR.translation(1)-vwPump.DriverFR.translation(1) height vwPump.DriverRR.translation(3)];
return
function initDrivenClock(vwClock,rad,Hcsize,Vcsize)
	Hcsize=-1*Hcsize;
    clocknumbers=nodes(vwClock);
	vwClock.DrivenhclampBox.size=[Vcsize 0.1 0.1];
	vwClock.Drivenhclamp.translation=[Vcsize/2 0 0];
	vwClock.DrivenvclampBox.size=[0.1 -Hcsize 0.1];
	vwClock.Drivenvclamp.translation=[Vcsize Hcsize/2 0];
    vwClock.DrivencirCy.radius=rad+1*0.2*rad;
    vwClock.DrivencirCy.height=0.2*0.2*rad;
    vwClock.Drivencircle.rotation=[1 0 0 pi/2];
    vwClock.Drivencircle.translation=[0 0 +0.18*rad];
	j=1;
	while strcmp(get(clocknumbers(j),'Name'),'Drivenclock')==0
		j=j+1;
	end
    for ii=-1:-1:-10
 		i=-1*ii;
		clocknumbers(j+ii).translation=[0 0 0.22*rad]+0.95*rad*[cos((i-1)*pi/5) sin((i-1)*pi/5) 0]+0.06*[-0.3 1.2 0]*rad;
        clocknumbers(j+ii).scale=0.2*rad*[1 1 1];
		clocknumbers(j+ii).rotation=[0 0 1 -pi/2];
    end
%   for i=1:10
%		ii=i;
%       clocknumbers(j+i).translation=[0 0 0.22*rad]+0.95*rad*[cos((i-1)*pi/5) sin((i-1)*pi/5) 0]+0.06*[0.3 1.2 0]*rad;
%       clocknumbers(j+i).scale=0.2*rad*[1 1 1];
%		clocknumbers(j+ii).rotation=[0 0 1 -pi/2];
%   end
    vwClock.DrivenindicatorCy.size=[0.9*rad 0.05*rad  0.05*rad];
	vwClock.Drivenidicator.translation=[0.4*rad 0.05*rad 0];
	vwClock.Drivenidicator.center=vwClock.Drivenidicator.center-[0.4*rad 0 0];
    vwClock.DriveniDicCy.size=[0.8*rad 0.05*rad 0.05*rad];
	vwClock.Drivenclock.translation=[Vcsize Hcsize 0];
	vwClock.DrivenBilClockText.rotation=[0 0 1 -pi/2];
	vwClock.DrivenBilClockText.translation=[-2*rad rad 0];
	vwClock.DrivenClockClamp.rotation=[0 1 0 pi];
return
function initClock(vwClock,rad,Hcsize,Vcsize)
    clocknumbers=nodes(vwClock);
	vwClock.hclampBox.size=[Vcsize 0.1 0.1];
	vwClock.hclamp.translation=[Vcsize/2 0 0];
	vwClock.vclampBox.size=[0.1 Hcsize 0.1];
	vwClock.vclamp.translation=[Vcsize Hcsize/2 0];
    vwClock.cirCy.radius=rad+1*0.2*rad;
    vwClock.cirCy.height=0.2*0.2*rad;
    vwClock.circle.rotation=[1 0 0 pi/2];
    vwClock.circle.translation=[0 0 +0.18*rad];
	j=1;
	while strcmp(get(clocknumbers(j),'Name'),'clock')==0
		j=j+1;
	end
   for ii=-1:-1:-10
 		i=-1*ii;
       clocknumbers(j+ii).translation=[0 0 0.22*rad]+0.95*rad*[cos((i-1)*pi/5) sin((i-1)*pi/5) 0]+0.06*[-0.3 1.2 0]*rad;
       clocknumbers(j+ii).scale=0.2*rad*[1 1 1];
 		clocknumbers(j+ii).rotation=[0 0 1 -pi/2];
   end
%    for i=1:10
%		ii=i;
%        clocknumbers(j+i).translation=[0 0 0.22*rad]+0.95*rad*[cos((i-1)*pi/5) sin((i-1)*pi/5) 0]+0.06*[0.3 1.2 0]*rad;
%        clocknumbers(j+i).scale=0.2*rad*[1 1 1];
%		clocknumbers(j+ii).rotation=[0 0 1 -pi/2];
%    end
    vwClock.indicatorCy.size=[0.9*rad 0.05*rad  0.05*rad];
	vwClock.idicator.translation=[0.4*rad 0.05*rad 0];
	vwClock.idicator.center=vwClock.idicator.center-[0.4*rad 0 0];
    vwClock.iDicCy.size=[0.8*rad 0.05*rad 0.05*rad];
	vwClock.clock.translation=[Vcsize Hcsize 0];
	vwClock.BilClockText.rotation=[0 0 1 -pi/2];
	vwClock.BilClockText.translation=[2*rad rad 0];
return
function initIndicDriven(vwPump,rad,hei,pSlenght)
	vwPump.indicatorDriven.translation=vwPump.DrivenShaft.translation+[0 0 0];
	vwPump.indicatorDrivenCy.radius=rad;
	vwPump.indicatorDrivenCy.height=hei;
return ;
function initIndicDriver(vwPump,rad,hei,pSlenght)
	vwPump.indicatorDriver.translation=vwPump.DriverShaft.translation+[0 0 0];
	vwPump.indicatorDriverCy.radius=rad;
	vwPump.indicatorDriverCy.height=hei;
return ;
