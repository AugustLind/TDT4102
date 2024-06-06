#include "AnimationWindow.h"
#include "Emoji.h"

// Definer størrelse på vindu og emoji
void drawEmojis(std::vector<std::unique_ptr<Emoji>>& emojis, AnimationWindow& win) {
    for (const auto& emoji : emojis) {
        emoji->draw(win);
    }
}

int main() {
    const Point tl{100, 100};
    constexpr int emojiRadius = 50;
    constexpr int eyeRadius = 8;
    constexpr int startDeg = 180;
    constexpr int endDeg = 360;

    const string win_label{"Emoji factory"};
    AnimationWindow win{tl.x, tl.y, 600, 400, win_label};

    // Opprett emoji-objekter
    std::vector<std::unique_ptr<Emoji>> emojis;
    emojis.push_back(make_unique<SmillingFace>(tl, emojiRadius, eyeRadius, startDeg, endDeg));

    const Point tl2{200, 100};
    emojis.push_back(make_unique<SadFace>(tl2, emojiRadius, eyeRadius, startDeg, endDeg));

    const Point tl3{300, 100};
    emojis.push_back(make_unique<AngryFace>(tl3, emojiRadius, eyeRadius, startDeg, endDeg));

    const Point tl4{400, 100};
    emojis.push_back(make_unique<SuprisedFace>(tl4, emojiRadius, eyeRadius));

    const Point tl5{500, 100};
    emojis.push_back(make_unique<ScaredFace>(tl5, emojiRadius, eyeRadius));

    // Tegn emojiene til vinduet
    drawEmojis(emojis, win);

    win.wait_for_close();

    return 0;
}