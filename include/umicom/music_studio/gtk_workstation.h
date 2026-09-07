/*-----------------------------------------------------------------------------
 * Umicom Music Studio
 * File: include/umicom/music_studio/gtk_workstation.h
 *
 * PURPOSE:
 *   Expose the thin native music composition over the Framework-owned product
 *   workstation, creative controllers and customisable suite layouts.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#ifndef UMICOM_MUSIC_STUDIO_GTK_WORKSTATION_H
#define UMICOM_MUSIC_STUDIO_GTK_WORKSTATION_H

#include <gtk/gtk.h>

#include "umicom/application/suite_layout/gtk4_product_workstation.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Represent the music studio gtk workstation data shared with callers of this public
 * contract.
 */
typedef struct UmiMusicStudioGtkWorkstation UmiMusicStudioGtkWorkstation;

/** Create Music Studio as a thin client of the shared native product host. */
UmiStatus umi_music_studio_gtk_workstation_create(
    UmiMusicStudioGtkWorkstation **out_workstation);
/** Bind the existing shared product identity to a native window before its
 * first realization. The Framework owns titlebar composition and lifetime;
 * no application catalogue or appearance state is duplicated. */
UmiStatus umi_music_studio_gtk_workstation_bind_window(
    UmiMusicStudioGtkWorkstation *workstation, GtkWindow *window);
/** Explicitly enable shared user-local SQLite layout checkpoints.
 * Native launchers opt in after construction; constructors do no checkpoint I/O.
 * A failed restore leaves the current layout visible and reports its error. */
UmiStatus umi_music_studio_gtk_workstation_enable_checkpoint_storage(
    UmiMusicStudioGtkWorkstation *workstation, int restore_saved);

/** Release the creative shell and all Framework services which it owns. */
void umi_music_studio_gtk_workstation_destroy(
    UmiMusicStudioGtkWorkstation *workstation);
/** Borrow the root widget for a native application window. */
GtkWidget *umi_music_studio_gtk_workstation_widget(
    UmiMusicStudioGtkWorkstation *workstation);
/** Select a compose, arrange or master workspace layout. */
UmiStatus umi_music_studio_gtk_workstation_select_layout(
    UmiMusicStudioGtkWorkstation *workstation,
    const char *layout_id);
/** Copy current layout, creative surface and panel-coverage evidence. */
UmiStatus umi_music_studio_gtk_workstation_snapshot(
    const UmiMusicStudioGtkWorkstation *workstation,
    UmiApplicationProductGtk4WorkstationSnapshot *out_snapshot);

#ifdef __cplusplus
}
#endif

#endif
