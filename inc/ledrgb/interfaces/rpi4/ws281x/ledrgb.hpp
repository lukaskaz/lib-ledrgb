#pragma once

#include "ledrgb/factory.hpp"

#include <chrono>
#include <tuple>

using namespace std::chrono_literals;

namespace ledrgb::rpi4::ws281x
{

using param_t = std::chrono::milliseconds;
using config_t = std::tuple<uint8_t, uint8_t>;

class Ledrgb : public LedrgbIf<param_t>
{
  public:
    ~Ledrgb();
    bool light(uint8_t, colortype) override;
    bool light(const grouptype&) override;
    bool light(uint8_t, colortype, const param_t&) override;
    bool light(const grouptype&, const param_t&) override;

  private:
    friend class ledrgb::Factory;
    Ledrgb(const config_t&);

    struct Handler;
    std::unique_ptr<Handler> handler;
};

} // namespace ledrgb::rpi4::ws281x
