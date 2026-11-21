
#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
using namespace geode::prelude;

class $modify(AutoBuildMenu, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        auto* menu = this->getChildByID("bottom-menu");
        if (!menu) {
            log::warn("AutoBuild Lite: bottom-menu not found");
            return true;
        }

        auto* sprite = ButtonSprite::create("AB");
        if (!sprite) return true;

        auto* button = CCMenuItemSpriteExtra::create(
            sprite,
            this,
            menu_selector(AutoBuildMenu::onAutoBuildPressed)
        );

        if (!button) return true;

        button->setID("autobuild-lite-button"_spr);
        menu->addChild(button);
        menu->updateLayout();

        return true;
    }

    void onAutoBuildPressed(CCObject*) {
        FLAlertLayer::create(
            "AutoBuild Lite",
            "Welcome to AutoBuild Lite!\n\n"
            "Building tools are currently in development.",
            "OK"
        )->show();
    }
};

$on_mod(Loaded) {
    log::info("AutoBuild Lite loaded successfully");
}
