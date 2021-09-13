#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>


struct PixelXY {
    int BGR[3];
    int grey;
    bool operator < (const PixelXY& pixel) const
    {
        return (grey < pixel.grey);
    }
};

cv::Mat& zadanie1a(cv::Mat_<cv::Vec3b>& I) {
    int matrixA[] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    cv::Mat_<cv::Vec3b> _I = I.clone();
    CV_Assert(I.depth() != sizeof(uchar));
    switch (I.channels()) {
    case 3:
        for (int i = 2; i < I.rows - 3; ++i)
            for (int j = 2; j < I.cols - 3; ++j) {
                int maskIterator = 0;
                float sumB = 0;
                float sumG = 0;
                float sumR = 0;
                for (int k = -2; k < 3; k++)
                    for (int l = -2; l < 3; l++) {
                        sumB += ((float)I(i + k, j + l)[0]) * matrixA[maskIterator]/25.f;
                        sumG += ((float)I(i + k, j + l)[1]) * matrixA[maskIterator]/25.f;
                        sumR += ((float)I(i + k, j + l)[2]) * matrixA[maskIterator]/25.f;
                        maskIterator++;
                    }
                if (sumB < 0) {
                    sumB = 0;
                }
                if (sumB > 255) {
                    sumB = 255;
                }
                if (sumG < 0) {
                    sumG = 0;
                }
                if (sumG > 255) {
                    sumG = 255;
                }
                if (sumR < 0) {
                    sumR = 0;
                }
                if (sumR > 255) {
                    sumR = 255;
                }
                _I(i, j)[0] = sumB;
                _I(i, j)[1] = sumG;
                _I(i, j)[2] = sumR;
            }
        break;
    }
    I = _I;
    return _I;
}

cv::Mat& zadanie1b(cv::Mat_<cv::Vec3b>& I) {
    int matrixB[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,24,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    cv::Mat_<cv::Vec3b> _I = I.clone();
    CV_Assert(I.depth() != sizeof(uchar));
    switch (I.channels()) {
    case 3:
        for (int i = 2; i < I.rows-3; ++i)
            for (int j = 2; j < I.cols-3; ++j) {
                int maskIterator = 0;
                int sumB = 0;
                int sumG = 0;
                int sumR = 0;
                for(int k = -2; k<3; k++)
                    for (int l = -2; l < 3; l++) {
                        sumB += ((int)I(i+k, j+l)[0]) * matrixB[maskIterator];
                        sumG += ((int)I(i+k, j+l)[1]) * matrixB[maskIterator];
                        sumR += ((int)I(i+k, j+l)[2]) * matrixB[maskIterator];
                        maskIterator++;
                    }
                if (sumB < 0) {
                    sumB = 0;
                }
                if (sumB > 255) {
                    sumB = 255;
                }
                if (sumG < 0) {
                    sumG = 0;
                }
                if (sumG > 255) {
                    sumG = 255;
                }
                if (sumR < 0) {
                    sumR = 0;
                }
                if (sumR > 255) {
                    sumR = 255;
                }
                _I(i, j)[0] = sumB;
                _I(i, j)[1] = sumG;
                _I(i, j)[2] = sumR;
            }
        break;
    }
    I = _I;
    return _I;
}

cv::Mat& zadanie2(cv::Mat_<cv::Vec3b>& I, int n, int index) {
    cv::Mat_<cv::Vec3b> _I = I.clone();
    std::vector<PixelXY> matrixPixels;
    CV_Assert(I.depth() != sizeof(uchar));
    switch (I.channels()) {
    case 3:
        for (int i = n/2; i < I.rows - (n/2 + 1); ++i)
            for (int j = n/2; j < I.cols - (n/2 + 1); ++j) {
                    for (int k = -(n / 2); k < (n / 2) + 1; k++)
                        for (int l = -(n / 2); l < (n / 2) + 1; l++) {
                            PixelXY pixelXY;
                            pixelXY.BGR[0] = ((int)I(i + k, j + l)[0]);
                            pixelXY.BGR[1] = ((int)I(i + k, j + l)[1]);
                            pixelXY.BGR[2] = ((int)I(i + k, j + l)[2]);
                            pixelXY.grey = (pixelXY.BGR[0] + pixelXY.BGR[1] + pixelXY.BGR[2]) / 3;
                            matrixPixels.push_back(pixelXY);
                        }
                    std::sort(matrixPixels.begin(), matrixPixels.end()); 
                    _I(i, j)[0] = matrixPixels[index].BGR[0];
                    _I(i, j)[1] = matrixPixels[index].BGR[1];
                    _I(i, j)[2] = matrixPixels[index].BGR[2];
                    matrixPixels.clear();
            }
        break;
    }
    I = _I;
    return _I;
}


int main(int, char *[]) {
    std::cout << "Start ..." << std::endl;
    std::cout << "1: Zadanie 1" << std::endl;
    std::cout << "2: Zadanie 2" << std::endl;
    int x;
    cv::Mat_<cv::Vec3b> image = cv::imread("Lena.png");
    std::cin >> x;
    if (x == 1) {
        std::cout << "1: Filtr dolnoprzepustowy" << std::endl;
        std::cout << "2: Filtr gornoprzepustowy" << std::endl;
        std::cin >> x;
        if (x == 1) {
            zadanie1a(image);
        }
        else {
            zadanie1b(image);
        }
    }
    else {
        int n, index;
        std::cout << "Prosze podac wielkosc macierzy: ";
        std::cin >> n;
        std::cout << std::endl << "Prosze podac indeks: ";
        std::cin >> index;
        std::cout << std::endl << "Prosze czekac...";
        zadanie2(image, n, index);
    }
    
    cv::imshow("Lena",image);
    cv::waitKey(-1);
    return 0;
}
