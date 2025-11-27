#include "TouchGestureDriver.h"

TouchGestureDriver::TouchGestureDriver(const sTouchConfig& config)
    : cfg_(config)
{
    q_.clear();
    resetPinch();
}

TouchGestureDriver::~TouchGestureDriver() = default;

void TouchGestureDriver::setConfig(const sTouchConfig& config) {
    cfg_ = config;
    while (q_.size() > cfg_.eventQueueSize && !q_.empty()) q_.pop_front();
}

const sTouchConfig& TouchGestureDriver::getConfig() const { return cfg_; }

bool TouchGestureDriver::hasEvents() const { return !q_.empty(); }

bool TouchGestureDriver::getNextEvent(sTouchEvent& event) {
    if (q_.empty()) return false;
    event = q_.front();
    q_.pop_front();
    return true;
}

const char* TouchGestureDriver::getGestureName(eGestureType g) {
    switch (g) {
        case eGestureType::NONE:             return "NONE";
        case eGestureType::ONEF_TAP:         return "ONEF_TAP";
        case eGestureType::ONEF_DOUBLE_TAP:  return "ONEF_DOUBLE_TAP";
        case eGestureType::ONEF_LONG_PRESS:  return "ONEF_LONG_PRESS";
        case eGestureType::ONEF_SWIPE_UP:    return "ONEF_SWIPE_UP";
        case eGestureType::ONEF_SWIPE_DOWN:  return "ONEF_SWIPE_DOWN";
        case eGestureType::ONEF_SWIPE_LEFT:  return "ONEF_SWIPE_LEFT";
        case eGestureType::ONEF_SWIPE_RIGHT: return "ONEF_SWIPE_RIGHT";
        case eGestureType::ONEF_DRAG:        return "ONEF_DRAG";
        case eGestureType::TWOF_ZOOM_IN:     return "TWOF_ZOOM_IN";
        case eGestureType::TWOF_ZOOM_OUT:    return "TWOF_ZOOM_OUT";
        default: return "?";
    }
}

void TouchGestureDriver::enqueue(const sTouchEvent& ev) {
    if (cfg_.eventQueueSize == 0) return;
    if (q_.size() >= cfg_.eventQueueSize) q_.pop_front();
    q_.push_back(ev);
}

int TouchGestureDriver::activeCount() const {
    int c = 0;
    for (auto& f : tr_) if (f.active) ++c;
    return c;
}

int TouchGestureDriver::findTrackByExt(uint8_t extId) const {
    for (int i = 0; i < kMaxTracks; ++i) {
        if (tr_[i].active && tr_[i].extId == extId) return i;
    }
    return -1;
}

int TouchGestureDriver::rebindToNearest(uint8_t extId, int16_t x, int16_t y) {
    int best = -1;
    int32_t bestD2 = std::numeric_limits<int32_t>::max();
    for (int i = 0; i < kMaxTracks; ++i) {
        if (!tr_[i].active) continue;
        int32_t d2 = dist2(x, y, tr_[i].lastX, tr_[i].lastY);
        if (d2 < bestD2) { bestD2 = d2; best = i; }
    }
    if (best >= 0) {
        tr_[best].extId = extId;
    }
    return best;
}

int TouchGestureDriver::acquireTrack(uint8_t extId, int16_t x, int16_t y, uint32_t ts, bool forceNew) {
    int idx = findTrackByExt(extId);
    if (idx >= 0) return idx;

    if (!forceNew) {
        idx = rebindToNearest(extId, x, y);
        if (idx >= 0) return idx;
    }

    for (int i = 0; i < kMaxTracks; ++i) {
        if (!tr_[i].active) {
            FingerTrack& f = tr_[i];
            f.active = true;
            f.internalId = i;
            f.extId = extId;
            f.startX = f.lastX = x;
            f.startY = f.lastY = y;
            f.startTime = f.lastTime = ts;
            f.everMoved = false;
            f.maxDx = f.maxDy = 0;
            f.cancelledSingle = false;
            return i;
        }
    }
    return rebindToNearest(extId, x, y);
}

void TouchGestureDriver::releaseTrack(int idx, uint32_t ts) {
    if (idx < 0 || idx >= kMaxTracks) return;
    tr_[idx].active = false;
    tr_[idx].lastTime = ts;
}

void TouchGestureDriver::markAllSingleCancelled() {
    for (auto& f : tr_) if (f.active) f.cancelledSingle = true;
}

void TouchGestureDriver::resetPinch() {
    pinchInitialized_ = false;
    pinchHadTwo_ = false;
    pinchStartCx_ = pinchStartCy_ = 0;
    pinchLastCx_ = pinchLastCy_ = 0;
    pinchStartDist2_ = pinchLastDist2_ = 0;
    pinchStartTs_ = pinchLastTs_ = 0;
}

void TouchGestureDriver::updatePinchMetrics() {
    int ids[2]; int k = 0;
    for (int i = 0; i < kMaxTracks; ++i) if (tr_[i].active) ids[k++] = i;
    if (k != 2) return;

    auto& a = tr_[ids[0]];
    auto& b = tr_[ids[1]];
    int cx = (int(a.lastX) + int(b.lastX)) / 2;
    int cy = (int(a.lastY) + int(b.lastY)) / 2;
    int dx = int(b.lastX) - int(a.lastX);
    int dy = int(b.lastY) - int(a.lastY);
    int32_t d2 = dist2(a.lastX, a.lastY, b.lastX, b.lastY);
    uint32_t ts = std::max(a.lastTime, b.lastTime);

    if (!pinchInitialized_) {
        pinchInitialized_ = true;
        pinchHadTwo_ = true;
        pinchStartCx_ = clamp16(cx);
        pinchStartCy_ = clamp16(cy);
        pinchStartDist2_ = d2;
        pinchStartTs_ = std::min(a.startTime, b.startTime);
    }

    pinchLastCx_ = clamp16(cx);
    pinchLastCy_ = clamp16(cy);
    pinchLastDist2_ = d2;
    pinchLastTs_ = ts;

    markAllSingleCancelled();
}

eGestureType TouchGestureDriver::classifyPinch(sTouchEvent& out) const {
    if (!pinchInitialized_) return eGestureType::NONE;

    int64_t delta2 = int64_t(pinchLastDist2_) - int64_t(pinchStartDist2_);
    int32_t thr2 = sqr32(cfg_.dragMinDistance); 
    if (std::llabs(delta2) < thr2) return eGestureType::NONE;

    out.gesture = (delta2 > 0) ? eGestureType::TWOF_ZOOM_IN : eGestureType::TWOF_ZOOM_OUT;
    out.startX = pinchStartCx_;
    out.startY = pinchStartCy_;
    out.x = pinchLastCx_;
    out.y = pinchLastCy_;
    out.deltaX = out.x - out.startX;
    out.deltaY = out.y - out.startY;
    out.duration = (pinchLastTs_ >= pinchStartTs_) ? (pinchLastTs_ - pinchStartTs_) : 0;
    out.timestamp = pinchLastTs_;
    return out.gesture;
}

eGestureType TouchGestureDriver::classifyOneFinger(const FingerTrack& f, uint32_t ts, sTouchEvent& out) const {
    uint32_t dur = (ts >= f.startTime) ? (ts - f.startTime) : 0;
    int dx = int(f.lastX) - int(f.startX);
    int dy = int(f.lastY) - int(f.startY);
    int adx = std::abs(dx);
    int ady = std::abs(dy);
    int maxAbs = std::max(adx, ady);
    int manh = adx + ady;

    if (dur < cfg_.debounceTimeMs && maxAbs <= cfg_.tapMaxDistance) {
        return eGestureType::NONE;
    }

    if (maxAbs <= cfg_.tapMaxDistance) {
        out.gesture = (dur >= cfg_.longPressTimeMs) ? eGestureType::ONEF_LONG_PRESS : eGestureType::ONEF_TAP;
        out.startX = f.startX; out.startY = f.startY;
        out.x = f.lastX; out.y = f.lastY;
        out.deltaX = dx; out.deltaY = dy;
        out.duration = dur;
        out.timestamp = ts;
        return out.gesture;
    }

    if (dur <= cfg_.swipeMaxTimeMs && maxAbs >= cfg_.swipeMinDistance) {
        out.gesture = (adx >= ady)
                      ? ((dx >= 0) ? eGestureType::ONEF_SWIPE_RIGHT : eGestureType::ONEF_SWIPE_LEFT)
                      : ((dy >= 0) ? eGestureType::ONEF_SWIPE_DOWN : eGestureType::ONEF_SWIPE_UP);
        out.startX = f.startX; out.startY = f.startY;
        out.x = f.lastX; out.y = f.lastY;
        out.deltaX = dx; out.deltaY = dy;
        out.duration = dur;
        out.timestamp = ts;
        return out.gesture;
    }

    if (manh >= cfg_.dragMinDistance) {
        out.gesture = eGestureType::ONEF_DRAG;
        out.startX = f.startX; out.startY = f.startY;
        out.x = f.lastX; out.y = f.lastY;
        out.deltaX = dx; out.deltaY = dy;
        out.duration = dur;
        out.timestamp = ts;
        return out.gesture;
    }

    return eGestureType::NONE;
}

void TouchGestureDriver::onSingleReleasedAndClassify(const FingerTrack& f, uint32_t ts) {
    if (f.cancelledSingle) return;

    sTouchEvent ev;
    ev.gesture = eGestureType::NONE;
    auto g = classifyOneFinger(f, ts, ev);

    if (g == eGestureType::ONEF_TAP) {
        if (pendingTap_.pending) {
            bool timeOk = (ts <= pendingTap_.expireAt);
            int adx = std::abs(int(ev.x) - int(pendingTap_.x));
            int ady = std::abs(int(ev.y) - int(pendingTap_.y));
            bool posOk = (std::max(adx, ady) <= cfg_.tapMaxDistance);
            if (timeOk && posOk) {
                sTouchEvent d;
                d.gesture = eGestureType::ONEF_DOUBLE_TAP;
                d.startX = pendingTap_.startX;
                d.startY = pendingTap_.startY;
                d.x = ev.x;
                d.y = ev.y;
                d.deltaX = d.x - d.startX;
                d.deltaY = d.y - d.startY;
                d.duration = (ts >= pendingTap_.startTime) ? (ts - pendingTap_.startTime) : 0;
                d.timestamp = ts;
                enqueue(d);
                pendingTap_ = PendingTap{};
                return;
            } else {
                sTouchEvent t;
                t.gesture = eGestureType::ONEF_TAP;
                t.startX = pendingTap_.startX; t.startY = pendingTap_.startY;
                t.x = pendingTap_.x; t.y = pendingTap_.y;
                t.deltaX = t.x - t.startX; t.deltaY = t.y - t.startY;
                t.duration = pendingTap_.duration;
                t.timestamp = pendingTap_.releaseTime;
                enqueue(t);
                pendingTap_ = PendingTap{};
                pendingTap_.pending = true;
                pendingTap_.x = ev.x; pendingTap_.y = ev.y;
                pendingTap_.startX = ev.startX; pendingTap_.startY = ev.startY;
                pendingTap_.startTime = f.startTime;
                pendingTap_.releaseTime = ts;
                pendingTap_.duration = ev.duration;
                pendingTap_.expireAt = ts + cfg_.swipeMaxTimeMs;
                return;
            }
        } else {
            pendingTap_.pending = true;
            pendingTap_.x = ev.x; pendingTap_.y = ev.y;
            pendingTap_.startX = ev.startX; pendingTap_.startY = ev.startY;
            pendingTap_.startTime = f.startTime;
            pendingTap_.releaseTime = ts;
            pendingTap_.duration = ev.duration;
            pendingTap_.expireAt = ts + cfg_.swipeMaxTimeMs;
            return;
        }
    }

    if (g != eGestureType::NONE) {
        enqueue(ev);
    }
}

void TouchGestureDriver::onMultiReleasedAndClassify(uint32_t) {
    if (!pinchHadTwo_) return;

    sTouchEvent ev;
    ev.gesture = eGestureType::NONE;
    auto g = classifyPinch(ev);
    if (g != eGestureType::NONE) {
        enqueue(ev);
    }
    resetPinch();
}

void TouchGestureDriver::flushPendingByTime(uint32_t nowTs) {
    if (pendingTap_.pending && nowTs > pendingTap_.expireAt) {
        sTouchEvent t;
        t.gesture = eGestureType::ONEF_TAP;
        t.startX = pendingTap_.startX; t.startY = pendingTap_.startY;
        t.x = pendingTap_.x; t.y = pendingTap_.y;
        t.deltaX = t.x - t.startX; t.deltaY = t.y - t.startY;
        t.duration = pendingTap_.duration;
        t.timestamp = pendingTap_.releaseTime;
        enqueue(t);
        pendingTap_ = PendingTap{};
    }
}

void TouchGestureDriver::update(const sTouchInput& in) {
    flushPendingByTime(in.timestamp);

    if (!in.isPressed && !in.justPressed && !in.justReleased) {
        return;
    }

    int idx = -1;

    if (in.justPressed) {
        idx = acquireTrack(in.n, in.x, in.y, in.timestamp, true);
        if (activeCount() == 2) {
            updatePinchMetrics();
        }
    } else {
        idx = findTrackByExt(in.n);
        if (idx < 0) {
            idx = rebindToNearest(in.n, in.x, in.y);
        }
        if (idx < 0) return;
    }

    FingerTrack& f = tr_[idx];

    if (in.isPressed || in.justReleased) {
        int dx = int(in.x) - int(f.startX);
        int dy = int(in.y) - int(f.startY);
        f.maxDx = static_cast<int16_t>(std::max<int>(std::abs(dx), std::abs(f.maxDx)));
        f.maxDy = static_cast<int16_t>(std::max<int>(std::abs(dy), std::abs(f.maxDy)));
        f.everMoved = f.everMoved || (std::abs(dx) > 0 || std::abs(dy) > 0);
        f.lastX = in.x;
        f.lastY = in.y;
        f.lastTime = in.timestamp;
    }

    if (activeCount() == 2) {
        updatePinchMetrics();
    }

    if (in.justReleased) {
        uint32_t ts = in.timestamp;
        bool wasMulti = pinchHadTwo_;
        releaseTrack(idx, ts);

        if (!wasMulti && activeCount() == 0) {
            onSingleReleasedAndClassify(f, ts);
        }

        if (wasMulti && activeCount() == 0) {
            onMultiReleasedAndClassify(ts);
            if (pendingTap_.pending) pendingTap_ = PendingTap{};
        }
    }
}
