#pragma once

#include <driver/CanInterface.h>

class PeakCanDriver;

class PeakCanInterface : public CanInterface
{
public:
    PeakCanInterface(PeakCanDriver *driver, uint32_t handle);
    virtual ~PeakCanInterface();
    void update();
    uint32_t getHandle() const;

    virtual QString getName() const;

    virtual void applyConfig(const MeasurementInterface &mi);

    virtual int getBitrate();

    virtual QList<CanTiming> getAvailableBitrates();

    virtual void open();
    virtual void close();

    virtual void sendMessage(const CanMessage &msg);
    virtual bool readMessage(CanMessage &msg, unsigned int timeout_ms);

    virtual bool updateStatistics();
    virtual uint32_t getState();
    virtual int getNumRxFrames();
    virtual int getNumRxErrors();
    virtual int getNumTxFrames();
    virtual int getNumTxErrors();
    virtual int getNumRxOverruns();
    virtual int getNumTxDropped();

private:
    uint32_t _handle;
    int64_t _timestampOffset;
    void *_autoResetEvent;

    struct {
        bool autoRestart;
        bool listenOnly;
        int bitrate;
    } _config;

    uint16_t calcBitrateMode(int bitrate);
    QString getErrorText(uint32_t status_code);

};
