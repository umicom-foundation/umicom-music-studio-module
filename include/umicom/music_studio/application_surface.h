/*-----------------------------------------------------------------------------
 * Umicom Music Studio Module
 * File: include/umicom/music_studio/application_surface.h
 *
 * PURPOSE:
 *   Expose Music Studio standard, focus and learning workspaces through the
 *   shared Framework product surface and creative-workflow controllers.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#ifndef UMICOM_MUSIC_STUDIO_APPLICATION_SURFACE_H
#define UMICOM_MUSIC_STUDIO_APPLICATION_SURFACE_H

#include "umicom/application/presentation/presentation.h"

#ifdef __cplusplus
extern "C" {
#endif

#define UMI_MUSIC_STUDIO_APPLICATION_ID "org.umicom.music-studio"
#define UMI_MUSIC_STUDIO_STANDARD_RECIPE_ID \
    "org.umicom.workspace.music-studio.standard"

/**
 * Represent the music studio application surface data shared with callers of this public
 * contract.
 */
typedef struct UmiMusicStudioApplicationSurface
    UmiMusicStudioApplicationSurface;

/**
 * Initialise music studio application surface from caller-provided values so later
 * operations receive a known state.
 */
UmiStatus umi_music_studio_application_surface_create(
    UmiMusicStudioApplicationSurface **out_surface);
/**
 * Provide the music studio application surface create for audience operation used by this
 * module and its client applications.
 */
UmiStatus umi_music_studio_application_surface_create_for_audience(
    UmiApplicationComponentRecipeAudience audience,
    UmiMusicStudioApplicationSurface **out_surface);
/**
 * Release or reset state held by music studio application surface so the same storage can
 * be reused safely.
 */
void umi_music_studio_application_surface_destroy(
    UmiMusicStudioApplicationSurface *surface);
/**
 * Provide the music studio application surface activate operation used by this module and
 * its client applications.
 */
UmiStatus umi_music_studio_application_surface_activate(
    UmiMusicStudioApplicationSurface *surface, const char *component_id);
/**
 * Provide the music studio application surface deactivate operation used by this module
 * and its client applications.
 */
UmiStatus umi_music_studio_application_surface_deactivate(
    UmiMusicStudioApplicationSurface *surface, const char *component_id);
/**
 * Provide the music studio application surface focus operation used by this module and its
 * client applications.
 */
UmiStatus umi_music_studio_application_surface_focus(
    UmiMusicStudioApplicationSurface *surface, const char *component_id);
/**
 * Provide the music studio application surface refresh operation used by this module and
 * its client applications.
 */
UmiStatus umi_music_studio_application_surface_refresh(
    UmiMusicStudioApplicationSurface *surface);
/**
 * Provide the music studio application surface command operation used by this module and
 * its client applications.
 */
UmiStatus umi_music_studio_application_surface_command(
    UmiMusicStudioApplicationSurface *surface,
    const char *component_id,
    const char *command_id);
/**
 * Provide the music studio application surface context changed operation used by this
 * module and its client applications.
 */
UmiStatus umi_music_studio_application_surface_context_changed(
    UmiMusicStudioApplicationSurface *surface,
    const char *component_id,
    const char *context_value);
/**
 * Provide the music studio application surface advance operation used by this module and
 * its client applications.
 */
UmiStatus umi_music_studio_application_surface_advance(
    UmiMusicStudioApplicationSurface *surface, uint32_t elapsed_seconds);
/**
 * Provide the music studio application surface set background operation used by this
 * module and its client applications.
 */
UmiStatus umi_music_studio_application_surface_set_background(
    UmiMusicStudioApplicationSurface *surface, int background);
/**
 * Provide the music studio application surface snapshot operation used by this module and
 * its client applications.
 */
UmiStatus umi_music_studio_application_surface_snapshot(
    const UmiMusicStudioApplicationSurface *surface,
    UmiApplicationPresentationSurfaceSnapshot *out_snapshot);
/**
 * Provide the music studio application surface runtime operation used by this module and
 * its client applications.
 */
UmiApplicationPresentationSurfaceRuntime *
umi_music_studio_application_surface_runtime(
    UmiMusicStudioApplicationSurface *surface);

#ifdef __cplusplus
}
#endif

#endif
