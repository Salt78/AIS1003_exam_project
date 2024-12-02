Kandidatnr: 

# Automatic shape sorting in ThreePP

This is a demo showing of OpenCV in conjunction with ThreePP.
The project's main goal was to achieve scene generation in ThreePP
and then to use OpenCV to recognize, and move the objects.

<img src="imagesReadme/gifs/generateRND.gif" width="250" height="250"/>

## How to build?

The project uses cmake fetch content and vcpkg to manage dependencies.
You'll have to specify the path to your vcpkg in the configuration for cmake:

```
-DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake
```

If you use MinGW, you'll also have to add these lines into your cmake config:

```
-DVCPKG_TARGET_TRIPLET=x64-mingw-[DYNAMIC|STATIC] # Choose either static OR dynamic
-DVCPKG_HOST_TRIPLET=x64-mingw-[DYNAMIC|STATIC]   # Only needed if MSVC cant be found
```

## Controls

- **SPACE** - Sort the scene
- **R** - Generate a new scene
- **TAB** - Opens OpenCV preview window
- **X** - Hold to see contour detection (preview window must be open)
- **ENTER** - DLC
- **ESC** - Exit

## Media

[comment]: <> (GPT helped me with the html. I couldn't use the markdown format becuase the images became to big.)

<div style="display: flex; justify-content: space-around; align-items: center;">
  <div style="text-align: center; margin: 10px;">
    <img src="imagesReadme/detection.png" style="width: 250px; height: 250px;" />
    <p>Detection preview</p>
  </div>

  <div style="text-align: center; margin: 10px;">
    <img src="imagesReadme/bigScene.png" style="width: 250px; height: 250px;" />
    <p>Big scene</p>
  </div>

  <div style="text-align: center; margin: 10px;">
    <img src="imagesReadme/bigSceneSorted.png" style="width: 250px; height: 250px;" />
    <p>Big scene sorted</p>
  </div>
</div>





