/*
 Copyright (C) 2019 Luis Fernando Garc’a PŽrez [http://luiscript.com]

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */


#ifndef DKOscServer_hpp
#define DKOscServer_hpp

#include "ofxOsc.h"
#include "DKModule.hpp"
#include "unordered_map"

struct DKoscParam
{
	int* intValue;
	float* floatValue;
	bool changed;
};

class DKOscServer : public DKModule
{
private:
	int port;
	string host;
	string newAddress;
	float min;
	float max;
	int precision;
	ofxOscSender sender;
	unordered_map<string, DKoscParam> oscMessages;
	ofxDatGuiFolder* params;
    ofxDatGuiFolder* addressList;
    
public:
	void setup();
	void update();
	void draw();
	void addModuleParameters();
	void onOscPortChange(ofxDatGuiTextInputEvent);
	void onOscHostChange(ofxDatGuiTextInputEvent);
	void onAddressNameChange(ofxDatGuiTextInputEvent);
	void onAddressMinChange(ofxDatGuiTextInputEvent);
	void onAddresMaxChange(ofxDatGuiTextInputEvent);
	void onAddressPrecisionChange(ofxDatGuiTextInputEvent);
	void onAddressButtonPressed(ofxDatGuiButtonEvent);
	void addOscSlider(string, float*);
};

#endif /* DKOscServer_hpp */
