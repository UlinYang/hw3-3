# hw3-3
Specification: static BufferedSerial device1(D10, D9); static BufferedSerial device2(D1, D0);

How to set up the lab: Connect D10 to D0, D9 to DD1

expected result:

test1 Slave Read: mode=1, value=8

Slave Write: mode=1, value=9

Master read from slave, mode=1, value=9

test2

Slave Read: mode=2, value=10

Slave Write: mode=2, value=12

Master read from slave, mode=2, value=12
