%% ctrldesign_PID_PD
% 2020/11/20 Shirato, Miyoshi
% identification_chirp.mで同定した結果を使う
% 極配置でPID制御器を設計
% PIDはワンさんのparaPID_pp.mを使う。
% 学生の書いたdesignPID.mを使っても良い。
Ts = 1/1000;
%% PID
%clear;
%close all;
s = tf('s');
% 重根配置したい周波数をここに入力
omega = 20 * 2 * pi;

% トルク指令値から速度の同定結果をここに入力。後ろの * (1/s);を消さないこと。
Gnominal =  0 * (1/s);

Gnominal_z = c2d(Gnominal,Ts,'tustin');

% designPIDを使ったプログラムを書く。
Cpid = 0; % paraPID_pp('pid',Gnominal,omega);

% PMAC実装のための単位換算  [Nm/rad] -> [V/count]
Cpid_c_pmac = Cpid / 0.98 / 312500 * (2 * pi);
Cpid_d_pmac = c2d(Cpid_c_pmac,Ts,'tustin')

%% PD
s = tf('s');
% 電圧の形をしたトルク指令値から速度の同定結果
% designPDを使ったプログラムを書く。
Cpd = 0;

% PMAC実装のための単位換算  [Nm/rad] -> [V/count]
Cpd_c_pmac = Cpd / 0.98 / 312500 * (2 * pi);
Cpd_d_pmac = c2d(Cpd_c_pmac,Ts,'tustin')
