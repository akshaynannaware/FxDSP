//
//  FtAudioFFT.h
//  Test
//
//  Created by Hamilton Kibbe on 5/27/13.
//
//

#ifndef FTAUDIOFFT_H
#define FTAUDIOFFT_H

#include "FtAudioError.h"
#ifdef __APPLE__
#include <Accelerate/Accelerate.h>
#endif


#ifdef __cplusplus
extern "C" {
#endif

typedef struct FtAudioFFTConfig FtAudioFFTConfig;

    
/** Create a new FtAudioFFTConfig
 *
 * @details Allocates memory and returns an initialized FtAudioFFTConfig,
 *			which is used to store the FFT Configuration. Play nice and call 
 *          FtAudioFFTFree on it when you're done.
 *
 * @param length        length of the FFT. should be a power of 2.
 * @return 				An initialized FtAudioFFTConfig.
 */
FtAudioFFTConfig*
FtAudioFFTInit(unsigned length);

    
/** Free memory associated with a FtAudioFFTConfig
 *
 * @details release all memory allocated by FtAudioFFTInit for the supplied
 *			fft configuration.
 *
 * @param fft       pointer to the FtAudioFFTConfig to free.
 * @return			Error code, 0 on success
 */
FtAudioError_t
FtAudioFFTFree(FtAudioFFTConfig* fft);

    
/** Calculate Real Forward FFT
 *
 * @details Calculates the magnitude and phase of the real forward FFT of the
 *          data in inBuffer.
 *
 * @param fft       Pointer to the FFT configuration.
 * @param inBuffer  Input data. should be the same size as the fft.
 * @param outMag    Allocated buffer where the magnitude will be written. length
 *                  should be (fft length / 2).
 * @param outPhase  Allocated buffer where the phase will be written. length 
 *                  should be (fft length / 2).
 * @return          Error code, 0 on success.
 */
FtAudioError_t
FtAudioFFTForward(FtAudioFFTConfig*     fft,
                  const float*          inBuffer,
                  float*                outMag,
                  float*                outPhase);

                  
/** Calculate Real Forward FFT
 *
 * @details Calculates the magnitude and phase of the real forward FFT of the
 *          data in inBuffer.
 *
 * @param fft       Pointer to the FFT configuration.
 * @param inBuffer  Input data. should be the same size as the fft.
 * @param out       Allocated buffer where the transform will be written. length
 *                  should be the same as the fft length
 * @return          Error code, 0 on success.
 */
FtAudioError_t
FtAudioFFTForwardInterleaved(FtAudioFFTConfig*     fft,
                             const float*          inBuffer,
                             float*                out);
                  
                  
             
/** Calculate Real Inverse FFT
 *
 * @details Calculates the real inverse FFT of the data in inMag and inPhase.        
 *
 * @param fft       Pointer to the FFT configuration.
 * @param inMag     FFT magnitude data. length should be (fft length / 2).
 * @param inPhase   FFT phase data. length should be (fft length / 2).
 * @param outBuffer Allocated buffer where the ifft will be written. length
 *                  should be the same as the fft size.
 * @return          Error code, 0 on success.
 */
FtAudioError_t
FtAudioFFTInverse(FtAudioFFTConfig*     fft,
                  const float*          inMag,
                  const float*          inPhase,
                  float*                outBuffer);


/** Calculate Real Inverse FFT
 *
 * @details Calculates the real inverse FFT of the data in inBuffer
 *
 * @param fft       Pointer to the FFT configuration.
 * @param inBuffer  interleaved real/imaginary input buffer. length same as fft.
 * @param outBuffer Allocated buffer where the ifft will be written. length
 *                  should be the same as the fft size.
 * @return          Error code, 0 on success.
 */
FtAudioError_t
FtAudioFFTInverseInterleaved(FtAudioFFTConfig*     fft,
                             const float*          inBuffer,
                              float*                outBuffer);

/** Perform Convolution using FFT*
 * @details convolve in1 with in2 and write results to dest
 * @param in1           First input to convolve.
 * @param in1_length    Length [samples] of in1.
 * @param in2           Second input to convolve.
 * @param in2_length    Length[samples] of second input.
 * @param dest          Output buffer. needs to be of length 
 *                      in1_length + in2_length - 1
 * @return              Error code.
 */
FtAudioError_t
FtAudioFFTConvolve(FtAudioFFTConfig* fft,
                    float       *in1, 
                   unsigned    in1_length, 
                   float       *in2, 
                   unsigned    in2_length, 
                   float       *dest);

                   
/** Perform Convolution using FFT*
 * @details Convolve in1 with IFFT(in2) and write results to dest.
 *          This takes an already transformed kernel as the second argument, to
 *          be used in an TI filter, where the FFT of the kernel can be pre-
 *          calculated.
 * @param in1           First input to convolve.
 * @param in1_length    Length [samples] of in1.
 * @param in2           Second input to convolve (Already FFT'ed).
 * @param in2_length    Length[samples] of second input.
 * @param dest          Output buffer. needs to be of length 
 *                      in1_length + in2_length - 1
 * @return              Error code.
 */
FtAudioError_t
FtAudioFFTFilterConvolve(FtAudioFFTConfig* fft,
`                          float       *in1, 
                         unsigned    in1_length, 
                         float       *in2, 
                         unsigned    in2_length, 
                         float       *dest);


    
#ifdef __cplusplus
}
#endif

#endif  // FTAUDIOFFT_H
