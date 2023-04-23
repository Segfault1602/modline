#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ModLinePluginAudioProcessor::ModLinePluginAudioProcessor()
     : AudioProcessor (BusesProperties()
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                       ), value_tree_state_(*this, nullptr, "Parameters", createParameters())
{
}

ModLinePluginAudioProcessor::~ModLinePluginAudioProcessor()
{
}

//==============================================================================
const juce::String ModLinePluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ModLinePluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ModLinePluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ModLinePluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ModLinePluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ModLinePluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ModLinePluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ModLinePluginAudioProcessor::setCurrentProgram (int index)
{
    juce::ignoreUnused (index);
}

const juce::String ModLinePluginAudioProcessor::getProgramName (int index)
{
    juce::ignoreUnused (index);
    return {};
}

void ModLinePluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused (index, newName);
}

//==============================================================================
void ModLinePluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    choruses_[0].Init(sampleRate, 10.f);
    choruses_[1].Init(sampleRate, 10.f);
}

void ModLinePluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool ModLinePluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;

    return true;
}

void ModLinePluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                              juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused (midiMessages);

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    float mixValue = *value_tree_state_.getRawParameterValue("mix");
    float widthValue = *value_tree_state_.getRawParameterValue("width");
    float speedValue = *value_tree_state_.getRawParameterValue("speed");

    for (auto& chorus : choruses_)
    {
        chorus.SetMix(mixValue);
        chorus.SetWidth(widthValue);
        chorus.SetSpeed(speedValue);
    }

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer (channel);
        for (size_t i = 0; i < buffer.getNumSamples(); ++i)
        {
            channelData[i] = choruses_[channel].Tick(channelData[i]);
        }
    }
}

//==============================================================================
bool ModLinePluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ModLinePluginAudioProcessor::createEditor()
{
    return new ModLinePluginAudioProcessorEditor (*this);
}

//==============================================================================
void ModLinePluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    juce::ignoreUnused (destData);
}

void ModLinePluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    juce::ignoreUnused (data, sizeInBytes);
}

juce::AudioProcessorValueTreeState::ParameterLayout ModLinePluginAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("mix", "Mix", 0.f, 1.f, 0.5f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("width", "Width", 0.f, 60.f, 30.f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("speed", "Freq", 0.f, 5.f, 1.f));

    return {parameters.begin(), parameters.end()};
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ModLinePluginAudioProcessor();
}
