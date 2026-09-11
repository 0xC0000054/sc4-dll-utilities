/*
 * This file is part of sc4-dll-utilities, a set of utilities for
 * SimCity 4 DLL Plugins.
 *
 * Copyright (C) 2026 Nicholas Hayes
 *
 * sc4-dll-utilities is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * sc4-dll-utilities is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with sc4-dll-utilities.
 * If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once
#include <chrono>

class Stopwatch
{
public:
	using clock = std::chrono::steady_clock;
	using time_point = clock::time_point;
	using duration = time_point::duration;

	enum class TimeFormat
	{
		Nanoseconds = 0,
		Microseconds,
		Milliseconds,
		Seconds,
		Minutes,
		Hours
	};

	Stopwatch() : startTimestamp(), elapsed(), isRunning(false)
	{
	}

	duration GetElapsedDuration() const
	{
		duration elapsed = this->elapsed;

		if (isRunning)
		{
			time_point endTimestamp = clock::now();
			duration elapsedThisPeriod = endTimestamp - startTimestamp;
			elapsed += elapsedThisPeriod;
		}

		return elapsed;
	}

	// Gets the elapsed time rounded to the nearest integer.
	template<TimeFormat format>
	duration::rep GetElapsed() const
	{
		const auto duration = GetElapsedDuration();

		if constexpr (format == Stopwatch::TimeFormat::Nanoseconds)
		{
			return std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
		}
		else if constexpr (format == Stopwatch::TimeFormat::Microseconds)
		{
			return std::chrono::round<std::chrono::microseconds>(duration).count();
		}
		else if constexpr (format == Stopwatch::TimeFormat::Milliseconds)
		{
			return std::chrono::round<std::chrono::milliseconds>(duration).count();
		}
		else if constexpr (format == Stopwatch::TimeFormat::Seconds)
		{
			return std::chrono::round<std::chrono::seconds>(duration).count();
		}
		else if constexpr (format == Stopwatch::TimeFormat::Minutes)
		{
			return std::chrono::round<std::chrono::minutes>(duration).count();
		}
		else if constexpr (format == Stopwatch::TimeFormat::Hours)
		{
			return std::chrono::round<std::chrono::hours>(duration).count();
		}
		else
		{
			static_assert(false, "Unsupported TimeFormat value.");
			return 0;
		}
	}

	// Gets the elapsed time including fractional values.
	template<TimeFormat format>
	double GetTotalElapsed() const
	{
		const auto duration = std::chrono::duration<double>(GetElapsedDuration());

		if constexpr (format == Stopwatch::TimeFormat::Nanoseconds)
		{
			return std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
		}
		else if constexpr (format == Stopwatch::TimeFormat::Microseconds)
		{
			return std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
		}
		else if constexpr (format == Stopwatch::TimeFormat::Milliseconds)
		{
			return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
		}
		else if constexpr (format == Stopwatch::TimeFormat::Seconds)
		{
			return std::chrono::duration_cast<std::chrono::seconds>(duration).count();
		}
		else if constexpr (format == Stopwatch::TimeFormat::Minutes)
		{
			return std::chrono::duration_cast<std::chrono::minutes>(duration).count();
		}
		else if constexpr (format == Stopwatch::TimeFormat::Hours)
		{
			return std::chrono::duration_cast<std::chrono::hours>(duration).count();
		}
		else
		{
			static_assert(false, "Unsupported TimeFormat value.");
			return 0.0;
		}
	}

	bool IsRunning() const
	{
		return isRunning;
	}

	void Reset()
	{
		isRunning = false;
		elapsed = duration::zero();
		startTimestamp = time_point();
	}

	void Restart()
	{
		Reset();
		Start();
	}

	void Start()
	{
		if (!isRunning)
		{
			startTimestamp = clock::now();
			isRunning = true;
		}
	}

	void Stop()
	{
		if (isRunning)
		{
			time_point endTimestamp = clock::now();
			duration elapsedThisPeriod = endTimestamp - startTimestamp;
			elapsed += elapsedThisPeriod;
			isRunning = false;
		}
	}

private:
	time_point startTimestamp;
	duration elapsed;
	bool isRunning;
};
