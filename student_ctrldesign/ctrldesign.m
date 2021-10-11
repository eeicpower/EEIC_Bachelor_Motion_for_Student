%% ctrldesign
% 2021/9/29 Shirato, Miyoshi
% 2021/10/11 Sakai: PIDとdistを統合(model2hdrを使う関係で)
% 
% このファイルについて:
% identification_chirp.mで同定した結果を使う
% 1. 極配置でPID, PD制御器を設計
% 2. 外乱オブザーバに使うローパスフィルタを設計
clear;
close all;

s = tf('s');
Ts = 1/1000;

% Gnominal = トルク指令値[Nm]から位置[rad]までのノミナルモデル
% identification_chirp.m の同定結果（注: 速度まで）をここに入力。後ろの * (1/s);を消さないこと。
Gnominal = (1/(s+1)) * (1/s);

%% PID
% PIDはワンさんのparaPID_pp.mを使う。
% 学生の書いたdesignPID.mを使っても良い。

% 重根配置したい周波数をここに入力
omega = 5 * 2 * pi; % [rad/s]

% designPIDを使ったプログラムを書く。
Cpid = tf(1, [1, 1, 1]); % paraPID_pp('pid',Gnominal,omega);

%% PD

% designPDを使ったプログラムを書く。
Cpd = tf(1, [1, 1]);

%% 外乱オブザーバ

% LPFの周波数をここに入力
wlpfdist = 50 * 2 * pi; % [rad/s]

% LPFの伝達関数。プラントが2次なので2次以上のフィルタとする。
% 例えば2次バターワースLPFとか。
Clpfdist = wlpfdist^2/(s^2 + 2*sqrt(0.5)*wlpfdist*s + wlpfdist^2);

% LPF * 逆ノミナルプラントの離散時間伝達関数。G_lpf * P_n^{-1}
INVQmath = Clpfdist/Gnominal;

%% C言語出力

K.pid = c2d(Cpid, Ts, 'tustin');
K.pd = c2d(Cpd, Ts, 'tustin');
K.LFmath = c2d(Clpfdist, Ts, 'tustin');
K.INVQmath = c2d(INVQmath, Ts, 'tustin');

[para] = model2hdr('ctrl_para.h', K);
% ctrl_para.h に出力されるので、PMACプロジェクト内にコピーする
