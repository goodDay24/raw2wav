#include <stdint.h>

#define WAVE_FORMAT_PCM 1

typedef struct WAVHEADER_t {
// идентификатор формата файла
	char	riff[4];
// общий размер файла
	//long	
	int32_t filesize;
// тип данных riff
	char	rifftype[4];
// идентификатор блока описания формата
	char	chunk_id1[4];
// размер блока описания формата
	//long
	int32_t chunksize1;
// идентификатор формата данных
	//short	
	int16_t wFormatTag;
// число каналов
	//short
	int16_t	nChannels;
// число сэмплов в секунду
	//long
	int32_t	nSamplesPerSec;
// среднее число байт/сек
	//long
	int32_t	nAvgBytesPerSec;
// размер одного блока (число каналов)*(число байтов на канал)
	//short	
	int16_t	nBlockAlign;
// число битов на один сэмпл
	//short	
	int16_t	wBitsPerSample;
// идентификатор области аудиоданных
	char	chunk_id2[4];
// длина области аудиоданных
	//long	
	int32_t chunksize2;
} WAVHEADER_t;

void fillheader(WAVHEADER_t *header, short channels, long
    samplerate, short databits, long rawsize)
{
	memcpy(header->riff, (const void *)"RIFF", 4);
	memcpy(header->rifftype, (const void *)"WAVE", 4);
	memcpy(header->chunk_id1, (const void *)"fmt ", 4);
	header->chunksize1 = 16;
	header->wFormatTag = WAVE_FORMAT_PCM;
	memcpy(header->chunk_id2, (const void *)"data", 4);
	header->nChannels = channels;
	header->nSamplesPerSec = samplerate;
	header->nBlockAlign = databits * channels / 8;
	header->nAvgBytesPerSec = samplerate * header->nBlockAlign;
	header->wBitsPerSample = databits;
	header->chunksize2 = rawsize;
	header->filesize = header->chunksize2 + 44;
}
