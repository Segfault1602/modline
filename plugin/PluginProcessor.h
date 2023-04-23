#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

#include <chorus.h>

//==============================================================================
class ModLinePluginAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    ModLinePluginAudioProcessor();
    ~ModLinePluginAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    using AudioProcessor::processBlock;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState value_tree_state_;
private:
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();

    // 4096 samples should us ~ 85ms of delay at 48kHz
    std::array<dsp::Chorus<4096>, 2> choruses_;

    juce::AudioParameterFloat* mix_;
    juce::AudioParameterFloat* chorus_width_;
    juce::AudioParameterFloat* chorus_speed_;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModLinePluginAudioProcessor)
};