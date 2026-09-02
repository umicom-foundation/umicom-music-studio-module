/*-----------------------------------------------------------------------------
 * Umicom Music Studio Module
 * File: src/application.c
 *
 * PURPOSE:
 *   Bind the product identity to the canonical Framework application-experience catalogue.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "umicom/music_studio/application.h"

#include "umicom/application/experience_catalogue.h"

/*
 * Provide the music studio application id operation used by this module and its client
 * applications.
 */
const char *umi_music_studio_application_id(void)
{
    return "org.umicom.music-studio";
}

/*
 * Provide the music studio application experience operation used by this module and its
 * client applications.
 */
const UmiApplicationExperienceDefinition *
umi_music_studio_application_experience(void)
{
    return umi_application_experience_catalogue_find(
        umi_music_studio_application_id());
}

/*
 * Provide the music studio application status operation used by this module and its client
 * applications.
 */
UmiStatus umi_music_studio_application_status(
    UmiApplicationExperienceStatus *out_status)
{
    const UmiApplicationExperienceDefinition *definition =
        umi_music_studio_application_experience();
    /*
     * Protect caller-owned memory by checking that required state is available before it is
     * used.
     */
    if (definition == NULL) return UMI_STATUS_NOT_FOUND;
    return umi_application_experience_status(definition, out_status);
}
