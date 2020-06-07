/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WaveShoppingAudioProcessor::WaveShoppingAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr,"Parameters", createParameters())
#endif
{
}

WaveShoppingAudioProcessor::~WaveShoppingAudioProcessor()
{
}

//==============================================================================
const String WaveShoppingAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool WaveShoppingAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool WaveShoppingAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool WaveShoppingAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double WaveShoppingAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int WaveShoppingAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int WaveShoppingAudioProcessor::getCurrentProgram()
{
    return 0;
}

void WaveShoppingAudioProcessor::setCurrentProgram (int index)
{
}

const String WaveShoppingAudioProcessor::getProgramName (int index)
{
    return {};
}

void WaveShoppingAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void WaveShoppingAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void WaveShoppingAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool WaveShoppingAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif


void WaveShoppingAudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();


    auto gainValue = apvts.getRawParameterValue("GAIN");
    auto drywetValue = apvts.getRawParameterValue("DRYWET");
    auto outputValue = apvts.getRawParameterValue("OUTPUT");
    auto distortion_typeValue = apvts.getRawParameterValue("DISTORTION_TYPE");
    auto bypassValue = apvts.getRawParameterValue("BYPASS");


    float drySignal;
    float wetSignal;
    float fulldry;


    //float mDrive = 1.f;
    //float mRange = 3000.f;
    //float mBlend = 1.f;
    //float mGain = 3.f;
    //float drySignal;
    //float wetSignal;




  // In case we have more outputs than inputs, this code clears any output
  // channels that didn't contain input data, (because these aren't
  // guaranteed to be empty - they may contain garbage).
  // This is here to avoid people getting screaming feedback
  // when they first compile a plugin, but obviously you don't need to keep
  // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);

        for (int sample = 0; sample < buffer.getNumSamples(); sample++)
        {
            fulldry = *channelData;
            drySignal = *channelData;
            wetSignal = *channelData;

            //*channelData *= mDrive * mRange;

            *channelData *= (*gainValue);
            if (*bypassValue == 0)
            {

                switch (int(*distortion_typeValue))
                {

                case 0:
                {
                    wetSignal = ((2.f / float_Pi) * atan(*channelData));
                    break;
                }
                case 1:
                {
                    *channelData /= 100;
                    wetSignal = std::sin(*channelData);
                    break;
                }

                case 2:
                {
                    wetSignal = fabsf(*channelData) / 50;
                    break;
                }


                }

            }
            //*channelData = (((wetSignal * mBlend) + (drySignal * (1.f / mBlend))) / 2.f) * mGain;
            //if (drywetValue != 0) {
            *channelData = (((wetSignal * (*drywetValue)) + (drySignal * (1.f / (*drywetValue)))) / 2.f) * (*outputValue);
            //}
            //else
            //{
            //    *channelData = drySignal * outputValue;
            //}


            //Logger::writeToLog("type " + String(distortion_typeValue) + " drive " + String(mDrive) + " multiplier " + String(mDrive * mRange) + " output " + String(outputValue) + " bypass " + String(bypassValue) + " gain " + String(gainValue) + " drywet " + String(drywetValue) + " blend" + String(mBlend));

            //*channelData = wetSignal;
            channelData++;
        }


        // ..do something to the data...
    }
}
//==============================================================================
bool WaveShoppingAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* WaveShoppingAudioProcessor::createEditor()
{
    return new WaveShoppingAudioProcessorEditor (*this);
}

//==============================================================================
void WaveShoppingAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void WaveShoppingAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new WaveShoppingAudioProcessor();
}

AudioProcessorValueTreeState::ParameterLayout WaveShoppingAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<RangedAudioParameter>> parameters;

    //Float
    parameters.push_back(std::make_unique<AudioParameterFloat>("DRYWET", "Drywet", 0.05f, 1.0f, 0.05f));

    parameters.push_back(std::make_unique<AudioParameterFloat>("GAIN", "Gain", 0.0f, 3000.f, 3000.0f));
    

    parameters.push_back(std::make_unique<AudioParameterFloat>("OUTPUT", "Output", 0.0f, 0.5f, 0.1f));

    //parameters.push_back(std::make_unique<AudioParameterFloat>("BLEND", "Blend", 0.0f, 1.f, 0.0001));

    //parameters.push_back(std::make_unique<AudioParameterFloat>("RANGE", "Range", 0.0f, 3000.f, 0.0001));

    //parameters.push_back(std::make_unique<AudioParameterFloat>("DRIVE", "Drive", 0.0f, 1.0f, 0.0001));

    //Choice
    parameters.push_back(std::make_unique<AudioParameterChoice>("DISTORTION_TYPE", "Distortion_type", StringArray("SoftClip", "Sine", "Me1rP"), 0));
    //parameters.push_back(std::make_unique<AudioParameterChoice>("DISTORTION_TYPE", "Distortion_type", NormalisableRange<float>(1, 3, 1), 0));

    //Bool
    parameters.push_back(std::make_unique<AudioParameterBool>("BYPASS", "Bypass", false));

    return { parameters.begin(), parameters.end() };
}