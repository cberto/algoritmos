# Cómo compilar TP-INTEGRADOR

Esta guía permite preparar el entorno, compilar y ejecutar el proyecto en Windows, Linux y macOS. Ejecutá los comandos desde la carpeta raíz del proyecto, donde está `CMakeLists.txt`, salvo que se indique otra ubicación.

## Qué incluye esta base

- `CMakeLists.txt`: configuración compartida para los tres sistemas.
- `src/main.cpp`: punto de entrada del programa.
- `src/Sistema.cpp`: implementación del sistema, incluida en la compilación.
- `include/`: carpeta para los encabezados `.h` o `.hpp`.
- `data/`: archivos de datos existentes.
- `.gitignore`: excluye las carpetas de compilación de Git.

Se eligió **C++17** como estándar inicial. Por ahora no hay dependencias externas: solo se usa la biblioteca estándar de C++. La configuración puede acompañar el desarrollo del trabajo práctico.

## Compilación automática con scripts

Si ya instalaste las herramientas, podés configurar y compilar con un solo comando. El script directo de Windows compila para desarrollo; los scripts de CMake compilan en **Release**. Todos se detienen si ocurre un error y muestran la ubicación del ejecutable cuando terminan correctamente. No instalan dependencias ni ejecutan el programa.

| Sistema / opción | Comando | Requisitos |
| --- | --- | --- |
| Windows, MSVC directo | `.\compilar.bat` | MSVC y Windows SDK |
| Windows, CMake opcional | `.\compilar-cmake.bat` | MSVC, Windows SDK, NMake y CMake 3.16 o posterior |
| Linux | `bash compilar.sh` | G++, Make y CMake 3.16 o posterior |
| macOS | `bash compilar.sh` | Apple Clang, Make y CMake 3.16 o posterior |

En Windows, `compilar.bat` prepara las herramientas automáticamente; solo `compilar-cmake.bat` requiere una terminal de desarrollo de Visual Studio. En Linux y macOS, `compilar.sh` detecta el sistema y elige el compilador correspondiente. Al invocarlo con `bash`, no hace falta darle permisos de ejecución.

Los scripts localizan el proyecto a partir de su propia ubicación, por lo que también podés invocarlos por su ruta desde otra carpeta. Para ejecutar el programa con sus datos, usá la raíz del proyecto como directorio de trabajo.

## Windows

Instalá Visual Studio 2022 Community con la carga de trabajo **Desarrollo para el escritorio con C++**, incluyendo MSVC y Windows SDK.

Desde PowerShell o CMD, en la raíz del proyecto:

```text
.\compilar.bat
```

El script llama a `vcvars64.bat` para preparar MSVC automáticamente. No hace falta abrir una terminal de desarrollo ni instalar CMake. La ruta configurada es:

```text
C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat
```

Si instalaste otra versión o edición de Visual Studio, cambiá esa ruta en `compilar.bat`.

Después compila `src/main.cpp` y `src/Sistema.cpp`, guarda los archivos intermedios en `work/` y genera **`bicis.exe`** en la raíz. Usa C++17, UTF-8, `/W4 /WX` (las advertencias detienen la compilación) y `/MDd /D_DEBUG` para desarrollo. Esta variante usa el runtime de depuración; para distribuir el programa, usá la alternativa Release con CMake.

Para ejecutar, desde la raíz:

```text
.\bicis.exe
```

El script no incluye pruebas porque todavía no existe `tests/pruebas.cpp`.

### Alternativa opcional: MSVC con CMake

Instalá [CMake para Windows](https://cmake.org/download/) y agregalo al `PATH`. Desde Developer PowerShell for VS, comprobá:

```powershell
cmake --version
Get-Command cl
Get-Command nmake
```

Luego, desde la raíz del proyecto:

```powershell
.\compilar-cmake.bat
.\build\windows\bin\tp_integrador.exe
```

Los comandos equivalentes para compilar manualmente con CMake son:

```powershell
cmake -S . -B build/windows -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build build/windows
```

Esta alternativa también genera un `.exe` con MSVC. CMake organiza la construcción y permite mantener una configuración compartida con Linux y macOS. Sus resultados se guardan en una carpeta distinta de la compilación directa.

## Linux

### 1. Instalar las herramientas

En **Ubuntu o Debian**:

```bash
sudo apt update
sudo apt install build-essential cmake
```

`build-essential` incluye G++ y Make; ver la [lista oficial de dependencias de Ubuntu](https://packages.ubuntu.com/noble/build-essential).

En otras distribuciones, instalá los paquetes equivalentes de **G++, Make y CMake** mediante el gestor de paquetes de tu distribución. Los comandos siguientes son iguales una vez instaladas esas herramientas.

### 2. Verificar la instalación

```bash
g++ --version
make --version
cmake --version
```

### 3. Configurar y compilar

Reemplazá la ruta de ejemplo por la ubicación real del proyecto:

```bash
cd "/ruta/a/TP-INTEGRADOR"
cmake -S . -B build/linux -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=g++
cmake --build build/linux --parallel
```

### 4. Ejecutar

Desde la misma carpeta raíz:

```bash
./build/linux/bin/tp_integrador
```

## macOS

### 1. Instalar las herramientas

Abrí Terminal e instalá las **Command Line Tools de Apple**:

```bash
xcode-select --install
```

Esperá a que termine la instalación en la ventana que se abre. Incluye Apple Clang y Make; no necesitás instalar el IDE completo de Xcode para este proyecto. Consultá la [documentación de Apple](https://developer.apple.com/documentation/xcode/installing-the-command-line-tools).

Para instalar CMake, si ya usás Homebrew:

```bash
brew install cmake
```

Este comando corresponde a la [fórmula oficial de CMake en Homebrew](https://formulae.brew.sh/formula/cmake.html). Si no tenés Homebrew, podés instalarlo siguiendo [su sitio oficial](https://brew.sh/) y las instrucciones finales para habilitarlo en tu terminal.

Como alternativa, instalá CMake desde el [sitio de CMake](https://cmake.org/download/), ubicá `CMake.app` en Aplicaciones y habilitá su ejecutable para la terminal actual:

```bash
export PATH="/Applications/CMake.app/Contents/bin:$PATH"
```

Si elegiste esta alternativa, repetí el `export` en cada terminal nueva o agregalo a tu archivo de configuración de shell (por ejemplo, `~/.zshrc` si usás zsh).

### 2. Verificar la instalación

```bash
clang++ --version
make --version
cmake --version
```

### 3. Configurar y compilar

```bash
cd "/ruta/a/TP-INTEGRADOR"
cmake -S . -B build/macos -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=clang++
cmake --build build/macos --parallel
```

### 4. Ejecutar

Desde la misma carpeta raíz:

```bash
./build/macos/bin/tp_integrador
```

La compilación usa la arquitectura de las herramientas locales, normalmente ARM64 en Apple Silicon y x86_64 en Mac Intel. No genera automáticamente un binario universal.

## Resultado esperado

Una compilación exitosa genera el ejecutable indicado para cada opción. La salida al ejecutarlo depende de la implementación actual del programa.

## Uso durante el desarrollo

### Volver a compilar después de editar código

Ejecutá el comando correspondiente desde la raíz:

| Sistema | Comando |
| --- | --- |
| Windows (MSVC directo) | `.\compilar.bat` |
| Windows (CMake opcional) | `.\compilar-cmake.bat` |
| Linux | `cmake --build build/linux --parallel` |
| macOS | `cmake --build build/macos --parallel` |

Volvé a ejecutar el programa después de que termine la compilación sin errores.

### Agregar archivos

Con `compilar.bat`, agregá cada nuevo `.cpp` a la línea que llama a `cl`, junto a `src\main.cpp` y `src\Sistema.cpp`. Para las variantes con CMake, agregá cada nuevo `.cpp` a `add_executable` en `CMakeLists.txt`. Por ejemplo, después de crear `src/Bicicleta.cpp`:

```cmake
add_executable(tp_integrador
    src/main.cpp
    src/Sistema.cpp
    src/Bicicleta.cpp
)
```

Los encabezados de `include/` ya están en la ruta de búsqueda; podés usar `#include "Bicicleta.h"` si existe `include/Bicicleta.h`. No incluyas archivos `.cpp` con `#include`: CMake los compila por separado. Debe haber una sola función `main` en este ejecutable.

### Compilar para depurar

Los scripts de CMake generan Release; `compilar.bat` usa la configuración de desarrollo de tu ejemplo. Para depurar usando CMake, repetí el comando de configuración de tu sistema, cambiando `-DCMAKE_BUILD_TYPE=Release` por `-DCMAKE_BUILD_TYPE=Debug`. Después, ejecutá el comando de compilación habitual. `Debug` agrega información útil para un depurador; `Release` prioriza las optimizaciones.

### Leer los archivos de datos

Ejecutá el programa desde la **raíz del proyecto**, como muestran los ejemplos, para que rutas relativas como `data/bicicletas.txt` encuentren los archivos. La base no copia los datos a `build/` ni cambia automáticamente el directorio de trabajo. Si usás un IDE, configurá su directorio de ejecución en la raíz del proyecto.

### Mantener el código portable

Usá la biblioteca estándar y guardá los fuentes como UTF-8. Evitá dependencias de un sistema como `windows.h`, `conio.h`, `system("pause")` o `system("cls")` si el mismo código debe funcionar en los tres. Respetá las mayúsculas de los nombres de archivo: Linux suele distinguirlas. Para rutas en C++, podés usar `std::filesystem::path` o rutas relativas con `/`.

## Problemas frecuentes

| Problema | Qué revisar |
| --- | --- |
| `cmake` no se reconoce o `command not found` | Instalá CMake, verificá el `PATH` y abrí otra terminal. |
| Windows no encuentra `cl` o `nmake` | Usá Developer PowerShell for VS y verificá la carga de trabajo de C++. |
| No se encuentra un compilador C++ | Instalá el compilador de tu sistema y verificá su comando antes de configurar. |
| CMake no encuentra `CMakeLists.txt` | Entrá a la raíz del proyecto antes de ejecutar `cmake -S . ...`. |
| Error de generador o compilador en la caché | Usá una carpeta de construcción nueva, por ejemplo `-B build/windows-nuevo`, y usá esa misma carpeta en `cmake --build` y al ejecutar. |
| Error `undefined reference` o símbolo externo sin resolver | Revisá que cada función tenga implementación y que su `.cpp` figure en la línea de `cl` para el script MSVC, o figure en `add_executable` para CMake. |
| No encuentra un archivo de `data/` | Ejecutá desde la raíz y revisá la ruta y las mayúsculas. |
| Se ejecuta una versión vieja | Confirmá que la última compilación terminó sin errores y ejecutá el binario de la carpeta que acabás de compilar. |

No compartas la carpeta `build/` entre equipos o sistemas operativos. Compartí el código y `CMakeLists.txt`; cada equipo genera su propia carpeta de construcción.

Para más detalles sobre configuración y compilación, consultá la [guía oficial de uso de CMake](https://cmake.org/cmake/help/latest/guide/user-interaction/).

## Alcance de la verificación

Se ejecutó `compilar.bat` y se comprobó que inicializa Visual Studio 2022 Community y llama a MSVC. La compilación se detuvo por errores del código actual: falta un `;` en `include/Estacion.h`, no se encuentra `mostrarMenu` en `src/main.cpp` y existen advertencias de ocultamiento de `cout` que `/WX` trata como errores. No se generó un ejecutable exitosamente. No se realizaron pruebas de las variantes CMake, Linux o macOS.