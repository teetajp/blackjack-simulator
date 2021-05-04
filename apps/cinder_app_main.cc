#include "blackjack_app.h"

using blackjack::BlackjackApp;

void prepareSettings(BlackjackApp::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(BlackjackApp, ci::app::RendererGl, prepareSettings);
