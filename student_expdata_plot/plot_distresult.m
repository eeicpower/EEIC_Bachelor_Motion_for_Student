%% plot_distresult.m
%% 学生に共有
% date: 2020.11.5 
% author: shirato
% 外乱オブザーバの推定結果
% fbresultのデータ用
% 外乱を調べるために指令値はもとの位置のままとして actposがrefout = initial_pos_num(P100)に戻ってくるか見ている
% 自分で書いたプログラムをもとに refoutを使うかinitialposrefを使うか判断すること

%load('')でmatfilesを読み込むこと。
%expfig('')で出力したいファイル名を指定すること。
close all;
clear;
%%
load('./matfiles/1105_dob.mat') % change name
t = time; refpos = refout; 
%vdistsim: ソフトウェア的に入れた外乱
%vdistest: 推定した外乱

figure; plot(t,vdistsim,'k');xlim([0,5]); hold on; plot(t,vdistest);
xlabel('time [s]')
ylabel('disturbance input and estimation[V]');
%expfig(['plot/fbdata/pid_10hz_dis_1_dist'],'-png','-pdf','-emf'); %change!

return