#include "port_handler.h"

namespace dynamixel
{


class PortHandlerSTM32 : public PortHandler
{
 private:
  int     socket_fd_;
  int     baudrate_;
  char    port_name_[100];

  double  packet_start_time_;
  double  packet_timeout_;
  double  tx_time_per_byte;

#if defined(__OPENCM904__)
  UARTClass *p_dxl_serial;
#endif

  bool    setupPort(const int cflag_baud);

  double  getCurrentTime();
  double  getTimeSinceStart();

  int     checkBaudrateAvailable(int baudrate);

  void    setPowerOn();
  void    setPowerOff();
  void    setTxEnable();
  void    setTxDisable();

 public:

  PortHandlerSTM32(const char *port_name);
  virtual ~PortHandlerSTM32() { closePort(); }
  bool    openPort() override;
  void    closePort() override;
  void    clearPort() override;
  void    setPortName(const char *port_name) override;
  char   *getPortName() override;
  bool    setBaudRate(const int baudrate) override;
  int     getBaudRate() override;
  int     getBytesAvailable() override;
  int     readPort(uint8_t *packet, int length) override;
  int     writePort(uint8_t *packet, int length) override;
  void    setPacketTimeout(uint16_t packet_length) override;
  void    setPacketTimeout(double msec) override;
  bool    isPacketTimeout() override;
};

}
