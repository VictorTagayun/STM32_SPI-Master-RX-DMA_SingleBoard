waveforms:  
PD13 = Half and complete call back = 64Hz  
PB10 = SPI CK = 1.024MHz  
PA4  = DAC = 515Hz sine = 15.997kHz sampling Freq (60uS),   

** SPI   
APB1 Periph Clock = 16.380952 MHz  
Prescaller = 16  
SPI Freq = 1.0238MHz  
PDM Decimation Factor = 64  
PDM to PCM Data output sampling freq = 15.997kHz      

** Timer2/6  
APB1 Timer Clock = 32.761905 MHz  
Prescaller = (16 - 1) = 16  
Counter Preriod = (128 - 1) = 128  
Timer Freq = 15.997kHz  

** PDM data  
1 cycle PDM datastream = 2000 data bits  
2000 data bit / 64 decimation is not whole number   
Multiply 2000 data bit by 4 cycles to get whole number after decimating 64  
8000 bits / 64 decimator = 125 samples at 15.997kHz   
With 8000 bits of data, it is equivalent to 1000 bytes  
