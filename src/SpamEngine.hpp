// Aliou's Buffer v3.6 - Smart Spam Engine
//
// Self-contained (standard library only) so it can be reasoned about and tested without
// the Geode SDK. main.cpp feeds it every real input (press / release, physics tick, game
// mode, level percent) and asks it whether a press should be let through. Everything it
// learns is per level section (5% bands) and can be saved / loaded as plain text.
//
// Time is measured in physics ticks (240 per second at the legit TPS).
#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <deque>
#include <filesystem>
#include <fstream>
#include <map>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

namespace spam {

constexpr int MODES = 8;           // cube, ship, ball, ufo, wave, robot, spider, swing (modeIndex order)
constexpr int BAND = 5;            // section width in percent for pattern memory
constexpr double TPS = 240.0;
constexpr size_t HISTORY = 64;     // presses kept for the live analysis
constexpr int BURST_GAP = 36;      // ticks (0.15 s): a longer gap ends a spam burst
constexpr int BURST_MIN = 4;       // presses before a run counts as spam

// Rough per-mode limits: the shortest press interval that still registers as a separate
// input with a visible effect, and a comfortable default interval. Tuned by hand; the
// engine replaces the default with what worked once it has data for a section.
constexpr std::array<int, MODES> MIN_INTERVAL = { 2, 2, 4, 3, 2, 3, 4, 3 };
constexpr std::array<int, MODES> DEFAULT_INTERVAL = { 14, 8, 16, 12, 6, 10, 14, 10 };

enum class Pattern { None, Steady, Accelerating, Decelerating, Burst, Jitter };

inline char const* patternName(Pattern p) {
    switch (p) {
        case Pattern::Steady: return "steady";
        case Pattern::Accelerating: return "speeding up";
        case Pattern::Decelerating: return "slowing down";
        case Pattern::Burst: return "bursts";
        case Pattern::Jitter: return "uneven";
        default: return "none";
    }
}

struct Stats {
    double mean = 0.0;    // mean interval (ticks)
    double stddev = 0.0;  // interval spread (ticks)
    double slope = 0.0;   // change of interval per press (ticks), <0 = getting faster
    int count = 0;
    double cps() const { return mean > 0.0 ? TPS / mean : 0.0; }
};

// One remembered spam pattern for a section
struct SavedPattern {
    double interval = 0.0;  // mean interval that worked
    double spread = 0.0;
    int passes = 0;         // times this section was passed while spamming
    int fails = 0;          // deaths in this section while spamming
    double safety() const { return (passes + 1.0) / (passes + fails + 2.0); }  // Laplace estimate
};

// A candidate input sequence for predictive branching: presses at these tick offsets
struct Branch {
    std::vector<int> presses;
    int survived = 0;  // filled in by the simulator callback
};

struct Advice {
    bool drop = false;           // rate limiter / stabilizer: swallow this press
    std::string reason;          // why (for the log)
};

class Engine {
public:
    // ---- settings (copied in by main.cpp) ----
    bool enabled = true;
    bool limiter = false;
    int limiterMin = 0;          // 0 = per-mode minimum
    bool stabilizer = false;
    int stabilizerJitter = 1;    // a press this many ticks after the previous one is a double tap
    bool rhythmLock = false;
    double rhythmTolerance = 0.25;  // fraction of the locked interval
    bool warnings = true;

    // ---- live state ----
    std::deque<int64_t> presses;  // ticks of recent presses (current burst)
    int mode = 0;
    int lastMode = -1;
    int percent = 0;
    std::optional<double> lockedInterval;  // rhythm lock target
    int rhythmMisses = 0;
    std::string pendingWarning;            // read and cleared by main.cpp
    std::map<int, SavedPattern> memory;    // band start percent -> pattern
    std::string memoryPath;

    bool inBurst() const { return static_cast<int>(presses.size()) >= BURST_MIN; }

    static Stats stats(std::deque<int64_t> const& p, size_t last = HISTORY) {
        Stats s;
        if (p.size() < 2) {
            return s;
        }
        size_t from = p.size() > last + 1 ? p.size() - last - 1 : 0;
        std::vector<double> iv;
        for (size_t i = from + 1; i < p.size(); ++i) {
            iv.push_back(static_cast<double>(p[i] - p[i - 1]));
        }
        s.count = static_cast<int>(iv.size());
        for (double v : iv) s.mean += v;
        s.mean /= iv.size();
        for (double v : iv) s.stddev += (v - s.mean) * (v - s.mean);
        s.stddev = std::sqrt(s.stddev / iv.size());
        if (iv.size() >= 3) {  // least squares slope over the interval index
            double n = static_cast<double>(iv.size()), sx = 0, sy = 0, sxy = 0, sxx = 0;
            for (size_t i = 0; i < iv.size(); ++i) {
                sx += i; sy += iv[i]; sxy += i * iv[i]; sxx += static_cast<double>(i) * i;
            }
            double den = n * sxx - sx * sx;
            s.slope = den != 0.0 ? (n * sxy - sx * sy) / den : 0.0;
        }
        return s;
    }

    // Adaptive Spam Detection: which kind of spam is this
    Pattern classify() const {
        if (!inBurst()) return Pattern::None;
        auto s = stats(presses, 16);
        double cv = s.mean > 0 ? s.stddev / s.mean : 0.0;
        if (s.slope < -0.08 * s.mean) return Pattern::Accelerating;
        if (s.slope > 0.08 * s.mean) return Pattern::Decelerating;
        if (cv < 0.15) return Pattern::Steady;
        // bursts: a mix of very short and long gaps
        int shortGaps = 0, longGaps = 0;
        for (size_t i = presses.size() > 16 ? presses.size() - 16 : 1; i < presses.size(); ++i) {
            double g = static_cast<double>(presses[i] - presses[i - 1]);
            if (g < 0.6 * s.mean) ++shortGaps;
            if (g > 1.5 * s.mean) ++longGaps;
        }
        if (shortGaps >= 2 && longGaps >= 2) return Pattern::Burst;
        return Pattern::Jitter;
    }

    int minInterval() const { return limiterMin > 0 ? limiterMin : MIN_INTERVAL[std::clamp(mode, 0, MODES - 1)]; }

    static int band(int pct) { return std::clamp(pct, 0, 100) / BAND * BAND; }

    // Adaptive Spam Rate + Spam Frequency Optimizer + Dynamic Spam Switching:
    // the interval to aim for right now (ticks)
    double targetInterval() const {
        // a remembered pattern for this or the next section wins if it is mostly safe
        for (int b : { band(percent), band(percent + BAND) }) {
            auto it = memory.find(b);
            if (it != memory.end() && it->second.passes > 0 && it->second.safety() >= 0.5) {
                return std::max<double>(it->second.interval, minInterval());
            }
        }
        return std::max(DEFAULT_INTERVAL[std::clamp(mode, 0, MODES - 1)], minInterval());
    }

    // Optimal CPS Finder: best remembered CPS for a section, or the mode default
    double optimalCps(int pct) const {
        auto it = memory.find(band(pct));
        double iv = (it != memory.end() && it->second.passes > 0) ? it->second.interval
                                                                  : DEFAULT_INTERVAL[std::clamp(mode, 0, MODES - 1)];
        return TPS / std::max(1.0, iv);
    }

    // Spam Difficulty Estimator (0..10): short and tight intervals are harder. `window` is the
    // timing window in ticks (how far off a press may be), from the simulator when available.
    double difficulty(double window = -1.0) const {
        auto s = stats(presses, 16);
        if (s.count < 2) return 0.0;
        double speed = std::clamp(TPS / s.mean / 20.0, 0.0, 1.0);  // 20 CPS = max speed score
        double tight = window > 0 ? std::clamp(1.0 - window / 8.0, 0.0, 1.0)
                                  : std::clamp(s.stddev / std::max(1.0, s.mean), 0.0, 1.0);
        double length = std::clamp(s.count / 40.0, 0.0, 1.0);
        return std::round((speed * 5.0 + tight * 3.0 + length * 2.0) * 10.0) / 10.0;
    }

    // Spam Pattern Comparison: which pattern produced safer outcomes (-1 a, 1 b, 0 tie)
    static int compare(SavedPattern const& a, SavedPattern const& b) {
        double d = a.safety() - b.safety();
        if (std::abs(d) < 0.05) return a.spread < b.spread ? -1 : (b.spread < a.spread ? 1 : 0);
        return d > 0 ? -1 : 1;
    }

    // Called for every real input. Returns whether a press should be swallowed.
    Advice onInput(bool down, int64_t tick, int modeNow, int pct) {
        Advice a;
        percent = pct;
        mode = std::clamp(modeNow, 0, MODES - 1);
        if (!enabled || !down) {
            return a;
        }
        if (!presses.empty() && tick - presses.back() > BURST_GAP) {
            endBurst(false);
        }
        // Dynamic Spam Switching: a mode change starts a new burst with a new target
        if (lastMode != -1 && lastMode != mode && !presses.empty()) {
            presses.clear();
            lockedInterval.reset();
            warn("spam: mode changed, target now " + fmtCps(TPS / targetInterval()));
        }
        lastMode = mode;
        if (!presses.empty()) {
            int64_t gap = tick - presses.back();
            // Spam Stabilizer: an accidental double tap far shorter than your rhythm
            if (stabilizer && inBurst() && gap <= stabilizerJitter) {
                a.drop = true;
                a.reason = "stabilizer: double tap " + std::to_string(gap) + "t";
                return a;
            }
            // Spam Rate Limiter: faster than the game can register for this mode
            if (limiter && gap < minInterval()) {
                a.drop = true;
                a.reason = "limiter: " + std::to_string(gap) + "t < " + std::to_string(minInterval()) + "t";
                return a;
            }
        }
        presses.push_back(tick);
        while (presses.size() > HISTORY) presses.pop_front();
        if (inBurst()) {
            onBurstPress();
        }
        return a;
    }

    // Spam Failure Predictor: called with the collision forecast for the rhythm continued
    // (ticks until the ghost would crash if you keep this rhythm; horizon = safe).
    void onForecast(int ticksToCrash, int horizon) {
        if (!enabled || !inBurst()) return;
        if (ticksToCrash < horizon) {
            warn("spam: this rhythm crashes in " + std::to_string(ticksToCrash) + "t (" +
                 fmtCps(stats(presses, 8).cps()) + ", try " + fmtCps(TPS / targetInterval()) + ")");
        }
    }

    // Branches for predictive branching: the rhythm continued at a few different rates
    std::vector<Branch> branches(int count, int horizon) const {
        std::vector<Branch> out;
        auto s = stats(presses, 8);
        double base = s.count ? s.mean : targetInterval();
        static constexpr double SCALE[] = { 1.0, 0.85, 1.15, 0.7, 1.3, 0.55, 1.5, 0.0 };
        for (int i = 0; i < std::clamp(count, 1, 8); ++i) {
            Branch b;
            double iv = SCALE[i] > 0.0 ? std::max<double>(minInterval(), base * SCALE[i]) : targetInterval();
            for (double t = iv; t < horizon; t += iv) b.presses.push_back(static_cast<int>(std::lround(t)));
            out.push_back(std::move(b));
        }
        return out;
    }

    // A death (true) or reaching the end of the burst alive (false)
    void endBurst(bool died) {
        if (presses.size() >= static_cast<size_t>(BURST_MIN)) {
            auto s = stats(presses);
            auto& m = memory[band(percent)];
            if (died) {
                ++m.fails;
            }
            else {
                // Spam Pattern Memory: blend in what worked, weighted by past passes
                double w = 1.0 / (m.passes + 1.0);
                m.interval = m.passes ? m.interval * (1.0 - w) + s.mean * w : s.mean;
                m.spread = m.passes ? m.spread * (1.0 - w) + s.stddev * w : s.stddev;
                ++m.passes;
            }
            save();
        }
        presses.clear();
        lockedInterval.reset();
        rhythmMisses = 0;
    }

    void reset() {
        presses.clear();
        lockedInterval.reset();
        lastMode = -1;
        rhythmMisses = 0;
    }

    std::string takeWarning() {
        std::string w;
        w.swap(pendingWarning);
        return w;
    }

    std::string status() const {
        if (!inBurst()) return "";
        auto s = stats(presses, 16);
        std::ostringstream o;
        o.precision(1);
        o << std::fixed << s.cps() << " CPS, " << patternName(classify()) << ", difficulty " << difficulty()
          << "/10, best " << optimalCps(percent) << " CPS";
        return o.str();
    }

    // ---- persistence: "band interval spread passes fails" per line ----
    void load(std::string const& path) {
        memoryPath = path;
        memory.clear();
        std::ifstream in(path);
        int b;
        SavedPattern p;
        while (in >> b >> p.interval >> p.spread >> p.passes >> p.fails) memory[b] = p;
    }

    void save() const {
        if (memoryPath.empty()) return;
        std::error_code ec;
        std::filesystem::create_directories(std::filesystem::path(memoryPath).parent_path(), ec);
        std::ofstream out(memoryPath, std::ios::trunc);
        for (auto const& [b, p] : memory) {
            out << b << ' ' << p.interval << ' ' << p.spread << ' ' << p.passes << ' ' << p.fails << '\n';
        }
    }

private:
    static std::string fmtCps(double cps) {
        std::ostringstream o;
        o.precision(1);
        o << std::fixed << cps << " CPS";
        return o.str();
    }

    void warn(std::string w) {
        if (warnings) pendingWarning = std::move(w);
    }

    void onBurstPress() {
        auto s = stats(presses, 8);
        // Spam Rhythm Lock: lock the rhythm once it settles, then report when you drift off it
        if (rhythmLock) {
            if (!lockedInterval && s.count >= 6 && s.stddev < 0.15 * s.mean) {
                lockedInterval = s.mean;
                warn("spam: rhythm locked at " + fmtCps(TPS / s.mean));
            }
            else if (lockedInterval) {
                double gap = static_cast<double>(presses.back() - presses[presses.size() - 2]);
                if (std::abs(gap - *lockedInterval) > rhythmTolerance * *lockedInterval) {
                    if (++rhythmMisses >= 2) {
                        warn("spam: off rhythm (" + std::to_string(static_cast<int>(gap)) + "t vs " +
                             std::to_string(static_cast<int>(std::lround(*lockedInterval))) + "t)");
                        rhythmMisses = 0;
                    }
                }
                else {
                    rhythmMisses = 0;
                }
            }
        }
        // Adaptive Spam Rate: tell the player when they are far from what this section wants
        double target = targetInterval();
        if (s.count >= 6 && (s.mean < 0.6 * target || s.mean > 1.6 * target)) {
            warn("spam: " + fmtCps(s.cps()) + " vs suggested " + fmtCps(TPS / target));
        }
    }
};

inline Engine& engine() {
    static Engine e;
    return e;
}

}  // namespace spam
