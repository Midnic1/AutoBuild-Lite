#include <Geode/Geode.hpp>
#include <Geode/modify/CCDirector.hpp>

using namespace geode::prelude;

// Rolling window of frame times, in seconds.
static std::array<float, 120> s_frames{};
static size_t s_index = 0;
static size_t s_count = 0;

// Average FPS and 1% low (slowest 1% of recent frames) from the window.
static std::pair<int, int> frameStats() {
    if (s_count == 0) return {0, 0};
    std::vector<float> sorted(s_frames.begin(), s_frames.begin() + s_count);
    float sum = 0.f;
    for (float f : sorted) sum += f;
    float avg = sum / s_count;
    std::sort(sorted.begin(), sorted.end(), std::greater<float>());
    size_t n = std::max<size_t>(1, s_count / 100);
    float worst = 0.f;
    for (size_t i = 0; i < n; ++i) worst += sorted[i];
    worst /= n;
    return {static_cast<int>(1.f / avg), static_cast<int>(1.f / worst)};
}

class $modify(PerfDirector, CCDirector) {
    struct Fields {
        CCLabelBMFont* label = nullptr;
    };

    void drawScene() {
        float dt = this->getDeltaTime();
        if (dt > 0.f) {
            s_frames[s_index] = dt;
            s_index = (s_index + 1) % s_frames.size();
            s_count = std::min(s_count + 1, s_frames.size());
        }

        CCDirector::drawScene();

        auto [fps, low] = frameStats();
        auto* scene = this->getRunningScene();
        if (!scene) return;
        if (!m_fields->label) {
            m_fields->label = CCLabelBMFont::create("", "bigFont.fnt");
            m_fields->label->setAnchorPoint({0.f, 1.f});
            m_fields->label->setScale(0.4f);
            m_fields->label->setZOrder(10000);
            scene->addChild(m_fields->label);
        }
        auto winSize = this->getWinSize();
        m_fields->label->setPosition({4.f, winSize.height - 4.f});
        m_fields->label->setString(fmt::format("{} fps | 1% low {}", fps, low).c_str());
    }
};

// Entry point: runs once the mod loads on any platform.
$on_mod(Loaded) {
    log::info("GD Perf 0.2.0 loaded");
}
