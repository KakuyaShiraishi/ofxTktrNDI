#include "ofxTktrNDIReceiver.h"
#include "ofUtils.h"

using namespace std;

bool ofxTktrNDIReceiver::setup(size_t index, const Settings &settings)
{
	auto &&sources = ofxTktrNDI::listSources();
	if(index < sources.size()) {
		return setup(sources[index], settings);
	}
	ofLogWarning("no NDI Source found");
	return false;
}
bool ofxTktrNDIReceiver::setup(const ofxTktrNDI::Source &source, const Settings &settings)
{
#ifdef ofxTktrNDI_USE_V2
	NDIlib_recv_create_t creator = { source, settings.color_format, settings.bandwidth, settings.deinterlace };
	instance_ = NDIlib_recv_create_v2(&creator);
#else
	NDIlib_recv_create_v3_t creator = { source, settings.color_format, settings.bandwidth, settings.deinterlace, nullptr };
	creator.p_ndi_name = settings.name==""?nullptr:settings.name.c_str();
	instance_ = NDIlib_recv_create_v3(&creator);
#endif
	if (!instance_) {
		ofLogError("NDI Receiver failed to initialize");
		return false;
	}
	return true;
}

void ofxTktrNDIReceiver::addConnectionMetadata(const string &metadata, int64_t timecode) const
{
	const NDIlib_metadata_frame_t data = {
		static_cast<int>(metadata.length()+1),
		timecode,
		const_cast<char*>(metadata.c_str())
	};
	NDIlib_recv_add_connection_metadata(instance_, &data);
}
void ofxTktrNDIReceiver::clearConnectionMetadata() const
{
	NDIlib_recv_clear_connection_metadata(instance_);
}

bool ofxTktrNDIReceiver::isConnected() const
{
	return isSetup() && NDIlib_recv_get_no_connections(instance_);
}

bool ofxTktrNDIReceiver::setTally(bool on_program, bool on_preview) const
{
	const NDIlib_tally_t tally = {
		on_program, on_preview
	};
	
	return NDIlib_recv_set_tally(instance_, &tally);
}

void ofxTktrNDIReceiver::getQueue(int *video, int *audio, int *metadata) const
{
	NDIlib_recv_queue_t frames;
	NDIlib_recv_get_queue(instance_, &frames);
	if(video) { *video = frames.video_frames; }
	if(audio) { *audio = frames.audio_frames; }
	if(metadata) { *metadata = frames.metadata_frames; }
}

std::string ofxTktrNDIReceiver::getWebControl() const
{
	const char *ptr = NDIlib_recv_get_web_control(instance_);
	std::string ret = ptr;
	NDIlib_recv_free_string(instance_, ptr);
	return ret;
}

void ofxTktrNDIReceiver::getNumReceivedFrame(int64_t *video, int64_t *audio, int64_t *metadata) const
{
	NDIlib_recv_performance_t frames;
	NDIlib_recv_get_performance(instance_, &frames, nullptr);
	if(video) { *video = frames.video_frames; }
	if(audio) { *audio = frames.audio_frames; }
	if(metadata) { *metadata = frames.metadata_frames; }
}
void ofxTktrNDIReceiver::getNumDroppedFrame(int64_t *video, int64_t *audio, int64_t *metadata) const
{
	NDIlib_recv_performance_t frames;
	NDIlib_recv_get_performance(instance_, nullptr, &frames);
	if(video) { *video = frames.video_frames; }
	if(audio) { *audio = frames.audio_frames; }
	if(metadata) { *metadata = frames.metadata_frames; }
}

ofxTktrNDIReceiver::~Receiver()
{
	NDIlib_recv_destroy(instance_);
	NDIlib_destroy();
}
