/*-----------------------------------------------------------------------------
 * Umicom Music Studio Module
 * File: include/umicom/music_studio/application.h
 *
 * PURPOSE:
 *   Expose the thin application composition over Framework-owned experience metadata and services.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#ifndef UMICOM_MUSIC_STUDIO_APPLICATION_H
#define UMICOM_MUSIC_STUDIO_APPLICATION_H

#include "umicom/application/experience.h"
#include "umicom/application/experience_status.h"

#ifdef __cplusplus
extern "C" {
#endif

#define UMI_MUSIC_STUDIO_MODULE_API_VERSION 1U

/**
 * Provide the music studio application id operation used by this module and its client
 * applications.
 */
const char *umi_music_studio_application_id(void);

/**
 * Provide the music studio application experience operation used by this module and its
 * client applications.
 */
const UmiApplicationExperienceDefinition *
umi_music_studio_application_experience(void);

/**
 * Provide the music studio application status operation used by this module and its client
 * applications.
 */
UmiStatus umi_music_studio_application_status(
    UmiApplicationExperienceStatus *out_status);

#ifdef __cplusplus
}
#endif

#endif
