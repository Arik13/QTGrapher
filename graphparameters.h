#ifndef GRAPHPARAMETERS_H
#define GRAPHPARAMETERS_H

/*
 * An aggregation of various graph settings
 */
struct GraphParameters {
    int width = 900;
    int height = 900;
    int axisWidth = 1;
    int lineWidth = 2;
    int pointSize = 2;
    int numHorMajorTicks = 8;
    int numVerMajorTicks = 8;
    float red = 0;
    float green = 1;
    float blue = 0;
    float majorTickLength = 0.02f;
    float maxVisDomain = 5;
    float minVisDomain = -5;
    float maxVisRange = 5;
    float minVisRange = -5;
};

#endif // GRAPHPARAMETERS_H
