

# IllusionOS
IllusionOS is a Mock OS that consists of most of the projects I built during siege and than some.
It is fully coded in C and it has applications that were also coded in C. I made this project in order to better
understand the usage of header files and having multiple files of .c to work with within a project.
<br>
This OS features apps like:
- NotSoSpammy: A email advertizing pyramid scheme
- SendyMaily: An email sending app
- NotSoNotFallty: A GUI based git Client
- NotSoNotSecure: A billboard Messaging app
- NotSoSpacy: An alarm Clock
- NotSoNotSpooky: A calculator that screams when you wanna do decimals
- ThreeEyedRaven: A magical Raven's weather app
- JustaGuiFramework: An app that lets you create GUI for your C software

# How to use?
- Execute the binary
- You'll be taken to a retro OS
- Click on the icons on the desktop or the dash to execute programs
- Use the programs as you'd normally use or check out the program's gh repo for more specific usage instructions


# ARCH LIUNX BUILD INSTRUCTIONS

# Arch Linux Build Instructions
| Commands                                            | What They Do?                     |
|-----------------------------------------------------|-----------------------------------|
| git clone https://github.com/acharya/illusionOS.git | Clones into the gh repo           |
| cd illusionOS                                       | Navigates into the illusionOS dir |
| chmod +x install.sh                                 | Makes the install.sh be runnable  |
| ./install.sh                                        | Runs the install Script           |
| cd build                                            | Navigates into the build dir      |
| ./illusionOS                                        | Runs the application              |

# What's inside the install.sh?
| Commands                  | What They Do?                |
|---------------------------|------------------------------|
| sudo pacman -S base-devel | Installs Base devel          |
| sudo pacman -S cmake      | Installs Cmake               |
| sudo pacman -S gtk        | Installs GTK                 |
| sudo pacman -S curl       | Installs Curl                |
| sudo pacman -S gstreamer  | Installs Gstreamer           |
| cd build                  | Navigates into the build dir |
| cmake ..                  | Checks for the Cmake file    |
| cmake --build .           | Executes the build           |
