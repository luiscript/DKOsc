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

#include "DKOscServer.hpp"


void DKOscServer::setup()
{
	newAddress = "newAddress";
	min = 0.0;
	max = 1.0;
	precision = 2;
}

void DKOscServer::update()
{
	if (oscMessages.size() > 0)
	{
		ofxOscBundle bundle;
		for (auto mapping : oscMessages)
		{
			ofxOscMessage message;
			message.setAddress(mapping.first);
			if (mapping.second.floatValue != nullptr)
			{
				message.addFloatArg(*mapping.second.floatValue);
			}
			else if (mapping.second.intValue != nullptr)
			{
				message.addIntArg(*mapping.second.intValue);
			}
			bundle.addMessage(message);
		}
		sender.sendBundle(bundle);
	}
	
}

void DKOscServer::draw()
{

}


void DKOscServer::addModuleParameters()
{
	ofxDatGuiTextInput* component = gui->addTextInput("Port");
	component->setText(ofToString(port));
	component->onTextInputEvent(this, &DKOscServer::onOscPortChange);

	ofxDatGuiTextInput* componentHost = gui->addTextInput("HOST");
	componentHost->setText(host);
	componentHost->onTextInputEvent(this, &DKOscServer::onOscHostChange);

	addressList = gui->addFolder("ADDRESS LIST");

	ofxDatGuiFolder* addParameter = gui->addFolder("ADD ADDRESS");
	ofxDatGuiTextInput* addressName = addParameter->addTextInput("ADDRESS", newAddress);
	addressName->onTextInputEvent(this, &DKOscServer::onAddressNameChange);
	
	ofxDatGuiTextInput* addressMin = addParameter->addTextInput("Min value", "0");
	addressMin->onTextInputEvent(this, &DKOscServer::onAddressMinChange);
	
	ofxDatGuiTextInput* addressMax = addParameter->addTextInput("Max value", "1");
	addressMax->onTextInputEvent(this, &DKOscServer::onAddresMaxChange);
	
	ofxDatGuiTextInput* addressPrecision = addParameter->addTextInput("Precision", "2");
	addressPrecision->onTextInputEvent(this, &DKOscServer::onAddressPrecisionChange);

	ofxDatGuiButton* addParameterButton = addParameter->addButton("ADD");
	addParameterButton->setLabelAlignment(ofxDatGuiAlignment::CENTER);
	addParameterButton->onButtonEvent(this, &DKOscServer::onAddressButtonPressed);

}

void DKOscServer::onOscPortChange(ofxDatGuiTextInputEvent e)
{
	sender.clear();
	port = ofToInt(e.text);
	sender.setup(host, port);
}

void DKOscServer::onOscHostChange(ofxDatGuiTextInputEvent e)
{
	sender.clear();
	host = ofToString(e.text);
	sender.setup(host, port);
}

void DKOscServer::onAddressNameChange(ofxDatGuiTextInputEvent e)
{
	newAddress = e.target->getText();
}

void DKOscServer::onAddressMinChange(ofxDatGuiTextInputEvent e)
{
	min = ofToFloat(e.target->getText());
}

void DKOscServer::onAddresMaxChange(ofxDatGuiTextInputEvent e)
{
	max = ofToFloat(e.target->getText());
}

void DKOscServer::onAddressPrecisionChange(ofxDatGuiTextInputEvent e)
{
	precision = ofToInt(e.target->getText());
}

void DKOscServer::onAddressButtonPressed(ofxDatGuiButtonEvent e)
{
	if (newAddress != "")
	{
		if (precision > 0)
		{
			float* newFloatParam = new float;
			ofxDatGuiSlider* newSlider;
			newSlider = addressList->addSlider(newAddress, min, max);
			newSlider->setPrecision(precision)->bind(*newFloatParam);
			if (getModuleMidiMapMode() != newSlider->getMidiMode())
			{
				newSlider->toggleMidiMode();
			}
			DKoscParam newParam = {nullptr, newFloatParam, false };
			oscMessages.insert({ newAddress, newParam });
		}
		else {
			int* newIntParam = new int;
			params->addSlider(newAddress, (int)min, (int)max, (int)min)->bind(*newIntParam);
			DKoscParam newParam = { newIntParam, nullptr, false };
			oscMessages.insert({ newAddress, newParam });
		}

		gui->setWidth(ofGetWidth() / 5);
	}
}

void DKOscServer::addOscSlider(string address, float* value)
{
	/*oscMappings.insert({ address, value });
	gui->setWidth(450);
	ofxDatGuiSlider* component = gui->addSlider(address, 0.0, 1.0);
	component->setPrecision(4);
	component->bind(*value);
	component->toggleMidiMode();*/
}
