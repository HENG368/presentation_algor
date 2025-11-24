#pragma once

#include <random>
#include <cstdint>

namespace rng {
	inline thread_local std::mt19937 gen{std::random_device{}()};

	inline void setSeed(uint32_t s) {
		gen.seed(s);
	}

	inline std::mt19937 &get() {
		return gen;
	}
}
