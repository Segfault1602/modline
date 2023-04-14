#pragma once

#include "PluginProcessor.h"

#include <chorus.h>

//==============================================================================
class ModLinePluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    explicit ModLinePluginAudioProcessorEditor (ModLinePluginAudioProcessor&);
    ~ModLinePluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ModLinePluginAudioProcessor& processorRef;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModLinePluginAudioProcessorEditor)
};