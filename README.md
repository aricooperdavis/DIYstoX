# DIYstoX
This repository stores the code for my DIY paperless cave surveying tool based on the fantastic DistoX system. It is a work in progress, but the end goal is for this repo to contain the code, wiring diagrams, and photos required for you to make this yourself at home.

## Introduction
I'm reverse engineering a SNDWAY Laser Distance Meter so that I can add magnetometer, accelerometer, and Bluetooth modules in order to make a DIY [DistoX2 paperless cave surveying tool](https://paperless.bheeb.ch/).
This will never compete with the accuracy, robustness, or usability of a DistoX2, but it's not supposed to compete, it's just a bit of fun for me. It's also a lot cheaper than me buying a proper one.
This also isn't the first attempt at [reverse engineering a laser rangefinder](https://web.archive.org/web/20190819080621/https://hackaday.com/2018/05/22/hacking-a-cheap-laser-rangefinder/), but as these devices differ greatly I still think that it is worth documenting my progress with this one.

## Hardware
- Microcontroller: [Adafruit Feather nRF52840 Express](https://www.adafruit.com/product/4062)
- Laser distance measure: [D1 SW-T100 100m LDM from SNDWAY](https://web.archive.org/web/20191206165848/https://www.ebay.co.uk/itm/SNDWAY-100M-Handheld-Digital-Laser-Distance-Meter-Range-Volume-Finder-Measure-D1-/362539784013?nma=true&si=OsgdOoaFCRm%252Fm1A7QFd30TFP3c8%253D&orig_cvip=true&nordt=true&rt=nc&_trksid=p2047675.l2557)
- Triple-axis accelerometer+magnetometer: [Adafruit LSM303DLHC](https://www.adafruit.com/product/1120)

## Software
### User facing (interface)
Whilst I've nicknamed this device the DIYstoX, it will operate quite differently. Rather than control the LDM it will just listen for readings from the LDM, acting as a buffer and Bluetooth LE interface. However, it will also take an inclination and heading measurement whenever the LDM sends a new distance measurement.

### Details (code)
I'm not going to develop my own bluetooth protocol for this DIY device - instead I'm going to simply pretent to be another device to ensure compatability with existing apps. One might expect that we would use the DistoX protocol, but as that doesn't use Bluetooth LE we will instead use the [BRIC4 protocol](https://www.caveexploration.org/s/BRIC4-Bluetooth-Protocol-revF.pdf) (thanks for publishing this, Team BRIC!).

## Blog posts
For some deep dives into aspects of the development, check out [my blog](https://www.cooper-davis.net/blog):

## Contribute
Please contribute if you can!

## License
This project has a strong copy-left license. Please ensure that you abide by the terms of this when distributing this software or any derivatives.
