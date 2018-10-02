//
//  ofxTktrNDIPTZ.cpp
//  sender-macos
//
//  Created by Kakuya Shiraishi on 2018/03/23.
//
//

#include "ofxTktrNDIPTZ.h"

bool ofxTktrNDIPTZControl::setup(ofxTktrNDIReceiver &receiver)
{
	return setup(receiver.getInstance());
}
bool ofxTktrNDIPTZControl::setup(ofxTktrNDIReceiver::Instance instance)
{
	instance_ = instance;
	return NDIlib_recv_ptz_is_supported(instance_);
}

bool ofxTktrNDIPTZControl::zoom(float zoom) const
{
	return NDIlib_recv_ptz_zoom(instance_, zoom);
}
bool ofxTktrNDIPTZControl::zoomBySpeed(float speed) const
{
	return NDIlib_recv_ptz_zoom_speed(instance_, speed);
}

bool ofxTktrNDIPTZControl::panTilt(float pan, float tilt) const
{
	return NDIlib_recv_ptz_pan_tilt(instance_, pan, tilt);
}
bool ofxTktrNDIPTZControl::panTiltBySpeed(float pan_speed, float tilt_speed) const
{
	return NDIlib_recv_ptz_pan_tilt_speed(instance_, pan_speed, tilt_speed);
}

bool ofxTktrNDIPTZControl::storePreset(int index) const
{
	return NDIlib_recv_ptz_store_preset(instance_, index);
}
bool ofxTktrNDIPTZControl::recallPreset(int index, float speed) const
{
	return NDIlib_recv_ptz_recall_preset(instance_, index, speed);
}

bool ofxTktrNDIPTZControl::autoFocus() const
{
	return NDIlib_recv_ptz_auto_focus(instance_);
}
bool ofxTktrNDIPTZControl::focus(float focus) const
{
	return NDIlib_recv_ptz_focus(instance_, focus);
}
bool ofxTktrNDIPTZControl::focusBySpeed(float speed) const
{
	return NDIlib_recv_ptz_focus_speed(instance_, speed);
}

bool ofxTktrNDIPTZControl::whiteBalanceMode(WhiteBalanceMode mode) const
{
	switch(mode) {
		case AUTO: return NDIlib_recv_ptz_white_balance_auto(instance_);
		case INDOOR: return NDIlib_recv_ptz_white_balance_indoor(instance_);
		case OUTDOOR: return NDIlib_recv_ptz_white_balance_outdoor(instance_);
		case ONESHOT: return NDIlib_recv_ptz_white_balance_oneshot(instance_);
	}
	return false;
}
bool ofxTktrNDIPTZControl::whiteBalance(float red, float blue) const
{
	return NDIlib_recv_ptz_white_balance_manual(instance_, red, blue);
}

bool ofxTktrNDIPTZControl::exposureAuto() const
{
	return NDIlib_recv_ptz_exposure_auto(instance_);
}
bool ofxTktrNDIPTZControl::exposure(float exposure) const
{
	return NDIlib_recv_ptz_exposure_manual(instance_, exposure);
}

