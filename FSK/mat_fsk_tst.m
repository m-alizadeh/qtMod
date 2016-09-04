
% FSK modulation using Matlab functions 
clc; clear all; close all;

M = 4;
BitIn = 0;
FreqSep = 1e3;
sps = 10;
SR =  0.5e3;

FSKH = comm.FSKModulator('ModulationOrder', M, 'BitInput',BitIn, 'FrequencySeparation', FreqSep ...
    , 'SamplesPerSymbol', sps, 'SymbolRate', SR, 'ContinuousPhase', 0,...
    'SymbolMapping', 'Binary');

I = randi([0,M-1],1000,1);
% I = 3*ones(105,1);
modS1 = step(FSKH,I);

% plot(linspace(0,(length(I)-1)/SR,length(I)*(sps)),real(modS1))
% hold on
% plot(linspace(0,(length(I)-1)/SR,length(I)*(sps)),imag(modS1), 'r')
 
figure
plot(linspace(-SR*sps/2,SR*sps/2,length(modS1)),abs(fftshift(fft(modS1))))

FSKDemod = comm.FSKDemodulator('ModulationOrder', M, 'SymbolMapping', 'Binary' , ...
    'FrequencySeparation',FreqSep/2, 'SamplesPerSymbol', sps, 'SymbolRate', SR);

dmodb = step(FSKDemod, modS1)
