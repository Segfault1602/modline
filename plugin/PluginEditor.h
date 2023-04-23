#pragma once

#include "PluginProcessor.h"

#include <chorus.h>

//==============================================================================
class ModLinePluginAudioProcessorEditor  : public juce::AudioProcessorEditor, private juce::Slider::Listener
{
public:
    explicit ModLinePluginAudioProcessorEditor (ModLinePluginAudioProcessor&);
    ~ModLinePluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void sliderValueChanged (juce::Slider* slider) override;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.

    juce::Slider mix_slider_;
    juce::Slider width_slider_;
    juce::Slider speed_slider_;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mix_attachment_;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> width_attachment_;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> speed_attachment_;

    ModLinePluginAudioProcessor& processorRef;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModLinePluginAudioProcessorEditor)
};