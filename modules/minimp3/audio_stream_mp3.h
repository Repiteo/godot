/**************************************************************************/
/*  audio_stream_mp3.h                                                    */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#ifndef AUDIO_STREAM_MP3_H
#define AUDIO_STREAM_MP3_H

#include "core/io/resource_loader.h"
#include "servers/audio/audio_stream.h"

#include <minimp3_ex.h>

class AudioStreamMP3;

class AudioStreamPlaybackMP3 : public AudioStreamPlaybackResampled {
	GDCLASS(AudioStreamPlaybackMP3, AudioStreamPlaybackResampled);

	enum {
		FADE_SIZE = 256
	};
	AudioFrame loop_fade[FADE_SIZE];
	int loop_fade_remaining = FADE_SIZE;

	bool looping_override = false;
	bool looping = false;
	mp3dec_ex_t *mp3d = nullptr;
	uint32_t frames_mixed = 0;
	bool active = false;
	int loops = 0;

	friend class AudioStreamMP3;

	Ref<AudioStreamMP3> mp3_stream;

	bool _is_sample = false;
	Ref<AudioSamplePlayback> sample_playback;

protected:
	int _mix_internal(AudioFrame *p_buffer, int p_frames) override;
	float get_stream_sampling_rate() override;

public:
	void start(double p_from_pos = 0.0) override;
	void stop() override;
	bool is_playing() const override;

	int get_loop_count() const override; //times it looped

	double get_playback_position() const override;
	void seek(double p_time) override;

	void tag_used_streams() override;

	void set_is_sample(bool p_is_sample) override;
	bool get_is_sample() const override;
	Ref<AudioSamplePlayback> get_sample_playback() const override;
	void set_sample_playback(const Ref<AudioSamplePlayback> &p_playback) override;

	void set_parameter(const StringName &p_name, const Variant &p_value) override;
	Variant get_parameter(const StringName &p_name) const override;

	AudioStreamPlaybackMP3() {}
	~AudioStreamPlaybackMP3() override;
};

class AudioStreamMP3 : public AudioStream {
	GDCLASS(AudioStreamMP3, AudioStream);
	OBJ_SAVE_TYPE(AudioStream) //children are all saved as AudioStream, so they can be exchanged
	RES_BASE_EXTENSION("mp3str");

	friend class AudioStreamPlaybackMP3;

	PackedByteArray data;
	uint32_t data_len = 0;

	float sample_rate = 1.0;
	int channels = 1;
	float length = 0.0;
	bool loop = false;
	float loop_offset = 0.0;
	void clear_data();

	double bpm = 0;
	int beat_count = 0;
	int bar_beats = 4;

protected:
	static void _bind_methods();

public:
	void set_loop(bool p_enable);
	bool has_loop() const override;

	void set_loop_offset(double p_seconds);
	double get_loop_offset() const;

	void set_bpm(double p_bpm);
	double get_bpm() const override;

	void set_beat_count(int p_beat_count);
	int get_beat_count() const override;

	void set_bar_beats(int p_bar_beats);
	int get_bar_beats() const override;

	Ref<AudioStreamPlayback> instantiate_playback() override;
	String get_stream_name() const override;

	void set_data(const Vector<uint8_t> &p_data);
	Vector<uint8_t> get_data() const;

	double get_length() const override;

	bool is_monophonic() const override;

	bool can_be_sampled() const override {
		return true;
	}
	Ref<AudioSample> generate_sample() const override;

	void get_parameter_list(List<Parameter> *r_parameters) override;

	AudioStreamMP3();
	~AudioStreamMP3() override;
};

#endif // AUDIO_STREAM_MP3_H
