***FFMPEG SEI NALU***<br />
Modified FFMPEG to allow the addition of SEI NAL units that can help with metadata insertion and live stream synchronisation provided H.264 codec is used.<br />
_______________________________________________________________________________________________________________________________

***Motivation***<br />
To allow for simpler marker insertion into H.264 video streams that can not only hold additional metadata such as sensor values corresponding to frames, bounding box values etc but can also help in live stream synchronisation.<br />
_______________________________________________________________________________________________________________________________

***Insertor***<br />
The FFMPEG build has been slightly modified to incorporate the addition of markers. Also, a few configure commands have been changed for the AOM build (AOM is unstable but required.... Use the stable build provided). These markers can be added with every I-frame only or with every I-frame and P-frame. The code can be modified to add additional sensor data as well.<br />
 **Steps:** <br/>
* Install all FFMPEG dependencies from the link : https://trac.ffmpeg.org/wiki/CompilationGuide/Ubuntu. For AOM and NASM use the builds provided.<br/>
* While Installing AOM use the following configure command:
  * PATH="$HOME/bin:$PATH" cmake -G "Unix Makefiles" -BUILD_SHARED_LIBS -DCMAKE_C_FLAGS="-fpic" -DCMAKE_CXX_FLAGS="-fpic" -DCMAKE_INSTALL_PREFIX="$HOME/ffmpeg_build" -DENABLE_SHARED=on -DENABLE_NASM=on ../aom <br/>
* Build FFMPEG completely. <br/>
* Copy SEINAlInsertor.c to the directory ffmpeg_sources/ffmpeg/fftools/ path and SEINalInsertor.sh script to the ffmpeg_sources/ffmpeg path.
* Run the SEINalInsertor.sh script to create the SEI Insertor executable
 * Execute SEINalInsertor with the same CLI as FFMPEG but the output stream/video will have the frame markers inserted.

______________________________________________________________________________________________________________________________
***Extractor***<br />
A Python wrapper using BOOST has been written to extract SEI NAL units from the video frames.  

Install Boost using the command: <br/>
* sudo apt-get install libboost-all-dev libboost-python <br/>

Copy the golomb.h and h264_ps.c files into ffmpeg_sources/ffmpeg/libavcodec folder to incorporate a few changes. <br/>


Run the script python2seiextractor.sh to get the Shared Object that can be imported into Python 2. <br/>

Run the script python3seiextractor.sh to get the Shared Object that can be imported into Python 3. <br/>

However, the shared object files created return a frame and an SEI Marker associated with that particular frame. Thus, it is necessary to follow the tutorials in https://github.com/praneet195/NUMPY-OPENCV-CONVERTER to convert a CV:MAT object into a NUMPY Python array.

A sample Python Script has been provided to extract frames with respective SEI in the extractor folder.

The following functions are available in the SEINalExtractor module for python:
* extract_frame_with_sei() : Involves the main code that updates the MAT object and SEI being returned. Return value is frame number being processed.
* getMAT() : Returns a frame as CV:MAT object which cv2 converts to numpy array
* getSEI(): Gets SEI value associated with a particular frame. Returns an empty string if no SEI is found.
* get_current_frame_number(): Returns the current frame number. <br/>

The following steps are required to use the functions in the module:<br/>
  *                     obj=SEINalExtractor.FMV(2, stream_link/video_path)
  *                     obj.connect(True)
  *                     Now obj can access required functions.


_______________________________________________________________________________________________________________________________


***Future Changes***<br/>
* Create a lighter build of FFMPEG as this method is applicable only for H.264 codec. All unnecesary codecs can be removed.
* Need to add custom flags to FFMPEG cli to allow for the selection of Iframe or both iFrame and Pframe options.
* Also need to add flags to allow markers to be published separately by zmq.
* Expose more functions that can be used from FFMPEG.

