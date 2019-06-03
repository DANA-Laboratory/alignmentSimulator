%vwPump=misAlignVerDriven(vwPump,-0.1,0.05);
function misAlignVerDriven(vw,front,rear)
    vw.DrivenFLCy.height=vw.DrivenFLCy.height+front;
    vw.DrivenFL.translation=vw.DrivenFL.translation+[0 front/2 0];
    vw.DrivenFRCy.height=vw.DrivenFRCy.height+front;
    vw.DrivenFR.translation=vw.DrivenFR.translation+[0 front/2 0];
    vw.DrivenRLCy.height=vw.DrivenRLCy.height+rear;
    vw.DrivenRL.translation=vw.DrivenRL.translation+[0 rear/2 0];
    vw.DrivenRRCy.height=vw.DrivenRRCy.height+rear; 
    vw.DrivenRR.translation=vw.DrivenRR.translation+[0 rear/2 0];
	vw.Driven.center=vw.DrivenEq.translation;
    vw.Driven.translation=vw.Driven.translation+[0 (front+rear)/2 0];
    ro=[0 0 1 atan((front-rear)/vw.DrivenEqBox.size(1))];
	vw.Driven.rotation=vw.Driven.rotation+ro;
return ;