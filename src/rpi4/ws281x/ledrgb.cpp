#include "ledrgb/interfaces/rpi4/ws281x/ledrgb.hpp"

#include "dma.h"
#include "gpio.h"
#include "ws2811.h"

#include <algorithm>
#include <functional>
#include <future>
#include <ranges>
#include <unordered_map>

namespace ledrgb::rpi4::ws281x
{

struct Ledrgb::Handler
{
  public:
    Handler(const config_t& config) :
        amount{std::get<0>(config)}, brightness{std::get<1>(config)}
    {
        ws2811_init(&setup);
    }

    ~Handler()
    {
        clear();
        ws2811_fini(&setup);
    }

    bool light(uint8_t num, colortype color)
    {
        return light({{num, color}});
    }

    bool light(const grouptype& group)
    {
        static const std::unordered_map<colortype, ws2811_led_t> colormap = {
            {colortype::red, 0x00200000},    {colortype::green, 0x00002000},
            {colortype::blue, 0x00000020},   {colortype::orange, 0x00201000},
            {colortype::yellow, 0x00202000}, {colortype::lightblue, 0x00002020},
            {colortype::purple, 0x00100010}, {colortype::pink, 0x00200010},
            {colortype::white, 0x00202020},  {colortype::black, 0x00000000},
        };

        std::ranges::for_each(group, [this](const auto& led) {
            if (colormap.contains(led.second))
            {
                setup.channel[0].leds[led.first] = colormap.at(led.second);
            }
        });
        ws2811_render(&setup);
        return true;
    }

    bool light(uint8_t num, colortype color, const param_t& delay)
    {
        return light({{num, color}}, delay);
    }

    bool light(const grouptype& group, const param_t& delay)
    {
        light(group);
        async = std::async(std::launch::async, [this, group, delay]() {
            usleep((uint32_t)delay.count() * 1000);
            cleargroup(group);
        });
        return true;
    }

    bool clear()
    {
        std::ranges::for_each(
            std::views::iota(0, (int32_t)amount),
            [this](uint8_t num) { light(num, colortype::black); });
        return true;
    }

    bool cleargroup(const grouptype& group)
    {
        grouptype grouptoclear;
        std::ranges::for_each(group, [&grouptoclear](const auto& led) {
            grouptoclear.emplace_back(led.first, colortype::black);
        });
        return light(grouptoclear);
    }

  private:
    uint8_t amount;
    uint8_t brightness;
    const int32_t gpiopin{18};
    const int32_t dmanum{10};
    const int32_t type{WS2811_STRIP_GRB};
    const uint32_t targetfreq{WS2811_TARGET_FREQ};
    ws2811_t setup = {
        .freq = targetfreq,
        .dmanum = dmanum,
        .channel = {{
            .gpionum = gpiopin,
            .invert = 0,
            .count = amount,
            .strip_type = type,
            .brightness = brightness,
        }},
    };
    std::future<void> async;
};

Ledrgb::Ledrgb(const config_t& config) :
    handler{std::make_unique<Handler>(config)}
{}
Ledrgb::~Ledrgb() = default;

bool Ledrgb::light(uint8_t lednum, colortype color)
{
    return handler->light(lednum, color);
}

bool Ledrgb::light(const grouptype& group)
{
    return handler->light(group);
}

bool Ledrgb::light(uint8_t lednum, colortype color, const param_t& delay)
{
    return handler->light(lednum, color, delay);
}

bool Ledrgb::light(const grouptype& group, const param_t& delay)
{
    return handler->light(group, delay);
}

} // namespace ledrgb::rpi4::ws281x
