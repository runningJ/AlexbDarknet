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

void RegionCorrect(Rect &region, int image_w, int image_h)
{
    if (region.x < 0)
    {
        region.x = 0;
    }
    if (region.y < 0)
    {
        region.y = 0;
    }
    if (region.x + region.width > image_w)
    {
        region.width = image_w - region.x - 1;
    }
    if (region.y + region.height > image_h)
    {
        region.height = image_h - region.y - 1;
    }
}

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
    int letter_box = detect_obj.letter_box;
    cout << "letter box value is "<< letter_box<<endl;
    std::vector<bbox_t> res_vec = detect_obj.detect(img, 0.4, 1);
    for (int i = 0; i < res_vec.size(); ++i)
    {
        Rect obj_rec;
        obj_rec.x = res_vec[i].x;
        obj_rec.y = res_vec[i].y;
        obj_rec.width = res_vec[i].w;
        obj_rec.height = res_vec[i].h;
        RegionCorrect(obj_rec, img.cols, img.rows);
        rectangle(img, obj_rec, Scalar(0, 255, 255), 2);
    }
    imshow("draw", img);
    waitKey(0);

    return 0;
}