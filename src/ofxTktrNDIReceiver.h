#pragma once

#include "ofConstants.h"
#include "ofxTktrNDI.h"
#include <string>
#include <vector>

namespace ofxTktrNDI {
namespace Recv {
		
class Receiver
{
public:
	using Instance = NDIlib_recv_instance_t;
	~Receiver();

	struct Settings {
		Settings(){}
#ifdef TARGET_WIN32
		NDIlib_recv_color_format_e color_format=NDIlib_recv_color_format_BGRX_BGRA;
#else
		NDIlib_recv_color_format_e color_format=NDIlib_recv_color_format_RGBX_RGBA;
#endif
		NDIlib_recv_bandwidth_e bandwidth=NDIlib_recv_bandwidth_highest;
		bool deinterlace=false;
#ifndef ofxTktrNDI_USE_V2
		std::string name="";
#endif
	};
	bool setup(std::size_t index=0, const Settings &settings=Settings());
	bool setup(const Source &source, const Settings &settings=Settings());
	void addConnectionMetadata(const std::string &metadata, int64_t timecode=NDIlib_send_timecode_synthesize) const;
	void clearConnectionMetadata() const;

	bool isSetup() const { return instance_ != nullptr; }
	bool isConnected() const;
	
	bool setTally(bool on_program, bool on_preview) const;
	
	void getQueue(int *video, int *audio, int *metadata) const;
	std::string getWebControl() const;
	
	void getNumReceivedFrame(int64_t *video, int64_t *audio, int64_t *metadata) const;
	void getNumDroppedFrame(int64_t *video, int64_t *audio, int64_t *metadata) const;
	
	NDIlib_recv_instance_t getInstance() const { return instance_; }
private:
	NDIlib_recv_instance_t instance_=nullptr;
};

}}

using ofxTktrNDIReceiver = ofxTktrNDI::Recv::Receiver;
