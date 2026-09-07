/*-----------------------------------------------------------------------------
 * Umicom Music Studio
 * File: src/gtk/main.c
 *
 * PURPOSE:
 *   Launch the branded native music workstation while reusable layout and
 *   panel behavior remains owned by Umicom Framework.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include <gtk/gtk.h>
#include <stdio.h>

#include "umicom/music_studio/gtk_workstation.h"
#include "umicom/ui/gtk4/workstation/shell_header.h"
#include "umicom/ui/gtk4/workstation/window_fit.h"

/* Clean up the thin workstation when its application window is destroyed. */
static void workstation_destroy_notify(gpointer data)
{
    umi_music_studio_gtk_workstation_destroy(
        (UmiMusicStudioGtkWorkstation *)data);
}

/* Create one resizable workstation suitable for laptop or larger displays. */
static void on_activate(GtkApplication *application, gpointer user_data)
{
    UmiMusicStudioGtkWorkstation *workstation = NULL;
    GtkWidget *content;
    GtkWindow *window;
    UmiStatus status;
    (void)user_data;
    status = umi_music_studio_gtk_workstation_create(&workstation);
    /* Preserve the original failure result so the caller can respond to the correct cause. */
    if (status != UMI_STATUS_OK) {
        (void)fprintf(stderr, "Unable to create Umicom Music Studio: %s\n",
                      umi_status_text(status));
        g_application_quit(G_APPLICATION(application));
        return;
    }
    /* Only the real native launcher opts into disk checkpoints. */
    {
        UmiStatus storage_status = umi_music_studio_gtk_workstation_enable_checkpoint_storage(workstation, 1);
        if (storage_status != UMI_STATUS_OK)
            (void)fprintf(stderr, "Layout storage unavailable: %s\n", umi_status_text(storage_status));
    }

    content = umi_music_studio_gtk_workstation_widget(workstation);
    /*
     * Protect caller-owned memory by checking that required state is available before it is
     * used.
     */
    if (content == NULL) {
        umi_music_studio_gtk_workstation_destroy(workstation);
        g_application_quit(G_APPLICATION(application));
        return;
    }
    window = GTK_WINDOW(gtk_application_window_new(application));
    gtk_window_set_title(window, "Umicom Music Studio");
    (void)umi_gtk4_ws_apply_window_identity(window);
    /* Let Framework adapt the preferred workstation size to the display. */
    (void)umi_gtk4_ws_window_fit(window, 1240, 800, 960, 600);
    /* Bind the existing Framework identity before the first realization. */
    status = umi_music_studio_gtk_workstation_bind_window(workstation, window);
    if (status != UMI_STATUS_OK) {
        (void)fprintf(stderr, "Umicom Music Studio titlebar failed: %s\n", umi_status_text(status));
        umi_music_studio_gtk_workstation_destroy(workstation);
        gtk_window_destroy(window);
        g_application_quit(G_APPLICATION(application));
        return;
    }
    gtk_window_set_child(window, content);
    g_object_set_data_full(G_OBJECT(window), "umicom-music-workstation",
                           workstation, workstation_destroy_notify);
    gtk_window_present(window);
}

/* Start the application under the identity used by packaging and desktop UI. */
int main(int argc, char **argv)
{
    GtkApplication *application;
    int result;
    g_set_prgname("umicom-music-studio");
    application = gtk_application_new(
        "org.umicom.music-studio", G_APPLICATION_DEFAULT_FLAGS);
    /*
     * Protect caller-owned memory by checking that required state is available before it is
     * used.
     */
    if (application == NULL) return 1;
    g_signal_connect(application, "activate", G_CALLBACK(on_activate), NULL);
    result = g_application_run(G_APPLICATION(application), argc, argv);
    g_object_unref(application);
    return result;
}

#ifdef _WIN32
#include <windows.h>

/* Windows forwards graphical startup to the shared portable main function. */
int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous_instance,
                   LPSTR command_line, int show_command)
{
    (void)instance;
    (void)previous_instance;
    (void)command_line;
    (void)show_command;
    return main(__argc, __argv);
}
#endif
