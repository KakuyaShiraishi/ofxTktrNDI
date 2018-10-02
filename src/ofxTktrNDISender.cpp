#include "ofxTktrNDISender.h"
#include "ofLog.h"

using namespace std;

bool ofxTktrNDISender::setup(const string &name, const string &group, bool clock_video, bool clock_audio)
{
	NDIlib_send_create_t create_settings = {
		name.c_str(),
		group.c_str(),
		clock_video,
		clock_audio };
	instance_ = NDIlib_send_create(&create_settings);
	if(!instance_) {
		ofLogError("NDI Sender failed to initialize");
		return false;
	}
	return true;
}

bool ofxTktrNDISender::isConnected(int64_t timeout_ms) const
{
	return isSetup() && NDIlib_send_get_no_connections(instance_, timeout_ms);
}

void ofxTktrNDISender::addConnectionMetadata(const string &metadata, int64_t timecode) const
{
	const NDIlib_metadata_frame_t data = {
		static_cast<int>(metadata.length()+1),
		timecode,
		const_cast<char*>(metadata.c_str())
	};
	NDIlib_send_add_connection_metadata(instance_, &data);
}
void ofxTktrNDISender::clearConnectionMetadata() const
{
	NDIlib_send_clear_connection_metadata(instance_);
}

void ofxTktrNDISender::setFailover(const ofxTktrNDI::Source &source) const
{
	NDIlib_source_t src = source;
	NDIlib_send_set_failover(instance_, &src);
}
bool ofxTktrNDISender::getTally(bool *on_program, bool *on_preview, int64_t timeout_ms) const
{
	NDIlib_tally_t tally;
	if(NDIlib_send_get_tally(instance_, &tally, timeout_ms)) {
		if(on_program) *on_program = tally.on_program;
		if(on_preview) *on_preview = tally.on_preview;
		return true;
	}
	return false;
}
ofxTktrNDISender::~Sender()
{
	NDIlib_send_destroy(instance_);
	NDIlib_destroy();
}
