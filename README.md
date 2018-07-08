# godot-sfs2x

SmartFoxServer 2X Client API

## Compile

* http://docs.godotengine.org/en/3.0/development/compiling/compiling_for_windows.html

* platform=osx
* platform=windows

```bash
scons -j8 platform=windows tools=yes target=release_debug bits=64
scons -j8 platform=windows tools=no target=release bits=64
scons -j8 platform=windows tools=no target=release_debug bits=64
7z a godot.windows.opt.tools.64.zip godot.windows.opt.tools.64.exe
```

### Mono build

```bash
scons -j8 platform=windows tools=yes module_mono_enabled=yes mono_glue=no bits=64
.\bin\godot.windows.tools.mono.exe --generate-mono-glue modules/mono/glue
scons -j8 platform=windows target=release_debug tools=yes module_mono_enabled=yes bits=64
scons -j8 platform=windws target=debug tools=no module_mono_enabled=yes bits=64
scons -j8 platform=windows target=release tools=no module_mono_enabled=yes bits=64
```
