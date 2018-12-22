
#include <iostream>
#include <vector>
#include <cstring> //http://cs.stmarys.ca/~porter/csc/ref/c_cpp_strings.html
#include <string>
#include <atomic>
#define _SVID_SOURCE
// FFmpeg
#define 	MAX_MMCO_COUNT   66
#define SUINT unsigned
#define AVERROR_PS_NOT_FOUND      FFERRTAG(0xF8,'?','P','S')

extern "C" {

#include <libavutil/motion_vector.h>
// #include "../include/libavutil/motion_vector.h"
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavcodec/avcodec.h>
#include <libavutil/avutil.h>
#include <libavutil/pixdesc.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
#include <libavutil/time.h>
 #include <libavcodec/avcodec.h>
#include <libavcodec/get_bits.h>

#include <libavcodec/h264_ps.h>
#include <libavcodec/h264_sei.h>
#include <libavcodec/internal.h>


#include "config.h"
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

#include <stdint.h>
#include <pthread.h>

#define AVERROR_PS_NOT_FOUND      FFERRTAG(0xF8,'?','P','S')
#if HAVE_IO_H
#include <io.h>
#endif
#if HAVE_UNISTD_H
#include <unistd.h>
#endif

#include "libavformat/avformat.h"
#include "libavdevice/avdevice.h"
#include "libswresample/swresample.h"
#include "libavutil/opt.h"
#include "libavutil/channel_layout.h"
#include "libavutil/parseutils.h"
#include "libavutil/samplefmt.h"
#include "libavutil/fifo.h"
#include "libavutil/hwcontext.h"
#include "libavutil/internal.h"
#include "libavutil/intreadwrite.h"
#include "libavutil/dict.h"
#include "libavutil/display.h"
#include "libavutil/mathematics.h"
#include "libavutil/pixdesc.h"
#include "libavutil/avstring.h"
#include "libavutil/libm.h"
#include "libavutil/imgutils.h"
#include "libavutil/timestamp.h"
#include "libavutil/bprint.h"
#include "libavutil/time.h"
#include "libavutil/thread.h"
#include "libavutil/threadmessage.h"
#include "libavcodec/mathops.h"
#include "libavformat/os_support.h"

# include "libavfilter/avfilter.h"
# include "libavfilter/buffersrc.h"
# include "libavfilter/buffersink.h"

#if HAVE_SYS_RESOURCE_H
#include <sys/time.h>
#include <sys/types.h>
#include <sys/resource.h>
#elif HAVE_GETPROCESSTIMES
#include <windows.h>
#endif
#if HAVE_GETPROCESSMEMORYINFO
#include <windows.h>
#include <psapi.h>
#endif
#if HAVE_SETCONSOLECTRLHANDLER
#include <windows.h>
#endif


#if HAVE_SYS_SELECT_H
#include <sys/select.h>
#endif

#if HAVE_TERMIOS_H
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <termios.h>
#elif HAVE_KBHIT
#include <conio.h>
#endif

#include <time.h>

 // #include "libavcodec/h264_parser.c"

#include "libavutil/avassert.h"
#include "libavcodec/h264.h"
#include "libavcodec/h264_parse.h"
#include "libavcodec/h264_sei.h"
#include "libavcodec/h264_ps.h"
#include "libavcodec/parser.h"
#include "libavcodec/h264dsp.h"
#include "libavcodec/h2645_parse.h"
#include "libavcodec/golomb.h"
#include "libavcodec/get_bits.h"




}
#define PICT_TOP_FIELD     1
#define PICT_BOTTOM_FIELD  2
#define PICT_FRAME         3
const uint8_t ff_h264_golomb_to_pict_type[5] = {
    AV_PICTURE_TYPE_P, AV_PICTURE_TYPE_B, AV_PICTURE_TYPE_I,
    AV_PICTURE_TYPE_SP, AV_PICTURE_TYPE_SI
};
// OpenCV
#include <opencv2/opencv.hpp>
#include </usr/include/boost/python.hpp>

using namespace std;
using namespace cv;

class FMV{
private:

typedef struct H264ParseContext {
    ParseContext pc;
    H264ParamSets ps;
    H264DSPContext h264dsp;
    H264POCContext poc;
    H264SEIContext sei;
    int is_avc;
    int nal_length_size;
    int got_first;
    int picture_structure;
    uint8_t parse_history[6];
    int parse_history_count;
    int parse_last_mb;
    int64_t reference_dts;
    int last_frame_num, last_picture_structure;
} H264ParseContext;
enum  	MMCOOpcode {
  MMCO_END = 0, MMCO_SHORT2UNUSED, MMCO_LONG2UNUSED, MMCO_SHORT2LONG,
  MMCO_SET_MAX_LONG, MMCO_RESET, MMCO_LONG
};
AVFormatContext   *pFormatCtx = NULL;
// static AVCodecContext *video_dec_ctx = NULL;
AVStream          *video_stream = NULL;
AVCodecParserContext *avparserctx=NULL;
const char        *src_filename = NULL;
AVCodecContext    *pCodecCtxOrig = NULL;
AVCodecContext    *pCodecCtx = NULL;
AVCodec           *pCodec = NULL;

int               video_stream_idx = -1;
AVFrame           *pFrame = NULL;
AVFrame           *pFrameRGB = NULL;
AVPacket          *pkt=NULL;
enum              AVMediaType type;
int               video_frame_count = 0;
int               frameFinished;
int               numBytes;
uint8_t           *buffer = NULL;
struct SwsContext *sws_ctx = NULL;
int               argc;
bool              gotFrame;
int               fps;
std::string       str;
char              temp_str[10];
std::string FINALNAL;

// compatibility with newer API
#if LIBAVCODEC_VERSION_INT < AV_VERSION_INT(55,28,1)
#define av_frame_alloc avcodec_alloc_frame
#define av_frame_free avcodec_free_frame
#endif

public:
FMV(int argc, char* videopath){
  // cout<<"line 50: FMV constructor called\n";
  this->argc = argc;
  this->src_filename=videopath;
};

Mat               cv_mat;

const char* getSrcFilename(){
  return this->src_filename;
}

void setFrameFlag(bool flag){
  this->gotFrame=flag;
}

bool getFrameFlag(){
  return this->gotFrame;
}

Mat getMAT(){
  return this->cv_mat;
}
//std::string getMV(){
  //return this->str;
//}


std::string getPacketData(){
  return this->str;
}
std::string getSEI(){
  return this->FINALNAL;
}
// int ff_h264_decode_extradata(H264Context *h, const uint8_t *buf, int size)
//    {
//        AVCodecContext *avctx = h->avctx;
//        int ret;
//
//        if (!buf || size <= 0)
//            return -1;
//
//        if (buf[0] == 1) {
//            int i, cnt, nalsize;
//            const unsigned char *p = buf;
//
//            h->is_avc = 1;
//
//            if (size < 7) {
//                av_log(avctx, AV_LOG_ERROR,
//                       "avcC %d too short\n", size);
//                return AVERROR_INVALIDDATA;
//            }
//            /* sps and pps in the avcC always have length coded with 2 bytes,
//             * so put a fake nal_length_size = 2 while parsing them */
//            h->nal_length_size = 2;
//            // Decode sps from avcC
//            cnt = *(p + 5) & 0x1f; // Number of sps
//            p  += 6;
//            for (i = 0; i < cnt; i++) {
//                nalsize = AV_RB16(p) + 2;
//                if(nalsize > size - (p-buf))
//                    return AVERROR_INVALIDDATA;
//                ret = decode_nal_units(h, p, nalsize, 1);
//                if (ret < 0) {
//                    av_log(avctx, AV_LOG_ERROR,
//                           "Decoding sps %d from avcC failed\n", i);
//                    return ret;
//                }
//                p += nalsize;
//            }
//            // Decode pps from avcC
//            cnt = *(p++); // Number of pps
//            for (i = 0; i < cnt; i++) {
//                nalsize = AV_RB16(p) + 2;
//                if(nalsize > size - (p-buf))
//                    return AVERROR_INVALIDDATA;
//                ret = decode_nal_units(h, p, nalsize, 1);
//                if (ret < 0) {
//                    av_log(avctx, AV_LOG_ERROR,
//                           "Decoding pps %d from avcC failed\n", i);
//                    return ret;
//                }
//                p += nalsize;
//            }
//            // Store right nal length size that will be used to parse all other nals
//            h->nal_length_size = (buf[4] & 0x03) + 1;
//        } else {
//            h->is_avc = 0;
//            ret = decode_nal_units(h, buf, size, 1);
//            if (ret < 0)
//                return ret;
//        }
//        return size;
//    }

 int scan_mmco_reset(AVCodecParserContext *s, GetBitContext *gb,
                           void *logctx)
{
    H264PredWeightTable pwt;
    int slice_type_nos = s->pict_type & 3;
    H264ParseContext *p =(H264ParseContext*) s->priv_data;
    int list_count, ref_count[2];


    if (p->ps.pps->redundant_pic_cnt_present)
        get_ue_golomb(gb); // redundant_pic_count

    if (slice_type_nos == AV_PICTURE_TYPE_B)
        get_bits1(gb); // direct_spatial_mv_pred

    if (ff_h264_parse_ref_count(&list_count, ref_count, gb, p->ps.pps,
                                slice_type_nos, p->picture_structure, logctx) < 0)
        return AVERROR_INVALIDDATA;

    if (slice_type_nos != AV_PICTURE_TYPE_I) {
        int list;
        for (list = 0; list < list_count; list++) {
            if (get_bits1(gb)) {
                int index;
                for (index = 0; ; index++) {
                    unsigned int reordering_of_pic_nums_idc = get_ue_golomb_31(gb);

                    if (reordering_of_pic_nums_idc < 3)
                        get_ue_golomb_long(gb);
                    else if (reordering_of_pic_nums_idc > 3) {
                        av_log(logctx, AV_LOG_ERROR,
                               "illegal reordering_of_pic_nums_idc %d\n",
                               reordering_of_pic_nums_idc);
                        return AVERROR_INVALIDDATA;
                    } else
                        break;

                    if (index >= ref_count[list]) {
                        av_log(logctx, AV_LOG_ERROR,
                               "reference count %d overflow\n", index);
                        return AVERROR_INVALIDDATA;
                    }
                }
            }
        }
    }

    if ((p->ps.pps->weighted_pred && slice_type_nos == AV_PICTURE_TYPE_P) ||
        (p->ps.pps->weighted_bipred_idc == 1 && slice_type_nos == AV_PICTURE_TYPE_B))
        ff_h264_pred_weight_table(gb, p->ps.sps, ref_count, slice_type_nos,
                                  &pwt, p->picture_structure, logctx);

    if (get_bits1(gb)) { // adaptive_ref_pic_marking_mode_flag
        int i;
        for (i = 0; i < MAX_MMCO_COUNT; i++) {
            MMCOOpcode opcode = (MMCOOpcode)get_ue_golomb_31(gb);
            if (opcode > (unsigned) MMCO_LONG) {
                av_log(logctx, AV_LOG_ERROR,
                       "illegal memory management control operation %d\n",
                       opcode);
                return AVERROR_INVALIDDATA;
            }
            if (opcode == MMCO_END)
               return 0;
            else if (opcode == MMCO_RESET)
                return 1;

            if (opcode == MMCO_SHORT2UNUSED || opcode == MMCO_SHORT2LONG)
                get_ue_golomb_long(gb); // difference_of_pic_nums_minus1
            if (opcode == MMCO_SHORT2LONG || opcode == MMCO_LONG2UNUSED ||
                opcode == MMCO_LONG || opcode == MMCO_SET_MAX_LONG)
                get_ue_golomb_31(gb);
        }
    }

    return 0;
}

 int find_start_code(const uint8_t *buf, int buf_size,
                             int buf_index, int next_avc)
  {
      uint32_t state = -1;

      buf_index = avpriv_find_start_code(buf + buf_index, buf + next_avc + 1, &state) - buf - 1;

      return FFMIN(buf_index, buf_size);
  }
 int h264_find_frame_end(H264ParseContext *p, const uint8_t *buf,
                               int buf_size, void *logctx)
{
    int i, j;
    uint32_t state;
    ParseContext *pc = &p->pc;

    int next_avc = p->is_avc ? 0 : buf_size;
//    mb_addr= pc->mb_addr - 1;
    state = pc->state;
    if (state > 13)
        state = 7;

    if (p->is_avc && !p->nal_length_size)
        av_log(logctx, AV_LOG_ERROR, "AVC-parser: nal length size invalid\n");

    for (i = 0; i < buf_size; i++) {
        if (i >= next_avc) {
            int nalsize = 0;
            i = next_avc;
            for (j = 0; j < p->nal_length_size; j++)
                nalsize = (nalsize << 8) | buf[i++];
            if (nalsize <= 0 || nalsize > buf_size - i) {
                av_log(logctx, AV_LOG_ERROR, "AVC-parser: nal size %d remaining %d\n", nalsize, buf_size - i);
                return buf_size;
            }
            next_avc = i + nalsize;
            state    = 5;
        }

        if (state == 7) {
            i += p->h264dsp.startcode_find_candidate(buf + i, next_avc - i);
            if (i < next_avc)
                state = 2;
        } else if (state <= 2) {
            if (buf[i] == 1)
                state ^= 5;            // 2->7, 1->4, 0->5
            else if (buf[i])
                state = 7;
            else
                state >>= 1;           // 2->1, 1->0, 0->0
        } else if (state <= 5) {
            int nalu_type = buf[i] & 0x1F;
            if (nalu_type == H264_NAL_SEI || nalu_type == H264_NAL_SPS ||
                nalu_type == H264_NAL_PPS || nalu_type == H264_NAL_AUD) {
                if (pc->frame_start_found) {
                    i++;
                    goto found;
                }
            } else if (nalu_type == H264_NAL_SLICE || nalu_type == H264_NAL_DPA ||
                       nalu_type == H264_NAL_IDR_SLICE) {
                state += 8;
                continue;
            }
            state = 7;
        } else {
            unsigned int mb, last_mb = p->parse_last_mb;
            GetBitContext gb;
            p->parse_history[p->parse_history_count++] = buf[i];

            init_get_bits(&gb, p->parse_history, 8*p->parse_history_count);
            mb= get_ue_golomb_long(&gb);
            if (get_bits_left(&gb) > 0 || p->parse_history_count > 5) {
                p->parse_last_mb = mb;
                if (pc->frame_start_found) {
                    if (mb <= last_mb) {
                        i -= p->parse_history_count - 1;
                        p->parse_history_count = 0;
                        goto found;
                    }
                } else
                    pc->frame_start_found = 1;
                p->parse_history_count = 0;
                state = 7;
            }
        }
    }
    pc->state = state;
    if (p->is_avc)
        return next_avc;
    return END_NOT_FOUND;

found:
    pc->state             = 7;
    pc->frame_start_found = 0;
    if (p->is_avc)
        return next_avc;
    return i - (state & 5);
}
int my_h264_parse(AVCodecParserContext *s,
                      AVCodecContext *avctx,
                      const uint8_t *buf, int buf_size)
{
    H264ParseContext *p = (H264ParseContext*)s->priv_data;
    ParseContext *pc = &p->pc;
    int next;

    if (!p->got_first) {
        p->got_first = 1;
        if (avctx->extradata_size) {
            ff_h264_decode_extradata(avctx->extradata, avctx->extradata_size,
                                     &p->ps, &p->is_avc, &p->nal_length_size,
                                     avctx->err_recognition, avctx);
        }
    }

    if (s->flags & PARSER_FLAG_COMPLETE_FRAMES) {
        next = buf_size;
    } else {
        next = h264_find_frame_end(p, buf, buf_size, avctx);

        if (ff_combine_frame(pc, next, &buf, &buf_size) < 0) {

            return buf_size;
        }

        if (next < 0 && next != END_NOT_FOUND) {
            av_assert1(pc->last_index + next >= 0);
            h264_find_frame_end(p, &pc->buffer[pc->last_index + next], -next, avctx); // update state
        }
    }

    my_parse_nal_units(s, avctx, buf, buf_size);

    if (avctx->framerate.num)
        avctx->time_base = av_inv_q(av_mul_q(avctx->framerate, (AVRational){avctx->ticks_per_frame, 1}));
    if (p->sei.picture_timing.cpb_removal_delay >= 0) {
        s->dts_sync_point    = p->sei.buffering_period.present;
        s->dts_ref_dts_delta = p->sei.picture_timing.cpb_removal_delay;
        s->pts_dts_delta     = p->sei.picture_timing.dpb_output_delay;
    } else {
        s->dts_sync_point    = INT_MIN;
        s->dts_ref_dts_delta = INT_MIN;
        s->pts_dts_delta     = INT_MIN;
    }

    if (s->flags & PARSER_FLAG_ONCE) {
        s->flags &= PARSER_FLAG_COMPLETE_FRAMES;
    }

    if (s->dts_sync_point >= 0) {
        int64_t den = avctx->time_base.den * (int64_t)avctx->pkt_timebase.num;
        if (den > 0) {
            int64_t num = avctx->time_base.num * (int64_t)avctx->pkt_timebase.den;
            if (s->dts != AV_NOPTS_VALUE) {
                // got DTS from the stream, update reference timestamp
                p->reference_dts = s->dts - av_rescale(s->dts_ref_dts_delta, num, den);
            } else if (p->reference_dts != AV_NOPTS_VALUE) {
                // compute DTS based on reference timestamp
                s->dts = p->reference_dts + av_rescale(s->dts_ref_dts_delta, num, den);
            }

            if (p->reference_dts != AV_NOPTS_VALUE && s->pts == AV_NOPTS_VALUE)
                s->pts = s->dts + av_rescale(s->pts_dts_delta, num, den);

            if (s->dts_sync_point > 0)
                p->reference_dts = s->dts; // new reference
        }
    }


    return next;
}

int my_parse_nal_units(AVCodecParserContext *s,
                                  AVCodecContext *avctx,
                                  const uint8_t * const buf, int buf_size)
{
    H264ParseContext *p = (H264ParseContext*)s->priv_data;
    H2645RBSP rbsp = { NULL };
    H2645NAL nal = { NULL };
    int buf_index, next_avc;
    unsigned int pps_id;
    unsigned int slice_type;
    int state = -1, got_reset = 0;
    int q264 = buf_size >=4 && !memcmp("Q264", buf, 4);
    int field_poc[2];
    int ret;

    /* set some sane default values */
    s->pict_type         = AV_PICTURE_TYPE_I;
    s->key_frame         = 0;
    s->picture_structure = AV_PICTURE_STRUCTURE_UNKNOWN;

    ff_h264_sei_uninit(&p->sei);
    p->sei.frame_packing.arrangement_cancel_flag = -1;

    if (!buf_size)
        return 0;

    av_fast_padded_malloc(&rbsp.rbsp_buffer,(unsigned int*) &rbsp.rbsp_buffer_alloc_size, buf_size);
    if (!rbsp.rbsp_buffer)
        return AVERROR(ENOMEM);

    buf_index     = 0;
    next_avc      = p->is_avc ? 0 : buf_size;
    for (;;) {
        const SPS *sps;
        int src_length, consumed, nalsize = 0;

        if (buf_index >= next_avc) {
            nalsize = get_nalsize(p->nal_length_size, buf, buf_size, &buf_index, avctx);
            if (nalsize < 0)
                break;
            next_avc = buf_index + nalsize;
        } else {
            buf_index = find_start_code(buf, buf_size, buf_index, next_avc);
            if (buf_index >= buf_size)
                break;
            if (buf_index >= next_avc)
                continue;
        }
        src_length = next_avc - buf_index;

        state = buf[buf_index];
        switch (state & 0x1f) {
        case H264_NAL_SLICE:
        case H264_NAL_IDR_SLICE:
            // Do not walk the whole buffer just to decode slice header
            if ((state & 0x1f) == H264_NAL_IDR_SLICE || ((state >> 5) & 0x3) == 0) {
                /* IDR or disposable slice
                 * No need to decode many bytes because MMCOs shall not be present. */
                if (src_length > 60)
                    src_length = 60;
            } else {
                /* To decode up to MMCOs */
                if (src_length > 1000)
                    src_length = 1000;
            }
            break;
        }
        consumed = ff_h2645_extract_rbsp(buf + buf_index, src_length, &rbsp, &nal, 1);
        if (consumed < 0)
            break;

        buf_index += consumed;

        ret = init_get_bits8(&nal.gb, nal.data, nal.size);
        if (ret < 0)
            goto fail;
        get_bits1(&nal.gb);
        nal.ref_idc = get_bits(&nal.gb, 2);
        nal.type    = get_bits(&nal.gb, 5);

        switch (nal.type) {
        case H264_NAL_SPS:
            ff_h264_decode_seq_parameter_set(&nal.gb, avctx, &p->ps, 0);
            break;
        case H264_NAL_PPS:
            ff_h264_decode_picture_parameter_set(&nal.gb, avctx, &p->ps,
                                                 nal.size_bits);
            break;
        case H264_NAL_SEI:
            my_ff_h264_sei_decode(&p->sei, &nal.gb, &p->ps, avctx);
            break;
        case H264_NAL_IDR_SLICE:
            s->key_frame = 1;

            p->poc.prev_frame_num        = 0;
            p->poc.prev_frame_num_offset = 0;
            p->poc.prev_poc_msb          =
            p->poc.prev_poc_lsb          = 0;
        /* fall through */
        case H264_NAL_SLICE:
            get_ue_golomb_long(&nal.gb);  // skip first_mb_in_slice
            slice_type   = get_ue_golomb_31(&nal.gb);
            s->pict_type = ff_h264_golomb_to_pict_type[slice_type % 5];
            if (p->sei.recovery_point.recovery_frame_cnt >= 0) {
                /* key frame, since recovery_frame_cnt is set */
                s->key_frame = 1;
            }
            pps_id = get_ue_golomb(&nal.gb);
            if (pps_id >= MAX_PPS_COUNT) {
                av_log(avctx, AV_LOG_ERROR,
                       "pps_id %u out of range\n", pps_id);
                goto fail;
            }
            if (!p->ps.pps_list[pps_id]) {
                av_log(avctx, AV_LOG_ERROR,
                       "non-existing PPS %u referenced\n", pps_id);
                goto fail;
            }

            av_buffer_unref(&p->ps.pps_ref);
            av_buffer_unref(&p->ps.sps_ref);
            p->ps.pps = NULL;
            p->ps.sps = NULL;
            p->ps.pps_ref = av_buffer_ref(p->ps.pps_list[pps_id]);
            if (!p->ps.pps_ref)
                goto fail;
            p->ps.pps = (const PPS*)p->ps.pps_ref->data;

            if (!p->ps.sps_list[p->ps.pps->sps_id]) {
                av_log(avctx, AV_LOG_ERROR,
                       "non-existing SPS %u referenced\n", p->ps.pps->sps_id);
                goto fail;
            }

            p->ps.sps_ref = av_buffer_ref(p->ps.sps_list[p->ps.pps->sps_id]);
            if (!p->ps.sps_ref)
                goto fail;
            p->ps.sps = (const SPS*)p->ps.sps_ref->data;

            sps = p->ps.sps;

            // heuristic to detect non marked keyframes
            if (p->ps.sps->ref_frame_count <= 1 && p->ps.pps->ref_count[0] <= 1 && s->pict_type == AV_PICTURE_TYPE_I)
                s->key_frame = 1;

            p->poc.frame_num = get_bits(&nal.gb, sps->log2_max_frame_num);

            s->coded_width  = 16 * sps->mb_width;
            s->coded_height = 16 * sps->mb_height;
            s->width        = s->coded_width  - (sps->crop_right + sps->crop_left);
            s->height       = s->coded_height - (sps->crop_top   + sps->crop_bottom);
            if (s->width <= 0 || s->height <= 0) {
                s->width  = s->coded_width;
                s->height = s->coded_height;
            }

            switch (sps->bit_depth_luma) {
            case 9:
                if (sps->chroma_format_idc == 3)      s->format = AV_PIX_FMT_YUV444P9;
                else if (sps->chroma_format_idc == 2) s->format = AV_PIX_FMT_YUV422P9;
                else                                  s->format = AV_PIX_FMT_YUV420P9;
                break;
            case 10:
                if (sps->chroma_format_idc == 3)      s->format = AV_PIX_FMT_YUV444P10;
                else if (sps->chroma_format_idc == 2) s->format = AV_PIX_FMT_YUV422P10;
                else                                  s->format = AV_PIX_FMT_YUV420P10;
                break;
            case 8:
                if (sps->chroma_format_idc == 3)      s->format = AV_PIX_FMT_YUV444P;
                else if (sps->chroma_format_idc == 2) s->format = AV_PIX_FMT_YUV422P;
                else                                  s->format = AV_PIX_FMT_YUV420P;
                break;
            default:
                s->format = AV_PIX_FMT_NONE;
            }

            avctx->profile = ff_h264_get_profile(sps);
            avctx->level   = sps->level_idc;

            if (sps->frame_mbs_only_flag) {
                p->picture_structure = PICT_FRAME;
            } else {
                if (get_bits1(&nal.gb)) { // field_pic_flag
                    p->picture_structure = PICT_TOP_FIELD + get_bits1(&nal.gb); // bottom_field_flag
                } else {
                    p->picture_structure = PICT_FRAME;
                }
            }

            if (nal.type == H264_NAL_IDR_SLICE)
                get_ue_golomb_long(&nal.gb); /* idr_pic_id */
            if (sps->poc_type == 0) {
                p->poc.poc_lsb = get_bits(&nal.gb, sps->log2_max_poc_lsb);

                if (p->ps.pps->pic_order_present == 1 &&
                    p->picture_structure == PICT_FRAME)
                    p->poc.delta_poc_bottom = get_se_golomb(&nal.gb);
            }

            if (sps->poc_type == 1 &&
                !sps->delta_pic_order_always_zero_flag) {
                p->poc.delta_poc[0] = get_se_golomb(&nal.gb);

                if (p->ps.pps->pic_order_present == 1 &&
                    p->picture_structure == PICT_FRAME)
                    p->poc.delta_poc[1] = get_se_golomb(&nal.gb);
            }

            /* Decode POC of this picture.
             * The prev_ values needed for decoding POC of the next picture are not set here. */
            field_poc[0] = field_poc[1] = INT_MAX;
            ret = ff_h264_init_poc(field_poc, &s->output_picture_number, sps,
                             &p->poc, p->picture_structure, nal.ref_idc);
            if (ret < 0)
                goto fail;

            /* Continue parsing to check if MMCO_RESET is present.
             * FIXME: MMCO_RESET could appear in non-first slice.
             *        Maybe, we should parse all undisposable non-IDR slice of this
             *        picture until encountering MMCO_RESET in a slice of it. */
            if (nal.ref_idc && nal.type != H264_NAL_IDR_SLICE) {
                got_reset = scan_mmco_reset(s, &nal.gb, avctx);
                if (got_reset < 0)
                    goto fail;
            }

            /* Set up the prev_ values for decoding POC of the next picture. */
            p->poc.prev_frame_num        = got_reset ? 0 : p->poc.frame_num;
            p->poc.prev_frame_num_offset = got_reset ? 0 : p->poc.frame_num_offset;
            if (nal.ref_idc != 0) {
                if (!got_reset) {
                    p->poc.prev_poc_msb = p->poc.poc_msb;
                    p->poc.prev_poc_lsb = p->poc.poc_lsb;
                } else {
                    p->poc.prev_poc_msb = 0;
                    p->poc.prev_poc_lsb =
                        p->picture_structure == PICT_BOTTOM_FIELD ? 0 : field_poc[0];
                }
            }

            if (sps->pic_struct_present_flag && p->sei.picture_timing.present) {
                switch (p->sei.picture_timing.pic_struct) {
                case H264_SEI_PIC_STRUCT_TOP_FIELD:
                case H264_SEI_PIC_STRUCT_BOTTOM_FIELD:
                    s->repeat_pict = 0;
                    break;
                case H264_SEI_PIC_STRUCT_FRAME:
                case H264_SEI_PIC_STRUCT_TOP_BOTTOM:
                case H264_SEI_PIC_STRUCT_BOTTOM_TOP:
                    s->repeat_pict = 1;
                    break;
                case H264_SEI_PIC_STRUCT_TOP_BOTTOM_TOP:
                case H264_SEI_PIC_STRUCT_BOTTOM_TOP_BOTTOM:
                    s->repeat_pict = 2;
                    break;
                case H264_SEI_PIC_STRUCT_FRAME_DOUBLING:
                    s->repeat_pict = 3;
                    break;
                case H264_SEI_PIC_STRUCT_FRAME_TRIPLING:
                    s->repeat_pict = 5;
                    break;
                default:
                    s->repeat_pict = p->picture_structure == PICT_FRAME ? 1 : 0;
                    break;
                }
            } else {
                s->repeat_pict = p->picture_structure == PICT_FRAME ? 1 : 0;
            }

            if (p->picture_structure == PICT_FRAME) {
                s->picture_structure = AV_PICTURE_STRUCTURE_FRAME;
                if (sps->pic_struct_present_flag && p->sei.picture_timing.present) {
                    switch (p->sei.picture_timing.pic_struct) {
                    case H264_SEI_PIC_STRUCT_TOP_BOTTOM:
                    case H264_SEI_PIC_STRUCT_TOP_BOTTOM_TOP:
                        s->field_order = AV_FIELD_TT;
                        break;
                    case H264_SEI_PIC_STRUCT_BOTTOM_TOP:
                    case H264_SEI_PIC_STRUCT_BOTTOM_TOP_BOTTOM:
                        s->field_order = AV_FIELD_BB;
                        break;
                    default:
                        s->field_order = AV_FIELD_PROGRESSIVE;
                        break;
                    }
                } else {
                    if (field_poc[0] < field_poc[1])
                        s->field_order = AV_FIELD_TT;
                    else if (field_poc[0] > field_poc[1])
                        s->field_order = AV_FIELD_BB;
                    else
                        s->field_order = AV_FIELD_PROGRESSIVE;
                }
            } else {
                if (p->picture_structure == PICT_TOP_FIELD)
                    s->picture_structure = AV_PICTURE_STRUCTURE_TOP_FIELD;
                else
                    s->picture_structure = AV_PICTURE_STRUCTURE_BOTTOM_FIELD;
                if (p->poc.frame_num == p->last_frame_num &&
                    p->last_picture_structure != AV_PICTURE_STRUCTURE_UNKNOWN &&
                    p->last_picture_structure != AV_PICTURE_STRUCTURE_FRAME &&
                    p->last_picture_structure != s->picture_structure) {
                    if (p->last_picture_structure == AV_PICTURE_STRUCTURE_TOP_FIELD)
                        s->field_order = AV_FIELD_TT;
                    else
                        s->field_order = AV_FIELD_BB;
                } else {
                    s->field_order = AV_FIELD_UNKNOWN;
                }
                p->last_picture_structure = s->picture_structure;
                p->last_frame_num = p->poc.frame_num;
            }

            av_freep(&rbsp.rbsp_buffer);
            return 0; /* no need to evaluate the rest */
        }
    }
    if (q264) {
        av_freep(&rbsp.rbsp_buffer);
        return 0;
    }
    /* didn't find a picture! */
    av_log(avctx, AV_LOG_ERROR, "missing picture in access unit with size %d\n", buf_size);
fail:
    av_freep(&rbsp.rbsp_buffer);
    return -1;
}
int my_ff_h264_sei_decode(H264SEIContext *h, GetBitContext *gb,
                       const H264ParamSets *ps, void *logctx)
{
    int master_ret = 0;

    while (get_bits_left(gb) > 16 && show_bits(gb, 16)) {
        int type = 0;
        unsigned size = 0;
        unsigned next;
        int ret  = 0;

        do {
            if (get_bits_left(gb) < 8)
                return AVERROR_INVALIDDATA;
            type += show_bits(gb, 8);
        } while (get_bits(gb, 8) == 255);

        do {
            if (get_bits_left(gb) < 8)
                return AVERROR_INVALIDDATA;
            size += show_bits(gb, 8);
        } while (get_bits(gb, 8) == 255);

        if (size > get_bits_left(gb) / 8) {
            av_log(logctx, AV_LOG_ERROR, "SEI type %d size %d truncated at %d\n",
                   type, 8*size, get_bits_left(gb));
            return AVERROR_INVALIDDATA;
        }
        next = get_bits_count(gb) + 8 * size;

        switch (type) {

        case H264_SEI_TYPE_USER_DATA_UNREGISTERED:
            ret = my_decode_unregistered_user_data(&h->unregistered, gb, logctx, size);
            break;

        default:
            av_log(logctx, AV_LOG_DEBUG, "unknown SEI type %d\n", type);
        }
        if (ret < 0 && ret != AVERROR_PS_NOT_FOUND)
            return ret;
        if (ret < 0)
            master_ret = ret;

        skip_bits_long(gb, next - get_bits_count(gb));

        // FIXME check bits here
        align_get_bits(gb);
    }

    return master_ret;
}
int my_decode_unregistered_user_data(H264SEIUnregistered *h, GetBitContext *gb,
                                                 void *logctx, int size)
        {char nal_data[500];
        char temp[100];
            uint8_t *user_data;
            int e, build, i;

            if (size < 16 || size >= INT_MAX - 16)
                return AVERROR_INVALIDDATA;

            user_data = (uint8_t*)av_malloc(16 + size + 1);
            if (!user_data)
                return AVERROR(ENOMEM);

            for (i = 0; i < size + 16; i++){
                user_data[i] = get_bits(gb, 8);
        sprintf(temp,"%02x",user_data[i]);
        strcat(nal_data,temp);
        }
        this->FINALNAL=nal_data;
        cout<<FINALNAL;
        printf("\n");

            user_data[i] = 0;
            // e = sscanf(user_data + 16, "x264 - core %d", &build);
            // if (e == 1 && build > 0)
            //     h->x264_build = build;
            // if (e == 1 && build == 1 && !strncmp(user_data+16, "x264 - core 0000", 16))
            //     h->x264_build = 67;

            av_free(user_data);
            return 0;
        }

        void connect(bool dump_av_format){
          // cout<<"line 58: connect() called\n";
          int ret = 0;
          AVPacket pkt = { 0 };
          this->code_meta_data();
          if (argc != 2) {
              if (this->getSrcFilename()==NULL) {
                cout<< "Error: No input file given\n";
                exit(1);
              }else{
              fprintf(stderr, "Usage: %s <video>\n", this->getSrcFilename());
              exit(1);
            }
          }

          // src_filename = videopath;

          if (avformat_open_input(&(this->pFormatCtx), this->getSrcFilename(), NULL, NULL) < 0) {
              fprintf(stderr, "Error:Could not open source file %s\n", this->getSrcFilename());
              exit(1);
          }

          if (avformat_find_stream_info(this->pFormatCtx, NULL) < 0) {
              fprintf(stderr, "Could not find stream information\n");
              exit(1);
          }

          this->type = AVMEDIA_TYPE_VIDEO;

          open_codec_context();
          if(dump_av_format)
            av_dump_format(this->pFormatCtx, 0, this->src_filename, 0);

        }

        int open_codec_context()
        {
            int ret;
            AVStream *st;
            AVCodecContext *dec_ctx = NULL;
            AVCodec *dec = NULL;
            AVDictionary *opts = NULL;

            ret = av_find_best_stream(this->pFormatCtx, this->type, -1, -1, &dec, 0);
            if (ret < 0) {
                fprintf(stderr, "Could not find %s stream in input file '%s'\n",
                        av_get_media_type_string(this->type), this->getSrcFilename());
                return ret;
            } else {
                int stream_idx = ret;
                st = this->pFormatCtx->streams[stream_idx];
                this->fps=av_q2d(st->r_frame_rate);
                dec_ctx = avcodec_alloc_context3(dec);
                if (!dec_ctx) {
                    fprintf(stderr, "Failed to allocate codec\n");
                    return AVERROR(EINVAL);
                }

                ret = avcodec_parameters_to_context(dec_ctx, st->codecpar);
                if (ret < 0) {
                    fprintf(stderr, "Failed to copy codec parameters to codec context\n");
                    return ret;
                }

                /* Init the video decoder */
                av_dict_set(&opts, "flags2", "+export_mvs", 0);
                if ((ret = avcodec_open2(dec_ctx, dec, &opts)) < 0) {
                    fprintf(stderr, "Failed to open %s codec\n",
                            av_get_media_type_string(this->type));
                    return ret;
                }

                this->video_stream_idx = stream_idx;
                this->video_stream = this->pFormatCtx->streams[this->video_stream_idx];
                this->pCodecCtx = dec_ctx;\
                this->avparserctx=av_parser_init(this->pCodecCtx->codec_id);
            }

            return 0;
        }
// int getheight(){
//   return this->pCodecCtx->height;
// }
// int getwidth(){
//   return this->pCodecCtx->width;
// }
// int getline(){
//   return this->pFrameRGB->linesize[0];
// }

//int64_t getPseudoRealTimeStamp(){ //Use this for epoch time
  //  this->pFormatCtx->start_time_realtime = av_gettime();
    //return this->pFormatCtx->start_time_realtime;
//}

/*int64_t getPseudoTimeStamp(){
    // this->pFormatCtx->start_time_realtime = av_gettime();
    return this->pFormatCtx->start_time;
}

int getFPS(){
  return this->fps;
}*/






int decode_packet()
{
  // cout<<"line 134: decode_packet() called\n";
  int ret = avcodec_send_packet(this->pCodecCtx, this->pkt);
  int size;
	this->str="";
  if (ret < 0) {
      fprintf(stderr, "Error while sending a packet to the decoder\n");
      return ret;
  }

  while (ret >= 0)  {
      ret = avcodec_receive_frame(this->pCodecCtx, this->pFrame);
      if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
          break;
      } else if (ret < 0) {
          fprintf(stderr, "Error while receiving a frame from the decoder: \n");
          return ret;
      }



      if (ret >= 0) {
          int i;
          AVFrameSideData *sd;
          // this->video_frame_count++;
          this->increase_current_frame_number();
          sws_scale(this->sws_ctx, (uint8_t const * const *)this->pFrame->data,
              this->pFrame->linesize, 0, this->pCodecCtx->height,
              this->pFrameRGB->data, this->pFrameRGB->linesize);

          //convert frame to Mat
          this->cv_mat=Mat(this->pCodecCtx->height, this->pCodecCtx->width, CV_8UC3, this->pFrameRGB->data[0], this->pFrameRGB->linesize[0]);
       my_h264_parse(this->avparserctx,
                              this->pCodecCtx,
                                this->pkt->data,this->pkt->size);

      for(int kk=0;kk<this->pkt->size;kk++)
{
   sprintf(this->temp_str,"%02x",this->pkt->data[kk]);
    this->str.append(this->temp_str);
}





//  printf("\rTotal Processed Frames:%d", this->video_frame_count);
//    fflush(stdout);
    //cout<<std::flush;
    //cout<<"Total Processed Frames:"<<this->video_frame_count<<endl;
          //Print frame data
          // print_frame_data(frame);
          av_frame_unref(this->pFrame);
      }
  }
  this->setFrameFlag(true);
  return this->video_frame_count;
  // return 0;
}

void code_meta_data(){
  printf("\n");

  // printf("--------------------------------------------------------------------------------------\n");
  // printf("framenum,source,blockw,blockh,srcx,srcy,dstx,dsty,motion_x,motion_y,motion_scale,flags\n");
  // printf("--------------------------------------------------------------------------------------\n");
}

int extract_frame_with_sei(){
    // cout<<"line 139: extract_motion_vectors() called\n";
    int ret = 0;
    AVPacket pkt = { 0 };
    // cout<<"1"<<endl;
    if (!this->video_stream) {
        fprintf(stderr, "Could not find video stream in the input, aborting\n");
        ret = 1;
        // cout<<"2"<<endl;
        goto end;
    }

    // cout<<"3"<<endl;
    this->pFrame = av_frame_alloc();
    if (!this->pFrame) {
        fprintf(stderr, "Could not allocate frame\n");
        ret = AVERROR(ENOMEM);
        // cout<<"4"<<endl;
        goto end;
    }

    // cout<<"5"<<endl;

    // Allocate an AVFrame structure
    this->pFrameRGB=av_frame_alloc();
    if(this->pFrameRGB==NULL)
      return -1;

      // Determine required buffer size and allocate buffer
      this->numBytes=avpicture_get_size(AV_PIX_FMT_BGR24, this->pCodecCtx->width,
                this->pCodecCtx->height);

      this->buffer=(uint8_t *)av_malloc(this->numBytes*sizeof(uint8_t));

    // Assign appropriate parts of buffer to image planes in pFrameRGB
    // Note that pFrameRGB is an AVFrame, but AVFrame is a superset
    // of AVPicture
    avpicture_fill((AVPicture *)this->pFrameRGB, this->buffer, AV_PIX_FMT_BGR24,
       this->pCodecCtx->width, this->pCodecCtx->height);
    // initialize SWS context for software scaling
    this->sws_ctx = sws_getContext(
           this->pCodecCtx->width,
           this->pCodecCtx->height,
           this->pCodecCtx->pix_fmt,
           this->pCodecCtx->width,
           this->pCodecCtx->height,
           AV_PIX_FMT_BGR24,
           SWS_BILINEAR,
           NULL,
           NULL,
           NULL
           );



    /* read frames from the file */
    while (av_read_frame(this->pFormatCtx, &pkt) >= 0) {

      // cout<<"6"<<endl;

        this->pkt = &pkt;
        if (this->pkt->stream_index == this->video_stream_idx){
              ret=this->decode_packet();
        }

        av_packet_unref(&pkt);
        av_packet_unref(this->pkt);
        if (ret < 0 || this->getFrameFlag()){
            av_freep(&(this->buffer));
            this->setFrameFlag(false);
            return this->video_frame_count;
            break;
          }
    }

    /* flush cached frames */
    // this->decode_packet(NULL);
    printf("\n--------------------------------------------------------------------------------------\n");

end:
    // cout<<"RET "<<endl;
    av_frame_free(&(this->pFrame));
    return ret < 0;
}

/* flush cached frames */
void flush_cached_frames(){
  this->pkt = NULL;
  this->decode_packet();
}

void freeStuff(){
  av_frame_free(&(this->pFrame));
  avcodec_free_context(&(this->pCodecCtx));
  avformat_close_input(&(this->pFormatCtx));
}

int get_current_frame_number(){
  return this->video_frame_count;
}

void increase_current_frame_number(){
  this->video_frame_count = this->video_frame_count%2500;
  this->video_frame_count++;
}


};

// Define C functions for the C++ class - as ctypes can only talk to C...


// extern "C"
// {
//     FMV* FMV_new(int argc, char **argv) {return new FMV(argc, argv[1]);}
//
//     const char* FMV_getSrcFilename(FMV* fmv) {return fmv->getSrcFilename();}
//
//     void FMV_setFrameFlag(FMV* fmv, bool flag){fmv->setFrameFlag(flag);}
//
//     bool FMV_getFrameFlag(FMV* fmv){return fmv->getFrameFlag();}
//
//     void FMV_connect(FMV* fmv, bool dump_av_format){fmv->connect(dump_av_format);}
//
//     int FMV_open_codec_context(FMV* fmv){return fmv->open_codec_context();}
//
//     int FMV_decode_packet(FMV* fmv){return fmv->decode_packet();}
//
//     int FMV_extract_motion_vectors(FMV* fmv){return fmv->extract_motion_vectors();}
//
//     /* flush cached frames */
//     void FMV_flush_cached_frames(FMV* fmv){fmv->flush_cached_frames();}
//
//     void FMV_freeStuff(FMV* fmv){fmv->freeStuff();}
//
//     int FMV_get_current_frame_number(FMV* fmv){return fmv->get_current_frame_number();}
//
//     void FMV_increase_current_frame_number(FMV* fmv){fmv->increase_current_frame_number();}
//
// }

FMV* createFMVobj(int argc, char *argv){
FMV* fmv = new FMV(argc, argv);
return fmv;

}

int main(int argc, char **argv){

  // FMV* fmv = createFMVobj(argc,argv[1]);
  FMV* fmv = new FMV(argc,argv[1]);
  fmv->connect(false);// Give true to dump_av_format
  int i = fmv->get_current_frame_number();
  int frame_num=0;
  while(frame_num==fmv->get_current_frame_number()){
    frame_num=fmv->extract_frame_with_sei();

    i=fmv->get_current_frame_number();

    /*Now printing the json object*/
    // printf ("%s\n",json_object_to_json_string(fmv->getFrameJson()));

    // cout<<"\t"<<fmv->getFPS()<<"|\t"<<fmv->getPseudoRealTimeStamp()<<endl;
    // cout<<"\t\t\t|\t"<<fmv->getPseudoRealTimeStamp();
  }
  // fmv->flush_cached_frames();
  fmv->freeStuff();
  return 0;
}


// int process(int argc, char *argv){
// // cout << "line 21: main() called\n";
//
//
// // FMV* fmv = createFMVobj(argc,argv[1]);
// FMV* fmv = new FMV(argc,argv[1]);
// fmv->connect(false);// Give true to dump_av_format
// int i = fmv->get_current_frame_number();
// int frame_num=0;
// cout<<"Total FPS:"<<fmv->getFPS()<<endl;
// while(frame_num==fmv->get_current_frame_number()){
//   frame_num=fmv->extract_motion_vectors();
//   fmv->getMAT();
//   i=fmv->get_current_frame_number();
//
//   /*Now printing the json object*/
//   // printf ("%s\n",json_object_to_json_string(fmv->getFrameJson()));
//
//   // cout<<"\t"<<fmv->getFPS()<<"|\t"<<fmv->getPseudoRealTimeStamp()<<endl;
//   // cout<<"\t\t\t|\t"<<fmv->getPseudoRealTimeStamp();
// }
// // fmv->flush_cached_frames();
// fmv->freeStuff();
// return 0;
// }

//
BOOST_PYTHON_MODULE(ffmpeg)

{using namespace boost::python;


    class_<FMV,FMV*>("FMV",init<int,char*>())
      .def_readonly("cv_mat",&FMV::cv_mat)
      .def("getSrcFilename",&FMV::getSrcFilename)
      .def("setFrameFlag",&FMV::setFrameFlag)
      .def("getFrameFlag",&FMV::getFrameFlag)
      .def("connect",&FMV::connect)
      .def("open_codec_context",&FMV::open_codec_context)
      .def("decode_packet",&FMV::decode_packet)
      .def("extract_frame_with_sei",&FMV::extract_frame_with_sei)
      .def("flush_cached_frames",&FMV::flush_cached_frames)
      .def("freeStuff",&FMV::freeStuff)
      .def("get_current_frame_number",&FMV::get_current_frame_number)
      .def("increase_current_frame_number",&FMV::increase_current_frame_number)
      .def("getMAT",&FMV::getMAT)
      .def("getPacketData",&FMV::getPacketData)
      .def("getSEI",&FMV::getSEI);




      //using namespace XM;

      //expose module-level functions


}


BOOST_PYTHON_MODULE(SEINalExtractor)

{using namespace boost::python;


    class_<FMV,FMV*>("FMV",init<int,char*>())
      .def_readonly("cv_mat",&FMV::cv_mat)
      .def("getSrcFilename",&FMV::getSrcFilename)
      .def("setFrameFlag",&FMV::setFrameFlag)
      .def("getFrameFlag",&FMV::getFrameFlag)
      .def("connect",&FMV::connect)
      .def("open_codec_context",&FMV::open_codec_context)
      .def("decode_packet",&FMV::decode_packet)
      .def("extract_frame_with_sei",&FMV::extract_frame_with_sei)
      .def("flush_cached_frames",&FMV::flush_cached_frames)
      .def("freeStuff",&FMV::freeStuff)
      .def("get_current_frame_number",&FMV::get_current_frame_number)
      .def("increase_current_frame_number",&FMV::increase_current_frame_number)
      .def("getMAT",&FMV::getMAT)
      .def("getPacketData",&FMV::getPacketData)
      .def("getSEI",&FMV::getSEI);




      //using namespace XM;

      //expose module-level functions


}

