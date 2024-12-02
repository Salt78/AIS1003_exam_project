# AIS1003_exam_project

This is a demo showing of OpenCV in conjunction with ThreePP. 
The project's main goal was to achieve scene generation in ThreePP
and then to use OpenCV to recognize, and move the objects.

## How to build?
The project uses cmake fetch content and vcpkg to manage dependencies.
You'll have to specify the path to your vcpkg::

```cmake
-DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake
```

If you use MinGW, you'll also have to add these lines into your cmake config:
```cmake
-DVCPKG_TARGET_TRIPLET=x64-mingw-[DYNAMIC|STATIC] # Choose either static OR dynamic
-DVCPKG_HOST_TRIPLET=x64-mingw-[DYNAMIC|STATIC]   # Only needed if MSVC cant be found
```
## Controls
- **SPACE** - Sort the scene
- **R** - Generate a new scene
- **TAB** - Opens OpenCV preview window
- **X** - Hold to see contour detection ()
- **ENTER** - DLC
- **ESC** - Exit






<img src="imagesReadme/gifs/generatingRND.gif" width="250" height="250"/>


