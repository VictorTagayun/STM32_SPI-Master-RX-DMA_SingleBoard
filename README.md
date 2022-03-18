# SPI Master Receive DMA using 2 SPI Channels on a Single Board

SPI Master Receive DMA using 2 SPI Channels on a Single Board by DMA. 1 SPI Master Receive and 1 SPI Slave transmit will be used.

## Purpose of Project

2 SPI channels will communicate with each other on a single STM32 MCU. One is master and the other is slave. Both SPI will be connected/wired together and will operate via DMA. As the project progresses, the slave SPI will be simulated as a PDM microphone and will have predefined PDM data.

This is prelude to PDM microphone or any PDM analog IC that can be interfaced with SPI. https://github.com/VictorTagayun/STM32_PDM-to-PCM-Processing

## Steps / Procedure

## Results

So far, G474 and H743 are the only ones working while F407 and H747 are still debugging.

G474 and H743 can work both Receive and Transfer only channels (2 lines).
F407 is transferring and receiving but needs to be Duplex (should have transfer/receive channels enabled, 3 lines), but the data received is wrong.
H747 totally no transfer.
