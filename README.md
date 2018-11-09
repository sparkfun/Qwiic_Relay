SparkFun Qwiic Relay
========================================

![SparkFun Qwiic Relay](https://cdn.sparkfun.com/assets/parts/1/2/8/6/6/14668-Qwiic_Relay-01.jpg)

[*SparkX Qwiic Relay (SPX-14668)*](https://www.sparkfun.com/products/14668)
Have you ever wanted to control something powerful? Have you ever needed to turn on/off a high voltage device from your Arduino? Now you can with the Qwiic Relay! This device allows you to control large power loads with simple I<sup>2</sup>C commands. The Qwiic Relay can handle 10 Amps at 120 Volts AC, perfect for large inductive loads like DC motors or blenders.

The Qwiic Relay comes with a default I<sup>2</sup>C address but can be changed with a simple command allowing you to control over 100 Qwiic Relays on a single bus!<sup>[1](#powerWarning)</sup>

The Qwiic Relay comes fully assembled and uses the simple [Qwiic](https://www.sparkfun.com/qwiic) interface. No soldering, no voltage translation, no figuring out which pin is SDA or SCL, just plug and go!

<div class="alert alert-warning"><b>Note:</b> Controlling high voltage (110/220VAC) requires certain precautions. A beginner can do it but if you're unsure then please consider the pre-made <a href="https://www.sparkfun.com/products/14236">IoT Power Relay</a>. It's not I<sup>2</sup>C but the IoT Power Relay contains shielding to prevent accidental shock.</div>

<a name="powerWarning"></a>Footnote 1: Toggling lots of relays on a 3.3V bus can cause voltage spikes. An external power supply will be required.
Repository Contents
-------------------

* **/Documents** - Datasheets
* **/Firmware** - Latest firmware and examples. 
* **/Hardware** - Eagle design files (.brd, .sch)

License Information
-------------------

This product is _**open source**_! 

Please review the LICENSE.md file for license information. 

If you have any questions or concerns on licensing, please contact techsupport@sparkfun.com.

Please use, reuse, and modify these files as you see fit. Please maintain attribution to SparkFun Electronics and release under the same license.

Distributed as-is; no warranty is given.

- Your friends at SparkFun.