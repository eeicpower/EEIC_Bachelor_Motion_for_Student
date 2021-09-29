%% 実験のtxtファイルをmatファイルに変えるファイル
%
% 2020/11/20 Shirato, Miyoshi
%
% このスクリプトを実行する。
% ダイアログが出てくるので変換したい.txtを選択する。
% 「インポート」ウインドウが出てくるので列ベクトル，文字ベクトルのセル配列，でインポートする
% txtのファイル名.matがmatfilesフォルダに作成される。
% P変数でデータを取ること！！(pshm->Motor[1].ActPosなどは読み取れない)
%
% このスクリプトでやっていること
% P98 P1 P2 P3 P5 P6 P7 P9 P10 P100 のデータを取得し，上のPMACnames，MATnamesを選択
% 単位系を変換する
% 名前を変える

clear
[filename,path] = uigetfile('*.txt');
if isequal(filename,0)
    disp('User selected Cancel');
    return
end
fullpath = strcat(path,filename);
T = readtable(fullpath);

%% 単位換算の前処理
% sysP98
% 時刻。
SysP98 = T.Sys_P_98_;

% sysP1
% モータの角速度。
SysP1 = T.Sys_P_1_;

% sysP2
% モータの位置指令値。
SysP2 = T.Sys_P_2_;

% sysP3
% モータの位置誤差。
SysP3 = T.Sys_P_3_;

% sysP5
% トルク制御入力。
SysP5 = T.Sys_P_5_;

% sysP6
% モータの位置。
SysP6 = T.Sys_P_6_;

% sysP7
% 外乱オブザーバ実験におけるv0信号（PD制御器出力）。
SysP7 = T.Sys_P_7_;

% sysP9
% 外乱オブザーバ実験におけるソフトウェア外乱入力。
SysP9 = T.Sys_P_9_;

% sysP10
% 外乱オブザーバ実験における推定外乱出力。
SysP10 = T.Sys_P_10_;

% sysP100
% モータ初期位置。
SysP100 = T.Sys_P_100_;

% 読み込み終わったのでTを消去
clearvars T

%%
% select this one
PMACnames = {'SysP98','SysP1','SysP2','SysP3','SysP5','SysP6','SysP9','SysP10','SysP100'};
MATnames = {'time','velocity','refout','error','ctrlcmd','actpos','vdistsim','vdistest','initialposref'};

% for test dataファイルの中のデータをインポートしてmatfilesが出てくるか確認するためのもの
%PMACnames = {'SysP98','SysP2','SysP3','SysP5','SysP6'};
%MATnames = {'time','refout','error','ctrlcmd','actpos'};

for k = 1:length(PMACnames)
    eval([MATnames{k} '=' PMACnames{k} ';'])
    eval(['s.' MATnames{k} ' = ' MATnames{k} ';'])   
end

sfile = ['./matfiles/', [filename(1:find(filename == '.', 1, 'last')), 'mat']];
save(sfile,'-struct','s');
