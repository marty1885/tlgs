// Generated raw-margin scorer. Do not compile with fast-math.
#include "ranker.h"
#include <stddef.h>
#include <stdint.h>
#undef HWY_TARGET_INCLUDE
#define HWY_TARGET_INCLUDE "ranker.cc"
#include "hwy/foreach_target.h"
#include "hwy/highway.h"
HWY_BEFORE_NAMESPACE();
namespace ranker_implementation {
    namespace HWY_NAMESPACE {
        namespace hn = hwy::HWY_NAMESPACE;
        float Score(const float *features) {
            float score = 0x0.0p+0f;
            /* Tree 0: preserve sequential float32 accumulation. */
            score += (features[2] < 0x1.4637640000000p-1f ? (!(features[50] >= 0x1.354c3e0000000p+0f) ? (features[100] < 0x1.99999a0000000p-3f ? (features[2] < 0x1.a338720000000p-2f ? -0x1.99ddcc0000000p-5f : -0x1.49fad00000000p-6f) : -0x1.e463b00000000p-5f) : 0x1.85da3c0000000p-5f) : (features[83] < 0x1.b6db6e0000000p-2f ? (features[161] < 0x1.26bb1c0000000p+1f ? (features[110] < 0x1.d595a00000000p+2f ? 0x1.0d7c400000000p-8f : 0x1.c839220000000p-6f) : (features[60] < 0x1.0000000000000p-1f ? -0x1.ca5b9e0000000p-7f : -0x1.d699b40000000p-5f)) : (features[158] < 0x1.193ea80000000p+1f ? -0x1.e4690c0000000p-5f : 0x1.4ac2e80000000p-5f)));
            /* Tree 1: preserve sequential float32 accumulation. */
            score += (features[158] < 0x1.26bb1c0000000p+1f ? (features[154] < 0x1.8000000000000p-1f ? (!(features[2] >= 0x1.8921560000000p-1f) ? (features[100] < 0x1.99999a0000000p-3f ? -0x1.091e0c0000000p-6f : -0x1.9d0f920000000p-5f) : (features[10] < 0x1.7a1e080000000p+2f ? -0x1.8307880000000p-8f : 0x1.0b68640000000p-6f)) : -0x1.dbc6060000000p-5f) : (features[102] < 0x1.9072f60000000p+4f ? (features[140] < 0x1.51cca20000000p+1f ? 0x1.b82a180000000p-5f : (features[9] < 0x1.2a0c1e0000000p+3f ? 0x1.3d79180000000p-6f : 0x1.9da1140000000p-5f)) : (features[154] < 0x1.99999a0000000p-2f ? (features[88] < 0x1.4322f40000000p-2f ? 0x1.4b292a0000000p-5f : 0x1.3d79180000000p-6f) : (features[52] < 0x1.bc75960000000p-1f ? 0x1.3d79180000000p-6f : 0x1.d4e7460000000p-5f))));
            /* Tree 2: preserve sequential float32 accumulation. */
            score += (features[2] < 0x1.4637640000000p-1f ? (!(features[52] >= 0x1.5b50c60000000p-1f) ? (features[100] < 0x1.99999a0000000p-3f ? (features[5] < 0x1.45828c0000000p-7f ? -0x1.55dc280000000p-5f : -0x1.33c1780000000p-8f) : -0x1.c1558e0000000p-5f) : (features[80] < 0x1.6ece540000000p-4f ? -0x1.4d68000000000p-7f : 0x1.b0c7460000000p-5f)) : (features[158] < 0x1.bf8d900000000p+1f ? (features[162] < 0x1.e1e1e20000000p-3f ? (features[15] < 0x1.6666660000000p-2f ? -0x1.d9a8400000000p-9f : 0x1.0827080000000p-6f) : (features[67] < 0x1.0000000000000p+0f ? -0x1.c44ff20000000p-7f : -0x1.b0f5ae0000000p-5f)) : (!(features[52] >= 0x1.5c08140000000p-1f) ? (features[95] < 0x1.3d28480000000p+3f ? 0x1.3c79060000000p-6f : 0x1.7d784a0000000p-5f) : (features[103] < 0x1.19db700000000p+2f ? 0x1.3c79060000000p-6f : 0x1.c7107e0000000p-5f))));
            /* Tree 3: preserve sequential float32 accumulation. */
            score += (features[2] < 0x1.4637640000000p-1f ? (!(features[52] >= 0x1.5b50c60000000p-1f) ? (features[100] < 0x1.99999a0000000p-3f ? (features[19] < 0x1.8c0f060000000p-4f ? -0x1.6438500000000p-5f : -0x1.1bb7420000000p-6f) : -0x1.b3d6b80000000p-5f) : (features[110] < 0x1.7ea57e0000000p+2f ? 0x1.867a260000000p-8f : 0x1.9c0e340000000p-5f)) : (features[158] < 0x1.26bb1c0000000p+1f ? (features[154] < 0x1.8000000000000p-1f ? (features[162] < 0x1.e1e1e20000000p-3f ? 0x1.0350a80000000p-7f : -0x1.65d5720000000p-6f) : -0x1.c247c00000000p-5f) : (features[95] < 0x1.eab3f80000000p+2f ? (features[123] < 0x1.0000000000000p-1f ? 0x1.1ba3320000000p-6f : 0x1.1d5eee0000000p-5f) : (features[102] < 0x1.2c23740000000p+4f ? 0x1.1ba3320000000p-6f : 0x1.a08a340000000p-5f))));
            /* Tree 4: preserve sequential float32 accumulation. */
            score += (features[2] < 0x1.4637640000000p-1f ? (!(features[52] >= 0x1.5b50c60000000p-1f) ? (features[100] < 0x1.99999a0000000p-3f ? (features[5] < 0x1.45828c0000000p-7f ? -0x1.31f15e0000000p-5f : -0x1.4f26f80000000p-8f) : -0x1.a62c120000000p-5f) : (features[3] < 0x1.75f50c0000000p-10f ? 0x1.42ea540000000p-7f : 0x1.89394c0000000p-5f)) : (features[158] < 0x1.26bb1c0000000p+1f ? (features[154] < 0x1.8000000000000p-1f ? (features[162] < 0x1.e1e1e20000000p-3f ? 0x1.9eb3560000000p-8f : -0x1.7ab3f80000000p-6f) : -0x1.b15c2e0000000p-5f) : (features[95] < 0x1.0f1ab00000000p+3f ? (features[55] < 0x1.f2272a0000000p+0f ? 0x1.0ad2b60000000p-6f : 0x1.1e59ee0000000p-5f) : (features[52] < 0x1.67fb6e0000000p-3f ? 0x1.0ad2b60000000p-6f : 0x1.95e60a0000000p-5f))));
            /* Tree 5: preserve sequential float32 accumulation. */
            score += (features[2] < 0x1.72c1100000000p-1f ? (features[156] < 0x1.62e4300000000p-1f ? (features[100] < 0x1.6a09e60000000p-1f ? (features[21] < 0x1.c6c93a0000000p-13f ? -0x1.39cd3e0000000p-5f : -0x1.77f1800000000p-7f) : (features[85] < 0x1.6666660000000p-2f ? -0x1.9ce58a0000000p-5f : 0x1.7f72160000000p-9f)) : (features[106] < 0x1.2302ca0000000p+1f ? 0x1.0286340000000p-6f : 0x1.94d8c80000000p-5f)) : (!(features[53] >= 0x1.0000000000000p+0f) ? (features[10] < 0x1.6d0ac60000000p+2f ? (features[158] < 0x1.193ea80000000p+1f ? -0x1.cb4d800000000p-7f : 0x1.01703c0000000p-6f) : (features[114] < 0x1.5a31760000000p+3f ? 0x1.66e9360000000p-7f : -0x1.5f84a60000000p-6f)) : (features[140] < 0x1.fc32860000000p+1f ? (features[103] < 0x1.6e66460000000p+1f ? 0x1.a3a3f60000000p-9f : 0x1.8e0b600000000p-5f) : -0x1.24eb620000000p-5f)));
            /* Tree 6: preserve sequential float32 accumulation. */
            score += (features[2] < 0x1.4637640000000p-1f ? (!(features[52] >= 0x1.5b50c60000000p-1f) ? (features[100] < 0x1.99999a0000000p-3f ? (features[11] < 0x1.6578160000000p-7f ? -0x1.388b940000000p-6f : -0x1.5f3dc00000000p-5f) : -0x1.8f960a0000000p-5f) : (features[110] < 0x1.3d61560000000p+2f ? 0x1.5b79ea0000000p-8f : 0x1.70f4f60000000p-5f)) : (features[158] < 0x1.26bb1c0000000p+1f ? (features[154] < 0x1.8000000000000p-1f ? (features[162] < 0x1.e1e1e20000000p-3f ? 0x1.8526f80000000p-8f : -0x1.70275e0000000p-6f) : -0x1.9f1ac00000000p-5f) : (features[95] < 0x1.0f1ab00000000p+3f ? (!(features[53] >= 0x1.0000000000000p+0f) ? 0x1.ec27de0000000p-7f : 0x1.355f100000000p-5f) : (features[52] < 0x1.67fb6e0000000p-3f ? 0x1.ec27de0000000p-7f : 0x1.7e71ba0000000p-5f))));
            /* Tree 7: preserve sequential float32 accumulation. */
            score += (features[2] < 0x1.4637640000000p-1f ? (!(features[52] >= 0x1.5b50c60000000p-1f) ? (features[100] < 0x1.99999a0000000p-3f ? (features[2] < 0x1.042ab40000000p-1f ? -0x1.44b3f20000000p-5f : -0x1.071f940000000p-6f) : -0x1.8599aa0000000p-5f) : (features[3] < 0x1.75f50c0000000p-10f ? 0x1.0faa9e0000000p-8f : 0x1.6bb32e0000000p-5f)) : (features[67] < 0x1.0000000000000p+0f ? (features[110] < 0x1.447d380000000p+3f ? (features[10] < 0x1.b8259e0000000p+2f ? -0x1.1e68900000000p-7f : 0x1.78979a0000000p-7f) : (features[147] < 0x1.99999a0000000p-3f ? 0x1.154a600000000p-6f : -0x1.b8f65c0000000p-5f)) : (features[60] < 0x1.0000000000000p-1f ? (features[0] < 0x1.25db2e0000000p+1f ? 0x1.5123180000000p-6f : -0x1.1877880000000p-6f) : -0x1.aca13c0000000p-5f)));
            /* Tree 8: preserve sequential float32 accumulation. */
            score += (features[83] < 0x1.b6db6e0000000p-2f ? (features[67] < 0x1.0000000000000p+0f ? (features[110] < 0x1.21dc500000000p+3f ? (!(features[2] >= 0x1.781b2a0000000p-1f) ? -0x1.7be12e0000000p-6f : -0x1.1961760000000p-9f) : (features[158] < 0x1.d82d340000000p+1f ? 0x1.3f0b6e0000000p-7f : 0x1.4d72380000000p-5f)) : (features[60] < 0x1.0000000000000p-1f ? (features[24] < 0x1.1d92280000000p-8f ? 0x1.792fd60000000p-6f : -0x1.5795c00000000p-7f) : -0x1.9bcb9a0000000p-5f)) : (features[158] < 0x1.193ea80000000p+1f ? -0x1.8e88800000000p-5f : 0x1.15ba4c0000000p-5f));
            /* Tree 9: preserve sequential float32 accumulation. */
            score += (features[2] < 0x1.72c1100000000p-1f ? (features[156] < 0x1.62e4300000000p-1f ? (features[100] < 0x1.6a09e60000000p-1f ? (features[21] < 0x1.c6c93a0000000p-13f ? -0x1.2ac9e40000000p-5f : -0x1.6c49500000000p-7f) : (features[85] < 0x1.6666660000000p-2f ? -0x1.7c38e40000000p-5f : 0x1.bb74b60000000p-8f)) : (features[106] < 0x1.2302ca0000000p+1f ? 0x1.46234a0000000p-7f : 0x1.738be80000000p-5f)) : (features[13] < 0x1.2345680000000p-7f ? (features[114] < 0x1.5a31760000000p+3f ? (features[140] < 0x1.f746100000000p+1f ? 0x1.6834d00000000p-6f : 0x1.aa5eac0000000p-8f) : (features[13] < 0x1.84f00c0000000p-10f ? -0x1.93dc580000000p-5f : -0x1.5233480000000p-7f)) : (features[158] < 0x1.26bb1c0000000p+1f ? (features[154] < 0x1.8000000000000p-1f ? -0x1.96dc7c0000000p-8f : -0x1.8776ea0000000p-5f) : (features[95] < 0x1.e360ea0000000p+2f ? 0x1.6924880000000p-7f : 0x1.594a540000000p-5f))));
            /* Tree 10: preserve sequential float32 accumulation. */
            score += (features[2] < 0x1.4637640000000p-1f ? (!(features[52] >= 0x1.5b50c60000000p-1f) ? (features[100] < 0x1.99999a0000000p-3f ? (features[5] < 0x1.45828c0000000p-7f ? -0x1.1201f60000000p-5f : -0x1.37679a0000000p-9f) : -0x1.70e65e0000000p-5f) : (features[3] < 0x1.75f50c0000000p-10f ? -0x1.541d0a0000000p-11f : 0x1.5353aa0000000p-5f)) : (!(features[53] >= 0x1.0000000000000p+0f) ? (features[15] < 0x1.5555560000000p-2f ? (!(features[24] >= 0x1.1a636e0000000p-4f) ? -0x1.bb6ffe0000000p-7f : 0x1.df5e220000000p-8f) : (features[67] < 0x1.0000000000000p+0f ? 0x1.81c74a0000000p-7f : -0x1.5a99420000000p-5f)) : (features[158] < 0x1.bf8d900000000p+1f ? (features[55] < 0x1.cab0c00000000p+0f ? -0x1.634d260000000p-5f : 0x1.27d4d00000000p-6f) : (features[114] < 0x1.4cefb80000000p+3f ? 0x1.6da8de0000000p-5f : 0x1.27d4d00000000p-6f))));
            /* Tree 11: preserve sequential float32 accumulation. */
            score += (features[83] < 0x1.b6db6e0000000p-2f ? (features[67] < 0x1.0000000000000p+0f ? (features[110] < 0x1.21dc500000000p+3f ? (features[2] < 0x1.042ab40000000p-1f ? -0x1.2d8b960000000p-5f : -0x1.e330f80000000p-9f) : (features[141] < 0x1.3e116c0000000p+1f ? 0x1.1e3a5c0000000p-6f : -0x1.0bd5fe0000000p-7f)) : (features[60] < 0x1.0000000000000p-1f ? (features[0] < 0x1.25db2e0000000p+1f ? 0x1.638b280000000p-6f : -0x1.94747e0000000p-7f) : -0x1.881e9c0000000p-5f)) : (features[158] < 0x1.193ea80000000p+1f ? -0x1.7acd580000000p-5f : 0x1.0cb8480000000p-5f));
            /* Tree 12: preserve sequential float32 accumulation. */
            score += (features[83] < 0x1.b6db6e0000000p-2f ? (features[67] < 0x1.0000000000000p+0f ? (features[110] < 0x1.21dc500000000p+3f ? (!(features[2] >= 0x1.781b2a0000000p-1f) ? -0x1.630bce0000000p-6f : -0x1.1779da0000000p-9f) : (features[140] < 0x1.22c5580000000p+2f ? 0x1.cbf1240000000p-7f : -0x1.e958d00000000p-6f)) : (features[60] < 0x1.0000000000000p-1f ? (features[0] < 0x1.25db2e0000000p+1f ? 0x1.7268dc0000000p-6f : -0x1.8fbeea0000000p-7f) : -0x1.7f74a60000000p-5f)) : (features[158] < 0x1.193ea80000000p+1f ? -0x1.73418e0000000p-5f : 0x1.11062a0000000p-5f));
            /* Tree 13: preserve sequential float32 accumulation. */
            score += (features[2] < 0x1.4637640000000p-1f ? (!(features[52] >= 0x1.5b50c60000000p-1f) ? (features[100] < 0x1.99999a0000000p-3f ? (features[5] < 0x1.45828c0000000p-7f ? -0x1.0a2a420000000p-5f : -0x1.a8d4800000000p-9f) : -0x1.5e9bce0000000p-5f) : (features[61] < 0x1.bd85e00000000p+2f ? 0x1.49793c0000000p-5f : 0x1.ed95ee0000000p-8f)) : (features[13] < 0x1.c71c720000000p-8f ? (features[103] < 0x1.594ab80000000p-2f ? (!(features[52] >= 0x1.338c7e0000000p-1f) ? -0x1.89d3580000000p-5f : -0x1.c323f20000000p-7f) : (features[125] < 0x1.32ee3c0000000p+1f ? 0x1.2733b00000000p-6f : -0x1.b3d2500000000p-8f)) : (features[158] < 0x1.26bb1c0000000p+1f ? (features[154] < 0x1.8000000000000p-1f ? -0x1.1f08da0000000p-8f : -0x1.749c6c0000000p-5f) : (features[88] < 0x1.a13b640000000p-1f ? 0x1.6218100000000p-7f : 0x1.40def20000000p-5f))));
            /* Tree 14: preserve sequential float32 accumulation. */
            score += (features[2] < 0x1.72c1100000000p-1f ? (features[156] < 0x1.62e4300000000p-1f ? (features[100] < 0x1.6a09e60000000p-1f ? (features[21] < 0x1.05a9ec0000000p-12f ? -0x1.139de20000000p-5f : -0x1.3a180a0000000p-7f) : (features[85] < 0x1.6666660000000p-2f ? -0x1.5e6f420000000p-5f : 0x1.ab3ba40000000p-8f)) : (features[106] < 0x1.2302ca0000000p+1f ? 0x1.d853bc0000000p-8f : 0x1.5a61920000000p-5f)) : (features[13] < 0x1.c71c720000000p-8f ? (features[114] < 0x1.5a31760000000p+3f ? (features[108] < 0x1.1e377a0000000p+0f ? 0x1.7317ac0000000p-7f : 0x1.04624a0000000p-5f) : (features[13] < 0x1.58791a0000000p-10f ? -0x1.70ef9a0000000p-5f : -0x1.1d21040000000p-7f)) : (features[158] < 0x1.26bb1c0000000p+1f ? (features[154] < 0x1.8000000000000p-1f ? -0x1.d5f5ca0000000p-9f : -0x1.6ce92a0000000p-5f) : (features[95] < 0x1.eab3f80000000p+2f ? 0x1.4d0d7c0000000p-7f : 0x1.36fbda0000000p-5f))));
            /* Tree 15: preserve sequential float32 accumulation. */
            score += (features[83] < 0x1.b6db6e0000000p-2f ? (features[67] < 0x1.0000000000000p+0f ? (features[102] < 0x1.c466680000000p+4f ? (features[15] < 0x1.5555560000000p-2f ? -0x1.0375c80000000p-7f : 0x1.3a28460000000p-7f) : (features[160] < 0x1.ab68a00000000p-5f ? 0x1.30fc000000000p-8f : 0x1.45b6040000000p-5f)) : (features[60] < 0x1.0000000000000p-1f ? (features[0] < 0x1.25db2e0000000p+1f ? 0x1.8925ac0000000p-6f : -0x1.953d780000000p-7f) : -0x1.74f8240000000p-5f)) : (features[158] < 0x1.193ea80000000p+1f ? -0x1.6256040000000p-5f : 0x1.eab18e0000000p-6f));
            /* Tree 16: preserve sequential float32 accumulation. */
            score += (features[2] < 0x1.4637640000000p-1f ? (!(features[52] >= 0x1.e4dfb00000000p-1f) ? (features[100] < 0x1.99999a0000000p-3f ? (features[5] < 0x1.45828c0000000p-7f ? -0x1.f561840000000p-6f : -0x1.a71d200000000p-9f) : -0x1.4feece0000000p-5f) : (features[66] < 0x1.3333340000000p-2f ? 0x1.47aef00000000p-5f : 0x1.77d0820000000p-7f)) : (features[10] < 0x1.876ac60000000p+2f ? (features[158] < 0x1.26bb1c0000000p+1f ? (features[154] < 0x1.4000000000000p-1f ? -0x1.1020500000000p-7f : -0x1.661b700000000p-5f) : (features[102] < 0x1.9072f60000000p+4f ? 0x1.0306760000000p-7f : 0x1.2c62e60000000p-5f)) : (features[110] < 0x1.1ccf640000000p+3f ? (features[70] < 0x1.aaaaaa0000000p-2f ? 0x1.3d3bec0000000p-8f : -0x1.743a520000000p-6f) : (features[67] < 0x1.e666660000000p-1f ? 0x1.366cde0000000p-6f : -0x1.4cd13a0000000p-5f))));
            /* Tree 17: preserve sequential float32 accumulation. */
            score += (features[2] < 0x1.72c1100000000p-1f ? (features[85] < 0x1.47ae140000000p-3f ? (features[100] < 0x1.6a09e60000000p-1f ? (features[21] < 0x1.05a9ec0000000p-12f ? -0x1.0e1a400000000p-5f : -0x1.4920660000000p-7f) : -0x1.50417c0000000p-5f) : (features[77] < 0x1.99999a0000000p-5f ? -0x1.b793aa0000000p-6f : (features[110] < 0x1.1335180000000p+3f ? 0x1.32e3520000000p-7f : 0x1.59114e0000000p-5f))) : (features[10] < 0x1.9d3bb60000000p+2f ? (features[158] < 0x1.193ea80000000p+1f ? (features[154] < 0x1.6db6dc0000000p-1f ? -0x1.56d7580000000p-8f : -0x1.5e5cf60000000p-5f) : (features[154] < 0x1.3333340000000p-1f ? 0x1.17bce40000000p-7f : 0x1.0fcac40000000p-5f)) : (features[114] < 0x1.5a31760000000p+3f ? (features[63] < 0x1.6aaaaa0000000p-2f ? 0x1.fc82ba0000000p-7f : -0x1.6ee1b60000000p-5f) : (features[13] < 0x1.58791a0000000p-10f ? -0x1.5e93420000000p-5f : -0x1.eb1b120000000p-8f))));
            /* Tree 18: preserve sequential float32 accumulation. */
            score += (features[2] < 0x1.8cfc700000000p-1f ? (features[156] < 0x1.62e4300000000p-1f ? (features[100] < 0x1.6a09e60000000p-1f ? (features[18] < 0x1.1a1f580000000p-1f ? -0x1.08de600000000p-8f : -0x1.90d83e0000000p-6f) : (features[50] < 0x1.f7a65c0000000p+0f ? 0x1.2cfe060000000p-7f : -0x1.5308e20000000p-5f)) : (features[93] < 0x1.bb67ae0000000p-1f ? 0x1.2d1e880000000p-7f : 0x1.47a3920000000p-5f)) : (features[70] < 0x1.aaaaaa0000000p-2f ? (features[10] < 0x1.6d0ac60000000p+2f ? (features[158] < 0x1.193ea80000000p+1f ? -0x1.39c33a0000000p-7f : 0x1.566d7a0000000p-6f) : (features[63] < 0x1.6aaaaa0000000p-2f ? 0x1.9a89ee0000000p-7f : -0x1.6c53800000000p-5f)) : (features[162] < 0x1.7b425e0000000p-3f ? (features[21] < 0x1.7008480000000p-9f ? -0x1.51d0d60000000p-6f : 0x1.49409e0000000p-10f) : (features[65] < 0x1.27350c0000000p-6f ? -0x1.51d0d60000000p-6f : -0x1.2ac24a0000000p-5f))));
            /* Tree 19: preserve sequential float32 accumulation. */
            score += (features[83] < 0x1.b6db6e0000000p-2f ? (features[67] < 0x1.0000000000000p+0f ? (features[102] < 0x1.c466680000000p+4f ? (features[15] < 0x1.5555560000000p-2f ? -0x1.dfc7f60000000p-8f : 0x1.24695c0000000p-7f) : (features[160] < 0x1.ab68a00000000p-5f ? 0x1.3ce7120000000p-8f : 0x1.2dd3340000000p-5f)) : (features[60] < 0x1.0000000000000p-1f ? (features[160] < 0x1.8618620000000p-4f ? -0x1.16da240000000p-6f : 0x1.2d9f9c0000000p-6f) : -0x1.6354120000000p-5f)) : (features[158] < 0x1.193ea80000000p+1f ? -0x1.52f7a40000000p-5f : 0x1.cc0d2a0000000p-6f));
            /* Tree 20: preserve sequential float32 accumulation. */
            score += (!(features[53] >= 0x1.0000000000000p+0f) ? (!(features[2] >= 0x1.781b2a0000000p-1f) ? (features[2] < 0x1.042ab40000000p-1f ? (features[84] < 0x1.6666660000000p-1f ? -0x1.28d52e0000000p-5f : 0x1.93835a0000000p-9f) : (features[142] < 0x1.99999a0000000p-3f ? -0x1.302b460000000p-6f : 0x1.3e456c0000000p-7f)) : (features[10] < 0x1.9d3bb60000000p+2f ? (features[141] < 0x1.5aa1640000000p+1f ? -0x1.3219a40000000p-9f : -0x1.e642040000000p-6f) : (features[160] < 0x1.ab68a00000000p-5f ? -0x1.3f63de0000000p-15f : 0x1.0e5d7c0000000p-6f))) : (features[158] < 0x1.bf8d900000000p+1f ? (features[160] < 0x1.d316740000000p-2f ? -0x1.3fddb40000000p-5f : (!(features[3] >= 0x1.6b957c0000000p-10f) ? 0x1.3f450c0000000p-8f : 0x1.40f89a0000000p-6f)) : (features[114] < 0x1.4cefb80000000p+3f ? (features[154] < 0x1.3333340000000p-1f ? 0x1.40f89a0000000p-6f : 0x1.52f8a60000000p-5f) : 0x1.40f89a0000000p-6f)));
            /* Tree 21: preserve sequential float32 accumulation. */
            score += (features[83] < 0x1.b6db6e0000000p-2f ? (features[67] < 0x1.0000000000000p+0f ? (features[110] < 0x1.2092c20000000p+3f ? (features[4] < 0x1.0000000000000p+0f ? -0x1.1568180000000p-6f : -0x1.c641b20000000p-11f) : (features[140] < 0x1.22c5580000000p+2f ? 0x1.9340780000000p-7f : -0x1.cfc9740000000p-6f)) : (features[60] < 0x1.0000000000000p-1f ? (features[13] < 0x1.5186440000000p-9f ? 0x1.fc19fc0000000p-6f : -0x1.1b952a0000000p-7f) : -0x1.5d4aaa0000000p-5f)) : (features[158] < 0x1.193ea80000000p+1f ? -0x1.4c87600000000p-5f : 0x1.c9d5220000000p-6f));
            /* Tree 22: preserve sequential float32 accumulation. */
            score += (!(features[53] >= 0x1.0000000000000p+0f) ? (!(features[2] >= 0x1.72c1100000000p-1f) ? (features[2] < 0x1.042ab40000000p-1f ? (features[84] < 0x1.6666660000000p-1f ? -0x1.2049e60000000p-5f : 0x1.d924680000000p-9f) : (features[31] < -0x1.3333340000000p-1f ? -0x1.e8ea3c0000000p-8f : -0x1.aa99a00000000p-6f)) : (features[10] < 0x1.9d3bb60000000p+2f ? (features[141] < 0x1.5aa1640000000p+1f ? -0x1.659e640000000p-9f : -0x1.cc831a0000000p-6f) : (features[154] < 0x1.8000000000000p-1f ? 0x1.7f53a20000000p-7f : -0x1.3bae720000000p-5f))) : (features[77] < 0x1.8618620000000p-5f ? (features[6] < 0x1.5555560000000p-3f ? 0x1.9f5b360000000p-6f : -0x1.29324c0000000p-5f) : (features[103] < 0x1.6e66460000000p+1f ? (features[80] < 0x1.dc47720000000p-4f ? -0x1.dcb29c0000000p-7f : 0x1.18338e0000000p-6f) : (features[63] < 0x1.579fca0000000p-3f ? 0x1.4636220000000p-5f : 0x1.e66c120000000p-13f))));
            /* Tree 23: preserve sequential float32 accumulation. */
            score += (features[83] < 0x1.b6db6e0000000p-2f ? (features[67] < 0x1.0000000000000p+0f ? (features[110] < 0x1.2092c20000000p+3f ? (features[70] < 0x1.aaaaaa0000000p-2f ? -0x1.6ddfee0000000p-9f : -0x1.8d334e0000000p-6f) : (features[141] < 0x1.3e116c0000000p+1f ? 0x1.c333be0000000p-7f : -0x1.e8ec9a0000000p-8f)) : (features[60] < 0x1.0000000000000p-1f ? (features[13] < 0x1.5186440000000p-9f ? 0x1.e7d8580000000p-6f : -0x1.c1359a0000000p-8f) : -0x1.5735820000000p-5f)) : (features[158] < 0x1.193ea80000000p+1f ? -0x1.4643a60000000p-5f : 0x1.c418b20000000p-6f));
            /* Tree 24: preserve sequential float32 accumulation. */
            score += (!(features[53] >= 0x1.0000000000000p+0f) ? (!(features[2] >= 0x1.4637640000000p-1f) ? (!(features[53] >= 0x1.0000000000000p-2f) ? (features[34] < -0x1.6db6dc0000000p-1f ? -0x1.1a7ca20000000p-6f : -0x1.130b5e0000000p-5f) : (features[31] < -0x1.5555540000000p-2f ? 0x1.1a384a0000000p-5f : -0x1.7fefea0000000p-6f)) : (features[10] < 0x1.876ac60000000p+2f ? (features[158] < 0x1.26bb1c0000000p+1f ? -0x1.33c8680000000p-7f : 0x1.1ae5060000000p-6f) : (features[162] < 0x1.d1745e0000000p-3f ? 0x1.4c0f4e0000000p-7f : -0x1.95acb00000000p-7f))) : (features[158] < 0x1.bf8d900000000p+1f ? (features[82] < 0x1.76fc640000000p-4f ? -0x1.273be60000000p-5f : 0x1.4887ee0000000p-6f) : (features[114] < 0x1.4cefb80000000p+3f ? (features[154] < 0x1.3333340000000p-1f ? 0x1.4887ee0000000p-6f : 0x1.46b9e80000000p-5f) : 0x1.4887ee0000000p-6f)));
            /* Tree 25: preserve sequential float32 accumulation. */
            score += (features[83] < 0x1.b6db6e0000000p-2f ? (features[80] < 0x1.6ece540000000p-4f ? (features[162] < 0x1.e1e1e20000000p-3f ? (features[15] < 0x1.5555560000000p-2f ? -0x1.9487b60000000p-8f : 0x1.405b7e0000000p-7f) : (features[31] < -0x1.3333340000000p-1f ? -0x1.e4826e0000000p-8f : -0x1.fbad780000000p-6f)) : (features[145] < 0x1.435e500000000p-3f ? (features[82] < 0x1.745d180000000p-4f ? -0x1.60ab7a0000000p-6f : 0x1.89ab760000000p-7f) : (features[160] < 0x1.99999a0000000p-6f ? 0x1.e000da0000000p-10f : 0x1.1d43a20000000p-5f))) : (features[158] < 0x1.193ea80000000p+1f ? -0x1.41ad460000000p-5f : 0x1.b3f55c0000000p-6f));
            /* Tree 26: preserve sequential float32 accumulation. */
            score += (features[2] < 0x1.944ed00000000p-1f ? (features[156] < 0x1.62e4300000000p-1f ? (features[100] < 0x1.89bd640000000p-1f ? (features[21] < 0x1.27fc6a0000000p-12f ? -0x1.a1debc0000000p-6f : -0x1.bc5e420000000p-9f) : (features[50] < 0x1.f7a65c0000000p+0f ? 0x1.4036600000000p-7f : -0x1.39b5a20000000p-5f)) : (features[103] < 0x1.ee924a0000000p+1f ? 0x1.9479b00000000p-7f : 0x1.367e340000000p-5f)) : (features[10] < 0x1.876ac60000000p+2f ? (features[158] < 0x1.26bb1c0000000p+1f ? (features[154] < 0x1.4000000000000p-1f ? -0x1.52411e0000000p-8f : -0x1.49aacc0000000p-5f) : (features[102] < 0x1.9072f60000000p+4f ? 0x1.b1674a0000000p-8f : 0x1.001f380000000p-5f)) : (features[114] < 0x1.5a31760000000p+3f ? (features[5] < 0x1.99999a0000000p-4f ? 0x1.5c328a0000000p-8f : 0x1.439af20000000p-6f) : (features[13] < 0x1.84f00c0000000p-10f ? -0x1.43c1c60000000p-5f : -0x1.3e084e0000000p-7f))));
            /* Tree 27: preserve sequential float32 accumulation. */
            score += (features[83] < 0x1.b6db6e0000000p-2f ? (features[67] < 0x1.0000000000000p+0f ? (features[110] < 0x1.4078be0000000p+3f ? (features[10] < 0x1.b8259e0000000p+2f ? -0x1.08be060000000p-7f : 0x1.ad464e0000000p-8f) : (features[147] < 0x1.99999a0000000p-3f ? 0x1.9ef0b20000000p-7f : -0x1.72e6840000000p-5f)) : (features[60] < 0x1.0000000000000p-1f ? (features[18] < 0x1.5473400000000p-2f ? 0x1.0b422c0000000p-5f : -0x1.b134c40000000p-9f) : -0x1.4d8dcc0000000p-5f)) : (features[158] < 0x1.193ea80000000p+1f ? -0x1.3b9e0c0000000p-5f : 0x1.a180780000000p-6f));
            /* Tree 28: preserve sequential float32 accumulation. */
            score += (!(features[53] >= 0x1.0000000000000p+0f) ? (!(features[2] >= 0x1.781b2a0000000p-1f) ? (features[21] < 0x1.c6c93a0000000p-13f ? (features[85] < 0x1.bbbbbc0000000p-3f ? -0x1.124ea20000000p-5f : 0x1.a4c6ac0000000p-6f) : (features[100] < 0x1.0c9f540000000p+2f ? -0x1.c014fe0000000p-8f : -0x1.f90f9e0000000p-6f)) : (features[10] < 0x1.b726480000000p+2f ? (features[42] < 0x1.aa85ae0000000p+1f ? -0x1.2457a40000000p-12f : -0x1.796ce00000000p-6f) : (features[114] < 0x1.5a31760000000p+3f ? 0x1.0ece800000000p-6f : -0x1.1488140000000p-6f))) : (features[158] < 0x1.bf8d900000000p+1f ? (features[160] < 0x1.d316740000000p-2f ? -0x1.216fe60000000p-5f : 0x1.3fb64a0000000p-6f) : (features[103] < 0x1.d2de9c0000000p+1f ? 0x1.3fb64a0000000p-6f : (features[154] < 0x1.3333340000000p-1f ? 0x1.3fb64a0000000p-6f : 0x1.3d433a0000000p-5f))));
            /* Tree 29: preserve sequential float32 accumulation. */
            score += (features[83] < 0x1.b6db6e0000000p-2f ? (features[67] < 0x1.e666660000000p-1f ? (features[102] < 0x1.c466680000000p+4f ? (features[15] < 0x1.5555560000000p-2f ? -0x1.a8f3aa0000000p-8f : 0x1.ef21720000000p-8f) : (features[160] < 0x1.ab68a00000000p-5f ? 0x1.03c71a0000000p-8f : 0x1.13e7600000000p-5f)) : (features[60] < 0x1.0000000000000p-1f ? (features[13] < 0x1.5186440000000p-9f ? 0x1.b788780000000p-6f : -0x1.af4f240000000p-8f) : -0x1.4880c40000000p-5f)) : (features[158] < 0x1.193ea80000000p+1f ? -0x1.373bca0000000p-5f : 0x1.9590140000000p-6f));
            /* Tree 30: preserve sequential float32 accumulation. */
            score += (!(features[53] >= 0x1.0000000000000p+0f) ? (!(features[2] >= 0x1.4637640000000p-1f) ? (!(features[53] >= 0x1.0000000000000p-2f) ? (features[34] < -0x1.6db6dc0000000p-1f ? -0x1.01c4b80000000p-6f : -0x1.02d5220000000p-5f) : (features[12] < 0x1.6816820000000p-4f ? 0x1.1a97140000000p-5f : -0x1.5ea2120000000p-6f)) : (features[10] < 0x1.9d3bb60000000p+2f ? (features[2] < 0x1.dd6dde0000000p-1f ? -0x1.7a8a840000000p-7f : 0x1.f37b680000000p-10f) : (features[77] < 0x1.0000000000000p-1f ? 0x1.3e7e920000000p-7f : -0x1.17edec0000000p-5f))) : (features[100] < 0x1.6939460000000p+2f ? (features[77] < 0x1.af286c0000000p-5f ? -0x1.199f3c0000000p-5f : (features[44] < 0x1.cbc14e0000000p-3f ? 0x1.fb61780000000p-6f : -0x1.7a60880000000p-6f)) : (features[103] < 0x1.6e66460000000p+1f ? (features[77] < 0x1.99999a0000000p-4f ? 0x1.55477c0000000p-6f : -0x1.6395ae0000000p-7f) : (features[154] < 0x1.3333340000000p-1f ? 0x1.4bde8a0000000p-7f : 0x1.35c6d00000000p-5f))));
            /* Tree 31: preserve sequential float32 accumulation. */
            score += (features[110] < 0x1.d376100000000p+2f ? (features[154] < 0x1.3333340000000p-1f ? (features[44] < 0x1.3716ae0000000p-5f ? (features[19] < 0x1.6a6a780000000p-6f ? -0x1.acb4920000000p-6f : -0x1.1be6660000000p-7f) : (features[9] < 0x1.2c79720000000p+3f ? -0x1.4bac7a0000000p-8f : 0x1.8ac0080000000p-6f)) : (features[43] < 0x1.2bb5120000000p-3f ? -0x1.3bcbaa0000000p-5f : (features[93] < 0x1.4629a20000000p+3f ? -0x1.883aac0000000p-10f : 0x1.0698980000000p-5f))) : (features[67] < 0x1.e666660000000p-1f ? (features[10] < 0x1.6d0ac60000000p+2f ? (features[139] < 0x1.4000000000000p-1f ? -0x1.f2c42e0000000p-8f : 0x1.002dc60000000p-5f) : (features[141] < 0x1.62e4300000000p+1f ? 0x1.9793620000000p-7f : -0x1.d6a2d60000000p-7f)) : (features[60] < 0x1.0000000000000p-1f ? (features[41] < 0x1.cab0c00000000p+1f ? 0x1.49b0e60000000p-6f : -0x1.c85fe20000000p-7f) : -0x1.44e2e00000000p-5f)));
            /* Tree 32: preserve sequential float32 accumulation. */
            score += (!(features[53] >= 0x1.0000000000000p+0f) ? (!(features[2] >= 0x1.8fd1440000000p-1f) ? (features[100] < 0x1.7127ae0000000p-1f ? (features[18] < 0x1.1a1f580000000p-1f ? -0x1.d96c520000000p-9f : -0x1.4489420000000p-6f) : (features[156] < 0x1.62e4300000000p-1f ? -0x1.2b29e80000000p-5f : 0x1.7df3ec0000000p-8f)) : (features[10] < 0x1.b726480000000p+2f ? (features[42] < 0x1.aa85ae0000000p+1f ? 0x1.5b43b80000000p-11f : -0x1.8231c20000000p-6f) : (features[114] < 0x1.5a31760000000p+3f ? 0x1.0a8ca40000000p-6f : -0x1.3fdcc20000000p-6f))) : (features[77] < 0x1.8618620000000p-5f ? (features[6] < 0x1.5555560000000p-3f ? 0x1.8a72520000000p-6f : -0x1.f1a0f60000000p-6f) : (features[103] < 0x1.6e66460000000p+1f ? (features[80] < 0x1.dc47720000000p-4f ? -0x1.df15ee0000000p-7f : 0x1.0ade160000000p-6f) : (features[63] < 0x1.579fca0000000p-3f ? 0x1.2c0bd00000000p-5f : -0x1.280f7e0000000p-8f))));
            /* Tree 33: preserve sequential float32 accumulation. */
            score += (features[142] < 0x1.99999a0000000p-3f ? (!(features[2] >= 0x1.781b2a0000000p-1f) ? (!(features[53] >= 0x1.0000000000000p-2f) ? (features[100] < 0x1.6a09e60000000p-1f ? -0x1.e6052e0000000p-7f : -0x1.25eef00000000p-5f) : (features[160] < 0x1.eb1a200000000p-1f ? 0x1.e189f40000000p-6f : -0x1.830cf40000000p-7f)) : (features[18] < 0x1.3a3caa0000000p-1f ? (features[70] < 0x1.aaaaaa0000000p-2f ? 0x1.96bd800000000p-8f : -0x1.1288140000000p-6f) : (features[55] < 0x1.9c04200000000p+0f ? -0x1.049a3e0000000p-6f : -0x1.1242d60000000p-9f))) : (features[147] < 0x1.99999a0000000p-3f ? (features[114] < 0x1.5a31760000000p+3f ? (features[114] < 0x1.f306d20000000p+2f ? 0x1.9d16d00000000p-7f : 0x1.120e940000000p-5f) : (features[2] < 0x1.b5b9b20000000p-1f ? 0x1.86f0700000000p-6f : -0x1.478f3c0000000p-6f)) : (features[70] < 0x1.5555560000000p-3f ? -0x1.79fa3c0000000p-5f : -0x1.fc31300000000p-10f)));
            /* Tree 34: preserve sequential float32 accumulation. */
            score += (features[83] < 0x1.b6db6e0000000p-2f ? (features[67] < 0x1.0000000000000p+0f ? (features[110] < 0x1.4078be0000000p+3f ? (features[10] < 0x1.b8259e0000000p+2f ? -0x1.dc60c20000000p-8f : 0x1.86b34e0000000p-8f) : (features[141] < 0x1.3e116c0000000p+1f ? 0x1.c4f1060000000p-7f : -0x1.d124000000000p-8f)) : (features[60] < 0x1.0000000000000p-1f ? (features[62] < 0x1.cbc48a0000000p+2f ? 0x1.12c2f00000000p-10f : 0x1.fcf1c60000000p-6f) : -0x1.3fa4a60000000p-5f)) : (features[158] < 0x1.193ea80000000p+1f ? -0x1.2fad200000000p-5f : 0x1.9c8ee80000000p-6f));
            /* Tree 35: preserve sequential float32 accumulation. */
            score += (!(features[53] >= 0x1.0000000000000p+0f) ? (!(features[2] >= 0x1.4637640000000p-1f) ? (!(features[53] >= 0x1.0000000000000p-2f) ? (features[34] < -0x1.6db6dc0000000p-1f ? -0x1.c5d9d00000000p-7f : -0x1.ef0b760000000p-6f) : (features[31] < -0x1.5555540000000p-2f ? 0x1.06c86c0000000p-5f : -0x1.7d2ef00000000p-6f)) : (features[15] < 0x1.5555560000000p-2f ? (features[24] < 0x1.1a636e0000000p-4f ? -0x1.4cac4c0000000p-7f : 0x1.bbfe9a0000000p-8f) : (features[114] < 0x1.5a31760000000p+3f ? 0x1.243aaa0000000p-7f : -0x1.3e34540000000p-6f))) : (features[55] < 0x1.193ea80000000p+0f ? (features[78] < 0x1.6b17ba0000000p+2f ? (features[0] < 0x1.717f840000000p+1f ? 0x1.d3b7ba0000000p-6f : 0x1.63d0480000000p-8f) : -0x1.047c420000000p-5f) : (features[93] < 0x1.0000000000000p-1f ? -0x1.6050920000000p-9f : (features[114] < 0x1.4cefb80000000p+3f ? 0x1.29c8420000000p-5f : 0x1.27437e0000000p-7f))));
            /* Tree 36: preserve sequential float32 accumulation. */
            score += (features[83] < 0x1.b6db6e0000000p-2f ? (features[67] < 0x1.e666660000000p-1f ? (features[110] < 0x1.3086480000000p+3f ? (features[70] < 0x1.aaaaaa0000000p-2f ? -0x1.cf6f7a0000000p-10f : -0x1.4d347a0000000p-6f) : (features[141] < 0x1.3e116c0000000p+1f ? 0x1.a137740000000p-7f : -0x1.ce682c0000000p-8f)) : (features[60] < 0x1.0000000000000p-1f ? (features[13] < 0x1.5186440000000p-9f ? 0x1.996e380000000p-6f : -0x1.8532fa0000000p-9f) : -0x1.3c74780000000p-5f)) : (features[158] < 0x1.193ea80000000p+1f ? -0x1.2cb0140000000p-5f : 0x1.9d16240000000p-6f));
            /* Tree 37: preserve sequential float32 accumulation. */
            score += (features[158] < 0x1.26bb1c0000000p+1f ? (features[154] < 0x1.8000000000000p-1f ? (features[162] < 0x1.f49f4a0000000p-3f ? (features[15] < 0x1.bbbbbc0000000p-2f ? -0x1.87325e0000000p-9f : 0x1.2dd1a20000000p-7f) : (features[63] < 0x1.6aaaaa0000000p-2f ? -0x1.40d0300000000p-7f : -0x1.2fcc860000000p-5f)) : -0x1.3ab69e0000000p-5f) : (features[102] < 0x1.9072f60000000p+4f ? (features[61] < 0x1.a556940000000p+2f ? (features[124] < 0x1.26bb1c0000000p+1f ? 0x1.f2c4d80000000p-6f : 0x1.2dd1a20000000p-7f) : (features[74] < 0x1.0822f80000000p+2f ? 0x1.1c95560000000p-5f : 0x1.2dd1a20000000p-7f)) : (features[160] < 0x1.ab68a00000000p-5f ? (features[20] < 0x1.0424fa0000000p-3f ? 0x1.2dd1a20000000p-7f : 0x1.00a6920000000p-5f) : (features[88] < 0x1.98526c0000000p-4f ? 0x1.2dd1a20000000p-7f : 0x1.2635020000000p-5f))));
            /* Tree 38: preserve sequential float32 accumulation. */
            score += (features[110] < 0x1.d376100000000p+2f ? (features[154] < 0x1.3333340000000p-1f ? (features[74] < 0x1.cab0c00000000p+0f ? (features[24] < 0x1.1bd4180000000p-11f ? -0x1.decaa60000000p-6f : -0x1.d7b4080000000p-8f) : (!(features[2] >= 0x1.3fd9300000000p-1f) ? -0x1.3f65880000000p-7f : 0x1.add1a60000000p-6f)) : (features[43] < 0x1.2bb5120000000p-3f ? -0x1.2fcee20000000p-5f : (features[50] < 0x1.2595400000000p+2f ? 0x1.01dcda0000000p-5f : 0x1.d330400000000p-12f))) : (features[67] < 0x1.e666660000000p-1f ? (features[15] < 0x1.6666660000000p-2f ? (features[158] < 0x1.193ea80000000p+1f ? -0x1.53129a0000000p-8f : 0x1.ab40020000000p-6f) : (features[114] < 0x1.5a31760000000p+3f ? 0x1.b19c300000000p-7f : -0x1.56c1fc0000000p-6f)) : (features[60] < 0x1.0000000000000p-1f ? (features[114] < 0x1.259c580000000p+3f ? 0x1.3185c80000000p-6f : -0x1.1e2eba0000000p-8f) : -0x1.37dc700000000p-5f)));
            /* Tree 39: preserve sequential float32 accumulation. */
            score += (!(features[53] >= 0x1.0000000000000p-2f) ? (!(features[2] >= 0x1.42a8480000000p-1f) ? (features[31] < -0x1.b6db6e0000000p-1f ? (features[140] < 0x1.0c234e0000000p+2f ? -0x1.3c742e0000000p-6f : 0x1.3df5dc0000000p-6f) : (features[19] < 0x1.b80d2a0000000p-3f ? -0x1.f9822c0000000p-6f : -0x1.013c520000000p-9f)) : (features[10] < 0x1.b726480000000p+2f ? (features[41] < 0x1.507ace0000000p+2f ? -0x1.3c07700000000p-10f : -0x1.7fb3b20000000p-6f) : (features[154] < 0x1.3333340000000p-1f ? 0x1.82e3460000000p-7f : -0x1.3d934a0000000p-5f))) : (features[158] < 0x1.bf8d900000000p+1f ? (features[82] < 0x1.611a7c0000000p-4f ? (features[65] < 0x1.e9131a0000000p-8f ? -0x1.57d4980000000p-5f : 0x1.84e9580000000p-11f) : (features[127] < 0x1.69696a0000000p-3f ? -0x1.010fc60000000p-6f : 0x1.fdf7160000000p-7f)) : (features[64] < 0x1.155a3c0000000p-3f ? (features[114] < 0x1.4cefb80000000p+3f ? 0x1.2503e20000000p-5f : 0x1.fdf7160000000p-7f) : (features[84] < 0x1.3333340000000p-1f ? 0x1.ed79160000000p-6f : 0x1.fdf7160000000p-7f))));
            /* Tree 40: preserve sequential float32 accumulation. */
            score += (features[83] < 0x1.b6db6e0000000p-2f ? (features[80] < 0x1.6ece540000000p-4f ? (features[162] < 0x1.f49f4a0000000p-3f ? (features[15] < 0x1.bbbbbc0000000p-2f ? -0x1.c31a940000000p-9f : 0x1.2b32340000000p-7f) : (features[31] < -0x1.3333340000000p-1f ? -0x1.939f080000000p-8f : -0x1.c262f20000000p-6f)) : (features[160] < 0x1.8618620000000p-5f ? (features[95] < 0x1.5db5e00000000p+3f ? -0x1.97316e0000000p-6f : 0x1.aec8aa0000000p-6f) : (features[110] < 0x1.6d757c0000000p+3f ? 0x1.5dbafa0000000p-7f : 0x1.05822e0000000p-5f))) : (features[158] < 0x1.193ea80000000p+1f ? -0x1.2686980000000p-5f : 0x1.7d42b20000000p-6f));
            /* Tree 41: preserve sequential float32 accumulation. */
            score += (features[2] < 0x1.9a3c660000000p-1f ? (features[156] < 0x1.62e4300000000p-1f ? (features[102] < 0x1.b599e00000000p+3f ? (features[87] < 0x1.bc7bc80000000p-2f ? -0x1.8976ea0000000p-7f : 0x1.0d172e0000000p-7f) : (features[97] < 0x1.4000000000000p+1f ? -0x1.1977d40000000p-5f : 0x1.7179780000000p-12f)) : (features[106] < 0x1.05a4c20000000p+0f ? 0x1.0d172e0000000p-7f : 0x1.1306880000000p-5f)) : (features[70] < 0x1.aaaaaa0000000p-2f ? (features[114] < 0x1.5a31760000000p+3f ? (!(features[2] >= 0x1.fda8520000000p-1f) ? 0x1.0040000000000p-8f : 0x1.65fa6c0000000p-6f) : (!(features[2] >= 0x1.f4e0b40000000p-1f) ? -0x1.56c4a40000000p-9f : -0x1.4db08c0000000p-6f)) : (features[162] < 0x1.8000000000000p-4f ? (features[22] < 0x1.2f6d2e0000000p-7f ? -0x1.be7ba00000000p-7f : 0x1.19b4440000000p-6f) : (features[5] < 0x1.5555560000000p-1f ? -0x1.e0e46e0000000p-6f : -0x1.cb65240000000p-7f))));
            /* Tree 42: preserve sequential float32 accumulation. */
            score += (features[83] < 0x1.b6db6e0000000p-2f ? (features[80] < 0x1.6ece540000000p-4f ? (features[67] < 0x1.0000000000000p+0f ? (features[15] < 0x1.5555560000000p-2f ? -0x1.82020a0000000p-8f : 0x1.87f9480000000p-8f) : (features[60] < 0x1.0000000000000p-1f ? 0x1.59bf2a0000000p-7f : -0x1.3071020000000p-5f)) : (features[160] < 0x1.8618620000000p-5f ? (features[95] < 0x1.5db5e00000000p+3f ? -0x1.8d78b20000000p-6f : 0x1.a3831e0000000p-6f) : (features[110] < 0x1.6d757c0000000p+3f ? 0x1.47edf00000000p-7f : 0x1.f9ff700000000p-6f))) : (features[158] < 0x1.193ea80000000p+1f ? -0x1.23a1de0000000p-5f : 0x1.7710660000000p-6f));
            /* Tree 43: preserve sequential float32 accumulation. */
            score += (features[2] < 0x1.944ed00000000p-1f ? (features[156] < 0x1.62e4300000000p-1f ? (features[100] < 0x1.89bd640000000p-1f ? (features[87] < 0x1.bc7bc80000000p-2f ? -0x1.8993840000000p-7f : 0x1.20a28a0000000p-7f) : (features[85] < 0x1.6666660000000p-2f ? -0x1.19f2c20000000p-5f : 0x1.3ca1720000000p-7f)) : (features[103] < 0x1.ee924a0000000p+1f ? 0x1.6d27460000000p-7f : 0x1.183f8a0000000p-5f)) : (features[70] < 0x1.aaaaaa0000000p-2f ? (features[9] < 0x1.b5a86e0000000p+2f ? (features[139] < 0x1.1c71c80000000p-1f ? -0x1.8666200000000p-7f : 0x1.c2cd380000000p-6f) : (features[114] < 0x1.5a31760000000p+3f ? 0x1.267d9e0000000p-7f : -0x1.51544e0000000p-7f)) : (features[64] < 0x1.5555560000000p-2f ? (features[108] < 0x1.78c0880000000p+0f ? -0x1.8191620000000p-6f : -0x1.baf3ca0000000p-9f) : (features[9] < 0x1.1881320000000p+3f ? -0x1.788ab00000000p-7f : 0x1.f21b720000000p-6f))));
            /* Tree 44: preserve sequential float32 accumulation. */
            score += (features[83] < 0x1.b6db6e0000000p-2f ? (features[67] < 0x1.e666660000000p-1f ? (features[110] < 0x1.4078be0000000p+3f ? (features[6] < 0x1.8000000000000p-1f ? -0x1.c077740000000p-7f : -0x1.c6c9760000000p-12f) : (features[147] < 0x1.99999a0000000p-3f ? 0x1.5023580000000p-7f : -0x1.55eaec0000000p-5f)) : (features[60] < 0x1.0000000000000p-1f ? (features[114] < 0x1.62e4700000000p+3f ? 0x1.2583800000000p-6f : -0x1.4f5d9a0000000p-7f) : -0x1.2e98480000000p-5f)) : (features[158] < 0x1.193ea80000000p+1f ? -0x1.20e1260000000p-5f : 0x1.700dec0000000p-6f));
            /* Tree 45: preserve sequential float32 accumulation. */
            score += (!(features[53] >= 0x1.0000000000000p+0f) ? (!(features[2] >= 0x1.944ed00000000p-1f) ? (features[100] < 0x1.0c9f540000000p+2f ? (features[21] < 0x1.27fc6a0000000p-12f ? -0x1.67a5f00000000p-6f : -0x1.bae7e20000000p-9f) : (features[139] < 0x1.b6db6e0000000p-2f ? -0x1.0b864c0000000p-5f : 0x1.9207f60000000p-6f)) : (features[10] < 0x1.b726480000000p+2f ? (features[42] < 0x1.aa85ae0000000p+1f ? 0x1.02430a0000000p-11f : -0x1.5df3060000000p-6f) : (features[11] < 0x1.b65e2e0000000p-9f ? -0x1.25bf580000000p-5f : 0x1.b3e7de0000000p-7f))) : (features[158] < 0x1.bf8d900000000p+1f ? (features[160] < 0x1.d316740000000p-2f ? -0x1.0c77ce0000000p-5f : 0x1.083de40000000p-6f) : (features[154] < 0x1.3333340000000p-1f ? 0x1.083de40000000p-6f : (features[114] < 0x1.4cefb80000000p+3f ? 0x1.2345c20000000p-5f : 0x1.083de40000000p-6f))));
            /* Tree 46: preserve sequential float32 accumulation. */
            score += (features[142] < 0x1.99999a0000000p-3f ? (features[154] < 0x1.6db6dc0000000p-1f ? (features[63] < 0x1.6aaaaa0000000p-2f ? (features[18] < 0x1.3a3caa0000000p-1f ? 0x1.c6e3040000000p-9f : -0x1.577f9c0000000p-7f) : -0x1.256e880000000p-5f) : (features[158] < 0x1.bf8d900000000p+1f ? (features[140] < 0x1.26bb1c0000000p+1f ? -0x1.20ad8e0000000p-7f : -0x1.3712d00000000p-5f) : (features[102] < 0x1.d7a0f40000000p+3f ? -0x1.20ad8e0000000p-7f : 0x1.e648320000000p-6f))) : (features[149] < 0x1.6db6dc0000000p-1f ? -0x1.6443040000000p-5f : (features[13] < 0x1.6914740000000p-8f ? (features[104] < 0x1.99999a0000000p-2f ? -0x1.e0da9c0000000p-7f : 0x1.09ca400000000p-5f) : (features[95] < 0x1.501bba0000000p+3f ? 0x1.83bc000000000p-8f : 0x1.f1786a0000000p-6f))));
            /* Tree 47: preserve sequential float32 accumulation. */
            score += (features[110] < 0x1.d376100000000p+2f ? (features[154] < 0x1.3333340000000p-1f ? (features[74] < 0x1.cab0c00000000p+0f ? (features[97] < 0x1.11acee0000000p-3f ? -0x1.07b5360000000p-10f : -0x1.a201d20000000p-7f) : (!(features[2] >= 0x1.3fd9300000000p-1f) ? -0x1.1caad00000000p-7f : 0x1.7fcd3e0000000p-6f)) : (features[43] < 0x1.2bb5120000000p-3f ? -0x1.2333340000000p-5f : (features[50] < 0x1.2595400000000p+2f ? 0x1.e16c280000000p-6f : 0x1.319f680000000p-9f))) : (features[67] < 0x1.e666660000000p-1f ? (features[15] < 0x1.6666660000000p-2f ? (features[158] < 0x1.193ea80000000p+1f ? -0x1.2872300000000p-8f : 0x1.86d5600000000p-6f) : (features[140] < 0x1.b35a700000000p+1f ? 0x1.a07ef60000000p-6f : 0x1.dc33d40000000p-8f)) : (features[60] < 0x1.0000000000000p-1f ? (features[114] < 0x1.259c580000000p+3f ? 0x1.499d9c0000000p-6f : -0x1.763f3c0000000p-8f) : -0x1.2ac0580000000p-5f)));
            /* Tree 48: preserve sequential float32 accumulation. */
            score += (features[142] < 0x1.99999a0000000p-3f ? (features[154] < 0x1.6db6dc0000000p-1f ? (features[63] < 0x1.6aaaaa0000000p-2f ? (features[18] < 0x1.3a3caa0000000p-1f ? 0x1.991fea0000000p-9f : -0x1.48d3580000000p-7f) : -0x1.1ee14c0000000p-5f) : (features[158] < 0x1.bf8d900000000p+1f ? (features[140] < 0x1.26bb1c0000000p+1f ? -0x1.168d080000000p-7f : -0x1.3289f40000000p-5f) : (!(features[53] >= 0x1.99999a0000000p-3f) ? -0x1.168d080000000p-7f : 0x1.e67c6a0000000p-6f))) : (features[149] < 0x1.6db6dc0000000p-1f ? -0x1.5a75fa0000000p-5f : (features[9] < 0x1.f3fe020000000p+2f ? (features[95] < 0x1.4a01140000000p+3f ? 0x1.c9016a0000000p-10f : 0x1.d8600e0000000p-6f) : (features[135] < 0x1.24924a0000000p-2f ? -0x1.1b1afc0000000p-5f : 0x1.d39a920000000p-6f))));
            /* Tree 49: preserve sequential float32 accumulation. */
            score += (features[142] < 0x1.69696a0000000p-3f ? (features[154] < 0x1.6db6dc0000000p-1f ? (features[63] < 0x1.6aaaaa0000000p-2f ? (features[18] < 0x1.3a3caa0000000p-1f ? 0x1.82be720000000p-9f : -0x1.42a9720000000p-7f) : -0x1.1d2df80000000p-5f) : (features[158] < 0x1.bf8d900000000p+1f ? (features[140] < 0x1.26bb1c0000000p+1f ? -0x1.11a0580000000p-7f : -0x1.2f72e40000000p-5f) : (!(features[53] >= 0x1.99999a0000000p-3f) ? -0x1.11a0580000000p-7f : 0x1.e05fea0000000p-6f))) : (features[149] < 0x1.6db6dc0000000p-1f ? -0x1.53c7120000000p-5f : (features[61] < 0x1.9deec60000000p+2f ? (features[95] < 0x1.6cae8a0000000p+3f ? 0x1.c2de480000000p-8f : 0x1.ffecda0000000p-6f) : (features[95] < 0x1.0d83bc0000000p+2f ? -0x1.7d9f6a0000000p-11f : 0x1.24517a0000000p-5f))));
            /* Tree 50: preserve sequential float32 accumulation. */
            score += (features[110] < 0x1.d376100000000p+2f ? (features[66] < 0x1.99999a0000000p-3f ? (features[154] < 0x1.3333340000000p-1f ? (features[21] < 0x1.c6c93a0000000p-13f ? -0x1.50a6b60000000p-6f : -0x1.98494c0000000p-8f) : (features[43] < 0x1.a5a5a60000000p-3f ? -0x1.1a708c0000000p-5f : 0x1.f27bc40000000p-7f)) : (features[13] < 0x1.12358e0000000p-7f ? (features[2] < 0x1.2662aa0000000p-1f ? -0x1.ad73fc0000000p-6f : 0x1.8a342e0000000p-6f) : (features[70] < 0x1.5555560000000p-3f ? 0x1.f00f100000000p-9f : -0x1.7700de0000000p-6f))) : (features[67] < 0x1.e666660000000p-1f ? (features[15] < 0x1.6666660000000p-2f ? (features[158] < 0x1.193ea80000000p+1f ? -0x1.1905ea0000000p-8f : 0x1.6d5ac20000000p-6f) : (features[114] < 0x1.5a31760000000p+3f ? 0x1.7055560000000p-7f : -0x1.4a32aa0000000p-6f)) : (features[60] < 0x1.0000000000000p-1f ? (features[114] < 0x1.259c580000000p+3f ? 0x1.15aae80000000p-6f : -0x1.8a1dfa0000000p-8f) : -0x1.2517120000000p-5f)));
            /* Tree 51: preserve sequential float32 accumulation. */
            score += (features[70] < 0x1.aaaaaa0000000p-2f ? (features[2] < 0x1.8fd1440000000p-1f ? (features[85] < 0x1.47ae140000000p-3f ? (features[100] < 0x1.89bd640000000p-1f ? -0x1.0508380000000p-7f : -0x1.1734b20000000p-5f) : (features[77] < 0x1.99999a0000000p-5f ? -0x1.e5d44e0000000p-8f : 0x1.f073240000000p-6f)) : (features[9] < 0x1.b5a86e0000000p+2f ? (features[139] < 0x1.1c71c80000000p-1f ? -0x1.6ae7340000000p-7f : 0x1.a976680000000p-6f) : (features[160] < 0x1.ab68a00000000p-5f ? -0x1.5c211a0000000p-9f : 0x1.4d48020000000p-7f))) : (features[65] < 0x1.edfd6e0000000p-8f ? (features[3] < 0x1.24924a0000000p-3f ? (features[44] < 0x1.56ebc20000000p-4f ? -0x1.03e13a0000000p-5f : 0x1.acdc620000000p-9f) : (features[2] < 0x1.ef80620000000p-1f ? 0x1.618dae0000000p-6f : -0x1.7189380000000p-7f)) : (features[142] < 0x1.5555560000000p-3f ? (features[13] < 0x1.9852f00000000p-9f ? 0x1.3ad09c0000000p-7f : -0x1.b74bb60000000p-6f) : (features[41] < 0x1.db56540000000p+1f ? -0x1.0206ce0000000p-6f : 0x1.0f06400000000p-6f))));
            /* Tree 52: preserve sequential float32 accumulation. */
            score += (features[83] < 0x1.b6db6e0000000p-2f ? (features[67] < 0x1.e666660000000p-1f ? (features[110] < 0x1.4078be0000000p+3f ? (features[6] < 0x1.8000000000000p-1f ? -0x1.ae236a0000000p-7f : -0x1.5500da0000000p-12f) : (features[141] < 0x1.3e116c0000000p+1f ? 0x1.72701a0000000p-7f : -0x1.bfcfb80000000p-8f)) : (features[60] < 0x1.0000000000000p-1f ? (features[160] < 0x1.f405fe0000000p-1f ? -0x1.6af8780000000p-9f : 0x1.5b6f280000000p-6f) : -0x1.217b1c0000000p-5f)) : (features[158] < 0x1.193ea80000000p+1f ? -0x1.1814b80000000p-5f : (features[0] < 0x1.54c9d20000000p+1f ? -0x1.52bc480000000p-9f : 0x1.62dcb20000000p-6f)));
            /* Tree 53: preserve sequential float32 accumulation. */
            score += (!(features[53] >= 0x1.0000000000000p+0f) ? (!(features[2] >= 0x1.8fd1440000000p-1f) ? (features[100] < 0x1.0c9f540000000p+2f ? (features[87] < 0x1.bc7bc80000000p-2f ? -0x1.8c74780000000p-7f : 0x1.81cd1e0000000p-8f) : (features[139] < 0x1.b6db6e0000000p-2f ? -0x1.ff0aa60000000p-6f : 0x1.7a87c80000000p-6f)) : (features[10] < 0x1.b726480000000p+2f ? (features[42] < 0x1.aa85ae0000000p+1f ? 0x1.4d5c9a0000000p-12f : -0x1.483e800000000p-6f) : (features[11] < 0x1.b65e2e0000000p-9f ? -0x1.1260360000000p-5f : 0x1.8b5da80000000p-7f))) : (features[93] < 0x1.5cc4700000000p+1f ? (features[77] < 0x1.1111120000000p-4f ? -0x1.9334720000000p-6f : (features[76] < 0x1.0000000000000p+0f ? 0x1.e479360000000p-10f : 0x1.b076c40000000p-6f)) : (features[64] < 0x1.579fca0000000p-3f ? (features[103] < 0x1.6e66460000000p+1f ? 0x1.0efa8c0000000p-7f : 0x1.1b183e0000000p-5f) : (features[4] < 0x1.0000000000000p+0f ? 0x1.7f616a0000000p-6f : -0x1.03de1e0000000p-6f))));
            /* Tree 54: preserve sequential float32 accumulation. */
            score += (features[70] < 0x1.aaaaaa0000000p-2f ? (features[83] < 0x1.b6db6e0000000p-2f ? (features[67] < 0x1.e666660000000p-1f ? (features[15] < 0x1.5555560000000p-2f ? -0x1.1ebf740000000p-9f : 0x1.03594c0000000p-7f) : (features[60] < 0x1.0000000000000p-1f ? 0x1.28355c0000000p-7f : -0x1.1de84a0000000p-5f)) : (features[158] < 0x1.193ea80000000p+1f ? -0x1.14b1e40000000p-5f : (features[0] < 0x1.54c9d20000000p+1f ? -0x1.d4b9640000000p-10f : 0x1.5ff0a40000000p-6f))) : (features[65] < 0x1.edfd6e0000000p-8f ? (features[3] < 0x1.24924a0000000p-3f ? (features[45] < 0x1.27350c0000000p-7f ? -0x1.c256660000000p-6f : 0x1.1016a20000000p-6f) : (features[11] < 0x1.b04ba60000000p-7f ? 0x1.7ce6ba0000000p-6f : -0x1.8cdddc0000000p-8f)) : (features[142] < 0x1.5555560000000p-3f ? (features[13] < 0x1.9852f00000000p-9f ? 0x1.3ebd860000000p-7f : -0x1.aca12a0000000p-6f) : (features[41] < 0x1.db56540000000p+1f ? -0x1.f6a5f60000000p-7f : 0x1.1446300000000p-6f))));
            /* Tree 55: preserve sequential float32 accumulation. */
            score += (!(features[53] >= 0x1.0000000000000p+0f) ? (!(features[2] >= 0x1.781b2a0000000p-1f) ? (features[21] < 0x1.6830800000000p-12f ? (features[85] < 0x1.bbbbbc0000000p-3f ? -0x1.bafff60000000p-6f : 0x1.76de9c0000000p-6f) : (features[3] < 0x1.8f9c180000000p-6f ? 0x1.c6c5e20000000p-7f : -0x1.8f102e0000000p-7f)) : (features[10] < 0x1.b8259e0000000p+2f ? (features[42] < 0x1.aa85ae0000000p+1f ? -0x1.162c2e0000000p-12f : -0x1.3203280000000p-6f) : (features[11] < 0x1.7790820000000p-9f ? -0x1.22e53c0000000p-5f : 0x1.6a05be0000000p-7f))) : (features[77] < 0x1.8618620000000p-5f ? (features[100] < 0x1.4515920000000p+2f ? -0x1.ab07220000000p-6f : 0x1.0d51600000000p-6f) : (features[103] < 0x1.6e66460000000p+1f ? (features[80] < 0x1.dc47720000000p-4f ? -0x1.d0231c0000000p-7f : 0x1.c33a720000000p-7f) : (features[64] < 0x1.579fca0000000p-3f ? 0x1.1c1e1e0000000p-5f : 0x1.3e99480000000p-7f))));
            /* Tree 56: preserve sequential float32 accumulation. */
            score += (features[139] < 0x1.b6db6e0000000p-2f ? (features[10] < 0x1.876ac60000000p+2f ? (!(features[3] >= 0x1.0000000000000p-2f) ? (features[55] < 0x1.0a2b240000000p+1f ? -0x1.e0664e0000000p-7f : 0x1.221dec0000000p-10f) : (features[114] < 0x1.f948b80000000p+2f ? 0x1.f6d31c0000000p-8f : -0x1.cd06d60000000p-7f)) : (!(features[24] >= 0x1.04958a0000000p-9f) ? (features[111] < 0x1.62e4300000000p+0f ? -0x1.33436e0000000p-6f : 0x1.77a6880000000p-7f) : (features[12] < 0x1.10a7500000000p-4f ? 0x1.fc56960000000p-8f : -0x1.5f2a380000000p-7f))) : (features[141] < 0x1.0a2b240000000p+1f ? (features[160] < 0x1.b91b920000000p-4f ? (features[3] < 0x1.5555560000000p-2f ? 0x1.fbb8420000000p-7f : -0x1.3dd6120000000p-7f) : (features[88] < 0x1.0cef9c0000000p-5f ? 0x1.f70f3c0000000p-7f : 0x1.1fd24c0000000p-5f)) : (features[49] < 0x1.1e79e80000000p-1f ? -0x1.0eee660000000p-5f : 0x1.36a72a0000000p-9f)));
            /* Tree 57: preserve sequential float32 accumulation. */
            score += (!(features[52] >= 0x1.bc75960000000p-1f) ? (features[2] < 0x1.42a8480000000p-1f ? (features[34] < -0x1.6db6dc0000000p-1f ? (features[19] < 0x1.8c0f060000000p-4f ? -0x1.6426240000000p-6f : 0x1.071f360000000p-6f) : (features[124] < 0x1.0a2b240000000p+1f ? -0x1.466bf60000000p-8f : -0x1.be32000000000p-6f)) : (features[10] < 0x1.c6e0100000000p+2f ? (features[70] < 0x1.aaaaaa0000000p-2f ? -0x1.14e4b20000000p-11f : -0x1.17cd440000000p-6f) : (features[13] < 0x1.b545640000000p-11f ? -0x1.1ed9e20000000p-5f : 0x1.8580860000000p-7f))) : (features[55] < 0x1.62e4300000000p+0f ? (features[14] < 0x1.99999a0000000p-3f ? (features[97] < 0x1.5930ba0000000p-2f ? -0x1.2036d80000000p-7f : -0x1.3a38120000000p-5f) : (features[95] < 0x1.83f2c60000000p+2f ? -0x1.3ad2b80000000p-7f : 0x1.c2c2d60000000p-6f)) : (features[102] < 0x1.cd68a60000000p+2f ? -0x1.3b4bbe0000000p-7f : (features[63] < 0x1.2f684c0000000p-3f ? 0x1.184d440000000p-5f : 0x1.ce4e680000000p-12f))));
            /* Tree 58: preserve sequential float32 accumulation. */
            score += (features[110] < 0x1.d376100000000p+2f ? (features[66] < 0x1.99999a0000000p-3f ? (features[154] < 0x1.3333340000000p-1f ? (features[21] < 0x1.c9ab660000000p-7f ? -0x1.878bda0000000p-7f : 0x1.796dda0000000p-10f) : (features[43] < 0x1.a5a5a60000000p-3f ? -0x1.152c3e0000000p-5f : 0x1.d54d6a0000000p-7f)) : (features[13] < 0x1.12358e0000000p-7f ? (features[2] < 0x1.2662aa0000000p-1f ? -0x1.8bbe880000000p-6f : 0x1.6bda560000000p-6f) : (features[70] < 0x1.5555560000000p-3f ? 0x1.fc8bfc0000000p-9f : -0x1.624bc20000000p-6f))) : (features[67] < 0x1.e666660000000p-1f ? (features[10] < 0x1.6d0ac60000000p+2f ? (!(features[24] >= 0x1.837a880000000p-3f) ? -0x1.c9b92e0000000p-8f : 0x1.4992120000000p-6f) : (features[5] < 0x1.5555560000000p-3f ? 0x1.662fa20000000p-9f : 0x1.f432460000000p-7f)) : (features[60] < 0x1.0000000000000p-1f ? (features[114] < 0x1.259c580000000p+3f ? 0x1.226fc20000000p-6f : -0x1.f132f20000000p-8f) : -0x1.1e7e720000000p-5f)));
            /* Tree 59: preserve sequential float32 accumulation. */
            score += (features[83] < 0x1.b6db6e0000000p-2f ? (features[67] < 0x1.e666660000000p-1f ? (features[110] < 0x1.4078be0000000p+3f ? (features[70] < 0x1.aaaaaa0000000p-2f ? -0x1.0c1f420000000p-10f : -0x1.16e83e0000000p-6f) : (features[141] < 0x1.3e116c0000000p+1f ? 0x1.5911580000000p-7f : -0x1.ea2e760000000p-8f)) : (features[60] < 0x1.0000000000000p-1f ? (features[114] < 0x1.37dbfe0000000p+3f ? 0x1.1f07e20000000p-6f : -0x1.5ab2120000000p-7f) : -0x1.1adcbc0000000p-5f)) : (features[158] < 0x1.193ea80000000p+1f ? -0x1.1424f60000000p-5f : 0x1.2b538e0000000p-6f));
            /* Tree 60: preserve sequential float32 accumulation. */
            score += (!(features[53] >= 0x1.0000000000000p-2f) ? (!(features[2] >= 0x1.42a8480000000p-1f) ? (features[34] < -0x1.6db6dc0000000p-1f ? (features[19] < 0x1.8c0f060000000p-4f ? -0x1.6159b40000000p-6f : 0x1.f5c2180000000p-7f) : (features[136] < 0x1.6db6dc0000000p-2f ? -0x1.bf3b520000000p-6f : 0x1.6ecb5e0000000p-8f)) : (features[10] < 0x1.c6e0100000000p+2f ? (features[2] < 0x1.dd6dde0000000p-1f ? -0x1.a224de0000000p-8f : 0x1.97b7e60000000p-9f) : (features[114] < 0x1.6a1f720000000p+3f ? 0x1.8d4b8a0000000p-7f : -0x1.8799780000000p-6f))) : (features[160] < 0x1.ab68a00000000p-5f ? (features[78] < 0x1.728eb60000000p+2f ? (features[140] < 0x1.d4ef960000000p+1f ? 0x1.9283060000000p-6f : -0x1.a3cf1c0000000p-10f) : (features[103] < 0x1.6e66460000000p+1f ? -0x1.eb947a0000000p-10f : -0x1.2b7ae00000000p-5f)) : (features[52] < 0x1.f603f60000000p-3f ? (features[102] < 0x1.c5cebc0000000p+2f ? 0x1.774ba60000000p-6f : -0x1.fa1e280000000p-6f) : (features[154] < 0x1.3333340000000p-1f ? 0x1.cc04820000000p-7f : 0x1.1a8aa00000000p-5f))));
            /* Tree 61: preserve sequential float32 accumulation. */
            score += (!(features[53] >= 0x1.0000000000000p-2f) ? (!(features[2] >= 0x1.781b2a0000000p-1f) ? (!(features[21] >= 0x1.c6c93a0000000p-13f) ? (features[145] < 0x1.b6db6e0000000p-2f ? -0x1.ba4a5e0000000p-6f : 0x1.23eb5a0000000p-7f) : (features[79] < 0x1.f2272a0000000p+0f ? -0x1.b640c80000000p-7f : 0x1.553a840000000p-7f)) : (features[15] < 0x1.bbbbbc0000000p-2f ? (features[42] < 0x1.aa85ae0000000p+1f ? -0x1.37a5460000000p-10f : -0x1.7dcae20000000p-6f) : (features[114] < 0x1.5a31760000000p+3f ? 0x1.26ac6e0000000p-7f : -0x1.1a1a1c0000000p-6f))) : (features[160] < 0x1.ab68a00000000p-5f ? (features[78] < 0x1.728eb60000000p+2f ? (features[126] < 0x1.b6db6e0000000p-3f ? 0x1.a601c80000000p-6f : 0x1.df73d60000000p-9f) : (features[103] < 0x1.6e66460000000p+1f ? -0x1.05e9f20000000p-9f : -0x1.17d04c0000000p-5f)) : (features[52] < 0x1.f603f60000000p-3f ? (features[102] < 0x1.c5cebc0000000p+2f ? 0x1.8e8f020000000p-6f : -0x1.ee3b9a0000000p-6f) : (features[154] < 0x1.3333340000000p-1f ? 0x1.af9d6c0000000p-7f : 0x1.166d820000000p-5f))));
            /* Tree 62: preserve sequential float32 accumulation. */
            score += (features[139] < 0x1.d89d8a0000000p-2f ? (features[10] < 0x1.851da00000000p+2f ? (!(features[2] >= 0x1.db820c0000000p-1f) ? (features[102] < 0x1.adf84a0000000p+3f ? -0x1.1468440000000p-7f : -0x1.92371e0000000p-6f) : (features[114] < 0x1.faacfa0000000p+2f ? 0x1.0692160000000p-8f : -0x1.cd1d820000000p-7f)) : (features[110] < 0x1.447d380000000p+3f ? (features[154] < 0x1.3333340000000p-1f ? 0x1.1179880000000p-11f : -0x1.1d3abc0000000p-5f) : (features[67] < 0x1.e666660000000p-1f ? 0x1.b1e7300000000p-7f : -0x1.d46a780000000p-6f))) : (features[80] < 0x1.47ae140000000p-4f ? (!(features[0] >= 0x1.4956f00000000p+1f) ? (features[16] < 0x1.99999a0000000p-2f ? -0x1.4417a00000000p-7f : 0x1.1ca57a0000000p-5f) : (features[142] < 0x1.1111120000000p-2f ? -0x1.cd15360000000p-6f : 0x1.3df3d80000000p-7f)) : (features[160] < 0x1.5555560000000p-4f ? (features[8] < 0x1.0000000000000p-1f ? 0x1.edb73a0000000p-7f : -0x1.09dbde0000000p-7f) : (features[16] < 0x1.cccccc0000000p-1f ? 0x1.23ee5a0000000p-5f : 0x1.aa97400000000p-7f))));
            /* Tree 63: preserve sequential float32 accumulation. */
            score += (features[139] < 0x1.b6db6e0000000p-2f ? (!(features[2] >= 0x1.9a3c660000000p-1f) ? (features[114] < 0x1.3d02520000000p+3f ? (features[144] < 0x1.9be3660000000p-4f ? -0x1.d55c2a0000000p-7f : 0x1.69f3080000000p-15f) : (features[2] < 0x1.1312740000000p-1f ? -0x1.84a98e0000000p-6f : 0x1.39f9480000000p-6f)) : (features[10] < 0x1.5b32620000000p+2f ? (features[22] < 0x1.332df60000000p-4f ? -0x1.2a0d440000000p-7f : 0x1.dc81c20000000p-6f) : (features[64] < 0x1.c7946e0000000p-4f ? -0x1.dda5200000000p-11f : 0x1.74b2fc0000000p-7f))) : (features[141] < 0x1.0a2b240000000p+1f ? (features[160] < 0x1.b91b920000000p-4f ? (features[44] < 0x1.5f15f20000000p-4f ? 0x1.6247440000000p-6f : -0x1.eadaee0000000p-8f) : (features[18] < 0x1.c71c720000000p-1f ? 0x1.0b99a20000000p-5f : 0x1.52d8860000000p-9f)) : (features[49] < 0x1.1e79e80000000p-1f ? -0x1.f47fb80000000p-6f : 0x1.7085ee0000000p-9f)));
            /* Tree 64: preserve sequential float32 accumulation. */
            score += (features[83] < 0x1.99999a0000000p-2f ? (features[87] < 0x1.c341160000000p-2f ? (!(features[2] >= 0x1.db820c0000000p-1f) ? (features[13] < 0x1.58ed240000000p-7f ? -0x1.50e4720000000p-10f : -0x1.e75a2c0000000p-7f) : (features[114] < 0x1.5a31760000000p+3f ? 0x1.af4f4a0000000p-8f : -0x1.96fb300000000p-7f)) : (features[18] < 0x1.773b9e0000000p-2f ? (features[11] < 0x1.eb851e0000000p-6f ? 0x1.18134e0000000p-5f : -0x1.616b120000000p-7f) : (features[142] < 0x1.0000000000000p-2f ? 0x1.e8bb6a0000000p-10f : 0x1.8e8f5c0000000p-6f))) : (features[158] < 0x1.193ea80000000p+1f ? -0x1.1424560000000p-5f : 0x1.4583e40000000p-6f));
            /* Tree 65: preserve sequential float32 accumulation. */
            score += (features[83] < 0x1.99999a0000000p-2f ? (features[67] < 0x1.e666660000000p-1f ? (features[110] < 0x1.429f840000000p+3f ? (features[10] < 0x1.b8259e0000000p+2f ? -0x1.6013d60000000p-8f : 0x1.2418700000000p-8f) : (features[141] < 0x1.3e116c0000000p+1f ? 0x1.51039a0000000p-7f : -0x1.dde6880000000p-8f)) : (features[60] < 0x1.0000000000000p-1f ? (features[114] < 0x1.37dbfe0000000p+3f ? 0x1.16ce7c0000000p-6f : -0x1.fd5e3c0000000p-8f) : -0x1.17d7f00000000p-5f)) : (features[158] < 0x1.193ea80000000p+1f ? -0x1.131e060000000p-5f : 0x1.4319180000000p-6f));
            /* Tree 66: preserve sequential float32 accumulation. */
            score += (features[139] < 0x1.d89d8a0000000p-2f ? (features[10] < 0x1.876ac60000000p+2f ? (!(features[24] >= 0x1.525cde0000000p-4f) ? (features[2] < 0x1.7b8e4e0000000p-1f ? -0x1.54dce40000000p-6f : -0x1.ab67960000000p-8f) : (features[114] < 0x1.0855f60000000p+3f ? 0x1.ac321e0000000p-7f : -0x1.f062320000000p-7f)) : (features[110] < 0x1.447d380000000p+3f ? (features[6] < 0x1.8000000000000p-1f ? -0x1.2aa0740000000p-6f : 0x1.0ecdf80000000p-9f) : (features[67] < 0x1.e666660000000p-1f ? 0x1.9ed5200000000p-7f : -0x1.c9334a0000000p-6f))) : (features[141] < 0x1.0a2b240000000p+1f ? (features[160] < 0x1.b91b920000000p-4f ? (features[3] < 0x1.5555560000000p-2f ? 0x1.a425b80000000p-7f : -0x1.a921da0000000p-7f) : (features[47] < 0x1.c28f5c0000000p-3f ? 0x1.0685a60000000p-5f : 0x1.188cee0000000p-8f)) : -0x1.b2cc700000000p-7f));
            /* Tree 67: preserve sequential float32 accumulation. */
            score += (features[83] < 0x1.99999a0000000p-2f ? (features[140] < 0x1.303ad20000000p+2f ? (features[145] < 0x1.b6db6e0000000p-3f ? (features[63] < 0x1.6aaaaa0000000p-2f ? 0x1.6583e80000000p-12f : -0x1.02741c0000000p-5f) : (features[97] < 0x1.4000000000000p+1f ? 0x1.77865c0000000p-6f : -0x1.9382ce0000000p-10f)) : -0x1.5623aa0000000p-5f) : (features[158] < 0x1.193ea80000000p+1f ? -0x1.115efa0000000p-5f : 0x1.2f774e0000000p-6f));
            /* Tree 68: preserve sequential float32 accumulation. */
            score += (!(features[53] >= 0x1.0000000000000p-2f) ? (!(features[2] >= 0x1.42a8480000000p-1f) ? (features[34] < -0x1.6db6dc0000000p-1f ? (features[19] < 0x1.8c0f060000000p-4f ? -0x1.490df40000000p-6f : 0x1.2b8c1a0000000p-6f) : (features[139] < 0x1.d89d8a0000000p-2f ? -0x1.a7b3280000000p-6f : 0x1.09c3940000000p-8f)) : (features[10] < 0x1.c6e0100000000p+2f ? (features[2] < 0x1.dd6dde0000000p-1f ? -0x1.9e01bc0000000p-8f : 0x1.8359b80000000p-9f) : (features[160] < 0x1.1111120000000p-4f ? 0x1.7eedcc0000000p-11f : 0x1.0ff4320000000p-6f))) : (features[160] < 0x1.ab68a00000000p-5f ? (features[78] < 0x1.728eb60000000p+2f ? (features[114] < 0x1.0f8e420000000p+3f ? 0x1.88606e0000000p-6f : -0x1.3ea9000000000p-13f) : (features[112] < 0x1.26bb1c0000000p+1f ? -0x1.36f1a40000000p-8f : -0x1.150cd40000000p-5f)) : (features[52] < 0x1.f603f60000000p-3f ? (features[110] < 0x1.f1c51c0000000p+1f ? 0x1.87dd280000000p-6f : -0x1.ba9b660000000p-6f) : (features[63] < 0x1.579fca0000000p-3f ? 0x1.e915c60000000p-6f : -0x1.73f87e0000000p-7f))));
            /* Tree 69: preserve sequential float32 accumulation. */
            score += (features[83] < 0x1.99999a0000000p-2f ? (features[87] < 0x1.c341160000000p-2f ? (!(features[2] >= 0x1.db820c0000000p-1f) ? (features[13] < 0x1.58ed240000000p-7f ? -0x1.dfa0480000000p-10f : -0x1.c820060000000p-7f) : (features[13] < 0x1.45828c0000000p-6f ? 0x1.d1b0fc0000000p-8f : -0x1.1887900000000p-7f)) : (features[18] < 0x1.773b9e0000000p-2f ? (features[11] < 0x1.eb851e0000000p-6f ? 0x1.1213580000000p-5f : -0x1.3b37a60000000p-7f) : (features[20] < 0x1.c790f80000000p-4f ? -0x1.12b1760000000p-8f : 0x1.7fb25c0000000p-7f))) : (features[158] < 0x1.193ea80000000p+1f ? -0x1.0f960a0000000p-5f : 0x1.3b1cc40000000p-6f));
            /* Tree 70: preserve sequential float32 accumulation. */
            score += (features[140] < 0x1.2cd4ac0000000p+2f ? (features[145] < 0x1.b6db6e0000000p-3f ? (features[101] < 0x1.0000000000000p-1f ? (features[103] < 0x1.be4a420000000p+2f ? -0x1.2a83de0000000p-8f : 0x1.2adce20000000p-8f) : (features[101] < 0x1.dd3c260000000p+0f ? -0x1.42acf60000000p-6f : 0x1.78a1480000000p-9f)) : (features[9] < 0x1.db11f60000000p+2f ? (features[95] < 0x1.501bba0000000p+3f ? -0x1.3557bc0000000p-8f : 0x1.f17a420000000p-6f) : (features[124] < 0x1.4850420000000p+1f ? 0x1.830fb40000000p-8f : 0x1.e2ff8e0000000p-6f))) : (features[160] < 0x1.e1e1e20000000p-5f ? -0x1.1475d60000000p-7f : -0x1.53d4600000000p-5f));
            /* Tree 71: preserve sequential float32 accumulation. */
            score += (features[142] < 0x1.99999a0000000p-3f ? (features[154] < 0x1.6db6dc0000000p-1f ? (features[63] < 0x1.6aaaaa0000000p-2f ? (features[18] < 0x1.3a3caa0000000p-1f ? 0x1.5987340000000p-9f : -0x1.2197f40000000p-7f) : -0x1.0c37a40000000p-5f) : (features[157] < 0x1.0074380000000p-2f ? -0x1.28b9540000000p-5f : (!(features[0] >= 0x1.5dca400000000p+1f) ? -0x1.9fa11e0000000p-7f : 0x1.02d7780000000p-5f))) : (features[149] < 0x1.6db6dc0000000p-1f ? -0x1.3e559c0000000p-5f : (features[95] < 0x1.6cae8a0000000p+3f ? (features[10] < 0x1.70c5740000000p+2f ? -0x1.488a860000000p-11f : 0x1.3a41e00000000p-6f) : (features[3] < 0x1.c71c720000000p-4f ? 0x1.4236280000000p-8f : 0x1.1a4b980000000p-5f))));
            /* Tree 72: preserve sequential float32 accumulation. */
            score += (features[15] < 0x1.bbbbbc0000000p-2f ? (features[158] < 0x1.193ea80000000p+1f ? (features[154] < 0x1.5555560000000p-3f ? (!(features[24] >= 0x1.1a636e0000000p-4f) ? -0x1.81b66c0000000p-8f : 0x1.4cffb20000000p-8f) : (features[110] < 0x1.0110740000000p+4f ? -0x1.20822a0000000p-5f : -0x1.d1ea740000000p-8f)) : (features[20] < 0x1.0386dc0000000p-4f ? (features[139] < 0x1.1c71c80000000p-1f ? 0x1.a669b20000000p-8f : 0x1.adb8800000000p-6f) : (features[52] < 0x1.87da1c0000000p-1f ? 0x1.a669b20000000p-8f : 0x1.0b96ae0000000p-5f))) : (features[114] < 0x1.5a31760000000p+3f ? (!(features[2] >= 0x1.781b2a0000000p-1f) ? (features[109] < 0x1.0000000000000p+0f ? -0x1.87f08a0000000p-6f : 0x1.4757a00000000p-6f) : (features[140] < 0x1.b35a700000000p+1f ? 0x1.8c0e620000000p-6f : 0x1.7a00840000000p-8f)) : (features[105] < 0x1.0398240000000p-3f ? (features[9] < 0x1.4d289e0000000p+3f ? -0x1.2679780000000p-8f : 0x1.c224b80000000p-6f) : (features[2] < 0x1.fc2e020000000p-1f ? -0x1.88f0a80000000p-7f : -0x1.bba5120000000p-6f))));
            /* Tree 73: preserve sequential float32 accumulation. */
            score += (features[142] < 0x1.99999a0000000p-3f ? (features[154] < 0x1.6db6dc0000000p-1f ? (features[63] < 0x1.6aaaaa0000000p-2f ? (features[18] < 0x1.3a3caa0000000p-1f ? 0x1.3b4d740000000p-9f : -0x1.118d400000000p-7f) : -0x1.06740a0000000p-5f) : (features[157] < 0x1.0074380000000p-2f ? -0x1.25a5140000000p-5f : (!(features[0] >= 0x1.5dca400000000p+1f) ? -0x1.a7d2980000000p-7f : 0x1.fa51460000000p-6f))) : (features[149] < 0x1.9249240000000p-1f ? -0x1.30dc7c0000000p-5f : (features[95] < 0x1.6cae8a0000000p+3f ? (features[10] < 0x1.b600000000000p+2f ? 0x1.750dee0000000p-8f : 0x1.a8200e0000000p-6f) : (features[3] < 0x1.c71c720000000p-4f ? 0x1.3326fa0000000p-8f : 0x1.20ca2a0000000p-5f))));
            /* Tree 74: preserve sequential float32 accumulation. */
            score += (features[15] < 0x1.bbbbbc0000000p-2f ? (features[158] < 0x1.193ea80000000p+1f ? (features[154] < 0x1.5555560000000p-3f ? (features[31] < -0x1.3333340000000p-1f ? -0x1.990ee60000000p-11f : -0x1.7bec480000000p-7f) : (features[110] < 0x1.0110740000000p+4f ? -0x1.1a7f660000000p-5f : -0x1.a6f3440000000p-8f)) : (features[20] < 0x1.0386dc0000000p-4f ? (features[139] < 0x1.1c71c80000000p-1f ? 0x1.6f2a1c0000000p-8f : 0x1.a908120000000p-6f) : (features[52] < 0x1.87da1c0000000p-1f ? 0x1.6f2a1c0000000p-8f : 0x1.01e2a60000000p-5f))) : (features[114] < 0x1.62e4700000000p+3f ? (!(features[2] >= 0x1.fda8520000000p-1f) ? (features[67] < 0x1.e666660000000p-1f ? 0x1.876fb40000000p-8f : -0x1.bf94f20000000p-6f) : (features[111] < 0x1.a5ddfc0000000p+1f ? 0x1.a058ea0000000p-6f : -0x1.e5c1860000000p-6f)) : (features[2] < 0x1.fc2e020000000p-1f ? (features[12] < 0x1.9ae24e0000000p-5f ? 0x1.de48200000000p-12f : -0x1.076f420000000p-6f) : (features[43] < 0x1.8618620000000p-3f ? -0x1.e1393e0000000p-6f : -0x1.743e660000000p-8f))));
            /* Tree 75: preserve sequential float32 accumulation. */
            score += (features[142] < 0x1.99999a0000000p-3f ? (features[154] < 0x1.6db6dc0000000p-1f ? (features[63] < 0x1.6aaaaa0000000p-2f ? (features[9] < 0x1.addcb00000000p+2f ? -0x1.8c246a0000000p-7f : 0x1.a08dc20000000p-10f) : -0x1.04f0b60000000p-5f) : (features[157] < 0x1.0074380000000p-2f ? -0x1.2489160000000p-5f : (!(features[0] >= 0x1.5dca400000000p+1f) ? -0x1.a9c5b60000000p-7f : 0x1.f145e40000000p-6f))) : (features[149] < 0x1.6db6dc0000000p-1f ? -0x1.307b920000000p-5f : (features[95] < 0x1.6cae8a0000000p+3f ? (features[9] < 0x1.ff17c00000000p+2f ? 0x1.b1e3c20000000p-9f : 0x1.5ce85e0000000p-6f) : (features[3] < 0x1.c71c720000000p-4f ? 0x1.2044440000000p-8f : 0x1.1dcebc0000000p-5f))));
            /* Tree 76: preserve sequential float32 accumulation. */
            score += (features[139] < 0x1.d89d8a0000000p-2f ? (features[10] < 0x1.876ac60000000p+2f ? (!(features[2] >= 0x1.dd6dde0000000p-1f) ? (features[102] < 0x1.adf84a0000000p+3f ? -0x1.e1f3fa0000000p-8f : -0x1.760b7a0000000p-6f) : (features[114] < 0x1.0855f60000000p+3f ? 0x1.97be2c0000000p-9f : -0x1.e3d9b60000000p-7f)) : (features[110] < 0x1.447d380000000p+3f ? (!(features[21] >= 0x1.6830800000000p-12f) ? -0x1.c6a1a00000000p-7f : 0x1.6b4a9a0000000p-9f) : (features[162] < 0x1.2d2d2e0000000p-2f ? 0x1.a945660000000p-7f : -0x1.0c05b00000000p-6f))) : (features[160] < 0x1.d316740000000p-2f ? (features[112] < 0x1.0a2b240000000p+1f ? -0x1.be75520000000p-6f : (features[15] < 0x1.59999a0000000p-1f ? 0x1.ab4f4e0000000p-8f : 0x1.04d5dc0000000p-5f)) : (features[102] < 0x1.4f8c7a0000000p+3f ? (features[102] < 0x1.8efa420000000p+2f ? 0x1.c1e2c80000000p-6f : -0x1.0ea4640000000p-6f) : (features[18] < 0x1.7777780000000p-1f ? 0x1.3396480000000p-5f : 0x1.c7c13a0000000p-7f))));
            /* Tree 77: preserve sequential float32 accumulation. */
            score += (features[142] < 0x1.99999a0000000p-3f ? (features[154] < 0x1.6db6dc0000000p-1f ? (features[63] < 0x1.6aaaaa0000000p-2f ? (features[9] < 0x1.addcb00000000p+2f ? -0x1.88a3460000000p-7f : 0x1.9c60100000000p-10f) : -0x1.02e2ac0000000p-5f) : (!(features[53] >= 0x1.99999a0000000p-3f) ? (features[140] < 0x1.3e116c0000000p+1f ? 0x1.227aec0000000p-7f : -0x1.2546920000000p-5f) : (features[126] < 0x1.8000000000000p-2f ? -0x1.134c560000000p-6f : 0x1.03d9c40000000p-5f))) : (features[149] < 0x1.6db6dc0000000p-1f ? -0x1.2b15780000000p-5f : (features[95] < 0x1.6cae8a0000000p+3f ? (features[13] < 0x1.6914740000000p-8f ? 0x1.7d16920000000p-6f : 0x1.32d0620000000p-8f) : (features[0] < 0x1.6146280000000p+1f ? 0x1.3d2dd60000000p-9f : 0x1.1117040000000p-5f))));
            /* Tree 78: preserve sequential float32 accumulation. */
            score += (features[15] < 0x1.bbbbbc0000000p-2f ? (features[24] < 0x1.1a636e0000000p-4f ? (features[55] < 0x1.0a2b240000000p+1f ? (features[67] < 0x1.99999a0000000p-6f ? -0x1.8a2c5c0000000p-8f : -0x1.2874140000000p-6f) : (features[13] < 0x1.e7dc6e0000000p-8f ? 0x1.705a980000000p-6f : -0x1.2e0cd40000000p-9f)) : (features[158] < 0x1.9157e00000000p+1f ? (features[20] < 0x1.5dd6300000000p-4f ? -0x1.9e9ac20000000p-6f : 0x1.50273c0000000p-8f) : (features[53] < 0x1.99999a0000000p-3f ? 0x1.edf5220000000p-7f : 0x1.ebd2200000000p-6f))) : (features[140] < 0x1.b35a700000000p+1f ? (features[110] < 0x1.0db2820000000p+3f ? (features[97] < 0x1.1ce26a0000000p-3f ? 0x1.5462240000000p-6f : -0x1.db888e0000000p-8f) : (features[67] < 0x1.aaaaaa0000000p-1f ? 0x1.d90dd00000000p-6f : -0x1.1f56040000000p-6f)) : (features[141] < 0x1.78e3600000000p+1f ? (features[127] < 0x1.3333340000000p-2f ? 0x1.027f280000000p-7f : -0x1.a22aac0000000p-8f) : (features[5] < 0x1.24924a0000000p-1f ? -0x1.493b0c0000000p-5f : -0x1.0dafc20000000p-8f))));
            /* Tree 79: preserve sequential float32 accumulation. */
            score += (features[70] < 0x1.aaaaaa0000000p-2f ? (features[47] < 0x1.24924a0000000p-3f ? (features[13] < 0x1.45828c0000000p-6f ? (features[160] < 0x1.e1e1e20000000p-5f ? -0x1.3278d80000000p-8f : 0x1.5073b20000000p-8f) : (features[157] < 0x1.ecbaac0000000p-4f ? -0x1.6bc8ce0000000p-7f : 0x1.ac7dea0000000p-7f)) : (features[45] < 0x1.b7d6c40000000p-7f ? (features[8] < 0x1.bacf920000000p-6f ? -0x1.4b21ee0000000p-9f : -0x1.038ade0000000p-5f) : (features[114] < 0x1.5a31760000000p+3f ? 0x1.a787660000000p-6f : -0x1.98c01a0000000p-8f))) : (features[65] < 0x1.edfd6e0000000p-8f ? (features[104] < 0x1.8000000000000p-1f ? (features[12] < 0x1.f3ac2c0000000p-6f ? 0x1.8580000000000p-7f : -0x1.0f4a980000000p-5f) : (features[21] < 0x1.249b660000000p-10f ? -0x1.652db80000000p-6f : 0x1.e74f2c0000000p-7f)) : (features[142] < 0x1.435e500000000p-3f ? (features[13] < 0x1.9852f00000000p-9f ? 0x1.4ed91c0000000p-7f : -0x1.8221d40000000p-6f) : (features[65] < 0x1.4141420000000p-5f ? 0x1.b2c2180000000p-6f : -0x1.7d73e00000000p-8f))));
            /* Tree 80: preserve sequential float32 accumulation. */
            score += (features[10] < 0x1.b8259e0000000p+2f ? (features[2] < 0x1.dd6dde0000000p-1f ? (features[47] < 0x1.47ae140000000p-5f ? (features[127] < 0x1.642c860000000p-4f ? -0x1.0581820000000p-5f : -0x1.df65e00000000p-9f) : (features[64] < 0x1.dc47720000000p-4f ? -0x1.87ba280000000p-7f : -0x1.19d8b60000000p-5f)) : (features[114] < 0x1.0f35e60000000p+3f ? (features[9] < 0x1.b5a86e0000000p+2f ? -0x1.0fe2280000000p-8f : 0x1.6bc7440000000p-7f) : (features[15] < 0x1.ddddde0000000p-3f ? 0x1.445de40000000p-10f : -0x1.26f11c0000000p-6f))) : (features[104] < 0x1.3333340000000p-1f ? (features[65] < 0x1.bdd2b80000000p-10f ? (features[112] < 0x1.8ba7480000000p+1f ? -0x1.2c076c0000000p-5f : -0x1.52a6f60000000p-7f) : 0x1.3f74220000000p-8f) : (features[87] < 0x1.d2a2060000000p-2f ? (!(features[2] >= 0x1.9923500000000p-1f) ? -0x1.de2f6e0000000p-8f : 0x1.1747a80000000p-7f) : (features[102] < 0x1.c55d600000000p+3f ? 0x1.907ec80000000p-6f : -0x1.29f35e0000000p-7f))));
            /* Tree 81: preserve sequential float32 accumulation. */
            score += (features[145] < 0x1.99999a0000000p-3f ? (features[154] < 0x1.6db6dc0000000p-1f ? (features[63] < 0x1.6aaaaa0000000p-2f ? (features[10] < 0x1.9d3bb60000000p+2f ? -0x1.b8a7c60000000p-9f : 0x1.27c4700000000p-8f) : (features[31] < -0x1.b6db6e0000000p-1f ? -0x1.ba81720000000p-7f : -0x1.0e43c80000000p-5f)) : (features[157] < 0x1.0074380000000p-2f ? -0x1.1b14620000000p-5f : (!(features[0] >= 0x1.5dca400000000p+1f) ? -0x1.ac378e0000000p-7f : 0x1.e3525c0000000p-6f))) : (features[140] < 0x1.1a07b00000000p+2f ? (features[95] < 0x1.4a01140000000p+3f ? (!(features[24] >= 0x1.430b200000000p-7f) ? 0x1.2279400000000p-6f : 0x1.934bd60000000p-11f) : (features[44] < 0x1.5151520000000p-2f ? 0x1.0193160000000p-5f : -0x1.ab17a00000000p-8f)) : -0x1.27b2680000000p-5f));
            /* Tree 82: preserve sequential float32 accumulation. */
            score += (features[70] < 0x1.aaaaaa0000000p-2f ? (features[78] < 0x1.d4ef960000000p+1f ? (features[2] < 0x1.781b2a0000000p-1f ? (features[11] < 0x1.b46bf80000000p-8f ? -0x1.6ef7960000000p-8f : -0x1.626fac0000000p-6f) : (features[13] < 0x1.45828c0000000p-6f ? 0x1.4e8a480000000p-9f : -0x1.23af420000000p-7f)) : (features[18] < 0x1.773b9e0000000p-2f ? (features[45] < 0x1.3333340000000p-4f ? 0x1.e17d9c0000000p-6f : -0x1.51c7d20000000p-6f) : (features[139] < 0x1.4000000000000p-1f ? 0x1.dc9f8a0000000p-10f : 0x1.d4faa60000000p-6f))) : (features[162] < 0x1.8000000000000p-4f ? (features[22] < 0x1.2f6d2e0000000p-7f ? (features[12] < 0x1.84bed40000000p-5f ? 0x1.c084920000000p-9f : -0x1.6d89520000000p-7f) : (features[105] < 0x1.53148e0000000p-2f ? 0x1.c329520000000p-6f : -0x1.6d89520000000p-7f)) : (features[64] < 0x1.af286c0000000p-5f ? (features[0] < 0x1.4f46680000000p+1f ? -0x1.bc4f780000000p-6f : -0x1.6d89520000000p-7f) : (features[108] < 0x1.83091e0000000p-2f ? -0x1.1241460000000p-5f : -0x1.6d89520000000p-7f))));
            /* Tree 83: preserve sequential float32 accumulation. */
            score += (features[67] < 0x1.e666660000000p-1f ? (features[110] < 0x1.429f840000000p+3f ? (features[124] < 0x1.0822f80000000p+2f ? (features[10] < 0x1.e7916e0000000p+2f ? -0x1.5177160000000p-9f : 0x1.bdc6a00000000p-7f) : (features[64] < 0x1.09f95a0000000p-3f ? -0x1.8aedf80000000p-6f : 0x1.c9efd00000000p-9f)) : (features[141] < 0x1.3e116c0000000p+1f ? (features[9] < 0x1.e500560000000p+2f ? 0x1.91177e0000000p-11f : 0x1.03a73e0000000p-6f) : (features[64] < 0x1.af286c0000000p-4f ? -0x1.3924000000000p-6f : 0x1.1f431c0000000p-7f))) : (features[60] < 0x1.0000000000000p-1f ? (features[114] < 0x1.37dbfe0000000p+3f ? (features[21] < 0x1.249b660000000p-10f ? -0x1.d4315a0000000p-8f : 0x1.bb8c740000000p-6f) : (features[10] < 0x1.c9fecc0000000p+2f ? -0x1.d95a1e0000000p-7f : 0x1.ce210a0000000p-10f)) : -0x1.0b9b6a0000000p-5f));
            /* Tree 84: preserve sequential float32 accumulation. */
            score += (features[110] < 0x1.ca96220000000p+2f ? (features[66] < 0x1.99999a0000000p-3f ? (features[42] < 0x1.1b92800000000p+2f ? (!(features[21] >= 0x1.ee26d20000000p-7f) ? -0x1.60aed40000000p-7f : 0x1.3518ee0000000p-9f) : (features[65] < 0x1.0000000000000p-5f ? -0x1.2ae2a60000000p-5f : 0x1.20feae0000000p-7f)) : (features[13] < 0x1.12358e0000000p-7f ? (features[135] < 0x1.24924a0000000p-2f ? 0x1.8ad4e20000000p-6f : -0x1.2868000000000p-7f) : (features[70] < 0x1.5555560000000p-3f ? 0x1.0aa16c0000000p-7f : -0x1.33bc2e0000000p-6f))) : (features[67] < 0x1.e666660000000p-1f ? (features[10] < 0x1.c57f680000000p+2f ? (features[102] < 0x1.d55a660000000p+4f ? -0x1.8ad48e0000000p-12f : 0x1.4293b00000000p-6f) : (features[64] < 0x1.c7946e0000000p-4f ? 0x1.b238300000000p-8f : 0x1.7cfe940000000p-6f)) : (features[60] < 0x1.0000000000000p-1f ? (features[65] < 0x1.1cf06a0000000p-7f ? -0x1.0c402e0000000p-9f : 0x1.d0886a0000000p-7f) : -0x1.0bea560000000p-5f)));
            /* Tree 85: preserve sequential float32 accumulation. */
            score += (!(features[2] >= 0x1.de2ada0000000p-1f) ? (features[55] < 0x1.193ea80000000p+1f ? (features[10] < 0x1.b8259e0000000p+2f ? (features[47] < 0x1.47ae140000000p-5f ? -0x1.cb98000000000p-8f : -0x1.5cf5620000000p-6f) : (features[87] < 0x1.bc7bc80000000p-2f ? -0x1.3064a60000000p-9f : 0x1.144d060000000p-6f)) : (features[78] < 0x1.6c661c0000000p+2f ? (features[0] < 0x1.5664f60000000p+1f ? -0x1.e82e7a0000000p-7f : 0x1.5dbb6a0000000p-7f) : (features[103] < 0x1.3d503a0000000p+1f ? -0x1.0d6c040000000p-8f : 0x1.3467200000000p-5f))) : (features[114] < 0x1.5a31760000000p+3f ? (features[64] < 0x1.a41a420000000p-4f ? (features[124] < 0x1.d19c6c0000000p+1f ? 0x1.ec22740000000p-8f : -0x1.5f1c460000000p-7f) : (features[13] < 0x1.4141420000000p-6f ? 0x1.3bc9b60000000p-6f : -0x1.35f0100000000p-9f)) : (features[128] < 0x1.642c860000000p-4f ? (features[112] < 0x1.5aa1640000000p+1f ? -0x1.666b1a0000000p-6f : 0x1.5d361c0000000p-10f) : (features[2] < 0x1.f956dc0000000p-1f ? -0x1.dab6980000000p-9f : -0x1.93a9a20000000p-6f))));
            /* Tree 86: preserve sequential float32 accumulation. */
            score += (features[140] < 0x1.b35a700000000p+1f ? (features[14] < 0x1.6666660000000p-1f ? (features[79] < 0x1.b35a700000000p+1f ? (!(features[24] >= 0x1.bf0c6e0000000p-4f) ? -0x1.f75cd40000000p-8f : 0x1.074afe0000000p-6f) : (features[103] < 0x1.d952b20000000p+1f ? -0x1.1c12a00000000p-8f : 0x1.5e00400000000p-6f)) : (!(features[2] >= 0x1.4637640000000p-1f) ? (features[88] < 0x1.2ca12c0000000p+0f ? -0x1.b84ad20000000p-6f : 0x1.2347c80000000p-7f) : (features[87] < 0x1.5555560000000p-1f ? 0x1.62a7d20000000p-6f : -0x1.62e4f60000000p-10f))) : (features[103] < 0x1.bc74440000000p+2f ? (features[5] < 0x1.9d0ac20000000p-6f ? (features[112] < 0x1.9157e00000000p+1f ? -0x1.94514a0000000p-6f : -0x1.c9f29a0000000p-8f) : (features[97] < 0x1.07582a0000000p-3f ? 0x1.d6054c0000000p-7f : -0x1.a0424c0000000p-8f)) : (features[67] < 0x1.e666660000000p-1f ? (features[2] < 0x1.fda8520000000p-1f ? 0x1.2b1c080000000p-14f : 0x1.b2668e0000000p-7f) : (features[20] < 0x1.f1027a0000000p-5f ? -0x1.2406fe0000000p-7f : -0x1.0435ca0000000p-5f))));
            /* Tree 87: preserve sequential float32 accumulation. */
            score += (features[83] < 0x1.99999a0000000p-2f ? (features[87] < 0x1.c341160000000p-2f ? (!(features[2] >= 0x1.db820c0000000p-1f) ? (features[9] < 0x1.01c6740000000p+3f ? -0x1.6d5e2c0000000p-7f : -0x1.7acb260000000p-10f) : (features[114] < 0x1.5a31760000000p+3f ? 0x1.68faf40000000p-8f : -0x1.5b938c0000000p-7f)) : (features[18] < 0x1.773b9e0000000p-2f ? (features[11] < 0x1.eb851e0000000p-6f ? 0x1.f1d5200000000p-6f : -0x1.2c884a0000000p-7f) : (!(features[24] >= 0x1.d095a80000000p-5f) ? 0x1.16cfa40000000p-12f : 0x1.1776280000000p-6f))) : (features[158] < 0x1.193ea80000000p+1f ? -0x1.05eec20000000p-5f : 0x1.23ebca0000000p-6f));
            /* Tree 88: preserve sequential float32 accumulation. */
            score += (features[70] < 0x1.aaaaaa0000000p-2f ? (features[160] < 0x1.e1e1e20000000p-5f ? (features[140] < 0x1.e740b80000000p+1f ? (features[13] < 0x1.623fa80000000p-8f ? 0x1.b5422e0000000p-7f : -0x1.0f51fe0000000p-8f) : (features[140] < 0x1.1b92800000000p+2f ? -0x1.90a4a80000000p-7f : 0x1.bff38e0000000p-7f)) : (!(features[2] >= 0x1.f2d1960000000p-1f) ? (features[10] < 0x1.9d3bb60000000p+2f ? -0x1.10fbb80000000p-8f : 0x1.e875420000000p-8f) : (features[13] < 0x1.4141420000000p-6f ? 0x1.35103c0000000p-6f : 0x1.f801b60000000p-10f))) : (features[65] < 0x1.edfd6e0000000p-8f ? (features[3] < 0x1.24924a0000000p-3f ? (features[44] < 0x1.56ebc20000000p-4f ? -0x1.ae51100000000p-6f : 0x1.92fa060000000p-8f) : (features[101] < 0x1.4a52940000000p-2f ? 0x1.0472880000000p-6f : -0x1.9ca8b80000000p-6f)) : (features[142] < 0x1.435e500000000p-3f ? (features[13] < 0x1.9852f00000000p-9f ? 0x1.9a50e00000000p-7f : -0x1.6ebc3e0000000p-6f) : (features[18] < 0x1.227f180000000p-1f ? 0x1.59ae9a0000000p-6f : -0x1.fec6980000000p-8f))));
            /* Tree 89: preserve sequential float32 accumulation. */
            score += (features[83] < 0x1.99999a0000000p-2f ? (features[87] < 0x1.c341160000000p-2f ? (!(features[2] >= 0x1.db820c0000000p-1f) ? (features[124] < 0x1.7f74280000000p+1f ? -0x1.b1f3540000000p-7f : -0x1.2161b00000000p-9f) : (features[12] < 0x1.1c71c80000000p-5f ? -0x1.99f56a0000000p-7f : 0x1.3ed65a0000000p-8f)) : (features[160] < 0x1.e1e1e20000000p-5f ? (features[22] < 0x1.e55bb80000000p-8f ? 0x1.3923c20000000p-9f : -0x1.b834980000000p-6f) : (!(features[24] >= 0x1.c50e220000000p-5f) ? 0x1.a6cf020000000p-8f : 0x1.9ec6fc0000000p-6f))) : (features[158] < 0x1.193ea80000000p+1f ? -0x1.0493e00000000p-5f : 0x1.20b10c0000000p-6f));
            /* Tree 90: preserve sequential float32 accumulation. */
            score += (features[145] < 0x1.99999a0000000p-3f ? (features[154] < 0x1.6db6dc0000000p-1f ? (features[63] < 0x1.6aaaaa0000000p-2f ? (features[114] < 0x1.98c2a20000000p+2f ? -0x1.3ce70c0000000p-6f : 0x1.bc19440000000p-11f) : (features[31] < -0x1.b6db6e0000000p-1f ? -0x1.d42a960000000p-7f : -0x1.0946300000000p-5f)) : (features[158] < 0x1.09291e0000000p+2f ? (!(features[24] >= 0x1.40e4a20000000p-3f) ? -0x1.13918e0000000p-5f : -0x1.7c8d1a0000000p-8f) : (features[114] < 0x1.0912620000000p+3f ? 0x1.fc9f8e0000000p-6f : -0x1.7c8d1a0000000p-8f))) : (features[140] < 0x1.1a07b00000000p+2f ? (features[46] < 0x1.99999a0000000p-3f ? (features[102] < 0x1.571f880000000p+3f ? -0x1.673eee0000000p-10f : 0x1.ef6ffc0000000p-7f) : (features[95] < 0x1.1027c20000000p+2f ? 0x1.e89f8a0000000p-11f : 0x1.0e40620000000p-5f)) : -0x1.256e980000000p-5f));
            /* Tree 91: preserve sequential float32 accumulation. */
            score += (features[5] < 0x1.d89d8a0000000p-6f ? (!(features[0] >= 0x1.55f05c0000000p+1f) ? (features[64] < 0x1.26934a0000000p-2f ? (features[160] < 0x1.f79b480000000p-2f ? -0x1.634fec0000000p-6f : -0x1.0bd5580000000p-8f) : (!(features[2] >= 0x1.8fd1440000000p-1f) ? -0x1.9bc5de0000000p-7f : 0x1.dc5b9e0000000p-6f)) : (features[13] < 0x1.e1e1e20000000p-8f ? (features[41] < 0x1.0fe7580000000p+2f ? 0x1.01c54e0000000p-6f : -0x1.eb9e080000000p-9f) : (features[24] < 0x1.2998ee0000000p-2f ? -0x1.5c91e20000000p-8f : 0x1.75c1bc0000000p-6f))) : (features[63] < 0x1.8000000000000p-2f ? (features[10] < 0x1.9d3bb60000000p+2f ? (features[74] < 0x1.f2272a0000000p+0f ? -0x1.ae20f00000000p-10f : 0x1.5399ba0000000p-6f) : (features[160] < 0x1.ab68a00000000p-5f ? -0x1.8608e20000000p-10f : 0x1.e6965a0000000p-7f)) : (features[112] < 0x1.193ea80000000p+1f ? 0x1.54ec780000000p-10f : -0x1.01ebd80000000p-5f)));
            /* Tree 92: preserve sequential float32 accumulation. */
            score += (features[55] < 0x1.0a2b240000000p+1f ? (features[15] < 0x1.6666660000000p-2f ? (!(features[24] >= 0x1.7dfafe0000000p-5f) ? (features[64] < 0x1.47ae140000000p-3f ? -0x1.ceda340000000p-7f : -0x1.bd91400000000p-9f) : (features[61] < 0x1.4a2df60000000p+2f ? 0x1.bad2880000000p-8f : -0x1.538fb80000000p-7f)) : (features[140] < 0x1.b35a700000000p+1f ? (features[87] < 0x1.5555560000000p-1f ? 0x1.3f95a00000000p-6f : -0x1.0b71f20000000p-7f) : (features[67] < 0x1.e666660000000p-1f ? 0x1.603fa00000000p-10f : -0x1.e6e7b60000000p-6f))) : (features[78] < 0x1.d4ef960000000p+1f ? (features[160] < 0x1.d316740000000p-2f ? (features[44] < 0x1.6aaaaa0000000p-2f ? -0x1.0e036c0000000p-6f : 0x1.00781a0000000p-6f) : (features[13] < 0x1.5390940000000p-7f ? 0x1.55d90a0000000p-6f : -0x1.0eb6ac0000000p-9f)) : (features[103] < 0x1.0432e40000000p+1f ? (features[97] < 0x1.aaaaaa0000000p-2f ? 0x1.ec79240000000p-9f : -0x1.9ead9c0000000p-6f) : (features[83] < 0x1.745d180000000p-6f ? 0x1.f979b60000000p-6f : 0x1.5302d20000000p-7f))));
            /* Tree 93: preserve sequential float32 accumulation. */
            score += (features[70] < 0x1.aaaaaa0000000p-2f ? (features[2] < 0x1.ffa64a0000000p-2f ? (!(features[50] >= 0x1.354c3e0000000p+0f) ? (features[55] < 0x1.0a2b240000000p+1f ? -0x1.a5cda60000000p-6f : -0x1.31508a0000000p-7f) : 0x1.4705080000000p-6f) : (features[74] < 0x1.f2272a0000000p+0f ? (features[9] < 0x1.addcb00000000p+2f ? -0x1.29c8840000000p-7f : 0x1.2ccff00000000p-9f) : (features[52] < 0x1.52d9680000000p-1f ? -0x1.d877760000000p-8f : 0x1.8f623c0000000p-6f))) : (features[162] < 0x1.0842100000000p-4f ? (features[32] < 0x1.24924a0000000p-2f ? (features[132] < 0x1.e1e1e20000000p-1f ? 0x1.84da880000000p-7f : -0x1.517e020000000p-7f) : (features[105] < 0x1.38c0f80000000p-2f ? 0x1.b94bd80000000p-6f : -0x1.517e020000000p-7f)) : (features[5] < 0x1.24924a0000000p-1f ? (features[64] < 0x1.99999a0000000p-5f ? -0x1.61e4060000000p-7f : -0x1.09f8b00000000p-5f) : (features[60] < 0x1.24924a0000000p-3f ? -0x1.517e020000000p-7f : -0x1.7a4c760000000p-6f))));
            /* Tree 94: preserve sequential float32 accumulation. */
            score += (features[67] < 0x1.e666660000000p-1f ? (features[110] < 0x1.429f840000000p+3f ? (features[124] < 0x1.0822f80000000p+2f ? (features[154] < 0x1.3333340000000p-1f ? -0x1.42d1740000000p-14f : -0x1.5e0eb40000000p-6f) : (features[64] < 0x1.09f95a0000000p-3f ? -0x1.9292660000000p-6f : 0x1.ff3b0e0000000p-9f)) : (features[141] < 0x1.3e116c0000000p+1f ? (features[9] < 0x1.e500560000000p+2f ? 0x1.9fc90e0000000p-12f : 0x1.ef6a8e0000000p-7f) : (features[64] < 0x1.1224480000000p-3f ? -0x1.f879320000000p-7f : 0x1.9deea00000000p-7f))) : (features[60] < 0x1.0000000000000p-1f ? (features[114] < 0x1.37dbfe0000000p+3f ? (features[21] < 0x1.249b660000000p-10f ? -0x1.0c450c0000000p-7f : 0x1.9822200000000p-6f) : -0x1.ee97a00000000p-8f) : -0x1.0416260000000p-5f));
            /* Tree 95: preserve sequential float32 accumulation. */
            score += (features[83] < 0x1.99999a0000000p-2f ? (features[87] < 0x1.c341160000000p-2f ? (features[2] < 0x1.76b14a0000000p-1f ? (features[11] < 0x1.b46bf80000000p-8f ? -0x1.a7251c0000000p-12f : -0x1.4f3dba0000000p-6f) : (features[14] < 0x1.99999a0000000p-2f ? -0x1.8228420000000p-8f : 0x1.42f5200000000p-9f)) : (features[18] < 0x1.773b9e0000000p-2f ? (features[11] < 0x1.eb851e0000000p-6f ? 0x1.e05a5e0000000p-6f : -0x1.26d91c0000000p-7f) : (features[160] < 0x1.e1e1e20000000p-5f ? -0x1.3d9a7a0000000p-7f : 0x1.f8b73c0000000p-8f))) : (features[158] < 0x1.193ea80000000p+1f ? -0x1.024a7e0000000p-5f : 0x1.29b10c0000000p-6f));
            /* Tree 96: preserve sequential float32 accumulation. */
            score += (features[5] < 0x1.d89d8a0000000p-6f ? (!(features[0] >= 0x1.55f05c0000000p+1f) ? (features[140] < 0x1.d19c6c0000000p+1f ? (features[64] < 0x1.26934a0000000p-2f ? -0x1.7203e80000000p-8f : 0x1.c70df40000000p-6f) : (features[11] < 0x1.b46bf80000000p-8f ? -0x1.09be240000000p-7f : -0x1.b9a0fe0000000p-6f)) : (features[10] < 0x1.c57f680000000p+2f ? (features[97] < 0x1.6cc8ee0000000p-3f ? -0x1.582aac0000000p-7f : 0x1.89c5e80000000p-9f) : (features[125] < 0x1.62e4300000000p+0f ? -0x1.49220a0000000p-6f : 0x1.106f280000000p-6f))) : (features[63] < 0x1.8000000000000p-2f ? (features[9] < 0x1.7910b20000000p+2f ? (features[160] < 0x1.829cbc0000000p-1f ? -0x1.bee0940000000p-6f : 0x1.9df1d40000000p-10f) : (features[114] < 0x1.62e4700000000p+3f ? 0x1.9ecdc00000000p-8f : -0x1.2ff3ec0000000p-7f)) : (features[112] < 0x1.193ea80000000p+1f ? 0x1.22011c0000000p-9f : -0x1.ff4b240000000p-6f)));
            /* Tree 97: preserve sequential float32 accumulation. */
            score += (features[70] < 0x1.aaaaaa0000000p-2f ? (features[2] < 0x1.ffa64a0000000p-2f ? (!(features[50] >= 0x1.354c3e0000000p+0f) ? (features[55] < 0x1.0a2b240000000p+1f ? -0x1.9ec59a0000000p-6f : -0x1.18d0360000000p-7f) : 0x1.5381380000000p-6f) : (features[74] < 0x1.f2272a0000000p+0f ? (features[13] < 0x1.45828c0000000p-6f ? 0x1.304ad20000000p-9f : -0x1.dcbb0e0000000p-8f) : (features[52] < 0x1.52d9680000000p-1f ? -0x1.94970a0000000p-8f : 0x1.8029200000000p-6f))) : (features[65] < 0x1.edfd6e0000000p-8f ? (features[8] < 0x1.bacf920000000p-6f ? (features[110] < 0x1.04852c0000000p+3f ? -0x1.d7c01a0000000p-6f : 0x1.4635660000000p-7f) : (features[105] < 0x1.99ed960000000p-2f ? 0x1.3389c00000000p-6f : -0x1.28f1dc0000000p-6f)) : (features[5] < 0x1.24924a0000000p-1f ? (features[13] < 0x1.9852f00000000p-9f ? 0x1.4b28f40000000p-6f : -0x1.978dba0000000p-6f) : (features[60] < 0x1.24924a0000000p-3f ? 0x1.b78b660000000p-9f : -0x1.7562820000000p-6f))));
            /* Tree 98: preserve sequential float32 accumulation. */
            score += (features[140] < 0x1.2cd4ac0000000p+2f ? (features[142] < 0x1.69696a0000000p-3f ? (features[154] < 0x1.6db6dc0000000p-1f ? (features[63] < 0x1.6aaaaa0000000p-2f ? 0x1.bd4d8c0000000p-13f : -0x1.e42d200000000p-6f) : (features[158] < 0x1.bf8d900000000p+1f ? -0x1.078b380000000p-5f : 0x1.cf5c2a0000000p-7f)) : (features[100] < 0x1.4246300000000p+1f ? (features[24] < 0x1.430b200000000p-7f ? 0x1.0bcdde0000000p-6f : -0x1.5ba8ca0000000p-9f) : (features[103] < 0x1.149a040000000p+2f ? -0x1.dd18a20000000p-8f : 0x1.5ef5440000000p-6f))) : (features[121] < 0x1.3333340000000p-1f ? -0x1.2cae9c0000000p-5f : -0x1.312f860000000p-7f));
            /* Tree 99: preserve sequential float32 accumulation. */
            score += (features[10] < 0x1.b8259e0000000p+2f ? (features[2] < 0x1.dd6dde0000000p-1f ? (features[55] < 0x1.9c04200000000p+0f ? (features[47] < 0x1.47ae140000000p-5f ? -0x1.ef51bc0000000p-8f : -0x1.63c0300000000p-6f) : (features[13] < 0x1.f81f820000000p-8f ? 0x1.bd2ffc0000000p-7f : -0x1.16a0be0000000p-8f)) : (features[114] < 0x1.0f35e60000000p+3f ? (features[9] < 0x1.b5a86e0000000p+2f ? -0x1.042a7c0000000p-8f : 0x1.4e4dc00000000p-7f) : (features[103] < 0x1.ecdf300000000p+2f ? -0x1.26846a0000000p-7f : -0x1.e244d80000000p-6f))) : (features[5] < 0x1.45828c0000000p-7f ? (features[12] < 0x1.b99e040000000p-5f ? (features[112] < 0x1.7f74280000000p+1f ? -0x1.0b333e0000000p-5f : 0x1.08aece0000000p-7f) : (features[55] < 0x1.62e4300000000p+0f ? -0x1.535bd80000000p-5f : -0x1.1aee200000000p-8f)) : (features[102] < 0x1.d650dc0000000p+2f ? (features[87] < 0x1.dc47720000000p-2f ? -0x1.aa1fea0000000p-8f : 0x1.5d3c400000000p-6f) : (features[98] < 0x1.38d7560000000p+1f ? 0x1.06d7e40000000p-6f : -0x1.375fb20000000p-8f))));
            /* Tree 100: preserve sequential float32 accumulation. */
            score += (features[139] < 0x1.d89d8a0000000p-2f ? (!(features[3] >= 0x1.bacf920000000p-8f) ? (!(features[53] >= 0x1.0000000000000p-2f) ? (features[18] < 0x1.50df5a0000000p-2f ? -0x1.71df2c0000000p-13f : -0x1.ad51340000000p-6f) : (features[12] < 0x1.dae6080000000p-5f ? 0x1.669af00000000p-6f : -0x1.d3c5d40000000p-7f)) : (features[10] < 0x1.b8259e0000000p+2f ? (features[70] < 0x1.aaaaaa0000000p-2f ? -0x1.2e10480000000p-11f : -0x1.df9b4e0000000p-7f) : (features[13] < 0x1.410ee40000000p-10f ? -0x1.c974680000000p-6f : 0x1.c8415c0000000p-8f))) : (features[160] < 0x1.d316740000000p-2f ? (features[112] < 0x1.0a2b240000000p+1f ? -0x1.7849100000000p-6f : (features[162] < 0x1.0b21640000000p-2f ? 0x1.436c460000000p-6f : -0x1.833f0c0000000p-7f)) : (features[102] < 0x1.4f8c7a0000000p+3f ? (features[102] < 0x1.8efa420000000p+2f ? 0x1.969ba60000000p-6f : -0x1.1433e80000000p-6f) : (features[18] < 0x1.7777780000000p-1f ? 0x1.1289020000000p-5f : 0x1.4ce2280000000p-7f))));
            /* Tree 101: preserve sequential float32 accumulation. */
            score += (features[139] < 0x1.d89d8a0000000p-2f ? (!(features[3] >= 0x1.bacf920000000p-8f) ? (!(features[53] >= 0x1.0000000000000p-2f) ? (features[18] < 0x1.50df5a0000000p-2f ? -0x1.ed51c00000000p-13f : -0x1.a49c2e0000000p-6f) : (features[42] < 0x1.9c04200000000p+0f ? -0x1.a657400000000p-7f : 0x1.5f24e80000000p-6f)) : (features[10] < 0x1.9b167a0000000p+2f ? (features[136] < 0x1.3333340000000p-2f ? -0x1.1a2bee0000000p-9f : -0x1.3a3d340000000p-5f) : (features[5] < 0x1.99999a0000000p-4f ? 0x1.dc08120000000p-15f : 0x1.57a61e0000000p-7f))) : (features[141] < 0x1.0a2b240000000p+1f ? (features[160] < 0x1.b91b920000000p-4f ? (!(features[24] >= 0x1.97e1460000000p-8f) ? 0x1.8aa1020000000p-7f : -0x1.7247100000000p-7f) : (features[100] < 0x1.00a5900000000p+2f ? 0x1.b1aaf80000000p-7f : 0x1.0a967e0000000p-5f)) : -0x1.65c0ee0000000p-7f));
            /* Tree 102: preserve sequential float32 accumulation. */
            score += (features[140] < 0x1.b35a700000000p+1f ? (features[141] < 0x1.f2272a0000000p+0f ? (features[139] < 0x1.b6db6e0000000p-2f ? (features[64] < 0x1.188c460000000p-2f ? 0x1.e6dcf60000000p-9f : -0x1.0766cc0000000p-6f) : (features[160] < 0x1.5789160000000p-3f ? 0x1.12448c0000000p-10f : 0x1.eb19800000000p-6f)) : (features[62] < 0x1.16d4520000000p+2f ? (features[20] < 0x1.220e640000000p-2f ? 0x1.f28eae0000000p-6f : -0x1.c62e3c0000000p-9f) : -0x1.4dfa2e0000000p-6f)) : (features[67] < 0x1.e666660000000p-1f ? (features[110] < 0x1.3086480000000p+3f ? (features[100] < 0x1.0c9f540000000p+2f ? -0x1.be8c520000000p-9f : -0x1.a8f5a00000000p-6f) : (features[24] < 0x1.bd42b20000000p-5f ? -0x1.4cdb8c0000000p-11f : 0x1.725af80000000p-7f)) : (features[60] < 0x1.99999a0000000p-3f ? (features[103] < 0x1.27a48e0000000p+2f ? -0x1.8d6a1e0000000p-7f : 0x1.2316100000000p-6f) : -0x1.f3ec040000000p-6f)));
            /* Tree 103: preserve sequential float32 accumulation. */
            score += (features[67] < 0x1.e666660000000p-1f ? (features[40] < 0x1.0000000000000p-3f ? (features[31] < -0x1.3333340000000p-1f ? (features[13] < 0x1.45828c0000000p-6f ? 0x1.584fbe0000000p-9f : -0x1.2647920000000p-7f) : (features[124] < 0x1.db56540000000p+1f ? -0x1.2f235a0000000p-8f : -0x1.94e0a60000000p-6f)) : (features[12] < 0x1.61d7ca0000000p-5f ? (features[128] < 0x1.b6db6e0000000p-3f ? -0x1.74cd020000000p-7f : 0x1.be579a0000000p-7f) : (features[114] < 0x1.5a31760000000p+3f ? 0x1.1766320000000p-6f : -0x1.2e1bb80000000p-7f))) : (features[60] < 0x1.0000000000000p-1f ? (features[18] < 0x1.5473400000000p-2f ? 0x1.2957c00000000p-6f : (features[103] < 0x1.27a48e0000000p+2f ? -0x1.9a00a40000000p-7f : 0x1.87e6060000000p-7f)) : -0x1.ff64840000000p-6f));
            /* Tree 104: preserve sequential float32 accumulation. */
            score += (features[140] < 0x1.b35a700000000p+1f ? (features[10] < 0x1.bf8d900000000p+1f ? (features[20] < 0x1.bbe8600000000p-3f ? (features[58] < 0x1.24924a0000000p-1f ? -0x1.23ac540000000p-5f : -0x1.0f0d1e0000000p-7f) : 0x1.14016c0000000p-6f) : (features[32] < 0x1.8000000000000p-1f ? (features[18] < 0x1.6e66c00000000p-2f ? 0x1.8be7740000000p-6f : 0x1.046bc80000000p-9f) : (features[114] < 0x1.5a31760000000p+3f ? 0x1.8172680000000p-6f : -0x1.35c8ce0000000p-7f))) : (features[140] < 0x1.2cd4ac0000000p+2f ? (features[145] < 0x1.b6db6e0000000p-3f ? (features[88] < 0x1.06857a0000000p-1f ? -0x1.387bec0000000p-10f : -0x1.2126800000000p-6f) : (features[114] < 0x1.fd92820000000p+2f ? 0x1.517d640000000p-8f : 0x1.83a5c80000000p-6f)) : (features[121] < 0x1.3333340000000p-1f ? -0x1.26609e0000000p-5f : -0x1.34290c0000000p-7f)));
            /* Tree 105: preserve sequential float32 accumulation. */
            score += (features[140] < 0x1.b35a700000000p+1f ? (features[141] < 0x1.f2272a0000000p+0f ? (features[139] < 0x1.b6db6e0000000p-2f ? (features[11] < 0x1.16872c0000000p-3f ? 0x1.7a96d60000000p-9f : -0x1.9cb62c0000000p-6f) : (features[160] < 0x1.5789160000000p-3f ? 0x1.cb0db20000000p-10f : 0x1.da94ba0000000p-6f)) : (features[55] < 0x1.193ea80000000p+0f ? (features[0] < 0x1.743e1e0000000p+1f ? 0x1.20cfa80000000p-5f : -0x1.5e1d960000000p-9f) : (features[19] < 0x1.1b63a20000000p-7f ? 0x1.1432580000000p-6f : -0x1.a2fc260000000p-6f))) : (features[0] < 0x1.1a5d280000000p+1f ? (features[86] < 0x1.99999a0000000p-2f ? (features[42] < 0x1.8ba7480000000p+1f ? -0x1.9d03e00000000p-6f : -0x1.c78abe0000000p-8f) : 0x1.42a31c0000000p-7f) : (features[140] < 0x1.2cd4ac0000000p+2f ? (features[116] < 0x1.3333340000000p-1f ? -0x1.8844e80000000p-10f : 0x1.b75a500000000p-7f) : (features[97] < 0x1.756a140000000p-2f ? -0x1.26f75e0000000p-5f : -0x1.79f8ec0000000p-7f))));
            /* Tree 106: preserve sequential float32 accumulation. */
            score += (features[74] < 0x1.f2272a0000000p+0f ? (features[15] < 0x1.bbbbbc0000000p-2f ? (features[24] < 0x1.1bd4180000000p-11f ? (features[160] < 0x1.260dd60000000p-1f ? -0x1.a7f0680000000p-6f : -0x1.dd1f380000000p-9f) : (features[158] < 0x1.193ea80000000p+1f ? -0x1.d9db2a0000000p-9f : 0x1.0890f80000000p-6f)) : (!(features[2] >= 0x1.781b2a0000000p-1f) ? (features[10] < 0x1.10aa480000000p+3f ? -0x1.aa6b7e0000000p-6f : 0x1.5e40660000000p-7f) : (features[114] < 0x1.5a31760000000p+3f ? 0x1.d633a60000000p-8f : -0x1.ae31240000000p-7f))) : (features[23] < 0x1.5972a80000000p-5f ? (features[82] < 0x1.71024e0000000p-4f ? (features[144] < 0x1.e9bd380000000p-3f ? -0x1.e28e300000000p-6f : 0x1.ac782c0000000p-7f) : (features[69] < 0x1.8413920000000p-1f ? 0x1.ae6df00000000p-9f : 0x1.ce88100000000p-6f)) : (features[41] < 0x1.c35fc80000000p+1f ? (features[20] < 0x1.959b940000000p-3f ? -0x1.630a5a0000000p-7f : 0x1.7b625c0000000p-6f) : (features[22] < 0x1.2997b60000000p-6f ? 0x1.2ca7e00000000p-5f : -0x1.39c45a0000000p-8f))));
            /* Tree 107: preserve sequential float32 accumulation. */
            score += (features[74] < 0x1.f2272a0000000p+0f ? (features[10] < 0x1.b8259e0000000p+2f ? (features[2] < 0x1.dd6dde0000000p-1f ? (features[100] < 0x1.2bfdc60000000p+2f ? -0x1.3edc200000000p-8f : -0x1.4d29460000000p-6f) : (features[114] < 0x1.0f35e60000000p+3f ? 0x1.3f961a0000000p-8f : -0x1.8d31140000000p-7f)) : (features[21] < 0x1.6830800000000p-12f ? (features[11] < 0x1.f4465a0000000p-8f ? -0x1.f02b6e0000000p-6f : 0x1.cb0a840000000p-9f) : (features[79] < 0x1.32ee3c0000000p+1f ? 0x1.2fca5e0000000p-8f : 0x1.447aea0000000p-6f))) : (!(features[0] >= 0x1.4836d20000000p+1f) ? (features[158] < 0x1.1e8cb00000000p+2f ? (!(features[52] >= 0x1.338c7e0000000p-1f) ? -0x1.7219600000000p-6f : 0x1.fd0fdc0000000p-9f) : (features[95] < 0x1.191efa0000000p+2f ? 0x1.fd0fdc0000000p-9f : 0x1.b2e97e0000000p-6f)) : (features[82] < 0x1.15b1e60000000p-4f ? (features[82] < 0x1.af286c0000000p-5f ? 0x1.4f55e40000000p-6f : -0x1.57e4e80000000p-6f) : (features[88] < 0x1.e744380000000p+0f ? 0x1.2a7a4c0000000p-5f : -0x1.7e849e0000000p-10f))));
            /* Tree 108: preserve sequential float32 accumulation. */
            score += (features[139] < 0x1.d89d8a0000000p-2f ? (features[77] < 0x1.0000000000000p-1f ? (features[63] < 0x1.6aaaaa0000000p-2f ? (features[15] < 0x1.bbbbbc0000000p-2f ? -0x1.2480a40000000p-9f : 0x1.35b7560000000p-8f) : (features[160] < 0x1.57f05e0000000p-4f ? -0x1.f944640000000p-11f : -0x1.f3ec8e0000000p-6f)) : (features[116] < 0x1.3333340000000p-1f ? (features[85] < 0x1.3333340000000p-2f ? -0x1.166d700000000p-5f : 0x1.77ad3e0000000p-8f) : (features[156] < 0x1.62e4300000000p-1f ? -0x1.4292b60000000p-7f : 0x1.25cc980000000p-6f))) : (features[83] < 0x1.2bb5120000000p-5f ? (features[49] < 0x1.570a3e0000000p-1f ? (features[100] < 0x1.a20bd80000000p-2f ? -0x1.83dbc80000000p-6f : 0x1.fcc0ee0000000p-7f) : (features[13] < 0x1.2f684c0000000p-6f ? 0x1.65ca200000000p-6f : -0x1.0cec600000000p-7f)) : (features[97] < 0x1.7181120000000p+0f ? 0x1.24f68c0000000p-5f : 0x1.1075680000000p-7f)));
            /* Tree 109: preserve sequential float32 accumulation. */
            score += (features[140] < 0x1.b35a700000000p+1f ? (features[141] < 0x1.f2272a0000000p+0f ? (features[139] < 0x1.b6db6e0000000p-2f ? (features[11] < 0x1.16872c0000000p-3f ? 0x1.584d1c0000000p-9f : -0x1.a001f60000000p-6f) : (features[160] < 0x1.5789160000000p-3f ? 0x1.15a4000000000p-10f : 0x1.e1b6040000000p-6f)) : (features[62] < 0x1.16d4520000000p+2f ? (features[20] < 0x1.c2fbbe0000000p-4f ? 0x1.ce3f0a0000000p-7f : 0x1.218bd20000000p-5f) : -0x1.3536c80000000p-6f)) : (features[18] < 0x1.106d840000000p-1f ? (features[127] < 0x1.24924a0000000p-2f ? (!(features[24] >= 0x1.431fae0000000p-9f) ? -0x1.52da6e0000000p-7f : 0x1.8943000000000p-8f) : (features[0] < 0x1.7204880000000p+1f ? -0x1.46d2e80000000p-7f : 0x1.dab8600000000p-8f)) : (features[44] < 0x1.0000000000000p-3f ? (features[12] < 0x1.cb5d4e0000000p-5f ? -0x1.f937d60000000p-7f : -0x1.cef5a80000000p-10f) : (features[2] < 0x1.7dd2460000000p-1f ? -0x1.8ec53e0000000p-6f : 0x1.4cb7360000000p-9f))));
            /* Tree 110: preserve sequential float32 accumulation. */
            score += (features[67] < 0x1.e666660000000p-1f ? (features[40] < 0x1.0000000000000p-3f ? (features[31] < -0x1.5555540000000p-1f ? (features[13] < 0x1.45828c0000000p-6f ? 0x1.60018a0000000p-9f : -0x1.159d720000000p-7f) : (features[10] < 0x1.d5458a0000000p+2f ? -0x1.c8df000000000p-7f : 0x1.d439d40000000p-8f)) : (features[70] < 0x1.5555560000000p-2f ? (features[2] < 0x1.dd6dde0000000p-1f ? 0x1.dc9eb60000000p-10f : 0x1.2fb93c0000000p-6f) : (features[3] < 0x1.c71c720000000p-4f ? 0x1.29cea20000000p-7f : -0x1.4bdd8e0000000p-6f))) : (features[60] < 0x1.0000000000000p-1f ? (features[114] < 0x1.37dbfe0000000p+3f ? (features[21] < 0x1.249b660000000p-10f ? -0x1.9b3a420000000p-8f : 0x1.8469580000000p-6f) : -0x1.2cb1180000000p-7f) : -0x1.faa5780000000p-6f));
            /* Tree 111: preserve sequential float32 accumulation. */
            score += (features[140] < 0x1.b35a700000000p+1f ? (features[141] < 0x1.f2272a0000000p+0f ? (features[139] < 0x1.b6db6e0000000p-2f ? (features[11] < 0x1.1648d60000000p-7f ? -0x1.94db240000000p-7f : 0x1.01deb00000000p-8f) : (features[160] < 0x1.5789160000000p-3f ? 0x1.e1ef100000000p-10f : 0x1.cb61be0000000p-6f)) : (features[12] < 0x1.10a7500000000p-4f ? (features[41] < 0x1.69c2620000000p+2f ? 0x1.df61800000000p-6f : -0x1.334a140000000p-7f) : -0x1.6edce00000000p-6f)) : (features[10] < 0x1.9d3bb60000000p+2f ? (features[3] < 0x1.0000000000000p-2f ? (features[140] < 0x1.1c54660000000p+2f ? -0x1.bfcf860000000p-8f : -0x1.b15ca00000000p-6f) : (features[114] < 0x1.faacfa0000000p+2f ? 0x1.df00e40000000p-8f : -0x1.038ba80000000p-7f)) : (features[160] < 0x1.e1e1e20000000p-5f ? (features[97] < 0x1.960adc0000000p-3f ? -0x1.5ecbc00000000p-7f : 0x1.ba741a0000000p-8f) : (features[114] < 0x1.0dd7180000000p+3f ? 0x1.7005bc0000000p-6f : 0x1.5e75fa0000000p-9f))));
            /* Tree 112: preserve sequential float32 accumulation. */
            score += (features[140] < 0x1.2cd4ac0000000p+2f ? (features[142] < 0x1.24924a0000000p-3f ? (features[154] < 0x1.3333340000000p-1f ? (features[87] < 0x1.ba781a0000000p-2f ? -0x1.33b2280000000p-9f : 0x1.ab30220000000p-8f) : (features[158] < 0x1.db56540000000p+1f ? -0x1.0658ae0000000p-5f : 0x1.2a8a1e0000000p-6f)) : (features[46] < 0x1.99999a0000000p-3f ? (features[138] < 0x1.0000000000000p-3f ? -0x1.bd734c0000000p-6f : 0x1.aa51fc0000000p-8f) : (features[70] < 0x1.0000000000000p-2f ? 0x1.ce0b7e0000000p-6f : -0x1.f016460000000p-11f))) : (features[97] < 0x1.756a140000000p-2f ? -0x1.21f4bc0000000p-5f : -0x1.968df80000000p-7f));
            /* Tree 113: preserve sequential float32 accumulation. */
            score += (features[67] < 0x1.e666660000000p-1f ? (features[5] < 0x1.0000000000000p-2f ? (!(features[0] >= 0x1.5583a40000000p+1f) ? (features[64] < 0x1.4000000000000p-2f ? -0x1.96d35e0000000p-7f : 0x1.9048080000000p-8f) : (features[10] < 0x1.b8259e0000000p+2f ? -0x1.c65d240000000p-10f : 0x1.0b7d540000000p-7f)) : (features[9] < 0x1.a42d4e0000000p+2f ? (features[62] < 0x1.c35fc80000000p+1f ? -0x1.f4ab200000000p-7f : 0x1.a8bbb40000000p-8f) : (features[114] < 0x1.62e4700000000p+3f ? 0x1.3a63a00000000p-7f : -0x1.26e05c0000000p-7f))) : (features[60] < 0x1.0000000000000p-1f ? (features[114] < 0x1.37dbfe0000000p+3f ? (features[21] < 0x1.249b660000000p-10f ? -0x1.54d1800000000p-8f : 0x1.7442080000000p-6f) : -0x1.cfeea80000000p-8f) : -0x1.f7a8ca0000000p-6f));
            /* Tree 114: preserve sequential float32 accumulation. */
            score += (features[140] < 0x1.c715a60000000p+1f ? (features[47] < 0x1.24924a0000000p-3f ? (features[78] < 0x1.4ba2580000000p+2f ? (features[124] < 0x1.9157e00000000p+1f ? -0x1.a6312a0000000p-8f : 0x1.2d0dc20000000p-7f) : (features[13] < 0x1.09ddba0000000p-9f ? -0x1.15d72a0000000p-6f : 0x1.b79ece0000000p-7f)) : (features[95] < 0x1.57fb1e0000000p+2f ? (features[19] < 0x1.6bd6020000000p-6f ? 0x1.25a2420000000p-7f : -0x1.cc33d40000000p-7f) : (features[110] < 0x1.f53b0a0000000p+2f ? -0x1.0db0a20000000p-13f : 0x1.2e18f20000000p-5f))) : (features[101] < 0x1.0000000000000p-1f ? (features[103] < 0x1.b94f720000000p+2f ? (features[21] < 0x1.c6c93a0000000p-13f ? -0x1.0a77340000000p-6f : -0x1.7376f60000000p-9f) : (features[10] < 0x1.d5f0180000000p+2f ? 0x1.7c5dce0000000p-11f : 0x1.b2fcc00000000p-7f)) : (features[0] < 0x1.7bb50a0000000p+1f ? (features[95] < 0x1.e60c920000000p+2f ? -0x1.63f23a0000000p-8f : -0x1.e538340000000p-6f) : (features[141] < 0x1.51cca20000000p+1f ? 0x1.2203420000000p-6f : -0x1.e81ed80000000p-6f))));
            /* Tree 115: preserve sequential float32 accumulation. */
            score += (features[125] < 0x1.32ee3c0000000p+1f ? (features[10] < 0x1.b8259e0000000p+2f ? (features[74] < 0x1.f2272a0000000p+0f ? (features[70] < 0x1.aaaaaa0000000p-2f ? -0x1.96c3ce0000000p-11f : -0x1.006fe60000000p-6f) : (features[50] < 0x1.0ec0500000000p+1f ? -0x1.3639020000000p-8f : 0x1.88a54c0000000p-6f)) : (features[103] < 0x1.f58e3c0000000p+2f ? (features[104] < 0x1.99999a0000000p-1f ? -0x1.44ff000000000p-6f : 0x1.30a0760000000p-8f) : (features[12] < 0x1.1422840000000p-4f ? 0x1.2bfef80000000p-6f : -0x1.2c53fc0000000p-6f))) : (features[44] < 0x1.6aaaaa0000000p-2f ? (features[22] < 0x1.4f50060000000p-7f ? (features[140] < 0x1.16d4520000000p+2f ? -0x1.8b0c400000000p-6f : -0x1.586f8c0000000p-8f) : (features[160] < 0x1.58b67e0000000p-2f ? 0x1.e1aa280000000p-7f : -0x1.24e36c0000000p-6f)) : (features[124] < 0x1.193ea80000000p+2f ? (features[160] < 0x1.033d920000000p-4f ? -0x1.ff66560000000p-9f : 0x1.286c6a0000000p-5f) : -0x1.b2b6540000000p-7f)));
            /* Tree 116: preserve sequential float32 accumulation. */
            score += (features[110] < 0x1.429f840000000p+3f ? (features[125] < 0x1.32ee3c0000000p+1f ? (features[127] < 0x1.24924a0000000p-2f ? (!(features[21] >= 0x1.7c22da0000000p-12f) ? -0x1.59a72c0000000p-7f : 0x1.96dbb00000000p-8f) : (features[74] < 0x1.0a2b240000000p+1f ? -0x1.e8f5220000000p-8f : 0x1.d88a2e0000000p-7f)) : (features[95] < 0x1.ec5cba0000000p+2f ? (features[44] < 0x1.aaaaaa0000000p-2f ? -0x1.2585040000000p-7f : 0x1.544f020000000p-6f) : (features[69] < 0x1.e5846a0000000p-1f ? -0x1.69d1aa0000000p-5f : -0x1.8d9f7c0000000p-7f))) : (features[67] < 0x1.e666660000000p-1f ? (features[10] < 0x1.6d0ac60000000p+2f ? (features[124] < 0x1.62e4300000000p+1f ? 0x1.90908a0000000p-7f : -0x1.849fa40000000p-8f) : (features[141] < 0x1.3e116c0000000p+1f ? 0x1.99cede0000000p-7f : -0x1.f92c660000000p-9f)) : (features[60] < 0x1.5555560000000p-2f ? 0x1.3889360000000p-8f : -0x1.fc74160000000p-6f)));
            /* Tree 117: preserve sequential float32 accumulation. */
            score += (features[83] < 0x1.99999a0000000p-2f ? (features[87] < 0x1.d67c8a0000000p-2f ? (!(features[2] >= 0x1.b9a9b80000000p-1f) ? (features[127] < 0x1.24924a0000000p-2f ? -0x1.79faa00000000p-10f : -0x1.a6d0460000000p-7f) : (features[78] < 0x1.7e52e60000000p+2f ? 0x1.35b6b80000000p-9f : -0x1.2c108a0000000p-6f)) : (features[18] < 0x1.729c080000000p-2f ? (features[69] < 0x1.1eb8520000000p-2f ? -0x1.91eec00000000p-8f : 0x1.e126120000000p-6f) : (features[160] < 0x1.033d920000000p-4f ? -0x1.3832d40000000p-7f : 0x1.e70aa60000000p-8f))) : (features[158] < 0x1.193ea80000000p+1f ? -0x1.f8eb580000000p-6f : 0x1.2de92e0000000p-6f));
            /* Tree 118: preserve sequential float32 accumulation. */
            score += (features[140] < 0x1.2cd4ac0000000p+2f ? (features[142] < 0x1.69696a0000000p-3f ? (features[154] < 0x1.6db6dc0000000p-1f ? (features[63] < 0x1.6aaaaa0000000p-2f ? 0x1.7e223e0000000p-13f : -0x1.ce607c0000000p-6f) : (features[158] < 0x1.bf8d900000000p+1f ? -0x1.ff14260000000p-6f : 0x1.7fd9fe0000000p-7f)) : (features[95] < 0x1.6cae8a0000000p+3f ? (features[24] < 0x1.430b200000000p-7f ? 0x1.f360740000000p-7f : -0x1.73d7960000000p-15f) : (features[44] < 0x1.6aaaaa0000000p-2f ? 0x1.dc9cd20000000p-6f : -0x1.f42ce60000000p-7f))) : -0x1.01c6e00000000p-5f);
            /* Tree 119: preserve sequential float32 accumulation. */
            score += (features[74] < 0x1.f2272a0000000p+0f ? (features[10] < 0x1.9d3bb60000000p+2f ? (features[2] < 0x1.d0983c0000000p-1f ? (features[160] < 0x1.f7bdf00000000p-1f ? -0x1.39aa860000000p-7f : 0x1.cb5ca40000000p-7f) : (features[124] < 0x1.32ee3c0000000p+1f ? 0x1.034a3a0000000p-6f : -0x1.833d760000000p-10f)) : (features[5] < 0x1.99999a0000000p-4f ? (features[42] < 0x1.27ff8e0000000p+2f ? 0x1.a238600000000p-11f : -0x1.bf5e340000000p-6f) : (features[160] < 0x1.69696a0000000p-5f ? -0x1.56e1060000000p-10f : 0x1.02b3fa0000000p-6f))) : (!(features[0] >= 0x1.4836d20000000p+1f) ? (features[158] < 0x1.1e8cb00000000p+2f ? (features[55] < 0x1.193ea80000000p+1f ? -0x1.791e8c0000000p-6f : 0x1.3097e00000000p-9f) : (features[95] < 0x1.55c5b60000000p+2f ? 0x1.3097e00000000p-9f : 0x1.cd1a040000000p-6f)) : (features[82] < 0x1.15b1e60000000p-4f ? (features[82] < 0x1.af286c0000000p-5f ? 0x1.e947f20000000p-7f : -0x1.73d5120000000p-6f) : (features[88] < 0x1.e744380000000p+0f ? 0x1.1d24b40000000p-5f : -0x1.0733160000000p-9f))));
            return score;
        }
        
        size_t LaneCount() {
            return hn::Lanes(hn::ScalableTag<float>());
        }
        const char *TargetName() {
            return hwy::TargetName(HWY_TARGET);
        }
        // Fixed-width backends can fold lane loads into vector construction.
        // Scalable backends retain gathers without a maximum-sized scratch array.
        template <class D>
        HWY_INLINE auto LoadFeature(const D d, const float *values, size_t stride) {
            #if HWY_HAVE_SCALABLE
            const hn::RebindToSigned<D> di;
            const auto offsets = hn::Mul(hn::Iota(di, 0), hn::Set(di, static_cast<int32_t>(stride)));
            return hn::GatherIndex(d, values, offsets);
            #else
            HWY_ALIGN float gathered[hn::MaxLanes(d)];
            for (size_t lane = 0; lane < hn::Lanes(d); ++lane) {
                gathered[lane] = values[lane * stride];
            }
            return hn::LoadU(d, gathered);
            #endif
        }
        void Batch(const float *features, size_t rows, float *scores) {
            const hn::ScalableTag<float> d;
            const size_t lanes = hn::Lanes(d);
            size_t row = 0;
            for (; rows - row >= lanes; row += lanes) {
                auto score = hn::Set(d, 0x0.0p+0f);
                const auto feature_2 = LoadFeature(d, features + row * 164 + 2, 164);
                const auto feature_50 = LoadFeature(d, features + row * 164 + 50, 164);
                const auto feature_60 = LoadFeature(d, features + row * 164 + 60, 164);
                const auto feature_83 = LoadFeature(d, features + row * 164 + 83, 164);
                const auto feature_100 = LoadFeature(d, features + row * 164 + 100, 164);
                const auto feature_110 = LoadFeature(d, features + row * 164 + 110, 164);
                const auto feature_158 = LoadFeature(d, features + row * 164 + 158, 164);
                const auto feature_161 = LoadFeature(d, features + row * 164 + 161, 164);
                /* Tree 0: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.a338720000000p-2f)),
                        hn::Set(d, -0x1.99ddcc0000000p-5f), hn::Set(d, -0x1.49fad00000000p-6f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_100, hn::Set(d, 0x1.99999a0000000p-3f)),
                        node_7, hn::Set(d, -0x1.e463b00000000p-5f));
                    const auto node_1 = hn::IfThenElse(hn::Ge(feature_50, hn::Set(d, 0x1.354c3e0000000p+0f)),
                        hn::Set(d, 0x1.85da3c0000000p-5f), node_3);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_110, hn::Set(d, 0x1.d595a00000000p+2f)),
                        hn::Set(d, 0x1.0d7c400000000p-8f), hn::Set(d, 0x1.c839220000000p-6f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_60, hn::Set(d, 0x1.0000000000000p-1f)),
                        hn::Set(d, -0x1.ca5b9e0000000p-7f), hn::Set(d, -0x1.d699b40000000p-5f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_161, hn::Set(d, 0x1.26bb1c0000000p+1f)),
                        node_9, node_10);
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.193ea80000000p+1f)),
                        hn::Set(d, -0x1.e4690c0000000p-5f), hn::Set(d, 0x1.4ac2e80000000p-5f));
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_83, hn::Set(d, 0x1.b6db6e0000000p-2f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.4637640000000p-1f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_9 = LoadFeature(d, features + row * 164 + 9, 164);
                const auto feature_10 = LoadFeature(d, features + row * 164 + 10, 164);
                const auto feature_52 = LoadFeature(d, features + row * 164 + 52, 164);
                const auto feature_88 = LoadFeature(d, features + row * 164 + 88, 164);
                const auto feature_102 = LoadFeature(d, features + row * 164 + 102, 164);
                const auto feature_140 = LoadFeature(d, features + row * 164 + 140, 164);
                const auto feature_154 = LoadFeature(d, features + row * 164 + 154, 164);
                /* Tree 1: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_100, hn::Set(d, 0x1.99999a0000000p-3f)),
                        hn::Set(d, -0x1.091e0c0000000p-6f), hn::Set(d, -0x1.9d0f920000000p-5f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.7a1e080000000p+2f)),
                        hn::Set(d, -0x1.8307880000000p-8f), hn::Set(d, 0x1.0b68640000000p-6f));
                    const auto node_3 = hn::IfThenElse(hn::Ge(feature_2, hn::Set(d, 0x1.8921560000000p-1f)),
                        node_8, node_7);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_154, hn::Set(d, 0x1.8000000000000p-1f)),
                        node_3, hn::Set(d, -0x1.dbc6060000000p-5f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_9, hn::Set(d, 0x1.2a0c1e0000000p+3f)),
                        hn::Set(d, 0x1.3d79180000000p-6f), hn::Set(d, 0x1.9da1140000000p-5f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_140, hn::Set(d, 0x1.51cca20000000p+1f)),
                        hn::Set(d, 0x1.b82a180000000p-5f), node_10);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_88, hn::Set(d, 0x1.4322f40000000p-2f)),
                        hn::Set(d, 0x1.4b292a0000000p-5f), hn::Set(d, 0x1.3d79180000000p-6f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_52, hn::Set(d, 0x1.bc75960000000p-1f)),
                        hn::Set(d, 0x1.3d79180000000p-6f), hn::Set(d, 0x1.d4e7460000000p-5f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_154, hn::Set(d, 0x1.99999a0000000p-2f)),
                        node_11, node_12);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_102, hn::Set(d, 0x1.9072f60000000p+4f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.26bb1c0000000p+1f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_5 = LoadFeature(d, features + row * 164 + 5, 164);
                const auto feature_15 = LoadFeature(d, features + row * 164 + 15, 164);
                const auto feature_67 = LoadFeature(d, features + row * 164 + 67, 164);
                const auto feature_80 = LoadFeature(d, features + row * 164 + 80, 164);
                const auto feature_95 = LoadFeature(d, features + row * 164 + 95, 164);
                const auto feature_103 = LoadFeature(d, features + row * 164 + 103, 164);
                const auto feature_162 = LoadFeature(d, features + row * 164 + 162, 164);
                /* Tree 2: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_5, hn::Set(d, 0x1.45828c0000000p-7f)),
                        hn::Set(d, -0x1.55dc280000000p-5f), hn::Set(d, -0x1.33c1780000000p-8f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_100, hn::Set(d, 0x1.99999a0000000p-3f)),
                        node_7, hn::Set(d, -0x1.c1558e0000000p-5f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_80, hn::Set(d, 0x1.6ece540000000p-4f)),
                        hn::Set(d, -0x1.4d68000000000p-7f), hn::Set(d, 0x1.b0c7460000000p-5f));
                    const auto node_1 = hn::IfThenElse(hn::Ge(feature_52, hn::Set(d, 0x1.5b50c60000000p-1f)),
                        node_4, node_3);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_15, hn::Set(d, 0x1.6666660000000p-2f)),
                        hn::Set(d, -0x1.d9a8400000000p-9f), hn::Set(d, 0x1.0827080000000p-6f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_67, hn::Set(d, 0x1.0000000000000p+0f)),
                        hn::Set(d, -0x1.c44ff20000000p-7f), hn::Set(d, -0x1.b0f5ae0000000p-5f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_162, hn::Set(d, 0x1.e1e1e20000000p-3f)),
                        node_11, node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_95, hn::Set(d, 0x1.3d28480000000p+3f)),
                        hn::Set(d, 0x1.3c79060000000p-6f), hn::Set(d, 0x1.7d784a0000000p-5f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_103, hn::Set(d, 0x1.19db700000000p+2f)),
                        hn::Set(d, 0x1.3c79060000000p-6f), hn::Set(d, 0x1.c7107e0000000p-5f));
                    const auto node_6 = hn::IfThenElse(hn::Ge(feature_52, hn::Set(d, 0x1.5c08140000000p-1f)),
                        node_14, node_13);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.bf8d900000000p+1f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.4637640000000p-1f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_19 = LoadFeature(d, features + row * 164 + 19, 164);
                const auto feature_123 = LoadFeature(d, features + row * 164 + 123, 164);
                /* Tree 3: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_19, hn::Set(d, 0x1.8c0f060000000p-4f)),
                        hn::Set(d, -0x1.6438500000000p-5f), hn::Set(d, -0x1.1bb7420000000p-6f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_100, hn::Set(d, 0x1.99999a0000000p-3f)),
                        node_7, hn::Set(d, -0x1.b3d6b80000000p-5f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_110, hn::Set(d, 0x1.7ea57e0000000p+2f)),
                        hn::Set(d, 0x1.867a260000000p-8f), hn::Set(d, 0x1.9c0e340000000p-5f));
                    const auto node_1 = hn::IfThenElse(hn::Ge(feature_52, hn::Set(d, 0x1.5b50c60000000p-1f)),
                        node_4, node_3);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_162, hn::Set(d, 0x1.e1e1e20000000p-3f)),
                        hn::Set(d, 0x1.0350a80000000p-7f), hn::Set(d, -0x1.65d5720000000p-6f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_154, hn::Set(d, 0x1.8000000000000p-1f)),
                        node_11, hn::Set(d, -0x1.c247c00000000p-5f));
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_123, hn::Set(d, 0x1.0000000000000p-1f)),
                        hn::Set(d, 0x1.1ba3320000000p-6f), hn::Set(d, 0x1.1d5eee0000000p-5f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_102, hn::Set(d, 0x1.2c23740000000p+4f)),
                        hn::Set(d, 0x1.1ba3320000000p-6f), hn::Set(d, 0x1.a08a340000000p-5f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_95, hn::Set(d, 0x1.eab3f80000000p+2f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.26bb1c0000000p+1f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.4637640000000p-1f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_3 = LoadFeature(d, features + row * 164 + 3, 164);
                const auto feature_55 = LoadFeature(d, features + row * 164 + 55, 164);
                /* Tree 4: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_5, hn::Set(d, 0x1.45828c0000000p-7f)),
                        hn::Set(d, -0x1.31f15e0000000p-5f), hn::Set(d, -0x1.4f26f80000000p-8f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_100, hn::Set(d, 0x1.99999a0000000p-3f)),
                        node_7, hn::Set(d, -0x1.a62c120000000p-5f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_3, hn::Set(d, 0x1.75f50c0000000p-10f)),
                        hn::Set(d, 0x1.42ea540000000p-7f), hn::Set(d, 0x1.89394c0000000p-5f));
                    const auto node_1 = hn::IfThenElse(hn::Ge(feature_52, hn::Set(d, 0x1.5b50c60000000p-1f)),
                        node_4, node_3);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_162, hn::Set(d, 0x1.e1e1e20000000p-3f)),
                        hn::Set(d, 0x1.9eb3560000000p-8f), hn::Set(d, -0x1.7ab3f80000000p-6f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_154, hn::Set(d, 0x1.8000000000000p-1f)),
                        node_11, hn::Set(d, -0x1.b15c2e0000000p-5f));
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_55, hn::Set(d, 0x1.f2272a0000000p+0f)),
                        hn::Set(d, 0x1.0ad2b60000000p-6f), hn::Set(d, 0x1.1e59ee0000000p-5f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_52, hn::Set(d, 0x1.67fb6e0000000p-3f)),
                        hn::Set(d, 0x1.0ad2b60000000p-6f), hn::Set(d, 0x1.95e60a0000000p-5f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_95, hn::Set(d, 0x1.0f1ab00000000p+3f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.26bb1c0000000p+1f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.4637640000000p-1f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_21 = LoadFeature(d, features + row * 164 + 21, 164);
                const auto feature_53 = LoadFeature(d, features + row * 164 + 53, 164);
                const auto feature_85 = LoadFeature(d, features + row * 164 + 85, 164);
                const auto feature_106 = LoadFeature(d, features + row * 164 + 106, 164);
                const auto feature_114 = LoadFeature(d, features + row * 164 + 114, 164);
                const auto feature_156 = LoadFeature(d, features + row * 164 + 156, 164);
                /* Tree 5: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_21, hn::Set(d, 0x1.c6c93a0000000p-13f)),
                        hn::Set(d, -0x1.39cd3e0000000p-5f), hn::Set(d, -0x1.77f1800000000p-7f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_85, hn::Set(d, 0x1.6666660000000p-2f)),
                        hn::Set(d, -0x1.9ce58a0000000p-5f), hn::Set(d, 0x1.7f72160000000p-9f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_100, hn::Set(d, 0x1.6a09e60000000p-1f)),
                        node_7, node_8);
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_106, hn::Set(d, 0x1.2302ca0000000p+1f)),
                        hn::Set(d, 0x1.0286340000000p-6f), hn::Set(d, 0x1.94d8c80000000p-5f));
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_156, hn::Set(d, 0x1.62e4300000000p-1f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.193ea80000000p+1f)),
                        hn::Set(d, -0x1.cb4d800000000p-7f), hn::Set(d, 0x1.01703c0000000p-6f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.5a31760000000p+3f)),
                        hn::Set(d, 0x1.66e9360000000p-7f), hn::Set(d, -0x1.5f84a60000000p-6f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.6d0ac60000000p+2f)),
                        node_11, node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_103, hn::Set(d, 0x1.6e66460000000p+1f)),
                        hn::Set(d, 0x1.a3a3f60000000p-9f), hn::Set(d, 0x1.8e0b600000000p-5f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_140, hn::Set(d, 0x1.fc32860000000p+1f)),
                        node_13, hn::Set(d, -0x1.24eb620000000p-5f));
                    const auto node_2 = hn::IfThenElse(hn::Ge(feature_53, hn::Set(d, 0x1.0000000000000p+0f)),
                        node_6, node_5);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.72c1100000000p-1f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_11 = LoadFeature(d, features + row * 164 + 11, 164);
                /* Tree 6: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_11, hn::Set(d, 0x1.6578160000000p-7f)),
                        hn::Set(d, -0x1.388b940000000p-6f), hn::Set(d, -0x1.5f3dc00000000p-5f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_100, hn::Set(d, 0x1.99999a0000000p-3f)),
                        node_7, hn::Set(d, -0x1.8f960a0000000p-5f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_110, hn::Set(d, 0x1.3d61560000000p+2f)),
                        hn::Set(d, 0x1.5b79ea0000000p-8f), hn::Set(d, 0x1.70f4f60000000p-5f));
                    const auto node_1 = hn::IfThenElse(hn::Ge(feature_52, hn::Set(d, 0x1.5b50c60000000p-1f)),
                        node_4, node_3);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_162, hn::Set(d, 0x1.e1e1e20000000p-3f)),
                        hn::Set(d, 0x1.8526f80000000p-8f), hn::Set(d, -0x1.70275e0000000p-6f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_154, hn::Set(d, 0x1.8000000000000p-1f)),
                        node_11, hn::Set(d, -0x1.9f1ac00000000p-5f));
                    const auto node_13 = hn::IfThenElse(hn::Ge(feature_53, hn::Set(d, 0x1.0000000000000p+0f)),
                        hn::Set(d, 0x1.355f100000000p-5f), hn::Set(d, 0x1.ec27de0000000p-7f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_52, hn::Set(d, 0x1.67fb6e0000000p-3f)),
                        hn::Set(d, 0x1.ec27de0000000p-7f), hn::Set(d, 0x1.7e71ba0000000p-5f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_95, hn::Set(d, 0x1.0f1ab00000000p+3f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.26bb1c0000000p+1f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.4637640000000p-1f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_0 = LoadFeature(d, features + row * 164 + 0, 164);
                const auto feature_147 = LoadFeature(d, features + row * 164 + 147, 164);
                /* Tree 7: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.042ab40000000p-1f)),
                        hn::Set(d, -0x1.44b3f20000000p-5f), hn::Set(d, -0x1.071f940000000p-6f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_100, hn::Set(d, 0x1.99999a0000000p-3f)),
                        node_7, hn::Set(d, -0x1.8599aa0000000p-5f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_3, hn::Set(d, 0x1.75f50c0000000p-10f)),
                        hn::Set(d, 0x1.0faa9e0000000p-8f), hn::Set(d, 0x1.6bb32e0000000p-5f));
                    const auto node_1 = hn::IfThenElse(hn::Ge(feature_52, hn::Set(d, 0x1.5b50c60000000p-1f)),
                        node_4, node_3);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.b8259e0000000p+2f)),
                        hn::Set(d, -0x1.1e68900000000p-7f), hn::Set(d, 0x1.78979a0000000p-7f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_147, hn::Set(d, 0x1.99999a0000000p-3f)),
                        hn::Set(d, 0x1.154a600000000p-6f), hn::Set(d, -0x1.b8f65c0000000p-5f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_110, hn::Set(d, 0x1.447d380000000p+3f)),
                        node_11, node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_0, hn::Set(d, 0x1.25db2e0000000p+1f)),
                        hn::Set(d, 0x1.5123180000000p-6f), hn::Set(d, -0x1.1877880000000p-6f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_60, hn::Set(d, 0x1.0000000000000p-1f)),
                        node_13, hn::Set(d, -0x1.aca13c0000000p-5f));
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_67, hn::Set(d, 0x1.0000000000000p+0f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.4637640000000p-1f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_24 = LoadFeature(d, features + row * 164 + 24, 164);
                /* Tree 8: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Ge(feature_2, hn::Set(d, 0x1.781b2a0000000p-1f)),
                        hn::Set(d, -0x1.1961760000000p-9f), hn::Set(d, -0x1.7be12e0000000p-6f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.d82d340000000p+1f)),
                        hn::Set(d, 0x1.3f0b6e0000000p-7f), hn::Set(d, 0x1.4d72380000000p-5f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_110, hn::Set(d, 0x1.21dc500000000p+3f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_24, hn::Set(d, 0x1.1d92280000000p-8f)),
                        hn::Set(d, 0x1.792fd60000000p-6f), hn::Set(d, -0x1.5795c00000000p-7f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_60, hn::Set(d, 0x1.0000000000000p-1f)),
                        node_9, hn::Set(d, -0x1.9bcb9a0000000p-5f));
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_67, hn::Set(d, 0x1.0000000000000p+0f)),
                        node_3, node_4);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.193ea80000000p+1f)),
                        hn::Set(d, -0x1.8e88800000000p-5f), hn::Set(d, 0x1.15ba4c0000000p-5f));
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_83, hn::Set(d, 0x1.b6db6e0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_13 = LoadFeature(d, features + row * 164 + 13, 164);
                /* Tree 9: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_21, hn::Set(d, 0x1.c6c93a0000000p-13f)),
                        hn::Set(d, -0x1.2ac9e40000000p-5f), hn::Set(d, -0x1.6c49500000000p-7f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_85, hn::Set(d, 0x1.6666660000000p-2f)),
                        hn::Set(d, -0x1.7c38e40000000p-5f), hn::Set(d, 0x1.bb74b60000000p-8f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_100, hn::Set(d, 0x1.6a09e60000000p-1f)),
                        node_7, node_8);
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_106, hn::Set(d, 0x1.2302ca0000000p+1f)),
                        hn::Set(d, 0x1.46234a0000000p-7f), hn::Set(d, 0x1.738be80000000p-5f));
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_156, hn::Set(d, 0x1.62e4300000000p-1f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_140, hn::Set(d, 0x1.f746100000000p+1f)),
                        hn::Set(d, 0x1.6834d00000000p-6f), hn::Set(d, 0x1.aa5eac0000000p-8f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_13, hn::Set(d, 0x1.84f00c0000000p-10f)),
                        hn::Set(d, -0x1.93dc580000000p-5f), hn::Set(d, -0x1.5233480000000p-7f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.5a31760000000p+3f)),
                        node_11, node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_154, hn::Set(d, 0x1.8000000000000p-1f)),
                        hn::Set(d, -0x1.96dc7c0000000p-8f), hn::Set(d, -0x1.8776ea0000000p-5f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_95, hn::Set(d, 0x1.e360ea0000000p+2f)),
                        hn::Set(d, 0x1.6924880000000p-7f), hn::Set(d, 0x1.594a540000000p-5f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.26bb1c0000000p+1f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_13, hn::Set(d, 0x1.2345680000000p-7f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.72c1100000000p-1f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 10: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_5, hn::Set(d, 0x1.45828c0000000p-7f)),
                        hn::Set(d, -0x1.1201f60000000p-5f), hn::Set(d, -0x1.37679a0000000p-9f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_100, hn::Set(d, 0x1.99999a0000000p-3f)),
                        node_7, hn::Set(d, -0x1.70e65e0000000p-5f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_3, hn::Set(d, 0x1.75f50c0000000p-10f)),
                        hn::Set(d, -0x1.541d0a0000000p-11f), hn::Set(d, 0x1.5353aa0000000p-5f));
                    const auto node_1 = hn::IfThenElse(hn::Ge(feature_52, hn::Set(d, 0x1.5b50c60000000p-1f)),
                        node_4, node_3);
                    const auto node_11 = hn::IfThenElse(hn::Ge(feature_24, hn::Set(d, 0x1.1a636e0000000p-4f)),
                        hn::Set(d, 0x1.df5e220000000p-8f), hn::Set(d, -0x1.bb6ffe0000000p-7f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_67, hn::Set(d, 0x1.0000000000000p+0f)),
                        hn::Set(d, 0x1.81c74a0000000p-7f), hn::Set(d, -0x1.5a99420000000p-5f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_15, hn::Set(d, 0x1.5555560000000p-2f)),
                        node_11, node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_55, hn::Set(d, 0x1.cab0c00000000p+0f)),
                        hn::Set(d, -0x1.634d260000000p-5f), hn::Set(d, 0x1.27d4d00000000p-6f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.4cefb80000000p+3f)),
                        hn::Set(d, 0x1.6da8de0000000p-5f), hn::Set(d, 0x1.27d4d00000000p-6f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.bf8d900000000p+1f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Ge(feature_53, hn::Set(d, 0x1.0000000000000p+0f)),
                        node_6, node_5);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.4637640000000p-1f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_141 = LoadFeature(d, features + row * 164 + 141, 164);
                /* Tree 11: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.042ab40000000p-1f)),
                        hn::Set(d, -0x1.2d8b960000000p-5f), hn::Set(d, -0x1.e330f80000000p-9f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_141, hn::Set(d, 0x1.3e116c0000000p+1f)),
                        hn::Set(d, 0x1.1e3a5c0000000p-6f), hn::Set(d, -0x1.0bd5fe0000000p-7f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_110, hn::Set(d, 0x1.21dc500000000p+3f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_0, hn::Set(d, 0x1.25db2e0000000p+1f)),
                        hn::Set(d, 0x1.638b280000000p-6f), hn::Set(d, -0x1.94747e0000000p-7f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_60, hn::Set(d, 0x1.0000000000000p-1f)),
                        node_9, hn::Set(d, -0x1.881e9c0000000p-5f));
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_67, hn::Set(d, 0x1.0000000000000p+0f)),
                        node_3, node_4);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.193ea80000000p+1f)),
                        hn::Set(d, -0x1.7acd580000000p-5f), hn::Set(d, 0x1.0cb8480000000p-5f));
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_83, hn::Set(d, 0x1.b6db6e0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 12: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Ge(feature_2, hn::Set(d, 0x1.781b2a0000000p-1f)),
                        hn::Set(d, -0x1.1779da0000000p-9f), hn::Set(d, -0x1.630bce0000000p-6f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_140, hn::Set(d, 0x1.22c5580000000p+2f)),
                        hn::Set(d, 0x1.cbf1240000000p-7f), hn::Set(d, -0x1.e958d00000000p-6f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_110, hn::Set(d, 0x1.21dc500000000p+3f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_0, hn::Set(d, 0x1.25db2e0000000p+1f)),
                        hn::Set(d, 0x1.7268dc0000000p-6f), hn::Set(d, -0x1.8fbeea0000000p-7f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_60, hn::Set(d, 0x1.0000000000000p-1f)),
                        node_9, hn::Set(d, -0x1.7f74a60000000p-5f));
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_67, hn::Set(d, 0x1.0000000000000p+0f)),
                        node_3, node_4);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.193ea80000000p+1f)),
                        hn::Set(d, -0x1.73418e0000000p-5f), hn::Set(d, 0x1.11062a0000000p-5f));
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_83, hn::Set(d, 0x1.b6db6e0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_61 = LoadFeature(d, features + row * 164 + 61, 164);
                const auto feature_125 = LoadFeature(d, features + row * 164 + 125, 164);
                /* Tree 13: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_5, hn::Set(d, 0x1.45828c0000000p-7f)),
                        hn::Set(d, -0x1.0a2a420000000p-5f), hn::Set(d, -0x1.a8d4800000000p-9f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_100, hn::Set(d, 0x1.99999a0000000p-3f)),
                        node_7, hn::Set(d, -0x1.5e9bce0000000p-5f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_61, hn::Set(d, 0x1.bd85e00000000p+2f)),
                        hn::Set(d, 0x1.49793c0000000p-5f), hn::Set(d, 0x1.ed95ee0000000p-8f));
                    const auto node_1 = hn::IfThenElse(hn::Ge(feature_52, hn::Set(d, 0x1.5b50c60000000p-1f)),
                        node_4, node_3);
                    const auto node_11 = hn::IfThenElse(hn::Ge(feature_52, hn::Set(d, 0x1.338c7e0000000p-1f)),
                        hn::Set(d, -0x1.c323f20000000p-7f), hn::Set(d, -0x1.89d3580000000p-5f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_125, hn::Set(d, 0x1.32ee3c0000000p+1f)),
                        hn::Set(d, 0x1.2733b00000000p-6f), hn::Set(d, -0x1.b3d2500000000p-8f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_103, hn::Set(d, 0x1.594ab80000000p-2f)),
                        node_11, node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_154, hn::Set(d, 0x1.8000000000000p-1f)),
                        hn::Set(d, -0x1.1f08da0000000p-8f), hn::Set(d, -0x1.749c6c0000000p-5f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_88, hn::Set(d, 0x1.a13b640000000p-1f)),
                        hn::Set(d, 0x1.6218100000000p-7f), hn::Set(d, 0x1.40def20000000p-5f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.26bb1c0000000p+1f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_13, hn::Set(d, 0x1.c71c720000000p-8f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.4637640000000p-1f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_108 = LoadFeature(d, features + row * 164 + 108, 164);
                /* Tree 14: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_21, hn::Set(d, 0x1.05a9ec0000000p-12f)),
                        hn::Set(d, -0x1.139de20000000p-5f), hn::Set(d, -0x1.3a180a0000000p-7f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_85, hn::Set(d, 0x1.6666660000000p-2f)),
                        hn::Set(d, -0x1.5e6f420000000p-5f), hn::Set(d, 0x1.ab3ba40000000p-8f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_100, hn::Set(d, 0x1.6a09e60000000p-1f)),
                        node_7, node_8);
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_106, hn::Set(d, 0x1.2302ca0000000p+1f)),
                        hn::Set(d, 0x1.d853bc0000000p-8f), hn::Set(d, 0x1.5a61920000000p-5f));
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_156, hn::Set(d, 0x1.62e4300000000p-1f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_108, hn::Set(d, 0x1.1e377a0000000p+0f)),
                        hn::Set(d, 0x1.7317ac0000000p-7f), hn::Set(d, 0x1.04624a0000000p-5f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_13, hn::Set(d, 0x1.58791a0000000p-10f)),
                        hn::Set(d, -0x1.70ef9a0000000p-5f), hn::Set(d, -0x1.1d21040000000p-7f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.5a31760000000p+3f)),
                        node_11, node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_154, hn::Set(d, 0x1.8000000000000p-1f)),
                        hn::Set(d, -0x1.d5f5ca0000000p-9f), hn::Set(d, -0x1.6ce92a0000000p-5f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_95, hn::Set(d, 0x1.eab3f80000000p+2f)),
                        hn::Set(d, 0x1.4d0d7c0000000p-7f), hn::Set(d, 0x1.36fbda0000000p-5f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.26bb1c0000000p+1f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_13, hn::Set(d, 0x1.c71c720000000p-8f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.72c1100000000p-1f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_160 = LoadFeature(d, features + row * 164 + 160, 164);
                /* Tree 15: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_15, hn::Set(d, 0x1.5555560000000p-2f)),
                        hn::Set(d, -0x1.0375c80000000p-7f), hn::Set(d, 0x1.3a28460000000p-7f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.ab68a00000000p-5f)),
                        hn::Set(d, 0x1.30fc000000000p-8f), hn::Set(d, 0x1.45b6040000000p-5f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_102, hn::Set(d, 0x1.c466680000000p+4f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_0, hn::Set(d, 0x1.25db2e0000000p+1f)),
                        hn::Set(d, 0x1.8925ac0000000p-6f), hn::Set(d, -0x1.953d780000000p-7f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_60, hn::Set(d, 0x1.0000000000000p-1f)),
                        node_9, hn::Set(d, -0x1.74f8240000000p-5f));
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_67, hn::Set(d, 0x1.0000000000000p+0f)),
                        node_3, node_4);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.193ea80000000p+1f)),
                        hn::Set(d, -0x1.6256040000000p-5f), hn::Set(d, 0x1.eab18e0000000p-6f));
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_83, hn::Set(d, 0x1.b6db6e0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_66 = LoadFeature(d, features + row * 164 + 66, 164);
                const auto feature_70 = LoadFeature(d, features + row * 164 + 70, 164);
                /* Tree 16: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_5, hn::Set(d, 0x1.45828c0000000p-7f)),
                        hn::Set(d, -0x1.f561840000000p-6f), hn::Set(d, -0x1.a71d200000000p-9f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_100, hn::Set(d, 0x1.99999a0000000p-3f)),
                        node_7, hn::Set(d, -0x1.4feece0000000p-5f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_66, hn::Set(d, 0x1.3333340000000p-2f)),
                        hn::Set(d, 0x1.47aef00000000p-5f), hn::Set(d, 0x1.77d0820000000p-7f));
                    const auto node_1 = hn::IfThenElse(hn::Ge(feature_52, hn::Set(d, 0x1.e4dfb00000000p-1f)),
                        node_4, node_3);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_154, hn::Set(d, 0x1.4000000000000p-1f)),
                        hn::Set(d, -0x1.1020500000000p-7f), hn::Set(d, -0x1.661b700000000p-5f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_102, hn::Set(d, 0x1.9072f60000000p+4f)),
                        hn::Set(d, 0x1.0306760000000p-7f), hn::Set(d, 0x1.2c62e60000000p-5f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.26bb1c0000000p+1f)),
                        node_11, node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_70, hn::Set(d, 0x1.aaaaaa0000000p-2f)),
                        hn::Set(d, 0x1.3d3bec0000000p-8f), hn::Set(d, -0x1.743a520000000p-6f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_67, hn::Set(d, 0x1.e666660000000p-1f)),
                        hn::Set(d, 0x1.366cde0000000p-6f), hn::Set(d, -0x1.4cd13a0000000p-5f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_110, hn::Set(d, 0x1.1ccf640000000p+3f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.876ac60000000p+2f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.4637640000000p-1f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_63 = LoadFeature(d, features + row * 164 + 63, 164);
                const auto feature_77 = LoadFeature(d, features + row * 164 + 77, 164);
                /* Tree 17: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_21, hn::Set(d, 0x1.05a9ec0000000p-12f)),
                        hn::Set(d, -0x1.0e1a400000000p-5f), hn::Set(d, -0x1.4920660000000p-7f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_100, hn::Set(d, 0x1.6a09e60000000p-1f)),
                        node_7, hn::Set(d, -0x1.50417c0000000p-5f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_110, hn::Set(d, 0x1.1335180000000p+3f)),
                        hn::Set(d, 0x1.32e3520000000p-7f), hn::Set(d, 0x1.59114e0000000p-5f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_77, hn::Set(d, 0x1.99999a0000000p-5f)),
                        hn::Set(d, -0x1.b793aa0000000p-6f), node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_85, hn::Set(d, 0x1.47ae140000000p-3f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_154, hn::Set(d, 0x1.6db6dc0000000p-1f)),
                        hn::Set(d, -0x1.56d7580000000p-8f), hn::Set(d, -0x1.5e5cf60000000p-5f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_154, hn::Set(d, 0x1.3333340000000p-1f)),
                        hn::Set(d, 0x1.17bce40000000p-7f), hn::Set(d, 0x1.0fcac40000000p-5f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.193ea80000000p+1f)),
                        node_11, node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_63, hn::Set(d, 0x1.6aaaaa0000000p-2f)),
                        hn::Set(d, 0x1.fc82ba0000000p-7f), hn::Set(d, -0x1.6ee1b60000000p-5f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_13, hn::Set(d, 0x1.58791a0000000p-10f)),
                        hn::Set(d, -0x1.5e93420000000p-5f), hn::Set(d, -0x1.eb1b120000000p-8f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.5a31760000000p+3f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.9d3bb60000000p+2f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.72c1100000000p-1f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_18 = LoadFeature(d, features + row * 164 + 18, 164);
                const auto feature_65 = LoadFeature(d, features + row * 164 + 65, 164);
                const auto feature_93 = LoadFeature(d, features + row * 164 + 93, 164);
                /* Tree 18: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_18, hn::Set(d, 0x1.1a1f580000000p-1f)),
                        hn::Set(d, -0x1.08de600000000p-8f), hn::Set(d, -0x1.90d83e0000000p-6f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_50, hn::Set(d, 0x1.f7a65c0000000p+0f)),
                        hn::Set(d, 0x1.2cfe060000000p-7f), hn::Set(d, -0x1.5308e20000000p-5f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_100, hn::Set(d, 0x1.6a09e60000000p-1f)),
                        node_7, node_8);
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_93, hn::Set(d, 0x1.bb67ae0000000p-1f)),
                        hn::Set(d, 0x1.2d1e880000000p-7f), hn::Set(d, 0x1.47a3920000000p-5f));
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_156, hn::Set(d, 0x1.62e4300000000p-1f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.193ea80000000p+1f)),
                        hn::Set(d, -0x1.39c33a0000000p-7f), hn::Set(d, 0x1.566d7a0000000p-6f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_63, hn::Set(d, 0x1.6aaaaa0000000p-2f)),
                        hn::Set(d, 0x1.9a89ee0000000p-7f), hn::Set(d, -0x1.6c53800000000p-5f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.6d0ac60000000p+2f)),
                        node_11, node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_21, hn::Set(d, 0x1.7008480000000p-9f)),
                        hn::Set(d, -0x1.51d0d60000000p-6f), hn::Set(d, 0x1.49409e0000000p-10f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_65, hn::Set(d, 0x1.27350c0000000p-6f)),
                        hn::Set(d, -0x1.51d0d60000000p-6f), hn::Set(d, -0x1.2ac24a0000000p-5f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_162, hn::Set(d, 0x1.7b425e0000000p-3f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_70, hn::Set(d, 0x1.aaaaaa0000000p-2f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.8cfc700000000p-1f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 19: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_15, hn::Set(d, 0x1.5555560000000p-2f)),
                        hn::Set(d, -0x1.dfc7f60000000p-8f), hn::Set(d, 0x1.24695c0000000p-7f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.ab68a00000000p-5f)),
                        hn::Set(d, 0x1.3ce7120000000p-8f), hn::Set(d, 0x1.2dd3340000000p-5f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_102, hn::Set(d, 0x1.c466680000000p+4f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.8618620000000p-4f)),
                        hn::Set(d, -0x1.16da240000000p-6f), hn::Set(d, 0x1.2d9f9c0000000p-6f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_60, hn::Set(d, 0x1.0000000000000p-1f)),
                        node_9, hn::Set(d, -0x1.6354120000000p-5f));
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_67, hn::Set(d, 0x1.0000000000000p+0f)),
                        node_3, node_4);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.193ea80000000p+1f)),
                        hn::Set(d, -0x1.52f7a40000000p-5f), hn::Set(d, 0x1.cc0d2a0000000p-6f));
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_83, hn::Set(d, 0x1.b6db6e0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_84 = LoadFeature(d, features + row * 164 + 84, 164);
                const auto feature_142 = LoadFeature(d, features + row * 164 + 142, 164);
                /* Tree 20: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_84, hn::Set(d, 0x1.6666660000000p-1f)),
                        hn::Set(d, -0x1.28d52e0000000p-5f), hn::Set(d, 0x1.93835a0000000p-9f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_142, hn::Set(d, 0x1.99999a0000000p-3f)),
                        hn::Set(d, -0x1.302b460000000p-6f), hn::Set(d, 0x1.3e456c0000000p-7f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.042ab40000000p-1f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_141, hn::Set(d, 0x1.5aa1640000000p+1f)),
                        hn::Set(d, -0x1.3219a40000000p-9f), hn::Set(d, -0x1.e642040000000p-6f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.ab68a00000000p-5f)),
                        hn::Set(d, -0x1.3f63de0000000p-15f), hn::Set(d, 0x1.0e5d7c0000000p-6f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.9d3bb60000000p+2f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Ge(feature_2, hn::Set(d, 0x1.781b2a0000000p-1f)),
                        node_4, node_3);
                    const auto node_12 = hn::IfThenElse(hn::Ge(feature_3, hn::Set(d, 0x1.6b957c0000000p-10f)),
                        hn::Set(d, 0x1.40f89a0000000p-6f), hn::Set(d, 0x1.3f450c0000000p-8f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.d316740000000p-2f)),
                        hn::Set(d, -0x1.3fddb40000000p-5f), node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_154, hn::Set(d, 0x1.3333340000000p-1f)),
                        hn::Set(d, 0x1.40f89a0000000p-6f), hn::Set(d, 0x1.52f8a60000000p-5f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.4cefb80000000p+3f)),
                        node_13, hn::Set(d, 0x1.40f89a0000000p-6f));
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.bf8d900000000p+1f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Ge(feature_53, hn::Set(d, 0x1.0000000000000p+0f)),
                        node_2, node_1);
                    score = hn::Add(score, node_0);
                }
                const auto feature_4 = LoadFeature(d, features + row * 164 + 4, 164);
                /* Tree 21: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_4, hn::Set(d, 0x1.0000000000000p+0f)),
                        hn::Set(d, -0x1.1568180000000p-6f), hn::Set(d, -0x1.c641b20000000p-11f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_140, hn::Set(d, 0x1.22c5580000000p+2f)),
                        hn::Set(d, 0x1.9340780000000p-7f), hn::Set(d, -0x1.cfc9740000000p-6f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_110, hn::Set(d, 0x1.2092c20000000p+3f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_13, hn::Set(d, 0x1.5186440000000p-9f)),
                        hn::Set(d, 0x1.fc19fc0000000p-6f), hn::Set(d, -0x1.1b952a0000000p-7f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_60, hn::Set(d, 0x1.0000000000000p-1f)),
                        node_9, hn::Set(d, -0x1.5d4aaa0000000p-5f));
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_67, hn::Set(d, 0x1.0000000000000p+0f)),
                        node_3, node_4);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.193ea80000000p+1f)),
                        hn::Set(d, -0x1.4c87600000000p-5f), hn::Set(d, 0x1.c9d5220000000p-6f));
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_83, hn::Set(d, 0x1.b6db6e0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_6 = LoadFeature(d, features + row * 164 + 6, 164);
                const auto feature_31 = LoadFeature(d, features + row * 164 + 31, 164);
                /* Tree 22: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_84, hn::Set(d, 0x1.6666660000000p-1f)),
                        hn::Set(d, -0x1.2049e60000000p-5f), hn::Set(d, 0x1.d924680000000p-9f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_31, hn::Set(d, -0x1.3333340000000p-1f)),
                        hn::Set(d, -0x1.e8ea3c0000000p-8f), hn::Set(d, -0x1.aa99a00000000p-6f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.042ab40000000p-1f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_141, hn::Set(d, 0x1.5aa1640000000p+1f)),
                        hn::Set(d, -0x1.659e640000000p-9f), hn::Set(d, -0x1.cc831a0000000p-6f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_154, hn::Set(d, 0x1.8000000000000p-1f)),
                        hn::Set(d, 0x1.7f53a20000000p-7f), hn::Set(d, -0x1.3bae720000000p-5f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.9d3bb60000000p+2f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Ge(feature_2, hn::Set(d, 0x1.72c1100000000p-1f)),
                        node_4, node_3);
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_6, hn::Set(d, 0x1.5555560000000p-3f)),
                        hn::Set(d, 0x1.9f5b360000000p-6f), hn::Set(d, -0x1.29324c0000000p-5f));
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_80, hn::Set(d, 0x1.dc47720000000p-4f)),
                        hn::Set(d, -0x1.dcb29c0000000p-7f), hn::Set(d, 0x1.18338e0000000p-6f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_63, hn::Set(d, 0x1.579fca0000000p-3f)),
                        hn::Set(d, 0x1.4636220000000p-5f), hn::Set(d, 0x1.e66c120000000p-13f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_103, hn::Set(d, 0x1.6e66460000000p+1f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_77, hn::Set(d, 0x1.8618620000000p-5f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Ge(feature_53, hn::Set(d, 0x1.0000000000000p+0f)),
                        node_2, node_1);
                    score = hn::Add(score, node_0);
                }
                /* Tree 23: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_70, hn::Set(d, 0x1.aaaaaa0000000p-2f)),
                        hn::Set(d, -0x1.6ddfee0000000p-9f), hn::Set(d, -0x1.8d334e0000000p-6f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_141, hn::Set(d, 0x1.3e116c0000000p+1f)),
                        hn::Set(d, 0x1.c333be0000000p-7f), hn::Set(d, -0x1.e8ec9a0000000p-8f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_110, hn::Set(d, 0x1.2092c20000000p+3f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_13, hn::Set(d, 0x1.5186440000000p-9f)),
                        hn::Set(d, 0x1.e7d8580000000p-6f), hn::Set(d, -0x1.c1359a0000000p-8f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_60, hn::Set(d, 0x1.0000000000000p-1f)),
                        node_9, hn::Set(d, -0x1.5735820000000p-5f));
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_67, hn::Set(d, 0x1.0000000000000p+0f)),
                        node_3, node_4);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.193ea80000000p+1f)),
                        hn::Set(d, -0x1.4643a60000000p-5f), hn::Set(d, 0x1.c418b20000000p-6f));
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_83, hn::Set(d, 0x1.b6db6e0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_34 = LoadFeature(d, features + row * 164 + 34, 164);
                const auto feature_82 = LoadFeature(d, features + row * 164 + 82, 164);
                /* Tree 24: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_34, hn::Set(d, -0x1.6db6dc0000000p-1f)),
                        hn::Set(d, -0x1.1a7ca20000000p-6f), hn::Set(d, -0x1.130b5e0000000p-5f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_31, hn::Set(d, -0x1.5555540000000p-2f)),
                        hn::Set(d, 0x1.1a384a0000000p-5f), hn::Set(d, -0x1.7fefea0000000p-6f));
                    const auto node_3 = hn::IfThenElse(hn::Ge(feature_53, hn::Set(d, 0x1.0000000000000p-2f)),
                        node_8, node_7);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.26bb1c0000000p+1f)),
                        hn::Set(d, -0x1.33c8680000000p-7f), hn::Set(d, 0x1.1ae5060000000p-6f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_162, hn::Set(d, 0x1.d1745e0000000p-3f)),
                        hn::Set(d, 0x1.4c0f4e0000000p-7f), hn::Set(d, -0x1.95acb00000000p-7f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.876ac60000000p+2f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Ge(feature_2, hn::Set(d, 0x1.4637640000000p-1f)),
                        node_4, node_3);
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_82, hn::Set(d, 0x1.76fc640000000p-4f)),
                        hn::Set(d, -0x1.273be60000000p-5f), hn::Set(d, 0x1.4887ee0000000p-6f));
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_154, hn::Set(d, 0x1.3333340000000p-1f)),
                        hn::Set(d, 0x1.4887ee0000000p-6f), hn::Set(d, 0x1.46b9e80000000p-5f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.4cefb80000000p+3f)),
                        node_13, hn::Set(d, 0x1.4887ee0000000p-6f));
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.bf8d900000000p+1f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Ge(feature_53, hn::Set(d, 0x1.0000000000000p+0f)),
                        node_2, node_1);
                    score = hn::Add(score, node_0);
                }
                const auto feature_145 = LoadFeature(d, features + row * 164 + 145, 164);
                /* Tree 25: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_15, hn::Set(d, 0x1.5555560000000p-2f)),
                        hn::Set(d, -0x1.9487b60000000p-8f), hn::Set(d, 0x1.405b7e0000000p-7f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_31, hn::Set(d, -0x1.3333340000000p-1f)),
                        hn::Set(d, -0x1.e4826e0000000p-8f), hn::Set(d, -0x1.fbad780000000p-6f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_162, hn::Set(d, 0x1.e1e1e20000000p-3f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_82, hn::Set(d, 0x1.745d180000000p-4f)),
                        hn::Set(d, -0x1.60ab7a0000000p-6f), hn::Set(d, 0x1.89ab760000000p-7f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.99999a0000000p-6f)),
                        hn::Set(d, 0x1.e000da0000000p-10f), hn::Set(d, 0x1.1d43a20000000p-5f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_145, hn::Set(d, 0x1.435e500000000p-3f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_80, hn::Set(d, 0x1.6ece540000000p-4f)),
                        node_3, node_4);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.193ea80000000p+1f)),
                        hn::Set(d, -0x1.41ad460000000p-5f), hn::Set(d, 0x1.b3f55c0000000p-6f));
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_83, hn::Set(d, 0x1.b6db6e0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 26: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_21, hn::Set(d, 0x1.27fc6a0000000p-12f)),
                        hn::Set(d, -0x1.a1debc0000000p-6f), hn::Set(d, -0x1.bc5e420000000p-9f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_50, hn::Set(d, 0x1.f7a65c0000000p+0f)),
                        hn::Set(d, 0x1.4036600000000p-7f), hn::Set(d, -0x1.39b5a20000000p-5f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_100, hn::Set(d, 0x1.89bd640000000p-1f)),
                        node_7, node_8);
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_103, hn::Set(d, 0x1.ee924a0000000p+1f)),
                        hn::Set(d, 0x1.9479b00000000p-7f), hn::Set(d, 0x1.367e340000000p-5f));
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_156, hn::Set(d, 0x1.62e4300000000p-1f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_154, hn::Set(d, 0x1.4000000000000p-1f)),
                        hn::Set(d, -0x1.52411e0000000p-8f), hn::Set(d, -0x1.49aacc0000000p-5f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_102, hn::Set(d, 0x1.9072f60000000p+4f)),
                        hn::Set(d, 0x1.b1674a0000000p-8f), hn::Set(d, 0x1.001f380000000p-5f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.26bb1c0000000p+1f)),
                        node_11, node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_5, hn::Set(d, 0x1.99999a0000000p-4f)),
                        hn::Set(d, 0x1.5c328a0000000p-8f), hn::Set(d, 0x1.439af20000000p-6f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_13, hn::Set(d, 0x1.84f00c0000000p-10f)),
                        hn::Set(d, -0x1.43c1c60000000p-5f), hn::Set(d, -0x1.3e084e0000000p-7f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.5a31760000000p+3f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.876ac60000000p+2f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.944ed00000000p-1f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 27: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.b8259e0000000p+2f)),
                        hn::Set(d, -0x1.08be060000000p-7f), hn::Set(d, 0x1.ad464e0000000p-8f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_147, hn::Set(d, 0x1.99999a0000000p-3f)),
                        hn::Set(d, 0x1.9ef0b20000000p-7f), hn::Set(d, -0x1.72e6840000000p-5f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_110, hn::Set(d, 0x1.4078be0000000p+3f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_18, hn::Set(d, 0x1.5473400000000p-2f)),
                        hn::Set(d, 0x1.0b422c0000000p-5f), hn::Set(d, -0x1.b134c40000000p-9f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_60, hn::Set(d, 0x1.0000000000000p-1f)),
                        node_9, hn::Set(d, -0x1.4d8dcc0000000p-5f));
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_67, hn::Set(d, 0x1.0000000000000p+0f)),
                        node_3, node_4);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.193ea80000000p+1f)),
                        hn::Set(d, -0x1.3b9e0c0000000p-5f), hn::Set(d, 0x1.a180780000000p-6f));
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_83, hn::Set(d, 0x1.b6db6e0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_42 = LoadFeature(d, features + row * 164 + 42, 164);
                /* Tree 28: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_85, hn::Set(d, 0x1.bbbbbc0000000p-3f)),
                        hn::Set(d, -0x1.124ea20000000p-5f), hn::Set(d, 0x1.a4c6ac0000000p-6f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_100, hn::Set(d, 0x1.0c9f540000000p+2f)),
                        hn::Set(d, -0x1.c014fe0000000p-8f), hn::Set(d, -0x1.f90f9e0000000p-6f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_21, hn::Set(d, 0x1.c6c93a0000000p-13f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_42, hn::Set(d, 0x1.aa85ae0000000p+1f)),
                        hn::Set(d, -0x1.2457a40000000p-12f), hn::Set(d, -0x1.796ce00000000p-6f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.5a31760000000p+3f)),
                        hn::Set(d, 0x1.0ece800000000p-6f), hn::Set(d, -0x1.1488140000000p-6f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.b726480000000p+2f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Ge(feature_2, hn::Set(d, 0x1.781b2a0000000p-1f)),
                        node_4, node_3);
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.d316740000000p-2f)),
                        hn::Set(d, -0x1.216fe60000000p-5f), hn::Set(d, 0x1.3fb64a0000000p-6f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_154, hn::Set(d, 0x1.3333340000000p-1f)),
                        hn::Set(d, 0x1.3fb64a0000000p-6f), hn::Set(d, 0x1.3d433a0000000p-5f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_103, hn::Set(d, 0x1.d2de9c0000000p+1f)),
                        hn::Set(d, 0x1.3fb64a0000000p-6f), node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.bf8d900000000p+1f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Ge(feature_53, hn::Set(d, 0x1.0000000000000p+0f)),
                        node_2, node_1);
                    score = hn::Add(score, node_0);
                }
                /* Tree 29: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_15, hn::Set(d, 0x1.5555560000000p-2f)),
                        hn::Set(d, -0x1.a8f3aa0000000p-8f), hn::Set(d, 0x1.ef21720000000p-8f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.ab68a00000000p-5f)),
                        hn::Set(d, 0x1.03c71a0000000p-8f), hn::Set(d, 0x1.13e7600000000p-5f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_102, hn::Set(d, 0x1.c466680000000p+4f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_13, hn::Set(d, 0x1.5186440000000p-9f)),
                        hn::Set(d, 0x1.b788780000000p-6f), hn::Set(d, -0x1.af4f240000000p-8f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_60, hn::Set(d, 0x1.0000000000000p-1f)),
                        node_9, hn::Set(d, -0x1.4880c40000000p-5f));
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_67, hn::Set(d, 0x1.e666660000000p-1f)),
                        node_3, node_4);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.193ea80000000p+1f)),
                        hn::Set(d, -0x1.373bca0000000p-5f), hn::Set(d, 0x1.9590140000000p-6f));
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_83, hn::Set(d, 0x1.b6db6e0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_12 = LoadFeature(d, features + row * 164 + 12, 164);
                const auto feature_44 = LoadFeature(d, features + row * 164 + 44, 164);
                /* Tree 30: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_34, hn::Set(d, -0x1.6db6dc0000000p-1f)),
                        hn::Set(d, -0x1.01c4b80000000p-6f), hn::Set(d, -0x1.02d5220000000p-5f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_12, hn::Set(d, 0x1.6816820000000p-4f)),
                        hn::Set(d, 0x1.1a97140000000p-5f), hn::Set(d, -0x1.5ea2120000000p-6f));
                    const auto node_3 = hn::IfThenElse(hn::Ge(feature_53, hn::Set(d, 0x1.0000000000000p-2f)),
                        node_8, node_7);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.dd6dde0000000p-1f)),
                        hn::Set(d, -0x1.7a8a840000000p-7f), hn::Set(d, 0x1.f37b680000000p-10f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_77, hn::Set(d, 0x1.0000000000000p-1f)),
                        hn::Set(d, 0x1.3e7e920000000p-7f), hn::Set(d, -0x1.17edec0000000p-5f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.9d3bb60000000p+2f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Ge(feature_2, hn::Set(d, 0x1.4637640000000p-1f)),
                        node_4, node_3);
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_44, hn::Set(d, 0x1.cbc14e0000000p-3f)),
                        hn::Set(d, 0x1.fb61780000000p-6f), hn::Set(d, -0x1.7a60880000000p-6f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_77, hn::Set(d, 0x1.af286c0000000p-5f)),
                        hn::Set(d, -0x1.199f3c0000000p-5f), node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_77, hn::Set(d, 0x1.99999a0000000p-4f)),
                        hn::Set(d, 0x1.55477c0000000p-6f), hn::Set(d, -0x1.6395ae0000000p-7f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_154, hn::Set(d, 0x1.3333340000000p-1f)),
                        hn::Set(d, 0x1.4bde8a0000000p-7f), hn::Set(d, 0x1.35c6d00000000p-5f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_103, hn::Set(d, 0x1.6e66460000000p+1f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_100, hn::Set(d, 0x1.6939460000000p+2f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Ge(feature_53, hn::Set(d, 0x1.0000000000000p+0f)),
                        node_2, node_1);
                    score = hn::Add(score, node_0);
                }
                const auto feature_41 = LoadFeature(d, features + row * 164 + 41, 164);
                const auto feature_43 = LoadFeature(d, features + row * 164 + 43, 164);
                const auto feature_139 = LoadFeature(d, features + row * 164 + 139, 164);
                /* Tree 31: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_19, hn::Set(d, 0x1.6a6a780000000p-6f)),
                        hn::Set(d, -0x1.acb4920000000p-6f), hn::Set(d, -0x1.1be6660000000p-7f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_9, hn::Set(d, 0x1.2c79720000000p+3f)),
                        hn::Set(d, -0x1.4bac7a0000000p-8f), hn::Set(d, 0x1.8ac0080000000p-6f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_44, hn::Set(d, 0x1.3716ae0000000p-5f)),
                        node_7, node_8);
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_93, hn::Set(d, 0x1.4629a20000000p+3f)),
                        hn::Set(d, -0x1.883aac0000000p-10f), hn::Set(d, 0x1.0698980000000p-5f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_43, hn::Set(d, 0x1.2bb5120000000p-3f)),
                        hn::Set(d, -0x1.3bcbaa0000000p-5f), node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_154, hn::Set(d, 0x1.3333340000000p-1f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_139, hn::Set(d, 0x1.4000000000000p-1f)),
                        hn::Set(d, -0x1.f2c42e0000000p-8f), hn::Set(d, 0x1.002dc60000000p-5f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_141, hn::Set(d, 0x1.62e4300000000p+1f)),
                        hn::Set(d, 0x1.9793620000000p-7f), hn::Set(d, -0x1.d6a2d60000000p-7f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.6d0ac60000000p+2f)),
                        node_11, node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_41, hn::Set(d, 0x1.cab0c00000000p+1f)),
                        hn::Set(d, 0x1.49b0e60000000p-6f), hn::Set(d, -0x1.c85fe20000000p-7f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_60, hn::Set(d, 0x1.0000000000000p-1f)),
                        node_13, hn::Set(d, -0x1.44e2e00000000p-5f));
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_67, hn::Set(d, 0x1.e666660000000p-1f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_110, hn::Set(d, 0x1.d376100000000p+2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 32: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_18, hn::Set(d, 0x1.1a1f580000000p-1f)),
                        hn::Set(d, -0x1.d96c520000000p-9f), hn::Set(d, -0x1.4489420000000p-6f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_156, hn::Set(d, 0x1.62e4300000000p-1f)),
                        hn::Set(d, -0x1.2b29e80000000p-5f), hn::Set(d, 0x1.7df3ec0000000p-8f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_100, hn::Set(d, 0x1.7127ae0000000p-1f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_42, hn::Set(d, 0x1.aa85ae0000000p+1f)),
                        hn::Set(d, 0x1.5b43b80000000p-11f), hn::Set(d, -0x1.8231c20000000p-6f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.5a31760000000p+3f)),
                        hn::Set(d, 0x1.0a8ca40000000p-6f), hn::Set(d, -0x1.3fdcc20000000p-6f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.b726480000000p+2f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Ge(feature_2, hn::Set(d, 0x1.8fd1440000000p-1f)),
                        node_4, node_3);
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_6, hn::Set(d, 0x1.5555560000000p-3f)),
                        hn::Set(d, 0x1.8a72520000000p-6f), hn::Set(d, -0x1.f1a0f60000000p-6f));
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_80, hn::Set(d, 0x1.dc47720000000p-4f)),
                        hn::Set(d, -0x1.df15ee0000000p-7f), hn::Set(d, 0x1.0ade160000000p-6f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_63, hn::Set(d, 0x1.579fca0000000p-3f)),
                        hn::Set(d, 0x1.2c0bd00000000p-5f), hn::Set(d, -0x1.280f7e0000000p-8f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_103, hn::Set(d, 0x1.6e66460000000p+1f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_77, hn::Set(d, 0x1.8618620000000p-5f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Ge(feature_53, hn::Set(d, 0x1.0000000000000p+0f)),
                        node_2, node_1);
                    score = hn::Add(score, node_0);
                }
                /* Tree 33: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_100, hn::Set(d, 0x1.6a09e60000000p-1f)),
                        hn::Set(d, -0x1.e6052e0000000p-7f), hn::Set(d, -0x1.25eef00000000p-5f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.eb1a200000000p-1f)),
                        hn::Set(d, 0x1.e189f40000000p-6f), hn::Set(d, -0x1.830cf40000000p-7f));
                    const auto node_3 = hn::IfThenElse(hn::Ge(feature_53, hn::Set(d, 0x1.0000000000000p-2f)),
                        node_8, node_7);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_70, hn::Set(d, 0x1.aaaaaa0000000p-2f)),
                        hn::Set(d, 0x1.96bd800000000p-8f), hn::Set(d, -0x1.1288140000000p-6f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_55, hn::Set(d, 0x1.9c04200000000p+0f)),
                        hn::Set(d, -0x1.049a3e0000000p-6f), hn::Set(d, -0x1.1242d60000000p-9f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_18, hn::Set(d, 0x1.3a3caa0000000p-1f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Ge(feature_2, hn::Set(d, 0x1.781b2a0000000p-1f)),
                        node_4, node_3);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.f306d20000000p+2f)),
                        hn::Set(d, 0x1.9d16d00000000p-7f), hn::Set(d, 0x1.120e940000000p-5f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.b5b9b20000000p-1f)),
                        hn::Set(d, 0x1.86f0700000000p-6f), hn::Set(d, -0x1.478f3c0000000p-6f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.5a31760000000p+3f)),
                        node_11, node_12);
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_70, hn::Set(d, 0x1.5555560000000p-3f)),
                        hn::Set(d, -0x1.79fa3c0000000p-5f), hn::Set(d, -0x1.fc31300000000p-10f));
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_147, hn::Set(d, 0x1.99999a0000000p-3f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_142, hn::Set(d, 0x1.99999a0000000p-3f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_62 = LoadFeature(d, features + row * 164 + 62, 164);
                /* Tree 34: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.b8259e0000000p+2f)),
                        hn::Set(d, -0x1.dc60c20000000p-8f), hn::Set(d, 0x1.86b34e0000000p-8f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_141, hn::Set(d, 0x1.3e116c0000000p+1f)),
                        hn::Set(d, 0x1.c4f1060000000p-7f), hn::Set(d, -0x1.d124000000000p-8f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_110, hn::Set(d, 0x1.4078be0000000p+3f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_62, hn::Set(d, 0x1.cbc48a0000000p+2f)),
                        hn::Set(d, 0x1.12c2f00000000p-10f), hn::Set(d, 0x1.fcf1c60000000p-6f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_60, hn::Set(d, 0x1.0000000000000p-1f)),
                        node_9, hn::Set(d, -0x1.3fa4a60000000p-5f));
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_67, hn::Set(d, 0x1.0000000000000p+0f)),
                        node_3, node_4);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.193ea80000000p+1f)),
                        hn::Set(d, -0x1.2fad200000000p-5f), hn::Set(d, 0x1.9c8ee80000000p-6f));
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_83, hn::Set(d, 0x1.b6db6e0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_78 = LoadFeature(d, features + row * 164 + 78, 164);
                /* Tree 35: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_34, hn::Set(d, -0x1.6db6dc0000000p-1f)),
                        hn::Set(d, -0x1.c5d9d00000000p-7f), hn::Set(d, -0x1.ef0b760000000p-6f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_31, hn::Set(d, -0x1.5555540000000p-2f)),
                        hn::Set(d, 0x1.06c86c0000000p-5f), hn::Set(d, -0x1.7d2ef00000000p-6f));
                    const auto node_3 = hn::IfThenElse(hn::Ge(feature_53, hn::Set(d, 0x1.0000000000000p-2f)),
                        node_8, node_7);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_24, hn::Set(d, 0x1.1a636e0000000p-4f)),
                        hn::Set(d, -0x1.4cac4c0000000p-7f), hn::Set(d, 0x1.bbfe9a0000000p-8f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.5a31760000000p+3f)),
                        hn::Set(d, 0x1.243aaa0000000p-7f), hn::Set(d, -0x1.3e34540000000p-6f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_15, hn::Set(d, 0x1.5555560000000p-2f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Ge(feature_2, hn::Set(d, 0x1.4637640000000p-1f)),
                        node_4, node_3);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_0, hn::Set(d, 0x1.717f840000000p+1f)),
                        hn::Set(d, 0x1.d3b7ba0000000p-6f), hn::Set(d, 0x1.63d0480000000p-8f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_78, hn::Set(d, 0x1.6b17ba0000000p+2f)),
                        node_11, hn::Set(d, -0x1.047c420000000p-5f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.4cefb80000000p+3f)),
                        hn::Set(d, 0x1.29c8420000000p-5f), hn::Set(d, 0x1.27437e0000000p-7f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_93, hn::Set(d, 0x1.0000000000000p-1f)),
                        hn::Set(d, -0x1.6050920000000p-9f), node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_55, hn::Set(d, 0x1.193ea80000000p+0f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Ge(feature_53, hn::Set(d, 0x1.0000000000000p+0f)),
                        node_2, node_1);
                    score = hn::Add(score, node_0);
                }
                /* Tree 36: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_70, hn::Set(d, 0x1.aaaaaa0000000p-2f)),
                        hn::Set(d, -0x1.cf6f7a0000000p-10f), hn::Set(d, -0x1.4d347a0000000p-6f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_141, hn::Set(d, 0x1.3e116c0000000p+1f)),
                        hn::Set(d, 0x1.a137740000000p-7f), hn::Set(d, -0x1.ce682c0000000p-8f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_110, hn::Set(d, 0x1.3086480000000p+3f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_13, hn::Set(d, 0x1.5186440000000p-9f)),
                        hn::Set(d, 0x1.996e380000000p-6f), hn::Set(d, -0x1.8532fa0000000p-9f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_60, hn::Set(d, 0x1.0000000000000p-1f)),
                        node_9, hn::Set(d, -0x1.3c74780000000p-5f));
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_67, hn::Set(d, 0x1.e666660000000p-1f)),
                        node_3, node_4);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.193ea80000000p+1f)),
                        hn::Set(d, -0x1.2cb0140000000p-5f), hn::Set(d, 0x1.9d16240000000p-6f));
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_83, hn::Set(d, 0x1.b6db6e0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_20 = LoadFeature(d, features + row * 164 + 20, 164);
                const auto feature_74 = LoadFeature(d, features + row * 164 + 74, 164);
                const auto feature_124 = LoadFeature(d, features + row * 164 + 124, 164);
                /* Tree 37: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_15, hn::Set(d, 0x1.bbbbbc0000000p-2f)),
                        hn::Set(d, -0x1.87325e0000000p-9f), hn::Set(d, 0x1.2dd1a20000000p-7f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_63, hn::Set(d, 0x1.6aaaaa0000000p-2f)),
                        hn::Set(d, -0x1.40d0300000000p-7f), hn::Set(d, -0x1.2fcc860000000p-5f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_162, hn::Set(d, 0x1.f49f4a0000000p-3f)),
                        node_7, node_8);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_154, hn::Set(d, 0x1.8000000000000p-1f)),
                        node_3, hn::Set(d, -0x1.3ab69e0000000p-5f));
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_124, hn::Set(d, 0x1.26bb1c0000000p+1f)),
                        hn::Set(d, 0x1.f2c4d80000000p-6f), hn::Set(d, 0x1.2dd1a20000000p-7f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_74, hn::Set(d, 0x1.0822f80000000p+2f)),
                        hn::Set(d, 0x1.1c95560000000p-5f), hn::Set(d, 0x1.2dd1a20000000p-7f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_61, hn::Set(d, 0x1.a556940000000p+2f)),
                        node_9, node_10);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_20, hn::Set(d, 0x1.0424fa0000000p-3f)),
                        hn::Set(d, 0x1.2dd1a20000000p-7f), hn::Set(d, 0x1.00a6920000000p-5f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_88, hn::Set(d, 0x1.98526c0000000p-4f)),
                        hn::Set(d, 0x1.2dd1a20000000p-7f), hn::Set(d, 0x1.2635020000000p-5f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.ab68a00000000p-5f)),
                        node_11, node_12);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_102, hn::Set(d, 0x1.9072f60000000p+4f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.26bb1c0000000p+1f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 38: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_24, hn::Set(d, 0x1.1bd4180000000p-11f)),
                        hn::Set(d, -0x1.decaa60000000p-6f), hn::Set(d, -0x1.d7b4080000000p-8f));
                    const auto node_8 = hn::IfThenElse(hn::Ge(feature_2, hn::Set(d, 0x1.3fd9300000000p-1f)),
                        hn::Set(d, 0x1.add1a60000000p-6f), hn::Set(d, -0x1.3f65880000000p-7f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_74, hn::Set(d, 0x1.cab0c00000000p+0f)),
                        node_7, node_8);
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_50, hn::Set(d, 0x1.2595400000000p+2f)),
                        hn::Set(d, 0x1.01dcda0000000p-5f), hn::Set(d, 0x1.d330400000000p-12f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_43, hn::Set(d, 0x1.2bb5120000000p-3f)),
                        hn::Set(d, -0x1.2fcee20000000p-5f), node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_154, hn::Set(d, 0x1.3333340000000p-1f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.193ea80000000p+1f)),
                        hn::Set(d, -0x1.53129a0000000p-8f), hn::Set(d, 0x1.ab40020000000p-6f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.5a31760000000p+3f)),
                        hn::Set(d, 0x1.b19c300000000p-7f), hn::Set(d, -0x1.56c1fc0000000p-6f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_15, hn::Set(d, 0x1.6666660000000p-2f)),
                        node_11, node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.259c580000000p+3f)),
                        hn::Set(d, 0x1.3185c80000000p-6f), hn::Set(d, -0x1.1e2eba0000000p-8f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_60, hn::Set(d, 0x1.0000000000000p-1f)),
                        node_13, hn::Set(d, -0x1.37dc700000000p-5f));
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_67, hn::Set(d, 0x1.e666660000000p-1f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_110, hn::Set(d, 0x1.d376100000000p+2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_64 = LoadFeature(d, features + row * 164 + 64, 164);
                const auto feature_127 = LoadFeature(d, features + row * 164 + 127, 164);
                /* Tree 39: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_140, hn::Set(d, 0x1.0c234e0000000p+2f)),
                        hn::Set(d, -0x1.3c742e0000000p-6f), hn::Set(d, 0x1.3df5dc0000000p-6f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_19, hn::Set(d, 0x1.b80d2a0000000p-3f)),
                        hn::Set(d, -0x1.f9822c0000000p-6f), hn::Set(d, -0x1.013c520000000p-9f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_31, hn::Set(d, -0x1.b6db6e0000000p-1f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_41, hn::Set(d, 0x1.507ace0000000p+2f)),
                        hn::Set(d, -0x1.3c07700000000p-10f), hn::Set(d, -0x1.7fb3b20000000p-6f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_154, hn::Set(d, 0x1.3333340000000p-1f)),
                        hn::Set(d, 0x1.82e3460000000p-7f), hn::Set(d, -0x1.3d934a0000000p-5f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.b726480000000p+2f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Ge(feature_2, hn::Set(d, 0x1.42a8480000000p-1f)),
                        node_4, node_3);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_65, hn::Set(d, 0x1.e9131a0000000p-8f)),
                        hn::Set(d, -0x1.57d4980000000p-5f), hn::Set(d, 0x1.84e9580000000p-11f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_127, hn::Set(d, 0x1.69696a0000000p-3f)),
                        hn::Set(d, -0x1.010fc60000000p-6f), hn::Set(d, 0x1.fdf7160000000p-7f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_82, hn::Set(d, 0x1.611a7c0000000p-4f)),
                        node_11, node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.4cefb80000000p+3f)),
                        hn::Set(d, 0x1.2503e20000000p-5f), hn::Set(d, 0x1.fdf7160000000p-7f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_84, hn::Set(d, 0x1.3333340000000p-1f)),
                        hn::Set(d, 0x1.ed79160000000p-6f), hn::Set(d, 0x1.fdf7160000000p-7f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_64, hn::Set(d, 0x1.155a3c0000000p-3f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.bf8d900000000p+1f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Ge(feature_53, hn::Set(d, 0x1.0000000000000p-2f)),
                        node_2, node_1);
                    score = hn::Add(score, node_0);
                }
                /* Tree 40: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_15, hn::Set(d, 0x1.bbbbbc0000000p-2f)),
                        hn::Set(d, -0x1.c31a940000000p-9f), hn::Set(d, 0x1.2b32340000000p-7f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_31, hn::Set(d, -0x1.3333340000000p-1f)),
                        hn::Set(d, -0x1.939f080000000p-8f), hn::Set(d, -0x1.c262f20000000p-6f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_162, hn::Set(d, 0x1.f49f4a0000000p-3f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_95, hn::Set(d, 0x1.5db5e00000000p+3f)),
                        hn::Set(d, -0x1.97316e0000000p-6f), hn::Set(d, 0x1.aec8aa0000000p-6f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_110, hn::Set(d, 0x1.6d757c0000000p+3f)),
                        hn::Set(d, 0x1.5dbafa0000000p-7f), hn::Set(d, 0x1.05822e0000000p-5f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.8618620000000p-5f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_80, hn::Set(d, 0x1.6ece540000000p-4f)),
                        node_3, node_4);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.193ea80000000p+1f)),
                        hn::Set(d, -0x1.2686980000000p-5f), hn::Set(d, 0x1.7d42b20000000p-6f));
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_83, hn::Set(d, 0x1.b6db6e0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_22 = LoadFeature(d, features + row * 164 + 22, 164);
                const auto feature_87 = LoadFeature(d, features + row * 164 + 87, 164);
                const auto feature_97 = LoadFeature(d, features + row * 164 + 97, 164);
                /* Tree 41: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_87, hn::Set(d, 0x1.bc7bc80000000p-2f)),
                        hn::Set(d, -0x1.8976ea0000000p-7f), hn::Set(d, 0x1.0d172e0000000p-7f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_97, hn::Set(d, 0x1.4000000000000p+1f)),
                        hn::Set(d, -0x1.1977d40000000p-5f), hn::Set(d, 0x1.7179780000000p-12f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_102, hn::Set(d, 0x1.b599e00000000p+3f)),
                        node_7, node_8);
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_106, hn::Set(d, 0x1.05a4c20000000p+0f)),
                        hn::Set(d, 0x1.0d172e0000000p-7f), hn::Set(d, 0x1.1306880000000p-5f));
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_156, hn::Set(d, 0x1.62e4300000000p-1f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Ge(feature_2, hn::Set(d, 0x1.fda8520000000p-1f)),
                        hn::Set(d, 0x1.65fa6c0000000p-6f), hn::Set(d, 0x1.0040000000000p-8f));
                    const auto node_12 = hn::IfThenElse(hn::Ge(feature_2, hn::Set(d, 0x1.f4e0b40000000p-1f)),
                        hn::Set(d, -0x1.4db08c0000000p-6f), hn::Set(d, -0x1.56c4a40000000p-9f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.5a31760000000p+3f)),
                        node_11, node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_22, hn::Set(d, 0x1.2f6d2e0000000p-7f)),
                        hn::Set(d, -0x1.be7ba00000000p-7f), hn::Set(d, 0x1.19b4440000000p-6f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_5, hn::Set(d, 0x1.5555560000000p-1f)),
                        hn::Set(d, -0x1.e0e46e0000000p-6f), hn::Set(d, -0x1.cb65240000000p-7f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_162, hn::Set(d, 0x1.8000000000000p-4f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_70, hn::Set(d, 0x1.aaaaaa0000000p-2f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.9a3c660000000p-1f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 42: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_15, hn::Set(d, 0x1.5555560000000p-2f)),
                        hn::Set(d, -0x1.82020a0000000p-8f), hn::Set(d, 0x1.87f9480000000p-8f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_60, hn::Set(d, 0x1.0000000000000p-1f)),
                        hn::Set(d, 0x1.59bf2a0000000p-7f), hn::Set(d, -0x1.3071020000000p-5f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_67, hn::Set(d, 0x1.0000000000000p+0f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_95, hn::Set(d, 0x1.5db5e00000000p+3f)),
                        hn::Set(d, -0x1.8d78b20000000p-6f), hn::Set(d, 0x1.a3831e0000000p-6f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_110, hn::Set(d, 0x1.6d757c0000000p+3f)),
                        hn::Set(d, 0x1.47edf00000000p-7f), hn::Set(d, 0x1.f9ff700000000p-6f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.8618620000000p-5f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_80, hn::Set(d, 0x1.6ece540000000p-4f)),
                        node_3, node_4);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.193ea80000000p+1f)),
                        hn::Set(d, -0x1.23a1de0000000p-5f), hn::Set(d, 0x1.7710660000000p-6f));
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_83, hn::Set(d, 0x1.b6db6e0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 43: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_87, hn::Set(d, 0x1.bc7bc80000000p-2f)),
                        hn::Set(d, -0x1.8993840000000p-7f), hn::Set(d, 0x1.20a28a0000000p-7f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_85, hn::Set(d, 0x1.6666660000000p-2f)),
                        hn::Set(d, -0x1.19f2c20000000p-5f), hn::Set(d, 0x1.3ca1720000000p-7f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_100, hn::Set(d, 0x1.89bd640000000p-1f)),
                        node_7, node_8);
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_103, hn::Set(d, 0x1.ee924a0000000p+1f)),
                        hn::Set(d, 0x1.6d27460000000p-7f), hn::Set(d, 0x1.183f8a0000000p-5f));
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_156, hn::Set(d, 0x1.62e4300000000p-1f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_139, hn::Set(d, 0x1.1c71c80000000p-1f)),
                        hn::Set(d, -0x1.8666200000000p-7f), hn::Set(d, 0x1.c2cd380000000p-6f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.5a31760000000p+3f)),
                        hn::Set(d, 0x1.267d9e0000000p-7f), hn::Set(d, -0x1.51544e0000000p-7f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_9, hn::Set(d, 0x1.b5a86e0000000p+2f)),
                        node_11, node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_108, hn::Set(d, 0x1.78c0880000000p+0f)),
                        hn::Set(d, -0x1.8191620000000p-6f), hn::Set(d, -0x1.baf3ca0000000p-9f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_9, hn::Set(d, 0x1.1881320000000p+3f)),
                        hn::Set(d, -0x1.788ab00000000p-7f), hn::Set(d, 0x1.f21b720000000p-6f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_64, hn::Set(d, 0x1.5555560000000p-2f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_70, hn::Set(d, 0x1.aaaaaa0000000p-2f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.944ed00000000p-1f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 44: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_6, hn::Set(d, 0x1.8000000000000p-1f)),
                        hn::Set(d, -0x1.c077740000000p-7f), hn::Set(d, -0x1.c6c9760000000p-12f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_147, hn::Set(d, 0x1.99999a0000000p-3f)),
                        hn::Set(d, 0x1.5023580000000p-7f), hn::Set(d, -0x1.55eaec0000000p-5f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_110, hn::Set(d, 0x1.4078be0000000p+3f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.62e4700000000p+3f)),
                        hn::Set(d, 0x1.2583800000000p-6f), hn::Set(d, -0x1.4f5d9a0000000p-7f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_60, hn::Set(d, 0x1.0000000000000p-1f)),
                        node_9, hn::Set(d, -0x1.2e98480000000p-5f));
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_67, hn::Set(d, 0x1.e666660000000p-1f)),
                        node_3, node_4);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.193ea80000000p+1f)),
                        hn::Set(d, -0x1.20e1260000000p-5f), hn::Set(d, 0x1.700dec0000000p-6f));
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_83, hn::Set(d, 0x1.b6db6e0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 45: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_21, hn::Set(d, 0x1.27fc6a0000000p-12f)),
                        hn::Set(d, -0x1.67a5f00000000p-6f), hn::Set(d, -0x1.bae7e20000000p-9f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_139, hn::Set(d, 0x1.b6db6e0000000p-2f)),
                        hn::Set(d, -0x1.0b864c0000000p-5f), hn::Set(d, 0x1.9207f60000000p-6f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_100, hn::Set(d, 0x1.0c9f540000000p+2f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_42, hn::Set(d, 0x1.aa85ae0000000p+1f)),
                        hn::Set(d, 0x1.02430a0000000p-11f), hn::Set(d, -0x1.5df3060000000p-6f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_11, hn::Set(d, 0x1.b65e2e0000000p-9f)),
                        hn::Set(d, -0x1.25bf580000000p-5f), hn::Set(d, 0x1.b3e7de0000000p-7f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.b726480000000p+2f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Ge(feature_2, hn::Set(d, 0x1.944ed00000000p-1f)),
                        node_4, node_3);
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.d316740000000p-2f)),
                        hn::Set(d, -0x1.0c77ce0000000p-5f), hn::Set(d, 0x1.083de40000000p-6f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.4cefb80000000p+3f)),
                        hn::Set(d, 0x1.2345c20000000p-5f), hn::Set(d, 0x1.083de40000000p-6f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_154, hn::Set(d, 0x1.3333340000000p-1f)),
                        hn::Set(d, 0x1.083de40000000p-6f), node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.bf8d900000000p+1f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Ge(feature_53, hn::Set(d, 0x1.0000000000000p+0f)),
                        node_2, node_1);
                    score = hn::Add(score, node_0);
                }
                const auto feature_104 = LoadFeature(d, features + row * 164 + 104, 164);
                const auto feature_149 = LoadFeature(d, features + row * 164 + 149, 164);
                /* Tree 46: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_18, hn::Set(d, 0x1.3a3caa0000000p-1f)),
                        hn::Set(d, 0x1.c6e3040000000p-9f), hn::Set(d, -0x1.577f9c0000000p-7f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_63, hn::Set(d, 0x1.6aaaaa0000000p-2f)),
                        node_7, hn::Set(d, -0x1.256e880000000p-5f));
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_140, hn::Set(d, 0x1.26bb1c0000000p+1f)),
                        hn::Set(d, -0x1.20ad8e0000000p-7f), hn::Set(d, -0x1.3712d00000000p-5f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_102, hn::Set(d, 0x1.d7a0f40000000p+3f)),
                        hn::Set(d, -0x1.20ad8e0000000p-7f), hn::Set(d, 0x1.e648320000000p-6f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.bf8d900000000p+1f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_154, hn::Set(d, 0x1.6db6dc0000000p-1f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_104, hn::Set(d, 0x1.99999a0000000p-2f)),
                        hn::Set(d, -0x1.e0da9c0000000p-7f), hn::Set(d, 0x1.09ca400000000p-5f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_95, hn::Set(d, 0x1.501bba0000000p+3f)),
                        hn::Set(d, 0x1.83bc000000000p-8f), hn::Set(d, 0x1.f1786a0000000p-6f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_13, hn::Set(d, 0x1.6914740000000p-8f)),
                        node_11, node_12);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_149, hn::Set(d, 0x1.6db6dc0000000p-1f)),
                        hn::Set(d, -0x1.6443040000000p-5f), node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_142, hn::Set(d, 0x1.99999a0000000p-3f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 47: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_97, hn::Set(d, 0x1.11acee0000000p-3f)),
                        hn::Set(d, -0x1.07b5360000000p-10f), hn::Set(d, -0x1.a201d20000000p-7f));
                    const auto node_8 = hn::IfThenElse(hn::Ge(feature_2, hn::Set(d, 0x1.3fd9300000000p-1f)),
                        hn::Set(d, 0x1.7fcd3e0000000p-6f), hn::Set(d, -0x1.1caad00000000p-7f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_74, hn::Set(d, 0x1.cab0c00000000p+0f)),
                        node_7, node_8);
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_50, hn::Set(d, 0x1.2595400000000p+2f)),
                        hn::Set(d, 0x1.e16c280000000p-6f), hn::Set(d, 0x1.319f680000000p-9f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_43, hn::Set(d, 0x1.2bb5120000000p-3f)),
                        hn::Set(d, -0x1.2333340000000p-5f), node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_154, hn::Set(d, 0x1.3333340000000p-1f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.193ea80000000p+1f)),
                        hn::Set(d, -0x1.2872300000000p-8f), hn::Set(d, 0x1.86d5600000000p-6f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_140, hn::Set(d, 0x1.b35a700000000p+1f)),
                        hn::Set(d, 0x1.a07ef60000000p-6f), hn::Set(d, 0x1.dc33d40000000p-8f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_15, hn::Set(d, 0x1.6666660000000p-2f)),
                        node_11, node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.259c580000000p+3f)),
                        hn::Set(d, 0x1.499d9c0000000p-6f), hn::Set(d, -0x1.763f3c0000000p-8f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_60, hn::Set(d, 0x1.0000000000000p-1f)),
                        node_13, hn::Set(d, -0x1.2ac0580000000p-5f));
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_67, hn::Set(d, 0x1.e666660000000p-1f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_110, hn::Set(d, 0x1.d376100000000p+2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_135 = LoadFeature(d, features + row * 164 + 135, 164);
                /* Tree 48: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_18, hn::Set(d, 0x1.3a3caa0000000p-1f)),
                        hn::Set(d, 0x1.991fea0000000p-9f), hn::Set(d, -0x1.48d3580000000p-7f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_63, hn::Set(d, 0x1.6aaaaa0000000p-2f)),
                        node_7, hn::Set(d, -0x1.1ee14c0000000p-5f));
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_140, hn::Set(d, 0x1.26bb1c0000000p+1f)),
                        hn::Set(d, -0x1.168d080000000p-7f), hn::Set(d, -0x1.3289f40000000p-5f));
                    const auto node_10 = hn::IfThenElse(hn::Ge(feature_53, hn::Set(d, 0x1.99999a0000000p-3f)),
                        hn::Set(d, 0x1.e67c6a0000000p-6f), hn::Set(d, -0x1.168d080000000p-7f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.bf8d900000000p+1f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_154, hn::Set(d, 0x1.6db6dc0000000p-1f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_95, hn::Set(d, 0x1.4a01140000000p+3f)),
                        hn::Set(d, 0x1.c9016a0000000p-10f), hn::Set(d, 0x1.d8600e0000000p-6f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_135, hn::Set(d, 0x1.24924a0000000p-2f)),
                        hn::Set(d, -0x1.1b1afc0000000p-5f), hn::Set(d, 0x1.d39a920000000p-6f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_9, hn::Set(d, 0x1.f3fe020000000p+2f)),
                        node_11, node_12);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_149, hn::Set(d, 0x1.6db6dc0000000p-1f)),
                        hn::Set(d, -0x1.5a75fa0000000p-5f), node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_142, hn::Set(d, 0x1.99999a0000000p-3f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 49: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_18, hn::Set(d, 0x1.3a3caa0000000p-1f)),
                        hn::Set(d, 0x1.82be720000000p-9f), hn::Set(d, -0x1.42a9720000000p-7f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_63, hn::Set(d, 0x1.6aaaaa0000000p-2f)),
                        node_7, hn::Set(d, -0x1.1d2df80000000p-5f));
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_140, hn::Set(d, 0x1.26bb1c0000000p+1f)),
                        hn::Set(d, -0x1.11a0580000000p-7f), hn::Set(d, -0x1.2f72e40000000p-5f));
                    const auto node_10 = hn::IfThenElse(hn::Ge(feature_53, hn::Set(d, 0x1.99999a0000000p-3f)),
                        hn::Set(d, 0x1.e05fea0000000p-6f), hn::Set(d, -0x1.11a0580000000p-7f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.bf8d900000000p+1f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_154, hn::Set(d, 0x1.6db6dc0000000p-1f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_95, hn::Set(d, 0x1.6cae8a0000000p+3f)),
                        hn::Set(d, 0x1.c2de480000000p-8f), hn::Set(d, 0x1.ffecda0000000p-6f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_95, hn::Set(d, 0x1.0d83bc0000000p+2f)),
                        hn::Set(d, -0x1.7d9f6a0000000p-11f), hn::Set(d, 0x1.24517a0000000p-5f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_61, hn::Set(d, 0x1.9deec60000000p+2f)),
                        node_11, node_12);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_149, hn::Set(d, 0x1.6db6dc0000000p-1f)),
                        hn::Set(d, -0x1.53c7120000000p-5f), node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_142, hn::Set(d, 0x1.69696a0000000p-3f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 50: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_21, hn::Set(d, 0x1.c6c93a0000000p-13f)),
                        hn::Set(d, -0x1.50a6b60000000p-6f), hn::Set(d, -0x1.98494c0000000p-8f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_43, hn::Set(d, 0x1.a5a5a60000000p-3f)),
                        hn::Set(d, -0x1.1a708c0000000p-5f), hn::Set(d, 0x1.f27bc40000000p-7f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_154, hn::Set(d, 0x1.3333340000000p-1f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.2662aa0000000p-1f)),
                        hn::Set(d, -0x1.ad73fc0000000p-6f), hn::Set(d, 0x1.8a342e0000000p-6f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_70, hn::Set(d, 0x1.5555560000000p-3f)),
                        hn::Set(d, 0x1.f00f100000000p-9f), hn::Set(d, -0x1.7700de0000000p-6f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_13, hn::Set(d, 0x1.12358e0000000p-7f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_66, hn::Set(d, 0x1.99999a0000000p-3f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.193ea80000000p+1f)),
                        hn::Set(d, -0x1.1905ea0000000p-8f), hn::Set(d, 0x1.6d5ac20000000p-6f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.5a31760000000p+3f)),
                        hn::Set(d, 0x1.7055560000000p-7f), hn::Set(d, -0x1.4a32aa0000000p-6f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_15, hn::Set(d, 0x1.6666660000000p-2f)),
                        node_11, node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.259c580000000p+3f)),
                        hn::Set(d, 0x1.15aae80000000p-6f), hn::Set(d, -0x1.8a1dfa0000000p-8f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_60, hn::Set(d, 0x1.0000000000000p-1f)),
                        node_13, hn::Set(d, -0x1.2517120000000p-5f));
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_67, hn::Set(d, 0x1.e666660000000p-1f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_110, hn::Set(d, 0x1.d376100000000p+2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 51: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_100, hn::Set(d, 0x1.89bd640000000p-1f)),
                        hn::Set(d, -0x1.0508380000000p-7f), hn::Set(d, -0x1.1734b20000000p-5f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_77, hn::Set(d, 0x1.99999a0000000p-5f)),
                        hn::Set(d, -0x1.e5d44e0000000p-8f), hn::Set(d, 0x1.f073240000000p-6f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_85, hn::Set(d, 0x1.47ae140000000p-3f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_139, hn::Set(d, 0x1.1c71c80000000p-1f)),
                        hn::Set(d, -0x1.6ae7340000000p-7f), hn::Set(d, 0x1.a976680000000p-6f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.ab68a00000000p-5f)),
                        hn::Set(d, -0x1.5c211a0000000p-9f), hn::Set(d, 0x1.4d48020000000p-7f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_9, hn::Set(d, 0x1.b5a86e0000000p+2f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.8fd1440000000p-1f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_44, hn::Set(d, 0x1.56ebc20000000p-4f)),
                        hn::Set(d, -0x1.03e13a0000000p-5f), hn::Set(d, 0x1.acdc620000000p-9f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.ef80620000000p-1f)),
                        hn::Set(d, 0x1.618dae0000000p-6f), hn::Set(d, -0x1.7189380000000p-7f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_3, hn::Set(d, 0x1.24924a0000000p-3f)),
                        node_11, node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_13, hn::Set(d, 0x1.9852f00000000p-9f)),
                        hn::Set(d, 0x1.3ad09c0000000p-7f), hn::Set(d, -0x1.b74bb60000000p-6f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_41, hn::Set(d, 0x1.db56540000000p+1f)),
                        hn::Set(d, -0x1.0206ce0000000p-6f), hn::Set(d, 0x1.0f06400000000p-6f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_142, hn::Set(d, 0x1.5555560000000p-3f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_65, hn::Set(d, 0x1.edfd6e0000000p-8f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_70, hn::Set(d, 0x1.aaaaaa0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 52: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_6, hn::Set(d, 0x1.8000000000000p-1f)),
                        hn::Set(d, -0x1.ae236a0000000p-7f), hn::Set(d, -0x1.5500da0000000p-12f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_141, hn::Set(d, 0x1.3e116c0000000p+1f)),
                        hn::Set(d, 0x1.72701a0000000p-7f), hn::Set(d, -0x1.bfcfb80000000p-8f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_110, hn::Set(d, 0x1.4078be0000000p+3f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.f405fe0000000p-1f)),
                        hn::Set(d, -0x1.6af8780000000p-9f), hn::Set(d, 0x1.5b6f280000000p-6f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_60, hn::Set(d, 0x1.0000000000000p-1f)),
                        node_9, hn::Set(d, -0x1.217b1c0000000p-5f));
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_67, hn::Set(d, 0x1.e666660000000p-1f)),
                        node_3, node_4);
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_0, hn::Set(d, 0x1.54c9d20000000p+1f)),
                        hn::Set(d, -0x1.52bc480000000p-9f), hn::Set(d, 0x1.62dcb20000000p-6f));
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.193ea80000000p+1f)),
                        hn::Set(d, -0x1.1814b80000000p-5f), node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_83, hn::Set(d, 0x1.b6db6e0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_76 = LoadFeature(d, features + row * 164 + 76, 164);
                /* Tree 53: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_87, hn::Set(d, 0x1.bc7bc80000000p-2f)),
                        hn::Set(d, -0x1.8c74780000000p-7f), hn::Set(d, 0x1.81cd1e0000000p-8f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_139, hn::Set(d, 0x1.b6db6e0000000p-2f)),
                        hn::Set(d, -0x1.ff0aa60000000p-6f), hn::Set(d, 0x1.7a87c80000000p-6f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_100, hn::Set(d, 0x1.0c9f540000000p+2f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_42, hn::Set(d, 0x1.aa85ae0000000p+1f)),
                        hn::Set(d, 0x1.4d5c9a0000000p-12f), hn::Set(d, -0x1.483e800000000p-6f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_11, hn::Set(d, 0x1.b65e2e0000000p-9f)),
                        hn::Set(d, -0x1.1260360000000p-5f), hn::Set(d, 0x1.8b5da80000000p-7f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.b726480000000p+2f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Ge(feature_2, hn::Set(d, 0x1.8fd1440000000p-1f)),
                        node_4, node_3);
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_76, hn::Set(d, 0x1.0000000000000p+0f)),
                        hn::Set(d, 0x1.e479360000000p-10f), hn::Set(d, 0x1.b076c40000000p-6f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_77, hn::Set(d, 0x1.1111120000000p-4f)),
                        hn::Set(d, -0x1.9334720000000p-6f), node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_103, hn::Set(d, 0x1.6e66460000000p+1f)),
                        hn::Set(d, 0x1.0efa8c0000000p-7f), hn::Set(d, 0x1.1b183e0000000p-5f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_4, hn::Set(d, 0x1.0000000000000p+0f)),
                        hn::Set(d, 0x1.7f616a0000000p-6f), hn::Set(d, -0x1.03de1e0000000p-6f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_64, hn::Set(d, 0x1.579fca0000000p-3f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_93, hn::Set(d, 0x1.5cc4700000000p+1f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Ge(feature_53, hn::Set(d, 0x1.0000000000000p+0f)),
                        node_2, node_1);
                    score = hn::Add(score, node_0);
                }
                const auto feature_45 = LoadFeature(d, features + row * 164 + 45, 164);
                /* Tree 54: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_15, hn::Set(d, 0x1.5555560000000p-2f)),
                        hn::Set(d, -0x1.1ebf740000000p-9f), hn::Set(d, 0x1.03594c0000000p-7f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_60, hn::Set(d, 0x1.0000000000000p-1f)),
                        hn::Set(d, 0x1.28355c0000000p-7f), hn::Set(d, -0x1.1de84a0000000p-5f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_67, hn::Set(d, 0x1.e666660000000p-1f)),
                        node_7, node_8);
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_0, hn::Set(d, 0x1.54c9d20000000p+1f)),
                        hn::Set(d, -0x1.d4b9640000000p-10f), hn::Set(d, 0x1.5ff0a40000000p-6f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.193ea80000000p+1f)),
                        hn::Set(d, -0x1.14b1e40000000p-5f), node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_83, hn::Set(d, 0x1.b6db6e0000000p-2f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_45, hn::Set(d, 0x1.27350c0000000p-7f)),
                        hn::Set(d, -0x1.c256660000000p-6f), hn::Set(d, 0x1.1016a20000000p-6f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_11, hn::Set(d, 0x1.b04ba60000000p-7f)),
                        hn::Set(d, 0x1.7ce6ba0000000p-6f), hn::Set(d, -0x1.8cdddc0000000p-8f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_3, hn::Set(d, 0x1.24924a0000000p-3f)),
                        node_11, node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_13, hn::Set(d, 0x1.9852f00000000p-9f)),
                        hn::Set(d, 0x1.3ebd860000000p-7f), hn::Set(d, -0x1.aca12a0000000p-6f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_41, hn::Set(d, 0x1.db56540000000p+1f)),
                        hn::Set(d, -0x1.f6a5f60000000p-7f), hn::Set(d, 0x1.1446300000000p-6f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_142, hn::Set(d, 0x1.5555560000000p-3f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_65, hn::Set(d, 0x1.edfd6e0000000p-8f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_70, hn::Set(d, 0x1.aaaaaa0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 55: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_85, hn::Set(d, 0x1.bbbbbc0000000p-3f)),
                        hn::Set(d, -0x1.bafff60000000p-6f), hn::Set(d, 0x1.76de9c0000000p-6f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_3, hn::Set(d, 0x1.8f9c180000000p-6f)),
                        hn::Set(d, 0x1.c6c5e20000000p-7f), hn::Set(d, -0x1.8f102e0000000p-7f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_21, hn::Set(d, 0x1.6830800000000p-12f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_42, hn::Set(d, 0x1.aa85ae0000000p+1f)),
                        hn::Set(d, -0x1.162c2e0000000p-12f), hn::Set(d, -0x1.3203280000000p-6f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_11, hn::Set(d, 0x1.7790820000000p-9f)),
                        hn::Set(d, -0x1.22e53c0000000p-5f), hn::Set(d, 0x1.6a05be0000000p-7f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.b8259e0000000p+2f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Ge(feature_2, hn::Set(d, 0x1.781b2a0000000p-1f)),
                        node_4, node_3);
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_100, hn::Set(d, 0x1.4515920000000p+2f)),
                        hn::Set(d, -0x1.ab07220000000p-6f), hn::Set(d, 0x1.0d51600000000p-6f));
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_80, hn::Set(d, 0x1.dc47720000000p-4f)),
                        hn::Set(d, -0x1.d0231c0000000p-7f), hn::Set(d, 0x1.c33a720000000p-7f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_64, hn::Set(d, 0x1.579fca0000000p-3f)),
                        hn::Set(d, 0x1.1c1e1e0000000p-5f), hn::Set(d, 0x1.3e99480000000p-7f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_103, hn::Set(d, 0x1.6e66460000000p+1f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_77, hn::Set(d, 0x1.8618620000000p-5f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Ge(feature_53, hn::Set(d, 0x1.0000000000000p+0f)),
                        node_2, node_1);
                    score = hn::Add(score, node_0);
                }
                const auto feature_49 = LoadFeature(d, features + row * 164 + 49, 164);
                const auto feature_111 = LoadFeature(d, features + row * 164 + 111, 164);
                /* Tree 56: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_55, hn::Set(d, 0x1.0a2b240000000p+1f)),
                        hn::Set(d, -0x1.e0664e0000000p-7f), hn::Set(d, 0x1.221dec0000000p-10f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.f948b80000000p+2f)),
                        hn::Set(d, 0x1.f6d31c0000000p-8f), hn::Set(d, -0x1.cd06d60000000p-7f));
                    const auto node_3 = hn::IfThenElse(hn::Ge(feature_3, hn::Set(d, 0x1.0000000000000p-2f)),
                        node_8, node_7);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_111, hn::Set(d, 0x1.62e4300000000p+0f)),
                        hn::Set(d, -0x1.33436e0000000p-6f), hn::Set(d, 0x1.77a6880000000p-7f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_12, hn::Set(d, 0x1.10a7500000000p-4f)),
                        hn::Set(d, 0x1.fc56960000000p-8f), hn::Set(d, -0x1.5f2a380000000p-7f));
                    const auto node_4 = hn::IfThenElse(hn::Ge(feature_24, hn::Set(d, 0x1.04958a0000000p-9f)),
                        node_10, node_9);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.876ac60000000p+2f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_3, hn::Set(d, 0x1.5555560000000p-2f)),
                        hn::Set(d, 0x1.fbb8420000000p-7f), hn::Set(d, -0x1.3dd6120000000p-7f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_88, hn::Set(d, 0x1.0cef9c0000000p-5f)),
                        hn::Set(d, 0x1.f70f3c0000000p-7f), hn::Set(d, 0x1.1fd24c0000000p-5f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.b91b920000000p-4f)),
                        node_11, node_12);
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_49, hn::Set(d, 0x1.1e79e80000000p-1f)),
                        hn::Set(d, -0x1.0eee660000000p-5f), hn::Set(d, 0x1.36a72a0000000p-9f));
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_141, hn::Set(d, 0x1.0a2b240000000p+1f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_139, hn::Set(d, 0x1.b6db6e0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_14 = LoadFeature(d, features + row * 164 + 14, 164);
                /* Tree 57: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_19, hn::Set(d, 0x1.8c0f060000000p-4f)),
                        hn::Set(d, -0x1.6426240000000p-6f), hn::Set(d, 0x1.071f360000000p-6f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_124, hn::Set(d, 0x1.0a2b240000000p+1f)),
                        hn::Set(d, -0x1.466bf60000000p-8f), hn::Set(d, -0x1.be32000000000p-6f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_34, hn::Set(d, -0x1.6db6dc0000000p-1f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_70, hn::Set(d, 0x1.aaaaaa0000000p-2f)),
                        hn::Set(d, -0x1.14e4b20000000p-11f), hn::Set(d, -0x1.17cd440000000p-6f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_13, hn::Set(d, 0x1.b545640000000p-11f)),
                        hn::Set(d, -0x1.1ed9e20000000p-5f), hn::Set(d, 0x1.8580860000000p-7f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.c6e0100000000p+2f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.42a8480000000p-1f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_97, hn::Set(d, 0x1.5930ba0000000p-2f)),
                        hn::Set(d, -0x1.2036d80000000p-7f), hn::Set(d, -0x1.3a38120000000p-5f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_95, hn::Set(d, 0x1.83f2c60000000p+2f)),
                        hn::Set(d, -0x1.3ad2b80000000p-7f), hn::Set(d, 0x1.c2c2d60000000p-6f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_14, hn::Set(d, 0x1.99999a0000000p-3f)),
                        node_11, node_12);
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_63, hn::Set(d, 0x1.2f684c0000000p-3f)),
                        hn::Set(d, 0x1.184d440000000p-5f), hn::Set(d, 0x1.ce4e680000000p-12f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_102, hn::Set(d, 0x1.cd68a60000000p+2f)),
                        hn::Set(d, -0x1.3b4bbe0000000p-7f), node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_55, hn::Set(d, 0x1.62e4300000000p+0f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Ge(feature_52, hn::Set(d, 0x1.bc75960000000p-1f)),
                        node_2, node_1);
                    score = hn::Add(score, node_0);
                }
                /* Tree 58: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_21, hn::Set(d, 0x1.c9ab660000000p-7f)),
                        hn::Set(d, -0x1.878bda0000000p-7f), hn::Set(d, 0x1.796dda0000000p-10f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_43, hn::Set(d, 0x1.a5a5a60000000p-3f)),
                        hn::Set(d, -0x1.152c3e0000000p-5f), hn::Set(d, 0x1.d54d6a0000000p-7f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_154, hn::Set(d, 0x1.3333340000000p-1f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.2662aa0000000p-1f)),
                        hn::Set(d, -0x1.8bbe880000000p-6f), hn::Set(d, 0x1.6bda560000000p-6f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_70, hn::Set(d, 0x1.5555560000000p-3f)),
                        hn::Set(d, 0x1.fc8bfc0000000p-9f), hn::Set(d, -0x1.624bc20000000p-6f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_13, hn::Set(d, 0x1.12358e0000000p-7f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_66, hn::Set(d, 0x1.99999a0000000p-3f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Ge(feature_24, hn::Set(d, 0x1.837a880000000p-3f)),
                        hn::Set(d, 0x1.4992120000000p-6f), hn::Set(d, -0x1.c9b92e0000000p-8f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_5, hn::Set(d, 0x1.5555560000000p-3f)),
                        hn::Set(d, 0x1.662fa20000000p-9f), hn::Set(d, 0x1.f432460000000p-7f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.6d0ac60000000p+2f)),
                        node_11, node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.259c580000000p+3f)),
                        hn::Set(d, 0x1.226fc20000000p-6f), hn::Set(d, -0x1.f132f20000000p-8f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_60, hn::Set(d, 0x1.0000000000000p-1f)),
                        node_13, hn::Set(d, -0x1.1e7e720000000p-5f));
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_67, hn::Set(d, 0x1.e666660000000p-1f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_110, hn::Set(d, 0x1.d376100000000p+2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 59: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_70, hn::Set(d, 0x1.aaaaaa0000000p-2f)),
                        hn::Set(d, -0x1.0c1f420000000p-10f), hn::Set(d, -0x1.16e83e0000000p-6f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_141, hn::Set(d, 0x1.3e116c0000000p+1f)),
                        hn::Set(d, 0x1.5911580000000p-7f), hn::Set(d, -0x1.ea2e760000000p-8f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_110, hn::Set(d, 0x1.4078be0000000p+3f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.37dbfe0000000p+3f)),
                        hn::Set(d, 0x1.1f07e20000000p-6f), hn::Set(d, -0x1.5ab2120000000p-7f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_60, hn::Set(d, 0x1.0000000000000p-1f)),
                        node_9, hn::Set(d, -0x1.1adcbc0000000p-5f));
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_67, hn::Set(d, 0x1.e666660000000p-1f)),
                        node_3, node_4);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.193ea80000000p+1f)),
                        hn::Set(d, -0x1.1424f60000000p-5f), hn::Set(d, 0x1.2b538e0000000p-6f));
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_83, hn::Set(d, 0x1.b6db6e0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_136 = LoadFeature(d, features + row * 164 + 136, 164);
                /* Tree 60: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_19, hn::Set(d, 0x1.8c0f060000000p-4f)),
                        hn::Set(d, -0x1.6159b40000000p-6f), hn::Set(d, 0x1.f5c2180000000p-7f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_136, hn::Set(d, 0x1.6db6dc0000000p-2f)),
                        hn::Set(d, -0x1.bf3b520000000p-6f), hn::Set(d, 0x1.6ecb5e0000000p-8f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_34, hn::Set(d, -0x1.6db6dc0000000p-1f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.dd6dde0000000p-1f)),
                        hn::Set(d, -0x1.a224de0000000p-8f), hn::Set(d, 0x1.97b7e60000000p-9f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.6a1f720000000p+3f)),
                        hn::Set(d, 0x1.8d4b8a0000000p-7f), hn::Set(d, -0x1.8799780000000p-6f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.c6e0100000000p+2f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Ge(feature_2, hn::Set(d, 0x1.42a8480000000p-1f)),
                        node_4, node_3);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_140, hn::Set(d, 0x1.d4ef960000000p+1f)),
                        hn::Set(d, 0x1.9283060000000p-6f), hn::Set(d, -0x1.a3cf1c0000000p-10f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_103, hn::Set(d, 0x1.6e66460000000p+1f)),
                        hn::Set(d, -0x1.eb947a0000000p-10f), hn::Set(d, -0x1.2b7ae00000000p-5f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_78, hn::Set(d, 0x1.728eb60000000p+2f)),
                        node_11, node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_102, hn::Set(d, 0x1.c5cebc0000000p+2f)),
                        hn::Set(d, 0x1.774ba60000000p-6f), hn::Set(d, -0x1.fa1e280000000p-6f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_154, hn::Set(d, 0x1.3333340000000p-1f)),
                        hn::Set(d, 0x1.cc04820000000p-7f), hn::Set(d, 0x1.1a8aa00000000p-5f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_52, hn::Set(d, 0x1.f603f60000000p-3f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.ab68a00000000p-5f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Ge(feature_53, hn::Set(d, 0x1.0000000000000p-2f)),
                        node_2, node_1);
                    score = hn::Add(score, node_0);
                }
                const auto feature_79 = LoadFeature(d, features + row * 164 + 79, 164);
                const auto feature_126 = LoadFeature(d, features + row * 164 + 126, 164);
                /* Tree 61: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_145, hn::Set(d, 0x1.b6db6e0000000p-2f)),
                        hn::Set(d, -0x1.ba4a5e0000000p-6f), hn::Set(d, 0x1.23eb5a0000000p-7f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_79, hn::Set(d, 0x1.f2272a0000000p+0f)),
                        hn::Set(d, -0x1.b640c80000000p-7f), hn::Set(d, 0x1.553a840000000p-7f));
                    const auto node_3 = hn::IfThenElse(hn::Ge(feature_21, hn::Set(d, 0x1.c6c93a0000000p-13f)),
                        node_8, node_7);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_42, hn::Set(d, 0x1.aa85ae0000000p+1f)),
                        hn::Set(d, -0x1.37a5460000000p-10f), hn::Set(d, -0x1.7dcae20000000p-6f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.5a31760000000p+3f)),
                        hn::Set(d, 0x1.26ac6e0000000p-7f), hn::Set(d, -0x1.1a1a1c0000000p-6f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_15, hn::Set(d, 0x1.bbbbbc0000000p-2f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Ge(feature_2, hn::Set(d, 0x1.781b2a0000000p-1f)),
                        node_4, node_3);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_126, hn::Set(d, 0x1.b6db6e0000000p-3f)),
                        hn::Set(d, 0x1.a601c80000000p-6f), hn::Set(d, 0x1.df73d60000000p-9f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_103, hn::Set(d, 0x1.6e66460000000p+1f)),
                        hn::Set(d, -0x1.05e9f20000000p-9f), hn::Set(d, -0x1.17d04c0000000p-5f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_78, hn::Set(d, 0x1.728eb60000000p+2f)),
                        node_11, node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_102, hn::Set(d, 0x1.c5cebc0000000p+2f)),
                        hn::Set(d, 0x1.8e8f020000000p-6f), hn::Set(d, -0x1.ee3b9a0000000p-6f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_154, hn::Set(d, 0x1.3333340000000p-1f)),
                        hn::Set(d, 0x1.af9d6c0000000p-7f), hn::Set(d, 0x1.166d820000000p-5f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_52, hn::Set(d, 0x1.f603f60000000p-3f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.ab68a00000000p-5f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Ge(feature_53, hn::Set(d, 0x1.0000000000000p-2f)),
                        node_2, node_1);
                    score = hn::Add(score, node_0);
                }
                const auto feature_8 = LoadFeature(d, features + row * 164 + 8, 164);
                const auto feature_16 = LoadFeature(d, features + row * 164 + 16, 164);
                /* Tree 62: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_102, hn::Set(d, 0x1.adf84a0000000p+3f)),
                        hn::Set(d, -0x1.1468440000000p-7f), hn::Set(d, -0x1.92371e0000000p-6f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.faacfa0000000p+2f)),
                        hn::Set(d, 0x1.0692160000000p-8f), hn::Set(d, -0x1.cd1d820000000p-7f));
                    const auto node_3 = hn::IfThenElse(hn::Ge(feature_2, hn::Set(d, 0x1.db820c0000000p-1f)),
                        node_8, node_7);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_154, hn::Set(d, 0x1.3333340000000p-1f)),
                        hn::Set(d, 0x1.1179880000000p-11f), hn::Set(d, -0x1.1d3abc0000000p-5f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_67, hn::Set(d, 0x1.e666660000000p-1f)),
                        hn::Set(d, 0x1.b1e7300000000p-7f), hn::Set(d, -0x1.d46a780000000p-6f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_110, hn::Set(d, 0x1.447d380000000p+3f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.851da00000000p+2f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_16, hn::Set(d, 0x1.99999a0000000p-2f)),
                        hn::Set(d, -0x1.4417a00000000p-7f), hn::Set(d, 0x1.1ca57a0000000p-5f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_142, hn::Set(d, 0x1.1111120000000p-2f)),
                        hn::Set(d, -0x1.cd15360000000p-6f), hn::Set(d, 0x1.3df3d80000000p-7f));
                    const auto node_5 = hn::IfThenElse(hn::Ge(feature_0, hn::Set(d, 0x1.4956f00000000p+1f)),
                        node_12, node_11);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_8, hn::Set(d, 0x1.0000000000000p-1f)),
                        hn::Set(d, 0x1.edb73a0000000p-7f), hn::Set(d, -0x1.09dbde0000000p-7f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_16, hn::Set(d, 0x1.cccccc0000000p-1f)),
                        hn::Set(d, 0x1.23ee5a0000000p-5f), hn::Set(d, 0x1.aa97400000000p-7f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.5555560000000p-4f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_80, hn::Set(d, 0x1.47ae140000000p-4f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_139, hn::Set(d, 0x1.d89d8a0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_144 = LoadFeature(d, features + row * 164 + 144, 164);
                /* Tree 63: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_144, hn::Set(d, 0x1.9be3660000000p-4f)),
                        hn::Set(d, -0x1.d55c2a0000000p-7f), hn::Set(d, 0x1.69f3080000000p-15f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.1312740000000p-1f)),
                        hn::Set(d, -0x1.84a98e0000000p-6f), hn::Set(d, 0x1.39f9480000000p-6f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.3d02520000000p+3f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_22, hn::Set(d, 0x1.332df60000000p-4f)),
                        hn::Set(d, -0x1.2a0d440000000p-7f), hn::Set(d, 0x1.dc81c20000000p-6f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_64, hn::Set(d, 0x1.c7946e0000000p-4f)),
                        hn::Set(d, -0x1.dda5200000000p-11f), hn::Set(d, 0x1.74b2fc0000000p-7f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.5b32620000000p+2f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Ge(feature_2, hn::Set(d, 0x1.9a3c660000000p-1f)),
                        node_4, node_3);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_44, hn::Set(d, 0x1.5f15f20000000p-4f)),
                        hn::Set(d, 0x1.6247440000000p-6f), hn::Set(d, -0x1.eadaee0000000p-8f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_18, hn::Set(d, 0x1.c71c720000000p-1f)),
                        hn::Set(d, 0x1.0b99a20000000p-5f), hn::Set(d, 0x1.52d8860000000p-9f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.b91b920000000p-4f)),
                        node_11, node_12);
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_49, hn::Set(d, 0x1.1e79e80000000p-1f)),
                        hn::Set(d, -0x1.f47fb80000000p-6f), hn::Set(d, 0x1.7085ee0000000p-9f));
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_141, hn::Set(d, 0x1.0a2b240000000p+1f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_139, hn::Set(d, 0x1.b6db6e0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 64: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_13, hn::Set(d, 0x1.58ed240000000p-7f)),
                        hn::Set(d, -0x1.50e4720000000p-10f), hn::Set(d, -0x1.e75a2c0000000p-7f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.5a31760000000p+3f)),
                        hn::Set(d, 0x1.af4f4a0000000p-8f), hn::Set(d, -0x1.96fb300000000p-7f));
                    const auto node_3 = hn::IfThenElse(hn::Ge(feature_2, hn::Set(d, 0x1.db820c0000000p-1f)),
                        node_8, node_7);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_11, hn::Set(d, 0x1.eb851e0000000p-6f)),
                        hn::Set(d, 0x1.18134e0000000p-5f), hn::Set(d, -0x1.616b120000000p-7f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_142, hn::Set(d, 0x1.0000000000000p-2f)),
                        hn::Set(d, 0x1.e8bb6a0000000p-10f), hn::Set(d, 0x1.8e8f5c0000000p-6f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_18, hn::Set(d, 0x1.773b9e0000000p-2f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_87, hn::Set(d, 0x1.c341160000000p-2f)),
                        node_3, node_4);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.193ea80000000p+1f)),
                        hn::Set(d, -0x1.1424560000000p-5f), hn::Set(d, 0x1.4583e40000000p-6f));
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_83, hn::Set(d, 0x1.99999a0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 65: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.b8259e0000000p+2f)),
                        hn::Set(d, -0x1.6013d60000000p-8f), hn::Set(d, 0x1.2418700000000p-8f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_141, hn::Set(d, 0x1.3e116c0000000p+1f)),
                        hn::Set(d, 0x1.51039a0000000p-7f), hn::Set(d, -0x1.dde6880000000p-8f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_110, hn::Set(d, 0x1.429f840000000p+3f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.37dbfe0000000p+3f)),
                        hn::Set(d, 0x1.16ce7c0000000p-6f), hn::Set(d, -0x1.fd5e3c0000000p-8f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_60, hn::Set(d, 0x1.0000000000000p-1f)),
                        node_9, hn::Set(d, -0x1.17d7f00000000p-5f));
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_67, hn::Set(d, 0x1.e666660000000p-1f)),
                        node_3, node_4);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.193ea80000000p+1f)),
                        hn::Set(d, -0x1.131e060000000p-5f), hn::Set(d, 0x1.4319180000000p-6f));
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_83, hn::Set(d, 0x1.99999a0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_47 = LoadFeature(d, features + row * 164 + 47, 164);
                /* Tree 66: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.7b8e4e0000000p-1f)),
                        hn::Set(d, -0x1.54dce40000000p-6f), hn::Set(d, -0x1.ab67960000000p-8f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.0855f60000000p+3f)),
                        hn::Set(d, 0x1.ac321e0000000p-7f), hn::Set(d, -0x1.f062320000000p-7f));
                    const auto node_3 = hn::IfThenElse(hn::Ge(feature_24, hn::Set(d, 0x1.525cde0000000p-4f)),
                        node_8, node_7);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_6, hn::Set(d, 0x1.8000000000000p-1f)),
                        hn::Set(d, -0x1.2aa0740000000p-6f), hn::Set(d, 0x1.0ecdf80000000p-9f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_67, hn::Set(d, 0x1.e666660000000p-1f)),
                        hn::Set(d, 0x1.9ed5200000000p-7f), hn::Set(d, -0x1.c9334a0000000p-6f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_110, hn::Set(d, 0x1.447d380000000p+3f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.876ac60000000p+2f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_3, hn::Set(d, 0x1.5555560000000p-2f)),
                        hn::Set(d, 0x1.a425b80000000p-7f), hn::Set(d, -0x1.a921da0000000p-7f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_47, hn::Set(d, 0x1.c28f5c0000000p-3f)),
                        hn::Set(d, 0x1.0685a60000000p-5f), hn::Set(d, 0x1.188cee0000000p-8f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.b91b920000000p-4f)),
                        node_11, node_12);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_141, hn::Set(d, 0x1.0a2b240000000p+1f)),
                        node_5, hn::Set(d, -0x1.b2cc700000000p-7f));
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_139, hn::Set(d, 0x1.d89d8a0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 67: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_63, hn::Set(d, 0x1.6aaaaa0000000p-2f)),
                        hn::Set(d, 0x1.6583e80000000p-12f), hn::Set(d, -0x1.02741c0000000p-5f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_97, hn::Set(d, 0x1.4000000000000p+1f)),
                        hn::Set(d, 0x1.77865c0000000p-6f), hn::Set(d, -0x1.9382ce0000000p-10f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_145, hn::Set(d, 0x1.b6db6e0000000p-3f)),
                        node_7, node_8);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_140, hn::Set(d, 0x1.303ad20000000p+2f)),
                        node_3, hn::Set(d, -0x1.5623aa0000000p-5f));
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.193ea80000000p+1f)),
                        hn::Set(d, -0x1.115efa0000000p-5f), hn::Set(d, 0x1.2f774e0000000p-6f));
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_83, hn::Set(d, 0x1.99999a0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_112 = LoadFeature(d, features + row * 164 + 112, 164);
                /* Tree 68: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_19, hn::Set(d, 0x1.8c0f060000000p-4f)),
                        hn::Set(d, -0x1.490df40000000p-6f), hn::Set(d, 0x1.2b8c1a0000000p-6f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_139, hn::Set(d, 0x1.d89d8a0000000p-2f)),
                        hn::Set(d, -0x1.a7b3280000000p-6f), hn::Set(d, 0x1.09c3940000000p-8f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_34, hn::Set(d, -0x1.6db6dc0000000p-1f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.dd6dde0000000p-1f)),
                        hn::Set(d, -0x1.9e01bc0000000p-8f), hn::Set(d, 0x1.8359b80000000p-9f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.1111120000000p-4f)),
                        hn::Set(d, 0x1.7eedcc0000000p-11f), hn::Set(d, 0x1.0ff4320000000p-6f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.c6e0100000000p+2f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Ge(feature_2, hn::Set(d, 0x1.42a8480000000p-1f)),
                        node_4, node_3);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.0f8e420000000p+3f)),
                        hn::Set(d, 0x1.88606e0000000p-6f), hn::Set(d, -0x1.3ea9000000000p-13f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_112, hn::Set(d, 0x1.26bb1c0000000p+1f)),
                        hn::Set(d, -0x1.36f1a40000000p-8f), hn::Set(d, -0x1.150cd40000000p-5f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_78, hn::Set(d, 0x1.728eb60000000p+2f)),
                        node_11, node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_110, hn::Set(d, 0x1.f1c51c0000000p+1f)),
                        hn::Set(d, 0x1.87dd280000000p-6f), hn::Set(d, -0x1.ba9b660000000p-6f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_63, hn::Set(d, 0x1.579fca0000000p-3f)),
                        hn::Set(d, 0x1.e915c60000000p-6f), hn::Set(d, -0x1.73f87e0000000p-7f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_52, hn::Set(d, 0x1.f603f60000000p-3f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.ab68a00000000p-5f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Ge(feature_53, hn::Set(d, 0x1.0000000000000p-2f)),
                        node_2, node_1);
                    score = hn::Add(score, node_0);
                }
                /* Tree 69: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_13, hn::Set(d, 0x1.58ed240000000p-7f)),
                        hn::Set(d, -0x1.dfa0480000000p-10f), hn::Set(d, -0x1.c820060000000p-7f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_13, hn::Set(d, 0x1.45828c0000000p-6f)),
                        hn::Set(d, 0x1.d1b0fc0000000p-8f), hn::Set(d, -0x1.1887900000000p-7f));
                    const auto node_3 = hn::IfThenElse(hn::Ge(feature_2, hn::Set(d, 0x1.db820c0000000p-1f)),
                        node_8, node_7);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_11, hn::Set(d, 0x1.eb851e0000000p-6f)),
                        hn::Set(d, 0x1.1213580000000p-5f), hn::Set(d, -0x1.3b37a60000000p-7f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_20, hn::Set(d, 0x1.c790f80000000p-4f)),
                        hn::Set(d, -0x1.12b1760000000p-8f), hn::Set(d, 0x1.7fb25c0000000p-7f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_18, hn::Set(d, 0x1.773b9e0000000p-2f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_87, hn::Set(d, 0x1.c341160000000p-2f)),
                        node_3, node_4);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.193ea80000000p+1f)),
                        hn::Set(d, -0x1.0f960a0000000p-5f), hn::Set(d, 0x1.3b1cc40000000p-6f));
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_83, hn::Set(d, 0x1.99999a0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_101 = LoadFeature(d, features + row * 164 + 101, 164);
                /* Tree 70: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_103, hn::Set(d, 0x1.be4a420000000p+2f)),
                        hn::Set(d, -0x1.2a83de0000000p-8f), hn::Set(d, 0x1.2adce20000000p-8f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_101, hn::Set(d, 0x1.dd3c260000000p+0f)),
                        hn::Set(d, -0x1.42acf60000000p-6f), hn::Set(d, 0x1.78a1480000000p-9f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_101, hn::Set(d, 0x1.0000000000000p-1f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_95, hn::Set(d, 0x1.501bba0000000p+3f)),
                        hn::Set(d, -0x1.3557bc0000000p-8f), hn::Set(d, 0x1.f17a420000000p-6f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_124, hn::Set(d, 0x1.4850420000000p+1f)),
                        hn::Set(d, 0x1.830fb40000000p-8f), hn::Set(d, 0x1.e2ff8e0000000p-6f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_9, hn::Set(d, 0x1.db11f60000000p+2f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_145, hn::Set(d, 0x1.b6db6e0000000p-3f)),
                        node_3, node_4);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.e1e1e20000000p-5f)),
                        hn::Set(d, -0x1.1475d60000000p-7f), hn::Set(d, -0x1.53d4600000000p-5f));
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_140, hn::Set(d, 0x1.2cd4ac0000000p+2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_157 = LoadFeature(d, features + row * 164 + 157, 164);
                /* Tree 71: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_18, hn::Set(d, 0x1.3a3caa0000000p-1f)),
                        hn::Set(d, 0x1.5987340000000p-9f), hn::Set(d, -0x1.2197f40000000p-7f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_63, hn::Set(d, 0x1.6aaaaa0000000p-2f)),
                        node_7, hn::Set(d, -0x1.0c37a40000000p-5f));
                    const auto node_10 = hn::IfThenElse(hn::Ge(feature_0, hn::Set(d, 0x1.5dca400000000p+1f)),
                        hn::Set(d, 0x1.02d7780000000p-5f), hn::Set(d, -0x1.9fa11e0000000p-7f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_157, hn::Set(d, 0x1.0074380000000p-2f)),
                        hn::Set(d, -0x1.28b9540000000p-5f), node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_154, hn::Set(d, 0x1.6db6dc0000000p-1f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.70c5740000000p+2f)),
                        hn::Set(d, -0x1.488a860000000p-11f), hn::Set(d, 0x1.3a41e00000000p-6f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_3, hn::Set(d, 0x1.c71c720000000p-4f)),
                        hn::Set(d, 0x1.4236280000000p-8f), hn::Set(d, 0x1.1a4b980000000p-5f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_95, hn::Set(d, 0x1.6cae8a0000000p+3f)),
                        node_11, node_12);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_149, hn::Set(d, 0x1.6db6dc0000000p-1f)),
                        hn::Set(d, -0x1.3e559c0000000p-5f), node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_142, hn::Set(d, 0x1.99999a0000000p-3f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_105 = LoadFeature(d, features + row * 164 + 105, 164);
                const auto feature_109 = LoadFeature(d, features + row * 164 + 109, 164);
                /* Tree 72: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Ge(feature_24, hn::Set(d, 0x1.1a636e0000000p-4f)),
                        hn::Set(d, 0x1.4cffb20000000p-8f), hn::Set(d, -0x1.81b66c0000000p-8f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_110, hn::Set(d, 0x1.0110740000000p+4f)),
                        hn::Set(d, -0x1.20822a0000000p-5f), hn::Set(d, -0x1.d1ea740000000p-8f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_154, hn::Set(d, 0x1.5555560000000p-3f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_139, hn::Set(d, 0x1.1c71c80000000p-1f)),
                        hn::Set(d, 0x1.a669b20000000p-8f), hn::Set(d, 0x1.adb8800000000p-6f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_52, hn::Set(d, 0x1.87da1c0000000p-1f)),
                        hn::Set(d, 0x1.a669b20000000p-8f), hn::Set(d, 0x1.0b96ae0000000p-5f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_20, hn::Set(d, 0x1.0386dc0000000p-4f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.193ea80000000p+1f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_109, hn::Set(d, 0x1.0000000000000p+0f)),
                        hn::Set(d, -0x1.87f08a0000000p-6f), hn::Set(d, 0x1.4757a00000000p-6f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_140, hn::Set(d, 0x1.b35a700000000p+1f)),
                        hn::Set(d, 0x1.8c0e620000000p-6f), hn::Set(d, 0x1.7a00840000000p-8f));
                    const auto node_5 = hn::IfThenElse(hn::Ge(feature_2, hn::Set(d, 0x1.781b2a0000000p-1f)),
                        node_12, node_11);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_9, hn::Set(d, 0x1.4d289e0000000p+3f)),
                        hn::Set(d, -0x1.2679780000000p-8f), hn::Set(d, 0x1.c224b80000000p-6f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.fc2e020000000p-1f)),
                        hn::Set(d, -0x1.88f0a80000000p-7f), hn::Set(d, -0x1.bba5120000000p-6f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_105, hn::Set(d, 0x1.0398240000000p-3f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.5a31760000000p+3f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_15, hn::Set(d, 0x1.bbbbbc0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 73: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_18, hn::Set(d, 0x1.3a3caa0000000p-1f)),
                        hn::Set(d, 0x1.3b4d740000000p-9f), hn::Set(d, -0x1.118d400000000p-7f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_63, hn::Set(d, 0x1.6aaaaa0000000p-2f)),
                        node_7, hn::Set(d, -0x1.06740a0000000p-5f));
                    const auto node_10 = hn::IfThenElse(hn::Ge(feature_0, hn::Set(d, 0x1.5dca400000000p+1f)),
                        hn::Set(d, 0x1.fa51460000000p-6f), hn::Set(d, -0x1.a7d2980000000p-7f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_157, hn::Set(d, 0x1.0074380000000p-2f)),
                        hn::Set(d, -0x1.25a5140000000p-5f), node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_154, hn::Set(d, 0x1.6db6dc0000000p-1f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.b600000000000p+2f)),
                        hn::Set(d, 0x1.750dee0000000p-8f), hn::Set(d, 0x1.a8200e0000000p-6f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_3, hn::Set(d, 0x1.c71c720000000p-4f)),
                        hn::Set(d, 0x1.3326fa0000000p-8f), hn::Set(d, 0x1.20ca2a0000000p-5f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_95, hn::Set(d, 0x1.6cae8a0000000p+3f)),
                        node_11, node_12);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_149, hn::Set(d, 0x1.9249240000000p-1f)),
                        hn::Set(d, -0x1.30dc7c0000000p-5f), node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_142, hn::Set(d, 0x1.99999a0000000p-3f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 74: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_31, hn::Set(d, -0x1.3333340000000p-1f)),
                        hn::Set(d, -0x1.990ee60000000p-11f), hn::Set(d, -0x1.7bec480000000p-7f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_110, hn::Set(d, 0x1.0110740000000p+4f)),
                        hn::Set(d, -0x1.1a7f660000000p-5f), hn::Set(d, -0x1.a6f3440000000p-8f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_154, hn::Set(d, 0x1.5555560000000p-3f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_139, hn::Set(d, 0x1.1c71c80000000p-1f)),
                        hn::Set(d, 0x1.6f2a1c0000000p-8f), hn::Set(d, 0x1.a908120000000p-6f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_52, hn::Set(d, 0x1.87da1c0000000p-1f)),
                        hn::Set(d, 0x1.6f2a1c0000000p-8f), hn::Set(d, 0x1.01e2a60000000p-5f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_20, hn::Set(d, 0x1.0386dc0000000p-4f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.193ea80000000p+1f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_67, hn::Set(d, 0x1.e666660000000p-1f)),
                        hn::Set(d, 0x1.876fb40000000p-8f), hn::Set(d, -0x1.bf94f20000000p-6f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_111, hn::Set(d, 0x1.a5ddfc0000000p+1f)),
                        hn::Set(d, 0x1.a058ea0000000p-6f), hn::Set(d, -0x1.e5c1860000000p-6f));
                    const auto node_5 = hn::IfThenElse(hn::Ge(feature_2, hn::Set(d, 0x1.fda8520000000p-1f)),
                        node_12, node_11);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_12, hn::Set(d, 0x1.9ae24e0000000p-5f)),
                        hn::Set(d, 0x1.de48200000000p-12f), hn::Set(d, -0x1.076f420000000p-6f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_43, hn::Set(d, 0x1.8618620000000p-3f)),
                        hn::Set(d, -0x1.e1393e0000000p-6f), hn::Set(d, -0x1.743e660000000p-8f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.fc2e020000000p-1f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.62e4700000000p+3f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_15, hn::Set(d, 0x1.bbbbbc0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 75: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_9, hn::Set(d, 0x1.addcb00000000p+2f)),
                        hn::Set(d, -0x1.8c246a0000000p-7f), hn::Set(d, 0x1.a08dc20000000p-10f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_63, hn::Set(d, 0x1.6aaaaa0000000p-2f)),
                        node_7, hn::Set(d, -0x1.04f0b60000000p-5f));
                    const auto node_10 = hn::IfThenElse(hn::Ge(feature_0, hn::Set(d, 0x1.5dca400000000p+1f)),
                        hn::Set(d, 0x1.f145e40000000p-6f), hn::Set(d, -0x1.a9c5b60000000p-7f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_157, hn::Set(d, 0x1.0074380000000p-2f)),
                        hn::Set(d, -0x1.2489160000000p-5f), node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_154, hn::Set(d, 0x1.6db6dc0000000p-1f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_9, hn::Set(d, 0x1.ff17c00000000p+2f)),
                        hn::Set(d, 0x1.b1e3c20000000p-9f), hn::Set(d, 0x1.5ce85e0000000p-6f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_3, hn::Set(d, 0x1.c71c720000000p-4f)),
                        hn::Set(d, 0x1.2044440000000p-8f), hn::Set(d, 0x1.1dcebc0000000p-5f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_95, hn::Set(d, 0x1.6cae8a0000000p+3f)),
                        node_11, node_12);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_149, hn::Set(d, 0x1.6db6dc0000000p-1f)),
                        hn::Set(d, -0x1.307b920000000p-5f), node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_142, hn::Set(d, 0x1.99999a0000000p-3f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 76: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_102, hn::Set(d, 0x1.adf84a0000000p+3f)),
                        hn::Set(d, -0x1.e1f3fa0000000p-8f), hn::Set(d, -0x1.760b7a0000000p-6f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.0855f60000000p+3f)),
                        hn::Set(d, 0x1.97be2c0000000p-9f), hn::Set(d, -0x1.e3d9b60000000p-7f));
                    const auto node_3 = hn::IfThenElse(hn::Ge(feature_2, hn::Set(d, 0x1.dd6dde0000000p-1f)),
                        node_8, node_7);
                    const auto node_9 = hn::IfThenElse(hn::Ge(feature_21, hn::Set(d, 0x1.6830800000000p-12f)),
                        hn::Set(d, 0x1.6b4a9a0000000p-9f), hn::Set(d, -0x1.c6a1a00000000p-7f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_162, hn::Set(d, 0x1.2d2d2e0000000p-2f)),
                        hn::Set(d, 0x1.a945660000000p-7f), hn::Set(d, -0x1.0c05b00000000p-6f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_110, hn::Set(d, 0x1.447d380000000p+3f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.876ac60000000p+2f)),
                        node_3, node_4);
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_15, hn::Set(d, 0x1.59999a0000000p-1f)),
                        hn::Set(d, 0x1.ab4f4e0000000p-8f), hn::Set(d, 0x1.04d5dc0000000p-5f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_112, hn::Set(d, 0x1.0a2b240000000p+1f)),
                        hn::Set(d, -0x1.be75520000000p-6f), node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_102, hn::Set(d, 0x1.8efa420000000p+2f)),
                        hn::Set(d, 0x1.c1e2c80000000p-6f), hn::Set(d, -0x1.0ea4640000000p-6f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_18, hn::Set(d, 0x1.7777780000000p-1f)),
                        hn::Set(d, 0x1.3396480000000p-5f), hn::Set(d, 0x1.c7c13a0000000p-7f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_102, hn::Set(d, 0x1.4f8c7a0000000p+3f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.d316740000000p-2f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_139, hn::Set(d, 0x1.d89d8a0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 77: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_9, hn::Set(d, 0x1.addcb00000000p+2f)),
                        hn::Set(d, -0x1.88a3460000000p-7f), hn::Set(d, 0x1.9c60100000000p-10f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_63, hn::Set(d, 0x1.6aaaaa0000000p-2f)),
                        node_7, hn::Set(d, -0x1.02e2ac0000000p-5f));
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_140, hn::Set(d, 0x1.3e116c0000000p+1f)),
                        hn::Set(d, 0x1.227aec0000000p-7f), hn::Set(d, -0x1.2546920000000p-5f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_126, hn::Set(d, 0x1.8000000000000p-2f)),
                        hn::Set(d, -0x1.134c560000000p-6f), hn::Set(d, 0x1.03d9c40000000p-5f));
                    const auto node_4 = hn::IfThenElse(hn::Ge(feature_53, hn::Set(d, 0x1.99999a0000000p-3f)),
                        node_10, node_9);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_154, hn::Set(d, 0x1.6db6dc0000000p-1f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_13, hn::Set(d, 0x1.6914740000000p-8f)),
                        hn::Set(d, 0x1.7d16920000000p-6f), hn::Set(d, 0x1.32d0620000000p-8f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_0, hn::Set(d, 0x1.6146280000000p+1f)),
                        hn::Set(d, 0x1.3d2dd60000000p-9f), hn::Set(d, 0x1.1117040000000p-5f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_95, hn::Set(d, 0x1.6cae8a0000000p+3f)),
                        node_11, node_12);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_149, hn::Set(d, 0x1.6db6dc0000000p-1f)),
                        hn::Set(d, -0x1.2b15780000000p-5f), node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_142, hn::Set(d, 0x1.99999a0000000p-3f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 78: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_67, hn::Set(d, 0x1.99999a0000000p-6f)),
                        hn::Set(d, -0x1.8a2c5c0000000p-8f), hn::Set(d, -0x1.2874140000000p-6f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_13, hn::Set(d, 0x1.e7dc6e0000000p-8f)),
                        hn::Set(d, 0x1.705a980000000p-6f), hn::Set(d, -0x1.2e0cd40000000p-9f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_55, hn::Set(d, 0x1.0a2b240000000p+1f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_20, hn::Set(d, 0x1.5dd6300000000p-4f)),
                        hn::Set(d, -0x1.9e9ac20000000p-6f), hn::Set(d, 0x1.50273c0000000p-8f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_53, hn::Set(d, 0x1.99999a0000000p-3f)),
                        hn::Set(d, 0x1.edf5220000000p-7f), hn::Set(d, 0x1.ebd2200000000p-6f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.9157e00000000p+1f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_24, hn::Set(d, 0x1.1a636e0000000p-4f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_97, hn::Set(d, 0x1.1ce26a0000000p-3f)),
                        hn::Set(d, 0x1.5462240000000p-6f), hn::Set(d, -0x1.db888e0000000p-8f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_67, hn::Set(d, 0x1.aaaaaa0000000p-1f)),
                        hn::Set(d, 0x1.d90dd00000000p-6f), hn::Set(d, -0x1.1f56040000000p-6f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_110, hn::Set(d, 0x1.0db2820000000p+3f)),
                        node_11, node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_127, hn::Set(d, 0x1.3333340000000p-2f)),
                        hn::Set(d, 0x1.027f280000000p-7f), hn::Set(d, -0x1.a22aac0000000p-8f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_5, hn::Set(d, 0x1.24924a0000000p-1f)),
                        hn::Set(d, -0x1.493b0c0000000p-5f), hn::Set(d, -0x1.0dafc20000000p-8f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_141, hn::Set(d, 0x1.78e3600000000p+1f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_140, hn::Set(d, 0x1.b35a700000000p+1f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_15, hn::Set(d, 0x1.bbbbbc0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 79: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.e1e1e20000000p-5f)),
                        hn::Set(d, -0x1.3278d80000000p-8f), hn::Set(d, 0x1.5073b20000000p-8f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_157, hn::Set(d, 0x1.ecbaac0000000p-4f)),
                        hn::Set(d, -0x1.6bc8ce0000000p-7f), hn::Set(d, 0x1.ac7dea0000000p-7f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_13, hn::Set(d, 0x1.45828c0000000p-6f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_8, hn::Set(d, 0x1.bacf920000000p-6f)),
                        hn::Set(d, -0x1.4b21ee0000000p-9f), hn::Set(d, -0x1.038ade0000000p-5f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.5a31760000000p+3f)),
                        hn::Set(d, 0x1.a787660000000p-6f), hn::Set(d, -0x1.98c01a0000000p-8f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_45, hn::Set(d, 0x1.b7d6c40000000p-7f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_47, hn::Set(d, 0x1.24924a0000000p-3f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_12, hn::Set(d, 0x1.f3ac2c0000000p-6f)),
                        hn::Set(d, 0x1.8580000000000p-7f), hn::Set(d, -0x1.0f4a980000000p-5f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_21, hn::Set(d, 0x1.249b660000000p-10f)),
                        hn::Set(d, -0x1.652db80000000p-6f), hn::Set(d, 0x1.e74f2c0000000p-7f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_104, hn::Set(d, 0x1.8000000000000p-1f)),
                        node_11, node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_13, hn::Set(d, 0x1.9852f00000000p-9f)),
                        hn::Set(d, 0x1.4ed91c0000000p-7f), hn::Set(d, -0x1.8221d40000000p-6f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_65, hn::Set(d, 0x1.4141420000000p-5f)),
                        hn::Set(d, 0x1.b2c2180000000p-6f), hn::Set(d, -0x1.7d73e00000000p-8f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_142, hn::Set(d, 0x1.435e500000000p-3f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_65, hn::Set(d, 0x1.edfd6e0000000p-8f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_70, hn::Set(d, 0x1.aaaaaa0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 80: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_127, hn::Set(d, 0x1.642c860000000p-4f)),
                        hn::Set(d, -0x1.0581820000000p-5f), hn::Set(d, -0x1.df65e00000000p-9f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_64, hn::Set(d, 0x1.dc47720000000p-4f)),
                        hn::Set(d, -0x1.87ba280000000p-7f), hn::Set(d, -0x1.19d8b60000000p-5f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_47, hn::Set(d, 0x1.47ae140000000p-5f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_9, hn::Set(d, 0x1.b5a86e0000000p+2f)),
                        hn::Set(d, -0x1.0fe2280000000p-8f), hn::Set(d, 0x1.6bc7440000000p-7f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_15, hn::Set(d, 0x1.ddddde0000000p-3f)),
                        hn::Set(d, 0x1.445de40000000p-10f), hn::Set(d, -0x1.26f11c0000000p-6f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.0f35e60000000p+3f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.dd6dde0000000p-1f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_112, hn::Set(d, 0x1.8ba7480000000p+1f)),
                        hn::Set(d, -0x1.2c076c0000000p-5f), hn::Set(d, -0x1.52a6f60000000p-7f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_65, hn::Set(d, 0x1.bdd2b80000000p-10f)),
                        node_11, hn::Set(d, 0x1.3f74220000000p-8f));
                    const auto node_13 = hn::IfThenElse(hn::Ge(feature_2, hn::Set(d, 0x1.9923500000000p-1f)),
                        hn::Set(d, 0x1.1747a80000000p-7f), hn::Set(d, -0x1.de2f6e0000000p-8f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_102, hn::Set(d, 0x1.c55d600000000p+3f)),
                        hn::Set(d, 0x1.907ec80000000p-6f), hn::Set(d, -0x1.29f35e0000000p-7f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_87, hn::Set(d, 0x1.d2a2060000000p-2f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_104, hn::Set(d, 0x1.3333340000000p-1f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.b8259e0000000p+2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 81: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.9d3bb60000000p+2f)),
                        hn::Set(d, -0x1.b8a7c60000000p-9f), hn::Set(d, 0x1.27c4700000000p-8f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_31, hn::Set(d, -0x1.b6db6e0000000p-1f)),
                        hn::Set(d, -0x1.ba81720000000p-7f), hn::Set(d, -0x1.0e43c80000000p-5f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_63, hn::Set(d, 0x1.6aaaaa0000000p-2f)),
                        node_7, node_8);
                    const auto node_10 = hn::IfThenElse(hn::Ge(feature_0, hn::Set(d, 0x1.5dca400000000p+1f)),
                        hn::Set(d, 0x1.e3525c0000000p-6f), hn::Set(d, -0x1.ac378e0000000p-7f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_157, hn::Set(d, 0x1.0074380000000p-2f)),
                        hn::Set(d, -0x1.1b14620000000p-5f), node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_154, hn::Set(d, 0x1.6db6dc0000000p-1f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Ge(feature_24, hn::Set(d, 0x1.430b200000000p-7f)),
                        hn::Set(d, 0x1.934bd60000000p-11f), hn::Set(d, 0x1.2279400000000p-6f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_44, hn::Set(d, 0x1.5151520000000p-2f)),
                        hn::Set(d, 0x1.0193160000000p-5f), hn::Set(d, -0x1.ab17a00000000p-8f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_95, hn::Set(d, 0x1.4a01140000000p+3f)),
                        node_11, node_12);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_140, hn::Set(d, 0x1.1a07b00000000p+2f)),
                        node_5, hn::Set(d, -0x1.27b2680000000p-5f));
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_145, hn::Set(d, 0x1.99999a0000000p-3f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 82: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_11, hn::Set(d, 0x1.b46bf80000000p-8f)),
                        hn::Set(d, -0x1.6ef7960000000p-8f), hn::Set(d, -0x1.626fac0000000p-6f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_13, hn::Set(d, 0x1.45828c0000000p-6f)),
                        hn::Set(d, 0x1.4e8a480000000p-9f), hn::Set(d, -0x1.23af420000000p-7f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.781b2a0000000p-1f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_45, hn::Set(d, 0x1.3333340000000p-4f)),
                        hn::Set(d, 0x1.e17d9c0000000p-6f), hn::Set(d, -0x1.51c7d20000000p-6f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_139, hn::Set(d, 0x1.4000000000000p-1f)),
                        hn::Set(d, 0x1.dc9f8a0000000p-10f), hn::Set(d, 0x1.d4faa60000000p-6f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_18, hn::Set(d, 0x1.773b9e0000000p-2f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_78, hn::Set(d, 0x1.d4ef960000000p+1f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_12, hn::Set(d, 0x1.84bed40000000p-5f)),
                        hn::Set(d, 0x1.c084920000000p-9f), hn::Set(d, -0x1.6d89520000000p-7f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_105, hn::Set(d, 0x1.53148e0000000p-2f)),
                        hn::Set(d, 0x1.c329520000000p-6f), hn::Set(d, -0x1.6d89520000000p-7f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_22, hn::Set(d, 0x1.2f6d2e0000000p-7f)),
                        node_11, node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_0, hn::Set(d, 0x1.4f46680000000p+1f)),
                        hn::Set(d, -0x1.bc4f780000000p-6f), hn::Set(d, -0x1.6d89520000000p-7f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_108, hn::Set(d, 0x1.83091e0000000p-2f)),
                        hn::Set(d, -0x1.1241460000000p-5f), hn::Set(d, -0x1.6d89520000000p-7f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_64, hn::Set(d, 0x1.af286c0000000p-5f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_162, hn::Set(d, 0x1.8000000000000p-4f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_70, hn::Set(d, 0x1.aaaaaa0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 83: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.e7916e0000000p+2f)),
                        hn::Set(d, -0x1.5177160000000p-9f), hn::Set(d, 0x1.bdc6a00000000p-7f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_64, hn::Set(d, 0x1.09f95a0000000p-3f)),
                        hn::Set(d, -0x1.8aedf80000000p-6f), hn::Set(d, 0x1.c9efd00000000p-9f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_124, hn::Set(d, 0x1.0822f80000000p+2f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_9, hn::Set(d, 0x1.e500560000000p+2f)),
                        hn::Set(d, 0x1.91177e0000000p-11f), hn::Set(d, 0x1.03a73e0000000p-6f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_64, hn::Set(d, 0x1.af286c0000000p-4f)),
                        hn::Set(d, -0x1.3924000000000p-6f), hn::Set(d, 0x1.1f431c0000000p-7f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_141, hn::Set(d, 0x1.3e116c0000000p+1f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_110, hn::Set(d, 0x1.429f840000000p+3f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_21, hn::Set(d, 0x1.249b660000000p-10f)),
                        hn::Set(d, -0x1.d4315a0000000p-8f), hn::Set(d, 0x1.bb8c740000000p-6f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.c9fecc0000000p+2f)),
                        hn::Set(d, -0x1.d95a1e0000000p-7f), hn::Set(d, 0x1.ce210a0000000p-10f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.37dbfe0000000p+3f)),
                        node_11, node_12);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_60, hn::Set(d, 0x1.0000000000000p-1f)),
                        node_5, hn::Set(d, -0x1.0b9b6a0000000p-5f));
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_67, hn::Set(d, 0x1.e666660000000p-1f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 84: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Ge(feature_21, hn::Set(d, 0x1.ee26d20000000p-7f)),
                        hn::Set(d, 0x1.3518ee0000000p-9f), hn::Set(d, -0x1.60aed40000000p-7f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_65, hn::Set(d, 0x1.0000000000000p-5f)),
                        hn::Set(d, -0x1.2ae2a60000000p-5f), hn::Set(d, 0x1.20feae0000000p-7f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_42, hn::Set(d, 0x1.1b92800000000p+2f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_135, hn::Set(d, 0x1.24924a0000000p-2f)),
                        hn::Set(d, 0x1.8ad4e20000000p-6f), hn::Set(d, -0x1.2868000000000p-7f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_70, hn::Set(d, 0x1.5555560000000p-3f)),
                        hn::Set(d, 0x1.0aa16c0000000p-7f), hn::Set(d, -0x1.33bc2e0000000p-6f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_13, hn::Set(d, 0x1.12358e0000000p-7f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_66, hn::Set(d, 0x1.99999a0000000p-3f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_102, hn::Set(d, 0x1.d55a660000000p+4f)),
                        hn::Set(d, -0x1.8ad48e0000000p-12f), hn::Set(d, 0x1.4293b00000000p-6f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_64, hn::Set(d, 0x1.c7946e0000000p-4f)),
                        hn::Set(d, 0x1.b238300000000p-8f), hn::Set(d, 0x1.7cfe940000000p-6f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.c57f680000000p+2f)),
                        node_11, node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_65, hn::Set(d, 0x1.1cf06a0000000p-7f)),
                        hn::Set(d, -0x1.0c402e0000000p-9f), hn::Set(d, 0x1.d0886a0000000p-7f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_60, hn::Set(d, 0x1.0000000000000p-1f)),
                        node_13, hn::Set(d, -0x1.0bea560000000p-5f));
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_67, hn::Set(d, 0x1.e666660000000p-1f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_110, hn::Set(d, 0x1.ca96220000000p+2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_128 = LoadFeature(d, features + row * 164 + 128, 164);
                /* Tree 85: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_47, hn::Set(d, 0x1.47ae140000000p-5f)),
                        hn::Set(d, -0x1.cb98000000000p-8f), hn::Set(d, -0x1.5cf5620000000p-6f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_87, hn::Set(d, 0x1.bc7bc80000000p-2f)),
                        hn::Set(d, -0x1.3064a60000000p-9f), hn::Set(d, 0x1.144d060000000p-6f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.b8259e0000000p+2f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_0, hn::Set(d, 0x1.5664f60000000p+1f)),
                        hn::Set(d, -0x1.e82e7a0000000p-7f), hn::Set(d, 0x1.5dbb6a0000000p-7f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_103, hn::Set(d, 0x1.3d503a0000000p+1f)),
                        hn::Set(d, -0x1.0d6c040000000p-8f), hn::Set(d, 0x1.3467200000000p-5f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_78, hn::Set(d, 0x1.6c661c0000000p+2f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_55, hn::Set(d, 0x1.193ea80000000p+1f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_124, hn::Set(d, 0x1.d19c6c0000000p+1f)),
                        hn::Set(d, 0x1.ec22740000000p-8f), hn::Set(d, -0x1.5f1c460000000p-7f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_13, hn::Set(d, 0x1.4141420000000p-6f)),
                        hn::Set(d, 0x1.3bc9b60000000p-6f), hn::Set(d, -0x1.35f0100000000p-9f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_64, hn::Set(d, 0x1.a41a420000000p-4f)),
                        node_11, node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_112, hn::Set(d, 0x1.5aa1640000000p+1f)),
                        hn::Set(d, -0x1.666b1a0000000p-6f), hn::Set(d, 0x1.5d361c0000000p-10f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.f956dc0000000p-1f)),
                        hn::Set(d, -0x1.dab6980000000p-9f), hn::Set(d, -0x1.93a9a20000000p-6f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_128, hn::Set(d, 0x1.642c860000000p-4f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.5a31760000000p+3f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Ge(feature_2, hn::Set(d, 0x1.de2ada0000000p-1f)),
                        node_2, node_1);
                    score = hn::Add(score, node_0);
                }
                /* Tree 86: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Ge(feature_24, hn::Set(d, 0x1.bf0c6e0000000p-4f)),
                        hn::Set(d, 0x1.074afe0000000p-6f), hn::Set(d, -0x1.f75cd40000000p-8f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_103, hn::Set(d, 0x1.d952b20000000p+1f)),
                        hn::Set(d, -0x1.1c12a00000000p-8f), hn::Set(d, 0x1.5e00400000000p-6f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_79, hn::Set(d, 0x1.b35a700000000p+1f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_88, hn::Set(d, 0x1.2ca12c0000000p+0f)),
                        hn::Set(d, -0x1.b84ad20000000p-6f), hn::Set(d, 0x1.2347c80000000p-7f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_87, hn::Set(d, 0x1.5555560000000p-1f)),
                        hn::Set(d, 0x1.62a7d20000000p-6f), hn::Set(d, -0x1.62e4f60000000p-10f));
                    const auto node_4 = hn::IfThenElse(hn::Ge(feature_2, hn::Set(d, 0x1.4637640000000p-1f)),
                        node_10, node_9);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_14, hn::Set(d, 0x1.6666660000000p-1f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_112, hn::Set(d, 0x1.9157e00000000p+1f)),
                        hn::Set(d, -0x1.94514a0000000p-6f), hn::Set(d, -0x1.c9f29a0000000p-8f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_97, hn::Set(d, 0x1.07582a0000000p-3f)),
                        hn::Set(d, 0x1.d6054c0000000p-7f), hn::Set(d, -0x1.a0424c0000000p-8f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_5, hn::Set(d, 0x1.9d0ac20000000p-6f)),
                        node_11, node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.fda8520000000p-1f)),
                        hn::Set(d, 0x1.2b1c080000000p-14f), hn::Set(d, 0x1.b2668e0000000p-7f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_20, hn::Set(d, 0x1.f1027a0000000p-5f)),
                        hn::Set(d, -0x1.2406fe0000000p-7f), hn::Set(d, -0x1.0435ca0000000p-5f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_67, hn::Set(d, 0x1.e666660000000p-1f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_103, hn::Set(d, 0x1.bc74440000000p+2f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_140, hn::Set(d, 0x1.b35a700000000p+1f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 87: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_9, hn::Set(d, 0x1.01c6740000000p+3f)),
                        hn::Set(d, -0x1.6d5e2c0000000p-7f), hn::Set(d, -0x1.7acb260000000p-10f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.5a31760000000p+3f)),
                        hn::Set(d, 0x1.68faf40000000p-8f), hn::Set(d, -0x1.5b938c0000000p-7f));
                    const auto node_3 = hn::IfThenElse(hn::Ge(feature_2, hn::Set(d, 0x1.db820c0000000p-1f)),
                        node_8, node_7);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_11, hn::Set(d, 0x1.eb851e0000000p-6f)),
                        hn::Set(d, 0x1.f1d5200000000p-6f), hn::Set(d, -0x1.2c884a0000000p-7f));
                    const auto node_10 = hn::IfThenElse(hn::Ge(feature_24, hn::Set(d, 0x1.d095a80000000p-5f)),
                        hn::Set(d, 0x1.1776280000000p-6f), hn::Set(d, 0x1.16cfa40000000p-12f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_18, hn::Set(d, 0x1.773b9e0000000p-2f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_87, hn::Set(d, 0x1.c341160000000p-2f)),
                        node_3, node_4);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.193ea80000000p+1f)),
                        hn::Set(d, -0x1.05eec20000000p-5f), hn::Set(d, 0x1.23ebca0000000p-6f));
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_83, hn::Set(d, 0x1.99999a0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 88: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_13, hn::Set(d, 0x1.623fa80000000p-8f)),
                        hn::Set(d, 0x1.b5422e0000000p-7f), hn::Set(d, -0x1.0f51fe0000000p-8f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_140, hn::Set(d, 0x1.1b92800000000p+2f)),
                        hn::Set(d, -0x1.90a4a80000000p-7f), hn::Set(d, 0x1.bff38e0000000p-7f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_140, hn::Set(d, 0x1.e740b80000000p+1f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.9d3bb60000000p+2f)),
                        hn::Set(d, -0x1.10fbb80000000p-8f), hn::Set(d, 0x1.e875420000000p-8f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_13, hn::Set(d, 0x1.4141420000000p-6f)),
                        hn::Set(d, 0x1.35103c0000000p-6f), hn::Set(d, 0x1.f801b60000000p-10f));
                    const auto node_4 = hn::IfThenElse(hn::Ge(feature_2, hn::Set(d, 0x1.f2d1960000000p-1f)),
                        node_10, node_9);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.e1e1e20000000p-5f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_44, hn::Set(d, 0x1.56ebc20000000p-4f)),
                        hn::Set(d, -0x1.ae51100000000p-6f), hn::Set(d, 0x1.92fa060000000p-8f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_101, hn::Set(d, 0x1.4a52940000000p-2f)),
                        hn::Set(d, 0x1.0472880000000p-6f), hn::Set(d, -0x1.9ca8b80000000p-6f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_3, hn::Set(d, 0x1.24924a0000000p-3f)),
                        node_11, node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_13, hn::Set(d, 0x1.9852f00000000p-9f)),
                        hn::Set(d, 0x1.9a50e00000000p-7f), hn::Set(d, -0x1.6ebc3e0000000p-6f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_18, hn::Set(d, 0x1.227f180000000p-1f)),
                        hn::Set(d, 0x1.59ae9a0000000p-6f), hn::Set(d, -0x1.fec6980000000p-8f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_142, hn::Set(d, 0x1.435e500000000p-3f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_65, hn::Set(d, 0x1.edfd6e0000000p-8f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_70, hn::Set(d, 0x1.aaaaaa0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 89: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_124, hn::Set(d, 0x1.7f74280000000p+1f)),
                        hn::Set(d, -0x1.b1f3540000000p-7f), hn::Set(d, -0x1.2161b00000000p-9f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_12, hn::Set(d, 0x1.1c71c80000000p-5f)),
                        hn::Set(d, -0x1.99f56a0000000p-7f), hn::Set(d, 0x1.3ed65a0000000p-8f));
                    const auto node_3 = hn::IfThenElse(hn::Ge(feature_2, hn::Set(d, 0x1.db820c0000000p-1f)),
                        node_8, node_7);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_22, hn::Set(d, 0x1.e55bb80000000p-8f)),
                        hn::Set(d, 0x1.3923c20000000p-9f), hn::Set(d, -0x1.b834980000000p-6f));
                    const auto node_10 = hn::IfThenElse(hn::Ge(feature_24, hn::Set(d, 0x1.c50e220000000p-5f)),
                        hn::Set(d, 0x1.9ec6fc0000000p-6f), hn::Set(d, 0x1.a6cf020000000p-8f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.e1e1e20000000p-5f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_87, hn::Set(d, 0x1.c341160000000p-2f)),
                        node_3, node_4);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.193ea80000000p+1f)),
                        hn::Set(d, -0x1.0493e00000000p-5f), hn::Set(d, 0x1.20b10c0000000p-6f));
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_83, hn::Set(d, 0x1.99999a0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_46 = LoadFeature(d, features + row * 164 + 46, 164);
                /* Tree 90: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.98c2a20000000p+2f)),
                        hn::Set(d, -0x1.3ce70c0000000p-6f), hn::Set(d, 0x1.bc19440000000p-11f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_31, hn::Set(d, -0x1.b6db6e0000000p-1f)),
                        hn::Set(d, -0x1.d42a960000000p-7f), hn::Set(d, -0x1.0946300000000p-5f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_63, hn::Set(d, 0x1.6aaaaa0000000p-2f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Ge(feature_24, hn::Set(d, 0x1.40e4a20000000p-3f)),
                        hn::Set(d, -0x1.7c8d1a0000000p-8f), hn::Set(d, -0x1.13918e0000000p-5f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.0912620000000p+3f)),
                        hn::Set(d, 0x1.fc9f8e0000000p-6f), hn::Set(d, -0x1.7c8d1a0000000p-8f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.09291e0000000p+2f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_154, hn::Set(d, 0x1.6db6dc0000000p-1f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_102, hn::Set(d, 0x1.571f880000000p+3f)),
                        hn::Set(d, -0x1.673eee0000000p-10f), hn::Set(d, 0x1.ef6ffc0000000p-7f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_95, hn::Set(d, 0x1.1027c20000000p+2f)),
                        hn::Set(d, 0x1.e89f8a0000000p-11f), hn::Set(d, 0x1.0e40620000000p-5f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_46, hn::Set(d, 0x1.99999a0000000p-3f)),
                        node_11, node_12);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_140, hn::Set(d, 0x1.1a07b00000000p+2f)),
                        node_5, hn::Set(d, -0x1.256e980000000p-5f));
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_145, hn::Set(d, 0x1.99999a0000000p-3f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 91: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.f79b480000000p-2f)),
                        hn::Set(d, -0x1.634fec0000000p-6f), hn::Set(d, -0x1.0bd5580000000p-8f));
                    const auto node_8 = hn::IfThenElse(hn::Ge(feature_2, hn::Set(d, 0x1.8fd1440000000p-1f)),
                        hn::Set(d, 0x1.dc5b9e0000000p-6f), hn::Set(d, -0x1.9bc5de0000000p-7f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_64, hn::Set(d, 0x1.26934a0000000p-2f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_41, hn::Set(d, 0x1.0fe7580000000p+2f)),
                        hn::Set(d, 0x1.01c54e0000000p-6f), hn::Set(d, -0x1.eb9e080000000p-9f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_24, hn::Set(d, 0x1.2998ee0000000p-2f)),
                        hn::Set(d, -0x1.5c91e20000000p-8f), hn::Set(d, 0x1.75c1bc0000000p-6f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_13, hn::Set(d, 0x1.e1e1e20000000p-8f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Ge(feature_0, hn::Set(d, 0x1.55f05c0000000p+1f)),
                        node_4, node_3);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_74, hn::Set(d, 0x1.f2272a0000000p+0f)),
                        hn::Set(d, -0x1.ae20f00000000p-10f), hn::Set(d, 0x1.5399ba0000000p-6f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.ab68a00000000p-5f)),
                        hn::Set(d, -0x1.8608e20000000p-10f), hn::Set(d, 0x1.e6965a0000000p-7f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.9d3bb60000000p+2f)),
                        node_11, node_12);
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_112, hn::Set(d, 0x1.193ea80000000p+1f)),
                        hn::Set(d, 0x1.54ec780000000p-10f), hn::Set(d, -0x1.01ebd80000000p-5f));
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_63, hn::Set(d, 0x1.8000000000000p-2f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_5, hn::Set(d, 0x1.d89d8a0000000p-6f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 92: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_64, hn::Set(d, 0x1.47ae140000000p-3f)),
                        hn::Set(d, -0x1.ceda340000000p-7f), hn::Set(d, -0x1.bd91400000000p-9f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_61, hn::Set(d, 0x1.4a2df60000000p+2f)),
                        hn::Set(d, 0x1.bad2880000000p-8f), hn::Set(d, -0x1.538fb80000000p-7f));
                    const auto node_3 = hn::IfThenElse(hn::Ge(feature_24, hn::Set(d, 0x1.7dfafe0000000p-5f)),
                        node_8, node_7);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_87, hn::Set(d, 0x1.5555560000000p-1f)),
                        hn::Set(d, 0x1.3f95a00000000p-6f), hn::Set(d, -0x1.0b71f20000000p-7f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_67, hn::Set(d, 0x1.e666660000000p-1f)),
                        hn::Set(d, 0x1.603fa00000000p-10f), hn::Set(d, -0x1.e6e7b60000000p-6f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_140, hn::Set(d, 0x1.b35a700000000p+1f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_15, hn::Set(d, 0x1.6666660000000p-2f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_44, hn::Set(d, 0x1.6aaaaa0000000p-2f)),
                        hn::Set(d, -0x1.0e036c0000000p-6f), hn::Set(d, 0x1.00781a0000000p-6f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_13, hn::Set(d, 0x1.5390940000000p-7f)),
                        hn::Set(d, 0x1.55d90a0000000p-6f), hn::Set(d, -0x1.0eb6ac0000000p-9f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.d316740000000p-2f)),
                        node_11, node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_97, hn::Set(d, 0x1.aaaaaa0000000p-2f)),
                        hn::Set(d, 0x1.ec79240000000p-9f), hn::Set(d, -0x1.9ead9c0000000p-6f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_83, hn::Set(d, 0x1.745d180000000p-6f)),
                        hn::Set(d, 0x1.f979b60000000p-6f), hn::Set(d, 0x1.5302d20000000p-7f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_103, hn::Set(d, 0x1.0432e40000000p+1f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_78, hn::Set(d, 0x1.d4ef960000000p+1f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_55, hn::Set(d, 0x1.0a2b240000000p+1f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_32 = LoadFeature(d, features + row * 164 + 32, 164);
                const auto feature_132 = LoadFeature(d, features + row * 164 + 132, 164);
                /* Tree 93: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_55, hn::Set(d, 0x1.0a2b240000000p+1f)),
                        hn::Set(d, -0x1.a5cda60000000p-6f), hn::Set(d, -0x1.31508a0000000p-7f));
                    const auto node_3 = hn::IfThenElse(hn::Ge(feature_50, hn::Set(d, 0x1.354c3e0000000p+0f)),
                        hn::Set(d, 0x1.4705080000000p-6f), node_7);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_9, hn::Set(d, 0x1.addcb00000000p+2f)),
                        hn::Set(d, -0x1.29c8840000000p-7f), hn::Set(d, 0x1.2ccff00000000p-9f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_52, hn::Set(d, 0x1.52d9680000000p-1f)),
                        hn::Set(d, -0x1.d877760000000p-8f), hn::Set(d, 0x1.8f623c0000000p-6f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_74, hn::Set(d, 0x1.f2272a0000000p+0f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.ffa64a0000000p-2f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_132, hn::Set(d, 0x1.e1e1e20000000p-1f)),
                        hn::Set(d, 0x1.84da880000000p-7f), hn::Set(d, -0x1.517e020000000p-7f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_105, hn::Set(d, 0x1.38c0f80000000p-2f)),
                        hn::Set(d, 0x1.b94bd80000000p-6f), hn::Set(d, -0x1.517e020000000p-7f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_32, hn::Set(d, 0x1.24924a0000000p-2f)),
                        node_11, node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_64, hn::Set(d, 0x1.99999a0000000p-5f)),
                        hn::Set(d, -0x1.61e4060000000p-7f), hn::Set(d, -0x1.09f8b00000000p-5f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_60, hn::Set(d, 0x1.24924a0000000p-3f)),
                        hn::Set(d, -0x1.517e020000000p-7f), hn::Set(d, -0x1.7a4c760000000p-6f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_5, hn::Set(d, 0x1.24924a0000000p-1f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_162, hn::Set(d, 0x1.0842100000000p-4f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_70, hn::Set(d, 0x1.aaaaaa0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 94: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_154, hn::Set(d, 0x1.3333340000000p-1f)),
                        hn::Set(d, -0x1.42d1740000000p-14f), hn::Set(d, -0x1.5e0eb40000000p-6f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_64, hn::Set(d, 0x1.09f95a0000000p-3f)),
                        hn::Set(d, -0x1.9292660000000p-6f), hn::Set(d, 0x1.ff3b0e0000000p-9f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_124, hn::Set(d, 0x1.0822f80000000p+2f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_9, hn::Set(d, 0x1.e500560000000p+2f)),
                        hn::Set(d, 0x1.9fc90e0000000p-12f), hn::Set(d, 0x1.ef6a8e0000000p-7f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_64, hn::Set(d, 0x1.1224480000000p-3f)),
                        hn::Set(d, -0x1.f879320000000p-7f), hn::Set(d, 0x1.9deea00000000p-7f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_141, hn::Set(d, 0x1.3e116c0000000p+1f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_110, hn::Set(d, 0x1.429f840000000p+3f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_21, hn::Set(d, 0x1.249b660000000p-10f)),
                        hn::Set(d, -0x1.0c450c0000000p-7f), hn::Set(d, 0x1.9822200000000p-6f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.37dbfe0000000p+3f)),
                        node_11, hn::Set(d, -0x1.ee97a00000000p-8f));
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_60, hn::Set(d, 0x1.0000000000000p-1f)),
                        node_5, hn::Set(d, -0x1.0416260000000p-5f));
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_67, hn::Set(d, 0x1.e666660000000p-1f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 95: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_11, hn::Set(d, 0x1.b46bf80000000p-8f)),
                        hn::Set(d, -0x1.a7251c0000000p-12f), hn::Set(d, -0x1.4f3dba0000000p-6f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_14, hn::Set(d, 0x1.99999a0000000p-2f)),
                        hn::Set(d, -0x1.8228420000000p-8f), hn::Set(d, 0x1.42f5200000000p-9f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.76b14a0000000p-1f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_11, hn::Set(d, 0x1.eb851e0000000p-6f)),
                        hn::Set(d, 0x1.e05a5e0000000p-6f), hn::Set(d, -0x1.26d91c0000000p-7f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.e1e1e20000000p-5f)),
                        hn::Set(d, -0x1.3d9a7a0000000p-7f), hn::Set(d, 0x1.f8b73c0000000p-8f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_18, hn::Set(d, 0x1.773b9e0000000p-2f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_87, hn::Set(d, 0x1.c341160000000p-2f)),
                        node_3, node_4);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.193ea80000000p+1f)),
                        hn::Set(d, -0x1.024a7e0000000p-5f), hn::Set(d, 0x1.29b10c0000000p-6f));
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_83, hn::Set(d, 0x1.99999a0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 96: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_64, hn::Set(d, 0x1.26934a0000000p-2f)),
                        hn::Set(d, -0x1.7203e80000000p-8f), hn::Set(d, 0x1.c70df40000000p-6f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_11, hn::Set(d, 0x1.b46bf80000000p-8f)),
                        hn::Set(d, -0x1.09be240000000p-7f), hn::Set(d, -0x1.b9a0fe0000000p-6f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_140, hn::Set(d, 0x1.d19c6c0000000p+1f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_97, hn::Set(d, 0x1.6cc8ee0000000p-3f)),
                        hn::Set(d, -0x1.582aac0000000p-7f), hn::Set(d, 0x1.89c5e80000000p-9f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_125, hn::Set(d, 0x1.62e4300000000p+0f)),
                        hn::Set(d, -0x1.49220a0000000p-6f), hn::Set(d, 0x1.106f280000000p-6f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.c57f680000000p+2f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Ge(feature_0, hn::Set(d, 0x1.55f05c0000000p+1f)),
                        node_4, node_3);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.829cbc0000000p-1f)),
                        hn::Set(d, -0x1.bee0940000000p-6f), hn::Set(d, 0x1.9df1d40000000p-10f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.62e4700000000p+3f)),
                        hn::Set(d, 0x1.9ecdc00000000p-8f), hn::Set(d, -0x1.2ff3ec0000000p-7f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_9, hn::Set(d, 0x1.7910b20000000p+2f)),
                        node_11, node_12);
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_112, hn::Set(d, 0x1.193ea80000000p+1f)),
                        hn::Set(d, 0x1.22011c0000000p-9f), hn::Set(d, -0x1.ff4b240000000p-6f));
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_63, hn::Set(d, 0x1.8000000000000p-2f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_5, hn::Set(d, 0x1.d89d8a0000000p-6f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 97: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_55, hn::Set(d, 0x1.0a2b240000000p+1f)),
                        hn::Set(d, -0x1.9ec59a0000000p-6f), hn::Set(d, -0x1.18d0360000000p-7f));
                    const auto node_3 = hn::IfThenElse(hn::Ge(feature_50, hn::Set(d, 0x1.354c3e0000000p+0f)),
                        hn::Set(d, 0x1.5381380000000p-6f), node_7);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_13, hn::Set(d, 0x1.45828c0000000p-6f)),
                        hn::Set(d, 0x1.304ad20000000p-9f), hn::Set(d, -0x1.dcbb0e0000000p-8f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_52, hn::Set(d, 0x1.52d9680000000p-1f)),
                        hn::Set(d, -0x1.94970a0000000p-8f), hn::Set(d, 0x1.8029200000000p-6f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_74, hn::Set(d, 0x1.f2272a0000000p+0f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.ffa64a0000000p-2f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_110, hn::Set(d, 0x1.04852c0000000p+3f)),
                        hn::Set(d, -0x1.d7c01a0000000p-6f), hn::Set(d, 0x1.4635660000000p-7f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_105, hn::Set(d, 0x1.99ed960000000p-2f)),
                        hn::Set(d, 0x1.3389c00000000p-6f), hn::Set(d, -0x1.28f1dc0000000p-6f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_8, hn::Set(d, 0x1.bacf920000000p-6f)),
                        node_11, node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_13, hn::Set(d, 0x1.9852f00000000p-9f)),
                        hn::Set(d, 0x1.4b28f40000000p-6f), hn::Set(d, -0x1.978dba0000000p-6f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_60, hn::Set(d, 0x1.24924a0000000p-3f)),
                        hn::Set(d, 0x1.b78b660000000p-9f), hn::Set(d, -0x1.7562820000000p-6f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_5, hn::Set(d, 0x1.24924a0000000p-1f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_65, hn::Set(d, 0x1.edfd6e0000000p-8f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_70, hn::Set(d, 0x1.aaaaaa0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_121 = LoadFeature(d, features + row * 164 + 121, 164);
                /* Tree 98: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_63, hn::Set(d, 0x1.6aaaaa0000000p-2f)),
                        hn::Set(d, 0x1.bd4d8c0000000p-13f), hn::Set(d, -0x1.e42d200000000p-6f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.bf8d900000000p+1f)),
                        hn::Set(d, -0x1.078b380000000p-5f), hn::Set(d, 0x1.cf5c2a0000000p-7f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_154, hn::Set(d, 0x1.6db6dc0000000p-1f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_24, hn::Set(d, 0x1.430b200000000p-7f)),
                        hn::Set(d, 0x1.0bcdde0000000p-6f), hn::Set(d, -0x1.5ba8ca0000000p-9f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_103, hn::Set(d, 0x1.149a040000000p+2f)),
                        hn::Set(d, -0x1.dd18a20000000p-8f), hn::Set(d, 0x1.5ef5440000000p-6f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_100, hn::Set(d, 0x1.4246300000000p+1f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_142, hn::Set(d, 0x1.69696a0000000p-3f)),
                        node_3, node_4);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_121, hn::Set(d, 0x1.3333340000000p-1f)),
                        hn::Set(d, -0x1.2cae9c0000000p-5f), hn::Set(d, -0x1.312f860000000p-7f));
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_140, hn::Set(d, 0x1.2cd4ac0000000p+2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_98 = LoadFeature(d, features + row * 164 + 98, 164);
                /* Tree 99: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_47, hn::Set(d, 0x1.47ae140000000p-5f)),
                        hn::Set(d, -0x1.ef51bc0000000p-8f), hn::Set(d, -0x1.63c0300000000p-6f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_13, hn::Set(d, 0x1.f81f820000000p-8f)),
                        hn::Set(d, 0x1.bd2ffc0000000p-7f), hn::Set(d, -0x1.16a0be0000000p-8f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_55, hn::Set(d, 0x1.9c04200000000p+0f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_9, hn::Set(d, 0x1.b5a86e0000000p+2f)),
                        hn::Set(d, -0x1.042a7c0000000p-8f), hn::Set(d, 0x1.4e4dc00000000p-7f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_103, hn::Set(d, 0x1.ecdf300000000p+2f)),
                        hn::Set(d, -0x1.26846a0000000p-7f), hn::Set(d, -0x1.e244d80000000p-6f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.0f35e60000000p+3f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.dd6dde0000000p-1f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_112, hn::Set(d, 0x1.7f74280000000p+1f)),
                        hn::Set(d, -0x1.0b333e0000000p-5f), hn::Set(d, 0x1.08aece0000000p-7f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_55, hn::Set(d, 0x1.62e4300000000p+0f)),
                        hn::Set(d, -0x1.535bd80000000p-5f), hn::Set(d, -0x1.1aee200000000p-8f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_12, hn::Set(d, 0x1.b99e040000000p-5f)),
                        node_11, node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_87, hn::Set(d, 0x1.dc47720000000p-2f)),
                        hn::Set(d, -0x1.aa1fea0000000p-8f), hn::Set(d, 0x1.5d3c400000000p-6f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_98, hn::Set(d, 0x1.38d7560000000p+1f)),
                        hn::Set(d, 0x1.06d7e40000000p-6f), hn::Set(d, -0x1.375fb20000000p-8f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_102, hn::Set(d, 0x1.d650dc0000000p+2f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_5, hn::Set(d, 0x1.45828c0000000p-7f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.b8259e0000000p+2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 100: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_18, hn::Set(d, 0x1.50df5a0000000p-2f)),
                        hn::Set(d, -0x1.71df2c0000000p-13f), hn::Set(d, -0x1.ad51340000000p-6f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_12, hn::Set(d, 0x1.dae6080000000p-5f)),
                        hn::Set(d, 0x1.669af00000000p-6f), hn::Set(d, -0x1.d3c5d40000000p-7f));
                    const auto node_3 = hn::IfThenElse(hn::Ge(feature_53, hn::Set(d, 0x1.0000000000000p-2f)),
                        node_8, node_7);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_70, hn::Set(d, 0x1.aaaaaa0000000p-2f)),
                        hn::Set(d, -0x1.2e10480000000p-11f), hn::Set(d, -0x1.df9b4e0000000p-7f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_13, hn::Set(d, 0x1.410ee40000000p-10f)),
                        hn::Set(d, -0x1.c974680000000p-6f), hn::Set(d, 0x1.c8415c0000000p-8f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.b8259e0000000p+2f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Ge(feature_3, hn::Set(d, 0x1.bacf920000000p-8f)),
                        node_4, node_3);
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_162, hn::Set(d, 0x1.0b21640000000p-2f)),
                        hn::Set(d, 0x1.436c460000000p-6f), hn::Set(d, -0x1.833f0c0000000p-7f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_112, hn::Set(d, 0x1.0a2b240000000p+1f)),
                        hn::Set(d, -0x1.7849100000000p-6f), node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_102, hn::Set(d, 0x1.8efa420000000p+2f)),
                        hn::Set(d, 0x1.969ba60000000p-6f), hn::Set(d, -0x1.1433e80000000p-6f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_18, hn::Set(d, 0x1.7777780000000p-1f)),
                        hn::Set(d, 0x1.1289020000000p-5f), hn::Set(d, 0x1.4ce2280000000p-7f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_102, hn::Set(d, 0x1.4f8c7a0000000p+3f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.d316740000000p-2f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_139, hn::Set(d, 0x1.d89d8a0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 101: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_18, hn::Set(d, 0x1.50df5a0000000p-2f)),
                        hn::Set(d, -0x1.ed51c00000000p-13f), hn::Set(d, -0x1.a49c2e0000000p-6f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_42, hn::Set(d, 0x1.9c04200000000p+0f)),
                        hn::Set(d, -0x1.a657400000000p-7f), hn::Set(d, 0x1.5f24e80000000p-6f));
                    const auto node_3 = hn::IfThenElse(hn::Ge(feature_53, hn::Set(d, 0x1.0000000000000p-2f)),
                        node_8, node_7);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_136, hn::Set(d, 0x1.3333340000000p-2f)),
                        hn::Set(d, -0x1.1a2bee0000000p-9f), hn::Set(d, -0x1.3a3d340000000p-5f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_5, hn::Set(d, 0x1.99999a0000000p-4f)),
                        hn::Set(d, 0x1.dc08120000000p-15f), hn::Set(d, 0x1.57a61e0000000p-7f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.9b167a0000000p+2f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Ge(feature_3, hn::Set(d, 0x1.bacf920000000p-8f)),
                        node_4, node_3);
                    const auto node_11 = hn::IfThenElse(hn::Ge(feature_24, hn::Set(d, 0x1.97e1460000000p-8f)),
                        hn::Set(d, -0x1.7247100000000p-7f), hn::Set(d, 0x1.8aa1020000000p-7f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_100, hn::Set(d, 0x1.00a5900000000p+2f)),
                        hn::Set(d, 0x1.b1aaf80000000p-7f), hn::Set(d, 0x1.0a967e0000000p-5f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.b91b920000000p-4f)),
                        node_11, node_12);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_141, hn::Set(d, 0x1.0a2b240000000p+1f)),
                        node_5, hn::Set(d, -0x1.65c0ee0000000p-7f));
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_139, hn::Set(d, 0x1.d89d8a0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 102: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_64, hn::Set(d, 0x1.188c460000000p-2f)),
                        hn::Set(d, 0x1.e6dcf60000000p-9f), hn::Set(d, -0x1.0766cc0000000p-6f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.5789160000000p-3f)),
                        hn::Set(d, 0x1.12448c0000000p-10f), hn::Set(d, 0x1.eb19800000000p-6f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_139, hn::Set(d, 0x1.b6db6e0000000p-2f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_20, hn::Set(d, 0x1.220e640000000p-2f)),
                        hn::Set(d, 0x1.f28eae0000000p-6f), hn::Set(d, -0x1.c62e3c0000000p-9f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_62, hn::Set(d, 0x1.16d4520000000p+2f)),
                        node_9, hn::Set(d, -0x1.4dfa2e0000000p-6f));
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_141, hn::Set(d, 0x1.f2272a0000000p+0f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_100, hn::Set(d, 0x1.0c9f540000000p+2f)),
                        hn::Set(d, -0x1.be8c520000000p-9f), hn::Set(d, -0x1.a8f5a00000000p-6f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_24, hn::Set(d, 0x1.bd42b20000000p-5f)),
                        hn::Set(d, -0x1.4cdb8c0000000p-11f), hn::Set(d, 0x1.725af80000000p-7f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_110, hn::Set(d, 0x1.3086480000000p+3f)),
                        node_11, node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_103, hn::Set(d, 0x1.27a48e0000000p+2f)),
                        hn::Set(d, -0x1.8d6a1e0000000p-7f), hn::Set(d, 0x1.2316100000000p-6f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_60, hn::Set(d, 0x1.99999a0000000p-3f)),
                        node_13, hn::Set(d, -0x1.f3ec040000000p-6f));
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_67, hn::Set(d, 0x1.e666660000000p-1f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_140, hn::Set(d, 0x1.b35a700000000p+1f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_40 = LoadFeature(d, features + row * 164 + 40, 164);
                /* Tree 103: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_13, hn::Set(d, 0x1.45828c0000000p-6f)),
                        hn::Set(d, 0x1.584fbe0000000p-9f), hn::Set(d, -0x1.2647920000000p-7f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_124, hn::Set(d, 0x1.db56540000000p+1f)),
                        hn::Set(d, -0x1.2f235a0000000p-8f), hn::Set(d, -0x1.94e0a60000000p-6f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_31, hn::Set(d, -0x1.3333340000000p-1f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_128, hn::Set(d, 0x1.b6db6e0000000p-3f)),
                        hn::Set(d, -0x1.74cd020000000p-7f), hn::Set(d, 0x1.be579a0000000p-7f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.5a31760000000p+3f)),
                        hn::Set(d, 0x1.1766320000000p-6f), hn::Set(d, -0x1.2e1bb80000000p-7f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_12, hn::Set(d, 0x1.61d7ca0000000p-5f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_40, hn::Set(d, 0x1.0000000000000p-3f)),
                        node_3, node_4);
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_103, hn::Set(d, 0x1.27a48e0000000p+2f)),
                        hn::Set(d, -0x1.9a00a40000000p-7f), hn::Set(d, 0x1.87e6060000000p-7f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_18, hn::Set(d, 0x1.5473400000000p-2f)),
                        hn::Set(d, 0x1.2957c00000000p-6f), node_12);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_60, hn::Set(d, 0x1.0000000000000p-1f)),
                        node_5, hn::Set(d, -0x1.ff64840000000p-6f));
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_67, hn::Set(d, 0x1.e666660000000p-1f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_58 = LoadFeature(d, features + row * 164 + 58, 164);
                /* Tree 104: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_58, hn::Set(d, 0x1.24924a0000000p-1f)),
                        hn::Set(d, -0x1.23ac540000000p-5f), hn::Set(d, -0x1.0f0d1e0000000p-7f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_20, hn::Set(d, 0x1.bbe8600000000p-3f)),
                        node_7, hn::Set(d, 0x1.14016c0000000p-6f));
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_18, hn::Set(d, 0x1.6e66c00000000p-2f)),
                        hn::Set(d, 0x1.8be7740000000p-6f), hn::Set(d, 0x1.046bc80000000p-9f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.5a31760000000p+3f)),
                        hn::Set(d, 0x1.8172680000000p-6f), hn::Set(d, -0x1.35c8ce0000000p-7f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_32, hn::Set(d, 0x1.8000000000000p-1f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.bf8d900000000p+1f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_88, hn::Set(d, 0x1.06857a0000000p-1f)),
                        hn::Set(d, -0x1.387bec0000000p-10f), hn::Set(d, -0x1.2126800000000p-6f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.fd92820000000p+2f)),
                        hn::Set(d, 0x1.517d640000000p-8f), hn::Set(d, 0x1.83a5c80000000p-6f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_145, hn::Set(d, 0x1.b6db6e0000000p-3f)),
                        node_11, node_12);
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_121, hn::Set(d, 0x1.3333340000000p-1f)),
                        hn::Set(d, -0x1.26609e0000000p-5f), hn::Set(d, -0x1.34290c0000000p-7f));
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_140, hn::Set(d, 0x1.2cd4ac0000000p+2f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_140, hn::Set(d, 0x1.b35a700000000p+1f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_86 = LoadFeature(d, features + row * 164 + 86, 164);
                const auto feature_116 = LoadFeature(d, features + row * 164 + 116, 164);
                /* Tree 105: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_11, hn::Set(d, 0x1.16872c0000000p-3f)),
                        hn::Set(d, 0x1.7a96d60000000p-9f), hn::Set(d, -0x1.9cb62c0000000p-6f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.5789160000000p-3f)),
                        hn::Set(d, 0x1.cb0db20000000p-10f), hn::Set(d, 0x1.da94ba0000000p-6f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_139, hn::Set(d, 0x1.b6db6e0000000p-2f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_0, hn::Set(d, 0x1.743e1e0000000p+1f)),
                        hn::Set(d, 0x1.20cfa80000000p-5f), hn::Set(d, -0x1.5e1d960000000p-9f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_19, hn::Set(d, 0x1.1b63a20000000p-7f)),
                        hn::Set(d, 0x1.1432580000000p-6f), hn::Set(d, -0x1.a2fc260000000p-6f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_55, hn::Set(d, 0x1.193ea80000000p+0f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_141, hn::Set(d, 0x1.f2272a0000000p+0f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_42, hn::Set(d, 0x1.8ba7480000000p+1f)),
                        hn::Set(d, -0x1.9d03e00000000p-6f), hn::Set(d, -0x1.c78abe0000000p-8f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_86, hn::Set(d, 0x1.99999a0000000p-2f)),
                        node_11, hn::Set(d, 0x1.42a31c0000000p-7f));
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_116, hn::Set(d, 0x1.3333340000000p-1f)),
                        hn::Set(d, -0x1.8844e80000000p-10f), hn::Set(d, 0x1.b75a500000000p-7f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_97, hn::Set(d, 0x1.756a140000000p-2f)),
                        hn::Set(d, -0x1.26f75e0000000p-5f), hn::Set(d, -0x1.79f8ec0000000p-7f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_140, hn::Set(d, 0x1.2cd4ac0000000p+2f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_0, hn::Set(d, 0x1.1a5d280000000p+1f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_140, hn::Set(d, 0x1.b35a700000000p+1f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_23 = LoadFeature(d, features + row * 164 + 23, 164);
                const auto feature_69 = LoadFeature(d, features + row * 164 + 69, 164);
                /* Tree 106: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.260dd60000000p-1f)),
                        hn::Set(d, -0x1.a7f0680000000p-6f), hn::Set(d, -0x1.dd1f380000000p-9f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.193ea80000000p+1f)),
                        hn::Set(d, -0x1.d9db2a0000000p-9f), hn::Set(d, 0x1.0890f80000000p-6f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_24, hn::Set(d, 0x1.1bd4180000000p-11f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.10aa480000000p+3f)),
                        hn::Set(d, -0x1.aa6b7e0000000p-6f), hn::Set(d, 0x1.5e40660000000p-7f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.5a31760000000p+3f)),
                        hn::Set(d, 0x1.d633a60000000p-8f), hn::Set(d, -0x1.ae31240000000p-7f));
                    const auto node_4 = hn::IfThenElse(hn::Ge(feature_2, hn::Set(d, 0x1.781b2a0000000p-1f)),
                        node_10, node_9);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_15, hn::Set(d, 0x1.bbbbbc0000000p-2f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_144, hn::Set(d, 0x1.e9bd380000000p-3f)),
                        hn::Set(d, -0x1.e28e300000000p-6f), hn::Set(d, 0x1.ac782c0000000p-7f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_69, hn::Set(d, 0x1.8413920000000p-1f)),
                        hn::Set(d, 0x1.ae6df00000000p-9f), hn::Set(d, 0x1.ce88100000000p-6f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_82, hn::Set(d, 0x1.71024e0000000p-4f)),
                        node_11, node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_20, hn::Set(d, 0x1.959b940000000p-3f)),
                        hn::Set(d, -0x1.630a5a0000000p-7f), hn::Set(d, 0x1.7b625c0000000p-6f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_22, hn::Set(d, 0x1.2997b60000000p-6f)),
                        hn::Set(d, 0x1.2ca7e00000000p-5f), hn::Set(d, -0x1.39c45a0000000p-8f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_41, hn::Set(d, 0x1.c35fc80000000p+1f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_23, hn::Set(d, 0x1.5972a80000000p-5f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_74, hn::Set(d, 0x1.f2272a0000000p+0f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 107: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_100, hn::Set(d, 0x1.2bfdc60000000p+2f)),
                        hn::Set(d, -0x1.3edc200000000p-8f), hn::Set(d, -0x1.4d29460000000p-6f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.0f35e60000000p+3f)),
                        hn::Set(d, 0x1.3f961a0000000p-8f), hn::Set(d, -0x1.8d31140000000p-7f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.dd6dde0000000p-1f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_11, hn::Set(d, 0x1.f4465a0000000p-8f)),
                        hn::Set(d, -0x1.f02b6e0000000p-6f), hn::Set(d, 0x1.cb0a840000000p-9f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_79, hn::Set(d, 0x1.32ee3c0000000p+1f)),
                        hn::Set(d, 0x1.2fca5e0000000p-8f), hn::Set(d, 0x1.447aea0000000p-6f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_21, hn::Set(d, 0x1.6830800000000p-12f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.b8259e0000000p+2f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Ge(feature_52, hn::Set(d, 0x1.338c7e0000000p-1f)),
                        hn::Set(d, 0x1.fd0fdc0000000p-9f), hn::Set(d, -0x1.7219600000000p-6f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_95, hn::Set(d, 0x1.191efa0000000p+2f)),
                        hn::Set(d, 0x1.fd0fdc0000000p-9f), hn::Set(d, 0x1.b2e97e0000000p-6f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.1e8cb00000000p+2f)),
                        node_11, node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_82, hn::Set(d, 0x1.af286c0000000p-5f)),
                        hn::Set(d, 0x1.4f55e40000000p-6f), hn::Set(d, -0x1.57e4e80000000p-6f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_88, hn::Set(d, 0x1.e744380000000p+0f)),
                        hn::Set(d, 0x1.2a7a4c0000000p-5f), hn::Set(d, -0x1.7e849e0000000p-10f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_82, hn::Set(d, 0x1.15b1e60000000p-4f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Ge(feature_0, hn::Set(d, 0x1.4836d20000000p+1f)),
                        node_6, node_5);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_74, hn::Set(d, 0x1.f2272a0000000p+0f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 108: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_15, hn::Set(d, 0x1.bbbbbc0000000p-2f)),
                        hn::Set(d, -0x1.2480a40000000p-9f), hn::Set(d, 0x1.35b7560000000p-8f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.57f05e0000000p-4f)),
                        hn::Set(d, -0x1.f944640000000p-11f), hn::Set(d, -0x1.f3ec8e0000000p-6f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_63, hn::Set(d, 0x1.6aaaaa0000000p-2f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_85, hn::Set(d, 0x1.3333340000000p-2f)),
                        hn::Set(d, -0x1.166d700000000p-5f), hn::Set(d, 0x1.77ad3e0000000p-8f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_156, hn::Set(d, 0x1.62e4300000000p-1f)),
                        hn::Set(d, -0x1.4292b60000000p-7f), hn::Set(d, 0x1.25cc980000000p-6f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_116, hn::Set(d, 0x1.3333340000000p-1f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_77, hn::Set(d, 0x1.0000000000000p-1f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_100, hn::Set(d, 0x1.a20bd80000000p-2f)),
                        hn::Set(d, -0x1.83dbc80000000p-6f), hn::Set(d, 0x1.fcc0ee0000000p-7f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_13, hn::Set(d, 0x1.2f684c0000000p-6f)),
                        hn::Set(d, 0x1.65ca200000000p-6f), hn::Set(d, -0x1.0cec600000000p-7f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_49, hn::Set(d, 0x1.570a3e0000000p-1f)),
                        node_11, node_12);
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_97, hn::Set(d, 0x1.7181120000000p+0f)),
                        hn::Set(d, 0x1.24f68c0000000p-5f), hn::Set(d, 0x1.1075680000000p-7f));
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_83, hn::Set(d, 0x1.2bb5120000000p-5f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_139, hn::Set(d, 0x1.d89d8a0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 109: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_11, hn::Set(d, 0x1.16872c0000000p-3f)),
                        hn::Set(d, 0x1.584d1c0000000p-9f), hn::Set(d, -0x1.a001f60000000p-6f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.5789160000000p-3f)),
                        hn::Set(d, 0x1.15a4000000000p-10f), hn::Set(d, 0x1.e1b6040000000p-6f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_139, hn::Set(d, 0x1.b6db6e0000000p-2f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_20, hn::Set(d, 0x1.c2fbbe0000000p-4f)),
                        hn::Set(d, 0x1.ce3f0a0000000p-7f), hn::Set(d, 0x1.218bd20000000p-5f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_62, hn::Set(d, 0x1.16d4520000000p+2f)),
                        node_9, hn::Set(d, -0x1.3536c80000000p-6f));
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_141, hn::Set(d, 0x1.f2272a0000000p+0f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Ge(feature_24, hn::Set(d, 0x1.431fae0000000p-9f)),
                        hn::Set(d, 0x1.8943000000000p-8f), hn::Set(d, -0x1.52da6e0000000p-7f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_0, hn::Set(d, 0x1.7204880000000p+1f)),
                        hn::Set(d, -0x1.46d2e80000000p-7f), hn::Set(d, 0x1.dab8600000000p-8f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_127, hn::Set(d, 0x1.24924a0000000p-2f)),
                        node_11, node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_12, hn::Set(d, 0x1.cb5d4e0000000p-5f)),
                        hn::Set(d, -0x1.f937d60000000p-7f), hn::Set(d, -0x1.cef5a80000000p-10f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.7dd2460000000p-1f)),
                        hn::Set(d, -0x1.8ec53e0000000p-6f), hn::Set(d, 0x1.4cb7360000000p-9f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_44, hn::Set(d, 0x1.0000000000000p-3f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_18, hn::Set(d, 0x1.106d840000000p-1f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_140, hn::Set(d, 0x1.b35a700000000p+1f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 110: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_13, hn::Set(d, 0x1.45828c0000000p-6f)),
                        hn::Set(d, 0x1.60018a0000000p-9f), hn::Set(d, -0x1.159d720000000p-7f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.d5458a0000000p+2f)),
                        hn::Set(d, -0x1.c8df000000000p-7f), hn::Set(d, 0x1.d439d40000000p-8f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_31, hn::Set(d, -0x1.5555540000000p-1f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.dd6dde0000000p-1f)),
                        hn::Set(d, 0x1.dc9eb60000000p-10f), hn::Set(d, 0x1.2fb93c0000000p-6f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_3, hn::Set(d, 0x1.c71c720000000p-4f)),
                        hn::Set(d, 0x1.29cea20000000p-7f), hn::Set(d, -0x1.4bdd8e0000000p-6f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_70, hn::Set(d, 0x1.5555560000000p-2f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_40, hn::Set(d, 0x1.0000000000000p-3f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_21, hn::Set(d, 0x1.249b660000000p-10f)),
                        hn::Set(d, -0x1.9b3a420000000p-8f), hn::Set(d, 0x1.8469580000000p-6f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.37dbfe0000000p+3f)),
                        node_11, hn::Set(d, -0x1.2cb1180000000p-7f));
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_60, hn::Set(d, 0x1.0000000000000p-1f)),
                        node_5, hn::Set(d, -0x1.faa5780000000p-6f));
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_67, hn::Set(d, 0x1.e666660000000p-1f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 111: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_11, hn::Set(d, 0x1.1648d60000000p-7f)),
                        hn::Set(d, -0x1.94db240000000p-7f), hn::Set(d, 0x1.01deb00000000p-8f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.5789160000000p-3f)),
                        hn::Set(d, 0x1.e1ef100000000p-10f), hn::Set(d, 0x1.cb61be0000000p-6f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_139, hn::Set(d, 0x1.b6db6e0000000p-2f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_41, hn::Set(d, 0x1.69c2620000000p+2f)),
                        hn::Set(d, 0x1.df61800000000p-6f), hn::Set(d, -0x1.334a140000000p-7f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_12, hn::Set(d, 0x1.10a7500000000p-4f)),
                        node_9, hn::Set(d, -0x1.6edce00000000p-6f));
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_141, hn::Set(d, 0x1.f2272a0000000p+0f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_140, hn::Set(d, 0x1.1c54660000000p+2f)),
                        hn::Set(d, -0x1.bfcf860000000p-8f), hn::Set(d, -0x1.b15ca00000000p-6f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.faacfa0000000p+2f)),
                        hn::Set(d, 0x1.df00e40000000p-8f), hn::Set(d, -0x1.038ba80000000p-7f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_3, hn::Set(d, 0x1.0000000000000p-2f)),
                        node_11, node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_97, hn::Set(d, 0x1.960adc0000000p-3f)),
                        hn::Set(d, -0x1.5ecbc00000000p-7f), hn::Set(d, 0x1.ba741a0000000p-8f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.0dd7180000000p+3f)),
                        hn::Set(d, 0x1.7005bc0000000p-6f), hn::Set(d, 0x1.5e75fa0000000p-9f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.e1e1e20000000p-5f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.9d3bb60000000p+2f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_140, hn::Set(d, 0x1.b35a700000000p+1f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_138 = LoadFeature(d, features + row * 164 + 138, 164);
                /* Tree 112: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_87, hn::Set(d, 0x1.ba781a0000000p-2f)),
                        hn::Set(d, -0x1.33b2280000000p-9f), hn::Set(d, 0x1.ab30220000000p-8f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.db56540000000p+1f)),
                        hn::Set(d, -0x1.0658ae0000000p-5f), hn::Set(d, 0x1.2a8a1e0000000p-6f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_154, hn::Set(d, 0x1.3333340000000p-1f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_138, hn::Set(d, 0x1.0000000000000p-3f)),
                        hn::Set(d, -0x1.bd734c0000000p-6f), hn::Set(d, 0x1.aa51fc0000000p-8f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_70, hn::Set(d, 0x1.0000000000000p-2f)),
                        hn::Set(d, 0x1.ce0b7e0000000p-6f), hn::Set(d, -0x1.f016460000000p-11f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_46, hn::Set(d, 0x1.99999a0000000p-3f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_142, hn::Set(d, 0x1.24924a0000000p-3f)),
                        node_3, node_4);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_97, hn::Set(d, 0x1.756a140000000p-2f)),
                        hn::Set(d, -0x1.21f4bc0000000p-5f), hn::Set(d, -0x1.968df80000000p-7f));
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_140, hn::Set(d, 0x1.2cd4ac0000000p+2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 113: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_64, hn::Set(d, 0x1.4000000000000p-2f)),
                        hn::Set(d, -0x1.96d35e0000000p-7f), hn::Set(d, 0x1.9048080000000p-8f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.b8259e0000000p+2f)),
                        hn::Set(d, -0x1.c65d240000000p-10f), hn::Set(d, 0x1.0b7d540000000p-7f));
                    const auto node_3 = hn::IfThenElse(hn::Ge(feature_0, hn::Set(d, 0x1.5583a40000000p+1f)),
                        node_8, node_7);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_62, hn::Set(d, 0x1.c35fc80000000p+1f)),
                        hn::Set(d, -0x1.f4ab200000000p-7f), hn::Set(d, 0x1.a8bbb40000000p-8f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.62e4700000000p+3f)),
                        hn::Set(d, 0x1.3a63a00000000p-7f), hn::Set(d, -0x1.26e05c0000000p-7f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_9, hn::Set(d, 0x1.a42d4e0000000p+2f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_5, hn::Set(d, 0x1.0000000000000p-2f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_21, hn::Set(d, 0x1.249b660000000p-10f)),
                        hn::Set(d, -0x1.54d1800000000p-8f), hn::Set(d, 0x1.7442080000000p-6f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_114, hn::Set(d, 0x1.37dbfe0000000p+3f)),
                        node_11, hn::Set(d, -0x1.cfeea80000000p-8f));
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_60, hn::Set(d, 0x1.0000000000000p-1f)),
                        node_5, hn::Set(d, -0x1.f7a8ca0000000p-6f));
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_67, hn::Set(d, 0x1.e666660000000p-1f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 114: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_124, hn::Set(d, 0x1.9157e00000000p+1f)),
                        hn::Set(d, -0x1.a6312a0000000p-8f), hn::Set(d, 0x1.2d0dc20000000p-7f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_13, hn::Set(d, 0x1.09ddba0000000p-9f)),
                        hn::Set(d, -0x1.15d72a0000000p-6f), hn::Set(d, 0x1.b79ece0000000p-7f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_78, hn::Set(d, 0x1.4ba2580000000p+2f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_19, hn::Set(d, 0x1.6bd6020000000p-6f)),
                        hn::Set(d, 0x1.25a2420000000p-7f), hn::Set(d, -0x1.cc33d40000000p-7f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_110, hn::Set(d, 0x1.f53b0a0000000p+2f)),
                        hn::Set(d, -0x1.0db0a20000000p-13f), hn::Set(d, 0x1.2e18f20000000p-5f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_95, hn::Set(d, 0x1.57fb1e0000000p+2f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_47, hn::Set(d, 0x1.24924a0000000p-3f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_21, hn::Set(d, 0x1.c6c93a0000000p-13f)),
                        hn::Set(d, -0x1.0a77340000000p-6f), hn::Set(d, -0x1.7376f60000000p-9f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.d5f0180000000p+2f)),
                        hn::Set(d, 0x1.7c5dce0000000p-11f), hn::Set(d, 0x1.b2fcc00000000p-7f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_103, hn::Set(d, 0x1.b94f720000000p+2f)),
                        node_11, node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_95, hn::Set(d, 0x1.e60c920000000p+2f)),
                        hn::Set(d, -0x1.63f23a0000000p-8f), hn::Set(d, -0x1.e538340000000p-6f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_141, hn::Set(d, 0x1.51cca20000000p+1f)),
                        hn::Set(d, 0x1.2203420000000p-6f), hn::Set(d, -0x1.e81ed80000000p-6f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_0, hn::Set(d, 0x1.7bb50a0000000p+1f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_101, hn::Set(d, 0x1.0000000000000p-1f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_140, hn::Set(d, 0x1.c715a60000000p+1f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 115: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_70, hn::Set(d, 0x1.aaaaaa0000000p-2f)),
                        hn::Set(d, -0x1.96c3ce0000000p-11f), hn::Set(d, -0x1.006fe60000000p-6f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_50, hn::Set(d, 0x1.0ec0500000000p+1f)),
                        hn::Set(d, -0x1.3639020000000p-8f), hn::Set(d, 0x1.88a54c0000000p-6f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_74, hn::Set(d, 0x1.f2272a0000000p+0f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_104, hn::Set(d, 0x1.99999a0000000p-1f)),
                        hn::Set(d, -0x1.44ff000000000p-6f), hn::Set(d, 0x1.30a0760000000p-8f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_12, hn::Set(d, 0x1.1422840000000p-4f)),
                        hn::Set(d, 0x1.2bfef80000000p-6f), hn::Set(d, -0x1.2c53fc0000000p-6f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_103, hn::Set(d, 0x1.f58e3c0000000p+2f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.b8259e0000000p+2f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_140, hn::Set(d, 0x1.16d4520000000p+2f)),
                        hn::Set(d, -0x1.8b0c400000000p-6f), hn::Set(d, -0x1.586f8c0000000p-8f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.58b67e0000000p-2f)),
                        hn::Set(d, 0x1.e1aa280000000p-7f), hn::Set(d, -0x1.24e36c0000000p-6f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_22, hn::Set(d, 0x1.4f50060000000p-7f)),
                        node_11, node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.033d920000000p-4f)),
                        hn::Set(d, -0x1.ff66560000000p-9f), hn::Set(d, 0x1.286c6a0000000p-5f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_124, hn::Set(d, 0x1.193ea80000000p+2f)),
                        node_13, hn::Set(d, -0x1.b2b6540000000p-7f));
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_44, hn::Set(d, 0x1.6aaaaa0000000p-2f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_125, hn::Set(d, 0x1.32ee3c0000000p+1f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 116: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Ge(feature_21, hn::Set(d, 0x1.7c22da0000000p-12f)),
                        hn::Set(d, 0x1.96dbb00000000p-8f), hn::Set(d, -0x1.59a72c0000000p-7f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_74, hn::Set(d, 0x1.0a2b240000000p+1f)),
                        hn::Set(d, -0x1.e8f5220000000p-8f), hn::Set(d, 0x1.d88a2e0000000p-7f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_127, hn::Set(d, 0x1.24924a0000000p-2f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_44, hn::Set(d, 0x1.aaaaaa0000000p-2f)),
                        hn::Set(d, -0x1.2585040000000p-7f), hn::Set(d, 0x1.544f020000000p-6f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_69, hn::Set(d, 0x1.e5846a0000000p-1f)),
                        hn::Set(d, -0x1.69d1aa0000000p-5f), hn::Set(d, -0x1.8d9f7c0000000p-7f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_95, hn::Set(d, 0x1.ec5cba0000000p+2f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_125, hn::Set(d, 0x1.32ee3c0000000p+1f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_124, hn::Set(d, 0x1.62e4300000000p+1f)),
                        hn::Set(d, 0x1.90908a0000000p-7f), hn::Set(d, -0x1.849fa40000000p-8f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_141, hn::Set(d, 0x1.3e116c0000000p+1f)),
                        hn::Set(d, 0x1.99cede0000000p-7f), hn::Set(d, -0x1.f92c660000000p-9f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.6d0ac60000000p+2f)),
                        node_11, node_12);
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_60, hn::Set(d, 0x1.5555560000000p-2f)),
                        hn::Set(d, 0x1.3889360000000p-8f), hn::Set(d, -0x1.fc74160000000p-6f));
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_67, hn::Set(d, 0x1.e666660000000p-1f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_110, hn::Set(d, 0x1.429f840000000p+3f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 117: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_127, hn::Set(d, 0x1.24924a0000000p-2f)),
                        hn::Set(d, -0x1.79faa00000000p-10f), hn::Set(d, -0x1.a6d0460000000p-7f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_78, hn::Set(d, 0x1.7e52e60000000p+2f)),
                        hn::Set(d, 0x1.35b6b80000000p-9f), hn::Set(d, -0x1.2c108a0000000p-6f));
                    const auto node_3 = hn::IfThenElse(hn::Ge(feature_2, hn::Set(d, 0x1.b9a9b80000000p-1f)),
                        node_8, node_7);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_69, hn::Set(d, 0x1.1eb8520000000p-2f)),
                        hn::Set(d, -0x1.91eec00000000p-8f), hn::Set(d, 0x1.e126120000000p-6f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.033d920000000p-4f)),
                        hn::Set(d, -0x1.3832d40000000p-7f), hn::Set(d, 0x1.e70aa60000000p-8f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_18, hn::Set(d, 0x1.729c080000000p-2f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_87, hn::Set(d, 0x1.d67c8a0000000p-2f)),
                        node_3, node_4);
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.193ea80000000p+1f)),
                        hn::Set(d, -0x1.f8eb580000000p-6f), hn::Set(d, 0x1.2de92e0000000p-6f));
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_83, hn::Set(d, 0x1.99999a0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 118: preserve ordered sums and scope node temporaries. */ {
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_63, hn::Set(d, 0x1.6aaaaa0000000p-2f)),
                        hn::Set(d, 0x1.7e223e0000000p-13f), hn::Set(d, -0x1.ce607c0000000p-6f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.bf8d900000000p+1f)),
                        hn::Set(d, -0x1.ff14260000000p-6f), hn::Set(d, 0x1.7fd9fe0000000p-7f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_154, hn::Set(d, 0x1.6db6dc0000000p-1f)),
                        node_5, node_6);
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_24, hn::Set(d, 0x1.430b200000000p-7f)),
                        hn::Set(d, 0x1.f360740000000p-7f), hn::Set(d, -0x1.73d7960000000p-15f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_44, hn::Set(d, 0x1.6aaaaa0000000p-2f)),
                        hn::Set(d, 0x1.dc9cd20000000p-6f), hn::Set(d, -0x1.f42ce60000000p-7f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_95, hn::Set(d, 0x1.6cae8a0000000p+3f)),
                        node_7, node_8);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_142, hn::Set(d, 0x1.69696a0000000p-3f)),
                        node_3, node_4);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_140, hn::Set(d, 0x1.2cd4ac0000000p+2f)),
                        node_1, hn::Set(d, -0x1.01c6e00000000p-5f));
                    score = hn::Add(score, node_0);
                }
                /* Tree 119: preserve ordered sums and scope node temporaries. */ {
                    const auto node_7 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.f7bdf00000000p-1f)),
                        hn::Set(d, -0x1.39aa860000000p-7f), hn::Set(d, 0x1.cb5ca40000000p-7f));
                    const auto node_8 = hn::IfThenElse(hn::Lt(feature_124, hn::Set(d, 0x1.32ee3c0000000p+1f)),
                        hn::Set(d, 0x1.034a3a0000000p-6f), hn::Set(d, -0x1.833d760000000p-10f));
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.d0983c0000000p-1f)),
                        node_7, node_8);
                    const auto node_9 = hn::IfThenElse(hn::Lt(feature_42, hn::Set(d, 0x1.27ff8e0000000p+2f)),
                        hn::Set(d, 0x1.a238600000000p-11f), hn::Set(d, -0x1.bf5e340000000p-6f));
                    const auto node_10 = hn::IfThenElse(hn::Lt(feature_160, hn::Set(d, 0x1.69696a0000000p-5f)),
                        hn::Set(d, -0x1.56e1060000000p-10f), hn::Set(d, 0x1.02b3fa0000000p-6f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_5, hn::Set(d, 0x1.99999a0000000p-4f)),
                        node_9, node_10);
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.9d3bb60000000p+2f)),
                        node_3, node_4);
                    const auto node_11 = hn::IfThenElse(hn::Lt(feature_55, hn::Set(d, 0x1.193ea80000000p+1f)),
                        hn::Set(d, -0x1.791e8c0000000p-6f), hn::Set(d, 0x1.3097e00000000p-9f));
                    const auto node_12 = hn::IfThenElse(hn::Lt(feature_95, hn::Set(d, 0x1.55c5b60000000p+2f)),
                        hn::Set(d, 0x1.3097e00000000p-9f), hn::Set(d, 0x1.cd1a040000000p-6f));
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_158, hn::Set(d, 0x1.1e8cb00000000p+2f)),
                        node_11, node_12);
                    const auto node_13 = hn::IfThenElse(hn::Lt(feature_82, hn::Set(d, 0x1.af286c0000000p-5f)),
                        hn::Set(d, 0x1.e947f20000000p-7f), hn::Set(d, -0x1.73d5120000000p-6f));
                    const auto node_14 = hn::IfThenElse(hn::Lt(feature_88, hn::Set(d, 0x1.e744380000000p+0f)),
                        hn::Set(d, 0x1.1d24b40000000p-5f), hn::Set(d, -0x1.0733160000000p-9f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_82, hn::Set(d, 0x1.15b1e60000000p-4f)),
                        node_13, node_14);
                    const auto node_2 = hn::IfThenElse(hn::Ge(feature_0, hn::Set(d, 0x1.4836d20000000p+1f)),
                        node_6, node_5);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_74, hn::Set(d, 0x1.f2272a0000000p+0f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                hn::StoreU(score, d, scores + row);
            }
            for (; row < rows; ++row) {
                scores[row] = Score(features + row * 164);
            }
        }
    }
}
HWY_AFTER_NAMESPACE();
#if HWY_ONCE
namespace ranker_implementation {
    HWY_EXPORT(Score);
    HWY_EXPORT(Batch);
    HWY_EXPORT(LaneCount);
    HWY_EXPORT(TargetName);
    extern "C" int ranker_batch_v2(const float *features, size_t values, size_t columns, float *scores, size_t rows) {
        if (columns != 164 || values % 164 != 0 || values / 164 != rows) {
            return 1;  // Incompatible shape; never read the input.
        }
        if (rows == 0) {
            return 0;
        }
        if (!features || !scores || values > SIZE_MAX / sizeof(float)) {
            return 2;  // Invalid buffers.
        }
        const uintptr_t input = reinterpret_cast<uintptr_t>(features);
        const uintptr_t output = reinterpret_cast<uintptr_t>(scores);
        if ((input <= output && output - input < values * sizeof(float)) || (output < input && input - output < rows * sizeof(float))) {
            return 3;  // Input/output buffers overlap.
        }
        HWY_DYNAMIC_DISPATCH(Batch)(features, rows, scores);
        return 0;
    }
    extern "C" size_t ranker_lanes() {
        return HWY_DYNAMIC_DISPATCH(LaneCount)();
    }
    extern "C" const char * ranker_target() {
        return HWY_DYNAMIC_DISPATCH(TargetName)();
    }
}
#endif  // HWY_ONCE
