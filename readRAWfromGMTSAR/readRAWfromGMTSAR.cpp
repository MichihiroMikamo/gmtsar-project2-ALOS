/*
これはGMTSARによって作られた.SLCファイルを読み込むためのプログラム
*/

#include <iostream>
#include <stdio.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

int existFile(const char* path)
{
    FILE* fp = fopen(path, "r");
    if (fp == NULL) {
        return 0;
    }

    fclose(fp);
    return 1;
}


cv::Mat PowerFunc(cv::Mat img, float gamma)
{
	int width  = img.cols;
	int height = img.rows;

	cv::Mat img2 = cv::Mat::zeros(height, width, CV_8UC1);

	double minVal, maxVal;
  	cv::Point minLoc, maxLoc;
  	cv::minMaxLoc(img, &minVal, &maxVal, &minLoc, &maxLoc);

	for (int y = 0; y < height; y++){
		for(int x = 0; x < width; x++){
			float val = (img.at<float>(y, x)  - minVal) / (maxVal - minVal);
			img2.at<unsigned char>(y, x) = (unsigned char)(std::pow(val, gamma)*255);
		}
	}

	return img2;
}


int readSLCfromGMTSAR(std::string infilename)
{
	if (existFile(infilename.c_str())) {
    std::cout << infilename << " exists." << std::endl;
    }
    else {
        std::cout << infilename << " does not exists." << std::endl;
    }

	FILE *fp;
	fp = fopen(infilename.c_str(), "rb");

	int ydims = 9216*3;
	int xdims = 11304;

	int num_of_pix = ydims * xdims;
	short *slc = (short*)malloc(sizeof(short) * (num_of_pix * 2));
	
	cv::Mat img = cv::Mat::zeros(ydims, xdims, CV_32F);
	
	fread(slc, 2, num_of_pix*2, fp); //short 2byte, ydim * (xdim * 2)

	std::cout << "read " << infilename << std::endl;

	for (int y = 0; y < ydims; y++) {
		for (int x = 0; x < xdims; x++) {
			float Q = slc[(y * xdims + x) * 2 + 0];
			float I = slc[(y * xdims + x) * 2 + 1];

			img.at<float>(y, x) = sqrt(Q*Q + I*I);
		}
	}

	cv::Mat img2;
	cv::resize(img, img2, cv::Size(), 0.05, 0.05, cv::INTER_NEAREST);

	std::string outfilename = infilename + ".hdr";
	cv::imwrite(outfilename, img2);

	// .bmp出力
	std::string outfilenameBmp = infilename + ".bmp";
	cv::Mat imgBmp;
	imgBmp = PowerFunc(img2, 0.8);
	cv::imwrite(outfilenameBmp, imgBmp);


	std::cout << "done." << std::endl;

	fclose(fp);
	free(slc);

	return 0;
}


int readRawfromGMTSAR(std::string infilename)
{
	if (existFile(infilename.c_str())) {
    std::cout << infilename << " exists." << std::endl;
    }
    else {
        std::cout << infilename << " does not exists." << std::endl;
    }

	FILE *fp;
	fp = fopen(infilename.c_str(), "rb");

	int good_bytes = 21020;
	int ydims = 16384*3;
	int xdims = int(good_bytes / 2);

	int num_of_pix = ydims * xdims;
	unsigned char *val = (unsigned char*)malloc(sizeof(unsigned char) * (ydims * good_bytes));
	
	cv::Mat img = cv::Mat::zeros(ydims, xdims, CV_32F);
	
	fread(val, 1, good_bytes * ydims, fp);

	std::cout << "read " << infilename << std::endl;

	for (int y = 0; y < ydims; y++) {
		for (int x = 0; x < xdims; x++) {
			float Q = val[(y * xdims + x) * 2 + 0];
			float I = val[(y * xdims + x) * 2 + 1];

			img.at<float>(y, x) = sqrt(Q*Q + I*I);
		}
	}

	cv::Mat img2;
	cv::resize(img, img2, cv::Size(), 0.05, 0.05, cv::INTER_NEAREST);

	std::string outfilename = infilename + ".hdr";
	cv::imwrite(outfilename, img2);

	// .bmp出力
	std::string outfilenameBmp = infilename + ".bmp";
	cv::Mat imgBmp2;
	imgBmp2 = PowerFunc(img2, 0.8);
	cv::imwrite(outfilenameBmp, imgBmp2);

	std::cout << "done." << std::endl;

	fclose(fp);
	free(val);

	return 0;
}


int readRawfromGMTSARRangeCompressed(std::string infilename)
{
	if (existFile(infilename.c_str())) {
    std::cout << infilename << " exists." << std::endl;
    }
    else {
        std::cout << infilename << " does not exists." << std::endl;
    }

	FILE *fp;
	fp = fopen(infilename.c_str(), "rb");

	int ydims = 16384*3;
	int nrows = 16384*3;
	int xdims = 16384;
	int ranfft = 16384;

	int num_of_pix = ydims * xdims;
	float *val = (float*)malloc(sizeof(float) * (num_of_pix * 2));
	
	cv::Mat img = cv::Mat::zeros(ydims, xdims, CV_32F);
	
	fread(val, sizeof(float), 2 * xdims * ydims, fp);

	std::cout << "read " << infilename << std::endl;

	for (int y = 0; y < ydims; y++) {
		for (int x = 0; x < xdims; x++) {
			float Q = val[(y * xdims + x) * 2 + 0];
			float I = val[(y * xdims + x) * 2 + 1];

			img.at<float>(y, x) = sqrt(Q*Q + I*I);
		}
	}

	cv::Mat img2;
	cv::resize(img, img2, cv::Size(), 0.05, 0.05, cv::INTER_NEAREST);

	std::string outfilename = infilename + ".hdr";
	cv::imwrite(outfilename, img2);

	// .bmp出力
	std::string outfilenameBmp = infilename + ".bmp";
	cv::Mat imgBmp2;
	imgBmp2 = PowerFunc(img2, 0.8);
	cv::imwrite(outfilenameBmp, imgBmp2);

	std::cout << "done." << std::endl;

	fclose(fp);
	free(val);

	return 0;

}


int readRawfromGMTSARRangeCompressedPatch(std::string infilename)
{
	if (existFile(infilename.c_str())) {
    std::cout << infilename << " exists." << std::endl;
    }
    else {
        std::cout << infilename << " does not exists." << std::endl;
    }

	FILE *fp;
	fp = fopen(infilename.c_str(), "rb");

	int nrows = 16384;
	int ydims = nrows;
	int num_rng_bins = 11304;
	int xdims = num_rng_bins;


	int num_of_pix = ydims * xdims;
	float *val = (float*)malloc(sizeof(float) * (num_of_pix * 2));
	
	cv::Mat img = cv::Mat::zeros(ydims, xdims, CV_32F);
	
	fread(val, sizeof(float), 2 * xdims * ydims, fp);

	std::cout << "read " << infilename << std::endl;

	for (int y = 0; y < ydims; y++) {
		for (int x = 0; x < xdims; x++) {
			float Q = val[(y * xdims + x) * 2 + 0];
			float I = val[(y * xdims + x) * 2 + 1];

			img.at<float>(y, x) = sqrt(Q*Q + I*I);
		}
	}

	cv::Mat img2;
	cv::resize(img, img2, cv::Size(), 0.05, 0.05, cv::INTER_NEAREST);

	std::cout << "img2.cols = " << img2.cols << std::endl;
	std::cout << "img2.rows = " << img2.rows << std::endl;

	std::string outfilename = infilename + ".hdr";
	cv::imwrite(outfilename, img2);

	// .bmp出力
	std::string outfilenameBmp = infilename + ".bmp";
	cv::Mat imgBmp2;
	imgBmp2 = PowerFunc(img2, 0.8);
	cv::imwrite(outfilenameBmp, imgBmp2);

	std::cout << "done." << std::endl;

	fclose(fp);
	free(val);

	return 0;

}


int readRawfromGMTSARRangeCompressedPatchLowToHigh(std::string infilename)
{
	if (existFile(infilename.c_str())) {
    std::cout << infilename << " exists." << std::endl;
    }
    else {
        std::cout << infilename << " does not exists." << std::endl;
    }

	FILE *fp;
	fp = fopen(infilename.c_str(), "rb");

	int hi_ind = 12800;
	int low_ind = 3584;
	int ydims = hi_ind - low_ind;
	int num_rng_bins = 11304;
	int xdims = num_rng_bins;


	int num_of_pix = ydims * xdims;
	float *val = (float*)malloc(sizeof(float) * (num_of_pix * 2));
	
	cv::Mat img = cv::Mat::zeros(ydims, xdims, CV_32F);
	
	fread(val, sizeof(float), 2 * xdims * ydims, fp);

	std::cout << "read " << infilename << std::endl;

	for (int y = 0; y < ydims; y++) {
		for (int x = 0; x < xdims; x++) {
			float Q = val[(y * xdims + x) * 2 + 0];
			float I = val[(y * xdims + x) * 2 + 1];

			img.at<float>(y, x) = sqrt(Q*Q + I*I);
		}
	}

	cv::Mat img2;
	cv::resize(img, img2, cv::Size(), 0.05, 0.05, cv::INTER_NEAREST);

	std::cout << "img2.cols = " << img2.cols << std::endl;
	std::cout << "img2.rows = " << img2.rows << std::endl;

	std::string outfilename = infilename + ".hdr";
	cv::imwrite(outfilename, img2);

	// .bmp出力
	std::string outfilenameBmp = infilename + ".bmp";
	cv::Mat imgBmp2;
	imgBmp2 = PowerFunc(img2, 0.8);
	cv::imwrite(outfilenameBmp, imgBmp2);

	std::cout << "done." << std::endl;

	fclose(fp);
	free(val);

	return 0;

}


int readRawfromGMTSARAzimuthCompressedPatch(std::string infilename)
{
	// これはアジマス圧縮後のデータを可視化するための関数
	// レンジ圧縮後のデータを可視化するための関数と内容は同じ

	if (existFile(infilename.c_str())) {
    std::cout << infilename << " exists." << std::endl;
    }
    else {
        std::cout << infilename << " does not exists." << std::endl;
    }

	FILE *fp;
	fp = fopen(infilename.c_str(), "rb");

	int nrows = 16384;
	int ydims = nrows;
	int num_rng_bins = 11304;
	int xdims = num_rng_bins;


	int num_of_pix = ydims * xdims;
	float *val = (float*)malloc(sizeof(float) * (num_of_pix * 2));
	
	cv::Mat img = cv::Mat::zeros(ydims, xdims, CV_32F);
	
	fread(val, sizeof(float), 2 * xdims * ydims, fp);

	std::cout << "read " << infilename << std::endl;

	for (int y = 0; y < ydims; y++) {
		for (int x = 0; x < xdims; x++) {
			float Q = val[(y * xdims + x) * 2 + 0];
			float I = val[(y * xdims + x) * 2 + 1];

			img.at<float>(y, x) = sqrt(Q*Q + I*I);
		}
	}

	cv::Mat img2;
	cv::resize(img, img2, cv::Size(), 0.05, 0.05, cv::INTER_NEAREST);

	std::cout << "img2.cols = " << img2.cols << std::endl;
	std::cout << "img2.rows = " << img2.rows << std::endl;

	std::string outfilename = infilename + ".hdr";
	cv::imwrite(outfilename, img2);

	// .bmp出力
	std::string outfilenameBmp = infilename + ".bmp";
	cv::Mat imgBmp2;
	imgBmp2 = PowerFunc(img2, 0.8);
	cv::imwrite(outfilenameBmp, imgBmp2);

	std::cout << "done." << std::endl;

	fclose(fp);
	free(val);

	return 0;

}


int main(int argc, char *argv[])
{
	// ファイルpathが場所によって異なるのでに注意
	// "../../data/IMG-HH-ALPSRP207600640-H1.0__A.SLC"
	
	// 最終的なSLC画像
	std::string infilename = "data/IMG-HH-ALPSRP207600640-H1.0__A.SLC";
	readSLCfromGMTSAR(infilename);

	std::string infilename2 = "data/CopyData_indata.raw";
	readRawfromGMTSAR(infilename2);

	std::string infilename3 = "data/CopyData_RangeCompressed.raw";
	//readRawfromGMTSARRangeCompressed(infilename3);



	// レンジ圧縮後のipatch
	std::string infilename4 = "data/fdata_ipatch1.raw";
	readRawfromGMTSARRangeCompressedPatch(infilename4);

	std::string infilename5 = "data/fdata_ipatch2.raw";
	readRawfromGMTSARRangeCompressedPatch(infilename5);

	std::string infilename6 = "data/fdata_ipatch3.raw";
	readRawfromGMTSARRangeCompressedPatch(infilename6);



	// アジマス圧縮直後のipatch
	std::string infilename10 = "data/fdata_ipatch1_after_acpatch.raw";
	readRawfromGMTSARAzimuthCompressedPatch(infilename10);

	std::string infilename11 = "data/fdata_ipatch2_after_acpatch.raw";
	readRawfromGMTSARAzimuthCompressedPatch(infilename11);

	std::string infilename12 = "data/fdata_ipatch3_after_acpatch.raw";
	readRawfromGMTSARAzimuthCompressedPatch(infilename12);



	// アジマス圧縮後，low_indからhigh_indを取り出したpatch
	std::string infilename7 = "data/fdata_ipatch1_low_to_high.raw";
	readRawfromGMTSARRangeCompressedPatchLowToHigh(infilename7);

	std::string infilename8 = "data/fdata_ipatch2_low_to_high.raw";
	readRawfromGMTSARRangeCompressedPatchLowToHigh(infilename8);

	std::string infilename9 = "data/fdata_ipatch3_low_to_high.raw";
	readRawfromGMTSARRangeCompressedPatchLowToHigh(infilename9);

	return 0;
}
