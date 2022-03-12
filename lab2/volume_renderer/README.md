# Volume Renderer

run on OSC Owens **Visualization** Node
```
module load intel/17.0.2
module load cmake
DISPLAY=:0

mkdir build 
cd build 
cmake ..
make 

# ./VR Dataset resolution use_Phong 
./VR heart 50 0
./VR heart 50 1
./VR heart 200 0
./VR heart 200 1
./VR mantle 256 0
./VR mantle 256 1
./VR mantle 512 0
./VR mantle 512 1
```
See the results in "res" directory. 

Higher resolution images give more detail of the volume. 
For the mantle volume, because we use lower opacity when rendering high resolution images, the images are more transparent.

I add a headlight when applying Phong model. 
When we apply Phong model, we can have a better perception of stereo because of the lighting. 
