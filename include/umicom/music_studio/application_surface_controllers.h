/*-----------------------------------------------------------------------------
 * Umicom Music Studio Module
 * File: include/umicom/music_studio/application_surface_controllers.h
 *
 * PURPOSE:
 *   Register creative guidance and local command feedback for every panel in
 *   a selected Framework-owned Music Studio workspace recipe.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#ifndef UMICOM_MUSIC_STUDIO_APPLICATION_SURFACE_CONTROLLERS_H
#define UMICOM_MUSIC_STUDIO_APPLICATION_SURFACE_CONTROLLERS_H

#include "umicom/application/presentation/surface_runtime.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Add music studio application surface controllers only after its inputs and available
 * capacity have been checked.
 */
UmiStatus umi_music_studio_application_surface_controllers_register(
    UmiApplicationPresentationSurfaceRuntime *runtime, void *context);

#ifdef __cplusplus
}
#endif

#endif
