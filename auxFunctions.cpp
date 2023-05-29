#include <cmath>

using namespace std;

constexpr double kEarthRadiusKm = 6371.0;
constexpr double toRadians = M_PI/180.0;

inline double getDistance(double lat1, double lon1, double lat2, double lon2){
    double latDif = (lat2 - lat1)*toRadians;
    double lonDif = (lon2 - lon1)*toRadians;

    double a = sin(latDif / 2.0) * sin(latDif / 2.0) +
               cos(lat2*toRadians) * cos(lat2*toRadians) *
               sin(lonDif / 2.0) * sin(lonDif / 2.0);
    double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));

    double distance = kEarthRadiusKm * c;
    return distance;
}