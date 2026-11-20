# AutoBuild Lite

An original, lightweight Geometry Dash Geode mod project inspired by general
level-building workflows. It does not copy AntiPrime's source code or assets.

## Target

- Android / arm64 (suitable target for the Infinix Hot 40i)
- Geometry Dash 2.208
- Geode v5.11.2 SDK baseline

Geode's release notes describe v5.11.2 as primarily targeting GD 2.2081, with
some 2.209 compatibility fixes. If your installed game reports a different
2.208 patch, update the `gd.android` value to the exact version expected by
your installed Geode SDK before building.

## Current status

This is **source code for an initial UI shell**, not a compiled `.geode` file.
It adds an `AB` button to the main menu and opens a prototype information
popup. The actual level-editor automation is not implemented yet.

## Planned development

1. Editor panel and safe-area layout for mobile screens
2. Grid snapping and placement preview
3. Duplicate / mirror helpers
4. Reusable structure templates
5. Pixel-art conversion and batch placement with object-count limits

## Build on a computer

Install the Geode CLI, Android NDK, and Android Geode SDK binaries, then run:

```sh
geode sdk install-binaries -p android64
geode build -p android64
```

The resulting `.geode` package should be in the `build-android64` folder.
This project has not been compiled or device-tested in this environment.

Official Geode docs:
https://docs.geode-sdk.org/getting-started/create-mod
