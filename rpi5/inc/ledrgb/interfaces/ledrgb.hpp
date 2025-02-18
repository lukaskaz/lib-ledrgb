#pragma once

#include <cstdint>
#include <vector>

namespace ledrgb
{

enum class colortype
{
    red = 0,
    green,
    blue,
    orange,
    yellow,
    lightblue,
    purple,
    pink,
    white,
    black
};

using grouptype = std::vector<std::pair<uint8_t, colortype>>;

template <typename P>
class LedrgbIf
{
  public:
    virtual ~LedrgbIf() = default;
    virtual bool light(uint8_t, colortype) = 0;
    virtual bool light(const grouptype&) = 0;
    virtual bool light(uint8_t, colortype, const P&) = 0;
    virtual bool light(const grouptype&, const P&) = 0;
};

} // namespace ledrgb
