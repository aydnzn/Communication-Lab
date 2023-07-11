%% EE 479 Project 1
% Aydın Uzun 11.11.2018
% 2015401210
%%
clear ;
close all ;

%% Parameters for filters
Sampling_rate = 8815; % Sampling rate of 8815 Hz
half_pass = 23; % calculated empirically
FilterOrder= 60; % The order of the butterworth filters, calculated empirically
%% Filters
% Reference for butterworth bandpass filters : https://www.mathworks.com/help/dsp/ref/fdesign.bandpass.html
% design filters that will be used later
filter_spec_obj_697 = fdesign.bandpass('N,F3dB1,F3dB2',FilterOrder,697-half_pass,697+half_pass,Sampling_rate);
filter_for_697 = design(filter_spec_obj_697,'butter');

filter_spec_obj_770 = fdesign.bandpass('N,F3dB1,F3dB2',FilterOrder,770-half_pass,770+half_pass,Sampling_rate);
filter_for_770= design(filter_spec_obj_770,'butter');

filter_spec_obj_852 = fdesign.bandpass('N,F3dB1,F3dB2',FilterOrder,852-half_pass,852+half_pass,Sampling_rate);
filter_for_852= design(filter_spec_obj_852,'butter');

filter_spec_obj_941 = fdesign.bandpass('N,F3dB1,F3dB2',FilterOrder,941-half_pass,941+half_pass,Sampling_rate);
filter_for_941= design(filter_spec_obj_941,'butter');

filter_spec_obj_1209 = fdesign.bandpass('N,F3dB1,F3dB2',FilterOrder,1209-half_pass,1209+half_pass,Sampling_rate);
filter_for_1209= design(filter_spec_obj_1209,'butter');

filter_spec_obj_1336 = fdesign.bandpass('N,F3dB1,F3dB2',FilterOrder,1336-half_pass,1336+half_pass,Sampling_rate);
filter_for_1336= design(filter_spec_obj_1336,'butter');

filter_spec_obj_1477 = fdesign.bandpass('N,F3dB1,F3dB2',FilterOrder,1477-half_pass,1477+half_pass,Sampling_rate);
filter_for_1477= design(filter_spec_obj_1477,'butter');

filter_spec_obj_1633 = fdesign.bandpass('N,F3dB1,F3dB2',FilterOrder,1633-half_pass,1633+half_pass,Sampling_rate);
filter_for_1633= design(filter_spec_obj_1633,'butter');
%% Given code
% Communication with Port
delete(instrfind);
s = serial('/dev/cu.wchusbserial1420');
s.InputBufferSize = 1000;
set(s,'BaudRate', 115200);
fopen(s);
%%%%%%%%%%%%%%%%%%%%% added
k = 0; % this variable will be used to get rid of repeated printing of numbers
% if k = 0 there's nothing to print
% if k = 1 there's a character to print
% if k>1 the program should not print any number or character because it's
% a repetition.
% there should be a blank space between repeated signals to print both of
% them.
%%%%%%%%%%%%%%%%%%%%% added
while 1
    
    data = fread(s);
    
    %% added
    % First one should remove DC component
    data = data - mean(data);
    
    % filter data using imlpemented butterworth bandpass filters
    signal_filtered_697 = filter(filter_for_697,data);
    signal_filtered_770 = filter(filter_for_770,data);
    signal_filtered_852 = filter(filter_for_852,data);
    signal_filtered_941 = filter(filter_for_941,data);
    signal_filtered_1209 = filter(filter_for_1209,data);
    signal_filtered_1336 = filter(filter_for_1336,data);
    signal_filtered_1477 = filter(filter_for_1477,data);
    signal_filtered_1633 = filter(filter_for_1633,data);
    
    % calculate energy of each filtered signal
    energy_697 = sum(signal_filtered_697.^2);
    energy_770 = sum(signal_filtered_770.^2);
    energy_852 = sum(signal_filtered_852.^2);
    energy_941 = sum(signal_filtered_941.^2);
    energy_1209 = sum(signal_filtered_1209.^2);
    energy_1336 = sum(signal_filtered_1336.^2);
    energy_1477 = sum(signal_filtered_1477.^2);
    energy_1633 = sum(signal_filtered_1633.^2);
    
    % find the maximum of column(1209,1336,1477,1633) and row(697,770,852,941)
    Column_max = max([energy_697 energy_770 energy_852 energy_941]);
    Row_max = max([energy_1209 energy_1336 energy_1477 energy_1633]);
    
    % ignore any noise
    if(Column_max <0.05 || Row_max<0.05)
        k= 0 ;
        continue
    else
        k = k+1;
    end
    
    % Detect DTMF signal.
    if k==1
        if(Column_max == energy_697 && Row_max == energy_1209)
            fprintf('1 ');   
        elseif(Column_max == energy_697 && Row_max == energy_1336)
            fprintf('2 ');
        elseif(Column_max == energy_697 && Row_max == energy_1477)
            fprintf('3 ');
        elseif(Column_max == energy_697 && Row_max == energy_1633)
            fprintf('A ')
            
        elseif(Column_max == energy_770 && Row_max == energy_1209)
            fprintf('4 ');         
        elseif(Column_max == energy_770 && Row_max == energy_1336)
            fprintf('5 ');
        elseif(Column_max == energy_770 && Row_max == energy_1477)
            fprintf('6 ');
        elseif(Column_max == energy_770 && Row_max == energy_1633)
            fprintf('B ')
            
        elseif(Column_max == energy_852 && Row_max == energy_1209)
            fprintf('7 ');
        elseif(Column_max == energy_852 && Row_max == energy_1336)
            fprintf('8 ');
        elseif(Column_max == energy_852 && Row_max == energy_1477)
            fprintf('9 ')
        elseif(Column_max == energy_852 && Row_max == energy_1633)
            fprintf('C ')
            
        elseif(Column_max == energy_941 && Row_max == energy_1209)
            fprintf('* ');
        elseif(Column_max == energy_941 && Row_max == energy_1336)
            fprintf('0 ');  
        elseif(Column_max == energy_941 && Row_max == energy_1477)
            fprintf('# ')    
        elseif(Column_max == energy_941 && Row_max == energy_1633)
            fprintf('D ')
            
            
        end
    end
end




fclose(s);
