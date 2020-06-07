/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WaveShoppingAudioProcessorEditor::WaveShoppingAudioProcessorEditor (WaveShoppingAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    //Float
    gainslider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gainslider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 10);
    gainslider.setRange(0.0, 1.0, 0.1);
    addAndMakeVisible(gainslider);
    gainAttachment = std::make_unique< AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "GAIN", gainslider);

    //blendslider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    //blendslider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, true, 50, 10);
    //blendslider.setRange(0.0f, 1.f, 0.0001);
    //addAndMakeVisible(blendslider);
    //blendAttachment = std::make_unique< AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "BLEND", blendslider);

    //rangeslider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    //rangeslider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, true, 50, 10);
    //rangeslider.setRange(0, 3000.f, 0.0001);
    //addAndMakeVisible(rangeslider);
//    rangeAttachment = std::make_unique< AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "RANGE", rangeslider);

    //driveslider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    //driveslider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, true, 50, 10);
    //driveslider.setRange(0.0f, 1.f, 0.0001);
    //addAndMakeVisible(driveslider);
    //driveAttachment = std::make_unique< AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "DRIVE", driveslider);

    outputslider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    outputslider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 10);
    outputslider.setRange(0.0, 1.0, 0.1);
    addAndMakeVisible(outputslider);
    outputAttachment = std::make_unique< AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "OUTPUT", outputslider);

    drywetslider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    drywetslider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 10);
    drywetslider.setRange(0.0, 1.0, 0.1);
    addAndMakeVisible(drywetslider);
    drywetAttachment = std::make_unique< AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, "DRYWET", drywetslider);

    //Bool
    powerButton.setColour(TextButton::buttonColourId, Colours::red);
    powerButton.setColour(TextButton::buttonOnColourId, Colours::green);
    powerButton.setClickingTogglesState(true);
    powerButton.onClick = [this]() {};
    addAndMakeVisible(powerButton);
    buttonAttachment = std::make_unique <AudioProcessorValueTreeState::ButtonAttachment>(processor.apvts, "BYPASS", powerButton);

    //Choice
    choiceBox.addItem("SoftClip", 1);
    choiceBox.addItem("Sine", 2);
    choiceBox.addItem("Me1rP", 3);
    choiceBox.setJustificationType(Justification::centred);
    addAndMakeVisible(choiceBox);

    choiceAttachment = std::make_unique <AudioProcessorValueTreeState::ComboBoxAttachment>(processor.apvts, "DISTORTION_TYPE", choiceBox);

    //setSize(400, 800);
    setSize(750, 150);
}

WaveShoppingAudioProcessorEditor::~WaveShoppingAudioProcessorEditor()
{
}

//==============================================================================
void WaveShoppingAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll(Colours::darkgrey);

    //const int border{ 10 };

    g.setColour(Colours::yellow);
    g.setFont(20.0f);


    //g.drawText("Audio Parameter Float", getWidth() / 2 - 100, border, 200, 20, Justification::centred);
    //g.drawText("Audio Parameter Int", getWidth() / 2 - 100, 200 + border, 200, 20, Justification::centred);
    //g.drawText("Audio Parameter Bool", getWidth() / 2 - 100, 400 + border, 200, 20, Justification::centred);
    //g.drawText("Audio Parameter Choice", getWidth() / 2 - 100, 600 + border, 200, 20, Justification::centred);

    //const int sectionSize{ 200 };

   // for (int i = sectionSize; i < getHeight(); i += sectionSize)
    //{
     //   g.setColour(Colours::white);
      //  g.drawLine(0, i, getWidth(), i, 10);
    //}
    g.drawText("Drive", getWidth() * 0.1 - 50, getHeight() / 2 - 110, 100, 100, Justification::centred);
    g.drawText("DryWet", getWidth() * 0.2 - 50, getHeight() / 2 - 110, 100, 100, Justification::centred);
    g.drawText("Output", getWidth() * 0.3 - 50, getHeight() / 2 - 110, 100, 100, Justification::centred);
    g.drawText("Bypass", getWidth() * 0.4 - 50, getHeight() / 2 - 110, 100, 100, Justification::centred);
    g.drawText("Type", getWidth() * 0.6 - 50, getHeight() / 2 - 110, 100, 100, Justification::centred);

}

void WaveShoppingAudioProcessorEditor::resized()
{
    //auto bounds = getLocalBounds();
    //const int componentSize{ 100 };
    setResizable(true, true);
    //gainslider.setBounds(150, 50, 50, 50);
    //drywetslider.setBounds(250, 50, 50, 50);
    //outputslider.setBounds(350,50,50,50);
    
    gainslider.setBounds(getWidth() * 0.1 - 50, getHeight() / 2 - 50, 100, 100);
    drywetslider.setBounds(getWidth() * 0.2 - 50, getHeight() / 2 - 50, 100, 100);
    outputslider.setBounds(getWidth() * 0.3 - 50, getHeight() / 2 - 50, 100, 100);
    powerButton.setBounds(getWidth() * 0.4 - 25, getHeight() / 2 - 25, 50, 50);
    choiceBox.setBounds(getWidth() * 0.6 - 100, getHeight() / 2 - 25, 200, 50);

    //blendslider.setBounds(150, 150, 50, 50);
    //rangeslider.setBounds(250, 150, 50, 50);
    //driveslider.setBounds(350, 150, 50, 50);

    //450, 50, 50, 501
    //choiceBox.setBounds(550, 50, 100, 50);
}
