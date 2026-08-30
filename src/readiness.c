/*-----------------------------------------------------------------------------
 * Umicom Music Studio Module
 * File: src/readiness.c
 *
 * PURPOSE:
 *   Project the canonical Framework feature backlog without product-local roadmap duplication.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "umicom/music_studio/readiness.h"

#include "umicom/music_studio/runtime.h"
#include "umicom/application/experience_plan.h"

UmiStatus umi_music_studio_readiness_report(
    UmiApplicationReadinessReport *out_report)
{
    const UmiApplicationExperienceDefinition *experience =
        umi_music_studio_runtime_experience();
    if (experience == NULL) return UMI_STATUS_NOT_FOUND;
    return umi_application_readiness_report(experience, out_report);
}

const UmiExperienceFeatureDefinition *umi_music_studio_readiness_next_feature(void)
{
    return umi_application_experience_next_feature(
        umi_music_studio_runtime_experience());
}
