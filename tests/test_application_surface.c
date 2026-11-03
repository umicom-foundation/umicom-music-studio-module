/*-----------------------------------------------------------------------------
 * Umicom Music Studio Module
 * File: tests/test_application_surface.c
 *
 * PURPOSE:
 *   Verify Music Studio starts standard, focus and learning layouts through
 *   the shared Framework surface without requiring audio or AI services.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "umicom/music_studio/application_surface.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

/* Exercise every registered panel controller in each audience. A generic
 * layout must not report successful playback/generation without an executor;
 * this is separate from the native Creative workspace note-editing tests. */
static int verify_unavailable_commands(UmiMusicStudioApplicationSurface *surface)
{
    UmiApplicationPresentationSurfaceRuntime *runtime =
        umi_music_studio_application_surface_runtime(surface);
    if (runtime == NULL || runtime->session.item_count == 0U) return 1;
    for (size_t i = 0U; i < runtime->session.item_count; ++i) {
        UmiApplicationPresentationSurfaceUpdate update;
        UmiStatus status = umi_application_presentation_surface_controller_dispatch(
            &runtime->controllers, runtime->session.items[i].placement,
            UMI_APPLICATION_PRESENTATION_EVENT_COMMAND, "play", &update);
        if (status != UMI_STATUS_NOT_IMPLEMENTED ||
            update.state == UMI_APPLICATION_PRESENTATION_STATE_READY ||
            strstr(update.message, "no audio or generation job was started") == NULL) {
            fprintf(stderr, "Music panel %zu acknowledged an unavailable command\n", i);
            return 1;
        }
    }
    return 0;
}

/*
 * Start this command or application, report setup failures, and return a process exit code
 * to the operating system.
 */
int main(void)
{
    const UmiApplicationComponentRecipeAudience audiences[] = {
        UMI_APPLICATION_COMPONENT_RECIPE_AUDIENCE_LEARNING,
        UMI_APPLICATION_COMPONENT_RECIPE_AUDIENCE_STANDARD,
        UMI_APPLICATION_COMPONENT_RECIPE_AUDIENCE_FOCUS};
    size_t index;
    /* Visit each bounded item once so every record receives the same rule. */
    for (index = 0U; index < sizeof(audiences) / sizeof(audiences[0]); ++index) {
        UmiMusicStudioApplicationSurface *surface = NULL;
        UmiApplicationPresentationSurfaceSnapshot snapshot;
        assert(umi_music_studio_application_surface_create_for_audience(
                   audiences[index], &surface) == UMI_STATUS_OK);
        assert(umi_music_studio_application_surface_snapshot(
                   surface, &snapshot) == UMI_STATUS_OK);
        assert(snapshot.panel_count > 0U);
        assert(snapshot.visible_count > 0U);
        if (verify_unavailable_commands(surface) != 0) {
            umi_music_studio_application_surface_destroy(surface); return 1;
        }
        umi_music_studio_application_surface_destroy(surface);
    }
    return 0;
}
