#include "ui/main_window.hpp"
#include "core/hardware_provider.hpp"

namespace Shift {
    MainWindow::MainWindow() : m_provider(std::make_unique<HardwareProvider>()) {
        set_title("Shift Monitor");
        set_default_size(350, 220);

        // UI Setup 
	// Adwaita styling 
        m_main_layout.set_margin(24);
	m_main_layout.set_spacing(12);

	// CPU label styling
        m_cpu_label.set_halign(Gtk::Align::START);
	m_cpu_label.set_markup("<span size='large' weight='bold'>CPU Usage</span>");
	m_cpu_label.set_margin_bottom(5);
        m_main_layout.append(m_cpu_label);

	// Separator or extra spacing
        m_main_layout.append(*Gtk::make_managed<Gtk::Separator>());

	// Memory Bar styling
	m_mem_title_label.set_text("Memory Usage");
	m_mem_title_label.set_halign(Gtk::Align::START);
        m_mem_title_label.set_markup("<b>Memory</b>"); // Bold title
	m_mem_bar.set_size_request(-1, 8);
	m_mem_bar.set_margin_top(10);
	m_mem_detail_label.set_halign(Gtk::Align::END); // Align details to the right
        m_mem_detail_label.add_css_class("caption");   // Slightly smaller text

        m_main_layout.append(m_mem_title_label);
        m_main_layout.append(m_mem_bar);
	m_main_layout.append(m_mem_detail_label);

        set_child(m_main_layout);

        // Robustness: Connect the thread-safe dispatcher
        m_dispatcher.connect(sigc::mem_fun(*this, &MainWindow::on_data_update));

        // Performance: Start the background polling thread
        m_worker_thread = std::thread(&MainWindow::worker_loop, this);

	// Correctness: Close the thread when the window is closed
        this->signal_hide().connect([this]() {
        m_keep_running = false;
        });

        // Aesthetics: Use a standard system icon
        set_icon_name("utilities-system-monitor");


    }

    void MainWindow::worker_loop() {
        while (m_keep_running) {
            auto new_data = m_provider->get_latest_data();
            {
                std::lock_guard<std::mutex> lock(m_data_mutex);
                m_shared_data = new_data;
            }
            m_dispatcher.emit(); // Alert the UI thread
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }

    void MainWindow::on_data_update() {
        std::lock_guard<std::mutex> lock(m_data_mutex);

        // OLD >    m_cpu_label.set_text("CPU Usage: " + std::to_string((int)m_shared_data.cpu.total_usage) + "%");
	// Update CPU
	m_cpu_label.set_markup("<b>CPU:</b> " + std::to_string((int)m_shared_data.cpu.total_usage) + "%");

	// Update Memory Bar
        m_mem_bar.set_value(m_shared_data.mem.percentage / 100);

	// Update Memory detail label
	double used_gb = m_shared_data.mem.used_bytes / (1024.0 * 1024.0 * 1024.0);
        double total_gb = m_shared_data.mem.total_bytes / (1024.0 * 1024.0 * 1024.0);

	char buffer[64];
        snprintf(buffer, sizeof(buffer), "%.1f / %.1f GiB (%.0f%%)", 
             used_gb, total_gb, m_shared_data.mem.percentage);
        m_mem_detail_label.set_text(buffer);
	
	/*
	 For Robustness, snprintf (or std::format in C++20) is preferred here because std::to_string for doubles is notoriously messy (it often outputs 17.060000). Using %.1f ensures your UI stays clean and professional.
	 */
	
    }

    MainWindow::~MainWindow() {
        m_keep_running = false;
        if (m_worker_thread.joinable()) m_worker_thread.join();
    }
}
