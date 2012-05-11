# Accelerometer Watch

Inspired by the awesome SolderTime watch by [Spikenzie Labs](http://spikenzielabs.com/SpikenzieLabs/SolderTime.html)

The Accelerometer Watch uses an accelerometer to detect when the wearer lifts their arm. 
The display is automatically turned on when the arm is lifted and the turned off to conserve power when the arm is lowered.
Most parts have been changed to surface mount to reduce the overall size and cost of the watch.

The project consists of a schematic, PCB layout, various firmware and a 3D watchface design suitable for 3D printing.

# Technology

- At the core is an [Atmel ATMEGA48](http://www.atmel.com/Images/doc2545.pdf) in a QFN-32 package 
- The system is clocked with a 32.768kHz crystal
- The electronics are powered by a CR2025 3V coin battery
- Included is the standard Atmel ICSP 6-pin programming header
- A right angle push button is included for setting the time
- The acceleromoter is a [Freescale MMA6331LT-ND](http://cache.freescale.com/files/sensors/doc/data_sheet/MMA6331L.pdf) in an LGA-14 package 
- The display is a [Lumex LDQ-M286RI](http://www.lumex.com/specs/LDQ-M286RI.pdf)

# Documentation

The docs folder contains schematic and pcb layout in both DipTrace and PDF formats

# Models

# Firmware

# License

The project is released under the [CC-BY-SA License](http://creativecommons.org/licenses/by-sa/2.0/)
