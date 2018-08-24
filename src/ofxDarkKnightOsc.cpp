//
//  ofxDarkKnightMidi.cpp
//  luiscript
//
//  Created by luiscript on 12/01/18.
//
//

#include "ofxDarkKnightOsc.hpp"


void ofxDarkNightOsc::setup()
{
    
}

void ofxDarkNightOsc::update()
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

void ofxDarkNightOsc::draw()
{
    
}


void ofxDarkNightOsc::addModuleParameters()
{
    ofxDatGuiTextInput * component = gui->addTextInput("Port");
    component->onTextInputEvent(this, &ofxDarkNightOsc::onOscPortChange);
}

void ofxDarkNightOsc::onOscPortChange(ofxDatGuiTextInputEvent e)
{
    port = ofToInt(e.text);
    oscIn.setup(port);
}

void ofxDarkNightOsc::addOscSlider(string address, float * value)
{
    oscMappings.insert({address, value});
    gui->setTheme(this->getGuiTheme());
    gui->setWidth(ofGetWidth()/5);
    ofxDatGuiSlider * component = gui->addSlider(address, 0.0, 1.0);
    component->setPrecision(4);
    component->bind(*value);
    component->toggleMidiMode();
}
