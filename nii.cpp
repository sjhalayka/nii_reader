#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int main(void)
{
	// https://brainder.org/2012/09/23/the-nifti-file-format/
	ifstream infile("example_func.nii", std::ios::binary);

	if (infile.fail())
	{
		cout << "Could not read file example_func.nii" << endl;
		return 0;
	}

	cout << "Reading header" << endl;

	int sizeof_header;
	infile.read(reinterpret_cast<char*>(&sizeof_header), sizeof(sizeof_header));

	char data_type[10];
	infile.read(reinterpret_cast<char*>(&data_type), sizeof(data_type));

	char db_name[18];
	infile.read(reinterpret_cast<char*>(&db_name), sizeof(db_name));

	int extents;
	infile.read(reinterpret_cast<char*>(&extents), sizeof(extents));

	short session_error;
	infile.read(reinterpret_cast<char*>(&session_error), sizeof(session_error));

	char regular;
	infile.read(reinterpret_cast<char*>(&regular), sizeof(regular));

	char dim_info;
	infile.read(reinterpret_cast<char*>(&dim_info), sizeof(dim_info));

	short dim[8];
	infile.read(reinterpret_cast<char*>(&dim), sizeof(dim));

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

	float intent_p2;
	infile.read(reinterpret_cast<char*>(&intent_p2), sizeof(intent_p2));

	float intent_p3;
	infile.read(reinterpret_cast<char*>(&intent_p3), sizeof(intent_p3));

	short intent_code;
	infile.read(reinterpret_cast<char*>(&intent_code), sizeof(intent_code));

	short datatype;
	infile.read(reinterpret_cast<char*>(&datatype), sizeof(datatype));

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

	float pixdim[8];
	infile.read(reinterpret_cast<char*>(&pixdim), sizeof(pixdim));

	float vox_offset;
	infile.read(reinterpret_cast<char*>(&vox_offset), sizeof(vox_offset));

	float scl_slope;
	infile.read(reinterpret_cast<char*>(&scl_slope), sizeof(scl_slope));

	float scl_inter;
	infile.read(reinterpret_cast<char*>(&scl_inter), sizeof(scl_inter));

	short slice_end;
	infile.read(reinterpret_cast<char*>(&slice_end), sizeof(slice_end));

	char slice_code;
	infile.read(reinterpret_cast<char*>(&slice_code), sizeof(slice_code));

	char xyzt_units;
	infile.read(reinterpret_cast<char*>(&xyzt_units), sizeof(xyzt_units));

	float cal_max;
	infile.read(reinterpret_cast<char*>(&cal_max), sizeof(cal_max));

	float cal_min;
	infile.read(reinterpret_cast<char*>(&cal_min), sizeof(cal_min));

	float slice_duration;
	infile.read(reinterpret_cast<char*>(&slice_duration), sizeof(slice_duration));

	float toffset;
	infile.read(reinterpret_cast<char*>(&toffset), sizeof(toffset));

	int glmax;
	infile.read(reinterpret_cast<char*>(&glmax), sizeof(glmax));

	int glmin;
	infile.read(reinterpret_cast<char*>(&glmin), sizeof(glmin));

	char descrip[80];
	infile.read(reinterpret_cast<char*>(&descrip), sizeof(descrip));

	char aux_file[24];
	infile.read(reinterpret_cast<char*>(&aux_file), sizeof(aux_file));

	short qform_code;
	infile.read(reinterpret_cast<char*>(&qform_code), sizeof(qform_code));

	short sform_code;
	infile.read(reinterpret_cast<char*>(&sform_code), sizeof(sform_code));

	float quatern_b;
	infile.read(reinterpret_cast<char*>(&quatern_b), sizeof(quatern_b));

	float quatern_c;
	infile.read(reinterpret_cast<char*>(&quatern_c), sizeof(quatern_c));

	float quatern_d;
	infile.read(reinterpret_cast<char*>(&quatern_d), sizeof(quatern_d));

	float qoffset_x;
	infile.read(reinterpret_cast<char*>(&qoffset_x), sizeof(qoffset_x));

	float qoffset_y;
	infile.read(reinterpret_cast<char*>(&qoffset_y), sizeof(qoffset_y));

	float qoffset_z;
	infile.read(reinterpret_cast<char*>(&qoffset_z), sizeof(qoffset_z));

	float srow_x[4];
	infile.read(reinterpret_cast<char*>(&srow_x), sizeof(srow_x));

	float srow_y[4];
	infile.read(reinterpret_cast<char*>(&srow_y), sizeof(srow_y));

	float srow_z[4];
	infile.read(reinterpret_cast<char*>(&srow_z), sizeof(srow_z));

	char intent_name[16];
	infile.read(reinterpret_cast<char*>(&intent_name), sizeof(intent_name));

	char magic[4];
	infile.read(reinterpret_cast<char*>(&magic), sizeof(magic));

	long unsigned int num_voxels = dim[1] * dim[2] * dim[3] * dim[4] * dim[5] * dim[6] * dim[7];
	cout << "Reading " << num_voxels << " voxels" << endl;

	vector<float> data(num_voxels, 0);
	infile.read(reinterpret_cast<char*>(&data[0]), sizeof(float)*num_voxels);








	return 0;
}