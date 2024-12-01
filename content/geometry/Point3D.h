/**
 * Author: Lucian Bicsi
 * Date: 2020-12-07
 * License: CC0
 * Source:
 * Description: Class to handle points in 3D space.
 * 	T can be e.g. double or long long.
 * Usage:
 * Status: tested
 */
#pragma once

using T = double;
using Face = array<int, 3>;

struct Point { 
  T x = 0, y = 0, z = 0;  
  Point operator+(Point o) { return { x+o.x, y+o.y, z+o.z }; } 
  Point operator-(Point o) { return { x-o.x, y-o.y, z-o.z }; } 
  Point operator*(T d) { return { x*d, y*d, z*d }; } 
  Point operator/(T d) { return { x/d, y/d, z/d }; } 
}; 
// Point orth to the span of (a, b) by right hand rule.
// abs() is equal to 2 * area of triangle.
Point cross(Point a, Point b) {
  return {a.y * b.z - a.z * b.y, 
          a.z * b.x - a.x * b.z, 
          a.x * b.y - a.y * b.x};
}
T dot(Point a, Point b) { return a.x*b.x + a.y*b.y + a.z*b.z; }
T norm(Point p) { return dot(p, p); }
T abs(Point p) { return sqrt(norm(p)); }
// 6 * signed volume of tetrahedron.
T det(Point a, Point b, Point c, Point d) { 
  return dot(a - d, cross(b - d, c - d));
}
//returns point rotated 'theta' radians ccw around axis a
Point rotate_ccw(Point p, Point a, double theta) {
  double s = sin(theta), c = cos(theta); Point u = a / abs(a);
  return u * dot(p, u) * (1-c) + p * c - cross(p, u) * s;
}
