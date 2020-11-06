%% 実験のcsvファイルをmatファイルに変えるファイル
% .txtを.csvにする
% matlabでcsvを開いて列ベクトル，文字ベクトルのセル配列，でインポートする
% ワークスペースにデータをインポート
% P変数でデータを取ること！！(pshm->Motor[1].ActPosなどは読み取れない)
% P98 P1 P2 P3 P5 P6 P7 P9 P10 P100 のデータを取得し，上のPMACnames，MATnamesを選択
% 名前を変える
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

sfile = './matfiles/1105_dob.mat';
save(sfile,'-struct','s');



