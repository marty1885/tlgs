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
            score += (!(features[3] >= 0x1.e1e1e20000000p-5f) ? (features[16] < 0x1.3333340000000p-2f ? (features[0] < 0x1.4b52ea0000000p+1f ? -0x1.82fef80000000p-5f : -0x1.d04fb00000000p-7f) : (features[8] < 0x1.99999a0000000p-3f ? -0x1.6e0ffc0000000p-7f : 0x1.96813e0000000p-6f)) : (features[6] < 0x1.5555560000000p-1f ? (features[21] < 0x1.90be5c0000000p-7f ? -0x1.1312900000000p-5f : 0x1.f3c7900000000p-9f) : (features[3] < 0x1.5555560000000p-3f ? 0x1.faba6a0000000p-9f : 0x1.879d920000000p-6f)));
            /* Tree 1: preserve sequential float32 accumulation. */
            score += (features[6] < 0x1.8000000000000p-1f ? (features[21] < 0x1.1569e60000000p-7f ? (features[105] < 0x1.e50d7a0000000p-2f ? -0x1.6849f60000000p-5f : 0x1.0ff0f20000000p-5f) : (features[61] < 0x1.63e2360000000p+2f ? -0x1.6775dc0000000p-6f : 0x1.13a3e20000000p-6f)) : (features[14] < 0x1.99999a0000000p-1f ? (features[24] < 0x1.07236a0000000p-3f ? -0x1.8a42300000000p-8f : 0x1.3361fe0000000p-6f) : (features[5] < 0x1.b6db6e0000000p-2f ? 0x1.b57bc80000000p-8f : 0x1.0b2d780000000p-5f)));
            /* Tree 2: preserve sequential float32 accumulation. */
            score += (features[5] < 0x1.e01e020000000p-7f ? (features[0] < 0x1.340c520000000p+1f ? (features[67] < 0x1.1111120000000p-4f ? -0x1.ace1e00000000p-5f : -0x1.0290b60000000p-6f) : (features[75] < 0x1.06dce60000000p+3f ? -0x1.a4f3020000000p-8f : -0x1.07de920000000p-5f)) : (features[15] < 0x1.5555560000000p-3f ? (features[64] < 0x1.3333340000000p-3f ? -0x1.ca8f340000000p-10f : -0x1.1a3eae0000000p-5f) : (features[3] < 0x1.5555560000000p-3f ? -0x1.922d7c0000000p-10f : 0x1.1d28660000000p-6f)));
            /* Tree 3: preserve sequential float32 accumulation. */
            score += (!(features[3] >= 0x1.5555560000000p-3f) ? (features[5] < 0x1.b6db6e0000000p-2f ? (!(features[21] >= 0x1.cd9bc20000000p-7f) ? -0x1.fec75c0000000p-6f : 0x1.030d320000000p-7f) : (features[15] < 0x1.1111120000000p-2f ? -0x1.ec0cda0000000p-7f : 0x1.83005a0000000p-8f)) : (features[18] < 0x1.64ac960000000p-1f ? (features[5] < 0x1.3333340000000p-1f ? 0x1.9d8e760000000p-9f : 0x1.66fbd80000000p-6f) : (features[11] < 0x1.92e2a00000000p-6f ? -0x1.3c2cee0000000p-5f : 0x1.bd13fa0000000p-19f)));
            /* Tree 4: preserve sequential float32 accumulation. */
            score += (features[3] < 0x1.5555560000000p-3f ? (features[5] < 0x1.5555560000000p-7f ? (features[21] < 0x1.96bb660000000p-7f ? -0x1.50a5dc0000000p-5f : 0x1.b3dfde0000000p-10f) : (features[75] < 0x1.199bc40000000p+3f ? -0x1.ba3f1e0000000p-7f : 0x1.9e94840000000p-7f)) : (features[9] < 0x1.d659cc0000000p+2f ? (!(features[2] >= 0x1.fa99b40000000p-1f) ? -0x1.db1a8a0000000p-7f : 0x1.cd36c80000000p-7f) : (features[75] < 0x1.3588380000000p+3f ? 0x1.2fc2aa0000000p-6f : -0x1.9b0a8e0000000p-6f)));
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
                const auto feature_0 = LoadFeature(d, features + row * 111 + 0, 111);
                const auto feature_3 = LoadFeature(d, features + row * 111 + 3, 111);
                const auto feature_6 = LoadFeature(d, features + row * 111 + 6, 111);
                const auto feature_8 = LoadFeature(d, features + row * 111 + 8, 111);
                const auto feature_16 = LoadFeature(d, features + row * 111 + 16, 111);
                const auto feature_21 = LoadFeature(d, features + row * 111 + 21, 111);
                /* Tree 0: preserve ordered sums and scope node temporaries. */ {
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_0, hn::Set(d, 0x1.4b52ea0000000p+1f)),
                        hn::Set(d, -0x1.82fef80000000p-5f), hn::Set(d, -0x1.d04fb00000000p-7f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_8, hn::Set(d, 0x1.99999a0000000p-3f)),
                        hn::Set(d, -0x1.6e0ffc0000000p-7f), hn::Set(d, 0x1.96813e0000000p-6f));
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_16, hn::Set(d, 0x1.3333340000000p-2f)),
                        node_3, node_4);
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_21, hn::Set(d, 0x1.90be5c0000000p-7f)),
                        hn::Set(d, -0x1.1312900000000p-5f), hn::Set(d, 0x1.f3c7900000000p-9f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_3, hn::Set(d, 0x1.5555560000000p-3f)),
                        hn::Set(d, 0x1.faba6a0000000p-9f), hn::Set(d, 0x1.879d920000000p-6f));
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_6, hn::Set(d, 0x1.5555560000000p-1f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Ge(feature_3, hn::Set(d, 0x1.e1e1e20000000p-5f)),
                        node_2, node_1);
                    score = hn::Add(score, node_0);
                }
                const auto feature_5 = LoadFeature(d, features + row * 111 + 5, 111);
                const auto feature_14 = LoadFeature(d, features + row * 111 + 14, 111);
                const auto feature_24 = LoadFeature(d, features + row * 111 + 24, 111);
                const auto feature_61 = LoadFeature(d, features + row * 111 + 61, 111);
                const auto feature_105 = LoadFeature(d, features + row * 111 + 105, 111);
                /* Tree 1: preserve ordered sums and scope node temporaries. */ {
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_105, hn::Set(d, 0x1.e50d7a0000000p-2f)),
                        hn::Set(d, -0x1.6849f60000000p-5f), hn::Set(d, 0x1.0ff0f20000000p-5f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_61, hn::Set(d, 0x1.63e2360000000p+2f)),
                        hn::Set(d, -0x1.6775dc0000000p-6f), hn::Set(d, 0x1.13a3e20000000p-6f));
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_21, hn::Set(d, 0x1.1569e60000000p-7f)),
                        node_3, node_4);
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_24, hn::Set(d, 0x1.07236a0000000p-3f)),
                        hn::Set(d, -0x1.8a42300000000p-8f), hn::Set(d, 0x1.3361fe0000000p-6f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_5, hn::Set(d, 0x1.b6db6e0000000p-2f)),
                        hn::Set(d, 0x1.b57bc80000000p-8f), hn::Set(d, 0x1.0b2d780000000p-5f));
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_14, hn::Set(d, 0x1.99999a0000000p-1f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_6, hn::Set(d, 0x1.8000000000000p-1f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_15 = LoadFeature(d, features + row * 111 + 15, 111);
                const auto feature_64 = LoadFeature(d, features + row * 111 + 64, 111);
                const auto feature_67 = LoadFeature(d, features + row * 111 + 67, 111);
                const auto feature_75 = LoadFeature(d, features + row * 111 + 75, 111);
                /* Tree 2: preserve ordered sums and scope node temporaries. */ {
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_67, hn::Set(d, 0x1.1111120000000p-4f)),
                        hn::Set(d, -0x1.ace1e00000000p-5f), hn::Set(d, -0x1.0290b60000000p-6f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_75, hn::Set(d, 0x1.06dce60000000p+3f)),
                        hn::Set(d, -0x1.a4f3020000000p-8f), hn::Set(d, -0x1.07de920000000p-5f));
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_0, hn::Set(d, 0x1.340c520000000p+1f)),
                        node_3, node_4);
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_64, hn::Set(d, 0x1.3333340000000p-3f)),
                        hn::Set(d, -0x1.ca8f340000000p-10f), hn::Set(d, -0x1.1a3eae0000000p-5f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_3, hn::Set(d, 0x1.5555560000000p-3f)),
                        hn::Set(d, -0x1.922d7c0000000p-10f), hn::Set(d, 0x1.1d28660000000p-6f));
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_15, hn::Set(d, 0x1.5555560000000p-3f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_5, hn::Set(d, 0x1.e01e020000000p-7f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_11 = LoadFeature(d, features + row * 111 + 11, 111);
                const auto feature_18 = LoadFeature(d, features + row * 111 + 18, 111);
                /* Tree 3: preserve ordered sums and scope node temporaries. */ {
                    const auto node_3 = hn::IfThenElse(hn::Ge(feature_21, hn::Set(d, 0x1.cd9bc20000000p-7f)),
                        hn::Set(d, 0x1.030d320000000p-7f), hn::Set(d, -0x1.fec75c0000000p-6f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_15, hn::Set(d, 0x1.1111120000000p-2f)),
                        hn::Set(d, -0x1.ec0cda0000000p-7f), hn::Set(d, 0x1.83005a0000000p-8f));
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_5, hn::Set(d, 0x1.b6db6e0000000p-2f)),
                        node_3, node_4);
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_5, hn::Set(d, 0x1.3333340000000p-1f)),
                        hn::Set(d, 0x1.9d8e760000000p-9f), hn::Set(d, 0x1.66fbd80000000p-6f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_11, hn::Set(d, 0x1.92e2a00000000p-6f)),
                        hn::Set(d, -0x1.3c2cee0000000p-5f), hn::Set(d, 0x1.bd13fa0000000p-19f));
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_18, hn::Set(d, 0x1.64ac960000000p-1f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Ge(feature_3, hn::Set(d, 0x1.5555560000000p-3f)),
                        node_2, node_1);
                    score = hn::Add(score, node_0);
                }
                const auto feature_2 = LoadFeature(d, features + row * 111 + 2, 111);
                const auto feature_9 = LoadFeature(d, features + row * 111 + 9, 111);
                /* Tree 4: preserve ordered sums and scope node temporaries. */ {
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_21, hn::Set(d, 0x1.96bb660000000p-7f)),
                        hn::Set(d, -0x1.50a5dc0000000p-5f), hn::Set(d, 0x1.b3dfde0000000p-10f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_75, hn::Set(d, 0x1.199bc40000000p+3f)),
                        hn::Set(d, -0x1.ba3f1e0000000p-7f), hn::Set(d, 0x1.9e94840000000p-7f));
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_5, hn::Set(d, 0x1.5555560000000p-7f)),
                        node_3, node_4);
                    const auto node_5 = hn::IfThenElse(hn::Ge(feature_2, hn::Set(d, 0x1.fa99b40000000p-1f)),
                        hn::Set(d, 0x1.cd36c80000000p-7f), hn::Set(d, -0x1.db1a8a0000000p-7f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_75, hn::Set(d, 0x1.3588380000000p+3f)),
                        hn::Set(d, 0x1.2fc2aa0000000p-6f), hn::Set(d, -0x1.9b0a8e0000000p-6f));
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_9, hn::Set(d, 0x1.d659cc0000000p+2f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_3, hn::Set(d, 0x1.5555560000000p-3f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                hn::StoreU(score, d, scores + row);
            }
            for (; row < rows; ++row) {
                scores[row] = Score(features + row * 111);
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
        if (columns != 111 || values % 111 != 0 || values / 111 != rows) {
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
