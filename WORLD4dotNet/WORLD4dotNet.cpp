// これは メイン DLL ファイルです。

#include "stdafx.h"

#include "WORLD4dotNet.h"
#include <memory.h>
#include <malloc.h>

// 2D-arrays idea is here
// http://stackoverflow.com/a/26717663

void WORLD4dotNet::WORLD::CheapTrick(array<Double>^ x, int x_length, int fs, array<Double>^ time_axis, array<Double>^ f0, int f0_length, array<Byte>^ option, array<Double, 2>^ spectrogram)
{
	pin_ptr<Double> ptr_x = &x[0];
	pin_ptr<Double> ptr_f0 = &f0[0];
	pin_ptr<Double> ptr_time_axis = &time_axis[0];
	pin_ptr<Double> ptr_spectrogram = &spectrogram[0, 0];
	CheapTrickOption tmpOption;
	pin_ptr<Byte> ptr_option = &option[0];

	memcpy(&tmpOption, ptr_option, sizeof(CheapTrickOption));
	
	// Cast to 2D-array
	int dimOuter = spectrogram->GetLength(0);
	int dimInner = spectrogram->GetLength(1);
	double **ptr_spec = (double**)alloca(sizeof(double*) * dimOuter);
	double *tmpPtr = ptr_spectrogram;

	for (int i = 0; i < dimOuter; i++) {
		ptr_spec[i] = tmpPtr;
		tmpPtr += dimInner;
	}
	
	::CheapTrick(ptr_x, x_length, fs, ptr_time_axis, ptr_f0, f0_length, &tmpOption, ptr_spec);

	ptr_x = nullptr;
	ptr_f0 = nullptr;
	ptr_time_axis = nullptr;
	ptr_spectrogram = nullptr;
	ptr_option = nullptr;
}

void WORLD4dotNet::WORLD::InitializeCheapTrickOption(array<Byte>^ option)
{
	CheapTrickOption tmpOption;
	pin_ptr<Byte> ptr_option = &option[0];
	memcpy(&tmpOption, ptr_option, sizeof(CheapTrickOption));
	::InitializeCheapTrickOption(&tmpOption);
	memcpy(ptr_option, &tmpOption, sizeof(CheapTrickOption));
	ptr_option = nullptr;
}

int WORLD4dotNet::WORLD::GetFFTSizeForCheapTrick(int fs)
{
	return ::GetFFTSizeForCheapTrick(fs);
}

void WORLD4dotNet::WORLD::D4C(array<Double>^ x, int x_length, int fs, array<Double>^ time_axis, array<Double>^ f0, int f0_length, int fft_size, array<Byte>^ option, array<Double, 2>^ aperiodicity)
{
	pin_ptr<Double> ptr_x = &x[0];
	pin_ptr<Double> ptr_f0 = &f0[0];
	pin_ptr<Double> ptr_time_axis = &time_axis[0];
	pin_ptr<Double> ptr_aperiodicity = &aperiodicity[0, 0];
	D4COption* tmpOption;
	pin_ptr<Byte> ptr_option = &option[0];

	memcpy(&tmpOption, ptr_option, sizeof(D4COption));

	// Cast to 2D-array
	int dimOuter = aperiodicity->GetLength(0);
	int dimInner = aperiodicity->GetLength(1);
	double **ptr_aperi = (double**)alloca(sizeof(double*) * dimOuter);
	double *tmpPtr = ptr_aperiodicity;

	for (int i = 0; i < dimOuter; i++) {
		ptr_aperi[i] = tmpPtr;
		tmpPtr += dimInner;
	}

	::D4C(ptr_x, x_length, fs, ptr_time_axis, ptr_f0, f0_length, fft_size, tmpOption, ptr_aperi);

	ptr_x = nullptr;
	ptr_f0 = nullptr;
	ptr_time_axis = nullptr;
	ptr_aperiodicity = nullptr;
	ptr_option = nullptr;
}

void WORLD4dotNet::WORLD::InitializeD4COption(array<Byte>^ option)
{
	D4COption tmpOption;
	pin_ptr<Byte> ptr_option = &option[0];
	memcpy(&tmpOption, ptr_option, sizeof(D4COption));
	::InitializeD4COption(&tmpOption);
	memcpy(ptr_option, &tmpOption, sizeof(D4COption));
	ptr_option = nullptr;
}

void WORLD4dotNet::WORLD::Dio(array<Double>^ x, int x_length, int fs, array<Byte>^ option, array<Double>^ time_axis, array<Double>^ f0)
{
	pin_ptr<Double> ptr_x = &x[0];
	pin_ptr<Double> ptr_time_axis = &time_axis[0];
	pin_ptr<Double> ptr_f0 = &f0[0];

	DioOption tmpOption;
	pin_ptr<Byte> ptr_option = &option[0];
	memcpy(&tmpOption, ptr_option, sizeof(DioOption));

	::Dio(ptr_x, x_length, fs, tmpOption, ptr_time_axis, ptr_f0);

	ptr_x = nullptr;
	ptr_time_axis = nullptr;
	ptr_f0 = nullptr;
	ptr_option = nullptr;
}

void WORLD4dotNet::WORLD::InitializeDioOption(array<Byte>^ option)
{
	DioOption tmpOption;
	pin_ptr<Byte> ptr_option = &option[0];
	memcpy(&tmpOption, ptr_option, sizeof(DioOption));
	::InitializeDioOption(&tmpOption);
	memcpy(ptr_option, &tmpOption, sizeof(DioOption));
	ptr_option = nullptr;
}

int WORLD4dotNet::WORLD::GetSamplesForDIO(int fs, int x_length, double frame_period)
{
	return ::GetSamplesForDIO(fs, x_length, frame_period);
}

void WORLD4dotNet::WORLD::StoneMask(array<Double>^ x, int x_length, int fs, array<Double>^ time_axis, array<Double>^ f0, int f0_length, array<Double>^ refined_f0)
{
	pin_ptr<Double> ptr_x = &x[0];
	pin_ptr<Double> ptr_f0 = &f0[0];
	pin_ptr<Double> ptr_time_axis = &time_axis[0];
	pin_ptr<Double> ptr_refined_f0 = &refined_f0[0];
	::StoneMask(ptr_x, x_length, fs, ptr_time_axis, ptr_f0, f0_length, ptr_refined_f0);
	ptr_x = nullptr;
	ptr_f0 = nullptr;
	ptr_time_axis = nullptr;
	ptr_refined_f0 = nullptr;
}

void WORLD4dotNet::WORLD::Synthesis(array<Double>^ f0, int f0_length, array<Double, 2>^ spectrogram, array<Double, 2>^ aperiodicity, int fft_size, double frame_period, int fs, int y_length, array<Double>^ y)
{
	pin_ptr<Double> ptr_f0 = &f0[0];
	pin_ptr<Double> ptr_y = &y[0];
	pin_ptr<Double> ptr_spectrogram = &spectrogram[0, 0];
	pin_ptr<Double> ptr_aperiodicity = &aperiodicity[0, 0];

	// Cast to 2D-array
	int dimSpecOuter = spectrogram->GetLength(0);
	int dimSpecInner = spectrogram->GetLength(1);
	int dimAperiOuter = aperiodicity->GetLength(0);
	int dimAperiInner = aperiodicity->GetLength(1);
	double **ptr_spec = (double**)alloca(sizeof(double*) * dimSpecOuter);
	double **ptr_aperi = (double**)alloca(sizeof(double*) * dimSpecOuter);
	double *tmpPtr = ptr_spectrogram;

	for (int i = 0; i < dimSpecOuter; i++) {
		ptr_spec[i] = tmpPtr;
		tmpPtr += dimSpecInner;
	}
	tmpPtr = ptr_aperiodicity;
	for (int i = 0; i < dimAperiOuter; i++) {
		ptr_aperi[i] = tmpPtr;
		tmpPtr += dimAperiInner;
	}

	::Synthesis(ptr_f0, f0_length, ptr_spec, ptr_aperi, fft_size, frame_period, fs, y_length, ptr_y);
	ptr_f0 = nullptr;
	ptr_y = nullptr;
	ptr_spectrogram = nullptr;
	ptr_aperiodicity = nullptr;
}

void WORLD4dotNet::WORLD::WavRead(String ^ filename, int % fs, int % nbit, int % wav_length, array<Double>^% wav_form)
{
	pin_ptr<int> ptr_fs = &fs;
	pin_ptr<int> ptr_nbit = &nbit;
	pin_ptr<int> ptr_wav_length = &wav_length;

	char* ptr_filename = (char*)Marshal::StringToHGlobalAnsi(filename).ToPointer();

	double* tmp_wav_form = ::wavread(ptr_filename, ptr_fs, ptr_nbit, ptr_wav_length);
	wav_form = gcnew array<Double>(wav_length);
	pin_ptr<Double> ptr_wav_form = &wav_form[0];
	memcpy(ptr_wav_form, tmp_wav_form, sizeof(double) * wav_length);
	Marshal::FreeHGlobal(IntPtr(ptr_filename));
	delete tmp_wav_form;
	ptr_fs = nullptr;
	ptr_nbit = nullptr;
	ptr_wav_length = nullptr;
}

void WORLD4dotNet::WORLD::WavWrite(array<double>^ x, int x_length, int fs, int nbit, String ^ filename)
{
	pin_ptr<Double> ptr_x = &x[0];
	char* ptr_filename = (char*)Marshal::StringToHGlobalAnsi(filename).ToPointer();
	::wavwrite(ptr_x, x_length, fs, nbit, ptr_filename);
	Marshal::FreeHGlobal(IntPtr(ptr_filename));
	ptr_x = nullptr;
}
