#pragma once

#include "DrawDebugHelpers.h"

#define DrawSphere(Location) if(GetWorld())	DrawDebugSphere(GetWorld(), Location, 32.f, 24, FColor::Emerald, false, 60.f);
#define DrawLine(StartLocation, EndLocation) if(GetWorld()) DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Black, true, -1.f, 0, 1.f);
#define DRAW_POINT(Location) if(GetWorld()) DrawDebugPoint(GetWorld(), Location, 15.f, FColor::Orange, true);
#define DRAW_VECTOR(StartLocation, EndLocation) if(GetWorld()) \
	{ \
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Black, true, -1.f, 0, 1.f);\
		DrawDebugPoint(GetWorld(), EndLocation, 15.f, FColor::Orange, true); \
	}