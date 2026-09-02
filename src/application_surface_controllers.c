/*-----------------------------------------------------------------------------
 * Umicom Music Studio Module
 * File: src/application_surface_controllers.c
 *
 * PURPOSE:
 *   Describe useful empty states for creative panels and report local command
 *   preparation without pretending that an AI or audio engine already ran.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "umicom/music_studio/application_surface_controllers.h"

#include <stdio.h>
#include <string.h>

/* Provide the music guidance operation used by this module and its client applications. */
static const char *music_guidance(const char *component_id)
{
    /* Use the stable identifier comparison to choose the matching record or policy. */
    if (strcmp(component_id, "umicom.music.arranger") == 0)
        return "Create or open a project to begin arranging.";
    /* Use the stable identifier comparison to choose the matching record or policy. */
    if (strcmp(component_id, "umicom.music.prompt") == 0)
        return "Describe the music you want to explore.";
    /* Use the stable identifier comparison to choose the matching record or policy. */
    if (strcmp(component_id, "umicom.music.generations") == 0)
        return "Generated ideas will appear here after an engine is connected.";
    /* Use the stable identifier comparison to choose the matching record or policy. */
    if (strcmp(component_id, "umicom.music.piano-roll") == 0)
        return "Select or create a MIDI clip to edit notes.";
    /* Use the stable identifier comparison to choose the matching record or policy. */
    if (strcmp(component_id, "umicom.music.stems") == 0)
        return "Import audio or generate a song to see its stems.";
    return "Connect an approved creative tool to use it in this project.";
}

/* Provide the music controller operation used by this module and its client applications. */
static UmiStatus music_controller(
    void *context,
    const UmiApplicationPresentationPanelPlacement *placement,
    UmiApplicationPresentationSurfaceEvent event,
    const char *payload,
    UmiApplicationPresentationSurfaceUpdate *out_update)
{
    (void)context;
    /*
     * Protect caller-owned memory by checking that required state is available before it is
     * used.
     */
    if (placement == NULL || placement->panel == NULL || out_update == NULL) {
        return UMI_STATUS_INVALID_ARGUMENT;
    }
    (void)memset(out_update, 0, sizeof(*out_update));
    /* Apply this branch only when its contract condition is satisfied. */
    if (event == UMI_APPLICATION_PRESENTATION_EVENT_UNMOUNT ||
        event == UMI_APPLICATION_PRESENTATION_EVENT_DEACTIVATE) {
        out_update->state = UMI_APPLICATION_PRESENTATION_STATE_DORMANT;
        return UMI_STATUS_OK;
    }
    /* Apply this branch only when its contract condition is satisfied. */
    if (event == UMI_APPLICATION_PRESENTATION_EVENT_COMMAND) {
        out_update->state = UMI_APPLICATION_PRESENTATION_STATE_READY;
        (void)snprintf(out_update->message, sizeof(out_update->message),
                       "Prepared creative command: %s",
                       payload != NULL ? payload : "");
        return UMI_STATUS_OK;
    }
    out_update->state = UMI_APPLICATION_PRESENTATION_STATE_EMPTY;
    (void)snprintf(out_update->message, sizeof(out_update->message), "%s",
                   music_guidance(placement->panel->component_id));
    return UMI_STATUS_OK;
}

/*
 * Add music studio application surface controllers only after its inputs and available
 * capacity have been checked.
 */
UmiStatus umi_music_studio_application_surface_controllers_register(
    UmiApplicationPresentationSurfaceRuntime *runtime, void *context)
{
    /*
     * Protect caller-owned memory by checking that required state is available before it is
     * used.
     */
    if (runtime == NULL) return UMI_STATUS_INVALID_ARGUMENT;
    return umi_application_presentation_surface_runtime_register_controller_for_all(
        runtime, music_controller, context);
}
