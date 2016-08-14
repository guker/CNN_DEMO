#ifndef LAYER_H
#define LAYER_H
#include "iostream"
#include "vector"
#include "util.h"
using namespace std;

/// 模板尺寸
class size
{
public:
	int   x;
	int   y;

	size(){};
	~size(){};

	size(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	size divide(size scalesize)
	{
		int x = this->x/scalesize.x;
		int y = this->y/scalesize.y;

		if(x*scalesize.x!= this->x||y*scalesize.y!=this->y)
		{
			std::cout<<this<<"can not divide"<<std::endl;
		}
		return size(x,y);
	}

	size substract(size s,int append)
	{
		int x = this->x-s.x+append;
		int y = this->y-s.y+append;
		return size(x,y);
	}

};


class Layer
{
private:
	int       outMapNum;        /// 每层的Feature Map的数目
	char      type;             /// 层的类型
	size      mapSize;          /// 每层生成的图像尺寸
	size      scaleSize;        /// 池化层模板尺寸
	size      kernelSize;       /// 卷积层模板尺寸
	int       classNum;         /// 输出层的结点个数

public:
	Layer(){};
	~Layer()
	{/*
		delete []kernel;
 		delete []outputmaps;
 		delete []errors;
 		delete []bias;
		*/
	};

	double**** kernel;         /// kernel参数
	double**** outputmaps;     /// ？？？？
	double**** errors;         /// ？？？？
	double*    bias;           /// 偏置

	Layer buildInputLayer(size mapSize);                          /// 输入层
	Layer buildConvLayer(int outMapNum, size kernelize);          /// 卷积层
	Layer buildSampLayer(size scaleSize);                         /// 池化层
	Layer buildOutputLayer(int classNum);                         /// 输出层

	void initKernel(int frontMapNum);
	void initOutputKernel(int frontMapNum,size s);
	void initErros(int batchSize);

	void initOutputmaps(int batchSize)
	{
		outputmaps = new double***[batchSize];
		for (int i=0;i<batchSize;i++)
		{
			outputmaps[i] = new double**[outMapNum];
			for (int j=0; j<outMapNum; j++)
			{
				outputmaps[i][j]=new double*[getMapSize().x];
				for(int ii=0; ii<getMapSize().x; ii++)
				{
					outputmaps[i][j][ii] = new double[getMapSize().y];
				}
			}
		}
	}
	void initBias(int frontmapNum)
	{
		bias = new double[outMapNum];
		for (int i=0; i<outMapNum; i++)
		{
			bias[i]=0.0;
		}
	}

	void setError(int numBatch,int mapNo, int mapX, int mapY, double v);

	double** getError(int numBatch, int mapNo)
	{
		return errors[numBatch][mapNo];
	}

	void setError(int numBatch, int mapNo, double** matrix, int m, int n);

	double** getKernel(int numBatch, int mapNo)
	{
		return kernel[numBatch][mapNo];
	}

	int getOutMapNum()
	{
		return outMapNum;
	}

	char getType()
	{
		return type;
	}

	size getMapSize()
	{
		return mapSize;
	}

	void setMapSize(size mapSize)
	{
		this->mapSize = mapSize;
	}

	void setOutMapNum(int outMapNum)
	{
		this->outMapNum = outMapNum;
	}

	size getKernelSize()
	{
		return kernelSize;
	}

	size getScaleSize()
	{
		return scaleSize;
	}

};
#endif
