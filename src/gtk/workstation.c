/*-----------------------------------------------------------------------------
 * Umicom Music Studio
 * File: src/gtk/workstation.c
 *
 * PURPOSE:
 *   Supply Music Studio identity and creative controllers to the shared
 *   Framework native product workstation.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "umicom/music_studio/gtk_workstation.h"

#include <stdlib.h>

#include "umicom/music_studio/application_surface.h"
#include "umicom/music_studio/application_surface_controllers.h"

struct UmiMusicStudioGtkWorkstation {
    UmiApplicationProductGtk4Workstation *framework_workstation;
};

/* Music Studio contributes its product boundary while Framework supplies the
 * reusable panel renderer, layout editor, docking and appearance services. */
UmiStatus umi_music_studio_gtk_workstation_create(
    UmiMusicStudioGtkWorkstation **out_workstation)
{
    UmiMusicStudioGtkWorkstation *workstation;
    UmiApplicationProductGtk4WorkstationConfig config;
    UmiStatus status;
    /*
     * Protect caller-owned memory by checking that required state is available before it is
     * used.
     */
    if (out_workstation == NULL) return UMI_STATUS_INVALID_ARGUMENT;
    *out_workstation = NULL;
    workstation = (UmiMusicStudioGtkWorkstation *)calloc(
        1U, sizeof(*workstation));
    /*
     * Protect caller-owned memory by checking that required state is available before it is
     * used.
     */
    if (workstation == NULL) return UMI_STATUS_OUT_OF_MEMORY;
    config = umi_application_product_gtk4_workstation_config_default(
        UMI_MUSIC_STUDIO_APPLICATION_ID,
        "Umicom Music Studio",
        umi_music_studio_application_surface_controllers_register,
        NULL);
    config.mode_badge = "Creative";
    status = umi_application_product_gtk4_workstation_create(
        &config, &workstation->framework_workstation);
    /* Preserve the original failure result so the caller can respond to the correct cause. */
    if (status != UMI_STATUS_OK) {
        umi_music_studio_gtk_workstation_destroy(workstation);
        return status;
    }
    *out_workstation = workstation;
    return UMI_STATUS_OK;
}

/* Destruction is null-safe and follows the reverse order of construction. */
void umi_music_studio_gtk_workstation_destroy(
    UmiMusicStudioGtkWorkstation *workstation)
{
    /*
     * Protect caller-owned memory by checking that required state is available before it is
     * used.
     */
    if (workstation == NULL) return;
    umi_application_product_gtk4_workstation_destroy(
        workstation->framework_workstation);
    workstation->framework_workstation = NULL;
    free(workstation);
}

/* The native window borrows this widget from the Framework workstation. */
GtkWidget *umi_music_studio_gtk_workstation_widget(
    UmiMusicStudioGtkWorkstation *workstation)
{
    return workstation != NULL
        ? umi_application_product_gtk4_workstation_widget(
              workstation->framework_workstation)
        : NULL;
}

/* Creative layouts are selected without application-owned geometry state. */
UmiStatus umi_music_studio_gtk_workstation_select_layout(
    UmiMusicStudioGtkWorkstation *workstation,
    const char *layout_id)
{
    return workstation != NULL
        ? umi_application_product_gtk4_workstation_select_layout(
              workstation->framework_workstation, layout_id)
        : UMI_STATUS_INVALID_ARGUMENT;
}

/* Copy diagnostics without exposing mutable controller or GTK objects. */
UmiStatus umi_music_studio_gtk_workstation_snapshot(
    const UmiMusicStudioGtkWorkstation *workstation,
    UmiApplicationProductGtk4WorkstationSnapshot *out_snapshot)
{
    return workstation != NULL
        ? umi_application_product_gtk4_workstation_snapshot(
              workstation->framework_workstation, out_snapshot)
        : UMI_STATUS_INVALID_ARGUMENT;
}
