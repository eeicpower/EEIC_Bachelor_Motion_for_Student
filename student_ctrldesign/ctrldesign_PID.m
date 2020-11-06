%% ctrldesign_PID_PD
% identification_chirp.mで同定した結果を使う
% 極配置でPID制御器を設計
% PIDはワンさんのparaPID_pp.mを使う
Ts = 1/1000;
%% PID
%clear;
%close all;
s = tf('s');
% 電圧の形をしたトルク指令値から速度の同定結果　7.263e06/(s + 20.15)*exp(-0.002*s)
Gnominal =  (7.263e06/(s + 20.15))*(1/s);
Gnominal_z = c2d(Gnominal,Ts,'tustin');
C = paraPID_pp('pid',Gnominal,10*2*pi);
%pltNyquist(C* Gnominal)
%figure; step((C * Gnominal)/(1 + C * Gnominal))
%figure; pzplot(C)
%pltBode((C * Gnominal*exp(-0.002*s))/(1 + C * Gnominal*exp(-0.002*s)));
%pltNyquist(C*Gnominal*exp(-0.002*s));
% (0.3192 s^2 + 136.6 s + 2.146e04)/(s^2 + 2493 s)
%figure; step(C/(1 + C * Gnominal))
Cpid = C;
Cz = c2d(C,Ts,'tustin');
%(0.1749 z^2 - 0.2794 z + 0.1141)/(z^2 - 0.8902 z - 0.1098) %100Hz
%(0.00241 z^2 - 0.004696 z + 0.002288)/(z^2 - 1.793 z + 0.7928) %10Hz   
%% PD
s = tf('s');
% 電圧の形をしたトルク指令値から速度の同定結果　7.263e06/(s + 20.15)*exp(-0.002*s)
Gnominal =  (7.263e06/(s + 20.15))*(1/s);
omega = 20 * 2 * pi;
Kp = omega^2/(7.263e06);
Kd = (2 * omega -20.15)/7.263e06;
taud = 0.1 * Kd;
Cpd = Kp + Kd*s/(taud*s+1);
Cpd_z = c2d(Cpd,Ts,'tustin'); % (0.06543 z - 0.06111)/(z + 0.9873)     
figure; step(Cpd/(1 + Cpd * Gnominal)) %PD制御では追従せず
pltNyquist(Cpd*Gnominal*exp(-0.002*s));
figure; pzplot(Cpd)