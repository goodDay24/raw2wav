#include <stdint.h>

#define WAVE_FORMAT_PCM 1

typedef struct WAVHEADER_t {
// ������������� ������� �����
	char	riff[4];
// ����� ������ �����
	//long	
	int32_t filesize;
// ��� ������ riff
	char	rifftype[4];
// ������������� ����� �������� �������
	char	chunk_id1[4];
// ������ ����� �������� �������
	//long
	int32_t chunksize1;
// ������������� ������� ������
	//short	
	int16_t wFormatTag;
// ����� �������
	//short
	int16_t	nChannels;
// ����� ������� � �������
	//long
	int32_t	nSamplesPerSec;
// ������� ����� ����/���
	//long
	int32_t	nAvgBytesPerSec;
// ������ ������ ����� (����� �������)*(����� ������ �� �����)
	//short	
	int16_t	nBlockAlign;
// ����� ����� �� ���� �����
	//short	
	int16_t	wBitsPerSample;
// ������������� ������� �����������
	char	chunk_id2[4];
// ����� ������� �����������
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
