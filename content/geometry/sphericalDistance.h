/**
 * Author: Lucian Bicsi
 * Date: 2009-04-07
 * License: CC0
 * Description: Conversions to/from spherical coordinates
 * and great circle distance formula
 * Status: somewhat tested locally
 tested with Kattis problem airlinehub
 to be tested with UVa 535
 */
#pragma once

Point3D FromSpherical(double r, double lat, double lon) {
  return Point3D{
    r * cos(lat) * cos(lon),
    r * cos(lat) * sin(lon),
    r * sin(lat)};
}

void ToSpherical(Point3D p, double& r,
                 double& lat, double& lon) {
  r = p.abs(); lat = asin(p.z / r); lon = atan2(p.y, p.x);
}

double SphericalDistance(double r, double lat1, double lon1,
                         double lat2, double lon2) {
	double d = (FromSpherical(1.0, lat1, lon1)
            - FromSpherical(1.0, lat2, lon2)).abs();
	return 2 * r * asin(d / 2);
}
