/*
 * @Author: Lei Jiang
 * @Email: leijiang420@163.com
 * @Date: 2020-06-30 16:50:43
 * @Description: code description
 */
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <glog/logging.h>
#include "../src/core/yolo_v2_class.hpp"
#include <string>

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        LOG(ERROR) << "usage " << argv[0] << " image.jpg";
        exit(0);
    }
    string image_path = argv[1];
    cv::Mat img = cv::imread(image_path);
    string cfg = "models/yolov4.cfg";
    string weights = "models/yolov4.weights";

    Detector detect_obj(cfg, weights);
    std::vector<bbox_t> res_vec = detect_obj.detect(image_path, 0.2);
    for (int i = 0; i < res_vec.size(); ++i)
    {
        Rect obj_rec;
        obj_rec.x = res_vec[i].x;
        obj_rec.y = res_vec[i].y;
        obj_rec.width = res_vec[i].w;
        obj_rec.height = res_vec[i].h;
        rectangle(img,obj_rec,Scalar(0,0,255),2);
    }
    imshow("draw",img);
    waitKey(0);

    return 0;
}