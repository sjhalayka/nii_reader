#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <strstream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;
#pragma comment(lib, "opencv_world331.lib")

int main(void)
{
	// https://brainder.org/2012/09/23/the-nifti-file-format/
	ifstream infile("example_func.nii", std::ios::binary);

	if (infile.fail())
	{
		cout << "Could not read file example_func.nii" << endl;
		return 0;
	}

	size_t bytes_read = 0;

	cout << "Reading header" << endl;

	int sizeof_header;
	infile.read(reinterpret_cast<char*>(&sizeof_header), sizeof(sizeof_header));
	bytes_read += infile.gcount();

	if (sizeof_header != 348)
	{
		cout << "Invalid header size: should be 348 bytes" << endl;
		return -1;
	}

	char data_type[10];
	infile.read(reinterpret_cast<char*>(&data_type), sizeof(data_type));
	bytes_read += infile.gcount();

	char db_name[18];
	infile.read(reinterpret_cast<char*>(&db_name), sizeof(db_name));
	bytes_read += infile.gcount();

	int extents;
	infile.read(reinterpret_cast<char*>(&extents), sizeof(extents));
	bytes_read += infile.gcount();

	short session_error;
	infile.read(reinterpret_cast<char*>(&session_error), sizeof(session_error));
	bytes_read += infile.gcount();

	char regular;
	infile.read(reinterpret_cast<char*>(&regular), sizeof(regular));
	bytes_read += infile.gcount();

	char dim_info;
	infile.read(reinterpret_cast<char*>(&dim_info), sizeof(dim_info));
	bytes_read += infile.gcount();

	short dim[8];
	infile.read(reinterpret_cast<char*>(&dim), sizeof(dim));
	bytes_read += infile.gcount();

	cout << dim[0] << " dimensions" << endl;
	cout << "Dim 1: " << dim[1] << endl;
	cout << "Dim 2: " << dim[2] << endl;
	cout << "Dim 3: " << dim[3] << endl;
	cout << "Dim 4: " << dim[4] << endl;
	cout << "Dim 5: " << dim[5] << endl;
	cout << "Dim 6: " << dim[6] << endl;
	cout << "Dim 7: " << dim[7] << endl;

	float intent_p1;
	infile.read(reinterpret_cast<char*>(&intent_p1), sizeof(intent_p1));
	bytes_read += infile.gcount();

	float intent_p2;
	infile.read(reinterpret_cast<char*>(&intent_p2), sizeof(intent_p2));
	bytes_read += infile.gcount();

	float intent_p3;
	infile.read(reinterpret_cast<char*>(&intent_p3), sizeof(intent_p3));
	bytes_read += infile.gcount();

	short intent_code;
	infile.read(reinterpret_cast<char*>(&intent_code), sizeof(intent_code));
	bytes_read += infile.gcount();

	short datatype;
	infile.read(reinterpret_cast<char*>(&datatype), sizeof(datatype));
	bytes_read += infile.gcount();

	if (datatype != 16)
	{
		cout << "Data type must be float" << endl;
		return -1;
	}
	else
	{
		cout << "Data type: float" << endl;
	}

	short bitpix;
	infile.read(reinterpret_cast<char*>(&bitpix), sizeof(bitpix));
	bytes_read += infile.gcount();

	if (bitpix != 32)
	{
		cout << "Bits per pixel must be 32-bit" << endl;
		return -1;
	}
	else
	{
		cout << "Bits per pixel: " << bitpix << endl;
	}

	short slice_start;
	infile.read(reinterpret_cast<char*>(&slice_start), sizeof(slice_start));
	bytes_read += infile.gcount();

	float pixdim[8];
	infile.read(reinterpret_cast<char*>(&pixdim), sizeof(pixdim));
	bytes_read += infile.gcount();

	float vox_offset;
	infile.read(reinterpret_cast<char*>(&vox_offset), sizeof(vox_offset));
	bytes_read += infile.gcount();

	float scl_slope;
	infile.read(reinterpret_cast<char*>(&scl_slope), sizeof(scl_slope));
	bytes_read += infile.gcount();

	float scl_inter;
	infile.read(reinterpret_cast<char*>(&scl_inter), sizeof(scl_inter));
	bytes_read += infile.gcount();

	short slice_end;
	infile.read(reinterpret_cast<char*>(&slice_end), sizeof(slice_end));
	bytes_read += infile.gcount();

	char slice_code;
	infile.read(reinterpret_cast<char*>(&slice_code), sizeof(slice_code));
	bytes_read += infile.gcount();

	char xyzt_units;
	infile.read(reinterpret_cast<char*>(&xyzt_units), sizeof(xyzt_units));
	bytes_read += infile.gcount();

	float cal_max;
	infile.read(reinterpret_cast<char*>(&cal_max), sizeof(cal_max));
	bytes_read += infile.gcount();

	float cal_min;
	infile.read(reinterpret_cast<char*>(&cal_min), sizeof(cal_min));
	bytes_read += infile.gcount();

	float slice_duration;
	infile.read(reinterpret_cast<char*>(&slice_duration), sizeof(slice_duration));
	bytes_read += infile.gcount();

	float toffset;
	infile.read(reinterpret_cast<char*>(&toffset), sizeof(toffset));
	bytes_read += infile.gcount();

	int glmax;
	infile.read(reinterpret_cast<char*>(&glmax), sizeof(glmax));
	bytes_read += infile.gcount();

	int glmin;
	infile.read(reinterpret_cast<char*>(&glmin), sizeof(glmin));
	bytes_read += infile.gcount();

	char descrip[80];
	infile.read(reinterpret_cast<char*>(&descrip), sizeof(descrip));
	bytes_read += infile.gcount();

	char aux_file[24];
	infile.read(reinterpret_cast<char*>(&aux_file), sizeof(aux_file));
	bytes_read += infile.gcount();

	short qform_code;
	infile.read(reinterpret_cast<char*>(&qform_code), sizeof(qform_code));
	bytes_read += infile.gcount();

	short sform_code;
	infile.read(reinterpret_cast<char*>(&sform_code), sizeof(sform_code));
	bytes_read += infile.gcount();

	float quatern_b;
	infile.read(reinterpret_cast<char*>(&quatern_b), sizeof(quatern_b));
	bytes_read += infile.gcount();

	float quatern_c;
	infile.read(reinterpret_cast<char*>(&quatern_c), sizeof(quatern_c));
	bytes_read += infile.gcount();

	float quatern_d;
	infile.read(reinterpret_cast<char*>(&quatern_d), sizeof(quatern_d));
	bytes_read += infile.gcount();

	float qoffset_x;
	infile.read(reinterpret_cast<char*>(&qoffset_x), sizeof(qoffset_x));
	bytes_read += infile.gcount();

	float qoffset_y;
	infile.read(reinterpret_cast<char*>(&qoffset_y), sizeof(qoffset_y));
	bytes_read += infile.gcount();

	float qoffset_z;
	infile.read(reinterpret_cast<char*>(&qoffset_z), sizeof(qoffset_z));
	bytes_read += infile.gcount();

	float srow_x[4];
	infile.read(reinterpret_cast<char*>(&srow_x), sizeof(srow_x));
	bytes_read += infile.gcount();

	float srow_y[4];
	infile.read(reinterpret_cast<char*>(&srow_y), sizeof(srow_y));
	bytes_read += infile.gcount();

	float srow_z[4];
	infile.read(reinterpret_cast<char*>(&srow_z), sizeof(srow_z));
	bytes_read += infile.gcount();

	char intent_name[16];
	infile.read(reinterpret_cast<char*>(&intent_name), sizeof(intent_name));
	bytes_read += infile.gcount();

	char magic[4];
	infile.read(reinterpret_cast<char*>(&magic), sizeof(magic));
	bytes_read += infile.gcount();

	cout << "Read " << bytes_read << " bytes" << endl;

	if (bytes_read != 348)
	{
		cout << "Error reading header" << endl;
		return -1;
	}

	long unsigned int num_voxels = dim[1] * dim[2] * dim[3] * dim[4] * dim[5] * dim[6] * dim[7];
	cout << "Reading " << num_voxels << " voxels" << endl;

	vector<float> data(num_voxels, 0);
	infile.read(reinterpret_cast<char*>(&data[0]), sizeof(float)*num_voxels);
	bytes_read = infile.gcount();

	if (bytes_read != sizeof(float)*num_voxels)
	{
		cout << "Error reading file" << endl;
		return -1;
	}

	for (int i = 0; i < dim[7]; i++)
	{
		for (int j = 0; j < dim[6]; j++)
		{
			for (int k = 0; k < dim[5]; k++)
			{
				for (int l = 0; l < dim[4]; l++)
				{
					for (int m = 0; m < dim[3]; m++)
					{
						string file_name = "output_";
						ostringstream oss;
						oss << i << "_" << j << "_" << k << "_" << l << "_" << m;
						file_name += oss.str();
						file_name += ".png";

						Mat img = Mat::zeros(Size(dim[1], dim[2]), CV_8UC3);
					
						for (int n = 0; n < dim[2]; n++)
						{
							for (int o = 0; o < dim[1]; o++)
							{
								size_t index = i*dim[6] * dim[5] * dim[4] * dim[3] * dim[2] * dim[1];
								      index += j*dim[5] * dim[4] * dim[3] * dim[2] * dim[1];
								      index += k*dim[4] * dim[3] * dim[2] * dim[1];
								      index += l*dim[3] * dim[2] * dim[1];
								      index += m*dim[2] * dim[1];
								      index += n*dim[1];
								      index += o;

								float f = data[index];

								img.at<Vec3b>(n, o)[0] = static_cast<unsigned char>(f / cal_max*255.0f);
								img.at<Vec3b>(n, o)[1] = static_cast<unsigned char>(f / cal_max*255.0f);
								img.at<Vec3b>(n, o)[2] = static_cast<unsigned char>(f / cal_max*255.0f);
							}
						}

						cout << "Writing " << dim[1] << "x" << dim[2] << " file " << file_name.c_str() << endl;
						imwrite(file_name.c_str(), img);
					}
				}
			}
		}
	}

	return 0;
}