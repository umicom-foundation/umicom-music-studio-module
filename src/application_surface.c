/*-----------------------------------------------------------------------------
 * Umicom Music Studio Module
 * File: src/application_surface.c
 *
 * PURPOSE:
 *   Compose Music Studio over the Framework product surface while preserving
 *   a small product API for native and future web frontends.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "umicom/music_studio/application_surface.h"

#include <stdlib.h>

#include "umicom/music_studio/application_surface_controllers.h"

struct UmiMusicStudioApplicationSurface {
    UmiApplicationPresentationProductSurface product;
};

UmiStatus umi_music_studio_application_surface_create(
    UmiMusicStudioApplicationSurface **out_surface)
{
    return umi_music_studio_application_surface_create_for_audience(
        UMI_APPLICATION_COMPONENT_RECIPE_AUDIENCE_STANDARD, out_surface);
}

UmiStatus umi_music_studio_application_surface_create_for_audience(
    UmiApplicationComponentRecipeAudience audience,
    UmiMusicStudioApplicationSurface **out_surface)
{
    UmiMusicStudioApplicationSurface *surface;
    UmiStatus status;
    if (out_surface == NULL) return UMI_STATUS_INVALID_ARGUMENT;
    *out_surface = NULL;
    surface = calloc(1U, sizeof(*surface));
    if (surface == NULL) return UMI_STATUS_OUT_OF_MEMORY;
    status = umi_application_presentation_product_surface_init_for_audience(
        UMI_MUSIC_STUDIO_APPLICATION_ID, audience,
        umi_music_studio_application_surface_controllers_register, surface,
        &surface->product);
    if (status != UMI_STATUS_OK) {
        umi_music_studio_application_surface_destroy(surface);
        return status;
    }
    *out_surface = surface;
    return UMI_STATUS_OK;
}

void umi_music_studio_application_surface_destroy(
    UmiMusicStudioApplicationSurface *surface)
{
    if (surface == NULL) return;
    umi_application_presentation_product_surface_dispose(&surface->product);
    free(surface);
}

UmiStatus umi_music_studio_application_surface_activate(
    UmiMusicStudioApplicationSurface *surface, const char *component_id)
{
    return surface != NULL
        ? umi_application_presentation_product_surface_activate(
              &surface->product, component_id)
        : UMI_STATUS_INVALID_ARGUMENT;
}

UmiStatus umi_music_studio_application_surface_deactivate(
    UmiMusicStudioApplicationSurface *surface, const char *component_id)
{
    return surface != NULL
        ? umi_application_presentation_product_surface_deactivate(
              &surface->product, component_id)
        : UMI_STATUS_INVALID_ARGUMENT;
}

UmiStatus umi_music_studio_application_surface_focus(
    UmiMusicStudioApplicationSurface *surface, const char *component_id)
{
    return surface != NULL
        ? umi_application_presentation_product_surface_focus(
              &surface->product, component_id)
        : UMI_STATUS_INVALID_ARGUMENT;
}

UmiStatus umi_music_studio_application_surface_refresh(
    UmiMusicStudioApplicationSurface *surface)
{
    return surface != NULL
        ? umi_application_presentation_product_surface_refresh(
              &surface->product)
        : UMI_STATUS_INVALID_ARGUMENT;
}

UmiStatus umi_music_studio_application_surface_command(
    UmiMusicStudioApplicationSurface *surface,
    const char *component_id,
    const char *command_id)
{
    return surface != NULL
        ? umi_application_presentation_product_surface_command(
              &surface->product, component_id, command_id)
        : UMI_STATUS_INVALID_ARGUMENT;
}

UmiStatus umi_music_studio_application_surface_context_changed(
    UmiMusicStudioApplicationSurface *surface,
    const char *component_id,
    const char *context_value)
{
    return surface != NULL
        ? umi_application_presentation_product_surface_context_changed(
              &surface->product, component_id, context_value)
        : UMI_STATUS_INVALID_ARGUMENT;
}

UmiStatus umi_music_studio_application_surface_advance(
    UmiMusicStudioApplicationSurface *surface, uint32_t elapsed_seconds)
{
    return surface != NULL
        ? umi_application_presentation_product_surface_advance(
              &surface->product, elapsed_seconds)
        : UMI_STATUS_INVALID_ARGUMENT;
}

UmiStatus umi_music_studio_application_surface_set_background(
    UmiMusicStudioApplicationSurface *surface, int background)
{
    return surface != NULL
        ? umi_application_presentation_product_surface_set_background(
              &surface->product, background)
        : UMI_STATUS_INVALID_ARGUMENT;
}

UmiStatus umi_music_studio_application_surface_snapshot(
    const UmiMusicStudioApplicationSurface *surface,
    UmiApplicationPresentationSurfaceSnapshot *out_snapshot)
{
    return surface != NULL
        ? umi_application_presentation_product_surface_snapshot(
              &surface->product, out_snapshot)
        : UMI_STATUS_INVALID_ARGUMENT;
}

UmiApplicationPresentationSurfaceRuntime *
umi_music_studio_application_surface_runtime(
    UmiMusicStudioApplicationSurface *surface)
{
    return surface != NULL
        ? umi_application_presentation_product_surface_runtime(
              &surface->product)
        : NULL;
}
