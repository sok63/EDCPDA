#pragma once

#include <cmath>
#include <cstdint>

struct MapCalcResult
{
    int32_t tilesZ = 0;
    int32_t tilesX = 0;
    int32_t tilesY = 0;

    int16_t offsetScreenX = 0;
    int16_t offsetScreenY = 0;

    int32_t tilePixelWidth = 0;
    int32_t tilePixelHeight = 0;

    int32_t startTileX = 0;
    int32_t startTileY = 0;
};

class MapCalculator
{
public:
    MapCalculator(int32_t screenWidthPx,
                  int32_t screenHeightPx,
                  int32_t tileSizePx = 4096);

    void setCenterLatLon(double latDeg, double lonDeg);

    double centerLatDeg() const
    {
        return m_centerLatDeg;
    }
    double centerLonDeg() const
    {
        return m_centerLonDeg;
    }

    void setNewZoom(double metersPerPixel);
    double getZoom();

    void setNewDetailLevel(int32_t z);
    int32_t getDetailLevel();

    void setNewCenterXY(int32_t screenX, int32_t screenY);

    MapCalcResult calculate() const;

private:
    static constexpr double EARTH_RADIUS_METERS = 6378137.0; // WGS84
    static constexpr double pi_ = 3.14159265358979323846;

    static double degToRad(double deg)
    {
        return deg * pi_ / 180.0;
    }
    static double radToDeg(double rad)
    {
        return rad * 180.0 / pi_;
    }

    static void latLonToMercator(double latDeg, double lonDeg,
                                 double& xMeters, double& yMeters);

    static void mercatorToLatLon(double xMeters, double yMeters,
                                 double& latDeg, double& lonDeg);

    static double worldWidthMeters()
    {
        return 2.0 * pi_ * EARTH_RADIUS_METERS;
    }

    double worldWidthPixels() const
    {
        return worldWidthMeters() / m_metersPerPixel;
    }

    void centerPixelXY(double& px, double& py) const;

private:
    int32_t m_screenWidthPx;
    int32_t m_screenHeightPx;
    int32_t m_tileSizePx;

    double m_centerLatDeg = 0.0;
    double m_centerLonDeg = 0.0;

    double m_metersPerPixel = 100.0;

    int32_t m_detailZ = 14;
};
