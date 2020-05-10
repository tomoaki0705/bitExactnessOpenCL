#include <opencv2/opencv.hpp>
#include <opencv2/core/ocl.hpp>
#include <CL/cl.h>
#include <iostream>

const char kernel[] = "                                                                   \n" \
"__kernel void sincosKernel(                                                              \n" \
"       __global float* dstSin, int dst_step, int dst_offset, int dst_rows, int dst_cols, \n" \
"       __global float* dstCos, int src_step, int src_offset,                             \n" \
"       float angleStep)                                                                  \n" \
"{                                                                                        \n" \
"    int theta_idx = get_global_id(0);                                                    \n" \
"    float cosVal;                                                                        \n" \
"    float sinVal = sincos(angleStep * ((float)theta_idx), &cosVal);                      \n" \
"    if (theta_idx < dst_cols)                                                            \n" \
"    {                                                                                    \n" \
"        dstSin[theta_idx] = sinVal;                                                      \n" \
"        dstCos[theta_idx] = cosVal;                                                      \n" \
"    }                                                                                    \n" \
"}                                                                                        \n";

void writeFloatImage(cv::InputArray target, const char* filename)
{
    cv::Mat cpuMat = target.getMat();
    int width = cpuMat.cols;
    cv::Mat writeMat = cv::Mat(1, width * 4, CV_8UC1, cpuMat.data);
    cv::imwrite(filename, writeMat);
}


int main(int argc, const char** argv)
{
    using namespace cv;
    CommandLineParser parser(
        argc, 
        argv, 
        "{angleStep|0.5|step of angle}"
        "{help h ?|false|message}"
    );
    if (parser.get<bool>("help"))
    {
        parser.printMessage();
        return 0;
    }
    float angleStep = parser.get<float>("angleStep");
    std::cout << "angleStep:" << angleStep << std::endl;

    UMat sinResult, cosResult;
    sinResult.create(1, (int)(180.f / angleStep), CV_32FC1);
    cosResult.create(1, (int)(180.f / angleStep), CV_32FC1);

    cv::ocl::Context ctx = cv::ocl::Context::getDefault();
    if (!ctx.ptr())
    {
        std::cerr << "OpenCL is not available" << std::endl;
        return 1;
    }
    cv::ocl::Device device = cv::ocl::Device::getDefault();
    if (!device.compilerAvailable())
    {
        std::cerr << "OpenCL compiler is not available" << std::endl;
        return 1;
    }

    cv::ocl::ProgramSource source(cv::String("sample"), "sincos", kernel, "");
    cv::ocl::Kernel sampleKernel("sincosKernel", source, "");
    if (sampleKernel.empty())
    {
         return 2;
    }

    int workgroup_size = sinResult.cols;
    size_t localThreads[2];
    size_t globalThreads[2];

    localThreads[0] = workgroup_size; localThreads[1] = 1;
    globalThreads[0] = workgroup_size; globalThreads[1] = 1;
    sampleKernel.args(
                    ocl::KernelArg::WriteOnly(sinResult),
                    ocl::KernelArg::WriteOnlyNoSize(cosResult),
                    (float)(CV_PI / (180.f / angleStep)));

    sampleKernel.run(2, globalThreads, NULL, true);
    writeFloatImage(sinResult, "sinResult.bmp");
    writeFloatImage(cosResult, "cosResult.bmp");


    return 0;
}
