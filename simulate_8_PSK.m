% Author of the script
%AYDIN UZUN
%2015401210

% Clears all the variables from the workspace
clear;

% Sets the number of symbols in the alphabet
M=8;

% Creates the 8-PSK code symbols
code_symbols=exp(1j*2*pi*[0:(M-1)]/M);

% Defines the alphabet (which in this case is just the indices of the symbols)
alphabet = [1 2 3 4 5 6 7 8];

% Generates random indices and corresponding modulated symbols, then plots the symbols
index = randi(8,1,10000);
modulated = code_symbols(index);
figure(1); scatter(real(modulated), imag(modulated));
title('Constellation Points');

% Adds Gaussian noise to the symbols and plots the noisy symbols
noise_gaussian_real = normrnd(0,0.1,1,10000);
noise_gaussian_imag = normrnd(0,0.1,1,10000);
modulated_noise = modulated + noise_gaussian_real + 1j*noise_gaussian_imag;
figure(1);scatter(real(modulated_noise), imag(modulated_noise));
title('After Noise Addition');

% Adds another type of Gaussian noise (with a standard deviation of sqrt(1/12)) to the symbols and plots the result
noise_gaussian_real_e = normrnd(0,sqrt(1/12),1,10000);
noise_gaussian_imag_e = normrnd(0,sqrt(1/12),1,10000);
modulated_noise_e = modulated + noise_gaussian_real_e ...
    + 1j*noise_gaussian_imag_e;
figure(1);scatter(real(modulated_noise_e), imag(modulated_noise_e));
title('Eb/N0=2 Noise Addition');

% Uses a nearest-neighbor rule to demodulate the symbols and highlights the errors
for k=1:10000
    dist = zeros(1,8);
    for r=1:M
        ref = code_symbols(r);
        dist(r) = norm(modulated_noise_e(k) - ref);
    end
    [minv, ind] = min(dist);
    received(k) = ind;
end
difference = received - index;

% Plots the demodulated symbols, marking the errors in red
received_sym = code_symbols(received);
scatter(real(modulated_noise_e), imag(modulated_noise_e), 'green'); hold on;
for k=1:10000
    if difference(k)~=0
        scatter(real(modulated_noise_e(k)), imag(modulated_noise_e(k)), 'red');
    end
end

% Repeats the above process, but this time all the transmitted symbols are the same
same_sig = ones(1,10000);
mod_same_sig = code_symbols(same_sig);
mod_same_sig_noise = mod_same_sig + noise_gaussian_real_e ...
    + 1j*noise_gaussian_imag_e;
for k=1:10000
    dist = zeros(1,8);
    for r=1:M
        ref = code_symbols(r);
        dist(r) = norm(mod_same_sig_noise(k) - ref);
    end
    [minv, ind] = min(dist);
    received_same(k) = ind;
end
difference_same = received_same - 1;
received_sym = code_symbols(received);
scatter(real(mod_same_sig_noise), imag(mod_same_sig_noise), 'green'); hold on;
for k=1:10000
    if difference_same(k)~=0
        scatter(real(mod_same_sig_noise(k)), imag(mod_same_sig_noise(k)), 'red');
    end
end

% Simulates a digital communication system for various values of Eb/N0 and plots the resulting Bit Error Rate (BER) vs Eb/N0
clear;
ferlim = 100;
N=4002;
max_nframe =2000;
EbNo = [0.8:0.2:3]; % assume EbNo linear not in db
errs=zeros(length(EbNo), 1);
nframes=zeros(length(EbNo), 1);
ferrs=errs;
code_symbols=exp(1j*2*pi*[0:(8-1)]/8);
Nsy=N/3;
bits8 = [0 0 0; 0 0 1; 0 1 0; 0 1 1; 1 0 0; 1 0 1; 1 1 0; 1 1 1];

% Simulation of the communication system for various values of Eb/N0
for i=1:length(EbNo)
    EbNo_i=EbNo(i);
    sigma = 1/sqrt(EbNo_i);
    nframe = 0;
    while (nframe<max_nframe) && (ferrs(i)<ferlim)

        err_count=0;
        nframe = nframe + 1;
        info_bits=round(rand(1,N));
        info_part=reshape(info_bits, 3, Nsy);
        info_matrix=info_part';
        sym_vec=ones(Nsy, 1);
        for v=1:3
            sym_vec=sym_vec+info_matrix(:,v).*2^(3-v);
        end
        sym_seq=code_symbols(sym_vec);
        snr = 10*log10(3) + 10*log10(EbNo(i)); % calculate snr in db
        rec_sig = awgn(sym_seq,snr,'measured');

        for k=1:Nsy
            min_metric=10^6; dm=zeros(1,8);
            for r=1:8
                x_r=code_symbols(r);
                dm(r)=norm(rec_sig(k)-x_r);
            end
            [rowmin, sym_ind]=min(dm);
            detected_bits=bits8(sym_ind, :);
            err = length(find(info_part(:,k)~=detected_bits'));
            errs(i)=errs(i)+err;
            err_count=err_count+err;
        end
        if err_count~=0
            ferrs(i)=ferrs(i)+1;
        end
    end
    nframes(i)=nframe;
    sim_res=[errs nframes]
end

% Plots the Bit Error Rate (BER) vs Eb/N0
semilogy(10*log10(EbNo), errs./nframes/4002, '-x'); % Eb/N0 in dB
xlabel('Eb/No (in dB)');
ylabel('BER');
