function  GTrain=macro(GTrain)
    global t2 t1 GTrain td2 td1
    if isvalid(GTrain) 
		close(GTrain)
		delete(GTrain)
	end
	b=0.2;
	r=1;
	Vcsize=r;
	Hcsize=1.7;
    GTrain=init('Alignment.wrl',0.2,0.5,3,2,1,2,b,0.5,Hcsize,Vcsize);
	misAlignHorDriver(GTrain,-0.1,-0.1);
    misAlignVerDriver(GTrain,0.1,-0.05);
    misAlignHorDriven(GTrain,-0.2,-0.2);
	misAlignVerDriven(GTrain,0.1,0.1);
	t2=indicatorDriver(GTrain,-Hcsize);
	dd=fzero(@fz,t2(1));
	t1=indicatorDriven(GTrain,dd);
    	a=sqrt((t1(2)-t2(2))^2+(t1(3)-t2(3))^2);
	delta=atan((t1(3)-t2(3))/(t1(2)-t2(2)));
	if (t1(2)-t2(2))<0
		a=a*-1;
	end
	td2=indicatorDriven(GTrain,-Hcsize);
	ddd=fzero(@fzd,td2(1));
	td1=indicatorDriver(GTrain,ddd);
	ad=sqrt((td1(2)-td2(2))^2+(td1(3)-td2(3))^2);
	deltad=atan((td1(3)-td2(3))/(td1(2)-td2(2)));
	if (td1(2)-td2(2))<0
		ad=ad*-1;
	end	
	GTrain.indicatorDriver.translation=td1;
	GTrain.indicatorDriven.translation=td2;
	booli=1;
	for k=1:4
		for rotAngle=0:pi/16:2*pi
			rotAngled=rotAngle+pi;
			if rotAngled>=2*pi
				rotAngled=rotAngled-2*pi;
			end
			idcs=GTrain.iDicCy.size;
			idcsd=GTrain.DriveniDicCy.size;
			iP=indicPosition(delta,pi/2-rotAngle,r,a,b);
			iPd=indicPosition(deltad,pi/2-rotAngled,r,ad,b);
			x=asin(a/(iP+b)*sin(delta+rotAngle));
			xd=asin(ad/(iPd+b)*sin(deltad+rotAngled));				
			GTrain.iDicCy.size=[iP idcs(2) idcs(3)];
			GTrain.DriveniDicCy.size=[iPd idcsd(2) idcsd(3)];
			GTrain.iDic.translation=[-iP/2 0 0];
			GTrain.DriveniDic.translation=[-iPd/2 0 0];
			GTrain.clock.rotation=[0 1 0 x];
			GTrain.Drivenclock.rotation=[0 1 0 xd];
			GTrain.DriverClockClamp.rotation=[0 1 0 rotAngle];
			GTrain.DrivenClockClamp.rotation=[0 1 0 rotAngled];
			if booli 
				view(GTrain); 
				iP0=iP;
				iPd0=iPd;
				booli=0;
				clockBilText=GTrain.clocktext.string;
				DrivenclockBilText=GTrain.Drivenclocktext.string;
			else 
				vrdrawnow;
				pause(0.5);
			end
			GTrain.idicator.rotation=[0 1 0 (iP-iP0)*2*pi];
			GTrain.Drivenidicator.rotation=[0 1 0 (iPd-iPd0)*2*pi];
			GTrain.clocktext.string=[strcat(clockBilText(1),num2str(100*(iP0-iP),'%+4.1f')),strcat(clockBilText(2),num2str(rotAngle*360/2/pi,'%+5.1f'))];
			GTrain.Drivenclocktext.string=[strcat(DrivenclockBilText(1),num2str(100*(iPd0-iPd),'%+4.1f')),strcat(DrivenclockBilText(2),num2str(rotAngled*360/2/pi,'%+5.1f'))];
			if(rotAngle==0 || rotAngle==pi/2 || rotAngle==pi || rotAngle==3*pi/2)
			pause(10);
			end
		end
	end
return;
function x=fz(dd)
    global t2 t1 GTrain
	t1=indicatorDriven(GTrain,dd);
	x=t2(1)-t1(1);
return;
function x=fzd(ddd)
    global td2 td1 GTrain
	td1=indicatorDriver(GTrain,ddd);
	x=td2(1)-td1(1);
return;
