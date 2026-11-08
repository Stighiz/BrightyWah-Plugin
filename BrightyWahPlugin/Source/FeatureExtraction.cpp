#include "FeatureExtraction.h"

RRMS::RRMS(float defaultTime, float defaultMaxTime) : rmsTime(defaultTime), maxTime(defaultMaxTime)
{
}

RRMS::~RRMS()
{
}

void RRMS::prepareToPlay(const double sr)
{
    sampleRate = sr;
    history.setSize(1, static_cast<int>(maxTime * sampleRate));
    reset();
}

void RRMS::releaseResources()
{
    history.setSize(0, 0);
}

void RRMS::processBlock(AudioBuffer<float>& buffer)
{
    const auto numSamples = buffer.getNumSamples();
    auto bufferData = buffer.getWritePointer(0);
    auto historyData = history.getWritePointer(0);

    FloatVectorOperations::multiply(bufferData, bufferData, numSamples);
    FloatVectorOperations::multiply(bufferData, 1.0f / static_cast<float>(windowSize), numSamples);

    for (int smp = 0; smp < numSamples; ++smp)
    {
        sum += bufferData[smp] - historyData[historyIndex];
        historyData[historyIndex] = bufferData[smp];
        bufferData[smp] = sqrt(sum);
        ++historyIndex %= windowSize;
    }
}

void RRMS::setRMSTime(float newValue)
{
    rmsTime = newValue;
    reset();
}

void RRMS::reset()
{
    windowSize = jlimit(1, static_cast<int>(maxTime * sampleRate), static_cast<int>(rmsTime * sampleRate));
    history.clear();
    historyIndex = 0;
    sum = 0.0f;
}


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


CoBE::CoBE() : peakDetectorMainBuffer(Parameters::DEFAULT_RMS_TIME, Parameters::MAX_RMS_TIME), peakDetectorDeltaBuffer(Parameters::DEFAULT_RMS_TIME, Parameters::MAX_RMS_TIME)
{
}

CoBE::~CoBE()
{
}

void CoBE::prepareToPlay(const double sampleRate, const int numChannels, const int numSamples)
{
    peakDetectorMainBuffer.prepareToPlay(sampleRate);
    peakDetectorDeltaBuffer.prepareToPlay(sampleRate);
    deltaBuffer.setSize(numChannels, numSamples);
    deltaBuffer.clear();
}

void CoBE::releaseResources()
{
    deltaBuffer.setSize(0, 0);
    peakDetectorMainBuffer.releaseResources();
    peakDetectorDeltaBuffer.releaseResources();
}

void CoBE::processBlock(AudioBuffer<float>& scBuffer)
{
    const auto numSamples = scBuffer.getNumSamples();

    applyFilter(scBuffer, deltaBuffer);

    peakDetectorMainBuffer.processBlock(scBuffer);
    auto scBufferData = scBuffer.getWritePointer(0);

    peakDetectorDeltaBuffer.processBlock(deltaBuffer);
    auto deltaBufferData = deltaBuffer.getReadPointer(0);

    for (int s = 0; s < numSamples; ++s) {
        scBufferData[s] = deltaBufferData[s] / scBufferData[s];
    }
}

void CoBE::applyFilter(AudioBuffer<float>& scBuffer, AudioBuffer<float>& deltaBuffer)
{
    const auto numSamples = scBuffer.getNumSamples();
    
    auto channelData = scBuffer.getReadPointer(0);
    auto deltaChannelData = deltaBuffer.getWritePointer(0);
    
    deltaChannelData[0] = channelData[0] - oldSample;
    oldSample = channelData[numSamples - 1];
        
    for (int i = 1; i < numSamples; ++i)
        deltaChannelData[i] = channelData[i] - channelData[i - 1];
}

void CoBE::setRMSTime(float newValue)
{
    peakDetectorMainBuffer.setRMSTime(newValue);
    peakDetectorDeltaBuffer.setRMSTime(newValue);
}
