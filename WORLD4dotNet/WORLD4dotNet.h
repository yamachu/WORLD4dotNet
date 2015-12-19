// WORLD4dotNet.h

#pragma once
#include "WORLD\cheaptrick.h"
#include "WORLD\d4c.h"
#include "WORLD\dio.h"
#include "WORLD\stonemask.h"
#include "WORLD\synthesis.h"
#include "WORLD\matlabfunctions.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace WORLD4dotNet {

	public ref class WORLD
	{
		// TODO: このクラスの、ユーザーのメソッドをここに追加してください。
	public:
		// CheapTrick
		static void CheapTrick(array<Double> ^x, int x_length, int fs, array<Double> ^time_axis, array<Double> ^f0,
			int f0_length, array<Byte> ^option, array<Double, 2> ^spectrogram);
		static void InitializeCheapTrickOption(array<Byte> ^option);
		static int GetFFTSizeForCheapTrick(int fs);

		// D4C
		static void D4C(array<Double> ^x, int x_length, int fs, array<Double> ^time_axis, array<Double> ^f0,
			int f0_length, int fft_size, array<Byte> ^option, array<Double, 2> ^aperiodicity);
		static void InitializeD4COption(array<Byte> ^option);

		// DIO
		static void Dio(array<Double> ^x, int x_length, int fs, array<Byte> ^option,
			array<Double> ^time_axis, array<Double> ^f0);
		static void InitializeDioOption(array<Byte> ^option);
		static int GetSamplesForDIO(int fs, int x_length, double frame_period);

		// StoneMask
		static void StoneMask(array<Double> ^x, int x_length, int fs, array<Double> ^time_axis, array<Double> ^f0,
			int f0_length, array<Double> ^refined_f0);

		// Synthesis
		static void Synthesis(array<Double> ^f0, int f0_length, array<Double, 2> ^spectrogram,
			array<Double, 2> ^aperiodicity, int fft_size, double frame_period, int fs,
			int y_length, array<Double> ^y);

		// matlabfunction
		static void WavRead(String^ filename, int %fs, int %nbit, int %wav_length, 
			[System::Runtime::InteropServices::OutAttribute]array<Double> ^%wav_form);
		static void WavWrite(array<double> ^x, int x_length, int fs, int nbit, String ^filename);

	};
}
