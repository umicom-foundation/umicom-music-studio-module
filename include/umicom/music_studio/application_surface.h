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

typedef struct UmiMusicStudioApplicationSurface
    UmiMusicStudioApplicationSurface;

UmiStatus umi_music_studio_application_surface_create(
    UmiMusicStudioApplicationSurface **out_surface);
UmiStatus umi_music_studio_application_surface_create_for_audience(
    UmiApplicationComponentRecipeAudience audience,
    UmiMusicStudioApplicationSurface **out_surface);
void umi_music_studio_application_surface_destroy(
    UmiMusicStudioApplicationSurface *surface);
UmiStatus umi_music_studio_application_surface_activate(
    UmiMusicStudioApplicationSurface *surface, const char *component_id);
UmiStatus umi_music_studio_application_surface_deactivate(
    UmiMusicStudioApplicationSurface *surface, const char *component_id);
UmiStatus umi_music_studio_application_surface_focus(
    UmiMusicStudioApplicationSurface *surface, const char *component_id);
UmiStatus umi_music_studio_application_surface_refresh(
    UmiMusicStudioApplicationSurface *surface);
UmiStatus umi_music_studio_application_surface_command(
    UmiMusicStudioApplicationSurface *surface,
    const char *component_id,
    const char *command_id);
UmiStatus umi_music_studio_application_surface_context_changed(
    UmiMusicStudioApplicationSurface *surface,
    const char *component_id,
    const char *context_value);
UmiStatus umi_music_studio_application_surface_advance(
    UmiMusicStudioApplicationSurface *surface, uint32_t elapsed_seconds);
UmiStatus umi_music_studio_application_surface_set_background(
    UmiMusicStudioApplicationSurface *surface, int background);
UmiStatus umi_music_studio_application_surface_snapshot(
    const UmiMusicStudioApplicationSurface *surface,
    UmiApplicationPresentationSurfaceSnapshot *out_snapshot);
UmiApplicationPresentationSurfaceRuntime *
umi_music_studio_application_surface_runtime(
    UmiMusicStudioApplicationSurface *surface);

#ifdef __cplusplus
}
#endif

#endif
