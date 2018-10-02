#pragma once

#include "ofxTktrNDI.h"
#include <string>
#include <Processing.NDI.Lib.h>

namespace ofxTktrNDI {
class Router
{
public:
	using Instance = NDIlib_routing_instance_t;
	~Router();

	bool setup(const std::string &name, const std::string &group="");
	bool setRoute(const ofxTktrNDI::Source &source) const;
	bool clear() const;
private:
	Instance instance_=nullptr;
};
}

using ofxTktrNDIRouter = ofxTktrNDI::Router;
