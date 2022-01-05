waveforms:  
PD13 = Half and complete call back = 64Hz  
PB10 = SPI CK = 1.024MHz  
PA4  = DAC = 515Hz sine = 15.997kHz sampling Freq (60uS),   

** SPI   
APB1 Periph Clock = 16.380952 MHz  
Prescaller = 16  
SPI Freq = 1.0238MHz  
PDM Decimation Factor = 64  
PDM to PCM Data output sampling freq = 1.0238MHz / 64 = 15.997kHz      

** Timer2/6 will trigger DAC   
APB1 Timer Clock = 32.761905 MHz  
Prescaller = (16 - 1) = 16  
Counter Preriod = (128 - 1) = 128  
Timer Freq = 15.997kHz  

** PDM data
1 cycle PDM datastream = 2000 data bits  
2000 data bit / 64 decimation is not whole number   
Multiply 2000 data bit by 4 cycles to get whole number after decimating 64  
8000 bits / 64 decimator = 125 samples at 15.997kHz   
With 8000 bits of data, it is equivalent to 1000 bytes. 

** PCM data  
With 8000 bits of PDM data (1000 bytes) will yield 125 int of PCM data  

** DAC data  
After the PCM data is retrieved, is it converted to 12bit DAC with 1.5V or 2048 as the center  

** DMA setup/strategy  
There will be an interrupt on Half and after completed DMA transfer of the SPI 2000 bytes   
PDM data variable to use 2x of 1000 bytes variable where first half [0 - 999] will be used for half of the DMA and [1000 - 1999] will be used for the other half or when DMA is completed  
PCM data variable to use 2x of 125 int16 variable where first half [0 - 124] will be used for half of the DMA and [125 - 250] will be used for the other half or when DMA is completed  
DAC data variable to use 2x of 125 uint16 variable where first half [0 - 124] will be used for half of the DMA and [125 - 250] will be used for the other half or when DMA is completed  

** DMA Interrupt
SPI Half and Complete DMA transfer both will process the 125 PDM data to be sent to DAC  
