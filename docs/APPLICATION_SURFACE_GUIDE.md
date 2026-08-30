# Umicom Music Studio Application Surface

Umicom Music Studio now has a runnable, toolkit-neutral surface assembled from
Framework components. Its standard workspace contains the arranger, prompt,
generations, piano roll, stems and AI tools. Learning gives a beginner three
clear panels. Focus keeps the arranger, piano roll and stems together.

The application starts without an audio engine or AI provider. Empty states
explain how to begin and never pretend that music has been generated. A future
engine adapter can update the same Framework surface when real work completes.

Use `umi_music_studio_application_surface_create()` for the standard layout or
`umi_music_studio_application_surface_create_for_audience()` for learning or
focus. Frontends should render this shared runtime instead of keeping a second
hard-coded panel list.
