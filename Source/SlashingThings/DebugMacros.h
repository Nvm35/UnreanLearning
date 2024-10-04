#pragma once

#include "DrawDebugHelpers.h"

#define DrawSphere(Location) if(GetWorld())	DrawDebugSphere(GetWorld(), Location, 32.f, 24, FColor::Emerald, true);
#define DRAW_SPHERE_WITH_COLOR(Location, Color) if(GetWorld())	DrawDebugSphere(GetWorld(), Location, 16.f, 16, Color, false, 5.f);
#define DRAW_SPHERE_SINGLEFRAME(Location) if(GetWorld()) DrawDebugSphere(GetWorld(), Location, 32.f, 24, FColor::Emerald, false, -1.f);
#define DrawLine(StartLocation, EndLocation) if(GetWorld()) DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Black, true, -1.f, 0, 1.f);
#define DRAW_LINE_SINGLEFRAME(StartLocation, EndLocation) if(GetWorld()) DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Black, false, -1.f, 0, 1.f);
#define DRAW_POINT(Location) if(GetWorld()) DrawDebugPoint(GetWorld(), Location, 15.f, FColor::Orange, true);
#define DRAW_POINT_SINGLEFRAME(Location) if(GetWorld()) DrawDebugPoint(GetWorld(), Location, 15.f, FColor::Orange, false, -1.f);
#define DRAW_VECTOR(StartLocation, EndLocation) if(GetWorld()) \
	{ \
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Black, true, -1.f, 0, 1.f);\
		DrawDebugPoint(GetWorld(), EndLocation, 15.f, FColor::Orange, true); \
	}
#define DRAW_VECTOR_SIGNLEFRAME(StartLocation, EndLocation) if(GetWorld()) \
	{ \
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Black, false, -1.f, 0, 1.f);\
		DrawDebugPoint(GetWorld(), EndLocation, 15.f, FColor::Orange, false); \
	}