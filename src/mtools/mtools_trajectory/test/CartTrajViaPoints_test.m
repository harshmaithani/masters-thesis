%%

%% load

CartTrajViaPoints_test_q ;
t = time ;
q = data ; 

clear data
CartTrajViaPoints_test_qd ;
qd = data ; 

clear data
CartTrajViaPoints_test_qdd ;
qdd = data ; 

%% plot

figure(1) ; 
subplot(311) ; plot(t, q') ;
xaxis([0 t(end)])

subplot(312) ; plot(t, qd') ;
xaxis([0 t(end)])

subplot(313) ; plot(t, qdd') ;
xaxis([0 t(end)])

%% plot 3D

figure(2) ;

P = [ 0 1 0 0 ;
      0 0 1 0 ;
      0 0 0 1 ].*0.1 ;  
rf = [1 2 1 3 1 4] ;
[x, y, z] = splitrow(P(:,rf)) ;
plot3(x, y, z, 'k') ;
axis equal
axis([-1 1 -1 1 -1 1].*.5)

frame = line('parent', gca, 'color', 'r', 'xdata', [], 'ydata', [], 'zdata', []) ;
clear p e
P(4,:) = 1 ;
rp = 1:3 ; 
re = 4:6 ;
n_step = size(q,2) ;

for i=1:n_step
    t(i)
    p = q(rp,i) ; 
    e = q(re,i) ;
    
    T = [e2R(e) p ; 0 0 0 1] ;
    PP = T*P ;
    [x, y, z, ~] = splitrow(PP(:,rf)) ;
    set(frame, 'xdata', x) ;
    set(frame, 'ydata', y) ;
    set(frame, 'zdata', z) ;
    pause(0.01) ;
    
end