/*
 * This file is part of the PRM project.
 *
 * PRM is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * PRM is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with PRM. If not, see <https://www.gnu.org/licenses/>.
 */

#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include <memory>
#include <filesystem>
#include "contact.h"
#include "contact_repository.h"
#include "contact_service.h"
#include "utility.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Get the home directory and create the PRM directory if it doesn't exist
    std::string homeDir = getHomeDirectory();
    std::string prmDir = homeDir + "/.PRM";
    if (!std::filesystem::exists(prmDir)) {
        std::filesystem::create_directory(prmDir);
    }

    // Database path
    std::string dbPath = prmDir + "/prm.db";

    // Create the repository and service
    auto contactRepository = std::make_shared<ContactRepository>(dbPath);
    ContactService contactService(contactRepository);

    // Set up the UI
    QWidget window;
    QVBoxLayout *layout = new QVBoxLayout(&window);

    QLabel *title = new QLabel("PRM");
    layout->addWidget(title);


    window.setLayout(layout);
    window.resize(400, 300);
    window.show();

    return QApplication::exec();
}
