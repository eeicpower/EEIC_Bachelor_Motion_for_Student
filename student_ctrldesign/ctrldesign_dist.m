%% ctrldesign_dist
% 2021/9/29 Shirato, Miyoshi
% identification_chirp.mで同定した結果を使う
% 外乱オブザーバに使うローパスフィルタを設計
%
clear;
close all;
s = tf('s');
z = tf('z');
Ts = 1/1000;

% トルク指令値から速度の同定結果をここに入力。後ろの * (1/s);を消さないこと。
Gnominal =  0 * (1/s);

% LPFの周波数。
flpfdist = 50;

wlpfdist = flpfdist*2*pi;

% LPFの伝達関数。プラントが2次なので2次以上のフィルタとする。
% 例えば2次バターワースLPFとか。
Clpfdist = wlpfdist^2/(s^2 + 2*sqrt(0.5)*wlpfdist*s + wlpfdist^2);

% LPFの離散時間伝達関数。G_lpf
LPFmath = Clpfdist;
LPFmath_d = c2d(LPFmath, Ts,'tustin')

% LPF * 逆ノミナルプラントの離散時間伝達関数。G_lpf * P_n^{-1}
INVQmath = Clpfdist/Gnominal;
INVQmath_d = c2d(INVQmath, Ts, 'tustin')
