%vwPump=misAlignVerDriver(vwPump,-0.1,0.05);
function misAlignVerDriver(vw,front,rear)
    vw.DriverFLCy.height=vw.DriverFLCy.height+front;
    vw.DriverFL.translation=vw.DriverFL.translation+[0 front/2 0];
    vw.DriverFRCy.height=vw.DriverFRCy.height+front;
    vw.DriverFR.translation=vw.DriverFR.translation+[0 front/2 0];
    vw.DriverRLCy.height=vw.DriverRLCy.height+rear;
    vw.DriverRL.translation=vw.DriverRL.translation+[0 rear/2 0];
    vw.DriverRRCy.height=vw.DriverRRCy.height+rear; 
    vw.DriverRR.translation=vw.DriverRR.translation+[0 rear/2 0];
	vw.Driver.center=vw.DriverEq.translation;
    vw.Driver.translation=vw.Driver.translation+[0 (front+rear)/2 0];
    ro=[0 0 1 atan((rear-front)/vw.DriverEqBox.size(1))];
	vw.Driver.rotation=vw.Driver.rotation+ro;
return ;