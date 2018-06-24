#include <gtest/gtest.h>
#include "snd.h"

TEST(DenormalTest, DenormalCancel) {
  float a = snd::denormalCancel<float>(static_cast<float>(1e-40f));
  EXPECT_FLOAT_EQ(0, a);
}
