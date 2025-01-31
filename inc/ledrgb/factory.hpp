#pragma once

#include "ledrgb/interfaces/ledrgb.hpp"

#include <memory>

namespace ledrgb
{

class Factory
{
  public:
    template <typename T, typename C, typename P>
    static std::shared_ptr<LedrgbIf<P>> create(const C& config)
    {
        return std::shared_ptr<T>(new T(config));
    }
};

} // namespace ledrgb
