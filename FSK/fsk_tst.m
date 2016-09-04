
% my own FSK modulator and testing it with Matlab demodulation
clc; clear all; close all;

M = 4;
I = randi([-M/2,M/2],1000,1);
% I = (I-1/2)*2;
I = I(find(I~=0));
% I = [-1 -1];
% I = -1*ones(1,5);

df = 1e3;
SR = .5e3;
sps = 10;

idx = 1;
modS(1) = 1;
for i=1:length(I)
    Fi = df*sign(I(i)).*(1/2+abs(I(i))-1);
    Dphi = 2*pi*Fi/(sps*SR);
    for c=1:sps
        modS(idx+1,1) = modS(idx,1)*exp(1j*Dphi);
        idx = idx+1;
    end
    % removing DC
    modS(sps*(i-1)+1:sps*i) = modS(sps*(i-1)+1:sps*i) - ...
        mean(modS(sps*(i-1)+1:sps*i));
%     figure
%     plot(linspace(0,i/SR,i*(sps)),real(modS))
%     hold on
%     plot(linspace(0,i/SR,i*(sps)),imag(modS), 'r')

end

% time domain signal
figure
plot(linspace(0,(length(I)-1)/SR,length(I)*(sps)+1),real(modS))
hold on
plot(linspace(0,(length(I)-1)/SR,length(I)*(sps)+1),imag(modS), 'r')

% t1 = 0:1/(sps*df):(length(I)-1)/df
figure
plot(linspace(-SR*sps/2,SR*sps/2,length(modS)),abs(fftshift(fft(modS))))

%% FSK demodulation (for testing)

FSKDemod = comm.FSKDemodulator('ModulationOrder', M, 'SymbolMapping', 'Binary' , ...
    'FrequencySeparation',df, 'SamplesPerSymbol', sps, 'SymbolRate', SR);

dmodb = step(FSKDemod, modS(2:end));

% comparison:
dmodb(find(dmodb==0)) = -2;
dmodb(find(dmodb==1)) = -1;
dmodb(find(dmodb==2)) = 1;
dmodb(find(dmodb==3)) = 2;

SER = sum(dmodb ~= I)/length(I)
