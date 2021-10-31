# SPI Transfer using 2 SPI Channels on a Single Board by DMA

This is prelude to PDM microphone or any PDM analog IC that can be interfaced with SPI.

So far, G474 and H743 are the only ones working while F407 and H747 are still debugging.

G474 and H743 can work both Receive and Transfer only channels (2 lines).
F407 is transferring and receiving but need to be Duplex (should have transfer/receive channels enabled, 3 lines), but the data received is wrong.
H747 totally no transfer.
