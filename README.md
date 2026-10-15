# ps5-awake

Payload para PS5 que **impide que la consola entre en reposo**. Al lanzarlo
muestra una vez el aviso *"2026 awake by Franchi"* y luego, cada 15 segundos,
reinicia el contador de reposo del sistema (`sceSystemServicePowerTick`).

```
awake: START
awake: notify("2026 awake by Franchi") rc=0
awake: powertick=0x...
```

## Compilar

Con el [ps5-payload-sdk](https://github.com/ps5-payload-dev/sdk):

```sh
$PS5_PAYLOAD_SDK/bin/prospero-clang -o awake.elf awake.c
```

Después se envía `awake.elf` al cargador de payloads de la consola.

## Lo que NO hace

- No termina solo: sigue activo hasta que se reinicia la consola.
- Si `powertick` sale `0x0`, la función no se encontró y solo muestra el aviso.

Fichero único: [`awake.c`](awake.c).
