#ifndef __LIBPITCH_SHIFT_SAMPLEBUFFER_H__
#define __LIBPITCH_SHIFT_SAMPLEBUFFER_H__
#include "Define.h"
#include "SamplePipe.h"

namespace e
{
	class SampleBuffer : public SamplePipe
	{
	public:
		SampleBuffer(uint channels = 2);
		virtual ~SampleBuffer(void);
		void SetChannels(uint channels);
		uint GetChannels(void) const;
		virtual void PutSamples(uint samples);
		virtual void PutSamples(const sample_t* samples, uint count);
		virtual uint GetSampleCount(void) const;
		virtual uint FetchSamples(uint count);
		virtual uint FetchSamples(sample_t* samples, uint count);
		virtual uint AdjustSampleCount(uint count);
		virtual sample_t* Begin(void);
		virtual sample_t* End(uint slackCapacity);
		virtual bool IsEmpty(void) const;
		virtual void Clear(void);
	private:
		void Rewind(void);
		void Capacity(uint capacity);
		uint GetCapacity(void) const;
	private:
		sample_t* buffer[2];
		uint sizeInBytes;
		uint sampleInBuffer;
		uint channels;
		uint offset;
	};
}

#endif