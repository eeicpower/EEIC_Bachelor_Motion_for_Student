%% ctrldesign_dist

%clear;
close all;
s = tf('s');
Ts = 1/1000;
flpfdist = 1;
wlpfdist = flpfdist*2*pi; %roll off周波数　180Hz以上だとまずいかもしれないから
Clpfdist = wlpfdist^2/(s^2 + 2*0.7*wlpfdist*s + wlpfdist^2);
Clpfdist3 = wlpfdist^3/((s^2 + 2*0.7*wlpfdist*s + wlpfdist^2)*(s + wlpfdist));

Clpfdist_z = c2d(Clpfdist, Ts, 'tustin');
Clpfdist3_z = c2d(Clpfdist3, Ts, 'tustin');
% (0.4354 z^2 + 0.8709 z + 0.4354)/(z^2 + 0.5179 z + 0.2238)     
C_ObsBlk1 = 1/(1-Clpfdist);
C_ObsBlk1_z = c2d(C_ObsBlk1,Ts,'tustin');
%(1.771 z^2 + 0.9174 z + 0.3964)/(z^2 - 0.6252 z - 0.3748)//500Hz
%(1.21 z^2 - 0.644 z + 0.2741)/(z^2 - 1.064 z + 0.06403)
z = tf('s');
C_ObsBlk1_z_500_ = (1.771 *z^2 + 0.9174 *z + 0.3964)/(z^2 - 0.6252 *z - 0.3748);%500Hz
Gnominal =  (7.263e06/(s + 20.15))*(1/s);
C_ObsBlk2 = (Clpfdist/(1-Clpfdist))/Gnominal;
minreal(C_ObsBlk2)
C_ObsBlk2_z = c2d(minreal(C_ObsBlk2),Ts,'tustin');
%(0.1168 z - 0.1145)/(z - 0.06403)
C_ObsBlk2_z_500_ = (0.429 * z - 0.4205)/( z + 0.3748);%500Hz

LFmath = Clpfdist;
LFmath_z = c2d(LFmath, Ts,'tustin');%2nd order (0.06415 z^2 + 0.1283 z + 0.06415)/(z^2 - 1.172 z + 0.4283)
INVQmath = Clpfdist/Gnominal;
INVQmath_z = c2d(INVQmath, Ts, 'tustin');%2nd order (0.03569 z^2 - 0.07066 z + 0.03497)/(z^2 - 1.172 z + 0.4283)

return
%% PIDと等価変換
%Gnominal =  (7.263e06/(s + 20.15))*(1/s);
Kt = 7.263e06;
J = 1;
D = 20.15;
K1 = 0.000551; K2 = 0.00928; K3 = 8.95e-06; tau = 0.00433;
%syms Kt J D K1 K2 K3 tau
syms Kd Kp omega s
eqn1 = K3 == Kd + (tau*s + 1)*(J*omega)/(Kt);
eqn2 = K2 == omega * Kp;
eqn3 = K1 == Kp + omega/(tau*s + 1)*Kd + (D * omega)/(Kt);
eqns = [eqn1 eqn2 eqn3];
S = solve(eqns,[Kd Kp omega],'ReturnConditions',true);
S.Kd
S.Kp
S.omega
