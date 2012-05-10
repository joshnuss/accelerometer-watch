# Accelerometer Watch

A derivative of the excellent SolderTime watch by [Spikenzie Labs](http://spikenzielabs.com/SpikenzieLabs/SolderTime.html)

The Accelerometer Watch uses an accelerometer to detect when the wearer lifts their arm. 
The display is automatically turned on when the arm is lifted and the turned off to conserve power when the arm is lowered.
Most parts have been changed to surface mount to reduce the overall size and cost of the watch.

The project consists of a schematic, PCB layout, various firmware and a 3D watchface design suitable for 3D printing.

# Technology

- At the core is an Atmel ATMEGA48 in a QFN-32 package [Datasheet](http://www.atmel.com/Images/doc2545.pdf)
- The system is clocked with a 32.768kHz crystal
- The electronics are powered by at CR2025 3V coin battery
- Included is the standard Atmel ICSP 6-pin programming header
- A right angle push button is included for setting the time
- The acceleromoter is an Freescale MMA6331LT-ND in an LGA-14 package [Datasheet](http://cache.freescale.com/files/sensors/doc/data_sheet/MMA6331L.pdf)

# Documentation

# Models

# Firmware

# License

The project is released under the [CC-BY-SA License](http://creativecommons.org/licenses/by-sa/2.0/)
