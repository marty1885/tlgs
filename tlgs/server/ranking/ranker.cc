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
            score += (features[2] < 0x1.3899200000000p-1f ? (features[24] < 0x1.cca9e00000000p-6f ? (features[74] < 0x1.193ea80000000p+1f ? -0x1.759afa0000000p-5f : 0x1.5653960000000p-7f) : (features[97] < 0x1.8fce0a0000000p-2f ? 0x1.d670c40000000p-7f : -0x1.8943680000000p-6f)) : (features[15] < 0x1.6666660000000p-2f ? (features[95] < 0x1.bc48bc0000000p+2f ? -0x1.c80de40000000p-7f : 0x1.7ffab20000000p-8f) : (features[70] < 0x1.aaaaaa0000000p-2f ? 0x1.7acfd60000000p-6f : -0x1.9c762a0000000p-8f)));
            /* Tree 1: preserve sequential float32 accumulation. */
            score += (features[15] < 0x1.6666660000000p-2f ? (features[3] < 0x1.0ecf560000000p-7f ? (features[84] < 0x1.99999a0000000p-1f ? -0x1.87afc80000000p-5f : 0x1.07b7bc0000000p-5f) : (features[70] < 0x1.aaaaaa0000000p-2f ? -0x1.09e8900000000p-8f : -0x1.c052e40000000p-6f)) : (features[102] < 0x1.17a4040000000p+3f ? (features[14] < 0x1.0000000000000p+0f ? -0x1.8ccfe80000000p-7f : 0x1.e22b1a0000000p-8f) : (!(features[24] >= 0x1.3024960000000p-5f) ? 0x1.630bba0000000p-7f : 0x1.03f1c20000000p-5f)));
            /* Tree 2: preserve sequential float32 accumulation. */
            score += (features[15] < 0x1.5555560000000p-2f ? (features[95] < 0x1.7f8c740000000p+2f ? (features[21] < 0x1.4eac1c0000000p-12f ? -0x1.5f98620000000p-5f : -0x1.2333f60000000p-6f) : (features[55] < 0x1.193ea80000000p+1f ? -0x1.2efd320000000p-7f : 0x1.5376500000000p-6f)) : (!(features[2] >= 0x1.fe19540000000p-1f) ? (features[10] < 0x1.8cd5240000000p+2f ? -0x1.10ea1a0000000p-7f : 0x1.afb83c0000000p-7f) : (features[102] < 0x1.a72a7c0000000p+2f ? -0x1.4c9f1c0000000p-5f : 0x1.1786d80000000p-5f)));
            /* Tree 3: preserve sequential float32 accumulation. */
            score += (features[15] < 0x1.cccccc0000000p-2f ? (!(features[24] >= 0x1.f05a3a0000000p-5f) ? (features[2] < 0x1.1296240000000p-1f ? -0x1.7039520000000p-5f : -0x1.3705100000000p-7f) : (features[10] < 0x1.36072a0000000p+2f ? -0x1.4009f20000000p-6f : 0x1.12f2c80000000p-6f)) : (features[141] < 0x1.78e3600000000p+1f ? (features[2] < 0x1.7408dc0000000p-1f ? -0x1.c35e7a0000000p-6f : 0x1.0dc7140000000p-6f) : (features[64] < 0x1.4141420000000p-5f ? 0x1.15b1b20000000p-6f : -0x1.77e62c0000000p-5f)));
            /* Tree 4: preserve sequential float32 accumulation. */
            score += (features[15] < 0x1.cccccc0000000p-2f ? (!(features[24] >= 0x1.15f18c0000000p-4f) ? (features[2] < 0x1.1296240000000p-1f ? -0x1.7435e20000000p-5f : -0x1.65384e0000000p-7f) : (features[10] < 0x1.36072a0000000p+2f ? -0x1.52eb100000000p-6f : 0x1.143b920000000p-6f)) : (!(features[2] >= 0x1.fe19540000000p-1f) ? (features[10] < 0x1.903ebc0000000p+2f ? -0x1.9bc8000000000p-8f : 0x1.a2adbe0000000p-7f) : (features[140] < 0x1.11b4e60000000p+2f ? 0x1.25ad3e0000000p-5f : -0x1.9ca84c0000000p-6f)));
            /* Tree 5: preserve sequential float32 accumulation. */
            score += (features[15] < 0x1.ddddde0000000p-3f ? (!(features[24] >= 0x1.0dfefe0000000p-4f) ? (features[55] < 0x1.0a2b240000000p+1f ? -0x1.5503f80000000p-6f : 0x1.4dfce60000000p-9f) : (features[70] < 0x1.aaaaaa0000000p-2f ? 0x1.6dd4060000000p-7f : -0x1.bafd5e0000000p-6f)) : (!(features[2] >= 0x1.fe19540000000p-1f) ? (features[2] < 0x1.4447760000000p-1f ? -0x1.2624fc0000000p-5f : 0x1.4944b00000000p-8f) : (features[140] < 0x1.11b4e60000000p+2f ? 0x1.f880ae0000000p-6f : -0x1.8e4a080000000p-8f)));
            /* Tree 6: preserve sequential float32 accumulation. */
            score += (features[15] < 0x1.cccccc0000000p-2f ? (!(features[24] >= 0x1.15f18c0000000p-4f) ? (features[2] < 0x1.3e5e340000000p-1f ? -0x1.346a5a0000000p-5f : -0x1.2fb0da0000000p-7f) : (features[18] < 0x1.6063800000000p-1f ? 0x1.d613920000000p-7f : -0x1.cea6b80000000p-7f)) : (features[145] < 0x1.745d180000000p-3f ? (!(features[24] >= 0x1.0809ba0000000p-9f) ? -0x1.8b69280000000p-7f : 0x1.79cb200000000p-7f) : (features[135] < 0x1.5555560000000p-2f ? -0x1.4abf6a0000000p-5f : 0x1.2b2d300000000p-5f)));
            /* Tree 7: preserve sequential float32 accumulation. */
            score += (features[15] < 0x1.5555560000000p-2f ? (features[3] < 0x1.b7d6c40000000p-8f ? (features[84] < 0x1.99999a0000000p-1f ? -0x1.686c380000000p-5f : 0x1.0860520000000p-5f) : (features[70] < 0x1.aaaaaa0000000p-2f ? -0x1.c468260000000p-9f : -0x1.aeb8420000000p-6f)) : (features[70] < 0x1.aaaaaa0000000p-2f ? (features[2] < 0x1.5b037e0000000p-1f ? -0x1.1e9c940000000p-5f : 0x1.a0f6e80000000p-7f) : (features[19] < 0x1.1f37840000000p-3f ? -0x1.5aff580000000p-6f : 0x1.4aed6a0000000p-5f)));
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
                const auto feature_2 = LoadFeature(d, features + row * 150 + 2, 150);
                const auto feature_15 = LoadFeature(d, features + row * 150 + 15, 150);
                const auto feature_24 = LoadFeature(d, features + row * 150 + 24, 150);
                const auto feature_70 = LoadFeature(d, features + row * 150 + 70, 150);
                const auto feature_74 = LoadFeature(d, features + row * 150 + 74, 150);
                const auto feature_95 = LoadFeature(d, features + row * 150 + 95, 150);
                const auto feature_97 = LoadFeature(d, features + row * 150 + 97, 150);
                /* Tree 0: preserve ordered sums and scope node temporaries. */ {
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_74, hn::Set(d, 0x1.193ea80000000p+1f)),
                        hn::Set(d, -0x1.759afa0000000p-5f), hn::Set(d, 0x1.5653960000000p-7f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_97, hn::Set(d, 0x1.8fce0a0000000p-2f)),
                        hn::Set(d, 0x1.d670c40000000p-7f), hn::Set(d, -0x1.8943680000000p-6f));
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_24, hn::Set(d, 0x1.cca9e00000000p-6f)),
                        node_3, node_4);
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_95, hn::Set(d, 0x1.bc48bc0000000p+2f)),
                        hn::Set(d, -0x1.c80de40000000p-7f), hn::Set(d, 0x1.7ffab20000000p-8f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_70, hn::Set(d, 0x1.aaaaaa0000000p-2f)),
                        hn::Set(d, 0x1.7acfd60000000p-6f), hn::Set(d, -0x1.9c762a0000000p-8f));
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_15, hn::Set(d, 0x1.6666660000000p-2f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.3899200000000p-1f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_3 = LoadFeature(d, features + row * 150 + 3, 150);
                const auto feature_14 = LoadFeature(d, features + row * 150 + 14, 150);
                const auto feature_84 = LoadFeature(d, features + row * 150 + 84, 150);
                const auto feature_102 = LoadFeature(d, features + row * 150 + 102, 150);
                /* Tree 1: preserve ordered sums and scope node temporaries. */ {
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_84, hn::Set(d, 0x1.99999a0000000p-1f)),
                        hn::Set(d, -0x1.87afc80000000p-5f), hn::Set(d, 0x1.07b7bc0000000p-5f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_70, hn::Set(d, 0x1.aaaaaa0000000p-2f)),
                        hn::Set(d, -0x1.09e8900000000p-8f), hn::Set(d, -0x1.c052e40000000p-6f));
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_3, hn::Set(d, 0x1.0ecf560000000p-7f)),
                        node_3, node_4);
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_14, hn::Set(d, 0x1.0000000000000p+0f)),
                        hn::Set(d, -0x1.8ccfe80000000p-7f), hn::Set(d, 0x1.e22b1a0000000p-8f));
                    const auto node_6 = hn::IfThenElse(hn::Ge(feature_24, hn::Set(d, 0x1.3024960000000p-5f)),
                        hn::Set(d, 0x1.03f1c20000000p-5f), hn::Set(d, 0x1.630bba0000000p-7f));
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_102, hn::Set(d, 0x1.17a4040000000p+3f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_15, hn::Set(d, 0x1.6666660000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_10 = LoadFeature(d, features + row * 150 + 10, 150);
                const auto feature_21 = LoadFeature(d, features + row * 150 + 21, 150);
                const auto feature_55 = LoadFeature(d, features + row * 150 + 55, 150);
                /* Tree 2: preserve ordered sums and scope node temporaries. */ {
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_21, hn::Set(d, 0x1.4eac1c0000000p-12f)),
                        hn::Set(d, -0x1.5f98620000000p-5f), hn::Set(d, -0x1.2333f60000000p-6f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_55, hn::Set(d, 0x1.193ea80000000p+1f)),
                        hn::Set(d, -0x1.2efd320000000p-7f), hn::Set(d, 0x1.5376500000000p-6f));
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_95, hn::Set(d, 0x1.7f8c740000000p+2f)),
                        node_3, node_4);
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.8cd5240000000p+2f)),
                        hn::Set(d, -0x1.10ea1a0000000p-7f), hn::Set(d, 0x1.afb83c0000000p-7f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_102, hn::Set(d, 0x1.a72a7c0000000p+2f)),
                        hn::Set(d, -0x1.4c9f1c0000000p-5f), hn::Set(d, 0x1.1786d80000000p-5f));
                    const auto node_2 = hn::IfThenElse(hn::Ge(feature_2, hn::Set(d, 0x1.fe19540000000p-1f)),
                        node_6, node_5);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_15, hn::Set(d, 0x1.5555560000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_64 = LoadFeature(d, features + row * 150 + 64, 150);
                const auto feature_141 = LoadFeature(d, features + row * 150 + 141, 150);
                /* Tree 3: preserve ordered sums and scope node temporaries. */ {
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.1296240000000p-1f)),
                        hn::Set(d, -0x1.7039520000000p-5f), hn::Set(d, -0x1.3705100000000p-7f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.36072a0000000p+2f)),
                        hn::Set(d, -0x1.4009f20000000p-6f), hn::Set(d, 0x1.12f2c80000000p-6f));
                    const auto node_1 = hn::IfThenElse(hn::Ge(feature_24, hn::Set(d, 0x1.f05a3a0000000p-5f)),
                        node_4, node_3);
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.7408dc0000000p-1f)),
                        hn::Set(d, -0x1.c35e7a0000000p-6f), hn::Set(d, 0x1.0dc7140000000p-6f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_64, hn::Set(d, 0x1.4141420000000p-5f)),
                        hn::Set(d, 0x1.15b1b20000000p-6f), hn::Set(d, -0x1.77e62c0000000p-5f));
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_141, hn::Set(d, 0x1.78e3600000000p+1f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_15, hn::Set(d, 0x1.cccccc0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_140 = LoadFeature(d, features + row * 150 + 140, 150);
                /* Tree 4: preserve ordered sums and scope node temporaries. */ {
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.1296240000000p-1f)),
                        hn::Set(d, -0x1.7435e20000000p-5f), hn::Set(d, -0x1.65384e0000000p-7f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.36072a0000000p+2f)),
                        hn::Set(d, -0x1.52eb100000000p-6f), hn::Set(d, 0x1.143b920000000p-6f));
                    const auto node_1 = hn::IfThenElse(hn::Ge(feature_24, hn::Set(d, 0x1.15f18c0000000p-4f)),
                        node_4, node_3);
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_10, hn::Set(d, 0x1.903ebc0000000p+2f)),
                        hn::Set(d, -0x1.9bc8000000000p-8f), hn::Set(d, 0x1.a2adbe0000000p-7f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_140, hn::Set(d, 0x1.11b4e60000000p+2f)),
                        hn::Set(d, 0x1.25ad3e0000000p-5f), hn::Set(d, -0x1.9ca84c0000000p-6f));
                    const auto node_2 = hn::IfThenElse(hn::Ge(feature_2, hn::Set(d, 0x1.fe19540000000p-1f)),
                        node_6, node_5);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_15, hn::Set(d, 0x1.cccccc0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                /* Tree 5: preserve ordered sums and scope node temporaries. */ {
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_55, hn::Set(d, 0x1.0a2b240000000p+1f)),
                        hn::Set(d, -0x1.5503f80000000p-6f), hn::Set(d, 0x1.4dfce60000000p-9f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_70, hn::Set(d, 0x1.aaaaaa0000000p-2f)),
                        hn::Set(d, 0x1.6dd4060000000p-7f), hn::Set(d, -0x1.bafd5e0000000p-6f));
                    const auto node_1 = hn::IfThenElse(hn::Ge(feature_24, hn::Set(d, 0x1.0dfefe0000000p-4f)),
                        node_4, node_3);
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.4447760000000p-1f)),
                        hn::Set(d, -0x1.2624fc0000000p-5f), hn::Set(d, 0x1.4944b00000000p-8f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_140, hn::Set(d, 0x1.11b4e60000000p+2f)),
                        hn::Set(d, 0x1.f880ae0000000p-6f), hn::Set(d, -0x1.8e4a080000000p-8f));
                    const auto node_2 = hn::IfThenElse(hn::Ge(feature_2, hn::Set(d, 0x1.fe19540000000p-1f)),
                        node_6, node_5);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_15, hn::Set(d, 0x1.ddddde0000000p-3f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_18 = LoadFeature(d, features + row * 150 + 18, 150);
                const auto feature_135 = LoadFeature(d, features + row * 150 + 135, 150);
                const auto feature_145 = LoadFeature(d, features + row * 150 + 145, 150);
                /* Tree 6: preserve ordered sums and scope node temporaries. */ {
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.3e5e340000000p-1f)),
                        hn::Set(d, -0x1.346a5a0000000p-5f), hn::Set(d, -0x1.2fb0da0000000p-7f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_18, hn::Set(d, 0x1.6063800000000p-1f)),
                        hn::Set(d, 0x1.d613920000000p-7f), hn::Set(d, -0x1.cea6b80000000p-7f));
                    const auto node_1 = hn::IfThenElse(hn::Ge(feature_24, hn::Set(d, 0x1.15f18c0000000p-4f)),
                        node_4, node_3);
                    const auto node_5 = hn::IfThenElse(hn::Ge(feature_24, hn::Set(d, 0x1.0809ba0000000p-9f)),
                        hn::Set(d, 0x1.79cb200000000p-7f), hn::Set(d, -0x1.8b69280000000p-7f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_135, hn::Set(d, 0x1.5555560000000p-2f)),
                        hn::Set(d, -0x1.4abf6a0000000p-5f), hn::Set(d, 0x1.2b2d300000000p-5f));
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_145, hn::Set(d, 0x1.745d180000000p-3f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_15, hn::Set(d, 0x1.cccccc0000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                const auto feature_19 = LoadFeature(d, features + row * 150 + 19, 150);
                /* Tree 7: preserve ordered sums and scope node temporaries. */ {
                    const auto node_3 = hn::IfThenElse(hn::Lt(feature_84, hn::Set(d, 0x1.99999a0000000p-1f)),
                        hn::Set(d, -0x1.686c380000000p-5f), hn::Set(d, 0x1.0860520000000p-5f));
                    const auto node_4 = hn::IfThenElse(hn::Lt(feature_70, hn::Set(d, 0x1.aaaaaa0000000p-2f)),
                        hn::Set(d, -0x1.c468260000000p-9f), hn::Set(d, -0x1.aeb8420000000p-6f));
                    const auto node_1 = hn::IfThenElse(hn::Lt(feature_3, hn::Set(d, 0x1.b7d6c40000000p-8f)),
                        node_3, node_4);
                    const auto node_5 = hn::IfThenElse(hn::Lt(feature_2, hn::Set(d, 0x1.5b037e0000000p-1f)),
                        hn::Set(d, -0x1.1e9c940000000p-5f), hn::Set(d, 0x1.a0f6e80000000p-7f));
                    const auto node_6 = hn::IfThenElse(hn::Lt(feature_19, hn::Set(d, 0x1.1f37840000000p-3f)),
                        hn::Set(d, -0x1.5aff580000000p-6f), hn::Set(d, 0x1.4aed6a0000000p-5f));
                    const auto node_2 = hn::IfThenElse(hn::Lt(feature_70, hn::Set(d, 0x1.aaaaaa0000000p-2f)),
                        node_5, node_6);
                    const auto node_0 = hn::IfThenElse(hn::Lt(feature_15, hn::Set(d, 0x1.5555560000000p-2f)),
                        node_1, node_2);
                    score = hn::Add(score, node_0);
                }
                hn::StoreU(score, d, scores + row);
            }
            for (; row < rows; ++row) {
                scores[row] = Score(features + row * 150);
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
        if (columns != 150 || values % 150 != 0 || values / 150 != rows) {
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
