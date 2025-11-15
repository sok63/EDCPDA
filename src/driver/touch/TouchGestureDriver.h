#pragma once

#include <cstdint>
#include <deque>
#include <array>
#include <cmath>
#include <limits>
#include <pda/core/TouchPrimitives.h>

struct sTouchInput
{
    uint8_t n = 0;
    int16_t x = 0;
    int16_t y = 0;
    bool isPressed = false;
    bool justPressed = false;
    bool justReleased = false;
    uint32_t timestamp = 0;
};

struct sTouchConfig
{
    uint32_t longPressTimeMs = 500;
    uint32_t debounceTimeMs = 30;
    uint32_t swipeMaxTimeMs = 400;
    int16_t tapMaxDistance = 20;
    int16_t swipeMinDistance = 50;
    int16_t dragMinDistance = 15;
    uint8_t eventQueueSize = 8;
};

class TouchGestureDriver
{
public:
    explicit TouchGestureDriver(const sTouchConfig& config = sTouchConfig());
    ~TouchGestureDriver();

    void update(const sTouchInput& input);
    bool getNextEvent(sTouchEvent& event);
    bool hasEvents() const;

    void setConfig(const sTouchConfig& config);
    const sTouchConfig& getConfig() const;

    static const char* getGestureName(eGestureType gesture);

private:
    struct FingerTrack {
        bool active = false;
        int internalId = -1;
        uint8_t extId = 0;
        int16_t startX = 0, startY = 0;
        int16_t lastX = 0, lastY = 0;
        uint32_t startTime = 0;
        uint32_t lastTime = 0;
        bool everMoved = false;
        int16_t maxDx = 0, maxDy = 0;
        bool cancelledSingle = false;
    };

    struct PendingTap {
        bool pending = false;
        int16_t x = 0, y = 0;
        int16_t startX = 0, startY = 0;
        uint32_t releaseTime = 0;
        uint32_t startTime = 0;
        uint32_t expireAt = 0;
        uint32_t duration = 0;
    };

    // Очередь событий
    void enqueue(const sTouchEvent& ev);

    // Отслеживание пальцев и устойчивость к смене extId
    int  acquireTrack(uint8_t extId, int16_t x, int16_t y, uint32_t ts, bool forceNew);
    int  findTrackByExt(uint8_t extId) const;
    int  rebindToNearest(uint8_t extId, int16_t x, int16_t y);
    void releaseTrack(int idx, uint32_t ts);
    int  activeCount() const;

    // Управление конфликтами жестов
    void markAllSingleCancelled(); // не включает мультитач-флаги!
    void onSingleReleasedAndClassify(const FingerTrack& f, uint32_t ts);
    void onMultiReleasedAndClassify(uint32_t ts);
    void flushPendingByTime(uint32_t nowTs);

    // Классификация
    eGestureType classifyOneFinger(const FingerTrack& f, uint32_t ts, sTouchEvent& out) const;
    eGestureType classifyPinch(sTouchEvent& out) const;

    // Пинч-метрики
    void updatePinchMetrics();
    void resetPinch();

    // Утилиты
    static int32_t sqr32(int v) { return int32_t(v) * int32_t(v); }
    static int32_t dist2(int x1, int y1, int x2, int y2) {
        return sqr32(x1 - x2) + sqr32(y1 - y2);
    }
    static int16_t clamp16(int v) {
        return static_cast<int16_t>(std::max<int>(std::numeric_limits<int16_t>::min(),
                                                  std::min<int>(std::numeric_limits<int16_t>::max(), v)));
    }

private:
    static constexpr int kMaxTracks = 2;

    sTouchConfig cfg_;
    std::deque<sTouchEvent> q_;
    std::array<FingerTrack, kMaxTracks> tr_{};

    // Двойной тап (pending)
    PendingTap pendingTap_{};

    // Пинч
    bool pinchInitialized_ = false; // база пинча зафиксирована
    bool pinchHadTwo_ = false;      // в сеансе было 2 пальца
    int16_t pinchStartCx_ = 0, pinchStartCy_ = 0;
    int16_t pinchLastCx_ = 0, pinchLastCy_ = 0;
    int32_t pinchStartDist2_ = 0;
    int32_t pinchLastDist2_ = 0;
    uint32_t pinchStartTs_ = 0;
    uint32_t pinchLastTs_ = 0;
};
