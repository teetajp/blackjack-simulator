#include "blackjack_app.h"

using blackjack::BlackJackApp;

void prepareSettings(IdealGasApp::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(BlackJackApp, ci::app::RendererGl, prepareSettings);
