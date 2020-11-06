%% plot_fbresult.m
%% 学生に共有
% date: 2020.10.19 
% author: shirato
% ctrldesign_PID.mで設計した制御器を用いてPID，PD
% fbresultのデータ用
% 外乱を調べるために指令値はもとの位置のままとして actposがrefout = initial_pos_num(P100)に戻ってくるか見ている
% 自分で書いたプログラムをもとに refoutを使うかinitialposrefを使うか判断すること

%load('')でmatfilesを読み込むこと。
%expfig('')で出力したいファイル名を指定すること。
close all;
clear;

%% PID
load('./matfiles/1105_pid.mat') % change name
t = time; refpos = refout; distvoltage = vdistsim;
hfig = figure; plot(t,refpos); hold on; plot(t,actpos); xlim([0,5]);%ylim([10*10^6, 12*10^6]);
xlabel('time [s]')
ylabel('position [count]');
legend('ref','act');
pfig = pubfig(hfig); pfig.Dimension = [12 8];
%expfig(['plot/fbdata/pid_10hz_dis_1'],'-png','-pdf','-emf'); %change!

hfig = figure; plot(t,distvoltage,'k');xlim([0,5]);
xlabel('time [s]')
ylabel('software disturbance [V]');
pfig = pubfig(hfig); pfig.Dimension = [12 8];
%expfig(['plot/fbdata/pid_10hz_dis_1_dist'],'-png','-pdf','-emf'); %change!

return
%% PD
clear; close all;
%load('./matfiles/MATDATANAME.mat') % change name
t = time; refpos = refout; distvoltage = vdistsim;

hfig = figure; plot(t,refpos); hold on; plot(t,actpos); xlim([0,5]); 
xlabel('time [s]')
ylabel('position [count]');
legend('ref','act');
pfig = pubfig(hfig); pfig.Dimension = [12 8];
%expfig(['plot/fbdata/pd_20hz_dis_1'],'-png','-pdf','-emf'); %change!
