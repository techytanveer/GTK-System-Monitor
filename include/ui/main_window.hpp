#pragma once
#include <gtkmm.h>
#include <libadwaita-1/adwaita.h>
#include <thread>
#include <mutex>
#include <memory>
#include "core/system_snapshot.hpp"
#include "core/provider_interface.hpp"

namespace Shift {
    class MainWindow : public Gtk::ApplicationWindow {
    public:
        MainWindow();
        virtual ~MainWindow();

    private:
        void worker_loop();
        void on_data_update();

        Gtk::Box m_main_layout{Gtk::Orientation::VERTICAL, 12};
        Gtk::Label m_cpu_label{"Initializing..."};
	Gtk::Label m_mem_title_label{"Memory Usage"}; // Static title
	Gtk::Label m_mem_detail_label{"0.0 / 0.0 GB"}; // Live details
        Gtk::LevelBar m_mem_bar;

        std::unique_ptr<IDataProvider> m_provider;
        std::thread m_worker_thread;
        bool m_keep_running{true};
        std::mutex m_data_mutex;
        SystemSnapshot m_shared_data;
        Glib::Dispatcher m_dispatcher;
    };
}
