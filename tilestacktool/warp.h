#ifndef WARP_H
#define WARP_H

#include <vector>
#include "JSON.h"
#include "Frame.h"

// TODO - if path2stack-projected always uses bounding boxes, we have to remove
// the third parameter: isProjection.

void parse_warp(std::vector<Frame> &frames, JSON path, bool isProjection, JSON settings);

#endif

