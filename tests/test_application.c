/*-----------------------------------------------------------------------------
 * Umicom Music Studio Module
 * File: tests/test_application.c
 *
 * PURPOSE:
 *   Verify the product resolves only Framework-owned experience metadata.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include <assert.h>

#include "umicom/music_studio/application.h"

int main(void)
{
    UmiApplicationExperienceStatus status;
    const UmiApplicationExperienceDefinition *definition =
        umi_music_studio_application_experience();

    assert(definition != NULL);
    assert(umi_application_experience_validate(definition) == UMI_STATUS_OK);
    assert(umi_music_studio_application_status(&status) == UMI_STATUS_OK);
    assert(status.feature_count == definition->feature_count);
    assert(status.panel_count == definition->panel_count);
    return 0;
}
