/*
 Copyright (C) 2018 Luis Fernando García [http://luiscript.com]
 
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

#include "ofxDarkKnightOsc.hpp"


void ofxDarkKnightOsc::setup()
{
    
}

void ofxDarkKnightOsc::update()
{
    while (oscIn.hasWaitingMessages())
    {
        ofxOscMessage m;
        oscIn.getNextMessage(m);
        string address = m.getAddress();
        
        // add new mapping when module is in mapping mode
        if(this->getModuleMidiMapMode())
        {
            string mapping;
            for (int i = 0; i < m.getNumArgs(); i++)
            {
                unordered_map<string, float *>::iterator it;
                mapping = address + ofToString(i);
                it = oscMappings.find(mapping);
                if(it == oscMappings.end())
                {
                    float * val = new float;
                    *val = m.getArgAsFloat(i);
                    addOscSlider(mapping, val);
                }
            }
        }
        else
        {
            if(m.getNumArgs() >= 1)
            {
                for (int i = 0; i < m.getNumArgs(); i++)
                {
                    string mapping = address + ofToString(i);
                    unordered_map<string, float *>::iterator it;
                    it = oscMappings.find(mapping);
                    if(it != oscMappings.end())
                    {
                        *it->second = m.getArgAsFloat(i);
                    }
                }
                
            }
        }
    }
}

void ofxDarkKnightOsc::draw()
{
    
}


void ofxDarkKnightOsc::addModuleParameters()
{
    ofxDatGuiTextInput * component = gui->addTextInput("Port");
    component->onTextInputEvent(this, &ofxDarkKnightOsc::onOscPortChange);
}

void ofxDarkKnightOsc::onOscPortChange(ofxDatGuiTextInputEvent e)
{
    port = ofToInt(e.text);
    oscIn.setup(port);
}

void ofxDarkKnightOsc::addOscSlider(string address, float * value)
{
    oscMappings.insert({address, value});
    gui->setWidth(450);
    ofxDatGuiSlider * component = gui->addSlider(address, 0.0, 1.0);
    component->setPrecision(4);
    component->bind(*value);
    component->toggleMidiMode();
}
