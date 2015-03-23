#pragma once

#include "stdafx.h"
#include "server.h"

namespace Patchouli {
  bool setup(boost::application::context& context, bool& is_service, const std::string service_name);
}
