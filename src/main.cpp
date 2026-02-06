#include "ui/main_window.hpp"
#include <libadwaita-1/adwaita.h>
#include <iostream>

int main(int argc, char* argv[]) {
    // Correctness: Initialize Adwaita BEFORE the app starts
    adw_init();

    auto app = Gtk::Application::create("com.github.tanveer.shift");

    return app->make_window_and_run<Shift::MainWindow>(argc, argv);
}
