
#include<iostream>
#include <sl/Camera.hpp>
using namespace sl;
using namespace std;
int main(int argc, char **argv) {

    // Create a ZED camera object
    Camera zed;
	//char fileName[] = "zed_recording.svo";
	//char fileName[] = "C:\Users\shany\Desktop\Zed.avi";

    // Set configuration parameters
    InitParameters init_params;
    init_params.depth_mode = DEPTH_MODE_PERFORMANCE; // Use PERFORMANCE depth mode
    init_params.coordinate_units = UNIT_METER; // Use millimeter units (for depth measurements)


    // Open the camera
    ERROR_CODE err = zed.open(init_params);
    if (err != SUCCESS)
        exit(-1);

    // Set runtime parameters after opening the camera
    RuntimeParameters runtime_parameters;
    runtime_parameters.sensing_mode = SENSING_MODE_STANDARD; // Use STANDARD sensing mode

	//if (zed.enableRecording(fileName, SVO_COMPRESSION_MODE_LOSSLESS) == SUCCESS) {
		//zed.enableRecording(fileName, SVO_COMPRESSION_MODE_LOSSLESS);
		
	//}

	Mat savedIm;

    // Capture 50 images and depth, then stop
    int i = 0;
    sl::Mat image, depth, point_cloud;

    while (i < 5000) {
        // A new image is available if grab() returns SUCCESS
        if (zed.grab(runtime_parameters) == SUCCESS) {


			//zed.retrieveImage(savedIm, VIEW_LEFT, MEM_CPU, 0, 0);
			//printf(savedIm.getInfos());

            // Retrieve left image
            zed.retrieveImage(image, VIEW_LEFT);
			
            // Retrieve depth map. Depth is aligned on the left image
            zed.retrieveMeasure(depth, MEASURE_DEPTH);
            // Retrieve colored point cloud. Point cloud is aligned on the left image.
			zed.retrieveMeasure(point_cloud, MEASURE_XYZRGBA);

            // Get and print distance value in mm at the center of the image
            // We measure the distance camera - object using Euclidean distance
            int x = image.getWidth() / 2;
            int y = image.getHeight() / 2;
			sl::float4 point_cloud_value;
			point_cloud.getValue(x, y, &point_cloud_value);

            float distance = sqrt(point_cloud_value.x*point_cloud_value.x + point_cloud_value.y*point_cloud_value.y + point_cloud_value.z*point_cloud_value.z);
            printf("Distance to Camera at (%d, %d): %f mm\n", x, y, distance);

      		// Increment the loop
            i++;
        }
    }

	//zed.disableRecording();
    // Close the camera
	zed.close();
    return 0;
}
