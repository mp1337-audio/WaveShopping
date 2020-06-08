 /*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class WaveShoppingAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    WaveShoppingAudioProcessorEditor (WaveShoppingAudioProcessor&);
    ~WaveShoppingAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:

    Slider gainslider;
    Slider drywetslider;
    Slider outputslider;
    //Slider driveslider;
    //Slider rangeslider;
    //Slider blendslider;

    TextButton powerButton;
    ComboBox choiceBox;

    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> gainAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> drywetAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> outputAttachment;



    std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> buttonAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> choiceAttachment;


    WaveShoppingAudioProcessor& processor;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveShoppingAudioProcessorEditor)
};
