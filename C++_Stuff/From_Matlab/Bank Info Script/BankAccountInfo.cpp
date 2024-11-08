%% Bank Account History Interactive Graph
%{
    Get Bank account info -> see "BankInfoDownloadTutorial.pdf"
    Press "Run"
    See graph of bank balance over time, minimum, maximum, average, etc.
%}


%% Import Acount History CSV Data
warning('off', 'all');
data = readtable('AccountHistory.csv');
warning('on', 'all');


%% PLOT SETTINGS
c_max = 'b';
c_min = 'r';
c_gain = 'g';
c_loss = 'm';

min2ploty_buffer = 100; % distance between the minimum value of the plot to the bottom of the plot

%% Setup Plot
f1 = figure('Name','Acount History');

s1 = axes(); %subplot(2,2,1);
xlabel(s1, "Date");
ylabel(s1, "Balance");
ytickformat(s1, 'usd');
hold(s1, "on");

%% Gains & Losses
gains_map = isnan(data.Debit);
gain_data = data(gains_map,:);
loss_data = data(~gains_map,:);

%% Min Max
[minimum, i_min] = min(data.Balance);
[maximum, i_max] = max(data.Balance);

%% Plot
p = plot(s1, ...
            loss_data.PostDate, loss_data.Balance, ...  %'m.', 'MarkerSize',20, ...
            gain_data.PostDate, gain_data.Balance, ...  %'g.', 'MarkerSize',20, ...
            data.PostDate(i_min), minimum, ...          %'bpentagram', 'MarkerSize',10, 'LineWidth',1, ...
            data.PostDate(i_max), maximum, ...          %, 'rpentagram', 'MarkerSize',10, 'LineWidth',1 ...
            data.PostDate, data.Balance);               % "k", ...

p(1).LineStyle = "none"; p(1).Color = c_loss; p(1).Marker = '.'; p(1).MarkerSize = 22;
p(2).LineStyle = "none"; p(2).Color = c_gain; p(2).Marker = '.'; p(2).MarkerSize = 22;
p(3).LineStyle = "none"; p(3).Color = c_min; p(3).Marker = 'pentagram'; p(3).MarkerSize = 15; p(3).LineWidth = 1.5;
p(4).LineStyle = "none"; p(4).Color = c_max; p(4).Marker = 'pentagram'; p(4).MarkerSize = 15; p(4).LineWidth = 1.5;
p(5).Color = "k";

yline(s1, 0, 'y', 'LineWidth',2);
ylim(s1, [minimum - 100, maximum+(0.05*abs(maximum))]);


%% Tooltip
change_amt = zeros(size(data,1), 1);
for i = 1:size(data,1)
    if gains_map(i) == 1
        change_amt(i) = data.Credit(i);
    else
        change_amt(i) = - data.Debit(i);
    end
end

mapi(:,1) = logical(~ gains_map);
mapi(:,2) = logical(gains_map);
mapi(:,3) = logical(data.Balance == minimum);
mapi(:,4) = logical(data.Balance == maximum);
mapi(:,5) = ones(size(mapi,1),1);


% Add ToolTip
for i_line = 1:length(p)
    % Get other info
    description = dataTipTextRow("Description", data.Description(mapi(:, i_line)));
    change = dataTipTextRow("\Delta", change_amt(mapi(:, i_line)), 'usd');
    date = dataTipTextRow("Date", data.PostDate(mapi(:, i_line)), 'yyyy-MM-dd');
    balance = dataTipTextRow("Balance", data.Balance(mapi(:, i_line)), 'usd');

    p(i_line).DataTipTemplate.DataTipRows(1) = date;
    p(i_line).DataTipTemplate.DataTipRows(2) = balance;
    p(i_line).DataTipTemplate.DataTipRows(end+1) = description;
    p(i_line).DataTipTemplate.DataTipRows(end+1) = change;
end
% % put in all-data line in plot
% p(5).DataTipTemplate.DataTipRows(1) = date;
% p(5).DataTipTemplate.DataTipRows(2) = balance;
% p(5).DataTipTemplate.DataTipRows(end+1) = description;
% p(5).DataTipTemplate.DataTipRows(end+1) = change;

%% Title & Legend
% Generate Statistic Details
avg = mean(data.Balance(~isnan(data.Balance)));
details = sprintf("Average: $%.2f\n" + ...
                  "Minimum: $%.2f\n" + ...
                  "Maximum: $%.2f\n" + ...
                  "Current: $%.2f", ...
                  avg, minimum, maximum, data.Balance(1));
% Title
title(details);

legend(s1, ...
       'Losses', 'Gains', 'Minimum', 'Maximum', 'All', ...
       'Location','northwest');

%% The End
hold(s1, "off");

fprintf(sprintf("%s\n", details));

