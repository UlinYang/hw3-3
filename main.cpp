#include "mbed.h"

// main() runs in its own thread in the OS
Thread thread_master;
Thread thread_slave;
#define MAXIMUM_BUFFER_SIZE 2
static BufferedSerial device1(D10, D9); // tx, rx  D10:tx  D9:rx
static BufferedSerial device2(D1, D0);  // tx, rx   D1:tx   D0:rx
//static BufferedSerial serial_port(USBTX, USBRX);

int slave(){
while (1) {
    char buf[MAXIMUM_BUFFER_SIZE];
    char msg[MAXIMUM_BUFFER_SIZE];
    int mode;
    int value;
    if (device2.size()) { // with at least 1 char
      device2.read(buf, 1);
      mode = buf[0];
      if (device2.size()) { // with at least 1 char
        device2.read(buf, 1);
        value = buf[0];
        printf("Slave Read: mode=%d, value=%d\n", mode, value);
        if (device2.writable()) {
          if (mode == 1) { // mode!=0
            value = value + 1;
            msg[0] = mode;
            msg[1] = value;
            printf("Slave Write: mode=%d, value=%d\n", mode, value);
            device2.write(msg, 2);
          } else if (mode == 2) {
            value = value + 2;
            msg[0] = mode;
            msg[1] = value;
            printf("Slave Write: mode=%d, value=%d\n", mode, value);
            device2.write(msg, 2);
          } else {
            msg[0] = mode;
            msg[1] = value;
            printf("Slave Write: mode=%d, value=%d\n", mode, value);
            device2.write(msg, 2);
          }
          ThisThread::sleep_for(100ms); //wait after write
        }
      }
    }
  }
}
void master() {
    printf("test1\n");
    char buf1[MAXIMUM_BUFFER_SIZE];
    buf1[0] = 1;
    buf1[1]=8;
    device1.write(buf1, 2);
    char res[2];
    ThisThread::sleep_for(1s);
    device1.read(res, 2);
    ThisThread::sleep_for(1s);
    int mode = res[0];
    int value = res[1];
    printf("Master read from slave, mode=%d, value=%d\n", mode, value);
    printf("test2\n");
    buf1[0] = 2;
    buf1[1]=10;
    device1.write(buf1, 2);
    ThisThread::sleep_for(1s);
    device1.read(res, 2);
    ThisThread::sleep_for(1s);
    mode = res[0];
    value = res[1];
    printf("Master read from slave, mode=%d, value=%d\n", mode, value);

}
int main()
{
      // Set desired properties (9600-8-N-1).
  device1.set_baud(9600);
  device1.set_format(
      /* bits */ 8,
      /* parity */ BufferedSerial::None,
      /* stop bit */ 2);

  // Set desired properties (9600-8-N-1).
  device2.set_baud(9600);
  device2.set_format(
      /* bits */ 8,
      /* parity */ BufferedSerial::None,
      /* stop bit */ 2);
  thread_master.start(master);
  thread_slave.start(slave);
}