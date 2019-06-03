%initClock('Clock.wrl',5)
function initClock(vwClockFilename,rad)
    vwClock = vrworld(vwClockFilename);
    open(vwClock);
    clocknumbers=nodes(vwClock);
    vwClock.cirCy.radius=rad+1;
    vwClock.cirCy.height=0.2;
    vwClock.circle.rotation=[1 0 0 pi/2];
    vwClock.circle.translation=[0 0 -0.2];
    for i=1 : 10
        clocknumbers(i).translation=(rad-1)*[sin((i-1)*pi/5) cos((i-1)*pi/5) 0]-[0.3 0.3 0];
        clocknumbers(10+i).translation=(rad)*[sin((i-11)*pi/5) cos((i-11)*pi/5) 0];
        clocknumbers(10+i).rotation=[0 0 1 (11-i)*pi/5];
    end
    view(vwClock);
    %close(vwClock);
    delete(vwClock);
return
