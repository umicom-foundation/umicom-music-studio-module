# Umicom Music Studio Module

Thin C23 product composition built from Framework-owned arranger, prompt,
generation, piano-roll, stems and AI-tool components.

Music Studio can now start learning, standard and focus layouts through the
shared Framework product surface. It supplies useful empty states without
pretending an audio or AI engine ran. See
[the Music Studio application surface guide](docs/APPLICATION_SURFACE_GUIDE.md).

The native `umicom-music-studio` workstation renders compose, arrange and
master layouts with Framework-owned identity, appearance, docking, floating,
grouping and layout editing. Its empty states remain truthful until real audio
and generation providers are connected.

## Review linked context values

Music Studio exposes Framework's reviewed context changes through
`umi_music_studio_workspace_context_review`, `umi_music_studio_workspace_context_apply`
and `umi_music_studio_workspace_clear_context` in
`umicom/music_studio/workspace_commands.h`. A context group is a named value that
related panels can share; for example, a host could use `music.project` with the sample
value `sample-session`. The host must connect that name to its panel consumers.

1. Use a runtime initialised with this product's canonical experience. Prepare
   the requested changes with the review function; preparation changes no live state.
2. Display the copied Framework summary and rows. Keep the runtime and its
   workbench alive while the user reviews the proposed values. If the summary
   reports UI differences, show the captured UI value beside the cached value.
3. Apply only after acceptance, then destroy the review. If the workspace changed,
   prepare a fresh review. Cancelling only destroys the review.

This is a module API; native review screens are separate host work. Context edits
do not execute product commands or external operations. The shared guide at
`framework/docs/guides/REVIEWING_LINKED_CONTEXTS.html` in the Applications checkout
explains capacity, ownership, thread coordination and recovery in more detail.

The [local asset capture guide](docs/LOCAL_ASSETS.html) explains the shared Assets page: select a complete local file, keep its bytes in memory and optionally write a new copy. Captures are not yet saved as project attachments or sent to AI providers.

The [song and video workflow guide](docs/SONG_AND_VIDEO_WORKFLOWS.html) introduces local timed lyrics, beat-aligned shot plans, SRT captions and reviewed PixVerse video requests.

Keep lyrics, a WAV recording and cover artwork in one collection. The **Creative workbench → Asset library** page imports complete files, reorders them, saves and reopens a portable collection, and exports selected assets. It is separate from the scene project and never uploads files. See the [shared asset library guide](../../framework/docs/learning/creative-asset-libraries.html) for limits, save steps and recovery.

The **Audio arrangement** page combines supported PCM WAV assets with timed placements, source trimming, gain and fades. Render in memory, inspect clipping, then export a new stereo WAV. Save the editable arrangement separately from its asset library. See [Arrange audio clips](../../framework/docs/learning/audio-arrangements.html) for the supported formats and complete workflow.

On **Audio clip**, render a range, choose **Load preview for listening**, then press Play. Editing the range retires the player; hiding the page pauses it. Listening volume does not change export gain. See [Listen to audio previews](../../framework/docs/learning/listen-to-audio-previews.html) for supported WAVE files, backend setup and recovery.
