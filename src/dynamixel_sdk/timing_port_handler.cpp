#include "timing_port_handler.h"

#define ADDITIONAL_TIMEOUT_MS 10
#include "stm32f7xx_hal.h"

namespace dynamixel 
{

TimingPortHandler::TimingPortHandler(uint32_t baudrate) :
    packetStartTime(0),
    packetTimeout(0),
    txTimePerByteUs(1000000 / baudrate * 10) //FIXME is this correct? (taken from arduino)
{
    //BUG this should be default but the interface is brocken...
    is_using_ = false;
}

void TimingPortHandler::setPacketTimeout(uint16_t packet_length)
{
    packetStartTime = HAL_GetTick();
    packetTimeout = (txTimePerByteUs * packet_length) / 1000 + ADDITIONAL_TIMEOUT_MS;
}

void TimingPortHandler::setPacketTimeout(double msec)
{
    packetStartTime = HAL_GetTick();
    packetTimeout = static_cast<uint32_t>(msec);
}

bool TimingPortHandler::isPacketTimeout()
{  
    const uint32_t elapsedTime = HAL_GetTick() - packetStartTime;
    
    if (elapsedTime > packetTimeout)
    {
        packetTimeout = 0;
        return true;
    }

    return false;
    
}

}
