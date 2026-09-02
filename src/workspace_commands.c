/*-----------------------------------------------------------------------------
 * Umicom Music Studio Module
 * File: src/workspace_commands.c
 *
 * PURPOSE:
 *   Forward product workspace actions into Framework-owned session and context orchestration.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "umicom/music_studio/workspace_commands.h"

/*
 * Provide the music studio workspace select layout operation used by this module and its
 * client applications.
 */
UmiStatus umi_music_studio_workspace_select_layout(
    UmiApplicationWorkspaceRuntime *runtime,
    const char *layout_id)
{
    return umi_application_workspace_runtime_select_layout(runtime, layout_id);
}

/*
 * Provide the music studio workspace activate panel operation used by this module and its
 * client applications.
 */
UmiStatus umi_music_studio_workspace_activate_panel(
    UmiApplicationWorkspaceRuntime *runtime,
    const char *panel_id)
{
    return umi_application_workspace_runtime_activate_panel(runtime, panel_id);
}

/*
 * Provide the music studio workspace set context operation used by this module and its
 * client applications.
 */
UmiStatus umi_music_studio_workspace_set_context(
    UmiApplicationWorkspaceRuntime *runtime,
    const char *group_id,
    const char *value)
{
    return umi_application_workspace_runtime_set_context(
        runtime, group_id, value);
}

/*
 * Provide the music studio workspace commands operation used by this module and its client
 * applications.
 */
const UmiApplicationCommandSurface *umi_music_studio_workspace_commands(
    const UmiApplicationWorkspaceRuntime *runtime)
{
    return runtime != NULL ? &runtime->commands : NULL;
}
