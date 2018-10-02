#include "ofxTktrNDISendStream.h"

#pragma mark video

void ofxTktrNDISendVideo::sendFrame(const ofxTktrNDI::VideoFrame &frame) const
{
	if(is_async_) {
		NDIlib_send_send_video_async_v2(instance_, &frame);
	}
	else {
		NDIlib_send_send_video_v2(instance_, &frame);
	}
}

template<>
void ofxTktrNDISendAudio::sendFrame(const ofxTktrNDI::AudioFrame &frame) const
{
	NDIlib_send_send_audio_v2(instance_, &frame);
}

void ofxTktrNDISendMetadata::sendFrame(const ofxTktrNDI::MetadataFrame &frame) const
{
	NDIlib_send_send_metadata(instance_, &frame);
}

template<>
void ofxTktrNDISendMetadataRecv::freeFrame()
{
	NDIlib_send_free_metadata(instance_, &frame_.back());
}
template<>
bool ofxTktrNDISendMetadataRecv::captureFrame() {
	return NDIlib_send_capture(instance_, &frame_.back(), timeout_ms_) == NDIlib_frame_type_metadata;
}
