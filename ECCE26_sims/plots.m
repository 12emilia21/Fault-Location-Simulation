close all;
clear;
clc;

%% ============================================================
% Files to compare
%% ============================================================
file1 = 'C:\Users\mem21\OneDrive\Documents\MATLAB\ls_solution\fault_location_sims\ECCE26_sims\estimations_25.mat';
file2 = 'C:\Users\mem21\OneDrive\Documents\MATLAB\ls_solution\fault_location_sims\ECCE26_sims\estimations_50.mat';
file3 = 'C:\Users\mem21\OneDrive\Documents\MATLAB\ls_solution\fault_location_sims\ECCE26_sims\estimations_75.mat';
file4 = 'C:\Users\mem21\OneDrive\Documents\MATLAB\ls_solution\fault_location_sims\ECCE26_sims\estimations_100.mat';

data1 = load(file1);
data2 = load(file2);
data3 = load(file3);
data4 = load(file4);

%% ============================================================
% Colors
%% ============================================================
Color1 = [0.5 0 0.5];             % Purple
Color2 = [0.8500 0.3250 0.0980];  % Orange
Color3 = [0.153 0.51 0.051];      % Green
Color4 = [0 0.4470 0.7410];       % Blue

LineWidth = 1;

%% ============================================================
% Limits
%% ============================================================
r_est_lim = [-0.05 0.6];
l_est_lim = [-10 140];
r_err_lim = [-0.9 12.3];
l_err_lim = [-0.2 3.1];

t_lim = [0.4999 0.501];

%% ============================================================
% Figure size (IEEE single column)
%% ============================================================
fig_width  = 8.6;   % 86 mm
fig_height = 8.6;   % 86 mm

fig2 = figure(2);
clf

set(fig2,'Units','centimeters')
set(fig2,'Position',[5 5 fig_width fig_height])

tiledlayout(2,2,...
    'TileSpacing','compact',...
    'Padding','compact')

%% ============================================================
% Extract variables
%% ============================================================
extract = @(data) deal( ...
    data.r_est_sim,...
    data.l_est_sim,...
    data.r_err_sim,...
    data.l_err_sim,...
    data.time_full_sim);

[r_est1,l_est1,r_err1,l_err1,time1] = extract(data1);
[r_est2,l_est2,r_err2,l_err2,time2] = extract(data2);
[r_est3,l_est3,r_err3,l_err3,time3] = extract(data3);
[r_est4,l_est4,r_err4,l_err4,time4] = extract(data4);

%% ============================================================
% True values
%% ============================================================
Rtrue = [0.1433 0.2766 0.4100 0.5433];
Ltrue = [3.1746*10 6.3492*10 9.5238*10 12.6980*10];


%% ============================================================
% (a) R estimation
%% ============================================================
nexttile
hold on
grid on
box off

plot(time1,r_est1,'Color',Color1,'LineWidth',LineWidth)
yline(Rtrue(1),'--','Color',Color1,'LineWidth',LineWidth)

plot(time2,r_est2,'Color',Color2,'LineWidth',LineWidth)
yline(Rtrue(2),'--','Color',Color2,'LineWidth',LineWidth)

plot(time3,r_est3,'Color',Color3,'LineWidth',LineWidth)
yline(Rtrue(3),'--','Color',Color3,'LineWidth',LineWidth)

plot(time4,r_est4,'Color',Color4,'LineWidth',LineWidth)
yline(Rtrue(4),'--','Color',Color4,'LineWidth',LineWidth)

xline(0.5,'r')

xlim(t_lim)
ylim(r_est_lim)

xlabel('$t~[\mathrm{s}]$','Interpreter','latex')
ylabel('$R_{est}~[\Omega]$','Interpreter','latex')
title('(a)','Interpreter','latex')


%% ============================================================
% (b) R error
%% ============================================================
nexttile
hold on
grid on
box off

plot(time1,r_err1,'Color',Color1,'LineWidth',LineWidth)
plot(time2,r_err2,'Color',Color2,'LineWidth',LineWidth)
plot(time3,r_err3,'Color',Color3,'LineWidth',LineWidth)
plot(time4,r_err4,'Color',Color4,'LineWidth',LineWidth)

xline(0.5,'r')

xlim(t_lim)
ylim(r_err_lim)

xlabel('$t~[\mathrm{s}]$','Interpreter','latex')
ylabel('$R_{err}~[\%]$','Interpreter','latex')
title('(b)','Interpreter','latex')


%% ============================================================
% (c) L estimation
%% ============================================================
nexttile
hold on
grid on
box off

plot(time1,l_est1*1e6,'Color',Color1,'LineWidth',LineWidth)
yline(Ltrue(1),'--','Color',Color1,'LineWidth',LineWidth)

plot(time2,l_est2*1e6,'Color',Color2,'LineWidth',LineWidth)
yline(Ltrue(2),'--','Color',Color2,'LineWidth',LineWidth)

plot(time3,l_est3*1e6,'Color',Color3,'LineWidth',LineWidth)
yline(Ltrue(3),'--','Color',Color3,'LineWidth',LineWidth)

plot(time4,l_est4*1e6,'Color',Color4,'LineWidth',LineWidth)
yline(Ltrue(4),'--','Color',Color4,'LineWidth',LineWidth)

xline(0.5,'r')

xlim(t_lim)
ylim(l_est_lim)

xlabel('$t~[\mathrm{s}]$','Interpreter','latex')
ylabel('$L_{est}~[\mu H]$','Interpreter','latex')
title('(c)','Interpreter','latex')


%% ============================================================
% (d) L error
%% ============================================================
nexttile
hold on
grid on
box off

plot(time1,l_err1,'Color',Color1,'LineWidth',LineWidth)
plot(time2,l_err2,'Color',Color2,'LineWidth',LineWidth)
plot(time3,l_err3,'Color',Color3,'LineWidth',LineWidth)
plot(time4,l_err4,'Color',Color4,'LineWidth',LineWidth)

xline(0.5,'r')

xlim(t_lim)
ylim(l_err_lim)

xlabel('$t~[\mathrm{s}]$','Interpreter','latex')
ylabel('$L_{err}~[\%]$','Interpreter','latex')
title('(d)','Interpreter','latex')


%% ============================================================
% Formatting
%% ============================================================
axs = findall(gcf,'Type','axes');

for k = 1:length(axs)
    axs(k).FontSize = 8;
    axs(k).Box = 'off';
end

set(gcf,'Renderer','painters')

set(gcf,'PaperUnits','centimeters')
set(gcf,'PaperPosition',[0 0 fig_width fig_height])
set(gcf,'PaperSize',[fig_width fig_height])


%% ============================================================
% Export
%% ============================================================
print(gcf,'results_signals_comparison','-dpdf','-painters')