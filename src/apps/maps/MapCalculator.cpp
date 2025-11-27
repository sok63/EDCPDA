#include "MapCalculator.h"
#include <Arduino.h>

void MapCalculator::latLonToMercator(double latDeg, double lonDeg,
                                     double& xMeters, double& yMeters)
{
    double latRad = degToRad(latDeg);
    double lonRad = degToRad(lonDeg);

    xMeters = EARTH_RADIUS_METERS * lonRad;

    const double maxLat = 85.05112878;
    if (latDeg > maxLat)
        latDeg = maxLat;
    if (latDeg < -maxLat)
        latDeg = -maxLat;
    latRad = degToRad(latDeg);

    yMeters = EARTH_RADIUS_METERS * std::log(std::tan(pi_ / 4.0 + latRad / 2.0));
}

void MapCalculator::mercatorToLatLon(double xMeters, double yMeters,
                                     double& latDeg, double& lonDeg)
{
    double lonRad = xMeters / EARTH_RADIUS_METERS;
    double latRad = 2.0 * std::atan(std::exp(yMeters / EARTH_RADIUS_METERS)) - pi_ / 2.0;

    lonDeg = radToDeg(lonRad);
    latDeg = radToDeg(latRad);
}

MapCalculator::MapCalculator(int32_t screenWidthPx,
                             int32_t screenHeightPx,
                             int32_t tileSizePx)
    : m_screenWidthPx(screenWidthPx)
    , m_screenHeightPx(screenHeightPx)
    , m_tileSizePx(tileSizePx)
{
}

void MapCalculator::setCenterLatLon(double latDeg, double lonDeg)
{
    m_centerLatDeg = latDeg;
    m_centerLonDeg = lonDeg;
}

void MapCalculator::setNewZoom(double metersPerPixel)
{
    if (metersPerPixel < 1.0)
        metersPerPixel = 1.0;
    if (metersPerPixel > static_cast<double>(INT16_MAX))
        metersPerPixel = static_cast<double>(INT16_MAX);

    m_metersPerPixel = metersPerPixel;
}

double MapCalculator::getZoom()
{
    return m_metersPerPixel;
}

void MapCalculator::setNewDetailLevel(int32_t z)
{
    if (z < 0)
        z = 0;
    if (z > 15)
        z = 15;
    m_detailZ = z;
}

int32_t MapCalculator::getDetailLevel()
{
    return m_detailZ;
}

void MapCalculator::centerPixelXY(double& px, double& py) const
{
    double xMeters, yMeters;
    latLonToMercator(m_centerLatDeg, m_centerLonDeg, xMeters, yMeters);

    double worldMeters = worldWidthMeters();
    double wwPx = worldWidthPixels();

    px = (xMeters + worldMeters / 2.0) / worldMeters * wwPx;
    py = (worldMeters / 2.0 - yMeters) / worldMeters * wwPx;
}

void MapCalculator::setNewCenterXY(int32_t screenX, int32_t screenY)
{
    double centerXM, centerYM;
    latLonToMercator(m_centerLatDeg, m_centerLonDeg, centerXM, centerYM);

    double dxScreen = static_cast<double>(screenX) - m_screenWidthPx / 2.0;
    double dyScreen = static_cast<double>(screenY) - m_screenHeightPx / 2.0;

    double dxMeters = dxScreen * m_metersPerPixel;
    double dyMeters = dyScreen * m_metersPerPixel;

    double newCenterXM = centerXM + dxMeters;
    double newCenterYM = centerYM - dyMeters;

    double worldMeters = worldWidthMeters(); // 2 * PI * R
    double halfWorld = worldMeters / 2.0;

    while (newCenterXM < -halfWorld)
        newCenterXM += worldMeters;
    while (newCenterXM > halfWorld)
        newCenterXM -= worldMeters;

    double maxY = PI * EARTH_RADIUS_METERS;
    if (newCenterYM > maxY)
        newCenterYM = maxY;
    if (newCenterYM < -maxY)
        newCenterYM = -maxY;

    double newLatDeg, newLonDeg;
    mercatorToLatLon(newCenterXM, newCenterYM, newLatDeg, newLonDeg);

    m_centerLatDeg = newLatDeg;
    m_centerLonDeg = newLonDeg;
}

MapCalcResult MapCalculator::calculate() const
{
    MapCalcResult res {};

    double wwPx = worldWidthPixels();

    double centerPx, centerPy;
    centerPixelXY(centerPx, centerPy);

    double leftPx = centerPx - m_screenWidthPx / 2.0;
    double rightPx = centerPx + m_screenWidthPx / 2.0;
    double topPx = centerPy - m_screenHeightPx / 2.0;
    double bottomPx = centerPy + m_screenHeightPx / 2.0;

    int64_t tilesPerAxis = static_cast<int64_t>(1) << m_detailZ;

    double tileSizeWorldPx = wwPx / static_cast<double>(tilesPerAxis);

    int32_t tilePxSize = static_cast<int32_t>(std::ceil(tileSizeWorldPx));
    res.tilePixelWidth = tilePxSize;
    res.tilePixelHeight = tilePxSize;

    double leftTileF = leftPx / tileSizeWorldPx;
    double rightTileF = rightPx / tileSizeWorldPx;
    double topTileF = topPx / tileSizeWorldPx;
    double bottomTileF = bottomPx / tileSizeWorldPx;

    int32_t leftTile = static_cast<int32_t>(std::floor(leftTileF));
    int32_t rightTile = static_cast<int32_t>(std::floor(rightTileF));
    int32_t topTile = static_cast<int32_t>(std::floor(topTileF));
    int32_t bottomTile = static_cast<int32_t>(std::floor(bottomTileF));

    auto wrapTileX = [tilesPerAxis](int32_t t) -> int32_t {
        int32_t mod = t % static_cast<int32_t>(tilesPerAxis);
        if (mod < 0)
            mod += static_cast<int32_t>(tilesPerAxis);
        return mod;
    };

    auto clampTileY = [tilesPerAxis](int32_t t) -> int32_t {
        if (t < 0)
            return 0;
        if (t >= static_cast<int32_t>(tilesPerAxis))
            return static_cast<int32_t>(tilesPerAxis - 1);
        return t;
    };

    int32_t startTileX = leftTile;
    int32_t startTileY = topTile;
    int32_t endTileX = rightTile;
    int32_t endTileY = bottomTile;

    res.startTileX = wrapTileX(startTileX);
    res.startTileY = clampTileY(startTileY);

    res.tilesX = endTileX - startTileX + 1;
    res.tilesY = endTileY - startTileY + 1;
    res.tilesZ = m_detailZ;

    double startTileLeftPx = static_cast<double>(startTileX) * tileSizeWorldPx;
    double startTileTopPx = static_cast<double>(startTileY) * tileSizeWorldPx;

    double offsetX = startTileLeftPx - leftPx;
    double offsetY = startTileTopPx - topPx;

    res.offsetScreenX = static_cast<int16_t>(std::round(offsetX));
    res.offsetScreenY = static_cast<int16_t>(std::round(offsetY));

    return res;
}
