%% identification_chirp.m
%% 学生に共有
% date: 2020.11.12
% author: shirato, miyoshi
% 位置で取ると不安定なので，電圧から速度までのシステム同定
% 時間，カウント位置，速度，角度の位置，入力電圧（トルク指令値）を測定。入力電圧（トルク指令値）から速度までをシステム同定。
% その後ctrldesign_PID.mで設計
% % 0.1-50Hz(30s), 51Hz-100 Hz(10s), 101 Hz-500 Hz(1s)に分けてシステム同定すると精度が良く同定できた。
close all;
clear;

%% １回ですべての周波数を同定する場合
load('./matfiles/1109_chirp_1Hz_200Hz_30s.mat');
fs = 1000;
tperiod = 30; 

[~,time_chirpstart] = min(abs(time-tperiod)); %はじめの１周期のデータは捨てる
time_chirpfin = time_chirpstart + (tperiod*1000)*3 -1; %３周期のデータを使う
time_chirp = time(time_chirpstart:time_chirpfin,1);
ctrlcmd_chirp = ctrlcmd(time_chirpstart:time_chirpfin,1);
velocity_chirp = velocity(time_chirpstart:time_chirpfin,1);
t = time_chirp;
x = ctrlcmd_chirp;
y = velocity_chirp;

y_detrend = detrend(y); %detrend
[txy,f] = tfestimate(x,y_detrend,fs*tperiod,[],[],fs); %detrend
G1 = frd(txy,f,'FrequencyUnit','Hz');
figure; bode(G1,2*pi*[1, 200])

G2 = G1;
% fittingがうまく行かない場合，次の行のコメントを外し，frdデータを見て形がきれいな周波数部分を取り出す
G2 = fselect(G1,0,100);

% expfig(['plot/chirp/chirp_0p1Hz_500Hz_G1Bode'],'-png','-pdf','-emf');

% from Torque reference to velocity, 1 order system
Gest = tfest(G2,1);
Gfit = tf(Gest.Numerator,Gest.Denominator);
s = tf('s');
Gfit.name = 'fitting';%Gfit.name = sprintf('$ 7.263e06/(s + 20.15)$');
 %Gfit2.sys = Gfit.sys * exp(-0.002*s);%actually, there must be a time delay
 %Gfit2.name = 'fitting (w delay)';
figure; bode(G2, 2 * pi * [1,200]); hold on; bode(Gfit, 2 * pi * [1,200]); legend;
%expfig(['plot/chirp/chirp_0p1Hz_500Hz_GcatGfitBode'],'-png','-pdf','-emf');

[cxy,f] = mscohere(x,y_detrend,fs*tperiod,[],[],fs);
G1.UserData = cxy;
figure;
semilogx(G1.Frequency,G1.UserData); xlim([1,200]);
xlabel('frequency[Hz]')
ylabel('coherence')
%% 複数のデータを統合する場合
% OP.fmin = 1; OP.fmax = 200;
% G1_ = fselect(G1,0.1,50);
% G2_ = fselect(G2,51,100);
% G3_ = fselect(G3,101,500);
% Gcat.sys = fcat(G1_,G2_,G3_);
% Gcat.name = 'data';
% pltBode(Gcat,OP)
% expfig(['plot/chirp/chirp_0p1Hz_500Hz_GcatBode'],'-png','-pdf','-emf');

% from Torque reference to velocity, 1 order system
% Gfit.sys = tfest(Gcat.sys,1,0);
% s = tf('s');
% %Gfit.name = sprintf('$ 7.263e06/(s + 20.15)$');
% Gfit.name = 'fitting';
%  Gfit2.sys = Gfit.sys * exp(-0.002*s);%actually, there must be a time delay
%  Gfit2.name = 'fitting (w delay)';
%  OP.fmin = 1; OP.fmax = 500;
% pltBode({Gcat,Gfit2},OP);
% expfig(['plot/chirp/chirp_0p1Hz_500Hz_GcatGfitBode'],'-png','-pdf','-emf');