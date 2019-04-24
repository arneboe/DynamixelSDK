#include "port_handler.h"

namespace dynamixel
{


/** Implements the time keeping features of the PortHandler on STM32 */
class TimingPortHandler : public PortHandler
{
 private:
  uint32_t packetStartTime; //time of the last call to setPacketTimeout() in ms
  uint32_t packetTimeout; //timeout in ms
  uint32_t txTimePerByteUs; //how long does it take to send one byte in us(!!)

 public:

  TimingPortHandler(uint32_t baudrate);
  virtual ~TimingPortHandler() {}
  void setPacketTimeout(uint16_t packet_length) override;
  void setPacketTimeout(double msec) override;
  bool isPacketTimeout() override;
};

}
